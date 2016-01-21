/*
 * Copyright (c) 2004, 2005 Claudio Jeker <claudio@openbsd.org>
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

#include <zebra.h>

#include "memory.h"

#include "ldpd.h"
#include "ldpe.h"
#include "lde.h"
#include "ldp_debug.h"

struct lde_nbr	*lde_nbr_new(u_int32_t, struct lde_nbr *);
void		 lde_nbr_del(struct lde_nbr *);

void		 lde_map_free(void *);
void		 lde_address_list_free(struct lde_nbr *);

RB_PROTOTYPE(fec_tree, fec, entry, fec_compare)
extern struct fec_tree rt;

/* label decision engine */
void
lde(void)
{
	struct timeval		 now;

	gettimeofday(&now, NULL);
	ldpd_conf->uptime = now.tv_sec;
}

/* ARGSUSED */
void
lde_process(int type, u_int32_t peerid, void *data, u_int16_t datalen)
{
	struct lde_nbr		 rn, *nbr;
	struct map		 map;
	struct in_addr		 addr;
	int			 state;
	struct kroute		 kr;

	switch (type) {
	case IMSG_LABEL_MAPPING_FULL:
		nbr = lde_nbr_find(peerid);
		if (nbr == NULL) {
			zlog_debug("lde_process: cannot find lde neighbor");
			return;
		}

		rt_snap(nbr);
		ldpe_process(IMSG_MAPPING_ADD_END, peerid, NULL, 0);
		break;
	case IMSG_LABEL_MAPPING:
	case IMSG_LABEL_REQUEST:
	case IMSG_LABEL_RELEASE:
	case IMSG_LABEL_WITHDRAW:
	case IMSG_LABEL_ABORT:
		if (datalen != sizeof(map))
			fatalx("invalid size of OE request");
		memcpy(&map, data, sizeof(map));

		nbr = lde_nbr_find(peerid);
		if (nbr == NULL) {
			zlog_debug("lde_process: cannot find lde neighbor");
			return;
		}

		switch (type) {
		case IMSG_LABEL_MAPPING:
			lde_check_mapping(&map, nbr);
			break;
		case IMSG_LABEL_REQUEST:
			lde_check_request(&map, nbr);
			break;
		case IMSG_LABEL_RELEASE:
			lde_check_release(&map, nbr);
			break;
		case IMSG_LABEL_WITHDRAW:
			lde_check_withdraw(&map, nbr);
			break;
		default:
			zlog_warn("type %d not yet handled. nbr %s",
			    type, inet_ntoa(nbr->id));
		}
		break;
	case IMSG_ADDRESS_ADD:
		if (datalen != sizeof(addr))
			fatalx("invalid size of OE request");
		memcpy(&addr, data, sizeof(addr));

		nbr = lde_nbr_find(peerid);
		if (nbr == NULL) {
			zlog_debug("lde_process: cannot find lde neighbor");
			return;
		}

		if (lde_address_add(nbr, &addr) < 0) {
			zlog_debug("lde_process: cannot add "
			    "address %s, it already exists", inet_ntoa(addr));
		}

		break;
	case IMSG_ADDRESS_DEL:
		if (datalen != sizeof(addr))
			fatalx("invalid size of OE request");
		memcpy(&addr, data, sizeof(addr));

		nbr = lde_nbr_find(peerid);
		if (nbr == NULL) {
			zlog_debug("lde_process: cannot find lde neighbor");
			return;
		}

		if (lde_address_del(nbr, &addr) < 0) {
			zlog_debug("lde_process: cannot delete "
			    "address %s, it does not exists", inet_ntoa(addr));
		}

		break;
	case IMSG_NEIGHBOR_UP:
		if (datalen != sizeof(rn))
			fatalx("invalid size of OE request");
		memcpy(&rn, data, sizeof(rn));

		if (lde_nbr_find(peerid))
			fatalx("lde_process: neighbor already exists");
		lde_nbr_new(peerid, &rn);
		break;
	case IMSG_NEIGHBOR_DOWN:
		lde_nbr_del(lde_nbr_find(peerid));
		break;
	case IMSG_NEIGHBOR_CHANGE:
		if (datalen != sizeof(state))
			fatalx("invalid size of OE request");
		memcpy(&state, data, sizeof(state));

		nbr = lde_nbr_find(peerid);
		if (nbr == NULL)
			break;

		nbr->state = state;
		break;
	case IMSG_ZEBRA_NETWORK_ADD:
	case IMSG_ZEBRA_NETWORK_DEL:
	case IMSG_ZEBRA_CHANGE_INPUT_LABEL:
		if (datalen != sizeof(kr)) {
			zlog_warn("lde_process: wrong imsg len");
			break;
		}
		memcpy(&kr, data, sizeof(kr));

		switch (type) {
		case IMSG_ZEBRA_NETWORK_ADD:
			lde_kernel_insert(&kr);
			break;
		case IMSG_ZEBRA_NETWORK_DEL:
			lde_kernel_remove(&kr);
			break;
		case IMSG_ZEBRA_CHANGE_INPUT_LABEL:
			lde_kernel_change_input_label(&kr);
			break;
		}
		break;
	default:
		zlog_debug("lde_process: unexpected imsg %d", type);
		break;
	}
}

void
lde_zebra_change_input_label(struct rt_node *rr)
{
	struct kroute	kr;

	bzero(&kr, sizeof(kr));
	kr.prefix.s_addr = rr->fec.prefix.s_addr;
	kr.prefixlen = rr->fec.prefixlen;
	kr.local_label = rr->local_label;

	ldpd_process(IMSG_ZEBRA_CHANGE_INPUT_LABEL, &kr, sizeof(kr));
}

void
lde_zebra_add_lsp(struct rt_node *rn)
{
	struct kroute	 kr;

	bzero(&kr, sizeof(kr));
	kr.prefix.s_addr = rn->fec.prefix.s_addr;
	kr.prefixlen = rn->fec.prefixlen;
	kr.nexthop.s_addr = rn->lsp.nexthop.s_addr;
	kr.remote_label = rn->lsp.remote_label;

	ldpd_process(IMSG_ZEBRA_ADD_LSP, &kr, sizeof(kr));
}

void
lde_zebra_delete_lsp(struct rt_node *rn)
{
	struct kroute	 kr;

	bzero(&kr, sizeof(kr));
	kr.prefix.s_addr = rn->fec.prefix.s_addr;
	kr.prefixlen = rn->fec.prefixlen;
	kr.nexthop.s_addr = rn->lsp.nexthop.s_addr;
	kr.remote_label = rn->lsp.remote_label;

	ldpd_process(IMSG_ZEBRA_DELETE_LSP, &kr, sizeof(kr));
}

void
lde_send_labelrequest(struct lde_nbr *ln, struct rt_node *rn)
{
	struct map	 map;

	/* TODO check if status of peer is OK to send requests (SLRq.2 & 6)
	 * For now assume no peer will send no-label-resource notifications */

	/* check if request is already pending */
	if (fec_find(&ln->sent_req, &rn->fec) != NULL)
		return;
	/* and try to add request to pending list */
	lde_req_add(ln, &rn->fec, 1);
	/* msgid does not matter since only one req can be pending */

	bzero(&map, sizeof(map));
	map.prefix = rn->fec.prefix;
	map.prefixlen = rn->fec.prefixlen;

	ldpe_process(IMSG_REQUEST_ADD, ln->peerid, &map, sizeof(map));
	ldpe_process(IMSG_REQUEST_ADD_END, ln->peerid, NULL, 0);
}

void
lde_send_labelmapping(struct lde_nbr *ln, struct rt_node *rn)
{
	struct lde_req	*lre;
	struct lde_map	*me;
	struct map	 map;

	/*
	 * This function skips SL.1 - 3 and SL.9 - 14 because the lable
	 * allocation is done way earlier (because of the merging nature of
	 * ldpd).
	 */

	bzero(&map, sizeof(map));
	map.label = rn->local_label;
	map.prefix = rn->fec.prefix;
	map.prefixlen = rn->fec.prefixlen;

	/* is there a pending request for this mapping? */
	lre = (struct lde_req *)fec_find(&ln->recv_req, &rn->fec);
	if (lre) {
		/* set label request msg id in the mapping response. */
		map.requestid = lre->msgid;
		map.flags = F_MAP_REQ_ID;
		lde_req_del(ln, lre, 0);
	}

	me = (struct lde_map *)fec_find(&ln->sent_map, &rn->fec);
	if (me == NULL)
		me = lde_map_add(ln, rn, 1);
	me->label = map.label;

	ldpe_process(IMSG_MAPPING_ADD, ln->peerid, &map, sizeof(map));
	ldpe_process(IMSG_MAPPING_ADD_END, ln->peerid, NULL, 0);
}

void
lde_send_labelwithdraw(struct lde_nbr *ln, struct rt_node *rn)
{
	struct lde_map	*me;
	struct map	 map;

	bzero(&map, sizeof(map));
	map.label = rn->local_label;
	map.prefix = rn->fec.prefix;
	map.prefixlen = rn->fec.prefixlen;

	me = (struct lde_map *)fec_find(&ln->sent_wdraw, &rn->fec);
	if (me == NULL)
		me = lde_withdraw_add(ln, rn);
	me->label = map.label;

	ldpe_process(IMSG_WITHDRAWN_ADD, ln->peerid, &map, sizeof(map));
	ldpe_process(IMSG_WITHDRAWN_ADD_END, ln->peerid, NULL, 0);
}

void
lde_send_labelrelease(struct lde_nbr *ln, struct rt_node *rn, u_int32_t label)
{
	struct map	 map;

	bzero(&map, sizeof(map));
	map.prefix = rn->fec.prefix;
	map.prefixlen = rn->fec.prefixlen;
	if (label != NO_LABEL) {
		map.flags = F_MAP_OPTLABEL;
		map.label = label;
	}

	ldpe_process(IMSG_RELEASE_ADD, ln->peerid, &map, sizeof(map));
	ldpe_process(IMSG_RELEASE_ADD_END, ln->peerid, NULL, 0);
}

void
lde_send_notification(u_int32_t peerid, u_int32_t code, u_int32_t msgid,
    u_int32_t type)
{
	struct notify_msg nm;

	bzero(&nm, sizeof(nm));

	/* Every field is in host byte order, to keep things clear */
	nm.status = code;
	nm.messageid = ntohl(msgid);
	nm.type = type;

	ldpe_process(IMSG_NOTIFICATION_SEND, peerid, &nm, sizeof(nm));
}

static __inline int lde_nbr_compare(struct lde_nbr *, struct lde_nbr *);

RB_HEAD(nbr_tree, lde_nbr);
RB_PROTOTYPE(nbr_tree, lde_nbr, entry, lde_nbr_compare)
RB_GENERATE(nbr_tree, lde_nbr, entry, lde_nbr_compare)

struct nbr_tree lde_nbrs = RB_INITIALIZER(&lde_nbrs);

static __inline int
lde_nbr_compare(struct lde_nbr *a, struct lde_nbr *b)
{
	return (a->peerid - b->peerid);
}

struct lde_nbr *
lde_nbr_find(u_int32_t peerid)
{
	struct lde_nbr	n;

	n.peerid = peerid;

	return (RB_FIND(nbr_tree, &lde_nbrs, &n));
}

struct lde_nbr *
lde_nbr_new(u_int32_t peerid, struct lde_nbr *new)
{
	struct lde_nbr	*nbr;

	if (lde_nbr_find(peerid))
		return (NULL);

	nbr = XCALLOC(MTYPE_LDP, sizeof(*nbr));
	memcpy(nbr, new, sizeof(*nbr));
	nbr->peerid = peerid;
	fec_init(&nbr->recv_map);
	fec_init(&nbr->sent_map);
	fec_init(&nbr->recv_req);
	fec_init(&nbr->sent_req);
	fec_init(&nbr->sent_wdraw);

	TAILQ_INIT(&nbr->addr_list);

	if (RB_INSERT(nbr_tree, &lde_nbrs, nbr) != NULL)
		fatalx("lde_nbr_new: RB_INSERT failed");

	return (nbr);
}

void
lde_nbr_del(struct lde_nbr *nbr)
{
	struct fec		*f;
	struct rt_node		*rn;
	struct lde_nbr_address	*addr = NULL;

	if (nbr == NULL)
		return;

	/* Remove installed mappings from kernel */
	RB_FOREACH(f, fec_tree, &rt) {
		rn = (struct rt_node *)f;
		if ((addr = lde_address_find(nbr, &rn->lsp.nexthop))) {
			lde_zebra_delete_lsp(rn);
			rn->lsp.remote_label = NO_LABEL;
		}
	}

	lde_address_list_free(nbr);

	fec_clear(&nbr->recv_map, lde_map_free);
	fec_clear(&nbr->sent_map, lde_map_free);
	fec_clear(&nbr->recv_req, free);
	fec_clear(&nbr->sent_req, free);
	fec_clear(&nbr->sent_wdraw, free);

	RB_REMOVE(nbr_tree, &lde_nbrs, nbr);

	XFREE(MTYPE_LDP, nbr);
}

void
lde_nbr_clear(void)
{
	struct lde_nbr	*nbr;

	while ((nbr = RB_ROOT(&lde_nbrs)) != NULL)
		lde_nbr_del(nbr);
}

void
lde_recognize_new_fec(struct rt_node *rn)
{
	struct lde_nbr	*ln;
	struct lde_nbr_address	*addr;
	struct lde_map		*map;

	/* We may already have a mapping for this new prefix
	 * if we are in liberal mode */
	addr = NULL;
	LIST_FOREACH(map, &rn->downstream, entry) {
		addr = lde_address_find(map->nexthop, &rn->lsp.nexthop);
		if (addr != NULL) {
			rn->lsp.remote_label = map->label;
			break;
		}
	}

	/* FEC.1 */
	RB_FOREACH(ln, nbr_tree, &lde_nbrs) {
		if (ldpd_conf->mode & MODE_ADV_ONDEMAND)
			break;

		if (ldpd_conf->mode & MODE_DIST_INDEPENDENT
		    || (lsr_egress_for_fec(rn) || addr))
			lde_send_labelmapping(ln, rn);
	}

	/* FEC.2 */
	if (addr != NULL) {
		/* FEC.5 */
		/* XXX: Generate "receive label mapping" event */
		lde_zebra_add_lsp(rn);
		return;
	}

	/* FEC.3 - Is next hop an LDP peer? */
	RB_FOREACH(ln, nbr_tree, &lde_nbrs) {
		addr = lde_address_find(ln, &rn->lsp.nexthop);
		/* FEC.4 - Perform label request procedure */
		if (addr != NULL) {
			/* XXX */
			break;
		}
	}
}

void
lde_nbr_do_mappings(struct rt_node *rn)
{
	struct lde_nbr	*ln;
	struct lde_map	*me;
	struct lde_req	*lre;

	/* This handles LMp.17-31 for lde_check_mapping() */

	RB_FOREACH(ln, nbr_tree, &lde_nbrs) {
		/* LMp.18 Did we already send a mapping to this peer? */
		me = (struct lde_map *)fec_find(&ln->sent_map, &rn->fec);
		if (me && me->label == rn->local_label)
			/* same mapping already sent, skip */
			/* TODO LMp.22-27 Loop detection check */
			continue;

		/* LMp.28 Is this from a pending request? */
		lre = (struct lde_req *)fec_find(&ln->recv_req, &rn->fec);

		/* Check for the only case where no mapping should be sent.
		 * This is the On Demand case of LMp.29  */
		if (ldpd_conf->mode & MODE_ADV_ONDEMAND && lre == NULL)
			/* adv. on demand but no req pending, skip */
			continue;

		lde_send_labelmapping(ln, rn);
		/* LMp.30 & 31 are not needed because labels are always added */
	}
}

void
lde_nbr_do_withdraws(struct rt_node *rn)
{
	struct lde_nbr	*ln;

	/* A.1.14.  LSR Decides to No Longer Label Switch a FEC */

	RB_FOREACH(ln, nbr_tree, &lde_nbrs)
		lde_send_labelwithdraw(ln, rn);
}

struct lde_map *
lde_map_add(struct lde_nbr *ln, struct rt_node *rn, int sent)
{
	struct lde_map  *me;

	me = XCALLOC(MTYPE_LDP, sizeof(*me));
	me->fec = rn->fec;
	me->nexthop = ln;

	if (sent) {
		LIST_INSERT_HEAD(&rn->upstream, me, entry);
		if (fec_insert(&ln->sent_map, &me->fec))
			zlog_warn("failed to add %s/%u to sent map",
			    inet_ntoa(me->fec.prefix), me->fec.prefixlen);
			/* XXX on failure more cleanup is needed */
	} else {
		LIST_INSERT_HEAD(&rn->downstream, me, entry);
		if (fec_insert(&ln->recv_map, &me->fec))
			zlog_warn("failed to add %s/%u to recv map",
			    inet_ntoa(me->fec.prefix), me->fec.prefixlen);
	}

	return (me);
}

void
lde_map_del(struct lde_nbr *ln, struct lde_map *me, int sent)
{
	if (sent)
		fec_remove(&ln->sent_map, &me->fec);
	else
		fec_remove(&ln->recv_map, &me->fec);

	lde_map_free(me);
}

void
lde_map_free(void *ptr)
{
	struct lde_map	*map = ptr;

	LIST_REMOVE(map, entry);
	XFREE(MTYPE_LDP, map);
}

struct lde_map *
lde_withdraw_add(struct lde_nbr *ln, struct rt_node *rn)
{
	struct lde_map  *me;

	me = XCALLOC(MTYPE_LDP, sizeof(*me));
	me->fec = rn->fec;

	if (fec_insert(&ln->sent_wdraw, &me->fec))
		zlog_warn("failed to add %s/%u to sent withdraw",
		    inet_ntoa(me->fec.prefix), me->fec.prefixlen);

	return (me);
}

struct lde_req *
lde_req_add(struct lde_nbr *ln, struct fec *fec, int sent)
{
	struct fec_tree	*ft;
	struct lde_req	*lre;

	ft = sent ? &ln->sent_req : &ln->recv_req;

	lre = XCALLOC(MTYPE_LDP, sizeof(*lre));

	lre->fec = *fec;

	if (fec_insert(ft, &lre->fec)) {
		zlog_warn("failed to add %s/%u to %s req",
		    inet_ntoa(lre->fec.prefix), lre->fec.prefixlen,
		    sent ? "sent" : "recv");
		XFREE(MTYPE_LDP, lre);
		return (NULL);
	}

	return (lre);
}

void
lde_req_del(struct lde_nbr *ln, struct lde_req *lre, int sent)
{
	if (sent)
		fec_remove(&ln->sent_req, &lre->fec);
	else
		fec_remove(&ln->recv_req, &lre->fec);

	XFREE(MTYPE_LDP, lre);
}

int
lde_address_add(struct lde_nbr *lr, struct in_addr *addr)
{
	struct lde_nbr_address	*address;

	if (lde_address_find(lr, addr) != NULL)
		return (-1);

	address = XCALLOC(MTYPE_LDP, sizeof(*address));
	address->addr.s_addr = addr->s_addr;

	TAILQ_INSERT_TAIL(&lr->addr_list, address, entry);

	log_event("lde_address_add: added %s", inet_ntoa(*addr));

	return (0);
}

struct lde_nbr_address *
lde_address_find(struct lde_nbr *lr, struct in_addr *addr)
{
	struct lde_nbr_address	*address = NULL;

	TAILQ_FOREACH(address, &lr->addr_list, entry) {
		if (address->addr.s_addr == addr->s_addr)
			return (address);
	}

	return (NULL);
}

int
lde_address_del(struct lde_nbr *lr, struct in_addr *addr)
{
	struct lde_nbr_address	*address;

	address = lde_address_find(lr, addr);
	if (address == NULL)
		return (-1);

	TAILQ_REMOVE(&lr->addr_list, address, entry);

	XFREE(MTYPE_LDP, address);

	log_event("lde_address_del: deleted %s", inet_ntoa(*addr));

	return (0);
}

void
lde_address_list_free(struct lde_nbr *nbr)
{
	struct lde_nbr_address	*addr;

	while ((addr = TAILQ_FIRST(&nbr->addr_list)) != NULL) {
		TAILQ_REMOVE(&nbr->addr_list, addr, entry);
		XFREE(MTYPE_LDP, addr);
	}
}

struct lde_nbr *
lde_find_address(struct in_addr address)
{
	struct lde_nbr	*ln;

	RB_FOREACH(ln, nbr_tree, &lde_nbrs) {
		if (lde_address_find(ln, &address) != NULL)
			return (ln);
	}

	return (NULL);
}
