/*
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

#include "memory.h"
#include "sockopt.h"
#include "thread.h"

#include "ldpd.h"
#include "ldpe.h"
#include "ldp_debug.h"

static int	 if_hello_timer(struct thread *);
void		 if_start_hello_timer(struct iface *);
void		 if_stop_hello_timer(struct iface *);

struct {
	int			state;
	enum iface_event	event;
	enum iface_action	action;
	int			new_state;
} iface_fsm[] = {
    /* current state	event that happened	action to take	resulting state */
    {IF_STA_DOWN,	IF_EVT_UP,		IF_ACT_STRT,	IF_STA_ACTIVE},
    {IF_STA_LOOPBACK,	IF_EVT_DOWN,		IF_ACT_NOTHING,	IF_STA_DOWN},
    {IF_STA_ANY,	IF_EVT_DOWN,		IF_ACT_RST,	IF_STA_DOWN},
    {-1,		IF_EVT_NOTHING,		IF_ACT_NOTHING,	0},
};

const char * const if_event_names[] = {
	"NOTHING",
	"UP",
	"DOWN"
};

const char * const if_action_names[] = {
	"NOTHING",
	"START",
	"RESET"
};

int
if_fsm(struct iface *iface, enum iface_event event)
{
	int	old_state;
	int	new_state = 0;
	int	i, ret = 0;

	old_state = iface->state;

	for (i = 0; iface_fsm[i].state != -1; i++)
		if ((iface_fsm[i].state & old_state) &&
		    (iface_fsm[i].event == event)) {
			new_state = iface_fsm[i].new_state;
			break;
		}

	if (iface_fsm[i].state == -1) {
		/* event outside of the defined fsm, ignore it. */
		zlog_warn("if_fsm: interface %s, "
		    "event %s not expected in state %s", iface->name,
		    if_event_names[event], if_state_name(old_state));
		return (0);
	}

	switch (iface_fsm[i].action) {
	case IF_ACT_STRT:
		ret = if_act_start(iface);
		break;
	case IF_ACT_RST:
		ret = if_act_reset(iface);
		break;
	case IF_ACT_NOTHING:
		/* do nothing */
		break;
	}

	if (ret) {
		zlog_warn("if_fsm: error changing state for interface %s, "
		    "event %s, state %s", iface->name, if_event_names[event],
		    if_state_name(old_state));
		return (-1);
	}

	if (new_state != 0)
		iface->state = new_state;

	log_event("if_fsm: event %s resulted in action %s and changing "
	    "state for interface %s from %s to %s",
	    if_event_names[event], if_action_names[iface_fsm[i].action],
	    iface->name, if_state_name(old_state), if_state_name(iface->state));

	return (ret);
}

struct iface *
if_new(struct interface *ifp)
{
	struct iface		*iface;

	iface = XCALLOC(MTYPE_LDP, sizeof(*iface));
	iface->state = IF_STA_DOWN;

	LIST_INIT(&iface->nbr_list);

	strlcpy(iface->name, ifp->name, sizeof(iface->name));

	/* checks if the interface is loopback */
	if (ifp->flags & IFF_LOOPBACK)
		iface->state = IF_STA_LOOPBACK;

	/* get mtu, index and flags */
	iface->mtu = ifp->mtu;
	iface->ifindex = ifp->ifindex;
	iface->flags = ifp->flags;
	iface->linkstate = 0;

	return (iface);
}

void
if_del(struct iface *iface)
{
	log_event("if_del: interface %s", iface->name);

	LDP_TIMER_OFF(iface->hello_timer);

	XFREE(MTYPE_LDP, iface);
}

void
if_init_ldp(struct iface *iface)
{
	iface->discovery_fd = ldpd_conf->ldp_discovery_socket;
}

/* timers */
static int
if_hello_timer(struct thread *thread)
{
	struct iface *iface = THREAD_ARG(thread);

	send_hello(iface);

	/* reschedule hello_timer */
	iface->hello_timer = NULL;
	LDP_IF_TIMER_ON(iface->hello_timer, if_hello_timer,
			ldpd_conf->hello_interval);

	return 0;
}

void
if_start_hello_timer(struct iface *iface)
{
	iface->hello_timer = NULL;
	LDP_IF_TIMER_ON(iface->hello_timer, if_hello_timer,
			ldpd_conf->hello_interval);
}

void
if_stop_hello_timer(struct iface *iface)
{
	LDP_TIMER_OFF(iface->hello_timer);
}

/* actions */
int
if_act_start(struct iface *iface)
{
	struct in_addr		 addr;
	struct timeval		 now;

	if (!(iface->flags & IFF_UP && iface->flags & IFF_RUNNING)) {
		log_event("if_act_start: interface %s link down",
		    iface->name);
		return (0);
	}

	gettimeofday(&now, NULL);
	iface->uptime = now.tv_sec;

	inet_aton(AllRouters, &addr);
	if (if_join_group(iface, &addr))
		return (-1);
	iface->state = IF_STA_DOWN;

	/* hello timer needs to be started in any case */
	if_start_hello_timer(iface);
	return (0);
}

int
if_act_reset(struct iface *iface)
{
	struct in_addr		 addr;

	inet_aton(AllRouters, &addr);
	if (if_leave_group(iface, &addr)) {
		zlog_warn("if_act_reset: error leaving group %s, "
		    "interface %s", inet_ntoa(addr), iface->name);
	}

	if_stop_hello_timer (iface);

	return (0);
}

/* misc */
int
if_set_mcast_ttl(int fd, u_int8_t ttl)
{
	if (setsockopt(fd, IPPROTO_IP, IP_MULTICAST_TTL,
	    (char *)&ttl, sizeof(ttl)) < 0) {
		zlog_warn("if_set_mcast_ttl: error setting "
		    "IP_MULTICAST_TTL to %d", ttl);
		return (-1);
	}

	return (0);
}

int
if_set_tos(int fd, int tos)
{
	if (setsockopt(fd, IPPROTO_IP, IP_TOS, (int *)&tos, sizeof(tos)) < 0) {
		zlog_warn("if_set_tos: error setting IP_TOS to 0x%x", tos);
		return (-1);
	}

	return (0);
}

int
if_set_recvif(int fd, int enable)
{
	return setsockopt_ifindex(AF_INET, fd, enable);
}

void
if_set_recvbuf(int fd)
{
	int	bsize;

	bsize = 65535;
	while (setsockopt(fd, SOL_SOCKET, SO_RCVBUF, &bsize,
	    sizeof(bsize)) == -1)
		bsize /= 2;
}

int
if_set_reuse(int fd, int enable)
{
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &enable,
	    sizeof(int)) < 0) {
		zlog_warn("if_set_reuse: error setting SO_REUSEADDR");
		return (-1);
	}

	return (0);
}

int
if_join_group(struct iface *iface, struct in_addr *addr)
{
	int ret;

	ret = setsockopt_ipv4_multicast(iface->discovery_fd,
					IP_ADD_MEMBERSHIP, iface->addr,
					addr->s_addr, iface->ifindex);
	if (ret < 0)
		zlog_warn("if_join_group: error IP_ADD_MEMBERSHIP, "
		    "interface %s address %s", iface->name,
		    inet_ntoa(*addr));

	return ret;
}

int
if_leave_group(struct iface *iface, struct in_addr *addr)
{
	int ret;

	ret = setsockopt_ipv4_multicast(iface->discovery_fd,
					IP_DROP_MEMBERSHIP, iface->addr,
					addr->s_addr, iface->ifindex);
	if (ret < 0)
		zlog_warn("if_leave_group: error IP_DROP_MEMBERSHIP, "
		    "interface %s address %s", iface->name,
		    inet_ntoa(*addr));

	return ret;
}

int
if_set_mcast(struct iface *iface)
{
	if (setsockopt_ipv4_multicast_if(iface->discovery_fd, iface->addr,
					 iface->ifindex) < 0) {
		zlog_warn("Can't setsockopt IP_MULTICAST_IF on fd %d to "
		    "ifindex %d for interface %s", iface->discovery_fd,
		    iface->ifindex, iface->name);
		return (-1);
	}

	return (0);
}

int
if_set_mcast_loop(int fd)
{
	u_int8_t	loop = 0;

	if (setsockopt(fd, IPPROTO_IP, IP_MULTICAST_LOOP,
	    (char *)&loop, sizeof(loop)) < 0) {
		zlog_warn("if_set_mcast_loop: error setting IP_MULTICAST_LOOP");
		return (-1);
	}

	return (0);
}
