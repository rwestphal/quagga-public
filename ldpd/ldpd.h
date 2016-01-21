/*
 * Copyright (c) 2009 Michele Marchetto <michele@openbsd.org>
 * Copyright (c) 2004 Esben Norby <norby@openbsd.org>
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

#ifndef _LDPD_H_
#define _LDPD_H_

#include <sys/queue.h>
#include "imsg.h"
#include "tree.h"
#include "if.h"
#include "prefix.h"
#include "ldp.h"

/* default configuration file name */
#define LDPD_DEFAULT_CONFIG     "ldpd.conf"
#define	LDPD_SOCKET		"/var/run/ldpd.sock"

/* LDP VTY port number */
#define LDP_VTY_PORT            2610

#define NBR_IDSELF		1
#define NBR_CNTSTART		(NBR_IDSELF + 1)

#define	LDP_BACKLOG		128

#define LDP_IF_TIMER_ON(T,F,V)                                                \
    do {                                                                      \
      if (!(T))                                                               \
	(T) = thread_add_timer (master, (F), iface, (V));                     \
    } while (0)

#define LDP_NBR_TIMER_ON(T,F,V)                                               \
    do {                                                                      \
      if (!(T))                                                               \
	(T) = thread_add_timer (master, (F), nbr, (V));                       \
    } while (0)

#define LDP_TIMER_OFF(X)                                                      \
    do {                                                                      \
      if (X)                                                                  \
        {                                                                     \
          thread_cancel (X);                                                  \
          (X) = NULL;                                                         \
        }                                                                     \
    } while (0)

struct evbuf {
	struct msgbuf		 wbuf;
	struct thread		*t_write;
	int			(*handler)(struct thread *);
	void			*arg;
};

enum imsg_type {
	IMSG_NONE,
	IMSG_ZEBRA_NETWORK_ADD,
	IMSG_ZEBRA_NETWORK_DEL,
	IMSG_ZEBRA_CHANGE_INPUT_LABEL,
	IMSG_ZEBRA_ADD_LSP,
	IMSG_ZEBRA_DELETE_LSP,
	IMSG_IF_ENABLE,
	IMSG_IF_DISABLE,
	IMSG_LABEL_MAPPING,
	IMSG_LABEL_MAPPING_FULL,
	IMSG_LABEL_REQUEST,
	IMSG_LABEL_RELEASE,
	IMSG_LABEL_WITHDRAW,
	IMSG_LABEL_ABORT,
	IMSG_REQUEST_ADD,
	IMSG_REQUEST_ADD_END,
	IMSG_MAPPING_ADD,
	IMSG_MAPPING_ADD_END,
	IMSG_WITHDRAWN_ADD,
	IMSG_WITHDRAWN_ADD_END,
	IMSG_RELEASE_ADD,
	IMSG_RELEASE_ADD_END,
	IMSG_ADDRESS_ADD,
	IMSG_ADDRESS_DEL,
	IMSG_NOTIFICATION_SEND,
	IMSG_NEIGHBOR_UP,
	IMSG_NEIGHBOR_DOWN,
	IMSG_NEIGHBOR_CHANGE,
};

/* interface states */
#define	IF_STA_NEW		0x00	/* dummy state for reload */
#define	IF_STA_DOWN		0x01
#define	IF_STA_LOOPBACK		0x02
#define	IF_STA_ACTIVE		0x04
#define	IF_STA_ANY		0x07

/* interface events */
enum iface_event {
	IF_EVT_NOTHING,
	IF_EVT_UP,
	IF_EVT_DOWN
};

/* interface actions */
enum iface_action {
	IF_ACT_NOTHING,
	IF_ACT_STRT,
	IF_ACT_RST
};

/* neighbor states */
#define	NBR_STA_DOWN		0x0001
#define	NBR_STA_PRESENT		0x0002
#define	NBR_STA_INITIAL		0x0004
#define	NBR_STA_OPENREC		0x0008
#define	NBR_STA_OPENSENT	0x0010
#define	NBR_STA_OPER		0x0020
#define	NBR_STA_SESSION		(NBR_STA_PRESENT | NBR_STA_INITIAL | \
				NBR_STA_OPENREC | NBR_STA_OPENSENT | \
				NBR_STA_OPER)

/* neighbor events */
enum nbr_event {
	NBR_EVT_NOTHING,
	NBR_EVT_HELLO_RCVD,
	NBR_EVT_SESSION_UP,
	NBR_EVT_CLOSE_SESSION,
	NBR_EVT_INIT_RCVD,
	NBR_EVT_KEEPALIVE_RCVD,
	NBR_EVT_PDU_RCVD,
	NBR_EVT_INIT_SENT,
	NBR_EVT_DOWN
};

/* neighbor actions */
enum nbr_action {
	NBR_ACT_NOTHING,
	NBR_ACT_STRT_ITIMER,
	NBR_ACT_RST_ITIMER,
	NBR_ACT_RST_KTIMEOUT,
	NBR_ACT_STRT_KTIMER,
	NBR_ACT_SESSION_EST,
	NBR_ACT_INIT_SEND,
	NBR_ACT_KEEPALIVE_SEND,
	NBR_ACT_CLOSE_SESSION
};

TAILQ_HEAD(mapping_head, mapping_entry);

struct map {
	struct in_addr	prefix;
	u_int32_t	label;
	u_int32_t	messageid;
	u_int32_t	requestid;
	u_int8_t	prefixlen;
	u_int8_t	flags;
};
#define F_MAP_WILDCARD	0x01	/* wildcard FEC */
#define F_MAP_OPTLABEL	0x02	/* optional label present */
#define F_MAP_REQ_ID	0x04	/* optional request message id present */

struct notify_msg {
	u_int32_t	messageid;
	u_int32_t	status;
	u_int32_t	type;
};

enum transport_addr_type {
	TRANSPORT_ADDRESS_ROUTER_ID = 0,
	TRANSPORT_ADDRESS_INTERFACE,
	TRANSPORT_ADDRESS_STATIC_IP
};

struct iface;

struct ldp_if_info {
	struct iface		*iface;
	int			 ldp_enabled;
	enum transport_addr_type transport_addr;
	struct in_addr		 transport_addr_static_ip;
};

struct iface {
	LIST_ENTRY(iface)	 entry;
	struct thread		*hello_timer;

	LIST_HEAD(, nbr)	 nbr_list;

	struct ldp_if_info	*if_info;
	char			 name[IF_NAMESIZE];
	struct in_addr		 addr;

	time_t			 uptime;
	unsigned int		 ifindex;
	int			 discovery_fd;
	int			 session_fd;
	int			 state;
	int			 mtu;
	u_int16_t		 flags;
	u_int8_t		 linkstate;
	u_int8_t		 passive;
};

/* ldp_conf */
enum blockmodes {
	BM_NORMAL,
	BM_NONBLOCK
};

#define	MODE_DIST_INDEPENDENT	0x01
#define	MODE_DIST_ORDERED	0x02
#define	MODE_RET_LIBERAL	0x04
#define	MODE_RET_CONSERVATIVE	0x08
#define	MODE_ADV_ONDEMAND	0x10
#define	MODE_ADV_UNSOLICITED	0x20

struct ldpd_conf {
	int			ldp_enabled;
	struct thread		*t_disc_ev, *t_sess_ev;
	struct in_addr		rtr_id;
	LIST_HEAD(, iface)	iface_list;

	u_int32_t		opts;
#define LDPD_OPT_EXPLICIT_NULL	0x00000001
	time_t			uptime;
	int			ldp_discovery_socket;
	int			ldp_session_socket;
	int			flags;
	u_int8_t		mode;

	u_int16_t		keepalive;
	u_int16_t		holdtime;
	u_int16_t		hello_interval;
};

/* kroute */
struct kroute {
	struct in_addr	prefix;
	struct in_addr	nexthop;
	u_int32_t	local_label;
	u_int32_t	remote_label;
	u_short		ifindex;
	u_int8_t	prefixlen;
	u_char		connected;
};

/* ldpd.c */
void	ldpd_process(int type, void *data, u_int16_t datalen);
void	evbuf_enqueue(struct evbuf *, struct ibuf *);
void	evbuf_event_add(struct evbuf *);
void	evbuf_init(struct evbuf *, int, int (*)(struct thread *), void *);
void	evbuf_clear(struct evbuf *);

/* ldp_zebra.c */
int	ldp_if_enabled(struct iface *);
int	ldp_zebra_send_change_input_label(struct kroute *);
int	ldp_zebra_send_lsp(int, struct kroute *);
uint32_t ldp_zebra_request_label (void);
void	ldp_zebra_init(void);

/* ldp_vty.c */
#define        TF_BUFS 8
#define        TF_LEN  9
void	ldp_vty_init(void);

/* socket helper functions */
void session_socket_blockmode(int fd, enum blockmodes bm);

/* global configuration status */
extern struct ldpd_conf	*ldpd_conf;

/* LDPd thread master */
extern struct thread_master *master;

#endif	/* _LDPD_H_ */
