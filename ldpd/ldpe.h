/*
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

#ifndef _LDPE_H_
#define _LDPE_H_

#include "if.h"

#define max(x,y) ((x) > (y) ? (x) : (y))

struct mapping_entry {
	TAILQ_ENTRY(mapping_entry)	entry;
	struct map			map;
};

struct nbr {
	RB_ENTRY(nbr)		 lsrid_tree, addr_tree, pid_tree;
	LIST_ENTRY(nbr)		 entry;
	struct evbuf		 wbuf;
	struct thread		*t_read;
	struct thread		*inactivity_timer;
	struct thread		*keepalive_timer;
	struct thread		*keepalive_timeout;
	struct thread		*initdelay_timer;

	struct mapping_head	 mapping_list;
	struct mapping_head	 withdraw_list;
	struct mapping_head	 request_list;
	struct mapping_head	 release_list;
	struct mapping_head	 abortreq_list;

	struct in_addr		 id;		/* LSR id */
	struct in_addr		 hello_addr;	/* Source IP from HELLO messages */
	struct in_addr		 remote_addr;	/* Remote end of TCP connection */
	in_port_t		 remote_port;	/* Remote port of TCP connection */
	struct in_addr		 local_addr;	/* Local end of TCP connection */
	in_port_t		 local_port;	/* Local port of TCP connection */

	struct ibuf_read	*rbuf;
	struct iface		*iface;

	time_t			 uptime;
	u_int32_t		 peerid;	/* unique ID in DB */

	int			 fd;
	int			 state;

	unsigned int		 msgs_sent;
	unsigned int		 msgs_rcvd;

	u_int16_t		 holdtime;
	u_int16_t		 keepalive;

	u_int8_t		 flags;
	u_int8_t		 hello_type;

};

/* hello.c */
int	 send_hello(struct iface *);
void	 recv_hello(struct iface *,  struct in_addr, char *, u_int16_t);

/* init.c */
void	 send_init(struct nbr *);
int	 recv_init(struct nbr *, char *, u_int16_t);

/* keepalive.c */
void	 send_keepalive(struct nbr *);
int	 recv_keepalive(struct nbr *, char *, u_int16_t);

/* notification.c */
void	 send_notification_nbr(struct nbr *, u_int32_t, u_int32_t, u_int32_t);
struct ibuf	*send_notification(u_int32_t, struct iface *, u_int32_t,
	    u_int32_t);
int	 recv_notification(struct nbr *, char *, u_int16_t);

/* address.c */
void	 send_address(struct nbr *, struct iface *);
int	 recv_address(struct nbr *, char *, u_int16_t);
void	 send_address_withdraw(struct nbr *, struct iface *);

/* labelmapping.c */
#define PREFIX_SIZE(x)	(((x) + 7) / 8)
void	 send_labelmapping(struct nbr *);
int	 recv_labelmapping(struct nbr *, char *, u_int16_t);
void	 send_labelrequest(struct nbr *);
int	 recv_labelrequest(struct nbr *, char *, u_int16_t);
void	 send_labelwithdraw(struct nbr *);
int	 recv_labelwithdraw(struct nbr *, char *, u_int16_t);
void	 send_labelrelease(struct nbr *);
int	 recv_labelrelease(struct nbr *, char *, u_int16_t);
void	 send_labelabortreq(struct nbr *);
int	 recv_labelabortreq(struct nbr *, char *, u_int16_t);

/* ldpe.c */
void		 ldpe(void);
void		 ldpe_process(int type, u_int32_t peerid, void *data, u_int16_t datalen);

/* interface.c */
int		 if_fsm(struct iface *, enum iface_event);

struct iface	*if_new(struct interface *);
void		 if_del(struct iface *);
void		 if_init_ldp(struct iface *);

int		 if_act_start(struct iface *);
int		 if_act_reset(struct iface *);

int	 if_join_group(struct iface *, struct in_addr *);
int	 if_leave_group(struct iface *, struct in_addr *);
int	 if_set_mcast(struct iface *);
int	 if_set_recvif(int, int);
void	 if_set_recvbuf(int);
int	 if_set_mcast_loop(int);
int	 if_set_mcast_ttl(int, u_int8_t);
int	 if_set_tos(int, int);
int	 if_set_reuse(int, int);

/* neighbor.c */
struct nbr	*nbr_new(u_int32_t, struct in_addr, struct iface *);
void		 nbr_del(struct nbr *);
void		 nbr_clear(void);

struct nbr	*nbr_find_ip(u_int32_t);
struct nbr	*nbr_find_lsrid(u_int32_t);
struct nbr	*nbr_find_peerid(u_int32_t);

int	 nbr_fsm(struct nbr *, enum nbr_event);

int	 nbr_itimer(struct thread *);
void	 nbr_start_itimer(struct nbr *);
void	 nbr_stop_itimer(struct nbr *);
int	 nbr_ktimer(struct thread *);
void	 nbr_start_ktimer(struct nbr *);
int	 nbr_ktimeout(struct thread *);
void	 nbr_start_ktimeout(struct nbr *);
int	 nbr_idtimer(struct thread *);
void	 nbr_start_idtimer(struct nbr *);
void	 nbr_stop_idtimer(struct nbr *);
int	 nbr_pending_idtimer(struct nbr *);

int	 nbr_act_session_establish(struct nbr *, int);

void			 nbr_mapping_add(struct nbr *, struct mapping_head *,
			    struct map *);
struct mapping_entry	*nbr_mapping_find(struct nbr *, struct mapping_head *,
			    struct map *);
void			 nbr_mapping_del(struct nbr *, struct mapping_head *,
			    struct map *);
void			 nbr_mapping_list_clr(struct nbr *,
			    struct mapping_head *);

void	ldpe_nbrs_send_adress(struct iface *iface);
void	ldpe_nbrs_send_adress_withdraw(struct iface *iface);

/* packet.c */
int	 gen_ldp_hdr(struct ibuf *, struct iface *, u_int16_t);
int	 gen_msg_tlv(struct nbr *, struct ibuf *, u_int32_t, u_int16_t);
int	 send_packet(struct iface *, void *, size_t, struct sockaddr_in *);
int	 disc_recv_packet(struct thread *);
int	 session_accept(struct thread *);

int	 session_read(struct thread *);
int	 session_write(struct thread *);
void	 session_close(struct nbr *);
void	 session_shutdown(struct nbr *, u_int32_t, u_int32_t, u_int32_t);

char	*pkt_ptr;	/* packet buffer */

#endif	/* _LDPE_H_ */
