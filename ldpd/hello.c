/*
 * Copyright (c) 2009 Michele Marchetto <michele@openbsd.org>
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

#include "ldpd.h"
#include "ldpe.h"
#include "ldp_debug.h"

int	tlv_decode_hello_prms(char *, u_int16_t, u_int16_t *, u_int16_t *);
int	tlv_decode_opt_hello_prms(char *, u_int16_t, struct in_addr *,
	    u_int32_t *);
int	gen_hello_prms_tlv(struct iface *, struct ibuf *);
int	gen_opt_hello_prms_tlv(struct iface *, struct ibuf *);

int
send_hello(struct iface *iface)
{
	struct sockaddr_in	 dst;
	struct ibuf		*buf;
	u_int16_t		 size;

	dst.sin_port = htons(LDP_PORT);
	dst.sin_family = AF_INET;
#ifdef HAVE_STRUCT_SOCKADDR_IN_SIN_LEN
	dst.sin_len = sizeof(struct sockaddr_in);
#endif /* HAVE_STRUCT_SOCKADDR_IN_SIN_LEN */
	inet_aton(AllRouters, &dst.sin_addr);

	if (iface->passive)
		return (0);

	if ((buf = ibuf_open(LDP_MAX_LEN)) == NULL)
		fatal("send_hello");

	log_pkt_send("send_hello: %s", iface->name);

	size = LDP_HDR_SIZE + sizeof(struct ldp_msg) +
	    sizeof(struct hello_prms_tlv) +
	    sizeof(struct opt_hello_prms_tlv);

	gen_ldp_hdr(buf, iface, size);

	size -= LDP_HDR_SIZE;

	gen_msg_tlv(NULL, buf, MSG_TYPE_HELLO, size);

	gen_hello_prms_tlv(iface, buf);
	gen_opt_hello_prms_tlv(iface, buf);

	send_packet(iface, buf->buf, buf->wpos, &dst);
	ibuf_free(buf);

	return (0);
}

void
recv_hello(struct iface *iface, struct in_addr src, char *buf, u_int16_t len)
{
	struct ldp_msg		 hello;
	struct ldp_hdr		 ldp;
	struct nbr		*nbr = NULL;
	struct in_addr		 address;
	struct in_addr		 transport_addr;
	u_int32_t		 conf_number;
	u_int16_t		 holdtime, flags;
	int			 r;

	bcopy(buf, &ldp, sizeof(ldp));
	buf += LDP_HDR_SIZE;
	len -= LDP_HDR_SIZE;

	bcopy(buf, &hello, sizeof(hello));
	buf += sizeof(struct ldp_msg);
	len -= sizeof(struct ldp_msg);

	r = tlv_decode_hello_prms(buf, len, &holdtime, &flags);
	if (r == -1) {
		address.s_addr = ldp.lsr_id;
		zlog_warn("recv_hello: neighbor %s: failed to decode params",
		    inet_ntoa(address));
		return;
	}

	buf += r;
	len -= r;

	r = tlv_decode_opt_hello_prms(buf, len, &address, &conf_number);
	if (r == -1) {
		address.s_addr = ldp.lsr_id;
		zlog_warn("recv_hello: neighbor %s: failed to decode "
		    "optional params", inet_ntoa(address));
		return;
	}
	if (r != len) {
		address.s_addr = ldp.lsr_id;
		zlog_warn("recv_hello: neighbor %s: unexpected data in message",
		    inet_ntoa(address));
		return;
	}

	nbr = nbr_find_lsrid(ldp.lsr_id);
	if (!nbr) {
		/* set neighbor parameters */
		if (address.s_addr == INADDR_ANY)
			transport_addr.s_addr = src.s_addr;
		else
			transport_addr.s_addr = address.s_addr;

		nbr = nbr_new(ldp.lsr_id, transport_addr, iface);

		nbr->hello_addr.s_addr = src.s_addr;
		nbr->hello_type = flags;

		if (holdtime == 0) {
			/* XXX: lacks support for targeted hellos */
			if (ldpd_conf->holdtime < LINK_DFLT_HOLDTIME)
				nbr->holdtime = ldpd_conf->holdtime;
			else
				nbr->holdtime = LINK_DFLT_HOLDTIME;
		} else if (holdtime == INFINITE_HOLDTIME) {
			/* No timeout for this neighbor */
			nbr->holdtime = ldpd_conf->holdtime;
		} else {
			if (ldpd_conf->holdtime < holdtime)
				nbr->holdtime = ldpd_conf->holdtime;
			else
				nbr->holdtime = holdtime;
		}
	}

	log_pkt_recv("recv_hello: LSR ID %s", inet_ntoa(nbr->id));

	nbr_fsm(nbr, NBR_EVT_HELLO_RCVD);

	if (htonl(nbr->remote_addr.s_addr) < htonl(nbr->local_addr.s_addr) &&
	    nbr->state == NBR_STA_PRESENT && !nbr_pending_idtimer(nbr))
		nbr_act_session_establish(nbr, 1);
}

int
gen_hello_prms_tlv(struct iface *iface, struct ibuf *buf)
{
	struct hello_prms_tlv	parms;

	bzero(&parms, sizeof(parms));
	parms.type = htons(TLV_TYPE_COMMONHELLO);
	parms.length = htons(sizeof(parms.holdtime) + sizeof(parms.flags));
	parms.holdtime = htons(ldpd_conf->holdtime);
	parms.flags = 0;

	return (ibuf_add(buf, &parms, sizeof(parms)));
}

int
gen_opt_hello_prms_tlv(struct iface *iface, struct ibuf *buf)
{
	struct opt_hello_prms_tlv	 parms;
	struct in_addr			*addr;

	bzero(&parms, sizeof(parms));
	parms.type = htons(TLV_TYPE_IPV4TRANSADDR);
	parms.length = htons(sizeof(parms.value));

	if (iface->if_info->transport_addr == TRANSPORT_ADDRESS_INTERFACE)
		addr = &iface->addr;
	else if (iface->if_info->transport_addr == TRANSPORT_ADDRESS_ROUTER_ID)
		addr = &ldpd_conf->rtr_id;
	else if (iface->if_info->transport_addr == TRANSPORT_ADDRESS_STATIC_IP)
		addr = &iface->if_info->transport_addr_static_ip;

	parms.value = addr->s_addr;

	return (ibuf_add(buf, &parms, sizeof(parms)));
}

int
tlv_decode_hello_prms(char *buf, u_int16_t len, u_int16_t *holdtime,
    u_int16_t *flags)
{
	struct hello_prms_tlv	tlv;

	if (len < sizeof(tlv))
		return (-1);
	bcopy(buf, &tlv, sizeof(tlv));

	if (ntohs(tlv.length) != sizeof(tlv) - TLV_HDR_LEN)
		return (-1);

	if (tlv.type != htons(TLV_TYPE_COMMONHELLO))
		return (-1);

	*holdtime = ntohs(tlv.holdtime);
	*flags = ntohs(tlv.flags);

	return (sizeof(tlv));
}

int
tlv_decode_opt_hello_prms(char *buf, u_int16_t len, struct in_addr *addr,
    u_int32_t *conf_number)
{
	struct tlv	tlv;
	int		cons = 0;
	u_int16_t	tlv_len;

	bzero(addr, sizeof(*addr));
	*conf_number = 0;

	while (len >= sizeof(tlv)) {
		bcopy(buf, &tlv, sizeof(tlv));
		tlv_len = ntohs(tlv.length);
		switch (ntohs(tlv.type)) {
		case TLV_TYPE_IPV4TRANSADDR:
			if (tlv_len != sizeof(u_int32_t))
				return (-1);
			bcopy(buf + TLV_HDR_LEN, addr, sizeof(u_int32_t));
			break;
		case TLV_TYPE_CONFIG:
			if (tlv_len != sizeof(u_int32_t))
				return (-1);
			bcopy(buf + TLV_HDR_LEN, conf_number,
			    sizeof(u_int32_t));
			break;
		default:
			/* if unknown flag set, ignore TLV */
			if (!(ntohs(tlv.type) & UNKNOWN_FLAG))
				return (-1);
			break;
		}
		buf += TLV_HDR_LEN + tlv_len;
		len -= TLV_HDR_LEN + tlv_len;
		cons += TLV_HDR_LEN + tlv_len;
	}

	return (cons);
}
