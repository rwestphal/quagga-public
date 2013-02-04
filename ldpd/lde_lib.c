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

#include "memory.h"

#include "ldpd.h"
#include "ldpe.h"
#include "lde.h"
#include "ldp_debug.h"

static int fec_compare(struct fec *, struct fec *);

void		 rt_free(void *);
struct rt_node	*rt_add(struct in_addr, u_int8_t);

RB_PROTOTYPE(fec_tree, fec, entry, fec_compare)
RB_GENERATE(fec_tree, fec, entry, fec_compare)

struct fec_tree	rt = RB_INITIALIZER(&rt);

/* FEC tree fucntions */
void
fec_init(struct fec_tree *fh)
{
	RB_INIT(fh);
}

static int
fec_compare(struct fec *a, struct fec *b)
{
	if (ntohl(a->prefix.s_addr) < ntohl(b->prefix.s_addr))
		return (-1);
	if (ntohl(a->prefix.s_addr) > ntohl(b->prefix.s_addr))
		return (1);
	if (a->prefixlen < b->prefixlen)
		return (-1);
	if (a->prefixlen > b->prefixlen)
		return (1);

	return (0);
}

struct fec *
fec_find_prefix(struct fec_tree *fh, in_addr_t prefix, u_int8_t prefixlen)
{
	struct fec	 s;

	s.prefix.s_addr = prefix;
	s.prefixlen = prefixlen;

	return (fec_find(fh, &s));
}

struct fec *
fec_find(struct fec_tree *fh, struct fec *f)
{
	return (RB_FIND(fec_tree, fh, f));
}


int
fec_insert(struct fec_tree *fh, struct fec *f)
{
	if (RB_INSERT(fec_tree, fh, f) != NULL)
		return (-1);
	return (0);
}

int
fec_remove(struct fec_tree *fh, struct fec *f)
{
	if (RB_REMOVE(fec_tree, fh, f) == NULL) {
		zlog_warn("fec_remove failed for %s/%u",
		    inet_ntoa(f->prefix), f->prefixlen);
		return (-1);
	}
	return (0);
}

void
fec_clear(struct fec_tree *fh, void (*free_cb)(void *))
{
	struct fec	*f;

	while ((f = RB_ROOT(fh)) != NULL) {
		fec_remove(fh, f);
		if (free_cb == free)
			XFREE(MTYPE_LDP, f);
		else
			free_cb(f);
	}
}


/* routing table functions */
void
rt_snap(struct lde_nbr *ln)
{
	struct fec	*f;
	struct rt_node	*r;
	struct lde_map	*me;
	struct map	 map;

	bzero(&map, sizeof(map));
	RB_FOREACH(f, fec_tree, &rt) {
		r = (struct rt_node *)f;
		map.prefix = r->fec.prefix;
		map.prefixlen = r->fec.prefixlen;
		map.label = r->local_label;

		me = lde_map_add(ln, r, 1);
		me->label = r->local_label;

		ldpe_process(IMSG_MAPPING_ADD, ln->peerid, &map, sizeof(map));
	}
}

void
rt_free(void *arg)
{
	struct rt_node	*rr = arg;

	if (!LIST_EMPTY(&rr->downstream))
		zlog_warn("rt_free: fec %s/%u downstream list not empty",
		    inet_ntoa(rr->fec.prefix), rr->fec.prefixlen);
	if (!LIST_EMPTY(&rr->upstream))
		zlog_warn("rt_free: fec %s/%u upstream list not empty",
		    inet_ntoa(rr->fec.prefix), rr->fec.prefixlen);

	rr->local_label = NO_LABEL;
	lde_zebra_change_input_label(rr);
	if (rr->lsp.remote_label != NO_LABEL)
	  lde_zebra_delete_lsp(rr);

	XFREE(MTYPE_LDP, rr);
}

void
rt_clear(void)
{
	fec_clear(&rt, rt_free);
}

struct rt_node *
rt_add(struct in_addr prefix, u_int8_t prefixlen)
{
	struct rt_node	*rn;

	rn = XCALLOC(MTYPE_LDP, sizeof(*rn));
	rn->fec.prefix.s_addr = prefix.s_addr;
	rn->fec.prefixlen = prefixlen;
	rn->lsp.nexthop.s_addr = INADDR_ANY;
	rn->lsp.remote_label = NO_LABEL;
	rn->local_label = NO_LABEL;
	LIST_INIT(&rn->upstream);
	LIST_INIT(&rn->downstream);

	if (fec_insert(&rt, &rn->fec))
		zlog_warn("failed to add %s/%u to rt tree",
		    inet_ntoa(rn->fec.prefix), rn->fec.prefixlen);

	return (rn);
}

struct rt_node *
rt_get(struct in_addr prefix, u_int8_t prefixlen)
{
	struct rt_node *rn;

	rn = (struct rt_node *)fec_find_prefix(&rt, prefix.s_addr,
	      prefixlen);
	if (rn == NULL)
		rn = rt_add(prefix, prefixlen);

	return (rn);
}

u_char
lsr_egress_for_fec(struct rt_node *rn)
{
	return (rn->connected);
}

static u_int32_t
lde_assign_label(struct rt_node *rn)
{
	/* Directly connected route */
	if (lsr_egress_for_fec(rn)) {
		if (CHECK_FLAG(ldpd_conf->opts, LDPD_OPT_EXPLICIT_NULL))
			return MPLS_IPV4_EXPLICIT_NULL;
		else
			return MPLS_LABEL_IMPLNULL;
	}

	/* XXX handle possible failure */
	return ldp_zebra_request_label();
}

void
lde_kernel_insert(struct kroute *kr)
{
	struct rt_node		*rn;

	rn = rt_get(kr->prefix, kr->prefixlen);

	/* If the next hop of a route change, zebra will withdraw that
	 * route and advertise it again with the new next hop. So we
	 * don't have to deal with next hop changes in this code */
	rn->lsp.nexthop = kr->nexthop;
	rn->connected = kr->connected;

	/* Set input label */
	if (rn->local_label == NO_LABEL) {
		rn->local_label = lde_assign_label(rn);
		rn->assigned_local_label = rn->local_label;
		lde_zebra_change_input_label(rn);
	}

	lde_recognize_new_fec(rn);
}

void
lde_kernel_remove(struct kroute *kr)
{
	struct rt_node		*rn;

	rn = (struct rt_node *)fec_find_prefix(&rt, kr->prefix.s_addr,
	    kr->prefixlen);
	if (rn == NULL)
		/* route lost */
		return;

	rn->lsp.nexthop.s_addr = INADDR_ANY;
	rn->lsp.remote_label = NO_LABEL;

	/* Send a label withdraw message to every nbr */
	lde_nbr_do_withdraws(rn);
}

void
lde_kernel_change_input_label(struct kroute *kr)
{
	struct rt_node		*rn;
	u_char			 rn_active = 1;

	rn = (struct rt_node *)fec_find_prefix(&rt, kr->prefix.s_addr,
	    kr->prefixlen);
	if (rn == NULL) {
		rn_active = 0;
		rn = rt_add(kr->prefix, kr->prefixlen);
	}

	if (rn_active)
		lde_kernel_remove(kr);

	/* Set input label */
	if (kr->local_label == NO_LABEL)
		/* Label previously assigned by LDP */
		rn->local_label = rn->assigned_local_label;
	else
		rn->local_label = kr->local_label;

	if (rn_active)
		lde_kernel_insert(kr);
}

void
lde_check_mapping(struct map *map, struct lde_nbr *ln)
{
	struct rt_node		*rn;
	struct lde_req		*lre;
	struct lde_nbr_address	*addr = NULL;
	struct lde_map		*me;

	log_pkt_recv("label mapping from nbr %s, FEC %s, label %u",
	    inet_ntoa(ln->id), log_fec(map), map->label);

	/* Add the route to the FIB if it's not there. In this case,
	 * there is no need to assign a local label because this function
	 * will return on LMp.12 */
	rn = rt_get(map->prefix, map->prefixlen);

	/* LMp.1 - LMp.2: first check if we have a pending request running */
	lre = (struct lde_req *)fec_find(&ln->sent_req, &rn->fec);
	if (lre)
		lde_req_del(ln, lre, 1);

	/* TODO Loop detection LMp.3 - LMp.8 */

	LIST_FOREACH(me, &rn->downstream, entry) {
		if (ln != me->nexthop)				/* LMp.9 */
			continue;

		if (lre)
			/* LMp.10 Note 6: req. mappings are always new */
			break;

		if (me->label == map->label)
			break;

		/* LMp.10a (introduced by RFC5036) */
		if (ldpd_conf->mode & MODE_ADV_UNSOLICITED) {
			if (lde_address_find(ln, &rn->lsp.nexthop)
			    && me->label == rn->lsp.remote_label) {
				lde_zebra_delete_lsp(rn);
				rn->lsp.remote_label = NO_LABEL;
			}

			lde_send_labelrelease(ln, rn, me->label);
			lde_map_del(ln, me, 0);
			me = NULL;
		}
		break;
	}

	/* LMp.11: get nexthop */
	addr = lde_address_find(ln, &rn->lsp.nexthop);

	/* LMp.12: is MsgSource the next hop for FEC? */
	if (addr == NULL) {
		/* LMp.13: route not yet available */
		if (ldpd_conf->mode & MODE_RET_CONSERVATIVE) {
			lde_send_labelrelease(ln, rn, map->label);
			return;
		}
		/* in liberal mode just note the mapping */
		if (me == NULL)
			me = lde_map_add(ln, rn, 0);
		me->label = map->label;

		return;
	}

	/* LMp.14: do we actually need this FEC for now this is always true */
	rn->lsp.remote_label = map->label;

	/* LMp.15: install FEC in the LFIB */
	lde_zebra_add_lsp(rn);

	/* LMp.16: Record the mapping from this peer */
	if (me == NULL)
		me = lde_map_add(ln, rn, 0);
	me->label = map->label;

	/* LMp.17-31: Redistribute the current mapping to every nbr */
	lde_nbr_do_mappings(rn);
}

void
lde_check_request(struct map *map, struct lde_nbr *ln)
{
	struct lde_req	*lre;
	struct rt_node	*rn;
	struct lde_nbr	*lnn;
	struct lde_map  *me;
	u_int8_t	 retained_prev_map = 0;

	log_pkt_recv("label request from nbr %s, FEC %s",
	    inet_ntoa(ln->id), log_fec(map));

	/* LRq.2 */
	rn = (struct rt_node *)fec_find_prefix(&rt, map->prefix.s_addr,
	    map->prefixlen);
	if (rn == NULL) {
		/* LRq.5 */
		lde_send_notification(ln->peerid, S_NO_ROUTE, map->messageid,
		    MSG_TYPE_LABELREQUEST);
		return;
	}

	/* LRq.3 */
	if (lde_address_find(ln, &rn->lsp.nexthop)) {
		/* LRq.4 */
		lde_send_notification(ln->peerid, S_LOOP_DETECTED,
		    map->messageid, MSG_TYPE_LABELREQUEST);
		return;
	}

	/* LRq.6: first check if we have a pending request running */
	lre = (struct lde_req *)fec_find(&ln->recv_req, &rn->fec);
	if (lre != NULL)
		/* LRq.7: duplicate request */
		return;

	/* LRq.8: record label request */
	lre = lde_req_add(ln, &rn->fec, 0);
	if (lre != NULL)
		lre->msgid = map->messageid;

	/* LRq.9 */
	me = (struct lde_map *)fec_find(&ln->recv_map, &rn->fec);
	if (me && lde_address_find(ln, &rn->lsp.nexthop)
	    && me->label == rn->lsp.remote_label)
		retained_prev_map = 1;

	if (ldpd_conf->mode & MODE_DIST_INDEPENDENT) {
		lde_send_labelmapping(ln, rn);
		if (lsr_egress_for_fec(rn) || retained_prev_map)
			return;
	} else {
		if (lsr_egress_for_fec(rn) || retained_prev_map)
			lde_send_labelmapping(ln, rn);
	}

	/* LRq.10: Perform LSR label request procedure */
	lnn = lde_find_address(rn->lsp.nexthop);
	if (lnn != NULL)
		lde_send_labelrequest(lnn, rn);
}

void
lde_check_release(struct map *map, struct lde_nbr *ln)
{
	struct rt_node	*rn;
	struct lde_req	*lre;
	struct lde_map	*me;

	log_pkt_recv("label release from nbr %s, FEC %s",
	    inet_ntoa(ln->id), log_fec(map));

	/* LRl.1 */
	rn = (struct rt_node *)fec_find_prefix(&rt, map->prefix.s_addr,
	    map->prefixlen);
	if (rn == NULL)
		return;

	/* LRl.3 - LRl.4: first check if we have a pending withdraw running */
	lre = (struct lde_req *)fec_find(&ln->sent_wdraw, &rn->fec);
	if (lre) {
		fec_remove(&ln->sent_wdraw, &lre->fec);
		XFREE(MTYPE_LDP, lre);
	}

	/* check sent map list and remove it if available */
	me = (struct lde_map *)fec_find(&ln->sent_map, &rn->fec);
	if (me)
		lde_map_del(ln, me, 1);

	/* remove FEC if not in use anymore */
	/* XXX what about outstanding label requests? */
	if (!LIST_EMPTY(&rn->upstream))
		return;

	/* XXX if originated here free all resources */
	/* else decide if a label release should be forwarded. */
	/* Since we do liberal retention we can keep the path mapped. */
}

void
lde_check_withdraw(struct map *map, struct lde_nbr *ln)
{
	struct rt_node	*rn;
	struct lde_map	*me;

	log_pkt_recv("label withdraw from nbr %s, FEC %s",
	    inet_ntoa(ln->id), log_fec(map));

	rn = rt_get(map->prefix, map->prefixlen);

	/* LWd.1: remove LSP from kernel */
	if (lde_address_find(ln, &rn->lsp.nexthop)) {
		lde_zebra_delete_lsp(rn);
		rn->lsp.remote_label = NO_LABEL;
	}

	/* LWd.2 */
	lde_send_labelrelease(ln, rn, map->label);

	/* LWd.3: check recv map list and remove it if available */
	me = (struct lde_map *)fec_find(&ln->recv_map, &rn->fec);
	if (me == NULL)
		return;

	/* LWd.4 */
	lde_map_del(ln, me, 0);

	/* LWd.5: If ordered distribution */
	/* LWd.8-12: walk over upstream list and send withdraws for
	 * LSP that depend on the removed LSP and return */

	/* LWd.6: If independent distribution and adv on demand */
	if (ldpd_conf->mode & MODE_ADV_ONDEMAND)
		/* LWd.7: Generate Event: Recognize New FEC for FEC. */
		lde_recognize_new_fec(rn);

	return;
}
