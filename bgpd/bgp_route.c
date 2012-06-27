/* BGP routing information
   Copyright (C) 1996, 97, 98, 99 Kunihiro Ishiguro

This file is part of GNU Zebra.

GNU Zebra is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2, or (at your option) any
later version.

GNU Zebra is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU Zebra; see the file COPYING.  If not, write to the Free
Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
02111-1307, USA.  */

#include <zebra.h>

#include "prefix.h"
#include "linklist.h"
#include "memory.h"
#include "command.h"
#include "stream.h"
#include "filter.h"
#include "str.h"
#include "log.h"
#include "routemap.h"
#include "buffer.h"
#include "sockunion.h"
#include "plist.h"
#include "thread.h"
#include "workqueue.h"

#include "bgpd/bgpd.h"
#include "bgpd/bgp_table.h"
#include "bgpd/bgp_route.h"
#include "bgpd/bgp_attr.h"
#include "bgpd/bgp_debug.h"
#include "bgpd/bgp_aspath.h"
#include "bgpd/bgp_regex.h"
#include "bgpd/bgp_community.h"
#include "bgpd/bgp_ecommunity.h"
#include "bgpd/bgp_clist.h"
#include "bgpd/bgp_packet.h"
#include "bgpd/bgp_filter.h"
#include "bgpd/bgp_fsm.h"
#include "bgpd/bgp_mplsvpn.h"
#include "bgpd/bgp_nexthop.h"
#include "bgpd/bgp_damp.h"
#include "bgpd/bgp_advertise.h"
#include "bgpd/bgp_zebra.h"
#include "bgpd/bgp_vty.h"
#include "bgpd/bgp_mpath.h"

static struct bgp_node *
bgp_afi_node_get (struct bgp_table *table, afi_t afi, safi_t safi, struct prefix *p,
		  struct prefix_rd *prd)
{
  struct bgp_node *rn;
  struct bgp_node *prn = NULL;
  
  assert (table);
  if (!table)
    return NULL;
  
  if (safi == SAFI_MPLS_VPN)
    {
      prn = bgp_node_get (table, (struct prefix *) prd);

      if (prn->info == NULL)
	prn->info = bgp_table_init (afi, safi);
      else
	bgp_unlock_node (prn);
      table = prn->info;
    }

  rn = bgp_node_get (table, p);

  if (safi == SAFI_MPLS_VPN)
    rn->prn = prn;

  return rn;
}

/* Allocate bgp_info_extra */
static struct bgp_info_extra *
bgp_info_extra_new (void)
{
  struct bgp_info_extra *new;
  new = XCALLOC (MTYPE_BGP_ROUTE_EXTRA, sizeof (struct bgp_info_extra));
  return new;
}

static void
bgp_info_extra_free (struct bgp_info_extra **extra)
{
  if (extra && *extra)
    {
      if ((*extra)->damp_info)
        bgp_damp_info_free ((*extra)->damp_info, 0);
      
      (*extra)->damp_info = NULL;
      
      XFREE (MTYPE_BGP_ROUTE_EXTRA, *extra);
      
      *extra = NULL;
    }
}

/* Get bgp_info extra information for the given bgp_info, lazy allocated
 * if required.
 */
struct bgp_info_extra *
bgp_info_extra_get (struct bgp_info *ri)
{
  if (!ri->extra)
    ri->extra = bgp_info_extra_new();
  return ri->extra;
}

/* Allocate new bgp info structure. */
static struct bgp_info *
bgp_info_new (void)
{
  return XCALLOC (MTYPE_BGP_ROUTE, sizeof (struct bgp_info));
}

/* Free bgp route information. */
static void
bgp_info_free (struct bgp_info *binfo)
{
  if (binfo->attr)
    bgp_attr_unintern (&binfo->attr);
  
  bgp_info_extra_free (&binfo->extra);
  bgp_info_mpath_free (&binfo->mpath);

  peer_unlock (binfo->peer); /* bgp_info peer reference */

  XFREE (MTYPE_BGP_ROUTE, binfo);
}

struct bgp_info *
bgp_info_lock (struct bgp_info *binfo)
{
  binfo->lock++;
  return binfo;
}

struct bgp_info *
bgp_info_unlock (struct bgp_info *binfo)
{
  assert (binfo && binfo->lock > 0);
  binfo->lock--;
  
  if (binfo->lock == 0)
    {
#if 0
      zlog_debug ("%s: unlocked and freeing", __func__);
      zlog_backtrace (LOG_DEBUG);
#endif
      bgp_info_free (binfo);
      return NULL;
    }

#if 0
  if (binfo->lock == 1)
    {
      zlog_debug ("%s: unlocked to 1", __func__);
      zlog_backtrace (LOG_DEBUG);
    }
#endif
  
  return binfo;
}

void
bgp_info_add (struct bgp_node *rn, struct bgp_info *ri)
{
  struct bgp_info *top;

  top = rn->info;
  
  ri->next = rn->info;
  ri->prev = NULL;
  if (top)
    top->prev = ri;
  rn->info = ri;
  
  bgp_info_lock (ri);
  bgp_lock_node (rn);
  peer_lock (ri->peer); /* bgp_info peer reference */
}

/* Do the actual removal of info from RIB, for use by bgp_process 
   completion callback *only* */
static void
bgp_info_reap (struct bgp_node *rn, struct bgp_info *ri)
{
  if (ri->next)
    ri->next->prev = ri->prev;
  if (ri->prev)
    ri->prev->next = ri->next;
  else
    rn->info = ri->next;
  
  bgp_info_mpath_dequeue (ri);
  bgp_info_unlock (ri);
  bgp_unlock_node (rn);
}

void
bgp_info_delete (struct bgp_node *rn, struct bgp_info *ri)
{
  bgp_info_set_flag (rn, ri, BGP_INFO_REMOVED);
  /* set of previous already took care of pcount */
  UNSET_FLAG (ri->flags, BGP_INFO_VALID);
}

/* undo the effects of a previous call to bgp_info_delete; typically
   called when a route is deleted and then quickly re-added before the
   deletion has been processed */
static void
bgp_info_restore (struct bgp_node *rn, struct bgp_info *ri)
{
  bgp_info_unset_flag (rn, ri, BGP_INFO_REMOVED);
  /* unset of previous already took care of pcount */
  SET_FLAG (ri->flags, BGP_INFO_VALID);
}

/* Adjust pcount as required */   
static void
bgp_pcount_adjust (struct bgp_node *rn, struct bgp_info *ri)
{
  assert (rn && rn->table);
  assert (ri && ri->peer && ri->peer->bgp);

  /* Ignore 'pcount' for RS-client tables */
  if (rn->table->type != BGP_TABLE_MAIN
      || ri->peer == ri->peer->bgp->peer_self)
    return;
    
  if (BGP_INFO_HOLDDOWN (ri)
      && CHECK_FLAG (ri->flags, BGP_INFO_COUNTED))
    {
          
      UNSET_FLAG (ri->flags, BGP_INFO_COUNTED);
      
      /* slight hack, but more robust against errors. */
      if (ri->peer->pcount[rn->table->afi][rn->table->safi])
        ri->peer->pcount[rn->table->afi][rn->table->safi]--;
      else
        {
          zlog_warn ("%s: Asked to decrement 0 prefix count for peer %s",
                     __func__, ri->peer->host);
          zlog_backtrace (LOG_WARNING);
          zlog_warn ("%s: Please report to Quagga bugzilla", __func__);
        }      
    }
  else if (!BGP_INFO_HOLDDOWN (ri) 
           && !CHECK_FLAG (ri->flags, BGP_INFO_COUNTED))
    {
      SET_FLAG (ri->flags, BGP_INFO_COUNTED);
      ri->peer->pcount[rn->table->afi][rn->table->safi]++;
    }
}


/* Set/unset bgp_info flags, adjusting any other state as needed.
 * This is here primarily to keep prefix-count in check.
 */
void
bgp_info_set_flag (struct bgp_node *rn, struct bgp_info *ri, u_int32_t flag)
{
  SET_FLAG (ri->flags, flag);
  
  /* early bath if we know it's not a flag that changes useability state */
  if (!CHECK_FLAG (flag, BGP_INFO_VALID|BGP_INFO_UNUSEABLE))
    return;
  
  bgp_pcount_adjust (rn, ri);
}

void
bgp_info_unset_flag (struct bgp_node *rn, struct bgp_info *ri, u_int32_t flag)
{
  UNSET_FLAG (ri->flags, flag);
  
  /* early bath if we know it's not a flag that changes useability state */
  if (!CHECK_FLAG (flag, BGP_INFO_VALID|BGP_INFO_UNUSEABLE))
    return;
  
  bgp_pcount_adjust (rn, ri);
}

/* Get MED value.  If MED value is missing and "bgp bestpath
   missing-as-worst" is specified, treat it as the worst value. */
static u_int32_t
bgp_med_value (struct attr *attr, struct bgp *bgp)
{
  if (attr->flag & ATTR_FLAG_BIT (BGP_ATTR_MULTI_EXIT_DISC))
    return attr->med;
  else
    {
      if (bgp_flag_check (bgp, BGP_FLAG_MED_MISSING_AS_WORST))
	return BGP_MED_MAX;
      else
	return 0;
    }
}

/* Compare two bgp route entity.  br is preferable then return 1. */
static int
bgp_info_cmp (struct bgp *bgp, struct bgp_info *new, struct bgp_info *exist,
	      int *paths_eq)
{
  struct attr *newattr, *existattr;
  struct attr_extra *newattre, *existattre;
  bgp_peer_sort_t new_sort;
  bgp_peer_sort_t exist_sort;
  u_int32_t new_pref;
  u_int32_t exist_pref;
  u_int32_t new_med;
  u_int32_t exist_med;
  u_int32_t new_weight;
  u_int32_t exist_weight;
  uint32_t newm, existm;
  struct in_addr new_id;
  struct in_addr exist_id;
  int new_cluster;
  int exist_cluster;
  int internal_as_route;
  int confed_as_route;
  int ret;

  *paths_eq = 0;

  /* 0. Null check. */
  if (new == NULL)
    return 0;
  if (exist == NULL)
    return 1;

  newattr = new->attr;
  existattr = exist->attr;
  newattre = newattr->extra;
  existattre = existattr->extra;

  /* 1. Weight check. */
  new_weight = exist_weight = 0;

  if (newattre)
    new_weight = newattre->weight;
  if (existattre)
    exist_weight = existattre->weight;

  if (new_weight > exist_weight)
    return 1;
  if (new_weight < exist_weight)
    return 0;

  /* 2. Local preference check. */
  new_pref = exist_pref = bgp->default_local_pref;

  if (newattr->flag & ATTR_FLAG_BIT (BGP_ATTR_LOCAL_PREF))
    new_pref = newattr->local_pref;
  if (existattr->flag & ATTR_FLAG_BIT (BGP_ATTR_LOCAL_PREF))
    exist_pref = existattr->local_pref;

  if (new_pref > exist_pref)
    return 1;
  if (new_pref < exist_pref)
    return 0;

  /* 3. Local route check. We prefer:
   *  - BGP_ROUTE_STATIC
   *  - BGP_ROUTE_AGGREGATE
   *  - BGP_ROUTE_REDISTRIBUTE
   */
  if (! (new->sub_type == BGP_ROUTE_NORMAL))
     return 1;
  if (! (exist->sub_type == BGP_ROUTE_NORMAL))
     return 0;

  /* 4. AS path length check. */
  if (! bgp_flag_check (bgp, BGP_FLAG_ASPATH_IGNORE))
    {
      int exist_hops = aspath_count_hops (existattr->aspath);
      int exist_confeds = aspath_count_confeds (existattr->aspath);
      
      if (bgp_flag_check (bgp, BGP_FLAG_ASPATH_CONFED))
	{
	  int aspath_hops;
	  
	  aspath_hops = aspath_count_hops (newattr->aspath);
          aspath_hops += aspath_count_confeds (newattr->aspath);
          
	  if ( aspath_hops < (exist_hops + exist_confeds))
	    return 1;
	  if ( aspath_hops > (exist_hops + exist_confeds))
	    return 0;
	}
      else
	{
	  int newhops = aspath_count_hops (newattr->aspath);
	  
	  if (newhops < exist_hops)
	    return 1;
          if (newhops > exist_hops)
	    return 0;
	}
    }

  /* 5. Origin check. */
  if (newattr->origin < existattr->origin)
    return 1;
  if (newattr->origin > existattr->origin)
    return 0;

  /* 6. MED check. */
  internal_as_route = (aspath_count_hops (newattr->aspath) == 0
		      && aspath_count_hops (existattr->aspath) == 0);
  confed_as_route = (aspath_count_confeds (newattr->aspath) > 0
		    && aspath_count_confeds (existattr->aspath) > 0
		    && aspath_count_hops (newattr->aspath) == 0
		    && aspath_count_hops (existattr->aspath) == 0);
  
  if (bgp_flag_check (bgp, BGP_FLAG_ALWAYS_COMPARE_MED)
      || (bgp_flag_check (bgp, BGP_FLAG_MED_CONFED)
	 && confed_as_route)
      || aspath_cmp_left (newattr->aspath, existattr->aspath)
      || aspath_cmp_left_confed (newattr->aspath, existattr->aspath)
      || internal_as_route)
    {
      new_med = bgp_med_value (new->attr, bgp);
      exist_med = bgp_med_value (exist->attr, bgp);

      if (new_med < exist_med)
	return 1;
      if (new_med > exist_med)
	return 0;
    }

  /* 7. Peer type check. */
  new_sort = new->peer->sort;
  exist_sort = exist->peer->sort;

  if (new_sort == BGP_PEER_EBGP
      && (exist_sort == BGP_PEER_IBGP || exist_sort == BGP_PEER_CONFED))
    return 1;
  if (exist_sort == BGP_PEER_EBGP
      && (new_sort == BGP_PEER_IBGP || new_sort == BGP_PEER_CONFED))
    return 0;

  /* 8. IGP metric check. */
  newm = existm = 0;

  if (new->extra)
    newm = new->extra->igpmetric;
  if (exist->extra)
    existm = exist->extra->igpmetric;

  if (newm < existm)
    ret = 1;
  if (newm > existm)
    ret = 0;

  /* 9. Maximum path check. */
  if (newm == existm)
    {
      if (new->peer->sort == BGP_PEER_IBGP)
	{
	  if (aspath_cmp (new->attr->aspath, exist->attr->aspath))
	    *paths_eq = 1;
	}
      else if (new->peer->as == exist->peer->as)
	*paths_eq = 1;
    }
  else
    {
      /*
       * TODO: If unequal cost ibgp multipath is enabled we can
       * mark the paths as equal here instead of returning
       */
      return ret;
    }

  /* 10. If both paths are external, prefer the path that was received
     first (the oldest one).  This step minimizes route-flap, since a
     newer path won't displace an older one, even if it was the
     preferred route based on the additional decision criteria below.  */
  if (! bgp_flag_check (bgp, BGP_FLAG_COMPARE_ROUTER_ID)
      && new_sort == BGP_PEER_EBGP
      && exist_sort == BGP_PEER_EBGP)
    {
      if (CHECK_FLAG (new->flags, BGP_INFO_SELECTED))
	return 1;
      if (CHECK_FLAG (exist->flags, BGP_INFO_SELECTED))
	return 0;
    }

  /* 11. Rourter-ID comparision. */
  if (newattr->flag & ATTR_FLAG_BIT(BGP_ATTR_ORIGINATOR_ID))
    new_id.s_addr = newattre->originator_id.s_addr;
  else
    new_id.s_addr = new->peer->remote_id.s_addr;
  if (existattr->flag & ATTR_FLAG_BIT(BGP_ATTR_ORIGINATOR_ID))
    exist_id.s_addr = existattre->originator_id.s_addr;
  else
    exist_id.s_addr = exist->peer->remote_id.s_addr;

  if (ntohl (new_id.s_addr) < ntohl (exist_id.s_addr))
    return 1;
  if (ntohl (new_id.s_addr) > ntohl (exist_id.s_addr))
    return 0;

  /* 12. Cluster length comparision. */
  new_cluster = exist_cluster = 0;

  if (newattr->flag & ATTR_FLAG_BIT(BGP_ATTR_CLUSTER_LIST))
    new_cluster = newattre->cluster->length;
  if (existattr->flag & ATTR_FLAG_BIT(BGP_ATTR_CLUSTER_LIST))
    exist_cluster = existattre->cluster->length;

  if (new_cluster < exist_cluster)
    return 1;
  if (new_cluster > exist_cluster)
    return 0;

  /* 13. Neighbor address comparision. */
  ret = sockunion_cmp (new->peer->su_remote, exist->peer->su_remote);

  if (ret == 1)
    return 0;
  if (ret == -1)
    return 1;

  return 1;
}

static enum filter_type
bgp_input_filter (struct peer *peer, struct prefix *p, struct attr *attr,
		  afi_t afi, safi_t safi)
{
  struct bgp_filter *filter;

  filter = &peer->filter[afi][safi];

#define FILTER_EXIST_WARN(F,f,filter) \
  if (BGP_DEBUG (update, UPDATE_IN) \
      && !(F ## _IN (filter))) \
    plog_warn (peer->log, "%s: Could not find configured input %s-list %s!", \
               peer->host, #f, F ## _IN_NAME(filter));
  
  if (DISTRIBUTE_IN_NAME (filter)) {
    FILTER_EXIST_WARN(DISTRIBUTE, distribute, filter);
      
    if (access_list_apply (DISTRIBUTE_IN (filter), p) == FILTER_DENY)
      return FILTER_DENY;
  }

  if (PREFIX_LIST_IN_NAME (filter)) {
    FILTER_EXIST_WARN(PREFIX_LIST, prefix, filter);
    
    if (prefix_list_apply (PREFIX_LIST_IN (filter), p) == PREFIX_DENY)
      return FILTER_DENY;
  }
  
  if (FILTER_LIST_IN_NAME (filter)) {
    FILTER_EXIST_WARN(FILTER_LIST, as, filter);
    
    if (as_list_apply (FILTER_LIST_IN (filter), attr->aspath)== AS_FILTER_DENY)
      return FILTER_DENY;
  }
  
  return FILTER_PERMIT;
#undef FILTER_EXIST_WARN
}

static enum filter_type
bgp_output_filter (struct peer *peer, struct prefix *p, struct attr *attr,
		   afi_t afi, safi_t safi)
{
  struct bgp_filter *filter;

  filter = &peer->filter[afi][safi];

#define FILTER_EXIST_WARN(F,f,filter) \
  if (BGP_DEBUG (update, UPDATE_OUT) \
      && !(F ## _OUT (filter))) \
    plog_warn (peer->log, "%s: Could not find configured output %s-list %s!", \
               peer->host, #f, F ## _OUT_NAME(filter));

  if (DISTRIBUTE_OUT_NAME (filter)) {
    FILTER_EXIST_WARN(DISTRIBUTE, distribute, filter);
    
    if (access_list_apply (DISTRIBUTE_OUT (filter), p) == FILTER_DENY)
      return FILTER_DENY;
  }

  if (PREFIX_LIST_OUT_NAME (filter)) {
    FILTER_EXIST_WARN(PREFIX_LIST, prefix, filter);
    
    if (prefix_list_apply (PREFIX_LIST_OUT (filter), p) == PREFIX_DENY)
      return FILTER_DENY;
  }

  if (FILTER_LIST_OUT_NAME (filter)) {
    FILTER_EXIST_WARN(FILTER_LIST, as, filter);
    
    if (as_list_apply (FILTER_LIST_OUT (filter), attr->aspath) == AS_FILTER_DENY)
      return FILTER_DENY;
  }

  return FILTER_PERMIT;
#undef FILTER_EXIST_WARN
}

/* If community attribute includes no_export then return 1. */
static int
bgp_community_filter (struct peer *peer, struct attr *attr)
{
  if (attr->community)
    {
      /* NO_ADVERTISE check. */
      if (community_include (attr->community, COMMUNITY_NO_ADVERTISE))
	return 1;

      /* NO_EXPORT check. */
      if (peer->sort == BGP_PEER_EBGP &&
	  community_include (attr->community, COMMUNITY_NO_EXPORT))
	return 1;

      /* NO_EXPORT_SUBCONFED check. */
      if (peer->sort == BGP_PEER_EBGP
	  || peer->sort == BGP_PEER_CONFED)
	if (community_include (attr->community, COMMUNITY_NO_EXPORT_SUBCONFED))
	  return 1;
    }
  return 0;
}

/* Route reflection loop check.  */
static int
bgp_cluster_filter (struct peer *peer, struct attr *attr)
{
  struct in_addr cluster_id;

  if (attr->extra && attr->extra->cluster)
    {
      if (peer->bgp->config & BGP_CONFIG_CLUSTER_ID)
	cluster_id = peer->bgp->cluster_id;
      else
	cluster_id = peer->bgp->router_id;
      
      if (cluster_loop_check (attr->extra->cluster, cluster_id))
	return 1;
    }
  return 0;
}

static int
bgp_input_modifier (struct peer *peer, struct prefix *p, struct attr *attr,
		    afi_t afi, safi_t safi)
{
  struct bgp_filter *filter;
  struct bgp_info info;
  route_map_result_t ret;

  filter = &peer->filter[afi][safi];

  /* Apply default weight value. */
  if (peer->weight)
    (bgp_attr_extra_get (attr))->weight = peer->weight;

  /* Route map apply. */
  if (ROUTE_MAP_IN_NAME (filter))
    {
      /* Duplicate current value to new strucutre for modification. */
      info.peer = peer;
      info.attr = attr;

      SET_FLAG (peer->rmap_type, PEER_RMAP_TYPE_IN); 

      /* Apply BGP route map to the attribute. */
      ret = route_map_apply (ROUTE_MAP_IN (filter), p, RMAP_BGP, &info);

      peer->rmap_type = 0;

      if (ret == RMAP_DENYMATCH)
	{
	  /* Free newly generated AS path and community by route-map. */
	  bgp_attr_flush (attr);
	  return RMAP_DENY;
	}
    }
  return RMAP_PERMIT;
}

static int
bgp_export_modifier (struct peer *rsclient, struct peer *peer,
        struct prefix *p, struct attr *attr, afi_t afi, safi_t safi)
{
  struct bgp_filter *filter;
  struct bgp_info info;
  route_map_result_t ret;

  filter = &peer->filter[afi][safi];

  /* Route map apply. */
  if (ROUTE_MAP_EXPORT_NAME (filter))
    {
      /* Duplicate current value to new strucutre for modification. */
      info.peer = rsclient;
      info.attr = attr;

      SET_FLAG (rsclient->rmap_type, PEER_RMAP_TYPE_EXPORT);

      /* Apply BGP route map to the attribute. */
      ret = route_map_apply (ROUTE_MAP_EXPORT (filter), p, RMAP_BGP, &info);

      rsclient->rmap_type = 0;

      if (ret == RMAP_DENYMATCH)
        {
          /* Free newly generated AS path and community by route-map. */
          bgp_attr_flush (attr);
          return RMAP_DENY;
        }
    }
  return RMAP_PERMIT;
}

static int
bgp_import_modifier (struct peer *rsclient, struct peer *peer,
        struct prefix *p, struct attr *attr, afi_t afi, safi_t safi)
{
  struct bgp_filter *filter;
  struct bgp_info info;
  route_map_result_t ret;

  filter = &rsclient->filter[afi][safi];

  /* Apply default weight value. */
  if (peer->weight)
    (bgp_attr_extra_get (attr))->weight = peer->weight;

  /* Route map apply. */
  if (ROUTE_MAP_IMPORT_NAME (filter))
    {
      /* Duplicate current value to new strucutre for modification. */
      info.peer = peer;
      info.attr = attr;

      SET_FLAG (peer->rmap_type, PEER_RMAP_TYPE_IMPORT);

      /* Apply BGP route map to the attribute. */
      ret = route_map_apply (ROUTE_MAP_IMPORT (filter), p, RMAP_BGP, &info);

      peer->rmap_type = 0;

      if (ret == RMAP_DENYMATCH)
        {
          /* Free newly generated AS path and community by route-map. */
          bgp_attr_flush (attr);
          return RMAP_DENY;
        }
    }
  return RMAP_PERMIT;
}

static int
bgp_announce_check (struct bgp_info *ri, struct peer *peer, struct prefix *p,
		    struct attr *attr, afi_t afi, safi_t safi)
{
  int ret;
  char buf[SU_ADDRSTRLEN];
  struct bgp_filter *filter;
  struct peer *from;
  struct bgp *bgp;
  int transparent;
  int reflect;
  struct attr *riattr;

  from = ri->peer;
  filter = &peer->filter[afi][safi];
  bgp = peer->bgp;
  riattr = bgp_info_mpath_count (ri) ? bgp_info_mpath_attr (ri) : ri->attr;
  
  if (DISABLE_BGP_ANNOUNCE)
    return 0;

  /* Do not send announces to RS-clients from the 'normal' bgp_table. */
  if (CHECK_FLAG(peer->af_flags[afi][safi], PEER_FLAG_RSERVER_CLIENT))
    return 0;

  /* Do not send back route to sender. */
  if (from == peer)
    return 0;

  /* If peer's id and route's nexthop are same. draft-ietf-idr-bgp4-23 5.1.3 */
  if (p->family == AF_INET
      && IPV4_ADDR_SAME(&peer->remote_id, &riattr->nexthop))
    return 0;
#ifdef HAVE_IPV6
  if (p->family == AF_INET6
     && IPV6_ADDR_SAME(&peer->remote_id, &riattr->nexthop))
    return 0;
#endif

  /* Aggregate-address suppress check. */
  if (ri->extra && ri->extra->suppress)
    if (! UNSUPPRESS_MAP_NAME (filter))
      return 0;

  /* Default route check.  */
  if (CHECK_FLAG (peer->af_sflags[afi][safi], PEER_STATUS_DEFAULT_ORIGINATE))
    {
      if (p->family == AF_INET && p->u.prefix4.s_addr == INADDR_ANY)
	return 0;
#ifdef HAVE_IPV6
      else if (p->family == AF_INET6 && p->prefixlen == 0)
	return 0;
#endif /* HAVE_IPV6 */
    }

  /* Transparency check. */
  if (CHECK_FLAG (peer->af_flags[afi][safi], PEER_FLAG_RSERVER_CLIENT)
      && CHECK_FLAG (from->af_flags[afi][safi], PEER_FLAG_RSERVER_CLIENT))
    transparent = 1;
  else
    transparent = 0;

  /* If community is not disabled check the no-export and local. */
  if (! transparent && bgp_community_filter (peer, riattr))
    return 0;

  /* If the attribute has originator-id and it is same as remote
     peer's id. */
  if (riattr->flag & ATTR_FLAG_BIT (BGP_ATTR_ORIGINATOR_ID))
    {
      if (IPV4_ADDR_SAME (&peer->remote_id, &riattr->extra->originator_id))
	{
	  if (BGP_DEBUG (filter, FILTER))  
	    zlog (peer->log, LOG_DEBUG,
		  "%s [Update:SEND] %s/%d originator-id is same as remote router-id",
		  peer->host,
		  inet_ntop(p->family, &p->u.prefix, buf, SU_ADDRSTRLEN),
		  p->prefixlen);
	  return 0;
	}
    }
 
  /* ORF prefix-list filter check */
  if (CHECK_FLAG (peer->af_cap[afi][safi], PEER_CAP_ORF_PREFIX_RM_ADV)
      && (CHECK_FLAG (peer->af_cap[afi][safi], PEER_CAP_ORF_PREFIX_SM_RCV)
	  || CHECK_FLAG (peer->af_cap[afi][safi], PEER_CAP_ORF_PREFIX_SM_OLD_RCV)))
    if (peer->orf_plist[afi][safi])
      {
	if (prefix_list_apply (peer->orf_plist[afi][safi], p) == PREFIX_DENY)
          return 0;
      }

  /* Output filter check. */
  if (bgp_output_filter (peer, p, riattr, afi, safi) == FILTER_DENY)
    {
      if (BGP_DEBUG (filter, FILTER))
	zlog (peer->log, LOG_DEBUG,
	      "%s [Update:SEND] %s/%d is filtered",
	      peer->host,
	      inet_ntop(p->family, &p->u.prefix, buf, SU_ADDRSTRLEN),
	      p->prefixlen);
      return 0;
    }

#ifdef BGP_SEND_ASPATH_CHECK
  /* AS path loop check. */
  if (aspath_loop_check (riattr->aspath, peer->as))
    {
      if (BGP_DEBUG (filter, FILTER))  
        zlog (peer->log, LOG_DEBUG, 
	      "%s [Update:SEND] suppress announcement to peer AS %u is AS path.",
	      peer->host, peer->as);
      return 0;
    }
#endif /* BGP_SEND_ASPATH_CHECK */

  /* If we're a CONFED we need to loop check the CONFED ID too */
  if (CHECK_FLAG(bgp->config, BGP_CONFIG_CONFEDERATION))
    {
      if (aspath_loop_check(riattr->aspath, bgp->confed_id))
	{
	  if (BGP_DEBUG (filter, FILTER))  
	    zlog (peer->log, LOG_DEBUG, 
		  "%s [Update:SEND] suppress announcement to peer AS %u is AS path.",
		  peer->host,
		  bgp->confed_id);
	  return 0;
	}      
    }

  /* Route-Reflect check. */
  if (from->sort == BGP_PEER_IBGP && peer->sort == BGP_PEER_IBGP)
    reflect = 1;
  else
    reflect = 0;

  /* IBGP reflection check. */
  if (reflect)
    {
      /* A route from a Client peer. */
      if (CHECK_FLAG (from->af_flags[afi][safi], PEER_FLAG_REFLECTOR_CLIENT))
	{
	  /* Reflect to all the Non-Client peers and also to the
             Client peers other than the originator.  Originator check
             is already done.  So there is noting to do. */
	  /* no bgp client-to-client reflection check. */
	  if (bgp_flag_check (bgp, BGP_FLAG_NO_CLIENT_TO_CLIENT))
	    if (CHECK_FLAG (peer->af_flags[afi][safi], PEER_FLAG_REFLECTOR_CLIENT))
	      return 0;
	}
      else
	{
	  /* A route from a Non-client peer. Reflect to all other
	     clients. */
	  if (! CHECK_FLAG (peer->af_flags[afi][safi], PEER_FLAG_REFLECTOR_CLIENT))
	    return 0;
	}
    }
  
  /* For modify attribute, copy it to temporary structure. */
  bgp_attr_dup (attr, riattr);
  
  /* If local-preference is not set. */
  if ((peer->sort == BGP_PEER_IBGP
       || peer->sort == BGP_PEER_CONFED)
      && (! (attr->flag & ATTR_FLAG_BIT (BGP_ATTR_LOCAL_PREF))))
    {
      attr->flag |= ATTR_FLAG_BIT (BGP_ATTR_LOCAL_PREF);
      attr->local_pref = bgp->default_local_pref;
    }

  /* Remove MED if its an EBGP peer - will get overwritten by route-maps */
  if (peer->sort == BGP_PEER_EBGP
      && attr->flag & ATTR_FLAG_BIT (BGP_ATTR_MULTI_EXIT_DISC))
    {
      if (ri->peer != bgp->peer_self && ! transparent
	  && ! CHECK_FLAG (peer->af_flags[afi][safi], PEER_FLAG_MED_UNCHANGED))
	attr->flag &= ~(ATTR_FLAG_BIT (BGP_ATTR_MULTI_EXIT_DISC));
    }

  /* next-hop-set */
  if (transparent || reflect
      || (CHECK_FLAG (peer->af_flags[afi][safi], PEER_FLAG_NEXTHOP_UNCHANGED)
	  && ((p->family == AF_INET && attr->nexthop.s_addr)
#ifdef HAVE_IPV6
	      || (p->family == AF_INET6 && 
                  ! IN6_IS_ADDR_UNSPECIFIED(&attr->extra->mp_nexthop_global))
#endif /* HAVE_IPV6 */
	      )))
    {
      /* NEXT-HOP Unchanged. */
    }
  else if (CHECK_FLAG (peer->af_flags[afi][safi], PEER_FLAG_NEXTHOP_SELF)
	   || (p->family == AF_INET && attr->nexthop.s_addr == 0)
#ifdef HAVE_IPV6
	   || (p->family == AF_INET6 && 
               IN6_IS_ADDR_UNSPECIFIED(&attr->extra->mp_nexthop_global))
#endif /* HAVE_IPV6 */
	   || (peer->sort == BGP_PEER_EBGP
	       && bgp_multiaccess_check_v4 (attr->nexthop, peer->host) == 0))
    {
      /* Set IPv4 nexthop. */
      if (p->family == AF_INET)
	{
	  if (safi == SAFI_MPLS_VPN)
	    memcpy (&attr->extra->mp_nexthop_global_in, &peer->nexthop.v4,
	            IPV4_MAX_BYTELEN);
	  else
	    memcpy (&attr->nexthop, &peer->nexthop.v4, IPV4_MAX_BYTELEN);
	}
#ifdef HAVE_IPV6
      /* Set IPv6 nexthop. */
      if (p->family == AF_INET6)
	{
	  /* IPv6 global nexthop must be included. */
	  memcpy (&attr->extra->mp_nexthop_global, &peer->nexthop.v6_global, 
		  IPV6_MAX_BYTELEN);
	  attr->extra->mp_nexthop_len = 16;
	}
#endif /* HAVE_IPV6 */
    }

#ifdef HAVE_IPV6
  if (p->family == AF_INET6)
    {
      /* Left nexthop_local unchanged if so configured. */ 
      if ( CHECK_FLAG (peer->af_flags[afi][safi], 
           PEER_FLAG_NEXTHOP_LOCAL_UNCHANGED) )
        {
          if ( IN6_IS_ADDR_LINKLOCAL (&attr->extra->mp_nexthop_local) )
            attr->extra->mp_nexthop_len=32;
          else
            attr->extra->mp_nexthop_len=16;
        }

      /* Default nexthop_local treatment for non-RS-Clients */
      else 
        {
      /* Link-local address should not be transit to different peer. */
      attr->extra->mp_nexthop_len = 16;

      /* Set link-local address for shared network peer. */
      if (peer->shared_network 
	  && ! IN6_IS_ADDR_UNSPECIFIED (&peer->nexthop.v6_local))
	{
	  memcpy (&attr->extra->mp_nexthop_local, &peer->nexthop.v6_local, 
		  IPV6_MAX_BYTELEN);
	  attr->extra->mp_nexthop_len = 32;
	}

      /* If bgpd act as BGP-4+ route-reflector, do not send link-local
	 address.*/
      if (reflect)
	attr->extra->mp_nexthop_len = 16;

      /* If BGP-4+ link-local nexthop is not link-local nexthop. */
      if (! IN6_IS_ADDR_LINKLOCAL (&peer->nexthop.v6_local))
	attr->extra->mp_nexthop_len = 16;
    }

    }
#endif /* HAVE_IPV6 */

  /* If this is EBGP peer and remove-private-AS is set.  */
  if (peer->sort == BGP_PEER_EBGP
      && peer_af_flag_check (peer, afi, safi, PEER_FLAG_REMOVE_PRIVATE_AS)
      && aspath_private_as_check (attr->aspath))
    attr->aspath = aspath_empty_get ();

  /* Route map & unsuppress-map apply. */
  if (ROUTE_MAP_OUT_NAME (filter)
      || (ri->extra && ri->extra->suppress) )
    {
      struct bgp_info info;
      struct attr dummy_attr;
      struct attr_extra dummy_extra;

      dummy_attr.extra = &dummy_extra;

      info.peer = peer;
      info.attr = attr;

      /* The route reflector is not allowed to modify the attributes
	 of the reflected IBGP routes. */
      if (from->sort == BGP_PEER_IBGP
	  && peer->sort == BGP_PEER_IBGP)
	{
	  bgp_attr_dup (&dummy_attr, attr);
	  info.attr = &dummy_attr;
	}

      SET_FLAG (peer->rmap_type, PEER_RMAP_TYPE_OUT); 

      if (ri->extra && ri->extra->suppress)
	ret = route_map_apply (UNSUPPRESS_MAP (filter), p, RMAP_BGP, &info);
      else
	ret = route_map_apply (ROUTE_MAP_OUT (filter), p, RMAP_BGP, &info);

      peer->rmap_type = 0;

      if (ret == RMAP_DENYMATCH)
	{
	  bgp_attr_flush (attr);
	  return 0;
	}
    }
  return 1;
}

static int
bgp_announce_check_rsclient (struct bgp_info *ri, struct peer *rsclient,
        struct prefix *p, struct attr *attr, afi_t afi, safi_t safi)
{
  int ret;
  char buf[SU_ADDRSTRLEN];
  struct bgp_filter *filter;
  struct bgp_info info;
  struct peer *from;
  struct attr *riattr;

  from = ri->peer;
  filter = &rsclient->filter[afi][safi];
  riattr = bgp_info_mpath_count (ri) ? bgp_info_mpath_attr (ri) : ri->attr;

  if (DISABLE_BGP_ANNOUNCE)
    return 0;

  /* Do not send back route to sender. */
  if (from == rsclient)
    return 0;

  /* Aggregate-address suppress check. */
  if (ri->extra && ri->extra->suppress)
    if (! UNSUPPRESS_MAP_NAME (filter))
      return 0;

  /* Default route check.  */
  if (CHECK_FLAG (rsclient->af_sflags[afi][safi],
          PEER_STATUS_DEFAULT_ORIGINATE))
    {
      if (p->family == AF_INET && p->u.prefix4.s_addr == INADDR_ANY)
        return 0;
#ifdef HAVE_IPV6
      else if (p->family == AF_INET6 && p->prefixlen == 0)
        return 0;
#endif /* HAVE_IPV6 */
    }

  /* If the attribute has originator-id and it is same as remote
     peer's id. */
  if (riattr->flag & ATTR_FLAG_BIT (BGP_ATTR_ORIGINATOR_ID))
    {
      if (IPV4_ADDR_SAME (&rsclient->remote_id, 
                          &riattr->extra->originator_id))
        {
         if (BGP_DEBUG (filter, FILTER))
           zlog (rsclient->log, LOG_DEBUG,
                 "%s [Update:SEND] %s/%d originator-id is same as remote router-id",
                 rsclient->host,
                 inet_ntop(p->family, &p->u.prefix, buf, SU_ADDRSTRLEN),
                 p->prefixlen);
         return 0;
       }
    }

  /* ORF prefix-list filter check */
  if (CHECK_FLAG (rsclient->af_cap[afi][safi], PEER_CAP_ORF_PREFIX_RM_ADV)
      && (CHECK_FLAG (rsclient->af_cap[afi][safi], PEER_CAP_ORF_PREFIX_SM_RCV)
         || CHECK_FLAG (rsclient->af_cap[afi][safi], PEER_CAP_ORF_PREFIX_SM_OLD_RCV)))
    if (rsclient->orf_plist[afi][safi])
      {
       if (prefix_list_apply (rsclient->orf_plist[afi][safi], p) == PREFIX_DENY)
          return 0;
      }

  /* Output filter check. */
  if (bgp_output_filter (rsclient, p, riattr, afi, safi) == FILTER_DENY)
    {
      if (BGP_DEBUG (filter, FILTER))
       zlog (rsclient->log, LOG_DEBUG,
             "%s [Update:SEND] %s/%d is filtered",
             rsclient->host,
             inet_ntop(p->family, &p->u.prefix, buf, SU_ADDRSTRLEN),
             p->prefixlen);
      return 0;
    }

#ifdef BGP_SEND_ASPATH_CHECK
  /* AS path loop check. */
  if (aspath_loop_check (riattr->aspath, rsclient->as))
    {
      if (BGP_DEBUG (filter, FILTER))
        zlog (rsclient->log, LOG_DEBUG,
             "%s [Update:SEND] suppress announcement to peer AS %u is AS path.",
             rsclient->host, rsclient->as);
      return 0;
    }
#endif /* BGP_SEND_ASPATH_CHECK */

  /* For modify attribute, copy it to temporary structure. */
  bgp_attr_dup (attr, riattr);

  /* next-hop-set */
  if ((p->family == AF_INET && attr->nexthop.s_addr == 0)
#ifdef HAVE_IPV6
          || (p->family == AF_INET6 &&
              IN6_IS_ADDR_UNSPECIFIED(&attr->extra->mp_nexthop_global))
#endif /* HAVE_IPV6 */
     )
  {
    /* Set IPv4 nexthop. */
    if (p->family == AF_INET)
      {
        if (safi == SAFI_MPLS_VPN)
          memcpy (&attr->extra->mp_nexthop_global_in, &rsclient->nexthop.v4,
                  IPV4_MAX_BYTELEN);
        else
          memcpy (&attr->nexthop, &rsclient->nexthop.v4, IPV4_MAX_BYTELEN);
      }
#ifdef HAVE_IPV6
    /* Set IPv6 nexthop. */
    if (p->family == AF_INET6)
      {
        /* IPv6 global nexthop must be included. */
        memcpy (&attr->extra->mp_nexthop_global, &rsclient->nexthop.v6_global,
                IPV6_MAX_BYTELEN);
        attr->extra->mp_nexthop_len = 16;
      }
#endif /* HAVE_IPV6 */
  }

#ifdef HAVE_IPV6
  if (p->family == AF_INET6)
    {
      struct attr_extra *attre = attr->extra;

      /* Left nexthop_local unchanged if so configured. */
      if ( CHECK_FLAG (rsclient->af_flags[afi][safi], 
           PEER_FLAG_NEXTHOP_LOCAL_UNCHANGED) )
        {
          if ( IN6_IS_ADDR_LINKLOCAL (&attre->mp_nexthop_local) )
            attre->mp_nexthop_len=32;
          else
            attre->mp_nexthop_len=16;
        }
        
      /* Default nexthop_local treatment for RS-Clients */
      else 
        { 
          /* Announcer and RS-Client are both in the same network */      
          if (rsclient->shared_network && from->shared_network &&
              (rsclient->ifindex == from->ifindex))
            {
              if ( IN6_IS_ADDR_LINKLOCAL (&attre->mp_nexthop_local) )
                attre->mp_nexthop_len=32;
              else
                attre->mp_nexthop_len=16;
            }

          /* Set link-local address for shared network peer. */
          else if (rsclient->shared_network
              && IN6_IS_ADDR_LINKLOCAL (&rsclient->nexthop.v6_local))
            {
              memcpy (&attre->mp_nexthop_local, &rsclient->nexthop.v6_local,
                      IPV6_MAX_BYTELEN);
              attre->mp_nexthop_len = 32;
            }

          else
            attre->mp_nexthop_len = 16;
        }

    }
#endif /* HAVE_IPV6 */


  /* If this is EBGP peer and remove-private-AS is set.  */
  if (rsclient->sort == BGP_PEER_EBGP
      && peer_af_flag_check (rsclient, afi, safi, PEER_FLAG_REMOVE_PRIVATE_AS)
      && aspath_private_as_check (attr->aspath))
    attr->aspath = aspath_empty_get ();

  /* Route map & unsuppress-map apply. */
  if (ROUTE_MAP_OUT_NAME (filter) || (ri->extra && ri->extra->suppress) )
    {
      info.peer = rsclient;
      info.attr = attr;

      SET_FLAG (rsclient->rmap_type, PEER_RMAP_TYPE_OUT);

      if (ri->extra && ri->extra->suppress)
        ret = route_map_apply (UNSUPPRESS_MAP (filter), p, RMAP_BGP, &info);
      else
        ret = route_map_apply (ROUTE_MAP_OUT (filter), p, RMAP_BGP, &info);

      rsclient->rmap_type = 0;

      if (ret == RMAP_DENYMATCH)
       {
         bgp_attr_flush (attr);
         return 0;
       }
    }

  return 1;
}

struct bgp_info_pair
{
  struct bgp_info *old;
  struct bgp_info *new;
};

static void
bgp_best_selection (struct bgp *bgp, struct bgp_node *rn,
		    struct bgp_maxpaths_cfg *mpath_cfg,
		    struct bgp_info_pair *result)
{
  struct bgp_info *new_select;
  struct bgp_info *old_select;
  struct bgp_info *ri;
  struct bgp_info *ri1;
  struct bgp_info *ri2;
  struct bgp_info *nextri = NULL;
  int paths_eq, do_mpath;
  struct list mp_list;

  bgp_mp_list_init (&mp_list);
  do_mpath = (mpath_cfg->maxpaths_ebgp != BGP_DEFAULT_MAXPATHS ||
	      mpath_cfg->maxpaths_ibgp != BGP_DEFAULT_MAXPATHS);

  /* bgp deterministic-med */
  new_select = NULL;
  if (bgp_flag_check (bgp, BGP_FLAG_DETERMINISTIC_MED))
    for (ri1 = rn->info; ri1; ri1 = ri1->next)
      {
	if (CHECK_FLAG (ri1->flags, BGP_INFO_DMED_CHECK))
	  continue;
	if (BGP_INFO_HOLDDOWN (ri1))
	  continue;

	new_select = ri1;
	if (do_mpath)
	  bgp_mp_list_add (&mp_list, ri1);
	old_select = CHECK_FLAG (ri1->flags, BGP_INFO_SELECTED) ? ri1 : NULL;
	if (ri1->next)
	  for (ri2 = ri1->next; ri2; ri2 = ri2->next)
	    {
	      if (CHECK_FLAG (ri2->flags, BGP_INFO_DMED_CHECK))
		continue;
	      if (BGP_INFO_HOLDDOWN (ri2))
		continue;

	      if (aspath_cmp_left (ri1->attr->aspath, ri2->attr->aspath)
		  || aspath_cmp_left_confed (ri1->attr->aspath,
					     ri2->attr->aspath))
		{
		  if (CHECK_FLAG (ri2->flags, BGP_INFO_SELECTED))
		    old_select = ri2;
		  if (bgp_info_cmp (bgp, ri2, new_select, &paths_eq))
		    {
		      bgp_info_unset_flag (rn, new_select, BGP_INFO_DMED_SELECTED);
		      new_select = ri2;
		      if (do_mpath && !paths_eq)
			{
			  bgp_mp_list_clear (&mp_list);
			  bgp_mp_list_add (&mp_list, ri2);
			}
		    }

		  if (do_mpath && paths_eq)
		    bgp_mp_list_add (&mp_list, ri2);

		  bgp_info_set_flag (rn, ri2, BGP_INFO_DMED_CHECK);
		}
	    }
	bgp_info_set_flag (rn, new_select, BGP_INFO_DMED_CHECK);
	bgp_info_set_flag (rn, new_select, BGP_INFO_DMED_SELECTED);

	bgp_info_mpath_update (rn, new_select, old_select, &mp_list, mpath_cfg);
	bgp_mp_list_clear (&mp_list);
      }

  /* Check old selected route and new selected route. */
  old_select = NULL;
  new_select = NULL;
  for (ri = rn->info; (ri != NULL) && (nextri = ri->next, 1); ri = nextri)
    {
      if (CHECK_FLAG (ri->flags, BGP_INFO_SELECTED))
	old_select = ri;

      if (BGP_INFO_HOLDDOWN (ri))
        {
          /* reap REMOVED routes, if needs be 
           * selected route must stay for a while longer though
           */
          if (CHECK_FLAG (ri->flags, BGP_INFO_REMOVED)
              && (ri != old_select))
              bgp_info_reap (rn, ri);
          
          continue;
        }

      if (bgp_flag_check (bgp, BGP_FLAG_DETERMINISTIC_MED)
          && (! CHECK_FLAG (ri->flags, BGP_INFO_DMED_SELECTED)))
	{
	  bgp_info_unset_flag (rn, ri, BGP_INFO_DMED_CHECK);
	  continue;
        }
      bgp_info_unset_flag (rn, ri, BGP_INFO_DMED_CHECK);
      bgp_info_unset_flag (rn, ri, BGP_INFO_DMED_SELECTED);

      if (bgp_info_cmp (bgp, ri, new_select, &paths_eq))
	{
	  if (do_mpath && bgp_flag_check (bgp, BGP_FLAG_DETERMINISTIC_MED))
	    bgp_mp_dmed_deselect (new_select);

	  new_select = ri;

	  if (do_mpath && !paths_eq)
	    {
	      bgp_mp_list_clear (&mp_list);
	      bgp_mp_list_add (&mp_list, ri);
	    }
	}
      else if (do_mpath && bgp_flag_check (bgp, BGP_FLAG_DETERMINISTIC_MED))
	bgp_mp_dmed_deselect (ri);

      if (do_mpath && paths_eq)
	bgp_mp_list_add (&mp_list, ri);
    }
    

  if (!bgp_flag_check (bgp, BGP_FLAG_DETERMINISTIC_MED))
    bgp_info_mpath_update (rn, new_select, old_select, &mp_list, mpath_cfg);

  bgp_info_mpath_aggregate_update (new_select, old_select);
  bgp_mp_list_clear (&mp_list);

  result->old = old_select;
  result->new = new_select;

  return;
}

static int
bgp_process_announce_selected (struct peer *peer, struct bgp_info *selected,
                               struct bgp_node *rn, afi_t afi, safi_t safi)
{
  struct prefix *p;
  struct attr attr;
  struct attr_extra extra;

  p = &rn->p;

  /* Announce route to Established peer. */
  if (peer->status != Established)
    return 0;

  /* Address family configuration check. */
  if (! peer->afc_nego[afi][safi])
    return 0;

  /* First update is deferred until ORF or ROUTE-REFRESH is received */
  if (CHECK_FLAG (peer->af_sflags[afi][safi],
      PEER_STATUS_ORF_WAIT_REFRESH))
    return 0;

  /* It's initialized in bgp_announce_[check|check_rsclient]() */
  attr.extra = &extra;

  switch (rn->table->type)
    {
      case BGP_TABLE_MAIN:
      /* Announcement to peer->conf.  If the route is filtered,
         withdraw it. */
        if (selected && bgp_announce_check (selected, peer, p, &attr, afi, safi))
          bgp_adj_out_set (rn, peer, p, &attr, afi, safi, selected);
        else
          bgp_adj_out_unset (rn, peer, p, afi, safi);
        break;
      case BGP_TABLE_RSCLIENT:
        /* Announcement to peer->conf.  If the route is filtered, 
           withdraw it. */
        if (selected && 
            bgp_announce_check_rsclient (selected, peer, p, &attr, afi, safi))
          bgp_adj_out_set (rn, peer, p, &attr, afi, safi, selected);
        else
	  bgp_adj_out_unset (rn, peer, p, afi, safi);
        break;
    }

  return 0;
}

struct bgp_process_queue 
{
  struct bgp *bgp;
  struct bgp_node *rn;
  afi_t afi;
  safi_t safi;
};

static wq_item_status
bgp_process_rsclient (struct work_queue *wq, void *data)
{
  struct bgp_process_queue *pq = data;
  struct bgp *bgp = pq->bgp;
  struct bgp_node *rn = pq->rn;
  afi_t afi = pq->afi;
  safi_t safi = pq->safi;
  struct bgp_info *new_select;
  struct bgp_info *old_select;
  struct bgp_info_pair old_and_new;
  struct listnode *node, *nnode;
  struct peer *rsclient = rn->table->owner;
  
  /* Best path selection. */
  bgp_best_selection (bgp, rn, &bgp->maxpaths[afi][safi], &old_and_new);
  new_select = old_and_new.new;
  old_select = old_and_new.old;

  if (CHECK_FLAG (rsclient->sflags, PEER_STATUS_GROUP))
    {
      if (rsclient->group)
        for (ALL_LIST_ELEMENTS (rsclient->group->peer, node, nnode, rsclient))
          {
            /* Nothing to do. */
            if (old_select && old_select == new_select)
              if (!CHECK_FLAG (old_select->flags, BGP_INFO_ATTR_CHANGED))
                continue;

            if (old_select)
              bgp_info_unset_flag (rn, old_select, BGP_INFO_SELECTED);
            if (new_select)
              {
                bgp_info_set_flag (rn, new_select, BGP_INFO_SELECTED);
                bgp_info_unset_flag (rn, new_select, BGP_INFO_ATTR_CHANGED);
		UNSET_FLAG (new_select->flags, BGP_INFO_MULTIPATH_CHG);
             }

            bgp_process_announce_selected (rsclient, new_select, rn,
                                           afi, safi);
          }
    }
  else
    {
      if (old_select)
	bgp_info_unset_flag (rn, old_select, BGP_INFO_SELECTED);
      if (new_select)
	{
	  bgp_info_set_flag (rn, new_select, BGP_INFO_SELECTED);
	  bgp_info_unset_flag (rn, new_select, BGP_INFO_ATTR_CHANGED);
	  UNSET_FLAG (new_select->flags, BGP_INFO_MULTIPATH_CHG);
	}
      bgp_process_announce_selected (rsclient, new_select, rn, afi, safi);
    }

  if (old_select && CHECK_FLAG (old_select->flags, BGP_INFO_REMOVED))
    bgp_info_reap (rn, old_select);
  
  UNSET_FLAG (rn->flags, BGP_NODE_PROCESS_SCHEDULED);
  return WQ_SUCCESS;
}

static wq_item_status
bgp_process_main (struct work_queue *wq, void *data)
{
  struct bgp_process_queue *pq = data;
  struct bgp *bgp = pq->bgp;
  struct bgp_node *rn = pq->rn;
  afi_t afi = pq->afi;
  safi_t safi = pq->safi;
  struct prefix *p = &rn->p;
  struct bgp_info *new_select;
  struct bgp_info *old_select;
  struct bgp_info_pair old_and_new;
  struct listnode *node, *nnode;
  struct peer *peer;
  
  /* Best path selection. */
  bgp_best_selection (bgp, rn, &bgp->maxpaths[afi][safi], &old_and_new);
  old_select = old_and_new.old;
  new_select = old_and_new.new;

  /* Nothing to do. */
  if (old_select && old_select == new_select)
    {
      if (! CHECK_FLAG (old_select->flags, BGP_INFO_ATTR_CHANGED))
        {
          if (CHECK_FLAG (old_select->flags, BGP_INFO_IGP_CHANGED) ||
	      CHECK_FLAG (old_select->flags, BGP_INFO_MULTIPATH_CHG))
            bgp_zebra_announce (p, old_select, bgp, safi);
          
	  UNSET_FLAG (old_select->flags, BGP_INFO_MULTIPATH_CHG);
          UNSET_FLAG (rn->flags, BGP_NODE_PROCESS_SCHEDULED);
          return WQ_SUCCESS;
        }
    }

  if (old_select)
    bgp_info_unset_flag (rn, old_select, BGP_INFO_SELECTED);
  if (new_select)
    {
      bgp_info_set_flag (rn, new_select, BGP_INFO_SELECTED);
      bgp_info_unset_flag (rn, new_select, BGP_INFO_ATTR_CHANGED);
      UNSET_FLAG (new_select->flags, BGP_INFO_MULTIPATH_CHG);
    }


  /* Check each BGP peer. */
  for (ALL_LIST_ELEMENTS (bgp->peer, node, nnode, peer))
    {
      bgp_process_announce_selected (peer, new_select, rn, afi, safi);
    }

  /* FIB update. */
  if ((safi == SAFI_UNICAST || safi == SAFI_MULTICAST) && (! bgp->name &&
      ! bgp_option_check (BGP_OPT_NO_FIB)))
    {
      if (new_select 
	  && new_select->type == ZEBRA_ROUTE_BGP 
	  && new_select->sub_type == BGP_ROUTE_NORMAL)
	bgp_zebra_announce (p, new_select, bgp, safi);
      else
	{
	  /* Withdraw the route from the kernel. */
	  if (old_select 
	      && old_select->type == ZEBRA_ROUTE_BGP
	      && old_select->sub_type == BGP_ROUTE_NORMAL)
	    bgp_zebra_withdraw (p, old_select, safi);
	}
    }
    
  /* Reap old select bgp_info, it it has been removed */
  if (old_select && CHECK_FLAG (old_select->flags, BGP_INFO_REMOVED))
    bgp_info_reap (rn, old_select);
  
  UNSET_FLAG (rn->flags, BGP_NODE_PROCESS_SCHEDULED);
  return WQ_SUCCESS;
}

static void
bgp_processq_del (struct work_queue *wq, void *data)
{
  struct bgp_process_queue *pq = data;
  struct bgp_table *table = pq->rn->table;
  
  bgp_unlock (pq->bgp);
  bgp_unlock_node (pq->rn);
  bgp_table_unlock (table);
  XFREE (MTYPE_BGP_PROCESS_QUEUE, pq);
}

static void
bgp_process_queue_init (void)
{
  bm->process_main_queue
    = work_queue_new (bm->master, "process_main_queue");
  bm->process_rsclient_queue
    = work_queue_new (bm->master, "process_rsclient_queue");
  
  if ( !(bm->process_main_queue && bm->process_rsclient_queue) )
    {
      zlog_err ("%s: Failed to allocate work queue", __func__);
      exit (1);
    }
  
  bm->process_main_queue->spec.workfunc = &bgp_process_main;
  bm->process_main_queue->spec.del_item_data = &bgp_processq_del;
  bm->process_main_queue->spec.max_retries = 0;
  bm->process_main_queue->spec.hold = 50;
  
  memcpy (bm->process_rsclient_queue, bm->process_main_queue,
          sizeof (struct work_queue *));
  bm->process_rsclient_queue->spec.workfunc = &bgp_process_rsclient;
}

void
bgp_process (struct bgp *bgp, struct bgp_node *rn, afi_t afi, safi_t safi)
{
  struct bgp_process_queue *pqnode;
  
  /* already scheduled for processing? */
  if (CHECK_FLAG (rn->flags, BGP_NODE_PROCESS_SCHEDULED))
    return;
  
  if ( (bm->process_main_queue == NULL) ||
       (bm->process_rsclient_queue == NULL) )
    bgp_process_queue_init ();
  
  pqnode = XCALLOC (MTYPE_BGP_PROCESS_QUEUE, 
                    sizeof (struct bgp_process_queue));
  if (!pqnode)
    return;

  /* all unlocked in bgp_processq_del */
  bgp_table_lock (rn->table);
  pqnode->rn = bgp_lock_node (rn);
  pqnode->bgp = bgp;
  bgp_lock (bgp);
  pqnode->afi = afi;
  pqnode->safi = safi;
  
  switch (rn->table->type)
    {
      case BGP_TABLE_MAIN:
        work_queue_add (bm->process_main_queue, pqnode);
        break;
      case BGP_TABLE_RSCLIENT:
        work_queue_add (bm->process_rsclient_queue, pqnode);
        break;
    }
  
  return;
}

static int
bgp_maximum_prefix_restart_timer (struct thread *thread)
{
  struct peer *peer;

  peer = THREAD_ARG (thread);
  peer->t_pmax_restart = NULL;

  if (BGP_DEBUG (events, EVENTS))
    zlog_debug ("%s Maximum-prefix restart timer expired, restore peering",
		peer->host);

  peer_clear (peer);

  return 0;
}

int
bgp_maximum_prefix_overflow (struct peer *peer, afi_t afi, 
                             safi_t safi, int always)
{
  if (!CHECK_FLAG (peer->af_flags[afi][safi], PEER_FLAG_MAX_PREFIX))
    return 0;

  if (peer->pcount[afi][safi] > peer->pmax[afi][safi])
    {
      if (CHECK_FLAG (peer->af_sflags[afi][safi], PEER_STATUS_PREFIX_LIMIT)
         && ! always)
       return 0;

      zlog (peer->log, LOG_INFO,
	    "%%MAXPFXEXCEED: No. of %s prefix received from %s %ld exceed, "
	    "limit %ld", afi_safi_print (afi, safi), peer->host,
	    peer->pcount[afi][safi], peer->pmax[afi][safi]);
      SET_FLAG (peer->af_sflags[afi][safi], PEER_STATUS_PREFIX_LIMIT);

      if (CHECK_FLAG (peer->af_flags[afi][safi], PEER_FLAG_MAX_PREFIX_WARNING))
       return 0;

      {
       u_int8_t ndata[7];

       if (safi == SAFI_MPLS_VPN)
         safi = SAFI_MPLS_LABELED_VPN;
         
       ndata[0] = (afi >>  8);
       ndata[1] = afi;
       ndata[2] = safi;
       ndata[3] = (peer->pmax[afi][safi] >> 24);
       ndata[4] = (peer->pmax[afi][safi] >> 16);
       ndata[5] = (peer->pmax[afi][safi] >> 8);
       ndata[6] = (peer->pmax[afi][safi]);

       SET_FLAG (peer->sflags, PEER_STATUS_PREFIX_OVERFLOW);
       bgp_notify_send_with_data (peer, BGP_NOTIFY_CEASE,
                                  BGP_NOTIFY_CEASE_MAX_PREFIX, ndata, 7);
      }

      /* restart timer start */
      if (peer->pmax_restart[afi][safi])
	{
	  peer->v_pmax_restart = peer->pmax_restart[afi][safi] * 60;

	  if (BGP_DEBUG (events, EVENTS))
	    zlog_debug ("%s Maximum-prefix restart timer started for %d secs",
			peer->host, peer->v_pmax_restart);

	  BGP_TIMER_ON (peer->t_pmax_restart, bgp_maximum_prefix_restart_timer,
			peer->v_pmax_restart);
	}

      return 1;
    }
  else
    UNSET_FLAG (peer->af_sflags[afi][safi], PEER_STATUS_PREFIX_LIMIT);

  if (peer->pcount[afi][safi] > (peer->pmax[afi][safi] * peer->pmax_threshold[afi][safi] / 100))
    {
      if (CHECK_FLAG (peer->af_sflags[afi][safi], PEER_STATUS_PREFIX_THRESHOLD)
         && ! always)
       return 0;

      zlog (peer->log, LOG_INFO,
	    "%%MAXPFX: No. of %s prefix received from %s reaches %ld, max %ld",
	    afi_safi_print (afi, safi), peer->host, peer->pcount[afi][safi],
	    peer->pmax[afi][safi]);
      SET_FLAG (peer->af_sflags[afi][safi], PEER_STATUS_PREFIX_THRESHOLD);
    }
  else
    UNSET_FLAG (peer->af_sflags[afi][safi], PEER_STATUS_PREFIX_THRESHOLD);
  return 0;
}

/* Unconditionally remove the route from the RIB, without taking
 * damping into consideration (eg, because the session went down)
 */
static void
bgp_rib_remove (struct bgp_node *rn, struct bgp_info *ri, struct peer *peer,
		afi_t afi, safi_t safi)
{
  bgp_aggregate_decrement (peer->bgp, &rn->p, ri, afi, safi);
  
  if (!CHECK_FLAG (ri->flags, BGP_INFO_HISTORY))
    bgp_info_delete (rn, ri); /* keep historical info */
    
  bgp_process (peer->bgp, rn, afi, safi);
}

static void
bgp_rib_withdraw (struct bgp_node *rn, struct bgp_info *ri, struct peer *peer,
		  afi_t afi, safi_t safi)
{
  int status = BGP_DAMP_NONE;

  /* apply dampening, if result is suppressed, we'll be retaining 
   * the bgp_info in the RIB for historical reference.
   */
  if (CHECK_FLAG (peer->bgp->af_flags[afi][safi], BGP_CONFIG_DAMPENING)
      && peer->sort == BGP_PEER_EBGP)
    if ( (status = bgp_damp_withdraw (ri, rn, afi, safi, 0)) 
         == BGP_DAMP_SUPPRESSED)
      {
        bgp_aggregate_decrement (peer->bgp, &rn->p, ri, afi, safi);
        return;
      }
    
  bgp_rib_remove (rn, ri, peer, afi, safi);
}

static void
bgp_update_rsclient (struct peer *rsclient, afi_t afi, safi_t safi,
      struct attr *attr, struct peer *peer, struct prefix *p, int type,
      int sub_type, struct prefix_rd *prd, u_char *tag)
{
  struct bgp_node *rn;
  struct bgp *bgp;
  struct attr new_attr;
  struct attr_extra new_extra;
  struct attr *attr_new;
  struct attr *attr_new2;
  struct bgp_info *ri;
  struct bgp_info *new;
  const char *reason;
  char buf[SU_ADDRSTRLEN];

  /* Do not insert announces from a rsclient into its own 'bgp_table'. */
  if (peer == rsclient)
    return;

  bgp = peer->bgp;
  rn = bgp_afi_node_get (rsclient->rib[afi][safi], afi, safi, p, prd);

  /* Check previously received route. */
  for (ri = rn->info; ri; ri = ri->next)
    if (ri->peer == peer && ri->type == type && ri->sub_type == sub_type)
      break;

  /* AS path loop check. */
  if (aspath_loop_check (attr->aspath, rsclient->as) > peer->allowas_in[afi][safi])
    {
      reason = "as-path contains our own AS;";
      goto filtered;
    }

  /* Route reflector originator ID check.  */
  if (attr->flag & ATTR_FLAG_BIT (BGP_ATTR_ORIGINATOR_ID)
      && IPV4_ADDR_SAME (&rsclient->remote_id, &attr->extra->originator_id))
    {
      reason = "originator is us;";
      goto filtered;
    }
  
  new_attr.extra = &new_extra;
  bgp_attr_dup (&new_attr, attr);

  /* Apply export policy. */
  if (CHECK_FLAG(peer->af_flags[afi][safi], PEER_FLAG_RSERVER_CLIENT) &&
        bgp_export_modifier (rsclient, peer, p, &new_attr, afi, safi) == RMAP_DENY)
    {
      reason = "export-policy;";
      goto filtered;
    }

  attr_new2 = bgp_attr_intern (&new_attr);
  
  /* Apply import policy. */
  if (bgp_import_modifier (rsclient, peer, p, &new_attr, afi, safi) == RMAP_DENY)
    {
      bgp_attr_unintern (&attr_new2);

      reason = "import-policy;";
      goto filtered;
    }

  attr_new = bgp_attr_intern (&new_attr);
  bgp_attr_unintern (&attr_new2);

  /* IPv4 unicast next hop check.  */
  if ((afi == AFI_IP) && ((safi == SAFI_UNICAST) || safi == SAFI_MULTICAST))
    {
     /* Next hop must not be 0.0.0.0 nor Class D/E address. */
      if (new_attr.nexthop.s_addr == 0
         || IPV4_CLASS_DE (ntohl (new_attr.nexthop.s_addr)))
       {
         bgp_attr_unintern (&attr_new);

         reason = "martian next-hop;";
         goto filtered;
       }
    }

  /* If the update is implicit withdraw. */
  if (ri)
    {
      ri->uptime = bgp_clock ();

      /* Same attribute comes in. */
      if (!CHECK_FLAG(ri->flags, BGP_INFO_REMOVED)
          && attrhash_cmp (ri->attr, attr_new))
        {

          bgp_info_unset_flag (rn, ri, BGP_INFO_ATTR_CHANGED);

          if (BGP_DEBUG (update, UPDATE_IN))
            zlog (peer->log, LOG_DEBUG,
                    "%s rcvd %s/%d for RS-client %s...duplicate ignored",
                    peer->host,
                    inet_ntop(p->family, &p->u.prefix, buf, SU_ADDRSTRLEN),
                    p->prefixlen, rsclient->host);

          bgp_unlock_node (rn);
          bgp_attr_unintern (&attr_new);

          return;
        }

      /* Withdraw/Announce before we fully processed the withdraw */
      if (CHECK_FLAG(ri->flags, BGP_INFO_REMOVED))
        bgp_info_restore (rn, ri);
      
      /* Received Logging. */
      if (BGP_DEBUG (update, UPDATE_IN))
        zlog (peer->log, LOG_DEBUG, "%s rcvd %s/%d for RS-client %s",
                peer->host,
                inet_ntop(p->family, &p->u.prefix, buf, SU_ADDRSTRLEN),
                p->prefixlen, rsclient->host);

      /* The attribute is changed. */
      bgp_info_set_flag (rn, ri, BGP_INFO_ATTR_CHANGED);

      /* Update to new attribute.  */
      bgp_attr_unintern (&ri->attr);
      ri->attr = attr_new;

      /* Update MPLS tag.  */
      if (safi == SAFI_MPLS_VPN)
        memcpy ((bgp_info_extra_get (ri))->tag, tag, 3);

      bgp_info_set_flag (rn, ri, BGP_INFO_VALID);

      /* Process change. */
      bgp_process (bgp, rn, afi, safi);
      bgp_unlock_node (rn);

      return;
    }

  /* Received Logging. */
  if (BGP_DEBUG (update, UPDATE_IN))
    {
      zlog (peer->log, LOG_DEBUG, "%s rcvd %s/%d for RS-client %s",
              peer->host,
              inet_ntop(p->family, &p->u.prefix, buf, SU_ADDRSTRLEN),
              p->prefixlen, rsclient->host);
    }

  /* Make new BGP info. */
  new = bgp_info_new ();
  new->type = type;
  new->sub_type = sub_type;
  new->peer = peer;
  new->attr = attr_new;
  new->uptime = bgp_clock ();

  /* Update MPLS tag. */
  if (safi == SAFI_MPLS_VPN)
    memcpy ((bgp_info_extra_get (new))->tag, tag, 3);

  bgp_info_set_flag (rn, new, BGP_INFO_VALID);

  /* Register new BGP information. */
  bgp_info_add (rn, new);
  
  /* route_node_get lock */
  bgp_unlock_node (rn);
  
  /* Process change. */
  bgp_process (bgp, rn, afi, safi);

  return;

 filtered: 

  /* This BGP update is filtered.  Log the reason then update BGP entry.  */
  if (BGP_DEBUG (update, UPDATE_IN))
        zlog (peer->log, LOG_DEBUG,
        "%s rcvd UPDATE about %s/%d -- DENIED for RS-client %s due to: %s",
        peer->host,
        inet_ntop (p->family, &p->u.prefix, buf, SU_ADDRSTRLEN),
        p->prefixlen, rsclient->host, reason);

  if (ri)
    bgp_rib_remove (rn, ri, peer, afi, safi);

  bgp_unlock_node (rn);

  return;
}

static void
bgp_withdraw_rsclient (struct peer *rsclient, afi_t afi, safi_t safi,
      struct peer *peer, struct prefix *p, int type, int sub_type,
      struct prefix_rd *prd, u_char *tag)
{
  struct bgp_node *rn;
  struct bgp_info *ri;
  char buf[SU_ADDRSTRLEN];

  if (rsclient == peer)
    return;

  rn = bgp_afi_node_get (rsclient->rib[afi][safi], afi, safi, p, prd);

  /* Lookup withdrawn route. */
  for (ri = rn->info; ri; ri = ri->next)
    if (ri->peer == peer && ri->type == type && ri->sub_type == sub_type)
      break;

  /* Withdraw specified route from routing table. */
  if (ri && ! CHECK_FLAG (ri->flags, BGP_INFO_HISTORY))
    bgp_rib_withdraw (rn, ri, peer, afi, safi);
  else if (BGP_DEBUG (update, UPDATE_IN))
    zlog (peer->log, LOG_DEBUG,
          "%s Can't find the route %s/%d", peer->host,
          inet_ntop (p->family, &p->u.prefix, buf, SU_ADDRSTRLEN),
          p->prefixlen);

  /* Unlock bgp_node_get() lock. */
  bgp_unlock_node (rn);
}

static int
bgp_update_main (struct peer *peer, struct prefix *p, struct attr *attr,
	    afi_t afi, safi_t safi, int type, int sub_type,
	    struct prefix_rd *prd, u_char *tag, int soft_reconfig)
{
  int ret;
  int aspath_loop_count = 0;
  struct bgp_node *rn;
  struct bgp *bgp;
  struct attr new_attr;
  struct attr_extra new_extra;
  struct attr *attr_new;
  struct bgp_info *ri;
  struct bgp_info *new;
  const char *reason;
  char buf[SU_ADDRSTRLEN];

  bgp = peer->bgp;
  rn = bgp_afi_node_get (bgp->rib[afi][safi], afi, safi, p, prd);
  
  /* When peer's soft reconfiguration enabled.  Record input packet in
     Adj-RIBs-In.  */
  if (! soft_reconfig && CHECK_FLAG (peer->af_flags[afi][safi], PEER_FLAG_SOFT_RECONFIG)
      && peer != bgp->peer_self)
    bgp_adj_in_set (rn, peer, attr);

  /* Check previously received route. */
  for (ri = rn->info; ri; ri = ri->next)
    if (ri->peer == peer && ri->type == type && ri->sub_type == sub_type)
      break;

  /* AS path local-as loop check. */
  if (peer->change_local_as)
    {
      if (! CHECK_FLAG (peer->flags, PEER_FLAG_LOCAL_AS_NO_PREPEND))
	aspath_loop_count = 1;

      if (aspath_loop_check (attr->aspath, peer->change_local_as) > aspath_loop_count) 
	{
	  reason = "as-path contains our own AS;";
	  goto filtered;
	}
    }

  /* AS path loop check. */
  if (aspath_loop_check (attr->aspath, bgp->as) > peer->allowas_in[afi][safi]
      || (CHECK_FLAG(bgp->config, BGP_CONFIG_CONFEDERATION)
	  && aspath_loop_check(attr->aspath, bgp->confed_id)
	  > peer->allowas_in[afi][safi]))
    {
      reason = "as-path contains our own AS;";
      goto filtered;
    }

  /* Route reflector originator ID check.  */
  if (attr->flag & ATTR_FLAG_BIT (BGP_ATTR_ORIGINATOR_ID)
      && IPV4_ADDR_SAME (&bgp->router_id, &attr->extra->originator_id))
    {
      reason = "originator is us;";
      goto filtered;
    }

  /* Route reflector cluster ID check.  */
  if (bgp_cluster_filter (peer, attr))
    {
      reason = "reflected from the same cluster;";
      goto  filtered;
    }

  /* Apply incoming filter.  */
  if (bgp_input_filter (peer, p, attr, afi, safi) == FILTER_DENY)
    {
      reason = "filter;";
      goto filtered;
    }

  new_attr.extra = &new_extra;
  bgp_attr_dup (&new_attr, attr);

  /* Apply incoming route-map. */
  if (bgp_input_modifier (peer, p, &new_attr, afi, safi) == RMAP_DENY)
    {
      reason = "route-map;";
      goto filtered;
    }

  /* IPv4 unicast next hop check.  */
  if (afi == AFI_IP && safi == SAFI_UNICAST)
    {
      /* If the peer is EBGP and nexthop is not on connected route,
	 discard it.  */
      if (peer->sort == BGP_PEER_EBGP && peer->ttl == 1
	  && ! bgp_nexthop_onlink (afi, &new_attr)
	  && ! CHECK_FLAG (peer->flags, PEER_FLAG_DISABLE_CONNECTED_CHECK))
	{
	  reason = "non-connected next-hop;";
	  goto filtered;
	}

      /* Next hop must not be 0.0.0.0 nor Class D/E address. Next hop
	 must not be my own address.  */
      if (new_attr.nexthop.s_addr == 0
	  || IPV4_CLASS_DE (ntohl (new_attr.nexthop.s_addr))
	  || bgp_nexthop_self (&new_attr))
	{
	  reason = "martian next-hop;";
	  goto filtered;
	}
    }

  attr_new = bgp_attr_intern (&new_attr);

  /* If the update is implicit withdraw. */
  if (ri)
    {
      ri->uptime = bgp_clock ();

      /* Same attribute comes in. */
      if (!CHECK_FLAG (ri->flags, BGP_INFO_REMOVED) 
          && attrhash_cmp (ri->attr, attr_new))
	{
	  bgp_info_unset_flag (rn, ri, BGP_INFO_ATTR_CHANGED);

	  if (CHECK_FLAG (bgp->af_flags[afi][safi], BGP_CONFIG_DAMPENING)
	      && peer->sort == BGP_PEER_EBGP
	      && CHECK_FLAG (ri->flags, BGP_INFO_HISTORY))
	    {
	      if (BGP_DEBUG (update, UPDATE_IN))  
		  zlog (peer->log, LOG_DEBUG, "%s rcvd %s/%d",
		  peer->host,
		  inet_ntop(p->family, &p->u.prefix, buf, SU_ADDRSTRLEN),
		  p->prefixlen);

	      if (bgp_damp_update (ri, rn, afi, safi) != BGP_DAMP_SUPPRESSED)
	        {
                  bgp_aggregate_increment (bgp, p, ri, afi, safi);
                  bgp_process (bgp, rn, afi, safi);
                }
	    }
          else /* Duplicate - odd */
	    {
	      if (BGP_DEBUG (update, UPDATE_IN))  
		zlog (peer->log, LOG_DEBUG,
		"%s rcvd %s/%d...duplicate ignored",
		peer->host,
		inet_ntop(p->family, &p->u.prefix, buf, SU_ADDRSTRLEN),
		p->prefixlen);

	      /* graceful restart STALE flag unset. */
	      if (CHECK_FLAG (ri->flags, BGP_INFO_STALE))
		{
		  bgp_info_unset_flag (rn, ri, BGP_INFO_STALE);
		  bgp_process (bgp, rn, afi, safi);
		}
	    }

	  bgp_unlock_node (rn);
	  bgp_attr_unintern (&attr_new);

	  return 0;
	}

      /* Withdraw/Announce before we fully processed the withdraw */
      if (CHECK_FLAG(ri->flags, BGP_INFO_REMOVED))
        {
          if (BGP_DEBUG (update, UPDATE_IN))
            zlog (peer->log, LOG_DEBUG, "%s rcvd %s/%d, flapped quicker than processing",
            peer->host,
            inet_ntop(p->family, &p->u.prefix, buf, SU_ADDRSTRLEN),
            p->prefixlen);
          bgp_info_restore (rn, ri);
        }

      /* Received Logging. */
      if (BGP_DEBUG (update, UPDATE_IN))  
	zlog (peer->log, LOG_DEBUG, "%s rcvd %s/%d",
	      peer->host,
	      inet_ntop(p->family, &p->u.prefix, buf, SU_ADDRSTRLEN),
	      p->prefixlen);

      /* graceful restart STALE flag unset. */
      if (CHECK_FLAG (ri->flags, BGP_INFO_STALE))
	bgp_info_unset_flag (rn, ri, BGP_INFO_STALE);

      /* The attribute is changed. */
      bgp_info_set_flag (rn, ri, BGP_INFO_ATTR_CHANGED);
      
      /* implicit withdraw, decrement aggregate and pcount here.
       * only if update is accepted, they'll increment below.
       */
      bgp_aggregate_decrement (bgp, p, ri, afi, safi);
      
      /* Update bgp route dampening information.  */
      if (CHECK_FLAG (bgp->af_flags[afi][safi], BGP_CONFIG_DAMPENING)
	  && peer->sort == BGP_PEER_EBGP)
	{
	  /* This is implicit withdraw so we should update dampening
	     information.  */
	  if (! CHECK_FLAG (ri->flags, BGP_INFO_HISTORY))
	    bgp_damp_withdraw (ri, rn, afi, safi, 1);  
	}
	
      /* Update to new attribute.  */
      bgp_attr_unintern (&ri->attr);
      ri->attr = attr_new;

      /* Update MPLS tag.  */
      if (safi == SAFI_MPLS_VPN)
        memcpy ((bgp_info_extra_get (ri))->tag, tag, 3);

      /* Update bgp route dampening information.  */
      if (CHECK_FLAG (bgp->af_flags[afi][safi], BGP_CONFIG_DAMPENING)
	  && peer->sort == BGP_PEER_EBGP)
	{
	  /* Now we do normal update dampening.  */
	  ret = bgp_damp_update (ri, rn, afi, safi);
	  if (ret == BGP_DAMP_SUPPRESSED)
	    {
	      bgp_unlock_node (rn);
	      return 0;
	    }
	}

      /* Nexthop reachability check. */
      if ((afi == AFI_IP || afi == AFI_IP6)
	  && safi == SAFI_UNICAST 
	  && (peer->sort == BGP_PEER_IBGP
              || peer->sort == BGP_PEER_CONFED
	      || (peer->sort == BGP_PEER_EBGP && peer->ttl != 1)
	      || CHECK_FLAG (peer->flags, PEER_FLAG_DISABLE_CONNECTED_CHECK)))
	{
	  if (bgp_nexthop_lookup (afi, peer, ri, NULL, NULL))
	    bgp_info_set_flag (rn, ri, BGP_INFO_VALID);
	  else
	    bgp_info_unset_flag (rn, ri, BGP_INFO_VALID);
	}
      else
        bgp_info_set_flag (rn, ri, BGP_INFO_VALID);

      /* Process change. */
      bgp_aggregate_increment (bgp, p, ri, afi, safi);

      bgp_process (bgp, rn, afi, safi);
      bgp_unlock_node (rn);

      return 0;
    }

  /* Received Logging. */
  if (BGP_DEBUG (update, UPDATE_IN))  
    {
      zlog (peer->log, LOG_DEBUG, "%s rcvd %s/%d",
	    peer->host,
	    inet_ntop(p->family, &p->u.prefix, buf, SU_ADDRSTRLEN),
	    p->prefixlen);
    }

  /* Make new BGP info. */
  new = bgp_info_new ();
  new->type = type;
  new->sub_type = sub_type;
  new->peer = peer;
  new->attr = attr_new;
  new->uptime = bgp_clock ();

  /* Update MPLS tag. */
  if (safi == SAFI_MPLS_VPN)
    memcpy ((bgp_info_extra_get (new))->tag, tag, 3);

  /* Nexthop reachability check. */
  if ((afi == AFI_IP || afi == AFI_IP6)
      && safi == SAFI_UNICAST
      && (peer->sort == BGP_PEER_IBGP
          || peer->sort == BGP_PEER_CONFED
	  || (peer->sort == BGP_PEER_EBGP && peer->ttl != 1)
	  || CHECK_FLAG (peer->flags, PEER_FLAG_DISABLE_CONNECTED_CHECK)))
    {
      if (bgp_nexthop_lookup (afi, peer, new, NULL, NULL))
	bgp_info_set_flag (rn, new, BGP_INFO_VALID);
      else
        bgp_info_unset_flag (rn, new, BGP_INFO_VALID);
    }
  else
    bgp_info_set_flag (rn, new, BGP_INFO_VALID);

  /* Increment prefix */
  bgp_aggregate_increment (bgp, p, new, afi, safi);
  
  /* Register new BGP information. */
  bgp_info_add (rn, new);
  
  /* route_node_get lock */
  bgp_unlock_node (rn);

  /* If maximum prefix count is configured and current prefix
     count exeed it. */
  if (bgp_maximum_prefix_overflow (peer, afi, safi, 0))
    return -1;

  /* Process change. */
  bgp_process (bgp, rn, afi, safi);

  return 0;

  /* This BGP update is filtered.  Log the reason then update BGP
     entry.  */
 filtered:
  if (BGP_DEBUG (update, UPDATE_IN))
    zlog (peer->log, LOG_DEBUG,
	  "%s rcvd UPDATE about %s/%d -- DENIED due to: %s",
	  peer->host,
	  inet_ntop (p->family, &p->u.prefix, buf, SU_ADDRSTRLEN),
	  p->prefixlen, reason);

  if (ri)
    bgp_rib_remove (rn, ri, peer, afi, safi);

  bgp_unlock_node (rn);

  return 0;
}

int
bgp_update (struct peer *peer, struct prefix *p, struct attr *attr,
            afi_t afi, safi_t safi, int type, int sub_type,
            struct prefix_rd *prd, u_char *tag, int soft_reconfig)
{
  struct peer *rsclient;
  struct listnode *node, *nnode;
  struct bgp *bgp;
  int ret;

  ret = bgp_update_main (peer, p, attr, afi, safi, type, sub_type, prd, tag,
          soft_reconfig);

  bgp = peer->bgp;

  /* Process the update for each RS-client. */
  for (ALL_LIST_ELEMENTS (bgp->rsclient, node, nnode, rsclient))
    {
      if (CHECK_FLAG (rsclient->af_flags[afi][safi], PEER_FLAG_RSERVER_CLIENT))
        bgp_update_rsclient (rsclient, afi, safi, attr, peer, p, type,
                sub_type, prd, tag);
    }

  return ret;
}

int
bgp_withdraw (struct peer *peer, struct prefix *p, struct attr *attr, 
	     afi_t afi, safi_t safi, int type, int sub_type, 
	     struct prefix_rd *prd, u_char *tag)
{
  struct bgp *bgp;
  char buf[SU_ADDRSTRLEN];
  struct bgp_node *rn;
  struct bgp_info *ri;
  struct peer *rsclient;
  struct listnode *node, *nnode;

  bgp = peer->bgp;

  /* Process the withdraw for each RS-client. */
  for (ALL_LIST_ELEMENTS (bgp->rsclient, node, nnode, rsclient))
    {
      if (CHECK_FLAG (rsclient->af_flags[afi][safi], PEER_FLAG_RSERVER_CLIENT))
        bgp_withdraw_rsclient (rsclient, afi, safi, peer, p, type, sub_type, prd, tag);
    }

  /* Logging. */
  if (BGP_DEBUG (update, UPDATE_IN))  
    zlog (peer->log, LOG_DEBUG, "%s rcvd UPDATE about %s/%d -- withdrawn",
	  peer->host,
	  inet_ntop(p->family, &p->u.prefix, buf, SU_ADDRSTRLEN),
	  p->prefixlen);

  /* Lookup node. */
  rn = bgp_afi_node_get (bgp->rib[afi][safi], afi, safi, p, prd);

  /* If peer is soft reconfiguration enabled.  Record input packet for
     further calculation. */
  if (CHECK_FLAG (peer->af_flags[afi][safi], PEER_FLAG_SOFT_RECONFIG)
      && peer != bgp->peer_self)
    bgp_adj_in_unset (rn, peer);

  /* Lookup withdrawn route. */
  for (ri = rn->info; ri; ri = ri->next)
    if (ri->peer == peer && ri->type == type && ri->sub_type == sub_type)
      break;

  /* Withdraw specified route from routing table. */
  if (ri && ! CHECK_FLAG (ri->flags, BGP_INFO_HISTORY))
    bgp_rib_withdraw (rn, ri, peer, afi, safi);
  else if (BGP_DEBUG (update, UPDATE_IN))
    zlog (peer->log, LOG_DEBUG, 
	  "%s Can't find the route %s/%d", peer->host,
	  inet_ntop (p->family, &p->u.prefix, buf, SU_ADDRSTRLEN),
	  p->prefixlen);

  /* Unlock bgp_node_get() lock. */
  bgp_unlock_node (rn);

  return 0;
}

void
bgp_default_originate (struct peer *peer, afi_t afi, safi_t safi, int withdraw)
{
  struct bgp *bgp;
  struct attr attr;
  struct aspath *aspath;
  struct prefix p;
  struct bgp_info binfo;
  struct peer *from;
  int ret = RMAP_DENYMATCH;
  
  if (!(afi == AFI_IP || afi == AFI_IP6))
    return;
  
  bgp = peer->bgp;
  from = bgp->peer_self;
  
  bgp_attr_default_set (&attr, BGP_ORIGIN_IGP);
  aspath = attr.aspath;
  attr.local_pref = bgp->default_local_pref;
  memcpy (&attr.nexthop, &peer->nexthop.v4, IPV4_MAX_BYTELEN);

  if (afi == AFI_IP)
    str2prefix ("0.0.0.0/0", &p);
#ifdef HAVE_IPV6
  else if (afi == AFI_IP6)
    {
      struct attr_extra *ae = attr.extra;

      str2prefix ("::/0", &p);

      /* IPv6 global nexthop must be included. */
      memcpy (&ae->mp_nexthop_global, &peer->nexthop.v6_global, 
	      IPV6_MAX_BYTELEN);
	      ae->mp_nexthop_len = 16;
 
      /* If the peer is on shared nextwork and we have link-local
	 nexthop set it. */
      if (peer->shared_network 
	  && !IN6_IS_ADDR_UNSPECIFIED (&peer->nexthop.v6_local))
	{
	  memcpy (&ae->mp_nexthop_local, &peer->nexthop.v6_local, 
		  IPV6_MAX_BYTELEN);
	  ae->mp_nexthop_len = 32;
	}
    }
#endif /* HAVE_IPV6 */

  if (peer->default_rmap[afi][safi].name)
    {
      binfo.peer = bgp->peer_self;
      binfo.attr = &attr;

      SET_FLAG (bgp->peer_self->rmap_type, PEER_RMAP_TYPE_DEFAULT);

      ret = route_map_apply (peer->default_rmap[afi][safi].map, &p,
			     RMAP_BGP, &binfo);

      bgp->peer_self->rmap_type = 0;

      if (ret == RMAP_DENYMATCH)
	{
	  bgp_attr_flush (&attr);
	  withdraw = 1;
	}
    }

  if (withdraw)
    {
      if (CHECK_FLAG (peer->af_sflags[afi][safi], PEER_STATUS_DEFAULT_ORIGINATE))
	bgp_default_withdraw_send (peer, afi, safi);
      UNSET_FLAG (peer->af_sflags[afi][safi], PEER_STATUS_DEFAULT_ORIGINATE);
    }
  else
    {
      SET_FLAG (peer->af_sflags[afi][safi], PEER_STATUS_DEFAULT_ORIGINATE);
      bgp_default_update_send (peer, &attr, afi, safi, from);
    }
  
  bgp_attr_extra_free (&attr);
  aspath_unintern (&aspath);
}

static void
bgp_announce_table (struct peer *peer, afi_t afi, safi_t safi,
                   struct bgp_table *table, int rsclient)
{
  struct bgp_node *rn;
  struct bgp_info *ri;
  struct attr attr;
  struct attr_extra extra;

  if (! table)
    table = (rsclient) ? peer->rib[afi][safi] : peer->bgp->rib[afi][safi];

  if (safi != SAFI_MPLS_VPN
      && CHECK_FLAG (peer->af_flags[afi][safi], PEER_FLAG_DEFAULT_ORIGINATE))
    bgp_default_originate (peer, afi, safi, 0);

  /* It's initialized in bgp_announce_[check|check_rsclient]() */
  attr.extra = &extra;

  for (rn = bgp_table_top (table); rn; rn = bgp_route_next(rn))
    for (ri = rn->info; ri; ri = ri->next)
      if (CHECK_FLAG (ri->flags, BGP_INFO_SELECTED) && ri->peer != peer)
	{
         if ( (rsclient) ?
              (bgp_announce_check_rsclient (ri, peer, &rn->p, &attr, afi, safi))
              : (bgp_announce_check (ri, peer, &rn->p, &attr, afi, safi)))
	    bgp_adj_out_set (rn, peer, &rn->p, &attr, afi, safi, ri);
	  else
	    bgp_adj_out_unset (rn, peer, &rn->p, afi, safi);
	}
}

void
bgp_announce_route (struct peer *peer, afi_t afi, safi_t safi)
{
  struct bgp_node *rn;
  struct bgp_table *table;

  if (peer->status != Established)
    return;

  if (! peer->afc_nego[afi][safi])
    return;

  /* First update is deferred until ORF or ROUTE-REFRESH is received */
  if (CHECK_FLAG (peer->af_sflags[afi][safi], PEER_STATUS_ORF_WAIT_REFRESH))
    return;

  if (safi != SAFI_MPLS_VPN)
    bgp_announce_table (peer, afi, safi, NULL, 0);
  else
    for (rn = bgp_table_top (peer->bgp->rib[afi][safi]); rn;
	 rn = bgp_route_next(rn))
      if ((table = (rn->info)) != NULL)
       bgp_announce_table (peer, afi, safi, table, 0);

  if (CHECK_FLAG(peer->af_flags[afi][safi], PEER_FLAG_RSERVER_CLIENT))
    bgp_announce_table (peer, afi, safi, NULL, 1);
}

void
bgp_announce_route_all (struct peer *peer)
{
  afi_t afi;
  safi_t safi;
  
  for (afi = AFI_IP; afi < AFI_MAX; afi++)
    for (safi = SAFI_UNICAST; safi < SAFI_MAX; safi++)
      bgp_announce_route (peer, afi, safi);
}

static void
bgp_soft_reconfig_table_rsclient (struct peer *rsclient, afi_t afi,
        safi_t safi, struct bgp_table *table, struct prefix_rd *prd)
{
  struct bgp_node *rn;
  struct bgp_adj_in *ain;

  if (! table)
    table = rsclient->bgp->rib[afi][safi];

  for (rn = bgp_table_top (table); rn; rn = bgp_route_next (rn))
    for (ain = rn->adj_in; ain; ain = ain->next)
      {
        struct bgp_info *ri = rn->info;

        bgp_update_rsclient (rsclient, afi, safi, ain->attr, ain->peer,
                &rn->p, ZEBRA_ROUTE_BGP, BGP_ROUTE_NORMAL, prd,
                (bgp_info_extra_get (ri))->tag);
      }
}

void
bgp_soft_reconfig_rsclient (struct peer *rsclient, afi_t afi, safi_t safi)
{
  struct bgp_table *table;
  struct bgp_node *rn;
  
  if (safi != SAFI_MPLS_VPN)
    bgp_soft_reconfig_table_rsclient (rsclient, afi, safi, NULL, NULL);

  else
    for (rn = bgp_table_top (rsclient->bgp->rib[afi][safi]); rn;
            rn = bgp_route_next (rn))
      if ((table = rn->info) != NULL)
        {
          struct prefix_rd prd;
          prd.family = AF_UNSPEC;
          prd.prefixlen = 64;
          memcpy(&prd.val, rn->p.u.val, 8);

          bgp_soft_reconfig_table_rsclient (rsclient, afi, safi, table, &prd);
        }
}

static void
bgp_soft_reconfig_table (struct peer *peer, afi_t afi, safi_t safi,
			 struct bgp_table *table, struct prefix_rd *prd)
{
  int ret;
  struct bgp_node *rn;
  struct bgp_adj_in *ain;

  if (! table)
    table = peer->bgp->rib[afi][safi];

  for (rn = bgp_table_top (table); rn; rn = bgp_route_next (rn))
    for (ain = rn->adj_in; ain; ain = ain->next)
      {
	if (ain->peer == peer)
	  {
	    struct bgp_info *ri = rn->info;

	    ret = bgp_update (peer, &rn->p, ain->attr, afi, safi,
			      ZEBRA_ROUTE_BGP, BGP_ROUTE_NORMAL,
			      prd, (bgp_info_extra_get (ri))->tag, 1);

	    if (ret < 0)
	      {
		bgp_unlock_node (rn);
		return;
	      }
	    continue;
	  }
      }
}

void
bgp_soft_reconfig_in (struct peer *peer, afi_t afi, safi_t safi)
{
  struct bgp_node *rn;
  struct bgp_table *table;

  if (peer->status != Established)
    return;

  if (safi != SAFI_MPLS_VPN)
    bgp_soft_reconfig_table (peer, afi, safi, NULL, NULL);
  else
    for (rn = bgp_table_top (peer->bgp->rib[afi][safi]); rn;
	 rn = bgp_route_next (rn))
      if ((table = rn->info) != NULL)
        {
          struct prefix_rd prd;
          prd.family = AF_UNSPEC;
          prd.prefixlen = 64;
          memcpy(&prd.val, rn->p.u.val, 8);

          bgp_soft_reconfig_table (peer, afi, safi, table, &prd);
        }
}


struct bgp_clear_node_queue
{
  struct bgp_node *rn;
  enum bgp_clear_route_type purpose;
};

static wq_item_status
bgp_clear_route_node (struct work_queue *wq, void *data)
{
  struct bgp_clear_node_queue *cnq = data;
  struct bgp_node *rn = cnq->rn;
  struct peer *peer = wq->spec.data;
  struct bgp_info *ri;
  afi_t afi = rn->table->afi;
  safi_t safi = rn->table->safi;
  
  assert (rn && peer);
  
  for (ri = rn->info; ri; ri = ri->next)
    if (ri->peer == peer || cnq->purpose == BGP_CLEAR_ROUTE_MY_RSCLIENT)
      {
        /* graceful restart STALE flag set. */
        if (CHECK_FLAG (peer->sflags, PEER_STATUS_NSF_WAIT)
            && peer->nsf[afi][safi]
            && ! CHECK_FLAG (ri->flags, BGP_INFO_STALE)
            && ! CHECK_FLAG (ri->flags, BGP_INFO_UNUSEABLE))
          bgp_info_set_flag (rn, ri, BGP_INFO_STALE);
        else
          bgp_rib_remove (rn, ri, peer, afi, safi);
        break;
      }
  return WQ_SUCCESS;
}

static void
bgp_clear_node_queue_del (struct work_queue *wq, void *data)
{
  struct bgp_clear_node_queue *cnq = data;
  struct bgp_node *rn = cnq->rn;
  struct bgp_table *table = rn->table;
  
  bgp_unlock_node (rn); 
  bgp_table_unlock (table);
  XFREE (MTYPE_BGP_CLEAR_NODE_QUEUE, cnq);
}

static void
bgp_clear_node_complete (struct work_queue *wq)
{
  struct peer *peer = wq->spec.data;
  
  /* Tickle FSM to start moving again */
  BGP_EVENT_ADD (peer, Clearing_Completed);

  peer_unlock (peer); /* bgp_clear_route */
}

static void
bgp_clear_node_queue_init (struct peer *peer)
{
  char wname[sizeof("clear xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx")];
  
  snprintf (wname, sizeof(wname), "clear %s", peer->host);
#undef CLEAR_QUEUE_NAME_LEN

  if ( (peer->clear_node_queue = work_queue_new (bm->master, wname)) == NULL)
    {
      zlog_err ("%s: Failed to allocate work queue", __func__);
      exit (1);
    }
  peer->clear_node_queue->spec.hold = 10;
  peer->clear_node_queue->spec.workfunc = &bgp_clear_route_node;
  peer->clear_node_queue->spec.del_item_data = &bgp_clear_node_queue_del;
  peer->clear_node_queue->spec.completion_func = &bgp_clear_node_complete;
  peer->clear_node_queue->spec.max_retries = 0;
  
  /* we only 'lock' this peer reference when the queue is actually active */
  peer->clear_node_queue->spec.data = peer;
}

static void
bgp_clear_route_table (struct peer *peer, afi_t afi, safi_t safi,
                       struct bgp_table *table, struct peer *rsclient,
                       enum bgp_clear_route_type purpose)
{
  struct bgp_node *rn;
  
  
  if (! table)
    table = (rsclient) ? rsclient->rib[afi][safi] : peer->bgp->rib[afi][safi];
  
  /* If still no table => afi/safi isn't configured at all or smth. */
  if (! table)
    return;
  
  for (rn = bgp_table_top (table); rn; rn = bgp_route_next (rn))
    {
      struct bgp_info *ri;
      struct bgp_adj_in *ain;
      struct bgp_adj_out *aout;
      
      if (rn->info == NULL)
        continue;

      /* XXX:TODO: This is suboptimal, every non-empty route_node is
       * queued for every clearing peer, regardless of whether it is
       * relevant to the peer at hand.
       *
       * Overview: There are 3 different indices which need to be
       * scrubbed, potentially, when a peer is removed:
       *
       * 1 peer's routes visible via the RIB (ie accepted routes)
       * 2 peer's routes visible by the (optional) peer's adj-in index
       * 3 other routes visible by the peer's adj-out index
       *
       * 3 there is no hurry in scrubbing, once the struct peer is
       * removed from bgp->peer, we could just GC such deleted peer's
       * adj-outs at our leisure.
       *
       * 1 and 2 must be 'scrubbed' in some way, at least made
       * invisible via RIB index before peer session is allowed to be
       * brought back up. So one needs to know when such a 'search' is
       * complete.
       *
       * Ideally:
       *
       * - there'd be a single global queue or a single RIB walker
       * - rather than tracking which route_nodes still need to be
       *   examined on a peer basis, we'd track which peers still
       *   aren't cleared
       *
       * Given that our per-peer prefix-counts now should be reliable,
       * this may actually be achievable. It doesn't seem to be a huge
       * problem at this time,
       */
      for (ri = rn->info; ri; ri = ri->next)
        if (ri->peer == peer || purpose == BGP_CLEAR_ROUTE_MY_RSCLIENT)
          {
            struct bgp_clear_node_queue *cnq;

            /* both unlocked in bgp_clear_node_queue_del */
            bgp_table_lock (rn->table);
            bgp_lock_node (rn);
            cnq = XCALLOC (MTYPE_BGP_CLEAR_NODE_QUEUE,
                           sizeof (struct bgp_clear_node_queue));
            cnq->rn = rn;
            cnq->purpose = purpose;
            work_queue_add (peer->clear_node_queue, cnq);
            break;
          }

      for (ain = rn->adj_in; ain; ain = ain->next)
        if (ain->peer == peer || purpose == BGP_CLEAR_ROUTE_MY_RSCLIENT)
          {
            bgp_adj_in_remove (rn, ain);
            bgp_unlock_node (rn);
            break;
          }
      for (aout = rn->adj_out; aout; aout = aout->next)
        if (aout->peer == peer || purpose == BGP_CLEAR_ROUTE_MY_RSCLIENT)
          {
            bgp_adj_out_remove (rn, aout, peer, afi, safi);
            bgp_unlock_node (rn);
            break;
          }
    }
  return;
}

void
bgp_clear_route (struct peer *peer, afi_t afi, safi_t safi,
                 enum bgp_clear_route_type purpose)
{
  struct bgp_node *rn;
  struct bgp_table *table;
  struct peer *rsclient;
  struct listnode *node, *nnode;

  if (peer->clear_node_queue == NULL)
    bgp_clear_node_queue_init (peer);
  
  /* bgp_fsm.c keeps sessions in state Clearing, not transitioning to
   * Idle until it receives a Clearing_Completed event. This protects
   * against peers which flap faster than we can we clear, which could
   * lead to:
   *
   * a) race with routes from the new session being installed before
   *    clear_route_node visits the node (to delete the route of that
   *    peer)
   * b) resource exhaustion, clear_route_node likely leads to an entry
   *    on the process_main queue. Fast-flapping could cause that queue
   *    to grow and grow.
   */
  if (!peer->clear_node_queue->thread)
    peer_lock (peer); /* bgp_clear_node_complete */

  switch (purpose)
    {
    case BGP_CLEAR_ROUTE_NORMAL:
      if (safi != SAFI_MPLS_VPN)
        bgp_clear_route_table (peer, afi, safi, NULL, NULL, purpose);
      else
        for (rn = bgp_table_top (peer->bgp->rib[afi][safi]); rn;
             rn = bgp_route_next (rn))
          if ((table = rn->info) != NULL)
            bgp_clear_route_table (peer, afi, safi, table, NULL, purpose);

      for (ALL_LIST_ELEMENTS (peer->bgp->rsclient, node, nnode, rsclient))
        if (CHECK_FLAG(rsclient->af_flags[afi][safi],
                       PEER_FLAG_RSERVER_CLIENT))
          bgp_clear_route_table (peer, afi, safi, NULL, rsclient, purpose);
      break;

    case BGP_CLEAR_ROUTE_MY_RSCLIENT:
      bgp_clear_route_table (peer, afi, safi, NULL, peer, purpose);
      break;

    default:
      assert (0);
      break;
    }
  
  /* If no routes were cleared, nothing was added to workqueue, the
   * completion function won't be run by workqueue code - call it here. 
   * XXX: Actually, this assumption doesn't hold, see
   * bgp_clear_route_table(), we queue all non-empty nodes.
   *
   * Additionally, there is a presumption in FSM that clearing is only
   * really needed if peer state is Established - peers in
   * pre-Established states shouldn't have any route-update state
   * associated with them (in or out).
   *
   * We still can get here in pre-Established though, through
   * peer_delete -> bgp_fsm_change_status, so this is a useful sanity
   * check to ensure the assumption above holds.
   *
   * At some future point, this check could be move to the top of the
   * function, and do a quick early-return when state is
   * pre-Established, avoiding above list and table scans. Once we're
   * sure it is safe..
   */
  if (!peer->clear_node_queue->thread)
    bgp_clear_node_complete (peer->clear_node_queue);
}
  
void
bgp_clear_route_all (struct peer *peer)
{
  afi_t afi;
  safi_t safi;

  for (afi = AFI_IP; afi < AFI_MAX; afi++)
    for (safi = SAFI_UNICAST; safi < SAFI_MAX; safi++)
      bgp_clear_route (peer, afi, safi, BGP_CLEAR_ROUTE_NORMAL);
}

void
bgp_clear_adj_in (struct peer *peer, afi_t afi, safi_t safi)
{
  struct bgp_table *table;
  struct bgp_node *rn;
  struct bgp_adj_in *ain;

  table = peer->bgp->rib[afi][safi];

  for (rn = bgp_table_top (table); rn; rn = bgp_route_next (rn))
    for (ain = rn->adj_in; ain ; ain = ain->next)
      if (ain->peer == peer)
	{
          bgp_adj_in_remove (rn, ain);
          bgp_unlock_node (rn);
          break;
	}
}

void
bgp_clear_stale_route (struct peer *peer, afi_t afi, safi_t safi)
{
  struct bgp_node *rn;
  struct bgp_info *ri;
  struct bgp_table *table;

  table = peer->bgp->rib[afi][safi];

  for (rn = bgp_table_top (table); rn; rn = bgp_route_next (rn))
    {
      for (ri = rn->info; ri; ri = ri->next)
	if (ri->peer == peer)
	  {
	    if (CHECK_FLAG (ri->flags, BGP_INFO_STALE))
	      bgp_rib_remove (rn, ri, peer, afi, safi);
	    break;
	  }
    }
}

/* Delete all kernel routes. */
void
bgp_cleanup_routes (void)
{
  struct bgp *bgp;
  struct listnode *node, *nnode;
  struct bgp_node *rn;
  struct bgp_table *table;
  struct bgp_info *ri;

  for (ALL_LIST_ELEMENTS (bm->bgp, node, nnode, bgp))
    {
      table = bgp->rib[AFI_IP][SAFI_UNICAST];

      for (rn = bgp_table_top (table); rn; rn = bgp_route_next (rn))
	for (ri = rn->info; ri; ri = ri->next)
	  if (CHECK_FLAG (ri->flags, BGP_INFO_SELECTED)
	      && ri->type == ZEBRA_ROUTE_BGP 
	      && ri->sub_type == BGP_ROUTE_NORMAL)
	    bgp_zebra_withdraw (&rn->p, ri,SAFI_UNICAST);

      table = bgp->rib[AFI_IP6][SAFI_UNICAST];

      for (rn = bgp_table_top (table); rn; rn = bgp_route_next (rn))
	for (ri = rn->info; ri; ri = ri->next)
	  if (CHECK_FLAG (ri->flags, BGP_INFO_SELECTED)
	      && ri->type == ZEBRA_ROUTE_BGP 
	      && ri->sub_type == BGP_ROUTE_NORMAL)
	    bgp_zebra_withdraw (&rn->p, ri,SAFI_UNICAST);
    }
}

void
bgp_reset (void)
{
  vty_reset ();
  bgp_zclient_reset ();
  access_list_reset ();
  prefix_list_reset ();
}

/* Parse NLRI stream.  Withdraw NLRI is recognized by NULL attr
   value. */
int
bgp_nlri_parse (struct peer *peer, struct attr *attr, struct bgp_nlri *packet)
{
  u_char *pnt;
  u_char *lim;
  struct prefix p;
  int psize;
  int ret;

  /* Check peer status. */
  if (peer->status != Established)
    return 0;
  
  pnt = packet->nlri;
  lim = pnt + packet->length;

  for (; pnt < lim; pnt += psize)
    {
      /* Clear prefix structure. */
      memset (&p, 0, sizeof (struct prefix));

      /* Fetch prefix length. */
      p.prefixlen = *pnt++;
      p.family = afi2family (packet->afi);
      
      /* Already checked in nlri_sanity_check().  We do double check
         here. */
      if ((packet->afi == AFI_IP && p.prefixlen > 32)
	  || (packet->afi == AFI_IP6 && p.prefixlen > 128))
	return -1;

      /* Packet size overflow check. */
      psize = PSIZE (p.prefixlen);

      /* When packet overflow occur return immediately. */
      if (pnt + psize > lim)
	return -1;

      /* Fetch prefix from NLRI packet. */
      memcpy (&p.u.prefix, pnt, psize);

      /* Check address. */
      if (packet->afi == AFI_IP && packet->safi == SAFI_UNICAST)
	{
	  if (IN_CLASSD (ntohl (p.u.prefix4.s_addr)))
	    {
	     /* 
 	      * From draft-ietf-idr-bgp4-22, Section 6.3: 
	      * If a BGP router receives an UPDATE message with a
	      * semantically incorrect NLRI field, in which a prefix is
	      * semantically incorrect (eg. an unexpected multicast IP
	      * address), it should ignore the prefix.
	      */
	      zlog (peer->log, LOG_ERR, 
		    "IPv4 unicast NLRI is multicast address %s",
		    inet_ntoa (p.u.prefix4));

	      return -1;
	    }
	}

#ifdef HAVE_IPV6
      /* Check address. */
      if (packet->afi == AFI_IP6 && packet->safi == SAFI_UNICAST)
	{
	  if (IN6_IS_ADDR_LINKLOCAL (&p.u.prefix6))
	    {
	      char buf[BUFSIZ];

	      zlog (peer->log, LOG_WARNING, 
		    "IPv6 link-local NLRI received %s ignore this NLRI",
		    inet_ntop (AF_INET6, &p.u.prefix6, buf, BUFSIZ));

	      continue;
	    }
	}
#endif /* HAVE_IPV6 */

      /* Normal process. */
      if (attr)
	ret = bgp_update (peer, &p, attr, packet->afi, packet->safi, 
			  ZEBRA_ROUTE_BGP, BGP_ROUTE_NORMAL, NULL, NULL, 0);
      else
	ret = bgp_withdraw (peer, &p, attr, packet->afi, packet->safi, 
			    ZEBRA_ROUTE_BGP, BGP_ROUTE_NORMAL, NULL, NULL);

      /* Address family configuration mismatch or maximum-prefix count
         overflow. */
      if (ret < 0)
	return -1;
    }

  /* Packet length consistency check. */
  if (pnt != lim)
    return -1;

  return 0;
}

/* NLRI encode syntax check routine. */
int
bgp_nlri_sanity_check (struct peer *peer, int afi, u_char *pnt,
		       bgp_size_t length)
{
  u_char *end;
  u_char prefixlen;
  int psize;

  end = pnt + length;

  /* RFC1771 6.3 The NLRI field in the UPDATE message is checked for
     syntactic validity.  If the field is syntactically incorrect,
     then the Error Subcode is set to Invalid Network Field. */

  while (pnt < end)
    {
      prefixlen = *pnt++;
      
      /* Prefix length check. */
      if ((afi == AFI_IP && prefixlen > 32)
	  || (afi == AFI_IP6 && prefixlen > 128))
	{
	  plog_err (peer->log, 
		    "%s [Error] Update packet error (wrong prefix length %d)",
		    peer->host, prefixlen);
	  bgp_notify_send (peer, BGP_NOTIFY_UPDATE_ERR, 
			   BGP_NOTIFY_UPDATE_INVAL_NETWORK);
	  return -1;
	}

      /* Packet size overflow check. */
      psize = PSIZE (prefixlen);

      if (pnt + psize > end)
	{
	  plog_err (peer->log, 
		    "%s [Error] Update packet error"
		    " (prefix data overflow prefix size is %d)",
		    peer->host, psize);
	  bgp_notify_send (peer, BGP_NOTIFY_UPDATE_ERR, 
			   BGP_NOTIFY_UPDATE_INVAL_NETWORK);
	  return -1;
	}

      pnt += psize;
    }

  /* Packet length consistency check. */
  if (pnt != end)
    {
      plog_err (peer->log,
		"%s [Error] Update packet error"
		" (prefix length mismatch with total length)",
		peer->host);
      bgp_notify_send (peer, BGP_NOTIFY_UPDATE_ERR, 
		       BGP_NOTIFY_UPDATE_INVAL_NETWORK);
      return -1;
    }
  return 0;
}

static struct bgp_static *
bgp_static_new (void)
{
  return XCALLOC (MTYPE_BGP_STATIC, sizeof (struct bgp_static));
}

static void
bgp_static_free (struct bgp_static *bgp_static)
{
  if (bgp_static->rmap.name)
    free (bgp_static->rmap.name);
  XFREE (MTYPE_BGP_STATIC, bgp_static);
}

static void
bgp_static_withdraw_rsclient (struct bgp *bgp, struct peer *rsclient,
        struct prefix *p, afi_t afi, safi_t safi)
{
  struct bgp_node *rn;
  struct bgp_info *ri;

  rn = bgp_afi_node_get (rsclient->rib[afi][safi], afi, safi, p, NULL);

  /* Check selected route and self inserted route. */
  for (ri = rn->info; ri; ri = ri->next)
    if (ri->peer == bgp->peer_self
       && ri->type == ZEBRA_ROUTE_BGP
       && ri->sub_type == BGP_ROUTE_STATIC)
      break;

  /* Withdraw static BGP route from routing table. */
  if (ri)
    {
      bgp_info_delete (rn, ri);
      bgp_process (bgp, rn, afi, safi);
    }

  /* Unlock bgp_node_lookup. */
  bgp_unlock_node (rn);
}

static void
bgp_static_update_rsclient (struct peer *rsclient, struct prefix *p,
                            struct bgp_static *bgp_static,
                            afi_t afi, safi_t safi)
{
  struct bgp_node *rn;
  struct bgp_info *ri;
  struct bgp_info *new;
  struct bgp_info info;
  struct attr *attr_new;
  struct attr attr;
  struct attr new_attr;
  struct attr_extra new_extra;
  struct bgp *bgp;
  int ret;
  char buf[SU_ADDRSTRLEN];

  bgp = rsclient->bgp;

  assert (bgp_static);
  if (!bgp_static)
    return;

  rn = bgp_afi_node_get (rsclient->rib[afi][safi], afi, safi, p, NULL);

  bgp_attr_default_set (&attr, BGP_ORIGIN_IGP);

  attr.nexthop = bgp_static->igpnexthop;
  attr.med = bgp_static->igpmetric;
  attr.flag |= ATTR_FLAG_BIT (BGP_ATTR_MULTI_EXIT_DISC);
  
  if (bgp_static->atomic)
    attr.flag |= ATTR_FLAG_BIT (BGP_ATTR_ATOMIC_AGGREGATE);
  
  /* Apply network route-map for export to this rsclient. */
  if (bgp_static->rmap.name)
    {
      struct attr attr_tmp = attr;
      info.peer = rsclient;
      info.attr = &attr_tmp;
      
      SET_FLAG (rsclient->rmap_type, PEER_RMAP_TYPE_EXPORT);
      SET_FLAG (rsclient->rmap_type, PEER_RMAP_TYPE_NETWORK);

      ret = route_map_apply (bgp_static->rmap.map, p, RMAP_BGP, &info);

      rsclient->rmap_type = 0;

      if (ret == RMAP_DENYMATCH)
        {
          /* Free uninterned attribute. */
          bgp_attr_flush (&attr_tmp);

          /* Unintern original. */
          aspath_unintern (&attr.aspath);
          bgp_static_withdraw_rsclient (bgp, rsclient, p, afi, safi);
          bgp_attr_extra_free (&attr);
          
          return;
        }
      attr_new = bgp_attr_intern (&attr_tmp);
    }
  else
    attr_new = bgp_attr_intern (&attr);

  new_attr.extra = &new_extra;
  bgp_attr_dup(&new_attr, attr_new);
  
  SET_FLAG (bgp->peer_self->rmap_type, PEER_RMAP_TYPE_NETWORK);

  if (bgp_import_modifier (rsclient, bgp->peer_self, p, &new_attr, afi, safi) 
        == RMAP_DENY)
    {
      /* This BGP update is filtered.  Log the reason then update BGP entry.  */
      if (BGP_DEBUG (update, UPDATE_IN))
              zlog (rsclient->log, LOG_DEBUG,
              "Static UPDATE about %s/%d -- DENIED for RS-client %s due to: import-policy",
              inet_ntop (p->family, &p->u.prefix, buf, SU_ADDRSTRLEN),
              p->prefixlen, rsclient->host);

      bgp->peer_self->rmap_type = 0;

      bgp_attr_unintern (&attr_new);
      aspath_unintern (&attr.aspath);
      bgp_attr_extra_free (&attr);

      bgp_static_withdraw_rsclient (bgp, rsclient, p, afi, safi);
      
      return;
    }

  bgp->peer_self->rmap_type = 0;

  bgp_attr_unintern (&attr_new);
  attr_new = bgp_attr_intern (&new_attr);

  for (ri = rn->info; ri; ri = ri->next)
    if (ri->peer == bgp->peer_self && ri->type == ZEBRA_ROUTE_BGP
            && ri->sub_type == BGP_ROUTE_STATIC)
      break;

  if (ri)
       {
      if (attrhash_cmp (ri->attr, attr_new) &&
	  !CHECK_FLAG(ri->flags, BGP_INFO_REMOVED))
        {
          bgp_unlock_node (rn);
          bgp_attr_unintern (&attr_new);
          aspath_unintern (&attr.aspath);
          bgp_attr_extra_free (&attr);
          return;
       }
      else
        {
          /* The attribute is changed. */
          bgp_info_set_flag (rn, ri, BGP_INFO_ATTR_CHANGED);

          /* Rewrite BGP route information. */
	  if (CHECK_FLAG(ri->flags, BGP_INFO_REMOVED))
	    bgp_info_restore(rn, ri);
          bgp_attr_unintern (&ri->attr);
          ri->attr = attr_new;
          ri->uptime = bgp_clock ();

          /* Process change. */
          bgp_process (bgp, rn, afi, safi);
          bgp_unlock_node (rn);
          aspath_unintern (&attr.aspath);
          bgp_attr_extra_free (&attr);
          return;
        }
    }
  
  /* Make new BGP info. */
  new = bgp_info_new ();
  new->type = ZEBRA_ROUTE_BGP;
  new->sub_type = BGP_ROUTE_STATIC;
  new->peer = bgp->peer_self;
  SET_FLAG (new->flags, BGP_INFO_VALID);
  new->attr = attr_new;
  new->uptime = bgp_clock ();

  /* Register new BGP information. */
  bgp_info_add (rn, new);
  
  /* route_node_get lock */
  bgp_unlock_node (rn);
  
  /* Process change. */
  bgp_process (bgp, rn, afi, safi);

  /* Unintern original. */
  aspath_unintern (&attr.aspath);
  bgp_attr_extra_free (&attr);
}

static void
bgp_static_update_main (struct bgp *bgp, struct prefix *p,
		   struct bgp_static *bgp_static, afi_t afi, safi_t safi)
{
  struct bgp_node *rn;
  struct bgp_info *ri;
  struct bgp_info *new;
  struct bgp_info info;
  struct attr attr;
  struct attr *attr_new;
  int ret;

  assert (bgp_static);
  if (!bgp_static)
    return;

  rn = bgp_afi_node_get (bgp->rib[afi][safi], afi, safi, p, NULL);

  bgp_attr_default_set (&attr, BGP_ORIGIN_IGP);
  
  attr.nexthop = bgp_static->igpnexthop;
  attr.med = bgp_static->igpmetric;
  attr.flag |= ATTR_FLAG_BIT (BGP_ATTR_MULTI_EXIT_DISC);

  if (bgp_static->atomic)
    attr.flag |= ATTR_FLAG_BIT (BGP_ATTR_ATOMIC_AGGREGATE);

  /* Apply route-map. */
  if (bgp_static->rmap.name)
    {
      struct attr attr_tmp = attr;
      info.peer = bgp->peer_self;
      info.attr = &attr_tmp;

      SET_FLAG (bgp->peer_self->rmap_type, PEER_RMAP_TYPE_NETWORK);

      ret = route_map_apply (bgp_static->rmap.map, p, RMAP_BGP, &info);

      bgp->peer_self->rmap_type = 0;

      if (ret == RMAP_DENYMATCH)
	{    
	  /* Free uninterned attribute. */
	  bgp_attr_flush (&attr_tmp);

	  /* Unintern original. */
	  aspath_unintern (&attr.aspath);
	  bgp_attr_extra_free (&attr);
	  bgp_static_withdraw (bgp, p, afi, safi);
	  return;
	}
      attr_new = bgp_attr_intern (&attr_tmp);
    }
  else
    attr_new = bgp_attr_intern (&attr);

  for (ri = rn->info; ri; ri = ri->next)
    if (ri->peer == bgp->peer_self && ri->type == ZEBRA_ROUTE_BGP
	&& ri->sub_type == BGP_ROUTE_STATIC)
      break;

  if (ri)
    {
      if (attrhash_cmp (ri->attr, attr_new) &&
	  !CHECK_FLAG(ri->flags, BGP_INFO_REMOVED))
	{
	  bgp_unlock_node (rn);
	  bgp_attr_unintern (&attr_new);
	  aspath_unintern (&attr.aspath);
	  bgp_attr_extra_free (&attr);
	  return;
	}
      else
	{
	  /* The attribute is changed. */
	  bgp_info_set_flag (rn, ri, BGP_INFO_ATTR_CHANGED);

	  /* Rewrite BGP route information. */
	  if (CHECK_FLAG(ri->flags, BGP_INFO_REMOVED))
	    bgp_info_restore(rn, ri);
	  else
	    bgp_aggregate_decrement (bgp, p, ri, afi, safi);
	  bgp_attr_unintern (&ri->attr);
	  ri->attr = attr_new;
	  ri->uptime = bgp_clock ();

	  /* Process change. */
	  bgp_aggregate_increment (bgp, p, ri, afi, safi);
	  bgp_process (bgp, rn, afi, safi);
	  bgp_unlock_node (rn);
	  aspath_unintern (&attr.aspath);
	  bgp_attr_extra_free (&attr);
	  return;
	}
    }

  /* Make new BGP info. */
  new = bgp_info_new ();
  new->type = ZEBRA_ROUTE_BGP;
  new->sub_type = BGP_ROUTE_STATIC;
  new->peer = bgp->peer_self;
  SET_FLAG (new->flags, BGP_INFO_VALID);
  new->attr = attr_new;
  new->uptime = bgp_clock ();

  /* Aggregate address increment. */
  bgp_aggregate_increment (bgp, p, new, afi, safi);
  
  /* Register new BGP information. */
  bgp_info_add (rn, new);
  
  /* route_node_get lock */
  bgp_unlock_node (rn);
  
  /* Process change. */
  bgp_process (bgp, rn, afi, safi);

  /* Unintern original. */
  aspath_unintern (&attr.aspath);
  bgp_attr_extra_free (&attr);
}

void
bgp_static_update (struct bgp *bgp, struct prefix *p,
                  struct bgp_static *bgp_static, afi_t afi, safi_t safi)
{
  struct peer *rsclient;
  struct listnode *node, *nnode;

  bgp_static_update_main (bgp, p, bgp_static, afi, safi);

  for (ALL_LIST_ELEMENTS (bgp->rsclient, node, nnode, rsclient))
    {
      if (CHECK_FLAG (rsclient->af_flags[afi][safi], PEER_FLAG_RSERVER_CLIENT))
        bgp_static_update_rsclient (rsclient, p, bgp_static, afi, safi);
    }
}

static void
bgp_static_update_vpnv4 (struct bgp *bgp, struct prefix *p, afi_t afi,
			 safi_t safi, struct prefix_rd *prd, u_char *tag)
{
  struct bgp_node *rn;
  struct bgp_info *new;
  
  rn = bgp_afi_node_get (bgp->rib[afi][safi], afi, safi, p, prd);

  /* Make new BGP info. */
  new = bgp_info_new ();
  new->type = ZEBRA_ROUTE_BGP;
  new->sub_type = BGP_ROUTE_STATIC;
  new->peer = bgp->peer_self;
  new->attr = bgp_attr_default_intern (BGP_ORIGIN_IGP);
  SET_FLAG (new->flags, BGP_INFO_VALID);
  new->uptime = bgp_clock ();
  new->extra = bgp_info_extra_new();
  memcpy (new->extra->tag, tag, 3);

  /* Aggregate address increment. */
  bgp_aggregate_increment (bgp, p, new, afi, safi);
  
  /* Register new BGP information. */
  bgp_info_add (rn, new);

  /* route_node_get lock */
  bgp_unlock_node (rn);
  
  /* Process change. */
  bgp_process (bgp, rn, afi, safi);
}

void
bgp_static_withdraw (struct bgp *bgp, struct prefix *p, afi_t afi,
		     safi_t safi)
{
  struct bgp_node *rn;
  struct bgp_info *ri;

  rn = bgp_afi_node_get (bgp->rib[afi][safi], afi, safi, p, NULL);

  /* Check selected route and self inserted route. */
  for (ri = rn->info; ri; ri = ri->next)
    if (ri->peer == bgp->peer_self 
	&& ri->type == ZEBRA_ROUTE_BGP
	&& ri->sub_type == BGP_ROUTE_STATIC)
      break;

  /* Withdraw static BGP route from routing table. */
  if (ri)
    {
      bgp_aggregate_decrement (bgp, p, ri, afi, safi);
      bgp_info_delete (rn, ri);
      bgp_process (bgp, rn, afi, safi);
    }

  /* Unlock bgp_node_lookup. */
  bgp_unlock_node (rn);
}

void
bgp_check_local_routes_rsclient (struct peer *rsclient, afi_t afi, safi_t safi)
{
  struct bgp_static *bgp_static;
  struct bgp *bgp;
  struct bgp_node *rn;
  struct prefix *p;

  bgp = rsclient->bgp;

  for (rn = bgp_table_top (bgp->route[afi][safi]); rn; rn = bgp_route_next (rn))
    if ((bgp_static = rn->info) != NULL)
      {
        p = &rn->p;

        bgp_static_update_rsclient (rsclient, p, bgp_static,
                afi, safi);
      }
}

static void
bgp_static_withdraw_vpnv4 (struct bgp *bgp, struct prefix *p, afi_t afi,
			   safi_t safi, struct prefix_rd *prd, u_char *tag)
{
  struct bgp_node *rn;
  struct bgp_info *ri;

  rn = bgp_afi_node_get (bgp->rib[afi][safi], afi, safi, p, prd);

  /* Check selected route and self inserted route. */
  for (ri = rn->info; ri; ri = ri->next)
    if (ri->peer == bgp->peer_self 
	&& ri->type == ZEBRA_ROUTE_BGP
	&& ri->sub_type == BGP_ROUTE_STATIC)
      break;

  /* Withdraw static BGP route from routing table. */
  if (ri)
    {
      bgp_aggregate_decrement (bgp, p, ri, afi, safi);
      bgp_info_delete (rn, ri);
      bgp_process (bgp, rn, afi, safi);
    }

  /* Unlock bgp_node_lookup. */
  bgp_unlock_node (rn);
}

/* Configure static BGP network.  When user don't run zebra, static
   route should be installed as valid.  */
static int
bgp_static_set (struct vty *vty, struct bgp *bgp, const char *ip_str, 
                afi_t afi, safi_t safi, const char *rmap, int backdoor)
{
  int ret;
  struct prefix p;
  struct bgp_static *bgp_static;
  struct bgp_node *rn;
  u_char need_update = 0;

  /* Convert IP prefix string to struct prefix. */
  ret = str2prefix (ip_str, &p);
  if (! ret)
    {
      vty_out (vty, "%% Malformed prefix%s", VTY_NEWLINE);
      return CMD_WARNING;
    }
#ifdef HAVE_IPV6
  if (afi == AFI_IP6 && IN6_IS_ADDR_LINKLOCAL (&p.u.prefix6))
    {
      vty_out (vty, "%% Malformed prefix (link-local address)%s",
	       VTY_NEWLINE);
      return CMD_WARNING;
    }
#endif /* HAVE_IPV6 */

  apply_mask (&p);

  /* Set BGP static route configuration. */
  rn = bgp_node_get (bgp->route[afi][safi], &p);

  if (rn->info)
    {
      /* Configuration change. */
      bgp_static = rn->info;

      /* Check previous routes are installed into BGP.  */
      if (bgp_static->valid && bgp_static->backdoor != backdoor)
        need_update = 1;
      
      bgp_static->backdoor = backdoor;
      
      if (rmap)
	{
	  if (bgp_static->rmap.name)
	    free (bgp_static->rmap.name);
	  bgp_static->rmap.name = strdup (rmap);
	  bgp_static->rmap.map = route_map_lookup_by_name (rmap);
	}
      else
	{
	  if (bgp_static->rmap.name)
	    free (bgp_static->rmap.name);
	  bgp_static->rmap.name = NULL;
	  bgp_static->rmap.map = NULL;
	  bgp_static->valid = 0;
	}
      bgp_unlock_node (rn);
    }
  else
    {
      /* New configuration. */
      bgp_static = bgp_static_new ();
      bgp_static->backdoor = backdoor;
      bgp_static->valid = 0;
      bgp_static->igpmetric = 0;
      bgp_static->igpnexthop.s_addr = 0;
      
      if (rmap)
	{
	  if (bgp_static->rmap.name)
	    free (bgp_static->rmap.name);
	  bgp_static->rmap.name = strdup (rmap);
	  bgp_static->rmap.map = route_map_lookup_by_name (rmap);
	}
      rn->info = bgp_static;
    }

  /* If BGP scan is not enabled, we should install this route here.  */
  if (! bgp_flag_check (bgp, BGP_FLAG_IMPORT_CHECK))
    {
      bgp_static->valid = 1;

      if (need_update)
	bgp_static_withdraw (bgp, &p, afi, safi);

      if (! bgp_static->backdoor)
	bgp_static_update (bgp, &p, bgp_static, afi, safi);
    }

  return CMD_SUCCESS;
}

/* Configure static BGP network. */
static int
bgp_static_unset (struct vty *vty, struct bgp *bgp, const char *ip_str,
		  afi_t afi, safi_t safi)
{
  int ret;
  struct prefix p;
  struct bgp_static *bgp_static;
  struct bgp_node *rn;

  /* Convert IP prefix string to struct prefix. */
  ret = str2prefix (ip_str, &p);
  if (! ret)
    {
      vty_out (vty, "%% Malformed prefix%s", VTY_NEWLINE);
      return CMD_WARNING;
    }
#ifdef HAVE_IPV6
  if (afi == AFI_IP6 && IN6_IS_ADDR_LINKLOCAL (&p.u.prefix6))
    {
      vty_out (vty, "%% Malformed prefix (link-local address)%s",
	       VTY_NEWLINE);
      return CMD_WARNING;
    }
#endif /* HAVE_IPV6 */

  apply_mask (&p);

  rn = bgp_node_lookup (bgp->route[afi][safi], &p);
  if (! rn)
    {
      vty_out (vty, "%% Can't find specified static route configuration.%s",
	       VTY_NEWLINE);
      return CMD_WARNING;
    }

  bgp_static = rn->info;
  
  /* Update BGP RIB. */
  if (! bgp_static->backdoor)
    bgp_static_withdraw (bgp, &p, afi, safi);

  /* Clear configuration. */
  bgp_static_free (bgp_static);
  rn->info = NULL;
  bgp_unlock_node (rn);
  bgp_unlock_node (rn);

  return CMD_SUCCESS;
}

/* Called from bgp_delete().  Delete all static routes from the BGP
   instance. */
void
bgp_static_delete (struct bgp *bgp)
{
  afi_t afi;
  safi_t safi;
  struct bgp_node *rn;
  struct bgp_node *rm;
  struct bgp_table *table;
  struct bgp_static *bgp_static;

  for (afi = AFI_IP; afi < AFI_MAX; afi++)
    for (safi = SAFI_UNICAST; safi < SAFI_MAX; safi++)
      for (rn = bgp_table_top (bgp->route[afi][safi]); rn; rn = bgp_route_next (rn))
	if (rn->info != NULL)
	  {      
	    if (safi == SAFI_MPLS_VPN)
	      {
		table = rn->info;

		for (rm = bgp_table_top (table); rm; rm = bgp_route_next (rm))
		  {
		    bgp_static = rn->info;
		    bgp_static_withdraw_vpnv4 (bgp, &rm->p,
					       AFI_IP, SAFI_MPLS_VPN,
					       (struct prefix_rd *)&rn->p,
					       bgp_static->tag);
		    bgp_static_free (bgp_static);
		    rn->info = NULL;
		    bgp_unlock_node (rn);
		  }
	      }
	    else
	      {
		bgp_static = rn->info;
		bgp_static_withdraw (bgp, &rn->p, afi, safi);
		bgp_static_free (bgp_static);
		rn->info = NULL;
		bgp_unlock_node (rn);
	      }
	  }
}

int
bgp_static_set_vpnv4 (struct vty *vty, const char *ip_str, const char *rd_str,
		      const char *tag_str)
{
  int ret;
  struct prefix p;
  struct prefix_rd prd;
  struct bgp *bgp;
  struct bgp_node *prn;
  struct bgp_node *rn;
  struct bgp_table *table;
  struct bgp_static *bgp_static;
  u_char tag[3];

  bgp = vty->index;

  ret = str2prefix (ip_str, &p);
  if (! ret)
    {
      vty_out (vty, "%% Malformed prefix%s", VTY_NEWLINE);
      return CMD_WARNING;
    }
  apply_mask (&p);

  ret = str2prefix_rd (rd_str, &prd);
  if (! ret)
    {
      vty_out (vty, "%% Malformed rd%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  ret = str2tag (tag_str, tag);
  if (! ret)
    {
      vty_out (vty, "%% Malformed tag%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  prn = bgp_node_get (bgp->route[AFI_IP][SAFI_MPLS_VPN],
			(struct prefix *)&prd);
  if (prn->info == NULL)
    prn->info = bgp_table_init (AFI_IP, SAFI_MPLS_VPN);
  else
    bgp_unlock_node (prn);
  table = prn->info;

  rn = bgp_node_get (table, &p);

  if (rn->info)
    {
      vty_out (vty, "%% Same network configuration exists%s", VTY_NEWLINE);
      bgp_unlock_node (rn);
    }
  else
    {
      /* New configuration. */
      bgp_static = bgp_static_new ();
      bgp_static->valid = 1;
      memcpy (bgp_static->tag, tag, 3);
      rn->info = bgp_static;

      bgp_static_update_vpnv4 (bgp, &p, AFI_IP, SAFI_MPLS_VPN, &prd, tag);
    }

  return CMD_SUCCESS;
}

/* Configure static BGP network. */
int
bgp_static_unset_vpnv4 (struct vty *vty, const char *ip_str, 
                        const char *rd_str, const char *tag_str)
{
  int ret;
  struct bgp *bgp;
  struct prefix p;
  struct prefix_rd prd;
  struct bgp_node *prn;
  struct bgp_node *rn;
  struct bgp_table *table;
  struct bgp_static *bgp_static;
  u_char tag[3];

  bgp = vty->index;

  /* Convert IP prefix string to struct prefix. */
  ret = str2prefix (ip_str, &p);
  if (! ret)
    {
      vty_out (vty, "%% Malformed prefix%s", VTY_NEWLINE);
      return CMD_WARNING;
    }
  apply_mask (&p);

  ret = str2prefix_rd (rd_str, &prd);
  if (! ret)
    {
      vty_out (vty, "%% Malformed rd%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  ret = str2tag (tag_str, tag);
  if (! ret)
    {
      vty_out (vty, "%% Malformed tag%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  prn = bgp_node_get (bgp->route[AFI_IP][SAFI_MPLS_VPN],
			(struct prefix *)&prd);
  if (prn->info == NULL)
    prn->info = bgp_table_init (AFI_IP, SAFI_MPLS_VPN);
  else
    bgp_unlock_node (prn);
  table = prn->info;

  rn = bgp_node_lookup (table, &p);

  if (rn)
    {
      bgp_static_withdraw_vpnv4 (bgp, &p, AFI_IP, SAFI_MPLS_VPN, &prd, tag);

      bgp_static = rn->info;
      bgp_static_free (bgp_static);
      rn->info = NULL;
      bgp_unlock_node (rn);
      bgp_unlock_node (rn);
    }
  else
    vty_out (vty, "%% Can't find the route%s", VTY_NEWLINE);

  return CMD_SUCCESS;
}

DEFUN (bgp_network,
       bgp_network_cmd,
       "network A.B.C.D/M",
       "Specify a network to announce via BGP\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n")
{
  return bgp_static_set (vty, vty->index, argv[0],
			 AFI_IP, bgp_node_safi (vty), NULL, 0);
}

DEFUN (bgp_network_route_map,
       bgp_network_route_map_cmd,
       "network A.B.C.D/M route-map WORD",
       "Specify a network to announce via BGP\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Route-map to modify the attributes\n"
       "Name of the route map\n")
{
  return bgp_static_set (vty, vty->index, argv[0],
			 AFI_IP, bgp_node_safi (vty), argv[1], 0);
}

DEFUN (bgp_network_backdoor,
       bgp_network_backdoor_cmd,
       "network A.B.C.D/M backdoor",
       "Specify a network to announce via BGP\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Specify a BGP backdoor route\n")
{
  return bgp_static_set (vty, vty->index, argv[0], AFI_IP, SAFI_UNICAST,
                         NULL, 1);
}

DEFUN (bgp_network_mask,
       bgp_network_mask_cmd,
       "network A.B.C.D mask A.B.C.D",
       "Specify a network to announce via BGP\n"
       "Network number\n"
       "Network mask\n"
       "Network mask\n")
{
  int ret;
  char prefix_str[BUFSIZ];
  
  ret = netmask_str2prefix_str (argv[0], argv[1], prefix_str);
  if (! ret)
    {
      vty_out (vty, "%% Inconsistent address and mask%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  return bgp_static_set (vty, vty->index, prefix_str,
			 AFI_IP, bgp_node_safi (vty), NULL, 0);
}

DEFUN (bgp_network_mask_route_map,
       bgp_network_mask_route_map_cmd,
       "network A.B.C.D mask A.B.C.D route-map WORD",
       "Specify a network to announce via BGP\n"
       "Network number\n"
       "Network mask\n"
       "Network mask\n"
       "Route-map to modify the attributes\n"
       "Name of the route map\n")
{
  int ret;
  char prefix_str[BUFSIZ];
  
  ret = netmask_str2prefix_str (argv[0], argv[1], prefix_str);
  if (! ret)
    {
      vty_out (vty, "%% Inconsistent address and mask%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  return bgp_static_set (vty, vty->index, prefix_str,
			 AFI_IP, bgp_node_safi (vty), argv[2], 0);
}

DEFUN (bgp_network_mask_backdoor,
       bgp_network_mask_backdoor_cmd,
       "network A.B.C.D mask A.B.C.D backdoor",
       "Specify a network to announce via BGP\n"
       "Network number\n"
       "Network mask\n"
       "Network mask\n"
       "Specify a BGP backdoor route\n")
{
  int ret;
  char prefix_str[BUFSIZ];
  
  ret = netmask_str2prefix_str (argv[0], argv[1], prefix_str);
  if (! ret)
    {
      vty_out (vty, "%% Inconsistent address and mask%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  return bgp_static_set (vty, vty->index, prefix_str, AFI_IP, SAFI_UNICAST,
                         NULL, 1);
}

DEFUN (bgp_network_mask_natural,
       bgp_network_mask_natural_cmd,
       "network A.B.C.D",
       "Specify a network to announce via BGP\n"
       "Network number\n")
{
  int ret;
  char prefix_str[BUFSIZ];

  ret = netmask_str2prefix_str (argv[0], NULL, prefix_str);
  if (! ret)
    {
      vty_out (vty, "%% Inconsistent address and mask%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  return bgp_static_set (vty, vty->index, prefix_str,
			 AFI_IP, bgp_node_safi (vty), NULL, 0);
}

DEFUN (bgp_network_mask_natural_route_map,
       bgp_network_mask_natural_route_map_cmd,
       "network A.B.C.D route-map WORD",
       "Specify a network to announce via BGP\n"
       "Network number\n"
       "Route-map to modify the attributes\n"
       "Name of the route map\n")
{
  int ret;
  char prefix_str[BUFSIZ];

  ret = netmask_str2prefix_str (argv[0], NULL, prefix_str);
  if (! ret)
    {
      vty_out (vty, "%% Inconsistent address and mask%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  return bgp_static_set (vty, vty->index, prefix_str,
			 AFI_IP, bgp_node_safi (vty), argv[1], 0);
}

DEFUN (bgp_network_mask_natural_backdoor,
       bgp_network_mask_natural_backdoor_cmd,
       "network A.B.C.D backdoor",
       "Specify a network to announce via BGP\n"
       "Network number\n"
       "Specify a BGP backdoor route\n")
{
  int ret;
  char prefix_str[BUFSIZ];

  ret = netmask_str2prefix_str (argv[0], NULL, prefix_str);
  if (! ret)
    {
      vty_out (vty, "%% Inconsistent address and mask%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  return bgp_static_set (vty, vty->index, prefix_str, AFI_IP, SAFI_UNICAST,
                         NULL, 1);
}

DEFUN (no_bgp_network,
       no_bgp_network_cmd,
       "no network A.B.C.D/M",
       NO_STR
       "Specify a network to announce via BGP\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n")
{
  return bgp_static_unset (vty, vty->index, argv[0], AFI_IP, 
			   bgp_node_safi (vty));
}

ALIAS (no_bgp_network,
       no_bgp_network_route_map_cmd,
       "no network A.B.C.D/M route-map WORD",
       NO_STR
       "Specify a network to announce via BGP\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Route-map to modify the attributes\n"
       "Name of the route map\n")

ALIAS (no_bgp_network,
       no_bgp_network_backdoor_cmd,
       "no network A.B.C.D/M backdoor",
       NO_STR
       "Specify a network to announce via BGP\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Specify a BGP backdoor route\n")

DEFUN (no_bgp_network_mask,
       no_bgp_network_mask_cmd,
       "no network A.B.C.D mask A.B.C.D",
       NO_STR
       "Specify a network to announce via BGP\n"
       "Network number\n"
       "Network mask\n"
       "Network mask\n")
{
  int ret;
  char prefix_str[BUFSIZ];

  ret = netmask_str2prefix_str (argv[0], argv[1], prefix_str);
  if (! ret)
    {
      vty_out (vty, "%% Inconsistent address and mask%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  return bgp_static_unset (vty, vty->index, prefix_str, AFI_IP, 
			   bgp_node_safi (vty));
}

ALIAS (no_bgp_network_mask,
       no_bgp_network_mask_route_map_cmd,
       "no network A.B.C.D mask A.B.C.D route-map WORD",
       NO_STR
       "Specify a network to announce via BGP\n"
       "Network number\n"
       "Network mask\n"
       "Network mask\n"
       "Route-map to modify the attributes\n"
       "Name of the route map\n")

ALIAS (no_bgp_network_mask,
       no_bgp_network_mask_backdoor_cmd,
       "no network A.B.C.D mask A.B.C.D backdoor",
       NO_STR
       "Specify a network to announce via BGP\n"
       "Network number\n"
       "Network mask\n"
       "Network mask\n"
       "Specify a BGP backdoor route\n")

DEFUN (no_bgp_network_mask_natural,
       no_bgp_network_mask_natural_cmd,
       "no network A.B.C.D",
       NO_STR
       "Specify a network to announce via BGP\n"
       "Network number\n")
{
  int ret;
  char prefix_str[BUFSIZ];

  ret = netmask_str2prefix_str (argv[0], NULL, prefix_str);
  if (! ret)
    {
      vty_out (vty, "%% Inconsistent address and mask%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  return bgp_static_unset (vty, vty->index, prefix_str, AFI_IP, 
			   bgp_node_safi (vty));
}

ALIAS (no_bgp_network_mask_natural,
       no_bgp_network_mask_natural_route_map_cmd,
       "no network A.B.C.D route-map WORD",
       NO_STR
       "Specify a network to announce via BGP\n"
       "Network number\n"
       "Route-map to modify the attributes\n"
       "Name of the route map\n")

ALIAS (no_bgp_network_mask_natural,
       no_bgp_network_mask_natural_backdoor_cmd,
       "no network A.B.C.D backdoor",
       NO_STR
       "Specify a network to announce via BGP\n"
       "Network number\n"
       "Specify a BGP backdoor route\n")

#ifdef HAVE_IPV6
DEFUN (ipv6_bgp_network,
       ipv6_bgp_network_cmd,
       "network X:X::X:X/M",
       "Specify a network to announce via BGP\n"
       "IPv6 prefix <network>/<length>\n")
{
  return bgp_static_set (vty, vty->index, argv[0], AFI_IP6, bgp_node_safi(vty),
                         NULL, 0);
}

DEFUN (ipv6_bgp_network_route_map,
       ipv6_bgp_network_route_map_cmd,
       "network X:X::X:X/M route-map WORD",
       "Specify a network to announce via BGP\n"
       "IPv6 prefix <network>/<length>\n"
       "Route-map to modify the attributes\n"
       "Name of the route map\n")
{
  return bgp_static_set (vty, vty->index, argv[0], AFI_IP6,
			 bgp_node_safi (vty), argv[1], 0);
}

DEFUN (no_ipv6_bgp_network,
       no_ipv6_bgp_network_cmd,
       "no network X:X::X:X/M",
       NO_STR
       "Specify a network to announce via BGP\n"
       "IPv6 prefix <network>/<length>\n")
{
  return bgp_static_unset (vty, vty->index, argv[0], AFI_IP6, bgp_node_safi(vty));
}

ALIAS (no_ipv6_bgp_network,
       no_ipv6_bgp_network_route_map_cmd,
       "no network X:X::X:X/M route-map WORD",
       NO_STR
       "Specify a network to announce via BGP\n"
       "IPv6 prefix <network>/<length>\n"
       "Route-map to modify the attributes\n"
       "Name of the route map\n")

ALIAS (ipv6_bgp_network,
       old_ipv6_bgp_network_cmd,
       "ipv6 bgp network X:X::X:X/M",
       IPV6_STR
       BGP_STR
       "Specify a network to announce via BGP\n"
       "IPv6 prefix <network>/<length>, e.g., 3ffe::/16\n")

ALIAS (no_ipv6_bgp_network,
       old_no_ipv6_bgp_network_cmd,
       "no ipv6 bgp network X:X::X:X/M",
       NO_STR
       IPV6_STR
       BGP_STR
       "Specify a network to announce via BGP\n"
       "IPv6 prefix <network>/<length>, e.g., 3ffe::/16\n")
#endif /* HAVE_IPV6 */

/* stubs for removed AS-Pathlimit commands, kept for config compatibility */
ALIAS_DEPRECATED (bgp_network,
       bgp_network_ttl_cmd,
       "network A.B.C.D/M pathlimit <0-255>",
       "Specify a network to announce via BGP\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "AS-Path hopcount limit attribute\n"
       "AS-Pathlimit TTL, in number of AS-Path hops\n")
ALIAS_DEPRECATED (bgp_network_backdoor,
       bgp_network_backdoor_ttl_cmd,
       "network A.B.C.D/M backdoor pathlimit <0-255>",
       "Specify a network to announce via BGP\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Specify a BGP backdoor route\n"
       "AS-Path hopcount limit attribute\n"
       "AS-Pathlimit TTL, in number of AS-Path hops\n")
ALIAS_DEPRECATED (bgp_network_mask,
       bgp_network_mask_ttl_cmd,
       "network A.B.C.D mask A.B.C.D pathlimit <0-255>",
       "Specify a network to announce via BGP\n"
       "Network number\n"
       "Network mask\n"
       "Network mask\n"
       "AS-Path hopcount limit attribute\n"
       "AS-Pathlimit TTL, in number of AS-Path hops\n")
ALIAS_DEPRECATED (bgp_network_mask_backdoor,
       bgp_network_mask_backdoor_ttl_cmd,
       "network A.B.C.D mask A.B.C.D backdoor pathlimit <0-255>",
       "Specify a network to announce via BGP\n"
       "Network number\n"
       "Network mask\n"
       "Network mask\n"
       "Specify a BGP backdoor route\n"
       "AS-Path hopcount limit attribute\n"
       "AS-Pathlimit TTL, in number of AS-Path hops\n")
ALIAS_DEPRECATED (bgp_network_mask_natural,
       bgp_network_mask_natural_ttl_cmd,
       "network A.B.C.D pathlimit <0-255>",
       "Specify a network to announce via BGP\n"
       "Network number\n"
       "AS-Path hopcount limit attribute\n"
       "AS-Pathlimit TTL, in number of AS-Path hops\n")
ALIAS_DEPRECATED (bgp_network_mask_natural_backdoor,
       bgp_network_mask_natural_backdoor_ttl_cmd,
       "network A.B.C.D backdoor pathlimit (1-255>",
       "Specify a network to announce via BGP\n"
       "Network number\n"
       "Specify a BGP backdoor route\n"
       "AS-Path hopcount limit attribute\n"
       "AS-Pathlimit TTL, in number of AS-Path hops\n")
ALIAS_DEPRECATED (no_bgp_network,
       no_bgp_network_ttl_cmd,
       "no network A.B.C.D/M pathlimit <0-255>",
       NO_STR
       "Specify a network to announce via BGP\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "AS-Path hopcount limit attribute\n"
       "AS-Pathlimit TTL, in number of AS-Path hops\n")
ALIAS_DEPRECATED (no_bgp_network,
       no_bgp_network_backdoor_ttl_cmd,
       "no network A.B.C.D/M backdoor pathlimit <0-255>",
       NO_STR
       "Specify a network to announce via BGP\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Specify a BGP backdoor route\n"
       "AS-Path hopcount limit attribute\n"
       "AS-Pathlimit TTL, in number of AS-Path hops\n")
ALIAS_DEPRECATED (no_bgp_network,
       no_bgp_network_mask_ttl_cmd,
       "no network A.B.C.D mask A.B.C.D pathlimit <0-255>",
       NO_STR
       "Specify a network to announce via BGP\n"
       "Network number\n"
       "Network mask\n"
       "Network mask\n"
       "AS-Path hopcount limit attribute\n"
       "AS-Pathlimit TTL, in number of AS-Path hops\n")
ALIAS_DEPRECATED (no_bgp_network_mask,
       no_bgp_network_mask_backdoor_ttl_cmd,
       "no network A.B.C.D mask A.B.C.D  backdoor pathlimit <0-255>",
       NO_STR
       "Specify a network to announce via BGP\n"
       "Network number\n"
       "Network mask\n"
       "Network mask\n"
       "Specify a BGP backdoor route\n"
       "AS-Path hopcount limit attribute\n"
       "AS-Pathlimit TTL, in number of AS-Path hops\n")
ALIAS_DEPRECATED (no_bgp_network_mask_natural,
       no_bgp_network_mask_natural_ttl_cmd,
       "no network A.B.C.D pathlimit <0-255>",
       NO_STR
       "Specify a network to announce via BGP\n"
       "Network number\n"
       "AS-Path hopcount limit attribute\n"
       "AS-Pathlimit TTL, in number of AS-Path hops\n")
ALIAS_DEPRECATED (no_bgp_network_mask_natural,
       no_bgp_network_mask_natural_backdoor_ttl_cmd,
       "no network A.B.C.D backdoor pathlimit <0-255>",
       NO_STR
       "Specify a network to announce via BGP\n"
       "Network number\n"
       "Specify a BGP backdoor route\n"
       "AS-Path hopcount limit attribute\n"
       "AS-Pathlimit TTL, in number of AS-Path hops\n")
#ifdef HAVE_IPV6
ALIAS_DEPRECATED (ipv6_bgp_network,
       ipv6_bgp_network_ttl_cmd,
       "network X:X::X:X/M pathlimit <0-255>",
       "Specify a network to announce via BGP\n"
       "IPv6 prefix <network>/<length>\n"
       "AS-Path hopcount limit attribute\n"
       "AS-Pathlimit TTL, in number of AS-Path hops\n")
ALIAS_DEPRECATED (no_ipv6_bgp_network,
       no_ipv6_bgp_network_ttl_cmd,
       "no network X:X::X:X/M pathlimit <0-255>",
       NO_STR
       "Specify a network to announce via BGP\n"
       "IPv6 prefix <network>/<length>\n"
       "AS-Path hopcount limit attribute\n"
       "AS-Pathlimit TTL, in number of AS-Path hops\n")
#endif /* HAVE_IPV6 */

/* Aggreagete address:

  advertise-map  Set condition to advertise attribute
  as-set         Generate AS set path information
  attribute-map  Set attributes of aggregate
  route-map      Set parameters of aggregate
  summary-only   Filter more specific routes from updates
  suppress-map   Conditionally filter more specific routes from updates
  <cr>
 */
struct bgp_aggregate
{
  /* Summary-only flag. */
  u_char summary_only;

  /* AS set generation. */
  u_char as_set;

  /* Route-map for aggregated route. */
  struct route_map *map;

  /* Suppress-count. */
  unsigned long count;

  /* SAFI configuration. */
  safi_t safi;
};

static struct bgp_aggregate *
bgp_aggregate_new (void)
{
  return XCALLOC (MTYPE_BGP_AGGREGATE, sizeof (struct bgp_aggregate));
}

static void
bgp_aggregate_free (struct bgp_aggregate *aggregate)
{
  XFREE (MTYPE_BGP_AGGREGATE, aggregate);
}     

static void
bgp_aggregate_route (struct bgp *bgp, struct prefix *p, struct bgp_info *rinew,
		     afi_t afi, safi_t safi, struct bgp_info *del, 
		     struct bgp_aggregate *aggregate)
{
  struct bgp_table *table;
  struct bgp_node *top;
  struct bgp_node *rn;
  u_char origin;
  struct aspath *aspath = NULL;
  struct aspath *asmerge = NULL;
  struct community *community = NULL;
  struct community *commerge = NULL;
  struct in_addr nexthop;
  u_int32_t med = 0;
  struct bgp_info *ri;
  struct bgp_info *new;
  int first = 1;
  unsigned long match = 0;

  /* Record adding route's nexthop and med. */
  if (rinew)
    {
      nexthop = rinew->attr->nexthop;
      med = rinew->attr->med;
    }

  /* ORIGIN attribute: If at least one route among routes that are
     aggregated has ORIGIN with the value INCOMPLETE, then the
     aggregated route must have the ORIGIN attribute with the value
     INCOMPLETE. Otherwise, if at least one route among routes that
     are aggregated has ORIGIN with the value EGP, then the aggregated
     route must have the origin attribute with the value EGP. In all
     other case the value of the ORIGIN attribute of the aggregated
     route is INTERNAL. */
  origin = BGP_ORIGIN_IGP;

  table = bgp->rib[afi][safi];

  top = bgp_node_get (table, p);
  for (rn = bgp_node_get (table, p); rn; rn = bgp_route_next_until (rn, top))
    if (rn->p.prefixlen > p->prefixlen)
      {
	match = 0;

	for (ri = rn->info; ri; ri = ri->next)
	  {
	    if (BGP_INFO_HOLDDOWN (ri))
	      continue;

	    if (del && ri == del)
	      continue;

	    if (! rinew && first)
	      {
		nexthop = ri->attr->nexthop;
		med = ri->attr->med;
		first = 0;
	      }

#ifdef AGGREGATE_NEXTHOP_CHECK
	    if (! IPV4_ADDR_SAME (&ri->attr->nexthop, &nexthop)
		|| ri->attr->med != med)
	      {
		if (aspath)
		  aspath_free (aspath);
		if (community)
		  community_free (community);
		bgp_unlock_node (rn);
		bgp_unlock_node (top);
		return;
	      }
#endif /* AGGREGATE_NEXTHOP_CHECK */

	    if (ri->sub_type != BGP_ROUTE_AGGREGATE)
	      {
		if (aggregate->summary_only)
		  {
		    (bgp_info_extra_get (ri))->suppress++;
		    bgp_info_set_flag (rn, ri, BGP_INFO_ATTR_CHANGED);
		    match++;
		  }

		aggregate->count++;

		if (aggregate->as_set)
		  {
		    if (origin < ri->attr->origin)
		      origin = ri->attr->origin;

		    if (aspath)
		      {
			asmerge = aspath_aggregate (aspath, ri->attr->aspath);
			aspath_free (aspath);
			aspath = asmerge;
		      }
		    else
		      aspath = aspath_dup (ri->attr->aspath);

		    if (ri->attr->community)
		      {
			if (community)
			  {
			    commerge = community_merge (community,
							ri->attr->community);
			    community = community_uniq_sort (commerge);
			    community_free (commerge);
			  }
			else
			  community = community_dup (ri->attr->community);
		      }
		  }
	      }
	  }
	if (match)
	  bgp_process (bgp, rn, afi, safi);
      }
  bgp_unlock_node (top);

  if (rinew)
    {
      aggregate->count++;
      
      if (aggregate->summary_only)
        (bgp_info_extra_get (rinew))->suppress++;

      if (aggregate->as_set)
	{
	  if (origin < rinew->attr->origin)
	    origin = rinew->attr->origin;

	  if (aspath)
	    {
	      asmerge = aspath_aggregate (aspath, rinew->attr->aspath);
	      aspath_free (aspath);
	      aspath = asmerge;
	    }
	  else
	    aspath = aspath_dup (rinew->attr->aspath);

	  if (rinew->attr->community)
	    {
	      if (community)
		{
		  commerge = community_merge (community,
					      rinew->attr->community);
		  community = community_uniq_sort (commerge);
		  community_free (commerge);
		}
	      else
		community = community_dup (rinew->attr->community);
	    }
	}
    }

  if (aggregate->count > 0)
    {
      rn = bgp_node_get (table, p);
      new = bgp_info_new ();
      new->type = ZEBRA_ROUTE_BGP;
      new->sub_type = BGP_ROUTE_AGGREGATE;
      new->peer = bgp->peer_self;
      SET_FLAG (new->flags, BGP_INFO_VALID);
      new->attr = bgp_attr_aggregate_intern (bgp, origin, aspath, community, aggregate->as_set);
      new->uptime = bgp_clock ();

      bgp_info_add (rn, new);
      bgp_unlock_node (rn);
      bgp_process (bgp, rn, afi, safi);
    }
  else
    {
      if (aspath)
	aspath_free (aspath);
      if (community)
	community_free (community);
    }
}

void bgp_aggregate_delete (struct bgp *, struct prefix *, afi_t, safi_t,
			   struct bgp_aggregate *);

void
bgp_aggregate_increment (struct bgp *bgp, struct prefix *p,
			 struct bgp_info *ri, afi_t afi, safi_t safi)
{
  struct bgp_node *child;
  struct bgp_node *rn;
  struct bgp_aggregate *aggregate;
  struct bgp_table *table;

  /* MPLS-VPN aggregation is not yet supported. */
  if (safi == SAFI_MPLS_VPN)
    return;

  table = bgp->aggregate[afi][safi];

  /* No aggregates configured. */
  if (table->top == NULL)
    return;

  if (p->prefixlen == 0)
    return;

  if (BGP_INFO_HOLDDOWN (ri))
    return;

  child = bgp_node_get (table, p);

  /* Aggregate address configuration check. */
  for (rn = child; rn; rn = rn->parent)
    if ((aggregate = rn->info) != NULL && rn->p.prefixlen < p->prefixlen)
      {
	bgp_aggregate_delete (bgp, &rn->p, afi, safi, aggregate);
	bgp_aggregate_route (bgp, &rn->p, ri, afi, safi, NULL, aggregate);
      }
  bgp_unlock_node (child);
}

void
bgp_aggregate_decrement (struct bgp *bgp, struct prefix *p, 
			 struct bgp_info *del, afi_t afi, safi_t safi)
{
  struct bgp_node *child;
  struct bgp_node *rn;
  struct bgp_aggregate *aggregate;
  struct bgp_table *table;

  /* MPLS-VPN aggregation is not yet supported. */
  if (safi == SAFI_MPLS_VPN)
    return;

  table = bgp->aggregate[afi][safi];

  /* No aggregates configured. */
  if (table->top == NULL)
    return;

  if (p->prefixlen == 0)
    return;

  child = bgp_node_get (table, p);

  /* Aggregate address configuration check. */
  for (rn = child; rn; rn = rn->parent)
    if ((aggregate = rn->info) != NULL && rn->p.prefixlen < p->prefixlen)
      {
	bgp_aggregate_delete (bgp, &rn->p, afi, safi, aggregate);
	bgp_aggregate_route (bgp, &rn->p, NULL, afi, safi, del, aggregate);
      }
  bgp_unlock_node (child);
}

static void
bgp_aggregate_add (struct bgp *bgp, struct prefix *p, afi_t afi, safi_t safi,
		   struct bgp_aggregate *aggregate)
{
  struct bgp_table *table;
  struct bgp_node *top;
  struct bgp_node *rn;
  struct bgp_info *new;
  struct bgp_info *ri;
  unsigned long match;
  u_char origin = BGP_ORIGIN_IGP;
  struct aspath *aspath = NULL;
  struct aspath *asmerge = NULL;
  struct community *community = NULL;
  struct community *commerge = NULL;

  table = bgp->rib[afi][safi];

  /* Sanity check. */
  if (afi == AFI_IP && p->prefixlen == IPV4_MAX_BITLEN)
    return;
  if (afi == AFI_IP6 && p->prefixlen == IPV6_MAX_BITLEN)
    return;
    
  /* If routes exists below this node, generate aggregate routes. */
  top = bgp_node_get (table, p);
  for (rn = bgp_node_get (table, p); rn; rn = bgp_route_next_until (rn, top))
    if (rn->p.prefixlen > p->prefixlen)
      {
	match = 0;

	for (ri = rn->info; ri; ri = ri->next)
	  {
	    if (BGP_INFO_HOLDDOWN (ri))
	      continue;

	    if (ri->sub_type != BGP_ROUTE_AGGREGATE)
	      {
		/* summary-only aggregate route suppress aggregated
		   route announcement.  */
		if (aggregate->summary_only)
		  {
		    (bgp_info_extra_get (ri))->suppress++;
		    bgp_info_set_flag (rn, ri, BGP_INFO_ATTR_CHANGED);
		    match++;
		  }
		/* as-set aggregate route generate origin, as path,
		   community aggregation.  */
		if (aggregate->as_set)
		  {
		    if (origin < ri->attr->origin)
		      origin = ri->attr->origin;

		    if (aspath)
		      {
			asmerge = aspath_aggregate (aspath, ri->attr->aspath);
			aspath_free (aspath);
			aspath = asmerge;
		      }
		    else
		      aspath = aspath_dup (ri->attr->aspath);

		    if (ri->attr->community)
		      {
			if (community)
			  {
			    commerge = community_merge (community,
							ri->attr->community);
			    community = community_uniq_sort (commerge);
			    community_free (commerge);
			  }
			else
			  community = community_dup (ri->attr->community);
		      }
		  }
		aggregate->count++;
	      }
	  }
	
	/* If this node is suppressed, process the change. */
	if (match)
	  bgp_process (bgp, rn, afi, safi);
      }
  bgp_unlock_node (top);

  /* Add aggregate route to BGP table. */
  if (aggregate->count)
    {
      rn = bgp_node_get (table, p);

      new = bgp_info_new ();
      new->type = ZEBRA_ROUTE_BGP;
      new->sub_type = BGP_ROUTE_AGGREGATE;
      new->peer = bgp->peer_self;
      SET_FLAG (new->flags, BGP_INFO_VALID);
      new->attr = bgp_attr_aggregate_intern (bgp, origin, aspath, community, aggregate->as_set);
      new->uptime = bgp_clock ();

      bgp_info_add (rn, new);
      bgp_unlock_node (rn);
      
      /* Process change. */
      bgp_process (bgp, rn, afi, safi);
    }
}

void
bgp_aggregate_delete (struct bgp *bgp, struct prefix *p, afi_t afi, 
		      safi_t safi, struct bgp_aggregate *aggregate)
{
  struct bgp_table *table;
  struct bgp_node *top;
  struct bgp_node *rn;
  struct bgp_info *ri;
  unsigned long match;

  table = bgp->rib[afi][safi];

  if (afi == AFI_IP && p->prefixlen == IPV4_MAX_BITLEN)
    return;
  if (afi == AFI_IP6 && p->prefixlen == IPV6_MAX_BITLEN)
    return;

  /* If routes exists below this node, generate aggregate routes. */
  top = bgp_node_get (table, p);
  for (rn = bgp_node_get (table, p); rn; rn = bgp_route_next_until (rn, top))
    if (rn->p.prefixlen > p->prefixlen)
      {
	match = 0;

	for (ri = rn->info; ri; ri = ri->next)
	  {
	    if (BGP_INFO_HOLDDOWN (ri))
	      continue;

	    if (ri->sub_type != BGP_ROUTE_AGGREGATE)
	      {
		if (aggregate->summary_only && ri->extra)
		  {
		    ri->extra->suppress--;

		    if (ri->extra->suppress == 0)
		      {
			bgp_info_set_flag (rn, ri, BGP_INFO_ATTR_CHANGED);
			match++;
		      }
		  }
		aggregate->count--;
	      }
	  }

	/* If this node was suppressed, process the change. */
	if (match)
	  bgp_process (bgp, rn, afi, safi);
      }
  bgp_unlock_node (top);

  /* Delete aggregate route from BGP table. */
  rn = bgp_node_get (table, p);

  for (ri = rn->info; ri; ri = ri->next)
    if (ri->peer == bgp->peer_self 
	&& ri->type == ZEBRA_ROUTE_BGP
	&& ri->sub_type == BGP_ROUTE_AGGREGATE)
      break;

  /* Withdraw static BGP route from routing table. */
  if (ri)
    {
      bgp_info_delete (rn, ri);
      bgp_process (bgp, rn, afi, safi);
    }

  /* Unlock bgp_node_lookup. */
  bgp_unlock_node (rn);
}

/* Aggregate route attribute. */
#define AGGREGATE_SUMMARY_ONLY 1
#define AGGREGATE_AS_SET       1

static int
bgp_aggregate_unset (struct vty *vty, const char *prefix_str,
                     afi_t afi, safi_t safi)
{
  int ret;
  struct prefix p;
  struct bgp_node *rn;
  struct bgp *bgp;
  struct bgp_aggregate *aggregate;

  /* Convert string to prefix structure. */
  ret = str2prefix (prefix_str, &p);
  if (!ret)
    {
      vty_out (vty, "Malformed prefix%s", VTY_NEWLINE);
      return CMD_WARNING;
    }
  apply_mask (&p);

  /* Get BGP structure. */
  bgp = vty->index;

  /* Old configuration check. */
  rn = bgp_node_lookup (bgp->aggregate[afi][safi], &p);
  if (! rn)
    {
      vty_out (vty, "%% There is no aggregate-address configuration.%s",
               VTY_NEWLINE);
      return CMD_WARNING;
    }

  aggregate = rn->info;
  if (aggregate->safi & SAFI_UNICAST)
    bgp_aggregate_delete (bgp, &p, afi, SAFI_UNICAST, aggregate);
  if (aggregate->safi & SAFI_MULTICAST)
    bgp_aggregate_delete (bgp, &p, afi, SAFI_MULTICAST, aggregate);

  /* Unlock aggregate address configuration. */
  rn->info = NULL;
  bgp_aggregate_free (aggregate);
  bgp_unlock_node (rn);
  bgp_unlock_node (rn);

  return CMD_SUCCESS;
}

static int
bgp_aggregate_set (struct vty *vty, const char *prefix_str,
                   afi_t afi, safi_t safi,
		   u_char summary_only, u_char as_set)
{
  int ret;
  struct prefix p;
  struct bgp_node *rn;
  struct bgp *bgp;
  struct bgp_aggregate *aggregate;

  /* Convert string to prefix structure. */
  ret = str2prefix (prefix_str, &p);
  if (!ret)
    {
      vty_out (vty, "Malformed prefix%s", VTY_NEWLINE);
      return CMD_WARNING;
    }
  apply_mask (&p);

  /* Get BGP structure. */
  bgp = vty->index;

  /* Old configuration check. */
  rn = bgp_node_get (bgp->aggregate[afi][safi], &p);

  if (rn->info)
    {
      vty_out (vty, "There is already same aggregate network.%s", VTY_NEWLINE);
      /* try to remove the old entry */
      ret = bgp_aggregate_unset (vty, prefix_str, afi, safi);
      if (ret)
        {
          vty_out (vty, "Error deleting aggregate.%s", VTY_NEWLINE);
	  bgp_unlock_node (rn);
	  return CMD_WARNING;
        }
    }

  /* Make aggregate address structure. */
  aggregate = bgp_aggregate_new ();
  aggregate->summary_only = summary_only;
  aggregate->as_set = as_set;
  aggregate->safi = safi;
  rn->info = aggregate;

  /* Aggregate address insert into BGP routing table. */
  if (safi & SAFI_UNICAST)
    bgp_aggregate_add (bgp, &p, afi, SAFI_UNICAST, aggregate);
  if (safi & SAFI_MULTICAST)
    bgp_aggregate_add (bgp, &p, afi, SAFI_MULTICAST, aggregate);

  return CMD_SUCCESS;
}

DEFUN (aggregate_address,
       aggregate_address_cmd,
       "aggregate-address A.B.C.D/M",
       "Configure BGP aggregate entries\n"
       "Aggregate prefix\n")
{
  return bgp_aggregate_set (vty, argv[0], AFI_IP, bgp_node_safi (vty), 0, 0);
}

DEFUN (aggregate_address_mask,
       aggregate_address_mask_cmd,
       "aggregate-address A.B.C.D A.B.C.D",
       "Configure BGP aggregate entries\n"
       "Aggregate address\n"
       "Aggregate mask\n")
{
  int ret;
  char prefix_str[BUFSIZ];

  ret = netmask_str2prefix_str (argv[0], argv[1], prefix_str);

  if (! ret)
    {
      vty_out (vty, "%% Inconsistent address and mask%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  return bgp_aggregate_set (vty, prefix_str, AFI_IP, bgp_node_safi (vty),
			    0, 0);
}

DEFUN (aggregate_address_summary_only,
       aggregate_address_summary_only_cmd,
       "aggregate-address A.B.C.D/M summary-only",
       "Configure BGP aggregate entries\n"
       "Aggregate prefix\n"
       "Filter more specific routes from updates\n")
{
  return bgp_aggregate_set (vty, argv[0], AFI_IP, bgp_node_safi (vty),
			    AGGREGATE_SUMMARY_ONLY, 0);
}

DEFUN (aggregate_address_mask_summary_only,
       aggregate_address_mask_summary_only_cmd,
       "aggregate-address A.B.C.D A.B.C.D summary-only",
       "Configure BGP aggregate entries\n"
       "Aggregate address\n"
       "Aggregate mask\n"
       "Filter more specific routes from updates\n")
{
  int ret;
  char prefix_str[BUFSIZ];

  ret = netmask_str2prefix_str (argv[0], argv[1], prefix_str);

  if (! ret)
    {
      vty_out (vty, "%% Inconsistent address and mask%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  return bgp_aggregate_set (vty, prefix_str, AFI_IP, bgp_node_safi (vty),
			    AGGREGATE_SUMMARY_ONLY, 0);
}

DEFUN (aggregate_address_as_set,
       aggregate_address_as_set_cmd,
       "aggregate-address A.B.C.D/M as-set",
       "Configure BGP aggregate entries\n"
       "Aggregate prefix\n"
       "Generate AS set path information\n")
{
  return bgp_aggregate_set (vty, argv[0], AFI_IP, bgp_node_safi (vty),
			    0, AGGREGATE_AS_SET);
}

DEFUN (aggregate_address_mask_as_set,
       aggregate_address_mask_as_set_cmd,
       "aggregate-address A.B.C.D A.B.C.D as-set",
       "Configure BGP aggregate entries\n"
       "Aggregate address\n"
       "Aggregate mask\n"
       "Generate AS set path information\n")
{
  int ret;
  char prefix_str[BUFSIZ];

  ret = netmask_str2prefix_str (argv[0], argv[1], prefix_str);

  if (! ret)
    {
      vty_out (vty, "%% Inconsistent address and mask%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  return bgp_aggregate_set (vty, prefix_str, AFI_IP, bgp_node_safi (vty),
			    0, AGGREGATE_AS_SET);
}


DEFUN (aggregate_address_as_set_summary,
       aggregate_address_as_set_summary_cmd,
       "aggregate-address A.B.C.D/M as-set summary-only",
       "Configure BGP aggregate entries\n"
       "Aggregate prefix\n"
       "Generate AS set path information\n"
       "Filter more specific routes from updates\n")
{
  return bgp_aggregate_set (vty, argv[0], AFI_IP, bgp_node_safi (vty),
			    AGGREGATE_SUMMARY_ONLY, AGGREGATE_AS_SET);
}

ALIAS (aggregate_address_as_set_summary,
       aggregate_address_summary_as_set_cmd,
       "aggregate-address A.B.C.D/M summary-only as-set",
       "Configure BGP aggregate entries\n"
       "Aggregate prefix\n"
       "Filter more specific routes from updates\n"
       "Generate AS set path information\n")

DEFUN (aggregate_address_mask_as_set_summary,
       aggregate_address_mask_as_set_summary_cmd,
       "aggregate-address A.B.C.D A.B.C.D as-set summary-only",
       "Configure BGP aggregate entries\n"
       "Aggregate address\n"
       "Aggregate mask\n"
       "Generate AS set path information\n"
       "Filter more specific routes from updates\n")
{
  int ret;
  char prefix_str[BUFSIZ];

  ret = netmask_str2prefix_str (argv[0], argv[1], prefix_str);

  if (! ret)
    {
      vty_out (vty, "%% Inconsistent address and mask%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  return bgp_aggregate_set (vty, prefix_str, AFI_IP, bgp_node_safi (vty),
			    AGGREGATE_SUMMARY_ONLY, AGGREGATE_AS_SET);
}

ALIAS (aggregate_address_mask_as_set_summary,
       aggregate_address_mask_summary_as_set_cmd,
       "aggregate-address A.B.C.D A.B.C.D summary-only as-set",
       "Configure BGP aggregate entries\n"
       "Aggregate address\n"
       "Aggregate mask\n"
       "Filter more specific routes from updates\n"
       "Generate AS set path information\n")

DEFUN (no_aggregate_address,
       no_aggregate_address_cmd,
       "no aggregate-address A.B.C.D/M",
       NO_STR
       "Configure BGP aggregate entries\n"
       "Aggregate prefix\n")
{
  return bgp_aggregate_unset (vty, argv[0], AFI_IP, bgp_node_safi (vty));
}

ALIAS (no_aggregate_address,
       no_aggregate_address_summary_only_cmd,
       "no aggregate-address A.B.C.D/M summary-only",
       NO_STR
       "Configure BGP aggregate entries\n"
       "Aggregate prefix\n"
       "Filter more specific routes from updates\n")

ALIAS (no_aggregate_address,
       no_aggregate_address_as_set_cmd,
       "no aggregate-address A.B.C.D/M as-set",
       NO_STR
       "Configure BGP aggregate entries\n"
       "Aggregate prefix\n"
       "Generate AS set path information\n")

ALIAS (no_aggregate_address,
       no_aggregate_address_as_set_summary_cmd,
       "no aggregate-address A.B.C.D/M as-set summary-only",
       NO_STR
       "Configure BGP aggregate entries\n"
       "Aggregate prefix\n"
       "Generate AS set path information\n"
       "Filter more specific routes from updates\n")

ALIAS (no_aggregate_address,
       no_aggregate_address_summary_as_set_cmd,
       "no aggregate-address A.B.C.D/M summary-only as-set",
       NO_STR
       "Configure BGP aggregate entries\n"
       "Aggregate prefix\n"
       "Filter more specific routes from updates\n"
       "Generate AS set path information\n")

DEFUN (no_aggregate_address_mask,
       no_aggregate_address_mask_cmd,
       "no aggregate-address A.B.C.D A.B.C.D",
       NO_STR
       "Configure BGP aggregate entries\n"
       "Aggregate address\n"
       "Aggregate mask\n")
{
  int ret;
  char prefix_str[BUFSIZ];

  ret = netmask_str2prefix_str (argv[0], argv[1], prefix_str);

  if (! ret)
    {
      vty_out (vty, "%% Inconsistent address and mask%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  return bgp_aggregate_unset (vty, prefix_str, AFI_IP, bgp_node_safi (vty));
}

ALIAS (no_aggregate_address_mask,
       no_aggregate_address_mask_summary_only_cmd,
       "no aggregate-address A.B.C.D A.B.C.D summary-only",
       NO_STR
       "Configure BGP aggregate entries\n"
       "Aggregate address\n"
       "Aggregate mask\n"
       "Filter more specific routes from updates\n")

ALIAS (no_aggregate_address_mask,
       no_aggregate_address_mask_as_set_cmd,
       "no aggregate-address A.B.C.D A.B.C.D as-set",
       NO_STR
       "Configure BGP aggregate entries\n"
       "Aggregate address\n"
       "Aggregate mask\n"
       "Generate AS set path information\n")

ALIAS (no_aggregate_address_mask,
       no_aggregate_address_mask_as_set_summary_cmd,
       "no aggregate-address A.B.C.D A.B.C.D as-set summary-only",
       NO_STR
       "Configure BGP aggregate entries\n"
       "Aggregate address\n"
       "Aggregate mask\n"
       "Generate AS set path information\n"
       "Filter more specific routes from updates\n")

ALIAS (no_aggregate_address_mask,
       no_aggregate_address_mask_summary_as_set_cmd,
       "no aggregate-address A.B.C.D A.B.C.D summary-only as-set",
       NO_STR
       "Configure BGP aggregate entries\n"
       "Aggregate address\n"
       "Aggregate mask\n"
       "Filter more specific routes from updates\n"
       "Generate AS set path information\n")

#ifdef HAVE_IPV6
DEFUN (ipv6_aggregate_address,
       ipv6_aggregate_address_cmd,
       "aggregate-address X:X::X:X/M",
       "Configure BGP aggregate entries\n"
       "Aggregate prefix\n")
{
  return bgp_aggregate_set (vty, argv[0], AFI_IP6, SAFI_UNICAST, 0, 0);
}

DEFUN (ipv6_aggregate_address_summary_only,
       ipv6_aggregate_address_summary_only_cmd,
       "aggregate-address X:X::X:X/M summary-only",
       "Configure BGP aggregate entries\n"
       "Aggregate prefix\n"
       "Filter more specific routes from updates\n")
{
  return bgp_aggregate_set (vty, argv[0], AFI_IP6, SAFI_UNICAST, 
			    AGGREGATE_SUMMARY_ONLY, 0);
}

DEFUN (no_ipv6_aggregate_address,
       no_ipv6_aggregate_address_cmd,
       "no aggregate-address X:X::X:X/M",
       NO_STR
       "Configure BGP aggregate entries\n"
       "Aggregate prefix\n")
{
  return bgp_aggregate_unset (vty, argv[0], AFI_IP6, SAFI_UNICAST);
}

DEFUN (no_ipv6_aggregate_address_summary_only,
       no_ipv6_aggregate_address_summary_only_cmd,
       "no aggregate-address X:X::X:X/M summary-only",
       NO_STR
       "Configure BGP aggregate entries\n"
       "Aggregate prefix\n"
       "Filter more specific routes from updates\n")
{
  return bgp_aggregate_unset (vty, argv[0], AFI_IP6, SAFI_UNICAST);
}

ALIAS (ipv6_aggregate_address,
       old_ipv6_aggregate_address_cmd,
       "ipv6 bgp aggregate-address X:X::X:X/M",
       IPV6_STR
       BGP_STR
       "Configure BGP aggregate entries\n"
       "Aggregate prefix\n")

ALIAS (ipv6_aggregate_address_summary_only,
       old_ipv6_aggregate_address_summary_only_cmd,
       "ipv6 bgp aggregate-address X:X::X:X/M summary-only",
       IPV6_STR
       BGP_STR
       "Configure BGP aggregate entries\n"
       "Aggregate prefix\n"
       "Filter more specific routes from updates\n")

ALIAS (no_ipv6_aggregate_address,
       old_no_ipv6_aggregate_address_cmd,
       "no ipv6 bgp aggregate-address X:X::X:X/M",
       NO_STR
       IPV6_STR
       BGP_STR
       "Configure BGP aggregate entries\n"
       "Aggregate prefix\n")

ALIAS (no_ipv6_aggregate_address_summary_only,
       old_no_ipv6_aggregate_address_summary_only_cmd,
       "no ipv6 bgp aggregate-address X:X::X:X/M summary-only",
       NO_STR
       IPV6_STR
       BGP_STR
       "Configure BGP aggregate entries\n"
       "Aggregate prefix\n"
       "Filter more specific routes from updates\n")
#endif /* HAVE_IPV6 */

/* Redistribute route treatment. */
void
bgp_redistribute_add (struct prefix *p, const struct in_addr *nexthop,
		      const struct in6_addr *nexthop6,
		      u_int32_t metric, u_char type)
{
  struct bgp *bgp;
  struct listnode *node, *nnode;
  struct bgp_info *new;
  struct bgp_info *bi;
  struct bgp_info info;
  struct bgp_node *bn;
  struct attr attr;
  struct attr *new_attr;
  afi_t afi;
  int ret;

  /* Make default attribute. */
  bgp_attr_default_set (&attr, BGP_ORIGIN_INCOMPLETE);
  if (nexthop)
    attr.nexthop = *nexthop;

#ifdef HAVE_IPV6
  if (nexthop6)
    {
      struct attr_extra *extra = bgp_attr_extra_get(&attr);
      extra->mp_nexthop_global = *nexthop6;
      extra->mp_nexthop_len = 16;
    }
#endif

  attr.med = metric;
  attr.flag |= ATTR_FLAG_BIT (BGP_ATTR_MULTI_EXIT_DISC);

  for (ALL_LIST_ELEMENTS (bm->bgp, node, nnode, bgp))
    {
      afi = family2afi (p->family);

      if (bgp->redist[afi][type])
	{
	  struct attr attr_new;
	  struct attr_extra extra_new;

	  /* Copy attribute for modification. */
	  attr_new.extra = &extra_new;
	  bgp_attr_dup (&attr_new, &attr);

	  if (bgp->redist_metric_flag[afi][type])
	    attr_new.med = bgp->redist_metric[afi][type];

	  /* Apply route-map. */
	  if (bgp->rmap[afi][type].map)
	    {
	      info.peer = bgp->peer_self;
	      info.attr = &attr_new;

              SET_FLAG (bgp->peer_self->rmap_type, PEER_RMAP_TYPE_REDISTRIBUTE);

	      ret = route_map_apply (bgp->rmap[afi][type].map, p, RMAP_BGP,
				     &info);

              bgp->peer_self->rmap_type = 0;

	      if (ret == RMAP_DENYMATCH)
		{
		  /* Free uninterned attribute. */
		  bgp_attr_flush (&attr_new);

		  /* Unintern original. */
		  aspath_unintern (&attr.aspath);
		  bgp_attr_extra_free (&attr);
		  bgp_redistribute_delete (p, type);
		  return;
		}
	    }

          bn = bgp_afi_node_get (bgp->rib[afi][SAFI_UNICAST], 
                                 afi, SAFI_UNICAST, p, NULL);
          
	  new_attr = bgp_attr_intern (&attr_new);

 	  for (bi = bn->info; bi; bi = bi->next)
 	    if (bi->peer == bgp->peer_self
 		&& bi->sub_type == BGP_ROUTE_REDISTRIBUTE)
 	      break;
 
 	  if (bi)
 	    {
 	      if (attrhash_cmp (bi->attr, new_attr) &&
		  !CHECK_FLAG(bi->flags, BGP_INFO_REMOVED))
 		{
 		  bgp_attr_unintern (&new_attr);
 		  aspath_unintern (&attr.aspath);
 		  bgp_attr_extra_free (&attr);
 		  bgp_unlock_node (bn);
 		  return;
 		}
 	      else
 		{
 		  /* The attribute is changed. */
 		  bgp_info_set_flag (bn, bi, BGP_INFO_ATTR_CHANGED);
 
 		  /* Rewrite BGP route information. */
		  if (CHECK_FLAG(bi->flags, BGP_INFO_REMOVED))
		    bgp_info_restore(bn, bi);
		  else
		    bgp_aggregate_decrement (bgp, p, bi, afi, SAFI_UNICAST);
 		  bgp_attr_unintern (&bi->attr);
 		  bi->attr = new_attr;
 		  bi->uptime = bgp_clock ();
 
 		  /* Process change. */
 		  bgp_aggregate_increment (bgp, p, bi, afi, SAFI_UNICAST);
 		  bgp_process (bgp, bn, afi, SAFI_UNICAST);
 		  bgp_unlock_node (bn);
 		  aspath_unintern (&attr.aspath);
 		  bgp_attr_extra_free (&attr);
 		  return;
 		} 
 	    }

	  new = bgp_info_new ();
	  new->type = type;
	  new->sub_type = BGP_ROUTE_REDISTRIBUTE;
	  new->peer = bgp->peer_self;
	  SET_FLAG (new->flags, BGP_INFO_VALID);
	  new->attr = new_attr;
	  new->uptime = bgp_clock ();

	  bgp_aggregate_increment (bgp, p, new, afi, SAFI_UNICAST);
	  bgp_info_add (bn, new);
	  bgp_unlock_node (bn);
	  bgp_process (bgp, bn, afi, SAFI_UNICAST);
	}
    }

  /* Unintern original. */
  aspath_unintern (&attr.aspath);
  bgp_attr_extra_free (&attr);
}

void
bgp_redistribute_delete (struct prefix *p, u_char type)
{
  struct bgp *bgp;
  struct listnode *node, *nnode;
  afi_t afi;
  struct bgp_node *rn;
  struct bgp_info *ri;

  for (ALL_LIST_ELEMENTS (bm->bgp, node, nnode, bgp))
    {
      afi = family2afi (p->family);

      if (bgp->redist[afi][type])
	{
         rn = bgp_afi_node_get (bgp->rib[afi][SAFI_UNICAST], afi, SAFI_UNICAST, p, NULL);

	  for (ri = rn->info; ri; ri = ri->next)
	    if (ri->peer == bgp->peer_self
		&& ri->type == type)
	      break;

	  if (ri)
	    {
	      bgp_aggregate_decrement (bgp, p, ri, afi, SAFI_UNICAST);
	      bgp_info_delete (rn, ri);
	      bgp_process (bgp, rn, afi, SAFI_UNICAST);
	    }
	  bgp_unlock_node (rn);
	}
    }
}

/* Withdraw specified route type's route. */
void
bgp_redistribute_withdraw (struct bgp *bgp, afi_t afi, int type)
{
  struct bgp_node *rn;
  struct bgp_info *ri;
  struct bgp_table *table;

  table = bgp->rib[afi][SAFI_UNICAST];

  for (rn = bgp_table_top (table); rn; rn = bgp_route_next (rn))
    {
      for (ri = rn->info; ri; ri = ri->next)
	if (ri->peer == bgp->peer_self
	    && ri->type == type)
	  break;

      if (ri)
	{
	  bgp_aggregate_decrement (bgp, &rn->p, ri, afi, SAFI_UNICAST);
	  bgp_info_delete (rn, ri);
	  bgp_process (bgp, rn, afi, SAFI_UNICAST);
	}
    }
}

#if 0
#define TALLY_SIGFIG 100000
static unsigned long
ravg_tally (unsigned long count, unsigned long oldavg, unsigned long newval)
{
  unsigned long newtot = (count-1) * oldavg + (newval * TALLY_SIGFIG);
  unsigned long res = (newtot * TALLY_SIGFIG) / count;
  unsigned long ret = newtot / count;
  
  if ((res % TALLY_SIGFIG) > (TALLY_SIGFIG/2))
    return ret + 1;
  else
    return ret;
}
#endif

struct bgp_table *bgp_distance_table;

struct bgp_distance
{
  /* Distance value for the IP source prefix. */
  u_char distance;

  /* Name of the access-list to be matched. */
  char *access_list;
};

static struct bgp_distance *
bgp_distance_new (void)
{
  return XCALLOC (MTYPE_BGP_DISTANCE, sizeof (struct bgp_distance));
}

static void
bgp_distance_free (struct bgp_distance *bdistance)
{
  XFREE (MTYPE_BGP_DISTANCE, bdistance);
}

static int
bgp_distance_set (struct vty *vty, const char *distance_str, 
                  const char *ip_str, const char *access_list_str)
{
  int ret;
  struct prefix_ipv4 p;
  u_char distance;
  struct bgp_node *rn;
  struct bgp_distance *bdistance;

  ret = str2prefix_ipv4 (ip_str, &p);
  if (ret == 0)
    {
      vty_out (vty, "Malformed prefix%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  distance = atoi (distance_str);

  /* Get BGP distance node. */
  rn = bgp_node_get (bgp_distance_table, (struct prefix *) &p);
  if (rn->info)
    {
      bdistance = rn->info;
      bgp_unlock_node (rn);
    }
  else
    {
      bdistance = bgp_distance_new ();
      rn->info = bdistance;
    }

  /* Set distance value. */
  bdistance->distance = distance;

  /* Reset access-list configuration. */
  if (bdistance->access_list)
    {
      free (bdistance->access_list);
      bdistance->access_list = NULL;
    }
  if (access_list_str)
    bdistance->access_list = strdup (access_list_str);

  return CMD_SUCCESS;
}

static int
bgp_distance_unset (struct vty *vty, const char *distance_str, 
                    const char *ip_str, const char *access_list_str)
{
  int ret;
  struct prefix_ipv4 p;
  u_char distance;
  struct bgp_node *rn;
  struct bgp_distance *bdistance;

  ret = str2prefix_ipv4 (ip_str, &p);
  if (ret == 0)
    {
      vty_out (vty, "Malformed prefix%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  distance = atoi (distance_str);

  rn = bgp_node_lookup (bgp_distance_table, (struct prefix *)&p);
  if (! rn)
    {
      vty_out (vty, "Can't find specified prefix%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  bdistance = rn->info;

  if (bdistance->access_list)
    free (bdistance->access_list);
  bgp_distance_free (bdistance);

  rn->info = NULL;
  bgp_unlock_node (rn);
  bgp_unlock_node (rn);

  return CMD_SUCCESS;
}

/* Apply BGP information to distance method. */
u_char
bgp_distance_apply (struct prefix *p, struct bgp_info *rinfo, struct bgp *bgp)
{
  struct bgp_node *rn;
  struct prefix_ipv4 q;
  struct peer *peer;
  struct bgp_distance *bdistance;
  struct access_list *alist;
  struct bgp_static *bgp_static;

  if (! bgp)
    return 0;

  if (p->family != AF_INET)
    return 0;

  peer = rinfo->peer;

  if (peer->su.sa.sa_family != AF_INET)
    return 0;

  memset (&q, 0, sizeof (struct prefix_ipv4));
  q.family = AF_INET;
  q.prefix = peer->su.sin.sin_addr;
  q.prefixlen = IPV4_MAX_BITLEN;

  /* Check source address. */
  rn = bgp_node_match (bgp_distance_table, (struct prefix *) &q);
  if (rn)
    {
      bdistance = rn->info;
      bgp_unlock_node (rn);

      if (bdistance->access_list)
	{
	  alist = access_list_lookup (AFI_IP, bdistance->access_list);
	  if (alist && access_list_apply (alist, p) == FILTER_PERMIT)
	    return bdistance->distance;
	}
      else
	return bdistance->distance;
    }

  /* Backdoor check. */
  rn = bgp_node_lookup (bgp->route[AFI_IP][SAFI_UNICAST], p);
  if (rn)
    {
      bgp_static = rn->info;
      bgp_unlock_node (rn);

      if (bgp_static->backdoor)
	{
	  if (bgp->distance_local)
	    return bgp->distance_local;
	  else
	    return ZEBRA_IBGP_DISTANCE_DEFAULT;
	}
    }

  if (peer->sort == BGP_PEER_EBGP)
    {
      if (bgp->distance_ebgp)
	return bgp->distance_ebgp;
      return ZEBRA_EBGP_DISTANCE_DEFAULT;
    }
  else
    {
      if (bgp->distance_ibgp)
	return bgp->distance_ibgp;
      return ZEBRA_IBGP_DISTANCE_DEFAULT;
    }
}

DEFUN (bgp_distance,
       bgp_distance_cmd,
       "distance bgp <1-255> <1-255> <1-255>",
       "Define an administrative distance\n"
       "BGP distance\n"
       "Distance for routes external to the AS\n"
       "Distance for routes internal to the AS\n"
       "Distance for local routes\n")
{
  struct bgp *bgp;

  bgp = vty->index;

  bgp->distance_ebgp = atoi (argv[0]);
  bgp->distance_ibgp = atoi (argv[1]);
  bgp->distance_local = atoi (argv[2]);
  return CMD_SUCCESS;
}

DEFUN (no_bgp_distance,
       no_bgp_distance_cmd,
       "no distance bgp <1-255> <1-255> <1-255>",
       NO_STR
       "Define an administrative distance\n"
       "BGP distance\n"
       "Distance for routes external to the AS\n"
       "Distance for routes internal to the AS\n"
       "Distance for local routes\n")
{
  struct bgp *bgp;

  bgp = vty->index;

  bgp->distance_ebgp= 0;
  bgp->distance_ibgp = 0;
  bgp->distance_local = 0;
  return CMD_SUCCESS;
}

ALIAS (no_bgp_distance,
       no_bgp_distance2_cmd,
       "no distance bgp",
       NO_STR
       "Define an administrative distance\n"
       "BGP distance\n")

DEFUN (bgp_distance_source,
       bgp_distance_source_cmd,
       "distance <1-255> A.B.C.D/M",
       "Define an administrative distance\n"
       "Administrative distance\n"
       "IP source prefix\n")
{
  bgp_distance_set (vty, argv[0], argv[1], NULL);
  return CMD_SUCCESS;
}

DEFUN (no_bgp_distance_source,
       no_bgp_distance_source_cmd,
       "no distance <1-255> A.B.C.D/M",
       NO_STR
       "Define an administrative distance\n"
       "Administrative distance\n"
       "IP source prefix\n")
{
  bgp_distance_unset (vty, argv[0], argv[1], NULL);
  return CMD_SUCCESS;
}

DEFUN (bgp_distance_source_access_list,
       bgp_distance_source_access_list_cmd,
       "distance <1-255> A.B.C.D/M WORD",
       "Define an administrative distance\n"
       "Administrative distance\n"
       "IP source prefix\n"
       "Access list name\n")
{
  bgp_distance_set (vty, argv[0], argv[1], argv[2]);
  return CMD_SUCCESS;
}

DEFUN (no_bgp_distance_source_access_list,
       no_bgp_distance_source_access_list_cmd,
       "no distance <1-255> A.B.C.D/M WORD",
       NO_STR
       "Define an administrative distance\n"
       "Administrative distance\n"
       "IP source prefix\n"
       "Access list name\n")
{
  bgp_distance_unset (vty, argv[0], argv[1], argv[2]);
  return CMD_SUCCESS;
}

DEFUN (bgp_damp_set,
       bgp_damp_set_cmd,
       "bgp dampening <1-45> <1-20000> <1-20000> <1-255>",
       "BGP Specific commands\n"
       "Enable route-flap dampening\n"
       "Half-life time for the penalty\n"
       "Value to start reusing a route\n"
       "Value to start suppressing a route\n"
       "Maximum duration to suppress a stable route\n")
{
  struct bgp *bgp;
  int half = DEFAULT_HALF_LIFE * 60;
  int reuse = DEFAULT_REUSE;
  int suppress = DEFAULT_SUPPRESS;
  int max = 4 * half;

  if (argc == 4)
    {
      half = atoi (argv[0]) * 60;
      reuse = atoi (argv[1]);
      suppress = atoi (argv[2]);
      max = atoi (argv[3]) * 60;
    }
  else if (argc == 1)
    {
      half = atoi (argv[0]) * 60;
      max = 4 * half;
    }

  bgp = vty->index;
  return bgp_damp_enable (bgp, bgp_node_afi (vty), bgp_node_safi (vty),
			  half, reuse, suppress, max);
}

ALIAS (bgp_damp_set,
       bgp_damp_set2_cmd,
       "bgp dampening <1-45>",
       "BGP Specific commands\n"
       "Enable route-flap dampening\n"
       "Half-life time for the penalty\n")

ALIAS (bgp_damp_set,
       bgp_damp_set3_cmd,
       "bgp dampening",
       "BGP Specific commands\n"
       "Enable route-flap dampening\n")

DEFUN (bgp_damp_unset,
       bgp_damp_unset_cmd,
       "no bgp dampening",
       NO_STR
       "BGP Specific commands\n"
       "Enable route-flap dampening\n")
{
  struct bgp *bgp;

  bgp = vty->index;
  return bgp_damp_disable (bgp, bgp_node_afi (vty), bgp_node_safi (vty));
}

ALIAS (bgp_damp_unset,
       bgp_damp_unset2_cmd,
       "no bgp dampening <1-45> <1-20000> <1-20000> <1-255>",
       NO_STR
       "BGP Specific commands\n"
       "Enable route-flap dampening\n"
       "Half-life time for the penalty\n"
       "Value to start reusing a route\n"
       "Value to start suppressing a route\n"
       "Maximum duration to suppress a stable route\n")

static int
bgp_config_write_network_vpnv4 (struct vty *vty, struct bgp *bgp,
				afi_t afi, safi_t safi, int *write)
{
  struct bgp_node *prn;
  struct bgp_node *rn;
  struct bgp_table *table;
  struct prefix *p;
  struct prefix_rd *prd;
  struct bgp_static *bgp_static;
  u_int32_t label;
  char buf[SU_ADDRSTRLEN];
  char rdbuf[RD_ADDRSTRLEN];
  
  /* Network configuration. */
  for (prn = bgp_table_top (bgp->route[afi][safi]); prn; prn = bgp_route_next (prn))
    if ((table = prn->info) != NULL)
      for (rn = bgp_table_top (table); rn; rn = bgp_route_next (rn)) 
	if ((bgp_static = rn->info) != NULL)
	  {
	    p = &rn->p;
	    prd = (struct prefix_rd *) &prn->p;

	    /* "address-family" display.  */
	    bgp_config_write_family_header (vty, afi, safi, write);

	    /* "network" configuration display.  */
	    prefix_rd2str (prd, rdbuf, RD_ADDRSTRLEN);
	    label = decode_label (bgp_static->tag);

	    vty_out (vty, " network %s/%d rd %s tag %d",
		     inet_ntop (p->family, &p->u.prefix, buf, SU_ADDRSTRLEN), 
		     p->prefixlen,
		     rdbuf, label);
	    vty_out (vty, "%s", VTY_NEWLINE);
	  }
  return 0;
}

/* Configuration of static route announcement and aggregate
   information. */
int
bgp_config_write_network (struct vty *vty, struct bgp *bgp,
			  afi_t afi, safi_t safi, int *write)
{
  struct bgp_node *rn;
  struct prefix *p;
  struct bgp_static *bgp_static;
  struct bgp_aggregate *bgp_aggregate;
  char buf[SU_ADDRSTRLEN];
  
  if (afi == AFI_IP && safi == SAFI_MPLS_VPN)
    return bgp_config_write_network_vpnv4 (vty, bgp, afi, safi, write);

  /* Network configuration. */
  for (rn = bgp_table_top (bgp->route[afi][safi]); rn; rn = bgp_route_next (rn)) 
    if ((bgp_static = rn->info) != NULL)
      {
	p = &rn->p;

	/* "address-family" display.  */
	bgp_config_write_family_header (vty, afi, safi, write);

	/* "network" configuration display.  */
	if (bgp_option_check (BGP_OPT_CONFIG_CISCO) && afi == AFI_IP)
	  {
	    u_int32_t destination; 
	    struct in_addr netmask;

	    destination = ntohl (p->u.prefix4.s_addr);
	    masklen2ip (p->prefixlen, &netmask);
	    vty_out (vty, " network %s",
		     inet_ntop (p->family, &p->u.prefix, buf, SU_ADDRSTRLEN));

	    if ((IN_CLASSC (destination) && p->prefixlen == 24)
		|| (IN_CLASSB (destination) && p->prefixlen == 16)
		|| (IN_CLASSA (destination) && p->prefixlen == 8)
		|| p->u.prefix4.s_addr == 0)
	      {
		/* Natural mask is not display. */
	      }
	    else
	      vty_out (vty, " mask %s", inet_ntoa (netmask));
	  }
	else
	  {
	    vty_out (vty, " network %s/%d",
		     inet_ntop (p->family, &p->u.prefix, buf, SU_ADDRSTRLEN), 
		     p->prefixlen);
	  }

	if (bgp_static->rmap.name)
	  vty_out (vty, " route-map %s", bgp_static->rmap.name);
	else 
	  {
	    if (bgp_static->backdoor)
	      vty_out (vty, " backdoor");
          }

	vty_out (vty, "%s", VTY_NEWLINE);
      }

  /* Aggregate-address configuration. */
  for (rn = bgp_table_top (bgp->aggregate[afi][safi]); rn; rn = bgp_route_next (rn))
    if ((bgp_aggregate = rn->info) != NULL)
      {
	p = &rn->p;

	/* "address-family" display.  */
	bgp_config_write_family_header (vty, afi, safi, write);

	if (bgp_option_check (BGP_OPT_CONFIG_CISCO) && afi == AFI_IP)
	  {
	    struct in_addr netmask;

	    masklen2ip (p->prefixlen, &netmask);
	    vty_out (vty, " aggregate-address %s %s",
		     inet_ntop (p->family, &p->u.prefix, buf, SU_ADDRSTRLEN),
		     inet_ntoa (netmask));
	  }
	else
	  {
	    vty_out (vty, " aggregate-address %s/%d",
		     inet_ntop (p->family, &p->u.prefix, buf, SU_ADDRSTRLEN),
		     p->prefixlen);
	  }

	if (bgp_aggregate->as_set)
	  vty_out (vty, " as-set");
	
	if (bgp_aggregate->summary_only)
	  vty_out (vty, " summary-only");

	vty_out (vty, "%s", VTY_NEWLINE);
      }

  return 0;
}

int
bgp_config_write_distance (struct vty *vty, struct bgp *bgp)
{
  struct bgp_node *rn;
  struct bgp_distance *bdistance;

  /* Distance configuration. */
  if (bgp->distance_ebgp
      && bgp->distance_ibgp
      && bgp->distance_local
      && (bgp->distance_ebgp != ZEBRA_EBGP_DISTANCE_DEFAULT
	  || bgp->distance_ibgp != ZEBRA_IBGP_DISTANCE_DEFAULT
	  || bgp->distance_local != ZEBRA_IBGP_DISTANCE_DEFAULT))
    vty_out (vty, " distance bgp %d %d %d%s",
	     bgp->distance_ebgp, bgp->distance_ibgp, bgp->distance_local,
	     VTY_NEWLINE);
  
  for (rn = bgp_table_top (bgp_distance_table); rn; rn = bgp_route_next (rn))
    if ((bdistance = rn->info) != NULL)
      {
	vty_out (vty, " distance %d %s/%d %s%s", bdistance->distance,
		 inet_ntoa (rn->p.u.prefix4), rn->p.prefixlen,
		 bdistance->access_list ? bdistance->access_list : "",
		 VTY_NEWLINE);
      }

  return 0;
}

/* Allocate routing table structure and install commands. */
void
bgp_route_init (void)
{
  /* Init BGP distance table. */
  bgp_distance_table = bgp_table_init (AFI_IP, SAFI_UNICAST);

  /* IPv4 BGP commands. */
  install_element (BGP_NODE, &bgp_network_cmd);
  install_element (BGP_NODE, &bgp_network_mask_cmd);
  install_element (BGP_NODE, &bgp_network_mask_natural_cmd);
  install_element (BGP_NODE, &bgp_network_route_map_cmd);
  install_element (BGP_NODE, &bgp_network_mask_route_map_cmd);
  install_element (BGP_NODE, &bgp_network_mask_natural_route_map_cmd);
  install_element (BGP_NODE, &bgp_network_backdoor_cmd);
  install_element (BGP_NODE, &bgp_network_mask_backdoor_cmd);
  install_element (BGP_NODE, &bgp_network_mask_natural_backdoor_cmd);
  install_element (BGP_NODE, &no_bgp_network_cmd);
  install_element (BGP_NODE, &no_bgp_network_mask_cmd);
  install_element (BGP_NODE, &no_bgp_network_mask_natural_cmd);
  install_element (BGP_NODE, &no_bgp_network_route_map_cmd);
  install_element (BGP_NODE, &no_bgp_network_mask_route_map_cmd);
  install_element (BGP_NODE, &no_bgp_network_mask_natural_route_map_cmd);
  install_element (BGP_NODE, &no_bgp_network_backdoor_cmd);
  install_element (BGP_NODE, &no_bgp_network_mask_backdoor_cmd);
  install_element (BGP_NODE, &no_bgp_network_mask_natural_backdoor_cmd);

  install_element (BGP_NODE, &aggregate_address_cmd);
  install_element (BGP_NODE, &aggregate_address_mask_cmd);
  install_element (BGP_NODE, &aggregate_address_summary_only_cmd);
  install_element (BGP_NODE, &aggregate_address_mask_summary_only_cmd);
  install_element (BGP_NODE, &aggregate_address_as_set_cmd);
  install_element (BGP_NODE, &aggregate_address_mask_as_set_cmd);
  install_element (BGP_NODE, &aggregate_address_as_set_summary_cmd);
  install_element (BGP_NODE, &aggregate_address_mask_as_set_summary_cmd);
  install_element (BGP_NODE, &aggregate_address_summary_as_set_cmd);
  install_element (BGP_NODE, &aggregate_address_mask_summary_as_set_cmd);
  install_element (BGP_NODE, &no_aggregate_address_cmd);
  install_element (BGP_NODE, &no_aggregate_address_summary_only_cmd);
  install_element (BGP_NODE, &no_aggregate_address_as_set_cmd);
  install_element (BGP_NODE, &no_aggregate_address_as_set_summary_cmd);
  install_element (BGP_NODE, &no_aggregate_address_summary_as_set_cmd);
  install_element (BGP_NODE, &no_aggregate_address_mask_cmd);
  install_element (BGP_NODE, &no_aggregate_address_mask_summary_only_cmd);
  install_element (BGP_NODE, &no_aggregate_address_mask_as_set_cmd);
  install_element (BGP_NODE, &no_aggregate_address_mask_as_set_summary_cmd);
  install_element (BGP_NODE, &no_aggregate_address_mask_summary_as_set_cmd);

  /* IPv4 unicast configuration.  */
  install_element (BGP_IPV4_NODE, &bgp_network_cmd);
  install_element (BGP_IPV4_NODE, &bgp_network_mask_cmd);
  install_element (BGP_IPV4_NODE, &bgp_network_mask_natural_cmd);
  install_element (BGP_IPV4_NODE, &bgp_network_route_map_cmd);
  install_element (BGP_IPV4_NODE, &bgp_network_mask_route_map_cmd);
  install_element (BGP_IPV4_NODE, &bgp_network_mask_natural_route_map_cmd);
  install_element (BGP_IPV4_NODE, &no_bgp_network_cmd);
  install_element (BGP_IPV4_NODE, &no_bgp_network_mask_cmd);
  install_element (BGP_IPV4_NODE, &no_bgp_network_mask_natural_cmd);
  install_element (BGP_IPV4_NODE, &no_bgp_network_route_map_cmd);
  install_element (BGP_IPV4_NODE, &no_bgp_network_mask_route_map_cmd);
  install_element (BGP_IPV4_NODE, &no_bgp_network_mask_natural_route_map_cmd);
  
  install_element (BGP_IPV4_NODE, &aggregate_address_cmd);
  install_element (BGP_IPV4_NODE, &aggregate_address_mask_cmd);
  install_element (BGP_IPV4_NODE, &aggregate_address_summary_only_cmd);
  install_element (BGP_IPV4_NODE, &aggregate_address_mask_summary_only_cmd);
  install_element (BGP_IPV4_NODE, &aggregate_address_as_set_cmd);
  install_element (BGP_IPV4_NODE, &aggregate_address_mask_as_set_cmd);
  install_element (BGP_IPV4_NODE, &aggregate_address_as_set_summary_cmd);
  install_element (BGP_IPV4_NODE, &aggregate_address_mask_as_set_summary_cmd);
  install_element (BGP_IPV4_NODE, &aggregate_address_summary_as_set_cmd);
  install_element (BGP_IPV4_NODE, &aggregate_address_mask_summary_as_set_cmd);
  install_element (BGP_IPV4_NODE, &no_aggregate_address_cmd);
  install_element (BGP_IPV4_NODE, &no_aggregate_address_summary_only_cmd);
  install_element (BGP_IPV4_NODE, &no_aggregate_address_as_set_cmd);
  install_element (BGP_IPV4_NODE, &no_aggregate_address_as_set_summary_cmd);
  install_element (BGP_IPV4_NODE, &no_aggregate_address_summary_as_set_cmd);
  install_element (BGP_IPV4_NODE, &no_aggregate_address_mask_cmd);
  install_element (BGP_IPV4_NODE, &no_aggregate_address_mask_summary_only_cmd);
  install_element (BGP_IPV4_NODE, &no_aggregate_address_mask_as_set_cmd);
  install_element (BGP_IPV4_NODE, &no_aggregate_address_mask_as_set_summary_cmd);
  install_element (BGP_IPV4_NODE, &no_aggregate_address_mask_summary_as_set_cmd);

  /* IPv4 multicast configuration.  */
  install_element (BGP_IPV4M_NODE, &bgp_network_cmd);
  install_element (BGP_IPV4M_NODE, &bgp_network_mask_cmd);
  install_element (BGP_IPV4M_NODE, &bgp_network_mask_natural_cmd);
  install_element (BGP_IPV4M_NODE, &bgp_network_route_map_cmd);
  install_element (BGP_IPV4M_NODE, &bgp_network_mask_route_map_cmd);
  install_element (BGP_IPV4M_NODE, &bgp_network_mask_natural_route_map_cmd);
  install_element (BGP_IPV4M_NODE, &no_bgp_network_cmd);
  install_element (BGP_IPV4M_NODE, &no_bgp_network_mask_cmd);
  install_element (BGP_IPV4M_NODE, &no_bgp_network_mask_natural_cmd);
  install_element (BGP_IPV4M_NODE, &no_bgp_network_route_map_cmd);
  install_element (BGP_IPV4M_NODE, &no_bgp_network_mask_route_map_cmd);
  install_element (BGP_IPV4M_NODE, &no_bgp_network_mask_natural_route_map_cmd);
  install_element (BGP_IPV4M_NODE, &aggregate_address_cmd);
  install_element (BGP_IPV4M_NODE, &aggregate_address_mask_cmd);
  install_element (BGP_IPV4M_NODE, &aggregate_address_summary_only_cmd);
  install_element (BGP_IPV4M_NODE, &aggregate_address_mask_summary_only_cmd);
  install_element (BGP_IPV4M_NODE, &aggregate_address_as_set_cmd);
  install_element (BGP_IPV4M_NODE, &aggregate_address_mask_as_set_cmd);
  install_element (BGP_IPV4M_NODE, &aggregate_address_as_set_summary_cmd);
  install_element (BGP_IPV4M_NODE, &aggregate_address_mask_as_set_summary_cmd);
  install_element (BGP_IPV4M_NODE, &aggregate_address_summary_as_set_cmd);
  install_element (BGP_IPV4M_NODE, &aggregate_address_mask_summary_as_set_cmd);
  install_element (BGP_IPV4M_NODE, &no_aggregate_address_cmd);
  install_element (BGP_IPV4M_NODE, &no_aggregate_address_summary_only_cmd);
  install_element (BGP_IPV4M_NODE, &no_aggregate_address_as_set_cmd);
  install_element (BGP_IPV4M_NODE, &no_aggregate_address_as_set_summary_cmd);
  install_element (BGP_IPV4M_NODE, &no_aggregate_address_summary_as_set_cmd);
  install_element (BGP_IPV4M_NODE, &no_aggregate_address_mask_cmd);
  install_element (BGP_IPV4M_NODE, &no_aggregate_address_mask_summary_only_cmd);
  install_element (BGP_IPV4M_NODE, &no_aggregate_address_mask_as_set_cmd);
  install_element (BGP_IPV4M_NODE, &no_aggregate_address_mask_as_set_summary_cmd);
  install_element (BGP_IPV4M_NODE, &no_aggregate_address_mask_summary_as_set_cmd);

  /* New config IPv6 BGP commands.  */
  install_element (BGP_IPV6_NODE, &ipv6_bgp_network_cmd);
  install_element (BGP_IPV6_NODE, &ipv6_bgp_network_route_map_cmd);
  install_element (BGP_IPV6_NODE, &no_ipv6_bgp_network_cmd);
  install_element (BGP_IPV6_NODE, &no_ipv6_bgp_network_route_map_cmd);

  install_element (BGP_IPV6_NODE, &ipv6_aggregate_address_cmd);
  install_element (BGP_IPV6_NODE, &ipv6_aggregate_address_summary_only_cmd);
  install_element (BGP_IPV6_NODE, &no_ipv6_aggregate_address_cmd);
  install_element (BGP_IPV6_NODE, &no_ipv6_aggregate_address_summary_only_cmd);

  install_element (BGP_IPV6M_NODE, &ipv6_bgp_network_cmd);
  install_element (BGP_IPV6M_NODE, &no_ipv6_bgp_network_cmd);

  /* Old config IPv6 BGP commands.  */
  install_element (BGP_NODE, &old_ipv6_bgp_network_cmd);
  install_element (BGP_NODE, &old_no_ipv6_bgp_network_cmd);

  install_element (BGP_NODE, &old_ipv6_aggregate_address_cmd);
  install_element (BGP_NODE, &old_ipv6_aggregate_address_summary_only_cmd);
  install_element (BGP_NODE, &old_no_ipv6_aggregate_address_cmd);
  install_element (BGP_NODE, &old_no_ipv6_aggregate_address_summary_only_cmd);

  install_element (BGP_NODE, &bgp_distance_cmd);
  install_element (BGP_NODE, &no_bgp_distance_cmd);
  install_element (BGP_NODE, &no_bgp_distance2_cmd);
  install_element (BGP_NODE, &bgp_distance_source_cmd);
  install_element (BGP_NODE, &no_bgp_distance_source_cmd);
  install_element (BGP_NODE, &bgp_distance_source_access_list_cmd);
  install_element (BGP_NODE, &no_bgp_distance_source_access_list_cmd);

  install_element (BGP_NODE, &bgp_damp_set_cmd);
  install_element (BGP_NODE, &bgp_damp_set2_cmd);
  install_element (BGP_NODE, &bgp_damp_set3_cmd);
  install_element (BGP_NODE, &bgp_damp_unset_cmd);
  install_element (BGP_NODE, &bgp_damp_unset2_cmd);
  install_element (BGP_IPV4_NODE, &bgp_damp_set_cmd);
  install_element (BGP_IPV4_NODE, &bgp_damp_set2_cmd);
  install_element (BGP_IPV4_NODE, &bgp_damp_set3_cmd);
  install_element (BGP_IPV4_NODE, &bgp_damp_unset_cmd);
  install_element (BGP_IPV4_NODE, &bgp_damp_unset2_cmd);
  
  /* Deprecated AS-Pathlimit commands */
  install_element (BGP_NODE, &bgp_network_ttl_cmd);
  install_element (BGP_NODE, &bgp_network_mask_ttl_cmd);
  install_element (BGP_NODE, &bgp_network_mask_natural_ttl_cmd);
  install_element (BGP_NODE, &bgp_network_backdoor_ttl_cmd);
  install_element (BGP_NODE, &bgp_network_mask_backdoor_ttl_cmd);
  install_element (BGP_NODE, &bgp_network_mask_natural_backdoor_ttl_cmd);
  
  install_element (BGP_NODE, &no_bgp_network_ttl_cmd);
  install_element (BGP_NODE, &no_bgp_network_mask_ttl_cmd);
  install_element (BGP_NODE, &no_bgp_network_mask_natural_ttl_cmd);
  install_element (BGP_NODE, &no_bgp_network_backdoor_ttl_cmd);
  install_element (BGP_NODE, &no_bgp_network_mask_backdoor_ttl_cmd);
  install_element (BGP_NODE, &no_bgp_network_mask_natural_backdoor_ttl_cmd);
  
  install_element (BGP_IPV4_NODE, &bgp_network_ttl_cmd);
  install_element (BGP_IPV4_NODE, &bgp_network_mask_ttl_cmd);
  install_element (BGP_IPV4_NODE, &bgp_network_mask_natural_ttl_cmd);
  install_element (BGP_IPV4_NODE, &bgp_network_backdoor_ttl_cmd);
  install_element (BGP_IPV4_NODE, &bgp_network_mask_backdoor_ttl_cmd);
  install_element (BGP_IPV4_NODE, &bgp_network_mask_natural_backdoor_ttl_cmd);
  
  install_element (BGP_IPV4_NODE, &no_bgp_network_ttl_cmd);
  install_element (BGP_IPV4_NODE, &no_bgp_network_mask_ttl_cmd);
  install_element (BGP_IPV4_NODE, &no_bgp_network_mask_natural_ttl_cmd);
  install_element (BGP_IPV4_NODE, &no_bgp_network_backdoor_ttl_cmd);
  install_element (BGP_IPV4_NODE, &no_bgp_network_mask_backdoor_ttl_cmd);
  install_element (BGP_IPV4_NODE, &no_bgp_network_mask_natural_backdoor_ttl_cmd);
  
  install_element (BGP_IPV4M_NODE, &bgp_network_ttl_cmd);
  install_element (BGP_IPV4M_NODE, &bgp_network_mask_ttl_cmd);
  install_element (BGP_IPV4M_NODE, &bgp_network_mask_natural_ttl_cmd);
  install_element (BGP_IPV4M_NODE, &bgp_network_backdoor_ttl_cmd);
  install_element (BGP_IPV4M_NODE, &bgp_network_mask_backdoor_ttl_cmd);
  install_element (BGP_IPV4M_NODE, &bgp_network_mask_natural_backdoor_ttl_cmd);
  
  install_element (BGP_IPV4M_NODE, &no_bgp_network_ttl_cmd);
  install_element (BGP_IPV4M_NODE, &no_bgp_network_mask_ttl_cmd);
  install_element (BGP_IPV4M_NODE, &no_bgp_network_mask_natural_ttl_cmd);
  install_element (BGP_IPV4M_NODE, &no_bgp_network_backdoor_ttl_cmd);
  install_element (BGP_IPV4M_NODE, &no_bgp_network_mask_backdoor_ttl_cmd);
  install_element (BGP_IPV4M_NODE, &no_bgp_network_mask_natural_backdoor_ttl_cmd);

#ifdef HAVE_IPV6
  install_element (BGP_IPV6_NODE, &ipv6_bgp_network_ttl_cmd);
  install_element (BGP_IPV6_NODE, &no_ipv6_bgp_network_ttl_cmd);
#endif
}

void
bgp_route_finish (void)
{
  bgp_table_unlock (bgp_distance_table);
  bgp_distance_table = NULL;
}
