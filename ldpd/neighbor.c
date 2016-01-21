/*
 * Copyright (c) 2009 Michele Marchetto <michele@openbsd.org>
 * Copyright (c) 2005 Claudio Jeker <claudio@openbsd.org>
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

#include "thread.h"
#include "memory.h"

#include "ldpd.h"
#include "ldpe.h"
#include "lde.h"
#include "ldp_debug.h"

int	nbr_establish_connection(struct nbr *);
void	nbr_send_labelmappings(struct nbr *);
int	nbr_act_session_operational(struct nbr *);

static __inline int nbr_lsrid_compare(struct nbr *, struct nbr *);
static __inline int nbr_addr_compare(struct nbr *, struct nbr *);
static __inline int nbr_pid_compare(struct nbr *, struct nbr *);

RB_HEAD(nbr_lsrid_head, nbr);
RB_PROTOTYPE(nbr_lsrid_head, nbr, lsrid_tree, nbr_lsrid_compare)
RB_GENERATE(nbr_lsrid_head, nbr, lsrid_tree, nbr_lsrid_compare)
RB_HEAD(nbr_addr_head, nbr);
RB_PROTOTYPE(nbr_addr_head, nbr, addr_tree, nbr_addr_compare)
RB_GENERATE(nbr_addr_head, nbr, addr_tree, nbr_addr_compare)
RB_HEAD(nbr_pid_head, nbr);
RB_PROTOTYPE(nbr_pid_head, nbr, pid_tree, nbr_pid_compare)
RB_GENERATE(nbr_pid_head, nbr, pid_tree, nbr_pid_compare)

static __inline int
nbr_lsrid_compare(struct nbr *a, struct nbr *b)
{
	return (ntohl(a->id.s_addr) - ntohl(b->id.s_addr));
}

static __inline int
nbr_addr_compare(struct nbr *a, struct nbr *b)
{
	return (ntohl(a->remote_addr.s_addr) - ntohl(b->remote_addr.s_addr));
}

static __inline int
nbr_pid_compare(struct nbr *a, struct nbr *b)
{
	return (a->peerid - b->peerid);
}

struct nbr_lsrid_head nbrs_by_lsrid = RB_INITIALIZER(&nbrs_by_lsrid);
struct nbr_addr_head nbrs_by_addr = RB_INITIALIZER(&nbrs_by_addr);
struct nbr_pid_head nbrs_by_pid = RB_INITIALIZER(&nbrs_by_pid);

u_int32_t	peercnt = NBR_CNTSTART;

struct {
	int		state;
	enum nbr_event	event;
	enum nbr_action	action;
	int		new_state;
} nbr_fsm_tbl[] = {
    /* current state	event that happened	action to take		resulting state */
/* Discovery States */
    {NBR_STA_DOWN,	NBR_EVT_HELLO_RCVD,	NBR_ACT_STRT_ITIMER,	NBR_STA_PRESENT},
    {NBR_STA_SESSION,	NBR_EVT_HELLO_RCVD,	NBR_ACT_RST_ITIMER,	0},
/* Passive Role */
    {NBR_STA_PRESENT,	NBR_EVT_SESSION_UP,	NBR_ACT_SESSION_EST,	NBR_STA_INITIAL},
    {NBR_STA_INITIAL,	NBR_EVT_INIT_RCVD,	NBR_ACT_INIT_SEND,	NBR_STA_OPENREC},
    {NBR_STA_OPENREC,	NBR_EVT_KEEPALIVE_RCVD,	NBR_ACT_STRT_KTIMER,	NBR_STA_OPER},
/* Active Role */
    {NBR_STA_PRESENT,	NBR_EVT_INIT_SENT,	NBR_ACT_NOTHING,	NBR_STA_OPENSENT},
    {NBR_STA_OPENSENT,	NBR_EVT_INIT_RCVD,	NBR_ACT_KEEPALIVE_SEND,	NBR_STA_OPER},
/* Session Maintenance */
    {NBR_STA_OPER,	NBR_EVT_PDU_RCVD,	NBR_ACT_RST_KTIMEOUT,	0},
/* Session Close */
    {NBR_STA_SESSION,	NBR_EVT_CLOSE_SESSION,	NBR_ACT_CLOSE_SESSION,	NBR_STA_PRESENT},
    {NBR_STA_SESSION,	NBR_EVT_DOWN,		NBR_ACT_CLOSE_SESSION,	},
    {-1,		NBR_EVT_NOTHING,	NBR_ACT_NOTHING,	0},
};

const char * const nbr_event_names[] = {
	"NOTHING",
	"HELLO RECEIVED",
	"SESSION UP",
	"SESSION CLOSE",
	"INIT RECEIVED",
	"KEEPALIVE RECEIVED",
	"PDU RECEIVED",
	"INIT SENT",
	"DOWN"
};

const char * const nbr_action_names[] = {
	"NOTHING",
	"START INACTIVITY TIMER",
	"RESET INACTIVITY TIMER",
	"RESET KEEPALIVE TIMEOUT",
	"START KEEPALIVE TIMER",
	"RESET KEEPALIVE TIMER",
	"START NEIGHBOR SESSION",
	"SEND INIT",
	"SEND KEEPALIVE",
	"CLOSE SESSION"
};

int
nbr_fsm(struct nbr *nbr, enum nbr_event event)
{
	struct timeval	now;
	int		old_state;
	int		new_state = 0;
	int		i, ret = 0;

	old_state = nbr->state;
	for (i = 0; nbr_fsm_tbl[i].state != -1; i++)
		if ((nbr_fsm_tbl[i].state & old_state) &&
		    (nbr_fsm_tbl[i].event == event)) {
			new_state = nbr_fsm_tbl[i].new_state;
			break;
		}

	if (nbr_fsm_tbl[i].state == -1) {
		/* event outside of the defined fsm, ignore it. */
		zlog_warn("nbr_fsm: neighbor ID %s, "
		    "event %s not expected in state %s",
		    inet_ntoa(nbr->id), nbr_event_names[event],
		    nbr_state_name(old_state));
		return (0);
	}

	ret = 0;

	switch (nbr_fsm_tbl[i].action) {
	case NBR_ACT_RST_ITIMER:
	case NBR_ACT_STRT_ITIMER:
		nbr_start_itimer(nbr);
		break;
	case NBR_ACT_RST_KTIMEOUT:
		nbr_start_ktimeout(nbr);
		break;
	case NBR_ACT_STRT_KTIMER:
		nbr_act_session_operational(nbr);
		nbr_start_ktimer(nbr);
		nbr_start_ktimeout(nbr);
		send_address(nbr, NULL);
		nbr_send_labelmappings(nbr);
		break;
	case NBR_ACT_SESSION_EST:
		ret = nbr_act_session_establish(nbr, 0);
		break;
	case NBR_ACT_INIT_SEND:
		send_init(nbr);
		send_keepalive(nbr);
		break;
	case NBR_ACT_KEEPALIVE_SEND:
		nbr_act_session_operational(nbr);
		nbr_start_ktimer(nbr);
		nbr_start_ktimeout(nbr);
		send_keepalive(nbr);
		send_address(nbr, NULL);
		nbr_send_labelmappings(nbr);
		break;
	case NBR_ACT_CLOSE_SESSION:
		lde_process(IMSG_NEIGHBOR_DOWN, nbr->peerid, NULL, 0);
		session_close(nbr);
		nbr_start_idtimer(nbr);
		break;
	case NBR_ACT_NOTHING:
		/* do nothing */
		break;
	}

	if (ret) {
		zlog_warn("nbr_fsm: error changing state for neighbor ID %s, "
		    "event %s, state %s", inet_ntoa(nbr->id),
		    nbr_event_names[event], nbr_state_name(old_state));
		return (-1);
	}

	if (new_state != 0)
		nbr->state = new_state;

	if (old_state != nbr->state) {
		log_event("nbr_fsm: event %s resulted in action %s and "
		    "changing state for neighbor ID %s from %s to %s",
		    nbr_event_names[event],
		    nbr_action_names[nbr_fsm_tbl[i].action],
		    inet_ntoa(nbr->id), nbr_state_name(old_state),
		    nbr_state_name(nbr->state));

		if (nbr->state == NBR_STA_OPER) {
			gettimeofday(&now, NULL);
			nbr->uptime = now.tv_sec;
		}
	}

	return (ret);
}

struct nbr *
nbr_new(u_int32_t nbr_id, struct in_addr transport_addr,
    struct iface *iface)
{
	struct nbr		*nbr;
	struct ldp_if_info	*if_info = iface->if_info;

	nbr = XCALLOC(MTYPE_LDP, sizeof(*nbr));
	nbr->rbuf = XCALLOC(MTYPE_LDP, sizeof(struct ibuf_read));
	nbr->state = NBR_STA_DOWN;
	nbr->id.s_addr = nbr_id;
	nbr->remote_addr.s_addr = transport_addr.s_addr;
	nbr->iface = iface;

	if (if_info->transport_addr == TRANSPORT_ADDRESS_ROUTER_ID)
		nbr->local_addr.s_addr = ldpd_conf->rtr_id.s_addr;
	else if (if_info->transport_addr == TRANSPORT_ADDRESS_INTERFACE)
		nbr->local_addr.s_addr = iface->addr.s_addr;
	else if (if_info->transport_addr == TRANSPORT_ADDRESS_STATIC_IP)
		nbr->local_addr.s_addr = if_info->transport_addr_static_ip.s_addr;
	else
		nbr->local_addr.s_addr = htonl(INADDR_ANY);

	LIST_INSERT_HEAD(&iface->nbr_list, nbr, entry);

	/* get next unused peerid */
	while (nbr_find_peerid(++peercnt))
		;
	nbr->peerid = peercnt;

	if (RB_INSERT(nbr_pid_head, &nbrs_by_pid, nbr) != NULL)
		fatalx("nbr_new: RB_INSERT(nbrs_by_pid) failed");
	if (RB_INSERT(nbr_addr_head, &nbrs_by_addr, nbr) != NULL)
		fatalx("nbr_new: RB_INSERT(nbrs_by_addr) failed");
	if (RB_INSERT(nbr_lsrid_head, &nbrs_by_lsrid, nbr) != NULL)
		fatalx("nbr_new: RB_INSERT(nbrs_by_id) failed");

	TAILQ_INIT(&nbr->mapping_list);
	TAILQ_INIT(&nbr->withdraw_list);
	TAILQ_INIT(&nbr->request_list);
	TAILQ_INIT(&nbr->release_list);
	TAILQ_INIT(&nbr->abortreq_list);

	return (nbr);
}

void
nbr_del(struct nbr *nbr)
{
	lde_process(IMSG_NEIGHBOR_DOWN, nbr->peerid, NULL, 0);
	session_close(nbr);

	LDP_TIMER_OFF(nbr->inactivity_timer);
	LDP_TIMER_OFF(nbr->keepalive_timer);
	LDP_TIMER_OFF(nbr->keepalive_timeout);
	LDP_TIMER_OFF(nbr->initdelay_timer);

	LIST_REMOVE (nbr, entry);

	nbr_mapping_list_clr(nbr, &nbr->mapping_list);
	nbr_mapping_list_clr(nbr, &nbr->withdraw_list);
	nbr_mapping_list_clr(nbr, &nbr->request_list);
	nbr_mapping_list_clr(nbr, &nbr->release_list);
	nbr_mapping_list_clr(nbr, &nbr->abortreq_list);

	RB_REMOVE(nbr_pid_head, &nbrs_by_pid, nbr);
	RB_REMOVE(nbr_addr_head, &nbrs_by_addr, nbr);
	RB_REMOVE(nbr_lsrid_head, &nbrs_by_lsrid, nbr);

	XFREE(MTYPE_LDP, nbr->rbuf);
	XFREE(MTYPE_LDP, nbr);
}

void
nbr_clear(void)
{
	struct nbr	*nbr;

	while ((nbr = RB_ROOT(&nbrs_by_pid)) != NULL)
		nbr_del(nbr);
}

struct nbr *
nbr_find_peerid(u_int32_t peerid)
{
	struct nbr	n;
	n.peerid = peerid;
	return (RB_FIND(nbr_pid_head, &nbrs_by_pid, &n));
}

struct nbr *
nbr_find_ip(u_int32_t addr)
{
	struct nbr	n;
	n.remote_addr.s_addr = addr;
	return (RB_FIND(nbr_addr_head, &nbrs_by_addr, &n));
}

struct nbr *
nbr_find_lsrid(u_int32_t rtr_id)
{
	struct nbr	n;
	n.id.s_addr = rtr_id;
	return (RB_FIND(nbr_lsrid_head, &nbrs_by_lsrid, &n));
}

/* timers */

/* Inactivity timer: timeout based on hellos */
int
nbr_itimer(struct thread *thread)
{
	struct nbr *nbr = THREAD_ARG(thread);

	log_event("nbr_itimer: neighbor ID %s peerid %u", inet_ntoa(nbr->id),
	    nbr->peerid);

	nbr_del(nbr);

	return 0;
}

void
nbr_start_itimer(struct nbr *nbr)
{
	LDP_TIMER_OFF(nbr->inactivity_timer);
	LDP_NBR_TIMER_ON(nbr->inactivity_timer, nbr_itimer, nbr->holdtime);
}

void
nbr_stop_itimer(struct nbr *nbr)
{
	LDP_TIMER_OFF(nbr->inactivity_timer);
}

/* Keepalive timer: timer to send keepalive message to neighbors */

int
nbr_ktimer(struct thread *thread)
{
	struct nbr	*nbr = THREAD_ARG(thread);

	send_keepalive(nbr);

	return 0;
}

void
nbr_start_ktimer(struct nbr *nbr)
{
	LDP_TIMER_OFF(nbr->keepalive_timer);

	/* XXX: just to be sure it will send three keepalives per period */
	LDP_NBR_TIMER_ON(nbr->keepalive_timer, nbr_ktimer,
			 nbr->keepalive / KEEPALIVE_PER_PERIOD);
}

/* Keepalive timeout: if the nbr hasn't sent keepalive */

int
nbr_ktimeout(struct thread *thread)
{
	struct nbr *nbr = THREAD_ARG(thread);

	log_event("nbr_ktimeout: neighbor ID %s peerid %u", inet_ntoa(nbr->id),
	    nbr->peerid);

	send_notification_nbr(nbr, S_KEEPALIVE_TMR, 0, 0);
	/* XXX race, send_notification_nbr() has no chance to be sent */
	session_close(nbr);

	return 0;
}

void
nbr_start_ktimeout(struct nbr *nbr)
{
	LDP_TIMER_OFF(nbr->keepalive_timeout);
	LDP_NBR_TIMER_ON(nbr->keepalive_timeout, nbr_ktimeout, nbr->keepalive);
}

/* Init delay timer: timer to retry to iniziatize session */

int
nbr_idtimer(struct thread *thread)
{
	struct nbr *nbr = THREAD_ARG(thread);

	if (htonl(nbr->remote_addr.s_addr) >= htonl(nbr->local_addr.s_addr))
		return 0;

	log_event("nbr_idtimer: neighbor ID %s peerid %u", inet_ntoa(nbr->id),
	    nbr->peerid);

	nbr_act_session_establish(nbr, 1);

	return 0;
}

void
nbr_start_idtimer(struct nbr *nbr)
{
	LDP_TIMER_OFF(nbr->initdelay_timer);
	LDP_NBR_TIMER_ON(nbr->initdelay_timer, nbr_idtimer, INIT_DELAY_TMR);
}

void
nbr_stop_idtimer(struct nbr *nbr)
{
	LDP_TIMER_OFF(nbr->initdelay_timer);
}

int
nbr_pending_idtimer(struct nbr *nbr)
{
	if (nbr->initdelay_timer)
		return (1);

	return (0);
}

int
nbr_establish_connection(struct nbr *nbr)
{
	struct sockaddr_in	in;
	struct sockaddr_in	local;
	socklen_t		len;

	bzero(&in, sizeof(in));
	in.sin_family = AF_INET;
	in.sin_port = htons(LDP_PORT);
	in.sin_addr.s_addr = nbr->remote_addr.s_addr;

	nbr->fd = socket(AF_INET, SOCK_STREAM, 0);
	if (nbr->fd == -1) {
		zlog_warn("nbr_establish_connection: error while "
		    "creating socket");
		return (-1);
	}

	bzero(&local, sizeof(local));
	local.sin_family = AF_INET;
	local.sin_port = htons(0);
	local.sin_addr.s_addr = nbr->local_addr.s_addr;

	if (bind(nbr->fd, &local, sizeof(struct sockaddr_in)) == -1) {
		zlog_warn("nbr_establish_connection: error while "
		    "binding to %s", inet_ntoa(nbr->remote_addr));
		nbr_start_idtimer(nbr);
		close(nbr->fd);
		return (-1);
	}

	len = sizeof(local);
	getsockname(nbr->fd, (struct sockaddr *)&local, &len);
	nbr->local_port = ntohs(local.sin_port);
	nbr->remote_port = ntohs(in.sin_port);

	if (connect(nbr->fd, (struct sockaddr *)&in, sizeof(in)) == -1) {
		zlog_warn("nbr_establish_connection: error while "
		    "connecting to %s", inet_ntoa(nbr->remote_addr));
		nbr_start_idtimer(nbr);
		close(nbr->fd);
		return (-1);
	}

	return (0);
}

int
nbr_act_session_establish(struct nbr *nbr, int active)
{
	if (active) {
		if (nbr_establish_connection(nbr) < 0)
			return (-1);
	}

	evbuf_init(&nbr->wbuf, nbr->fd, session_write, nbr);

	nbr->t_read = NULL;
	THREAD_READ_ON(master, nbr->t_read, session_read, nbr, nbr->fd);

	if (active) {
		send_init(nbr);
		nbr_fsm(nbr, NBR_EVT_INIT_SENT);
	}

	return (0);
}

int
nbr_act_session_operational(struct nbr *nbr)
{
	struct lde_nbr	 rn;

	bzero(&rn, sizeof(rn));
	rn.id.s_addr = nbr->id.s_addr;

	lde_process(IMSG_NEIGHBOR_UP, nbr->peerid, &rn, sizeof(rn));

	return 0;
}

void
nbr_send_labelmappings(struct nbr *nbr)
{
	if (ldpd_conf->mode & MODE_ADV_UNSOLICITED) {
		lde_process(IMSG_LABEL_MAPPING_FULL, nbr->peerid, NULL, 0);
	}
}

void
nbr_mapping_add(struct nbr *nbr, struct mapping_head *mh, struct map *map)
{
	struct mapping_entry	*me;

	me = XCALLOC(MTYPE_LDP, sizeof(*me));
	me->map = *map;

	TAILQ_INSERT_TAIL(mh, me, entry);
}

struct mapping_entry *
nbr_mapping_find(struct nbr *nbr, struct mapping_head *mh, struct map *map)
{
	struct mapping_entry	*me = NULL;

	TAILQ_FOREACH(me, mh, entry) {
		if (me->map.prefix.s_addr == map->prefix.s_addr &&
		    me->map.prefixlen == map->prefixlen)
			return (me);
	}

	return (NULL);
}

void
nbr_mapping_del(struct nbr *nbr, struct mapping_head *mh, struct map *map)
{
	struct mapping_entry	*me;

	me = nbr_mapping_find(nbr, mh, map);
	if (me == NULL)
		return;

	TAILQ_REMOVE(mh, me, entry);
	XFREE(MTYPE_LDP, me);
}

void
nbr_mapping_list_clr(struct nbr *nbr, struct mapping_head *mh)
{
	struct mapping_entry	*me;

	while ((me = TAILQ_FIRST(mh)) != NULL) {
		TAILQ_REMOVE(mh, me, entry);
		XFREE(MTYPE_LDP, me);
	}
}

void
ldpe_nbrs_send_adress(struct iface *iface)
{
	struct nbr *nbr;

	RB_FOREACH(nbr, nbr_lsrid_head, &nbrs_by_lsrid)
		if (nbr->state == NBR_STA_OPER)
			send_address(nbr, iface);
}

void
ldpe_nbrs_send_adress_withdraw(struct iface *iface)
{
	struct nbr *nbr;

	RB_FOREACH(nbr, nbr_lsrid_head, &nbrs_by_lsrid)
		if (nbr->state == NBR_STA_OPER)
			send_address_withdraw(nbr, iface);
}
