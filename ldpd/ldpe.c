/*
 * Copyright (c) 2005 Claudio Jeker <claudio@openbsd.org>
 * Copyright (c) 2004, 2008 Esben Norby <norby@openbsd.org>
 * Copyright (c) 2003, 2004 Henning Brauer <henning@openbsd.org>
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

#include "ldpd.h"
#include "ldpe.h"
#include "ldp_debug.h"

void	 recv_packet(int, short, void *);

extern struct zebra_privs_t ldpd_privs;

/* label distribution protocol engine */
void
ldpe(void)
{
	struct sockaddr_in	 disc_addr, sess_addr;

	/* create the discovery UDP socket */
	disc_addr.sin_family = AF_INET;
	disc_addr.sin_port = htons(LDP_PORT);
	disc_addr.sin_addr.s_addr = INADDR_ANY;

	if ((ldpd_conf->ldp_discovery_socket = socket(AF_INET, SOCK_DGRAM,
	    IPPROTO_UDP)) == -1)
		fatal("error creating discovery socket");

	if (ldpd_privs.change (ZPRIVS_RAISE))
		zlog_err ("ldpe: could not raise privs");

	if (bind(ldpd_conf->ldp_discovery_socket, (struct sockaddr *)&disc_addr,
	    sizeof(disc_addr)) == -1)
		fatal("error binding discovery socket");

	if (ldpd_privs.change (ZPRIVS_LOWER))
		zlog_err ("ldpe: could not lower privs");

	/* set some defaults */
	if (if_set_mcast_ttl(ldpd_conf->ldp_discovery_socket,
	    IP_DEFAULT_MULTICAST_TTL) == -1)
		fatal("if_set_mcast_ttl");
	if (if_set_mcast_loop(ldpd_conf->ldp_discovery_socket) == -1)
		fatal("if_set_mcast_loop");
	if (if_set_tos(ldpd_conf->ldp_discovery_socket,
	    IPTOS_PREC_INTERNETCONTROL) == -1)
		fatal("if_set_tos");
	if (if_set_recvif(ldpd_conf->ldp_discovery_socket, 1) == -1)
		fatal("if_set_recvif");
	if_set_recvbuf(ldpd_conf->ldp_discovery_socket);

	/* create the session TCP socket */
	sess_addr.sin_family = AF_INET;
	sess_addr.sin_port = htons(LDP_PORT);
	sess_addr.sin_addr.s_addr = INADDR_ANY;

	if ((ldpd_conf->ldp_session_socket = socket(AF_INET, SOCK_STREAM,
	    IPPROTO_TCP)) == -1)
		fatal("error creating session socket");

	if (if_set_reuse(ldpd_conf->ldp_session_socket, 1) == -1)
		fatal("if_set_reuse");

	if (ldpd_privs.change (ZPRIVS_RAISE))
		zlog_err ("ldpe: could not raise privs");

	if (bind(ldpd_conf->ldp_session_socket, (struct sockaddr *)&sess_addr,
	    sizeof(sess_addr)) == -1)
		fatal("error binding session socket");

	if (ldpd_privs.change (ZPRIVS_LOWER))
		zlog_err ("ldpe: could not lower privs");

	if (listen(ldpd_conf->ldp_session_socket, LDP_BACKLOG) == -1)
		fatal("error in listen on session socket");

	/* set some defaults */
	if (if_set_tos(ldpd_conf->ldp_session_socket,
	    IPTOS_PREC_INTERNETCONTROL) == -1)
		fatal("if_set_tos");
	session_socket_blockmode(ldpd_conf->ldp_session_socket, BM_NONBLOCK);

	/* setup event handler */
	ldpd_conf->t_disc_ev = NULL;
	THREAD_READ_ON (master, ldpd_conf->t_disc_ev, disc_recv_packet,
			ldpd_conf, ldpd_conf->ldp_discovery_socket);

	ldpd_conf->t_sess_ev = NULL;
	THREAD_READ_ON (master, ldpd_conf->t_sess_ev, session_accept,
			ldpd_conf, ldpd_conf->ldp_session_socket);

	pkt_ptr = XCALLOC(MTYPE_LDP, IBUF_READ_SIZE);
}

/* ARGSUSED */
void
ldpe_process(int type, u_int32_t peerid, void *data, u_int16_t datalen)
{
	struct iface		*iface = NULL;
	struct map		 map;
	struct notify_msg	 nm;
	struct nbr		*nbr = NULL;

	switch (type) {
	case IMSG_IF_ENABLE:
	case IMSG_IF_DISABLE:
	case IMSG_ADDRESS_ADD:
	case IMSG_ADDRESS_DEL:
		if (datalen != sizeof(struct iface))
			fatalx("IFINFO imsg with wrong len");
		iface = data;
		switch (type) {
		case IMSG_IF_ENABLE:
			if_fsm(iface, IF_EVT_UP);
			log_event("interface %s up", iface->name);
			break;
		case IMSG_IF_DISABLE:
			if_fsm(iface, IF_EVT_DOWN);
			log_event("interface %s down", iface->name);
			break;
		case IMSG_ADDRESS_ADD:
			ldpe_nbrs_send_adress (iface);
			break;
		case IMSG_ADDRESS_DEL:
			ldpe_nbrs_send_adress_withdraw (iface);
			break;
		}
		break;
	case IMSG_MAPPING_ADD:
	case IMSG_WITHDRAWN_ADD:
	case IMSG_RELEASE_ADD:
	case IMSG_REQUEST_ADD:
		if (datalen != sizeof(map))
			fatalx("invalid size of map request");
		memcpy(&map, data, sizeof(map));

		nbr = nbr_find_peerid(peerid);
		if (nbr == NULL) {
			zlog_debug("ldpe_process: cannot find neighbor");
			return;
		}

		switch (type) {
		case IMSG_MAPPING_ADD:
			nbr_mapping_add(nbr, &nbr->mapping_list, &map);
			break;
		case IMSG_WITHDRAWN_ADD:
			nbr_mapping_add(nbr, &nbr->withdraw_list, &map);
			break;
		case IMSG_RELEASE_ADD:
			nbr_mapping_add(nbr, &nbr->release_list, &map);
			break;
		case IMSG_REQUEST_ADD:
			nbr_mapping_add(nbr, &nbr->request_list, &map);
			break;
		}
		break;
	case IMSG_MAPPING_ADD_END:
	case IMSG_WITHDRAWN_ADD_END:
	case IMSG_RELEASE_ADD_END:
	case IMSG_REQUEST_ADD_END:
		nbr = nbr_find_peerid(peerid);
		if (nbr == NULL) {
			zlog_debug("ldpe_process: cannot find neighbor");
			return;
		}

		switch (type) {
		case IMSG_MAPPING_ADD_END:
			send_labelmapping(nbr);
			break;
		case IMSG_WITHDRAWN_ADD_END:
			send_labelwithdraw(nbr);
			break;
		case IMSG_RELEASE_ADD_END:
			send_labelrelease(nbr);
			break;
		case IMSG_REQUEST_ADD_END:
			send_labelrequest(nbr);
			break;
		}
		break;
	case IMSG_NOTIFICATION_SEND:
		if (datalen != sizeof(nm))
			fatalx("invalid size of OE request");
		memcpy(&nm, data, sizeof(nm));

		nbr = nbr_find_peerid(peerid);
		if (nbr == NULL) {
			zlog_debug("ldpe_process: cannot find neighbor");
			return;
		}

		send_notification_nbr(nbr, nm.status, htonl(nm.messageid),
					  htonl(nm.type));
		break;
	default:
		zlog_debug("ldpe_process: error handling imsg %d", type);
		break;
	}
}
