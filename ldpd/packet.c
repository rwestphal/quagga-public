/*
 * Copyright (c) 2009 Michele Marchetto <michele@openbsd.org>
 * Copyright (c) 2004, 2005, 2008 Esben Norby <norby@openbsd.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <zebra.h>

#include "privs.h"
#include "memory.h"
#include "thread.h"
#include "sockopt.h"
#include "sockunion.h"

#include "ldpd.h"
#include "ldpe.h"
#include "ldp_debug.h"

int		 ldp_hdr_sanity_check(struct ldp_hdr *, u_int16_t,
		    const struct iface *);
struct iface	*find_iface(unsigned int);
ssize_t		 session_get_pdu(struct ibuf_read *, char **);

static int	 msgcnt = 0;
extern struct	 zebra_privs_t ldpd_privs;

int
gen_ldp_hdr(struct ibuf *buf, struct iface *iface, u_int16_t size)
{
	struct ldp_hdr	ldp_hdr;

	bzero(&ldp_hdr, sizeof(ldp_hdr));
	ldp_hdr.version = htons(LDP_VERSION);

	/* We want just the size of the value */
	size -= TLV_HDR_LEN;

	ldp_hdr.length = htons(size);
	ldp_hdr.lsr_id = ldpd_conf->rtr_id.s_addr;

	return (ibuf_add(buf, &ldp_hdr, LDP_HDR_SIZE));
}

int
gen_msg_tlv(struct nbr *nbr, struct ibuf *buf, u_int32_t type, u_int16_t size)
{
	struct ldp_msg	msg;

	/* We want just the size of the value */
	size -= TLV_HDR_LEN;

	bzero(&msg, sizeof(msg));
	msg.type = htons(type);
	msg.length = htons(size);
	msg.msgid = htonl(++msgcnt);

	/* Increase received messages counter */
	if (nbr)
		nbr->msgs_sent++;

	return (ibuf_add(buf, &msg, sizeof(msg)));
}

/* send and receive packets */
int
send_packet(struct iface *iface, void *pkt, size_t len, struct sockaddr_in *dst)
{
	/* set outgoing interface for multicast traffic */
	if (IN_MULTICAST(ntohl(dst->sin_addr.s_addr)))
		if (if_set_mcast(iface) == -1) {
			zlog_warn("send_packet: error setting multicast "
			    "interface, %s", iface->name);
			return (-1);
		}

	if (sendto(iface->discovery_fd, pkt, len, 0,
	    (struct sockaddr *)dst, sizeof(*dst)) == -1) {
		zlog_warn("send_packet: error sending packet on interface %s",
		    iface->name);
		return (-1);
	}

	return (0);
}

/* Discovery functions */
int
disc_recv_packet(struct thread *thread)
{
	struct ldpd_conf	*ldpd_conf = THREAD_ARG (thread);
	char adata[1024];
	struct sockaddr_in	 src;
	struct msghdr		 msg;
	struct iovec		 iov;
	struct ldp_hdr		 ldp_hdr;
	struct ldp_msg		 ldp_msg;
	struct iface		*iface;
	char			*buf;
	ssize_t			 r;
	u_int16_t		 len;
	int			 l;
	unsigned int		 ifindex = 0;
	int			 fd = THREAD_FD (thread);

	/* setup buffer */
	bzero(&msg, sizeof(msg));
	iov.iov_base = buf = pkt_ptr;
	iov.iov_len = IBUF_READ_SIZE;
	msg.msg_name = &src;
	msg.msg_namelen = sizeof(src);
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_control = (void *) adata;
	msg.msg_controllen = sizeof adata;

	if ((r = recvmsg(fd, &msg, 0)) == -1) {
		if (errno != EAGAIN && errno != EINTR)
			zlog_debug("disc_recv_packet: read error: %s",
			    strerror(errno));
		goto out;
	}

#if 0
        cmsg = CMSG_FIRSTHDR(&msg);
        if (cmsg != NULL &&
           cmsg->cmsg_level == IPPROTO_IP &&
           cmsg->cmsg_type == IP_PKTINFO) {
               ifindex = ((struct in_pktinfo *)CMSG_DATA(cmsg))->ipi_ifindex;
        }
#endif

	ifindex = getsockopt_ifindex(AF_INET, &msg);

	len = (u_int16_t)r;

	/* find a matching interface */
	if ((iface = find_iface(ifindex)) == NULL) {
		zlog_debug("disc_recv_packet: cannot find a matching interface");
		goto out;
	}

	/* receiving interface needs to be active */
	if (iface->passive)
		goto out;

	/* LDP header sanity checks */
	if (len < LDP_HDR_SIZE || len > LDP_MAX_LEN) {
		zlog_debug("disc_recv_packet: bad packet size");
		goto out;
	}
	bcopy(buf, &ldp_hdr, sizeof(ldp_hdr));

	if (ntohs(ldp_hdr.version) != LDP_VERSION) {
		zlog_debug("dsc_recv_packet: invalid LDP version %d",
		    ldp_hdr.version);
		goto out;
	}

	if ((l = ldp_hdr_sanity_check(&ldp_hdr, len, iface)) == -1)
		goto out;

	if (l > len) {
		zlog_debug("disc_recv_packet: invalid LDP packet length %d",
		    ntohs(ldp_hdr.length));
		goto out;
	}

	if (len < LDP_HDR_SIZE + LDP_MSG_LEN) {
		zlog_debug("disc_recv_packet: invalid LDP packet length %d",
		    ntohs(ldp_hdr.length));
		goto out;
	}

	bcopy(buf + LDP_HDR_SIZE, &ldp_msg, sizeof(ldp_msg));


	/* switch LDP packet type */
	switch (ntohs(ldp_msg.type)) {
	case MSG_TYPE_HELLO:
		recv_hello(iface, src.sin_addr, buf, len);
		break;
	default:
		zlog_debug("recv_packet: unknown LDP packet type, interface %s",
		    iface->name);
	}

out:
	ldpd_conf->t_disc_ev = NULL;
	THREAD_READ_ON (master, ldpd_conf->t_disc_ev, disc_recv_packet,
			ldpd_conf, ldpd_conf->ldp_discovery_socket);
	return 0;
}

int
ldp_hdr_sanity_check(struct ldp_hdr *ldp_hdr, u_int16_t len,
    const struct iface *iface)
{
	struct in_addr		 addr;

	if (ldp_hdr->lspace_id != 0) {
		addr.s_addr = ldp_hdr->lsr_id;
		zlog_debug("ldp_hdr_sanity_check: invalid label space "
		    "ID %s, interface %s", inet_ntoa(addr), iface->name);
		return (-1);
	}

	return (ntohs(ldp_hdr->length));
}

struct iface *
find_iface(unsigned int ifindex)
{
	struct iface	*iface = NULL;

	LIST_FOREACH(iface, &ldpd_conf->iface_list, entry) {
		if (ifindex == iface->ifindex)
			return iface;
	}

	return (NULL);
}

int
session_accept(struct thread *thread)
{
	struct ldpd_conf	*ldpd_conf = THREAD_ARG (thread);
	struct nbr		*nbr = NULL;
	int			 newfd;
	union sockunion		 su;
	struct sockaddr_in	 sin;
	socklen_t		 len;
	int			 fd = THREAD_FD(thread);

	newfd = sockunion_accept(fd, &su);
	if (newfd == -1) {
		zlog_debug("sess_recv_packet: accept error: %s",
		    strerror(errno));
		goto out;
	}

	session_socket_blockmode(newfd, BM_NONBLOCK);

	nbr = nbr_find_ip(su.sin.sin_addr.s_addr);
	if (nbr == NULL) {
		struct ibuf	*buf;
		/* If there is no neighbor matching there is no
		   Hello adjacency: try to send notification */
		buf = send_notification(S_NO_HELLO, NULL, 0, 0);
		write(newfd, buf->buf, buf->wpos);
		ibuf_free(buf);
		close(newfd);
		goto out;
	}

	len = sizeof(sin);
	nbr->fd = newfd;
	getsockname(nbr->fd, (struct sockaddr *)&sin, &len);
	nbr->local_addr.s_addr = sin.sin_addr.s_addr;
	nbr->local_port = ntohs(sin.sin_port);
	getpeername(nbr->fd, (struct sockaddr *)&sin, &len);
	nbr->remote_port = ntohs(sin.sin_port);

	nbr_fsm(nbr, NBR_EVT_SESSION_UP);

out:
	ldpd_conf->t_sess_ev = NULL;
	THREAD_READ_ON (master, ldpd_conf->t_sess_ev, session_accept,
			ldpd_conf, ldpd_conf->ldp_session_socket);

	return 0;
}

int
session_read(struct thread *thread)
{
	struct nbr	*nbr = THREAD_ARG (thread);
	struct iface	*iface = nbr->iface;
	struct ldp_hdr	*ldp_hdr;
	struct ldp_msg	*ldp_msg;
	char		*buf, *pdu;
	ssize_t		 n, len;
	int		 l, msg_size;
	u_int16_t	 pdu_len;
	int		fd = nbr->fd;

	if ((n = read(fd, nbr->rbuf->buf + nbr->rbuf->wpos,
	    sizeof(nbr->rbuf->buf) - nbr->rbuf->wpos)) == -1) {
		if (errno != EINTR && errno != EAGAIN) {
			session_shutdown(nbr, S_SHUTDOWN, 0, 0);
			return -1;
		}
		/* retry read */
		goto out;
	}
	if (n == 0) {
		/* connection closed */
		session_shutdown(nbr, S_SHUTDOWN, 0, 0);
		return -1;
	}
	nbr->rbuf->wpos += n;

	while ((len = session_get_pdu(nbr->rbuf, &buf)) > 0) {
		pdu = buf;
		ldp_hdr = (struct ldp_hdr *)pdu;
		if (ntohs(ldp_hdr->version) != LDP_VERSION) {
			session_shutdown(nbr, S_BAD_PROTO_VER, 0, 0);
			XFREE(MTYPE_LDP, buf);
			return -1;
		}

		pdu_len = ntohs(ldp_hdr->length);
		if (pdu_len < LDP_HDR_SIZE || pdu_len > LDP_MAX_LEN) {
			session_shutdown(nbr, S_BAD_MSG_LEN, 0, 0);
			XFREE(MTYPE_LDP, buf);
			return -1;
		}

		if ((l = ldp_hdr_sanity_check(ldp_hdr, len, iface)) == -1) {
			session_shutdown(nbr, S_BAD_LDP_ID, 0, 0);
			XFREE(MTYPE_LDP, buf);
			return -1;
		}

		pdu += LDP_HDR_SIZE;
		len -= LDP_HDR_SIZE;

		while (len >= LDP_MSG_LEN) {
			ldp_msg = (struct ldp_msg *)pdu;

			pdu_len = ntohs(ldp_msg->length) + TLV_HDR_LEN;
			if (pdu_len > len ||
			    pdu_len < LDP_MSG_LEN - TLV_HDR_LEN) {
				session_shutdown(nbr, S_BAD_TLV_LEN, 0, 0);
				XFREE(MTYPE_LDP, buf);
				return -1;
			}

			/* Increase received messages counter */
			nbr->msgs_rcvd++;

			/* switch LDP packet type */
			switch (ntohs(ldp_msg->type)) {
			case MSG_TYPE_NOTIFICATION:
				msg_size = recv_notification(nbr, pdu, pdu_len);
				break;
			case MSG_TYPE_INIT:
				msg_size = recv_init(nbr, pdu, pdu_len);
				break;
			case MSG_TYPE_KEEPALIVE:
				msg_size = recv_keepalive(nbr, pdu, pdu_len);
				break;
			case MSG_TYPE_ADDR:
			case MSG_TYPE_ADDRWITHDRAW:
				msg_size = recv_address(nbr, pdu, pdu_len);
				break;
			case MSG_TYPE_LABELMAPPING:
				msg_size = recv_labelmapping(nbr, pdu, pdu_len);
				break;
			case MSG_TYPE_LABELREQUEST:
				msg_size = recv_labelrequest(nbr, pdu, pdu_len);
				break;
			case MSG_TYPE_LABELWITHDRAW:
				msg_size = recv_labelwithdraw(nbr, pdu, pdu_len);
				break;
			case MSG_TYPE_LABELRELEASE:
				msg_size = recv_labelrelease(nbr, pdu, pdu_len);
				break;
			case MSG_TYPE_LABELABORTREQ:
			case MSG_TYPE_HELLO:
			default:
				zlog_debug("session_read: unknown LDP packet "
				    "type interface %s", iface->name);
				XFREE(MTYPE_LDP, buf);
				return -1;
			}

			if (msg_size == -1) {
				/* parser failed, giving up */
				XFREE(MTYPE_LDP, buf);
				return -1;
			}

			/* Analyse the next message */
			pdu += msg_size + TLV_HDR_LEN;
			len -= msg_size + TLV_HDR_LEN;
		}
		XFREE(MTYPE_LDP, buf);
		if (len != 0) {
			session_shutdown(nbr, S_BAD_PDU_LEN, 0, 0);
			return -1;
		}
	}

out:
	nbr->t_read = NULL;
	THREAD_READ_ON (master, nbr->t_read, session_read, nbr, nbr->fd);
	return 0;
}

int
session_write(struct thread *thread)
{
	struct nbr *nbr = THREAD_ARG(thread);

	THREAD_WRITE_OFF(nbr->wbuf.t_write);

	if (msgbuf_write(&nbr->wbuf.wbuf) == -1)
		nbr_fsm(nbr, NBR_EVT_CLOSE_SESSION);

	evbuf_event_add(&nbr->wbuf);

	return 0;
}

void
session_shutdown(struct nbr *nbr, u_int32_t status, u_int32_t msgid,
    u_int32_t type)
{
	log_event("session_shutdown: nbr ID %s, status %x",
	    inet_ntoa(nbr->id), status);

	send_notification_nbr(nbr, status, msgid, type);

	/* try to flush write buffer, if it fails tough shit */
	msgbuf_write(&nbr->wbuf.wbuf);

	nbr_fsm(nbr, NBR_EVT_CLOSE_SESSION);
}

void
session_close(struct nbr *nbr)
{
	log_event("session_close: closing session with nbr ID %s",
	    inet_ntoa(nbr->id));

	evbuf_clear(&nbr->wbuf);
	THREAD_READ_OFF(nbr->t_read);

	LDP_TIMER_OFF(nbr->keepalive_timer);
	LDP_TIMER_OFF(nbr->keepalive_timeout);

	close(nbr->fd);
}

ssize_t
session_get_pdu(struct ibuf_read *r, char **b)
{
	struct ldp_hdr	l;
	size_t		av, dlen, left;

	av = r->wpos;
	if (av < sizeof(l))
		return (0);

	memcpy(&l, r->buf, sizeof(l));
	dlen = ntohs(l.length) + TLV_HDR_LEN;
	if (dlen > av)
		return (0);

	*b = XMALLOC(MTYPE_LDP, dlen);
	memcpy(*b, r->buf, dlen);
	if (dlen < av) {
		left = av - dlen;
		memmove(r->buf, r->buf + dlen, left);
		r->wpos = left;
	} else
		r->wpos = 0;

	return (dlen);
}
