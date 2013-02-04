#include <net/if.h>
#include <netinet/in.h>
#include <linux/socket.h>
#include <linux/mpls.h>
#include <zebra.h>

#include "prefix.h"
#include "interface.h"

#include "zebra/debug.h"
#include "zebra/rt_netlink.h"
#include "zebra/rib.h"
#include "zebra/mpls_lib.h"

static struct nlsock
  netlink_mpls  = { -1, 0, {0}, "netlink-mpls"};

extern const struct message nlmsg_str[];

static int
mpls_kernel_set_interface (struct interface *ifp, unsigned flags)
{
  struct
  {
    struct nlmsghdr n;
    struct ifinfomsg i;
  } req;

  memset (&req, 0, sizeof (req));
  req.n.nlmsg_len = NLMSG_LENGTH (sizeof (struct ifinfomsg));
  req.n.nlmsg_flags = NLM_F_REQUEST;
  req.n.nlmsg_type = RTM_NEWLINK;
  req.i.ifi_family = 0;
  req.i.ifi_change |= IFF_MPLS;
  req.i.ifi_flags = flags;
  req.i.ifi_index = ifp->ifindex;

  return netlink_talk (&req.n, &netlink_mpls);
}

int
mpls_kernel_enable_interface (struct interface *ifp)
{
  return mpls_kernel_set_interface (ifp, IFF_MPLS);
}

int
mpls_kernel_disable_interface (struct interface *ifp)
{
  return mpls_kernel_set_interface (ifp, 0);
}

static int
mpls_kernel_ilm (int cmd, unsigned flags, u_int32_t in_label,
		 struct mpls_lsp *lsp)
{
  struct {
    struct nlmsghdr n;
    struct rtmsg r;
    char buf[1024];
  } req;

  if (IS_ZEBRA_DEBUG_KERNEL)
    zlog_debug ("mpls_kernel_ilm: type=%s, in label=%u",
		lookup (nlmsg_str, cmd), in_label);

  memset (&req, 0, sizeof (req));
  req.n.nlmsg_len = NLMSG_LENGTH (sizeof (struct rtmsg));
  req.n.nlmsg_flags = NLM_F_REQUEST | flags;
  req.n.nlmsg_type = cmd;
  req.r.rtm_family = AF_MPLS;
  req.r.rtm_dst_len = 32;
  req.r.rtm_table = RT_TABLE_MAIN;
  req.r.rtm_protocol = RTPROT_ZEBRA;
  req.r.rtm_scope = RT_SCOPE_UNIVERSE;
  req.r.rtm_type = RTN_UNICAST;

  /* MPLS input label */
  addattr32 (&req.n, sizeof (req), RTA_DST, in_label);

  /* MPLS LSP */
  if (lsp)
    {
      struct rtattr *mpls;

      mpls = addattr_nest (&req.n, sizeof (req), RTA_MPLS);

      /* MPLS label operation */
      if (lsp->remote_label != MPLS_IMPLICIT_NULL)
	{
	  struct mpls_hdr swap = {0};

	  if (IS_ZEBRA_DEBUG_KERNEL)
	    zlog_debug ("mpls_kernel_ilm(): swap to label %u",
			lsp->remote_label);

	  mpls_hdr_set_label (&swap, lsp->remote_label);
	  addattr_l (&req.n, sizeof (req), MPLSA_SWAP, &swap, sizeof (swap));
	}
      else
	{
	  u_int8_t pop = 1;

	  if (IS_ZEBRA_DEBUG_KERNEL)
	    zlog_debug ("mpls_kernel_ilm(): pop 1");

	  addattr_l (&req.n, sizeof (req), MPLSA_POP, &pop, sizeof (pop));
	}

      /* nexthop address */
	{
	  struct sockaddr_in sin;

	  if (IS_ZEBRA_DEBUG_KERNEL)
	    zlog_debug ("mpls_kernel_ilm(): nexthop ipv4 %s",
			inet_ntoa (lsp->addr));

	  memset (&sin, 0, sizeof (sin));
	  sin.sin_family = AF_INET;
	  sin.sin_addr.s_addr = lsp->addr.s_addr;
	  addattr_l (&req.n, sizeof (req), MPLSA_NEXTHOP_ADDR, &sin, sizeof (sin));
	}

      addattr_nest_end (&req.n, mpls);
    }
  /* "No Label" case */
  else
    {
      struct rtattr *mpls;

      if (IS_ZEBRA_DEBUG_KERNEL)
	zlog_debug ("mpls_kernel_ilm(): no label");

      mpls = addattr_nest (&req.n, sizeof (req), RTA_MPLS);
      u_int8_t pop = POP_ALL;
      addattr_l (&req.n, sizeof (req), MPLSA_POP, &pop, sizeof (pop));
      addattr_nest_end (&req.n, mpls);
    }

  /* All MPLS traffic pass through the mpls0 interface */
  if (cmd == RTM_NEWROUTE)
    {
      struct interface *mpls_dev = if_lookup_by_name (MPLS_MASTER_DEV);
      if (! mpls_dev)
	{
	  zlog_err ("mpls_kernel_ilm(): MPLS master device (%s) not found",
		    MPLS_MASTER_DEV);
	  return -1;
	}

      addattr32 (&req.n, sizeof(req), RTA_OIF, mpls_dev->ifindex);
    }

  return netlink_talk (&req.n, &netlink_mpls);
}

int
mpls_kernel_install_ilm (u_int32_t in_label, struct mpls_lsp *lsp)
{
  return mpls_kernel_ilm (RTM_NEWROUTE, NLM_F_CREATE|NLM_F_APPEND, in_label, lsp);
}

int
mpls_kernel_uninstall_ilm (u_int32_t in_label, struct mpls_lsp *lsp)
{
  return mpls_kernel_ilm (RTM_DELROUTE, 0, in_label, lsp);
}

void
mpls_kernel_init (void)
{
  netlink_socket (&netlink_mpls, 0);
}

void
mpls_kernel_exit (void)
{
  close (netlink_mpls.sock);
}
