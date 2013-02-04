#include <zebra.h>
#include <net/route.h>
#include <netmpls/mpls.h>

#include "privs.h"
#include "prefix.h"
#include "interface.h"
#include "log.h"

#include "zebra/debug.h"
#include "zebra/mpls_lib.h"

extern struct zebra_privs_t zserv_privs;

struct {
  u_int32_t rtseq;
  int fd;
} kr_state;

static int
setifxflags (struct interface *ifp, int value)
{
  int s, xflags, ret;
  struct ifreq my_ifr;

  s = socket(AF_INET, SOCK_DGRAM, 0);
  if (s < 0)
    {
      zlog_err("Cannot create UDP socket: %s", safe_strerror (errno));
      return -1;
    }

  strlcpy (my_ifr.ifr_name, ifp->name, sizeof (my_ifr.ifr_name));
  if (ioctl (s, SIOCGIFXFLAGS, (caddr_t) &my_ifr) < 0)
    zlog_warn ("ioctl(SIOCGIFXFLAGS) failed: %s", safe_strerror (errno));

  xflags = my_ifr.ifr_flags;
  if (value < 0) {
      value = -value;
      xflags &= ~value;
  } else
    xflags |= value;
  my_ifr.ifr_flags = xflags;

  if (zserv_privs.change(ZPRIVS_RAISE))
    zlog_err ("Can't raise privileges");
  ret = ioctl (s, SIOCSIFXFLAGS, (caddr_t) &my_ifr);
  if (zserv_privs.change(ZPRIVS_LOWER))
    zlog_err ("Can't lower privileges");
  if (ret < 0)
    zlog_warn ("ioctl(SIOCSIFXFLAGS) failed: %s", safe_strerror (errno));
  close (s);

  return ret;
}

int
mpls_kernel_enable_interface (struct interface *ifp)
{
  return setifxflags (ifp, IFXF_MPLS);
};

int
mpls_kernel_disable_interface (struct interface *ifp)
{
  return setifxflags (ifp, -IFXF_MPLS);
};

static int
mpls_kernel_ilm (int action, u_int32_t in_label, struct mpls_lsp *lsp)
{
  struct iovec iov[5];
  struct rt_msghdr hdr;
  struct sockaddr_mpls sa_label_in, sa_label_out;
  struct sockaddr_in nexthop;
  int iovcnt = 0;
  int ret;

  if (IS_ZEBRA_DEBUG_KERNEL)
    zlog_debug ("mpls_kernel_ilm: 0x%x, label=%u", action, in_label);

  /* initialize header */
  bzero(&hdr, sizeof (hdr));
  hdr.rtm_version = RTM_VERSION;

  hdr.rtm_type = action;
  hdr.rtm_flags = RTF_UP;
  hdr.rtm_fmask = RTF_MPLS;
  hdr.rtm_seq = kr_state.rtseq++;	/* overflow doesn't matter */
  hdr.rtm_msglen = sizeof (hdr);
  hdr.rtm_hdrlen = sizeof (struct rt_msghdr);
  hdr.rtm_priority = 0;
  /* adjust iovec */
  iov[iovcnt].iov_base = &hdr;
  iov[iovcnt++].iov_len = sizeof (hdr);

  /* in label */
  bzero(&sa_label_in, sizeof (sa_label_in));
  sa_label_in.smpls_len = sizeof (sa_label_in);
  sa_label_in.smpls_family = AF_MPLS;
  sa_label_in.smpls_label = htonl(in_label << MPLS_LABEL_OFFSET);
  /* adjust header */
  hdr.rtm_flags |= RTF_MPLS | RTF_MPATH;
  hdr.rtm_addrs |= RTA_DST;
  hdr.rtm_msglen += sizeof (sa_label_in);
  /* adjust iovec */
  iov[iovcnt].iov_base = &sa_label_in;
  iov[iovcnt++].iov_len = sizeof (sa_label_in);

  /* nexthop */
  bzero(&nexthop, sizeof (nexthop));
  nexthop.sin_len = sizeof (nexthop);
  nexthop.sin_family = AF_INET;
  nexthop.sin_addr.s_addr = (lsp ? lsp->addr.s_addr : htonl (INADDR_LOOPBACK));
  /* adjust header */
  hdr.rtm_flags |= RTF_GATEWAY;
  hdr.rtm_addrs |= RTA_GATEWAY;
  hdr.rtm_msglen += sizeof (nexthop);
  /* adjust iovec */
  iov[iovcnt].iov_base = &nexthop;
  iov[iovcnt++].iov_len = sizeof (nexthop);

  /* If action is RTM_DELETE we have to get rid of MPLS infos */
  if (lsp && lsp->remote_label != NO_LABEL && action != RTM_DELETE)
    {
      bzero(&sa_label_out, sizeof (sa_label_out));
      sa_label_out.smpls_len = sizeof (sa_label_out);
      sa_label_out.smpls_family = AF_MPLS;
      sa_label_out.smpls_label =
	htonl(lsp->remote_label << MPLS_LABEL_OFFSET);
      /* adjust header */
      hdr.rtm_addrs |= RTA_SRC;
      hdr.rtm_flags |= RTF_MPLS;
      hdr.rtm_msglen += sizeof (sa_label_out);
      /* adjust iovec */
      iov[iovcnt].iov_base = &sa_label_out;
      iov[iovcnt++].iov_len = sizeof (sa_label_out);

      if (lsp->remote_label == MPLS_LABEL_IMPLNULL)
	hdr.rtm_mpls = MPLS_OP_POP;
      else
	hdr.rtm_mpls = MPLS_OP_SWAP;
    }

  if (zserv_privs.change(ZPRIVS_RAISE))
    zlog_err ("Can't raise privileges");
  ret = writev (kr_state.fd, iov, iovcnt);
  if (zserv_privs.change(ZPRIVS_LOWER))
    zlog_err ("Can't lower privileges");

  if (ret == -1)
    zlog_err ("mpls_kernel_ilm: %s", safe_strerror (errno));

  return ret;
}

int
mpls_kernel_install_ilm (u_int32_t in_label, struct mpls_lsp *lsp)
{
  return mpls_kernel_ilm (RTM_ADD, in_label, lsp);
}

int
mpls_kernel_uninstall_ilm (u_int32_t in_label, struct mpls_lsp *lsp)
{
  return mpls_kernel_ilm (RTM_DELETE, in_label, lsp);
}

#define MAX_RTSOCK_BUF	128 * 1024
void
mpls_kernel_init (void)
{
  int		rcvbuf, default_rcvbuf;
  socklen_t	optlen;

  if ((kr_state.fd = socket(AF_ROUTE, SOCK_RAW, 0)) == -1) {
      zlog_warn("kr_init: socket");
      return;
  }

  /* grow receive buffer, don't wanna miss messages */
  optlen = sizeof (default_rcvbuf);
  if (getsockopt(kr_state.fd, SOL_SOCKET, SO_RCVBUF,
		 &default_rcvbuf, &optlen) == -1)
    zlog_warn("kr_init getsockopt SOL_SOCKET SO_RCVBUF");
  else
    for (rcvbuf = MAX_RTSOCK_BUF;
	 rcvbuf > default_rcvbuf &&
	 setsockopt(kr_state.fd, SOL_SOCKET, SO_RCVBUF,
		    &rcvbuf, sizeof (rcvbuf)) == -1 && errno == ENOBUFS;
	 rcvbuf /= 2)
      ;	/* nothing */

  kr_state.rtseq = 1;
}

void
mpls_kernel_exit (void)
{
  close (kr_state.fd);
}
