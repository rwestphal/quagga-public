/* Functions used by the "show bgp ..." CLI commands.
   Copyright (C) 1996, 97, 98, 99, 2000 Kunihiro Ishiguro

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
#include "bgpd/bgp_mpath.h"
#include "bgpd/bgp_open.h"
#include "bgpd/bgp_vty.h"
#include "bgpd/bgp_vty_show.h"

/* Extern from bgp_dump.c */
extern const char *bgp_origin_str[];
extern const char *bgp_origin_long_str[];

static const char *table_stats_strs[] =
{
  [BGP_STATS_PREFIXES]            = "Total Prefixes",
  [BGP_STATS_TOTPLEN]             = "Average prefix length",
  [BGP_STATS_RIB]                 = "Total Advertisements",
  [BGP_STATS_UNAGGREGATEABLE]     = "Unaggregateable prefixes",
  [BGP_STATS_MAX_AGGREGATEABLE]   = "Maximum aggregateable prefixes",
  [BGP_STATS_AGGREGATES]          = "BGP Aggregate advertisements",
  [BGP_STATS_SPACE]               = "Address space advertised",
  [BGP_STATS_ASPATH_COUNT]        = "Advertisements with paths",
  [BGP_STATS_ASPATH_MAXHOPS]      = "Longest AS-Path (hops)",
  [BGP_STATS_ASPATH_MAXSIZE]      = "Largest AS-Path (bytes)",
  [BGP_STATS_ASPATH_TOTHOPS]      = "Average AS-Path length (hops)",
  [BGP_STATS_ASPATH_TOTSIZE]      = "Average AS-Path size (bytes)",
  [BGP_STATS_ASN_HIGHEST]         = "Highest public ASN",
  [BGP_STATS_MAX] = NULL,
};

static const char *pcount_strs[] =
{
  [PCOUNT_ADJ_IN]  = "Adj-in",
  [PCOUNT_DAMPED]  = "Damped",
  [PCOUNT_REMOVED] = "Removed",
  [PCOUNT_HISTORY] = "History",
  [PCOUNT_STALE]   = "Stale",
  [PCOUNT_VALID]   = "Valid",
  [PCOUNT_ALL]     = "All RIB",
  [PCOUNT_COUNTED] = "PfxCt counted",
  [PCOUNT_PFCNT]   = "Useable",
  [PCOUNT_MAX]     = NULL,
};

#define BGP_SHOW_SCODE_HEADER "Status codes: s suppressed, d damped, h history, * valid, > best, i - internal,%s              r RIB-failure, S Stale, R Removed%s"
#define BGP_SHOW_OCODE_HEADER "Origin codes: i - IGP, e - EGP, ? - incomplete%s%s"
#define BGP_SHOW_HEADER "   Network          Next Hop            Metric LocPrf Weight Path%s"
#define BGP_SHOW_DAMP_HEADER "   Network          From             Reuse    Path%s"
#define BGP_SHOW_FLAP_HEADER "   Network          From            Flaps Duration Reuse    Path%s"

/* Print the short form route status for a bgp_info */
static void
route_vty_short_status_out (struct vty *vty, struct bgp_info *binfo)
{
 /* Route status display. */
  if (CHECK_FLAG (binfo->flags, BGP_INFO_REMOVED))
    vty_out (vty, "R");
  else if (CHECK_FLAG (binfo->flags, BGP_INFO_STALE))
    vty_out (vty, "S");
  else if (binfo->extra && binfo->extra->suppress)
    vty_out (vty, "s");
  else if (! CHECK_FLAG (binfo->flags, BGP_INFO_HISTORY))
    vty_out (vty, "*");
  else
    vty_out (vty, " ");

  /* Selected */
  if (CHECK_FLAG (binfo->flags, BGP_INFO_HISTORY))
    vty_out (vty, "h");
  else if (CHECK_FLAG (binfo->flags, BGP_INFO_DAMPED))
    vty_out (vty, "d");
  else if (CHECK_FLAG (binfo->flags, BGP_INFO_SELECTED))
    vty_out (vty, ">");
  else
    vty_out (vty, " ");

  /* Internal route. */
    if ((binfo->peer->as) && (binfo->peer->as == binfo->peer->local_as))
      vty_out (vty, "i");
    else
      vty_out (vty, " ");
}

/* Static function to display route. */
static void
route_vty_out_route (struct prefix *p, struct vty *vty)
{
  int len;
  u_int32_t destination;
  char buf[BUFSIZ];

  if (p->family == AF_INET)
    {
      len = vty_out (vty, "%s", inet_ntop (p->family, &p->u.prefix, buf, BUFSIZ));
      destination = ntohl (p->u.prefix4.s_addr);

      if ((IN_CLASSC (destination) && p->prefixlen == 24)
	  || (IN_CLASSB (destination) && p->prefixlen == 16)
	  || (IN_CLASSA (destination) && p->prefixlen == 8)
	  || p->u.prefix4.s_addr == 0)
	{
	  /* When mask is natural, mask is not displayed. */
	}
      else
	len += vty_out (vty, "/%d", p->prefixlen);
    }
  else
    len = vty_out (vty, "%s/%d", inet_ntop (p->family, &p->u.prefix, buf, BUFSIZ),
		   p->prefixlen);

  len = 17 - len;
  if (len < 1)
    vty_out (vty, "%s%*s", VTY_NEWLINE, 20, " ");
  else
    vty_out (vty, "%*s", len, " ");
}

/* called from terminal list command */
static void
route_vty_out (struct vty *vty, struct prefix *p,
	       struct bgp_info *binfo, int display, safi_t safi)
{
  struct attr *attr;

  /* short status lead text */
  route_vty_short_status_out (vty, binfo);

  /* print prefix and mask */
  if (! display)
    route_vty_out_route (p, vty);
  else
    vty_out (vty, "%*s", 17, " ");

  /* Print attribute */
  attr = binfo->attr;
  if (attr)
    {
      if (p->family == AF_INET)
	{
	  if (safi == SAFI_MPLS_VPN)
	    vty_out (vty, "%-16s",
                     inet_ntoa (attr->extra->mp_nexthop_global_in));
	  else
	    vty_out (vty, "%-16s", inet_ntoa (attr->nexthop));
	}
#ifdef HAVE_IPV6
      else if (p->family == AF_INET6)
	{
	  int len;
	  char buf[BUFSIZ];

	  len = vty_out (vty, "%s",
			 inet_ntop (AF_INET6, &attr->extra->mp_nexthop_global,
			 buf, BUFSIZ));
	  len = 16 - len;
	  if (len < 1)
	    vty_out (vty, "%s%*s", VTY_NEWLINE, 36, " ");
	  else
	    vty_out (vty, "%*s", len, " ");
	}
#endif /* HAVE_IPV6 */

      if (attr->flag & ATTR_FLAG_BIT (BGP_ATTR_MULTI_EXIT_DISC))
	vty_out (vty, "%10u", attr->med);
      else
	vty_out (vty, "          ");

      if (attr->flag & ATTR_FLAG_BIT (BGP_ATTR_LOCAL_PREF))
	vty_out (vty, "%7u", attr->local_pref);
      else
	vty_out (vty, "       ");

      vty_out (vty, "%7u ", (attr->extra ? attr->extra->weight : 0));

      /* Print aspath */
      if (attr->aspath)
        aspath_print_vty (vty, "%s", attr->aspath, " ");

      /* Print origin */
      vty_out (vty, "%s", bgp_origin_str[attr->origin]);
    }
  vty_out (vty, "%s", VTY_NEWLINE);
}

/* called from terminal list command */
static void
route_vty_out_tmp (struct vty *vty, struct prefix *p,
		   struct attr *attr, safi_t safi)
{
  /* Route status display. */
  vty_out (vty, "*");
  vty_out (vty, ">");
  vty_out (vty, " ");

  /* print prefix and mask */
  route_vty_out_route (p, vty);

  /* Print attribute */
  if (attr)
    {
      if (p->family == AF_INET)
	{
	  if (safi == SAFI_MPLS_VPN)
	    vty_out (vty, "%-16s",
                     inet_ntoa (attr->extra->mp_nexthop_global_in));
	  else
	    vty_out (vty, "%-16s", inet_ntoa (attr->nexthop));
	}
#ifdef HAVE_IPV6
      else if (p->family == AF_INET6)
        {
          int len;
          char buf[BUFSIZ];

          assert (attr->extra);

          len = vty_out (vty, "%s",
                         inet_ntop (AF_INET6, &attr->extra->mp_nexthop_global,
                         buf, BUFSIZ));
          len = 16 - len;
          if (len < 1)
            vty_out (vty, "%s%*s", VTY_NEWLINE, 36, " ");
          else
            vty_out (vty, "%*s", len, " ");
        }
#endif /* HAVE_IPV6 */

      if (attr->flag & ATTR_FLAG_BIT (BGP_ATTR_MULTI_EXIT_DISC))
	vty_out (vty, "%10u", attr->med);
      else
	vty_out (vty, "          ");

      if (attr->flag & ATTR_FLAG_BIT (BGP_ATTR_LOCAL_PREF))
	vty_out (vty, "%7u", attr->local_pref);
      else
	vty_out (vty, "       ");

      vty_out (vty, "%7u ", (attr->extra ? attr->extra->weight : 0));

      /* Print aspath */
      if (attr->aspath)
        aspath_print_vty (vty, "%s", attr->aspath, " ");

      /* Print origin */
      vty_out (vty, "%s", bgp_origin_str[attr->origin]);
    }

  vty_out (vty, "%s", VTY_NEWLINE);
}

/* dampening route */
static void
damp_route_vty_out (struct vty *vty, struct prefix *p,
		    struct bgp_info *binfo, int display, safi_t safi)
{
  struct attr *attr;
  int len;
  char timebuf[BGP_UPTIME_LEN];

  /* short status lead text */
  route_vty_short_status_out (vty, binfo);

  /* print prefix and mask */
  if (! display)
    route_vty_out_route (p, vty);
  else
    vty_out (vty, "%*s", 17, " ");

  len = vty_out (vty, "%s", binfo->peer->host);
  len = 17 - len;
  if (len < 1)
    vty_out (vty, "%s%*s", VTY_NEWLINE, 34, " ");
  else
    vty_out (vty, "%*s", len, " ");

  vty_out (vty, "%s ", bgp_damp_reuse_time_vty (vty, binfo, timebuf, BGP_UPTIME_LEN));

  /* Print attribute */
  attr = binfo->attr;
  if (attr)
    {
      /* Print aspath */
      if (attr->aspath)
	aspath_print_vty (vty, "%s", attr->aspath, " ");

      /* Print origin */
      vty_out (vty, "%s", bgp_origin_str[attr->origin]);
    }
  vty_out (vty, "%s", VTY_NEWLINE);
}

/* flap route */
static void
flap_route_vty_out (struct vty *vty, struct prefix *p,
		    struct bgp_info *binfo, int display, safi_t safi)
{
  struct attr *attr;
  struct bgp_damp_info *bdi;
  char timebuf[BGP_UPTIME_LEN];
  int len;

  if (!binfo->extra)
    return;

  bdi = binfo->extra->damp_info;

  /* short status lead text */
  route_vty_short_status_out (vty, binfo);

  /* print prefix and mask */
  if (! display)
    route_vty_out_route (p, vty);
  else
    vty_out (vty, "%*s", 17, " ");

  len = vty_out (vty, "%s", binfo->peer->host);
  len = 16 - len;
  if (len < 1)
    vty_out (vty, "%s%*s", VTY_NEWLINE, 33, " ");
  else
    vty_out (vty, "%*s", len, " ");

  len = vty_out (vty, "%d", bdi->flap);
  len = 5 - len;
  if (len < 1)
    vty_out (vty, " ");
  else
    vty_out (vty, "%*s ", len, " ");

  vty_out (vty, "%s ", peer_uptime (bdi->start_time,
	   timebuf, BGP_UPTIME_LEN));

  if (CHECK_FLAG (binfo->flags, BGP_INFO_DAMPED)
      && ! CHECK_FLAG (binfo->flags, BGP_INFO_HISTORY))
    vty_out (vty, "%s ", bgp_damp_reuse_time_vty (vty, binfo, timebuf, BGP_UPTIME_LEN));
  else
    vty_out (vty, "%*s ", 8, " ");

  /* Print attribute */
  attr = binfo->attr;
  if (attr)
    {
      /* Print aspath */
      if (attr->aspath)
	aspath_print_vty (vty, "%s", attr->aspath, " ");

      /* Print origin */
      vty_out (vty, "%s", bgp_origin_str[attr->origin]);
    }
  vty_out (vty, "%s", VTY_NEWLINE);
}

static void
route_vty_out_tag (struct vty *vty, struct prefix *p,
		   struct bgp_info *binfo, int display, safi_t safi)
{
  struct attr *attr;
  u_int32_t label = 0;

  if (!binfo->extra)
    return;

  /* short status lead text */
  route_vty_short_status_out (vty, binfo);

  /* print prefix and mask */
  if (! display)
    route_vty_out_route (p, vty);
  else
    vty_out (vty, "%*s", 17, " ");

  /* Print attribute */
  attr = binfo->attr;
  if (attr)
    {
      if (p->family == AF_INET)
	{
	  if (safi == SAFI_MPLS_VPN)
	    vty_out (vty, "%-16s",
                     inet_ntoa (attr->extra->mp_nexthop_global_in));
	  else
	    vty_out (vty, "%-16s", inet_ntoa (attr->nexthop));
	}
#ifdef HAVE_IPV6
      else if (p->family == AF_INET6)
	{
	  assert (attr->extra);
	  char buf[BUFSIZ];
	  char buf1[BUFSIZ];
	  if (attr->extra->mp_nexthop_len == 16)
	    vty_out (vty, "%s",
		     inet_ntop (AF_INET6, &attr->extra->mp_nexthop_global,
                     buf, BUFSIZ));
	  else if (attr->extra->mp_nexthop_len == 32)
	    vty_out (vty, "%s(%s)",
		     inet_ntop (AF_INET6, &attr->extra->mp_nexthop_global,
		                buf, BUFSIZ),
		     inet_ntop (AF_INET6, &attr->extra->mp_nexthop_local,
		                buf1, BUFSIZ));

	}
#endif /* HAVE_IPV6 */
    }

  label = decode_label (binfo->extra->tag);

  vty_out (vty, "notag/%d", label);

  vty_out (vty, "%s", VTY_NEWLINE);
}

int
bgp_show_table (struct vty *vty, struct bgp_table *table, struct in_addr *router_id,
	  enum bgp_show_type type, void *output_arg)
{
  struct bgp_info *ri;
  struct bgp_node *rn;
  int header = 1;
  int display;
  unsigned long output_count;

  /* This is first entry point, so reset total line. */
  output_count = 0;

  /* Start processing of routes. */
  for (rn = bgp_table_top (table); rn; rn = bgp_route_next (rn))
    if (rn->info != NULL)
      {
	display = 0;

	for (ri = rn->info; ri; ri = ri->next)
	  {
	    if (type == bgp_show_type_flap_statistics
		|| type == bgp_show_type_flap_address
		|| type == bgp_show_type_flap_prefix
		|| type == bgp_show_type_flap_cidr_only
		|| type == bgp_show_type_flap_regexp
		|| type == bgp_show_type_flap_filter_list
		|| type == bgp_show_type_flap_prefix_list
		|| type == bgp_show_type_flap_prefix_longer
		|| type == bgp_show_type_flap_route_map
		|| type == bgp_show_type_flap_neighbor
		|| type == bgp_show_type_dampend_paths
		|| type == bgp_show_type_damp_neighbor)
	      {
		if (!(ri->extra && ri->extra->damp_info))
		  continue;
	      }
	    if (type == bgp_show_type_regexp
		|| type == bgp_show_type_flap_regexp)
	      {
		regex_t *regex = output_arg;

		if (bgp_regexec (regex, ri->attr->aspath) == REG_NOMATCH)
		  continue;
	      }
	    if (type == bgp_show_type_prefix_list
		|| type == bgp_show_type_flap_prefix_list)
	      {
		struct prefix_list *plist = output_arg;

		if (prefix_list_apply (plist, &rn->p) != PREFIX_PERMIT)
		  continue;
	      }
	    if (type == bgp_show_type_filter_list
		|| type == bgp_show_type_flap_filter_list)
	      {
		struct as_list *as_list = output_arg;

		if (as_list_apply (as_list, ri->attr->aspath) != AS_FILTER_PERMIT)
		  continue;
	      }
	    if (type == bgp_show_type_route_map
		|| type == bgp_show_type_flap_route_map)
	      {
		struct route_map *rmap = output_arg;
		struct bgp_info binfo;
		struct attr dummy_attr;
		struct attr_extra dummy_extra;
		int ret;

		dummy_attr.extra = &dummy_extra;
		bgp_attr_dup (&dummy_attr, ri->attr);

		binfo.peer = ri->peer;
		binfo.attr = &dummy_attr;

		ret = route_map_apply (rmap, &rn->p, RMAP_BGP, &binfo);
		if (ret == RMAP_DENYMATCH)
		  continue;
	      }
	    if (type == bgp_show_type_neighbor
		|| type == bgp_show_type_flap_neighbor
		|| type == bgp_show_type_damp_neighbor)
	      {
		union sockunion *su = output_arg;

		if (ri->peer->su_remote == NULL || ! sockunion_same(ri->peer->su_remote, su))
		  continue;
	      }
	    if (type == bgp_show_type_cidr_only
		|| type == bgp_show_type_flap_cidr_only)
	      {
		u_int32_t destination;

		destination = ntohl (rn->p.u.prefix4.s_addr);
		if (IN_CLASSC (destination) && rn->p.prefixlen == 24)
		  continue;
		if (IN_CLASSB (destination) && rn->p.prefixlen == 16)
		  continue;
		if (IN_CLASSA (destination) && rn->p.prefixlen == 8)
		  continue;
	      }
	    if (type == bgp_show_type_prefix_longer
		|| type == bgp_show_type_flap_prefix_longer)
	      {
		struct prefix *p = output_arg;

		if (! prefix_match (p, &rn->p))
		  continue;
	      }
	    if (type == bgp_show_type_community_all)
	      {
		if (! ri->attr->community)
		  continue;
	      }
	    if (type == bgp_show_type_community)
	      {
		struct community *com = output_arg;

		if (! ri->attr->community ||
		    ! community_match (ri->attr->community, com))
		  continue;
	      }
	    if (type == bgp_show_type_community_exact)
	      {
		struct community *com = output_arg;

		if (! ri->attr->community ||
		    ! community_cmp (ri->attr->community, com))
		  continue;
	      }
	    if (type == bgp_show_type_community_list)
	      {
		struct community_list *list = output_arg;

		if (! community_list_match (ri->attr->community, list))
		  continue;
	      }
	    if (type == bgp_show_type_community_list_exact)
	      {
		struct community_list *list = output_arg;

		if (! community_list_exact_match (ri->attr->community, list))
		  continue;
	      }
	    if (type == bgp_show_type_flap_address
		|| type == bgp_show_type_flap_prefix)
	      {
		struct prefix *p = output_arg;

		if (! prefix_match (&rn->p, p))
		  continue;

		if (type == bgp_show_type_flap_prefix)
		  if (p->prefixlen != rn->p.prefixlen)
		    continue;
	      }
	    if (type == bgp_show_type_dampend_paths
		|| type == bgp_show_type_damp_neighbor)
	      {
		if (! CHECK_FLAG (ri->flags, BGP_INFO_DAMPED)
		    || CHECK_FLAG (ri->flags, BGP_INFO_HISTORY))
		  continue;
	      }

	    if (header)
	      {
		vty_out (vty, "BGP table version is 0, local router ID is %s%s", inet_ntoa (*router_id), VTY_NEWLINE);
		vty_out (vty, BGP_SHOW_SCODE_HEADER, VTY_NEWLINE, VTY_NEWLINE);
		vty_out (vty, BGP_SHOW_OCODE_HEADER, VTY_NEWLINE, VTY_NEWLINE);
		if (type == bgp_show_type_dampend_paths
		    || type == bgp_show_type_damp_neighbor)
		  vty_out (vty, BGP_SHOW_DAMP_HEADER, VTY_NEWLINE);
		else if (type == bgp_show_type_flap_statistics
			 || type == bgp_show_type_flap_address
			 || type == bgp_show_type_flap_prefix
			 || type == bgp_show_type_flap_cidr_only
			 || type == bgp_show_type_flap_regexp
			 || type == bgp_show_type_flap_filter_list
			 || type == bgp_show_type_flap_prefix_list
			 || type == bgp_show_type_flap_prefix_longer
			 || type == bgp_show_type_flap_route_map
			 || type == bgp_show_type_flap_neighbor)
		  vty_out (vty, BGP_SHOW_FLAP_HEADER, VTY_NEWLINE);
		else
		  vty_out (vty, BGP_SHOW_HEADER, VTY_NEWLINE);
		header = 0;
	      }

	    if (type == bgp_show_type_dampend_paths
		|| type == bgp_show_type_damp_neighbor)
	      damp_route_vty_out (vty, &rn->p, ri, display, SAFI_UNICAST);
	    else if (type == bgp_show_type_flap_statistics
		     || type == bgp_show_type_flap_address
		     || type == bgp_show_type_flap_prefix
		     || type == bgp_show_type_flap_cidr_only
		     || type == bgp_show_type_flap_regexp
		     || type == bgp_show_type_flap_filter_list
		     || type == bgp_show_type_flap_prefix_list
		     || type == bgp_show_type_flap_prefix_longer
		     || type == bgp_show_type_flap_route_map
		     || type == bgp_show_type_flap_neighbor)
	      flap_route_vty_out (vty, &rn->p, ri, display, SAFI_UNICAST);
	    else
	      route_vty_out (vty, &rn->p, ri, display, SAFI_UNICAST);
	    display++;
	  }
	if (display)
	  output_count++;
      }

  /* No route is displayed */
  if (output_count == 0)
    {
      if (type == bgp_show_type_normal)
	vty_out (vty, "No BGP network exists%s", VTY_NEWLINE);
    }
  else
    vty_out (vty, "%sTotal number of prefixes %ld%s",
	     VTY_NEWLINE, output_count, VTY_NEWLINE);

  return CMD_SUCCESS;
}

int
bgp_show (struct vty *vty, struct bgp *bgp, afi_t afi, safi_t safi,
         enum bgp_show_type type, void *output_arg)
{
  struct bgp_table *table;

  if (bgp == NULL) {
    bgp = bgp_get_default ();
  }

  if (bgp == NULL)
    {
      vty_out (vty, "No BGP process is configured%s", VTY_NEWLINE);
      return CMD_WARNING;
    }


  table = bgp->rib[afi][safi];

  return bgp_show_table (vty, table, &bgp->router_id, type, output_arg);
}

int
bgp_show_prefix_list (struct vty *vty, const char *prefix_list_str, afi_t afi,
		      safi_t safi, enum bgp_show_type type)
{
  struct prefix_list *plist;

  plist = prefix_list_lookup (afi, prefix_list_str);
  if (plist == NULL)
    {
      vty_out (vty, "%% %s is not a valid prefix-list name%s",
               prefix_list_str, VTY_NEWLINE);
      return CMD_WARNING;
    }

  return bgp_show (vty, NULL, afi, safi, type, plist);
}

int
bgp_show_filter_list (struct vty *vty, const char *filter, afi_t afi,
		      safi_t safi, enum bgp_show_type type)
{
  struct as_list *as_list;

  as_list = as_list_lookup (filter);
  if (as_list == NULL)
    {
      vty_out (vty, "%% %s is not a valid AS-path access-list name%s", filter, VTY_NEWLINE);
      return CMD_WARNING;
    }

  return bgp_show (vty, NULL, afi, safi, type, as_list);
}

int
bgp_show_regexp (struct vty *vty, int argc, const char **argv, afi_t afi,
		 safi_t safi, enum bgp_show_type type)
{
  int i;
  struct buffer *b;
  char *regstr;
  int first;
  regex_t *regex;
  int rc;

  first = 0;
  b = buffer_new (1024);
  for (i = 0; i < argc; i++)
    {
      if (first)
	buffer_putc (b, ' ');
      else
	{
	  if ((strcmp (argv[i], "unicast") == 0) || (strcmp (argv[i], "multicast") == 0))
	    continue;
	  first = 1;
	}

      buffer_putstr (b, argv[i]);
    }
  buffer_putc (b, '\0');

  regstr = buffer_getstr (b);
  buffer_free (b);

  regex = bgp_regcomp (regstr);
  XFREE(MTYPE_TMP, regstr);
  if (! regex)
    {
      vty_out (vty, "Can't compile regexp %s%s", argv[0],
	       VTY_NEWLINE);
      return CMD_WARNING;
    }

  rc = bgp_show (vty, NULL, afi, safi, type, regex);
  bgp_regex_free (regex);
  return rc;
}

int
bgp_show_route_map (struct vty *vty, const char *rmap_str, afi_t afi,
		    safi_t safi, enum bgp_show_type type)
{
  struct route_map *rmap;

  rmap = route_map_lookup_by_name (rmap_str);
  if (! rmap)
    {
      vty_out (vty, "%% %s is not a valid route-map name%s",
	       rmap_str, VTY_NEWLINE);
      return CMD_WARNING;
    }

  return bgp_show (vty, NULL, afi, safi, type, rmap);
}

int
bgp_show_neighbor_route (struct vty *vty, struct peer *peer, afi_t afi,
			 safi_t safi, enum bgp_show_type type)
{
  if (! peer || ! peer->afc[afi][safi])
    {
      vty_out (vty, "%% No such neighbor or address family%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  return bgp_show (vty, peer->bgp, afi, safi, type, &peer->su);
}

int
bgp_show_prefix_longer (struct vty *vty, const char *prefix, afi_t afi,
			safi_t safi, enum bgp_show_type type)
{
  int ret;
  struct prefix *p;

  p = prefix_new();

  ret = str2prefix (prefix, p);
  if (! ret)
    {
      vty_out (vty, "%% Malformed Prefix%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  ret = bgp_show (vty, NULL, afi, safi, type, p);
  prefix_free(p);
  return ret;
}

int
bgp_show_community (struct vty *vty, const char *view_name, int argc,
		    const char **argv, int exact, afi_t afi, safi_t safi)
{
  struct community *com;
  struct buffer *b;
  struct bgp *bgp;
  int i;
  char *str;
  int first = 0;

  /* BGP structure lookup */
  if (view_name)
    {
      bgp = bgp_lookup_by_name (view_name);
      if (bgp == NULL)
	{
	  vty_out (vty, "Can't find BGP view %s%s", view_name, VTY_NEWLINE);
	  return CMD_WARNING;
	}
    }
  else
    {
      bgp = bgp_get_default ();
      if (bgp == NULL)
	{
	  vty_out (vty, "No BGP process is configured%s", VTY_NEWLINE);
	  return CMD_WARNING;
	}
    }

  b = buffer_new (1024);
  for (i = 0; i < argc; i++)
    {
      if (first)
        buffer_putc (b, ' ');
      else
	{
	  if ((strcmp (argv[i], "unicast") == 0) || (strcmp (argv[i], "multicast") == 0))
	    continue;
	  first = 1;
	}

      buffer_putstr (b, argv[i]);
    }
  buffer_putc (b, '\0');

  str = buffer_getstr (b);
  buffer_free (b);

  com = community_str2com (str);
  XFREE (MTYPE_TMP, str);
  if (! com)
    {
      vty_out (vty, "%% Community malformed: %s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  return bgp_show (vty, bgp, afi, safi,
                   (exact ? bgp_show_type_community_exact :
		            bgp_show_type_community), com);
}

int
bgp_show_community_list (struct vty *vty, const char *com, int exact,
			 afi_t afi, safi_t safi)
{
  struct community_list *list;

  list = community_list_lookup (bgp_clist, com, COMMUNITY_LIST_MASTER);
  if (list == NULL)
    {
      vty_out (vty, "%% %s is not a valid community-list name%s", com,
	       VTY_NEWLINE);
      return CMD_WARNING;
    }

  return bgp_show (vty, NULL, afi, safi,
                   (exact ? bgp_show_type_community_list_exact :
		            bgp_show_type_community_list), list);
}

static void
show_adj_route (struct vty *vty, struct peer *peer, afi_t afi, safi_t safi,
		int in)
{
  struct bgp_table *table;
  struct bgp_adj_in *ain;
  struct bgp_adj_out *adj;
  unsigned long output_count;
  struct bgp_node *rn;
  int header1 = 1;
  struct bgp *bgp;
  int header2 = 1;

  bgp = peer->bgp;

  if (! bgp)
    return;

  table = bgp->rib[afi][safi];

  output_count = 0;

  if (! in && CHECK_FLAG (peer->af_sflags[afi][safi],
			  PEER_STATUS_DEFAULT_ORIGINATE))
    {
      vty_out (vty, "BGP table version is 0, local router ID is %s%s", inet_ntoa (bgp->router_id), VTY_NEWLINE);
      vty_out (vty, BGP_SHOW_SCODE_HEADER, VTY_NEWLINE, VTY_NEWLINE);
      vty_out (vty, BGP_SHOW_OCODE_HEADER, VTY_NEWLINE, VTY_NEWLINE);

      vty_out (vty, "Originating default network 0.0.0.0%s%s",
	       VTY_NEWLINE, VTY_NEWLINE);
      header1 = 0;
    }

  for (rn = bgp_table_top (table); rn; rn = bgp_route_next (rn))
    if (in)
      {
	for (ain = rn->adj_in; ain; ain = ain->next)
	  if (ain->peer == peer)
	    {
	      if (header1)
		{
		  vty_out (vty, "BGP table version is 0, local router ID is %s%s", inet_ntoa (bgp->router_id), VTY_NEWLINE);
		  vty_out (vty, BGP_SHOW_SCODE_HEADER, VTY_NEWLINE, VTY_NEWLINE);
		  vty_out (vty, BGP_SHOW_OCODE_HEADER, VTY_NEWLINE, VTY_NEWLINE);
		  header1 = 0;
		}
	      if (header2)
		{
		  vty_out (vty, BGP_SHOW_HEADER, VTY_NEWLINE);
		  header2 = 0;
		}
	      if (ain->attr)
		{
		  route_vty_out_tmp (vty, &rn->p, ain->attr, safi);
		  output_count++;
		}
	    }
      }
    else
      {
	for (adj = rn->adj_out; adj; adj = adj->next)
	  if (adj->peer == peer)
	    {
	      if (header1)
		{
		  vty_out (vty, "BGP table version is 0, local router ID is %s%s", inet_ntoa (bgp->router_id), VTY_NEWLINE);
		  vty_out (vty, BGP_SHOW_SCODE_HEADER, VTY_NEWLINE, VTY_NEWLINE);
		  vty_out (vty, BGP_SHOW_OCODE_HEADER, VTY_NEWLINE, VTY_NEWLINE);
		  header1 = 0;
		}
	      if (header2)
		{
		  vty_out (vty, BGP_SHOW_HEADER, VTY_NEWLINE);
		  header2 = 0;
		}
	      if (adj->attr)
		{
		  route_vty_out_tmp (vty, &rn->p, adj->attr, safi);
		  output_count++;
		}
	    }
      }

  if (output_count != 0)
    vty_out (vty, "%sTotal number of prefixes %ld%s",
	     VTY_NEWLINE, output_count, VTY_NEWLINE);
}

int
peer_adj_routes (struct vty *vty, struct peer *peer, afi_t afi, safi_t safi, int in)
{
  if (! peer || ! peer->afc[afi][safi])
    {
      vty_out (vty, "%% No such neighbor or address family%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  if (in && ! CHECK_FLAG (peer->af_flags[afi][safi], PEER_FLAG_SOFT_RECONFIG))
    {
      vty_out (vty, "%% Inbound soft reconfiguration not enabled%s",
	       VTY_NEWLINE);
      return CMD_WARNING;
    }

  show_adj_route (vty, peer, afi, safi, in);

  return CMD_SUCCESS;
}

int
show_adj_route_vpn (struct vty *vty, struct peer *peer, struct prefix_rd *prd)
{
  struct bgp *bgp;
  struct bgp_table *table;
  struct bgp_node *rn;
  struct bgp_node *rm;
  struct attr *attr;
  int rd_header;
  int header = 1;
  char v4_header[] = "   Network          Next Hop            Metric LocPrf Weight Path%s";

  bgp = bgp_get_default ();
  if (bgp == NULL)
    {
      vty_out (vty, "No BGP process is configured%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  for (rn = bgp_table_top (bgp->rib[AFI_IP][SAFI_MPLS_VPN]); rn;
       rn = bgp_route_next (rn))
    {
      if (prd && memcmp (rn->p.u.val, prd->val, 8) != 0)
        continue;

      if ((table = rn->info) != NULL)
        {
          rd_header = 1;

          for (rm = bgp_table_top (table); rm; rm = bgp_route_next (rm))
            if ((attr = rm->info) != NULL)
              {
                if (header)
                  {
                    vty_out (vty, "BGP table version is 0, local router ID is %s%s",
                             inet_ntoa (bgp->router_id), VTY_NEWLINE);
                    vty_out (vty, "Status codes: s suppressed, d damped, h history, * valid, > best, i - internal%s",
                             VTY_NEWLINE);
                    vty_out (vty, "Origin codes: i - IGP, e - EGP, ? - incomplete%s%s",
                             VTY_NEWLINE, VTY_NEWLINE);
                    vty_out (vty, v4_header, VTY_NEWLINE);
                    header = 0;
                  }

                if (rd_header)
                  {
                    u_int16_t type;
                    struct rd_as rd_as;
                    struct rd_ip rd_ip;
                    u_char *pnt;

                    pnt = rn->p.u.val;

                    /* Decode RD type. */
                    type = decode_rd_type (pnt);
                    /* Decode RD value. */
                    if (type == RD_TYPE_AS)
                      decode_rd_as (pnt + 2, &rd_as);
                    else if (type == RD_TYPE_IP)
                      decode_rd_ip (pnt + 2, &rd_ip);

                    vty_out (vty, "Route Distinguisher: ");

                    if (type == RD_TYPE_AS)
                      vty_out (vty, "%u:%d", rd_as.as, rd_as.val);
                    else if (type == RD_TYPE_IP)
                      vty_out (vty, "%s:%d", inet_ntoa (rd_ip.ip), rd_ip.val);

                    vty_out (vty, "%s", VTY_NEWLINE);
                    rd_header = 0;
                  }
                route_vty_out_tmp (vty, &rm->p, attr, SAFI_MPLS_VPN);
              }
        }
    }
  return CMD_SUCCESS;
}

int
bgp_show_mpls_vpn (struct vty *vty, struct prefix_rd *prd, enum bgp_show_type type,
		   void *output_arg, int tags)
{
  struct bgp *bgp;
  struct bgp_table *table;
  struct bgp_node *rn;
  struct bgp_node *rm;
  struct bgp_info *ri;
  int rd_header;
  int header = 1;
  char v4_header[] = "   Network          Next Hop            Metric LocPrf Weight Path%s";
  char v4_header_tag[] = "   Network          Next Hop      In tag/Out tag%s";

  bgp = bgp_get_default ();
  if (bgp == NULL)
    {
      vty_out (vty, "No BGP process is configured%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  for (rn = bgp_table_top (bgp->rib[AFI_IP][SAFI_MPLS_VPN]); rn; rn = bgp_route_next (rn))
    {
      if (prd && memcmp (rn->p.u.val, prd->val, 8) != 0)
	continue;

      if ((table = rn->info) != NULL)
	{
	  rd_header = 1;

	  for (rm = bgp_table_top (table); rm; rm = bgp_route_next (rm))
	    for (ri = rm->info; ri; ri = ri->next)
	      {
		if (type == bgp_show_type_neighbor)
		  {
		    union sockunion *su = output_arg;

		    if (ri->peer->su_remote == NULL || ! sockunion_same(ri->peer->su_remote, su))
		      continue;
		  }
		if (header)
		  {
		    if (tags)
		      vty_out (vty, v4_header_tag, VTY_NEWLINE);
		    else
		      {
			vty_out (vty, "BGP table version is 0, local router ID is %s%s",
				 inet_ntoa (bgp->router_id), VTY_NEWLINE);
			vty_out (vty, "Status codes: s suppressed, d damped, h history, * valid, > best, i - internal%s",
				 VTY_NEWLINE);
			vty_out (vty, "Origin codes: i - IGP, e - EGP, ? - incomplete%s%s",
				 VTY_NEWLINE, VTY_NEWLINE);
			vty_out (vty, v4_header, VTY_NEWLINE);
		      }
		    header = 0;
		  }

		if (rd_header)
		  {
		    u_int16_t type;
		    struct rd_as rd_as;
		    struct rd_ip rd_ip;
		    u_char *pnt;

		    pnt = rn->p.u.val;

		    /* Decode RD type. */
		    type = decode_rd_type (pnt);
		    /* Decode RD value. */
		    if (type == RD_TYPE_AS)
		      decode_rd_as (pnt + 2, &rd_as);
		    else if (type == RD_TYPE_IP)
		      decode_rd_ip (pnt + 2, &rd_ip);

		    vty_out (vty, "Route Distinguisher: ");

		    if (type == RD_TYPE_AS)
		      vty_out (vty, "%u:%d", rd_as.as, rd_as.val);
		    else if (type == RD_TYPE_IP)
		      vty_out (vty, "%s:%d", inet_ntoa (rd_ip.ip), rd_ip.val);

		    vty_out (vty, "%s", VTY_NEWLINE);
		    rd_header = 0;
		  }
	        if (tags)
		  route_vty_out_tag (vty, &rm->p, ri, 0, SAFI_MPLS_VPN);
	        else
		  route_vty_out (vty, &rm->p, ri, 0, SAFI_MPLS_VPN);
	      }
        }
    }
  return CMD_SUCCESS;
}

/* Header of detailed BGP route information */
static void
route_vty_out_detail_header (struct vty *vty, struct bgp *bgp,
			     struct bgp_node *rn,
                             struct prefix_rd *prd, afi_t afi, safi_t safi)
{
  struct bgp_info *ri;
  struct prefix *p;
  struct peer *peer;
  struct listnode *node, *nnode;
  char buf1[INET6_ADDRSTRLEN];
  char buf2[INET6_ADDRSTRLEN];
  int count = 0;
  int best = 0;
  int suppress = 0;
  int no_export = 0;
  int no_advertise = 0;
  int local_as = 0;
  int first = 0;

  p = &rn->p;
  vty_out (vty, "BGP routing table entry for %s%s%s/%d%s",
	   (safi == SAFI_MPLS_VPN ?
	   prefix_rd2str (prd, buf1, RD_ADDRSTRLEN) : ""),
	   safi == SAFI_MPLS_VPN ? ":" : "",
	   inet_ntop (p->family, &p->u.prefix, buf2, INET6_ADDRSTRLEN),
	   p->prefixlen, VTY_NEWLINE);

  for (ri = rn->info; ri; ri = ri->next)
    {
      count++;
      if (CHECK_FLAG (ri->flags, BGP_INFO_SELECTED))
	{
	  best = count;
	  if (ri->extra && ri->extra->suppress)
	    suppress = 1;
	  if (ri->attr->community != NULL)
	    {
	      if (community_include (ri->attr->community, COMMUNITY_NO_ADVERTISE))
		no_advertise = 1;
	      if (community_include (ri->attr->community, COMMUNITY_NO_EXPORT))
		no_export = 1;
	      if (community_include (ri->attr->community, COMMUNITY_LOCAL_AS))
		local_as = 1;
	    }
	}
    }

  vty_out (vty, "Paths: (%d available", count);
  if (best)
    {
      vty_out (vty, ", best #%d", best);
      if (safi == SAFI_UNICAST)
	vty_out (vty, ", table Default-IP-Routing-Table");
    }
  else
    vty_out (vty, ", no best path");
  if (no_advertise)
    vty_out (vty, ", not advertised to any peer");
  else if (no_export)
    vty_out (vty, ", not advertised to EBGP peer");
  else if (local_as)
    vty_out (vty, ", not advertised outside local AS");
  if (suppress)
    vty_out (vty, ", Advertisements suppressed by an aggregate.");
  vty_out (vty, ")%s", VTY_NEWLINE);

  /* advertised peer */
  for (ALL_LIST_ELEMENTS (bgp->peer, node, nnode, peer))
    {
      if (bgp_adj_out_lookup (peer, p, afi, safi, rn))
	{
	  if (! first)
	    vty_out (vty, "  Advertised to non peer-group peers:%s ", VTY_NEWLINE);
	  vty_out (vty, " %s", sockunion2str (&peer->su, buf1, SU_ADDRSTRLEN));
	  first = 1;
	}
    }
  if (! first)
    vty_out (vty, "  Not advertised to any peer");
  vty_out (vty, "%s", VTY_NEWLINE);
}

static void
route_vty_out_detail (struct vty *vty, struct bgp *bgp, struct prefix *p,
		      struct bgp_info *binfo, afi_t afi, safi_t safi)
{
  char buf[INET6_ADDRSTRLEN];
  char buf1[BUFSIZ];
  struct attr *attr;
  int sockunion_vty_out (struct vty *, union sockunion *);
#ifdef HAVE_CLOCK_MONOTONIC
  time_t tbuf;
#endif

  attr = binfo->attr;

  if (attr)
    {
      /* Line1 display AS-path, Aggregator */
      if (attr->aspath)
	{
	  vty_out (vty, "  ");
	  if (aspath_count_hops (attr->aspath) == 0)
	    vty_out (vty, "Local");
	  else
	    aspath_print_vty (vty, "%s", attr->aspath, "");
	}

      if (CHECK_FLAG (binfo->flags, BGP_INFO_REMOVED))
        vty_out (vty, ", (removed)");
      if (CHECK_FLAG (binfo->flags, BGP_INFO_STALE))
	vty_out (vty, ", (stale)");
      if (CHECK_FLAG (attr->flag, ATTR_FLAG_BIT (BGP_ATTR_AGGREGATOR)))
	vty_out (vty, ", (aggregated by %u %s)",
	         attr->extra->aggregator_as,
		 inet_ntoa (attr->extra->aggregator_addr));
      if (CHECK_FLAG (binfo->peer->af_flags[afi][safi], PEER_FLAG_REFLECTOR_CLIENT))
	vty_out (vty, ", (Received from a RR-client)");
      if (CHECK_FLAG (binfo->peer->af_flags[afi][safi], PEER_FLAG_RSERVER_CLIENT))
	vty_out (vty, ", (Received from a RS-client)");
      if (CHECK_FLAG (binfo->flags, BGP_INFO_HISTORY))
	vty_out (vty, ", (history entry)");
      else if (CHECK_FLAG (binfo->flags, BGP_INFO_DAMPED))
	vty_out (vty, ", (suppressed due to dampening)");
      vty_out (vty, "%s", VTY_NEWLINE);

      /* Line2 display Next-hop, Neighbor, Router-id */
      if (p->family == AF_INET)
	{
	  vty_out (vty, "    %s", safi == SAFI_MPLS_VPN ?
		   inet_ntoa (attr->extra->mp_nexthop_global_in) :
		   inet_ntoa (attr->nexthop));
	}
#ifdef HAVE_IPV6
      else
	{
	  assert (attr->extra);
	  vty_out (vty, "    %s",
		   inet_ntop (AF_INET6, &attr->extra->mp_nexthop_global,
			      buf, INET6_ADDRSTRLEN));
	}
#endif /* HAVE_IPV6 */

      if (binfo->peer == bgp->peer_self)
	{
	  vty_out (vty, " from %s ",
		   p->family == AF_INET ? "0.0.0.0" : "::");
	  vty_out (vty, "(%s)", inet_ntoa(bgp->router_id));
	}
      else
	{
	  if (! CHECK_FLAG (binfo->flags, BGP_INFO_VALID))
	    vty_out (vty, " (inaccessible)");
	  else if (binfo->extra && binfo->extra->igpmetric)
	    vty_out (vty, " (metric %u)", binfo->extra->igpmetric);
	  vty_out (vty, " from %s", sockunion2str (&binfo->peer->su, buf, SU_ADDRSTRLEN));
	  if (attr->flag & ATTR_FLAG_BIT(BGP_ATTR_ORIGINATOR_ID))
	    vty_out (vty, " (%s)", inet_ntoa (attr->extra->originator_id));
	  else
	    vty_out (vty, " (%s)", inet_ntop (AF_INET, &binfo->peer->remote_id, buf1, BUFSIZ));
	}
      vty_out (vty, "%s", VTY_NEWLINE);

#ifdef HAVE_IPV6
      /* display nexthop local */
      if (attr->extra && attr->extra->mp_nexthop_len == 32)
	{
	  vty_out (vty, "    (%s)%s",
		   inet_ntop (AF_INET6, &attr->extra->mp_nexthop_local,
			      buf, INET6_ADDRSTRLEN),
		   VTY_NEWLINE);
	}
#endif /* HAVE_IPV6 */

      /* Line 3 display Origin, Med, Locpref, Weight, valid, Int/Ext/Local, Atomic, best */
      vty_out (vty, "      Origin %s", bgp_origin_long_str[attr->origin]);

      if (attr->flag & ATTR_FLAG_BIT(BGP_ATTR_MULTI_EXIT_DISC))
	vty_out (vty, ", metric %u", attr->med);

      if (attr->flag & ATTR_FLAG_BIT(BGP_ATTR_LOCAL_PREF))
	vty_out (vty, ", localpref %u", attr->local_pref);
      else
	vty_out (vty, ", localpref %u", bgp->default_local_pref);

      if (attr->extra && attr->extra->weight != 0)
	vty_out (vty, ", weight %u", attr->extra->weight);

      if (! CHECK_FLAG (binfo->flags, BGP_INFO_HISTORY))
	vty_out (vty, ", valid");

      if (binfo->peer != bgp->peer_self)
	{
	  if (binfo->peer->as == binfo->peer->local_as)
	    vty_out (vty, ", internal");
	  else
	    vty_out (vty, ", %s",
		     (bgp_confederation_peers_check(bgp, binfo->peer->as) ? "confed-external" : "external"));
	}
      else if (binfo->sub_type == BGP_ROUTE_AGGREGATE)
	vty_out (vty, ", aggregated, local");
      else if (binfo->type != ZEBRA_ROUTE_BGP)
	vty_out (vty, ", sourced");
      else
	vty_out (vty, ", sourced, local");

      if (attr->flag & ATTR_FLAG_BIT(BGP_ATTR_ATOMIC_AGGREGATE))
	vty_out (vty, ", atomic-aggregate");

      if (CHECK_FLAG (binfo->flags, BGP_INFO_MULTIPATH) ||
	  (CHECK_FLAG (binfo->flags, BGP_INFO_SELECTED) &&
	   bgp_info_mpath_count (binfo)))
	vty_out (vty, ", multipath");

      if (CHECK_FLAG (binfo->flags, BGP_INFO_SELECTED))
	vty_out (vty, ", best");

      vty_out (vty, "%s", VTY_NEWLINE);

      /* Line 4 display Community */
      if (attr->community)
	vty_out (vty, "      Community: %s%s", attr->community->str,
		 VTY_NEWLINE);

      /* Line 5 display Extended-community */
      if (attr->flag & ATTR_FLAG_BIT(BGP_ATTR_EXT_COMMUNITIES))
	vty_out (vty, "      Extended Community: %s%s",
	         attr->extra->ecommunity->str, VTY_NEWLINE);

      /* Line 6 display Originator, Cluster-id */
      if ((attr->flag & ATTR_FLAG_BIT(BGP_ATTR_ORIGINATOR_ID)) ||
	  (attr->flag & ATTR_FLAG_BIT(BGP_ATTR_CLUSTER_LIST)))
	{
	  assert (attr->extra);
	  if (attr->flag & ATTR_FLAG_BIT(BGP_ATTR_ORIGINATOR_ID))
	    vty_out (vty, "      Originator: %s",
	             inet_ntoa (attr->extra->originator_id));

	  if (attr->flag & ATTR_FLAG_BIT(BGP_ATTR_CLUSTER_LIST))
	    {
	      int i;
	      vty_out (vty, ", Cluster list: ");
	      for (i = 0; i < attr->extra->cluster->length / 4; i++)
		vty_out (vty, "%s ",
		         inet_ntoa (attr->extra->cluster->list[i]));
	    }
	  vty_out (vty, "%s", VTY_NEWLINE);
	}

      if (binfo->extra && binfo->extra->damp_info)
	bgp_damp_info_vty (vty, binfo);

      /* Line 7 display Uptime */
#ifdef HAVE_CLOCK_MONOTONIC
      tbuf = time(NULL) - (bgp_clock() - binfo->uptime);
      vty_out (vty, "      Last update: %s", ctime(&tbuf));
#else
      vty_out (vty, "      Last update: %s", ctime(&binfo->uptime));
#endif /* HAVE_CLOCK_MONOTONIC */
    }
  vty_out (vty, "%s", VTY_NEWLINE);
}

/* Display specified route of BGP table. */
int
bgp_show_route_in_table (struct vty *vty, struct bgp *bgp,
                         struct bgp_table *rib, const char *ip_str,
                         afi_t afi, safi_t safi, struct prefix_rd *prd,
                         int prefix_check)
{
  int ret;
  int header;
  int display = 0;
  struct prefix match;
  struct bgp_node *rn;
  struct bgp_node *rm;
  struct bgp_info *ri;
  struct bgp_table *table;

  /* Check IP address argument. */
  ret = str2prefix (ip_str, &match);
  if (! ret)
    {
      vty_out (vty, "address is malformed%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  match.family = afi2family (afi);

  if (safi == SAFI_MPLS_VPN)
    {
      for (rn = bgp_table_top (rib); rn; rn = bgp_route_next (rn))
        {
          if (prd && memcmp (rn->p.u.val, prd->val, 8) != 0)
            continue;

          if ((table = rn->info) != NULL)
            {
              header = 1;

              if ((rm = bgp_node_match (table, &match)) != NULL)
                {
                  if (prefix_check && rm->p.prefixlen != match.prefixlen)
                    {
                      bgp_unlock_node (rm);
                      continue;
                    }

                  for (ri = rm->info; ri; ri = ri->next)
                    {
                      if (header)
                        {
                          route_vty_out_detail_header (vty, bgp, rm, (struct prefix_rd *)&rn->p,
                                                       AFI_IP, SAFI_MPLS_VPN);

                          header = 0;
                        }
                      display++;
                      route_vty_out_detail (vty, bgp, &rm->p, ri, AFI_IP, SAFI_MPLS_VPN);
                    }

                  bgp_unlock_node (rm);
                }
            }
        }
    }
  else
    {
      header = 1;

      if ((rn = bgp_node_match (rib, &match)) != NULL)
        {
          if (! prefix_check || rn->p.prefixlen == match.prefixlen)
            {
              for (ri = rn->info; ri; ri = ri->next)
                {
                  if (header)
                    {
                      route_vty_out_detail_header (vty, bgp, rn, NULL, afi, safi);
                      header = 0;
                    }
                  display++;
                  route_vty_out_detail (vty, bgp, &rn->p, ri, afi, safi);
                }
            }

          bgp_unlock_node (rn);
        }
    }

  if (! display)
    {
      vty_out (vty, "%% Network not in table%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  return CMD_SUCCESS;
}

/* Display specified route of Main RIB */
int
bgp_show_route (struct vty *vty, const char *view_name, const char *ip_str,
		afi_t afi, safi_t safi, struct prefix_rd *prd,
		int prefix_check)
{
  struct bgp *bgp;

  /* BGP structure lookup. */
  if (view_name)
    {
      bgp = bgp_lookup_by_name (view_name);
      if (bgp == NULL)
	{
	  vty_out (vty, "Can't find BGP view %s%s", view_name, VTY_NEWLINE);
	  return CMD_WARNING;
	}
    }
  else
    {
      bgp = bgp_get_default ();
      if (bgp == NULL)
	{
	  vty_out (vty, "No BGP process is configured%s", VTY_NEWLINE);
	  return CMD_WARNING;
	}
    }

  return bgp_show_route_in_table (vty, bgp, bgp->rib[afi][safi], ip_str,
                                   afi, safi, prd, prefix_check);
}

struct peer *
peer_lookup_in_view (struct vty *vty, const char *view_name,
                     const char *ip_str)
{
  int ret;
  struct bgp *bgp;
  struct peer *peer;
  union sockunion su;

  /* BGP structure lookup. */
  if (view_name)
    {
      bgp = bgp_lookup_by_name (view_name);
      if (! bgp)
        {
          vty_out (vty, "Can't find BGP view %s%s", view_name, VTY_NEWLINE);
          return NULL;
        }
    }
  else
    {
      bgp = bgp_get_default ();
      if (! bgp)
        {
          vty_out (vty, "No BGP process is configured%s", VTY_NEWLINE);
          return NULL;
        }
    }

  /* Get peer sockunion. */
  ret = str2sockunion (ip_str, &su);
  if (ret < 0)
    {
      vty_out (vty, "Malformed address: %s%s", ip_str, VTY_NEWLINE);
      return NULL;
    }

  /* Peer structure lookup. */
  peer = peer_lookup (bgp, &su);
  if (! peer)
    {
      vty_out (vty, "No such neighbor%s", VTY_NEWLINE);
      return NULL;
    }

  return peer;
}

static int
bgp_table_stats_walker (struct thread *t)
{
  struct bgp_node *rn;
  struct bgp_node *top;
  struct bgp_table_stats *ts = THREAD_ARG (t);
  unsigned int space = 0;

  if (!(top = bgp_table_top (ts->table)))
    return 0;

  switch (top->p.family)
    {
      case AF_INET:
        space = IPV4_MAX_BITLEN;
        break;
      case AF_INET6:
        space = IPV6_MAX_BITLEN;
        break;
    }

  ts->counts[BGP_STATS_MAXBITLEN] = space;

  for (rn = top; rn; rn = bgp_route_next (rn))
    {
      struct bgp_info *ri;
      struct bgp_node *prn = rn->parent;
      unsigned int rinum = 0;

      if (rn == top)
        continue;

      if (!rn->info)
        continue;

      ts->counts[BGP_STATS_PREFIXES]++;
      ts->counts[BGP_STATS_TOTPLEN] += rn->p.prefixlen;

#if 0
      ts->counts[BGP_STATS_AVGPLEN]
        = ravg_tally (ts->counts[BGP_STATS_PREFIXES],
                      ts->counts[BGP_STATS_AVGPLEN],
                      rn->p.prefixlen);
#endif

      /* check if the prefix is included by any other announcements */
      while (prn && !prn->info)
        prn = prn->parent;

      if (prn == NULL || prn == top)
        {
          ts->counts[BGP_STATS_UNAGGREGATEABLE]++;
          /* announced address space */
          if (space)
            ts->counts[BGP_STATS_SPACE] += 1 << (space - rn->p.prefixlen);
        }
      else if (prn->info)
        ts->counts[BGP_STATS_MAX_AGGREGATEABLE]++;

      for (ri = rn->info; ri; ri = ri->next)
        {
          rinum++;
          ts->counts[BGP_STATS_RIB]++;

          if (ri->attr &&
              (CHECK_FLAG (ri->attr->flag,
                           ATTR_FLAG_BIT (BGP_ATTR_ATOMIC_AGGREGATE))))
            ts->counts[BGP_STATS_AGGREGATES]++;

          /* as-path stats */
          if (ri->attr && ri->attr->aspath)
            {
              unsigned int hops = aspath_count_hops (ri->attr->aspath);
              unsigned int size = aspath_size (ri->attr->aspath);
              as_t highest = aspath_highest (ri->attr->aspath);

              ts->counts[BGP_STATS_ASPATH_COUNT]++;

              if (hops > ts->counts[BGP_STATS_ASPATH_MAXHOPS])
                ts->counts[BGP_STATS_ASPATH_MAXHOPS] = hops;

              if (size > ts->counts[BGP_STATS_ASPATH_MAXSIZE])
                ts->counts[BGP_STATS_ASPATH_MAXSIZE] = size;

              ts->counts[BGP_STATS_ASPATH_TOTHOPS] += hops;
              ts->counts[BGP_STATS_ASPATH_TOTSIZE] += size;
#if 0
              ts->counts[BGP_STATS_ASPATH_AVGHOPS]
                = ravg_tally (ts->counts[BGP_STATS_ASPATH_COUNT],
                              ts->counts[BGP_STATS_ASPATH_AVGHOPS],
                              hops);
              ts->counts[BGP_STATS_ASPATH_AVGSIZE]
                = ravg_tally (ts->counts[BGP_STATS_ASPATH_COUNT],
                              ts->counts[BGP_STATS_ASPATH_AVGSIZE],
                              size);
#endif
              if (highest > ts->counts[BGP_STATS_ASN_HIGHEST])
                ts->counts[BGP_STATS_ASN_HIGHEST] = highest;
            }
        }
    }
  return 0;
}

static int
bgp_table_stats (struct vty *vty, struct bgp *bgp, afi_t afi, safi_t safi)
{
  struct bgp_table_stats ts;
  unsigned int i;

  if (!bgp->rib[afi][safi])
    {
      vty_out (vty, "%% No RIB exist for the AFI/SAFI%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  memset (&ts, 0, sizeof (ts));
  ts.table = bgp->rib[afi][safi];
  thread_execute (bm->master, bgp_table_stats_walker, &ts, 0);

  vty_out (vty, "BGP %s RIB statistics%s%s",
           afi_safi_print (afi, safi), VTY_NEWLINE, VTY_NEWLINE);

  for (i = 0; i < BGP_STATS_MAX; i++)
    {
      if (!table_stats_strs[i])
        continue;

      switch (i)
        {
#if 0
          case BGP_STATS_ASPATH_AVGHOPS:
          case BGP_STATS_ASPATH_AVGSIZE:
          case BGP_STATS_AVGPLEN:
            vty_out (vty, "%-30s: ", table_stats_strs[i]);
            vty_out (vty, "%12.2f",
                     (float)ts.counts[i] / (float)TALLY_SIGFIG);
            break;
#endif
          case BGP_STATS_ASPATH_TOTHOPS:
          case BGP_STATS_ASPATH_TOTSIZE:
            vty_out (vty, "%-30s: ", table_stats_strs[i]);
            vty_out (vty, "%12.2f",
                     ts.counts[i] ?
                     (float)ts.counts[i] /
                      (float)ts.counts[BGP_STATS_ASPATH_COUNT]
                     : 0);
            break;
          case BGP_STATS_TOTPLEN:
            vty_out (vty, "%-30s: ", table_stats_strs[i]);
            vty_out (vty, "%12.2f",
                     ts.counts[i] ?
                     (float)ts.counts[i] /
                      (float)ts.counts[BGP_STATS_PREFIXES]
                     : 0);
            break;
          case BGP_STATS_SPACE:
            vty_out (vty, "%-30s: ", table_stats_strs[i]);
            vty_out (vty, "%12llu%s", ts.counts[i], VTY_NEWLINE);
            if (ts.counts[BGP_STATS_MAXBITLEN] < 9)
              break;
            vty_out (vty, "%30s: ", "%% announced ");
            vty_out (vty, "%12.2f%s",
                     100 * (float)ts.counts[BGP_STATS_SPACE] /
                       (float)((uint64_t)1UL << ts.counts[BGP_STATS_MAXBITLEN]),
                       VTY_NEWLINE);
            vty_out (vty, "%30s: ", "/8 equivalent ");
            vty_out (vty, "%12.2f%s",
                     (float)ts.counts[BGP_STATS_SPACE] /
                       (float)(1UL << (ts.counts[BGP_STATS_MAXBITLEN] - 8)),
                     VTY_NEWLINE);
            if (ts.counts[BGP_STATS_MAXBITLEN] < 25)
              break;
            vty_out (vty, "%30s: ", "/24 equivalent ");
            vty_out (vty, "%12.2f",
                     (float)ts.counts[BGP_STATS_SPACE] /
                       (float)(1UL << (ts.counts[BGP_STATS_MAXBITLEN] - 24)));
            break;
          default:
            vty_out (vty, "%-30s: ", table_stats_strs[i]);
            vty_out (vty, "%12llu", ts.counts[i]);
        }

      vty_out (vty, "%s", VTY_NEWLINE);
    }
  return CMD_SUCCESS;
}

int
bgp_table_stats_vty (struct vty *vty, const char *name,
                     const char *afi_str, const char *safi_str)
{
  struct bgp *bgp;
  afi_t afi;
  safi_t safi;

 if (name)
    bgp = bgp_lookup_by_name (name);
  else
    bgp = bgp_get_default ();

  if (!bgp)
    {
      vty_out (vty, "%% No such BGP instance exist%s", VTY_NEWLINE);
      return CMD_WARNING;
    }
  if (strncmp (afi_str, "ipv", 3) == 0)
    {
      if (strncmp (afi_str, "ipv4", 4) == 0)
        afi = AFI_IP;
      else if (strncmp (afi_str, "ipv6", 4) == 0)
        afi = AFI_IP6;
      else
        {
          vty_out (vty, "%% Invalid address family %s%s",
                   afi_str, VTY_NEWLINE);
          return CMD_WARNING;
        }
      if (strncmp (safi_str, "m", 1) == 0)
        safi = SAFI_MULTICAST;
      else if (strncmp (safi_str, "u", 1) == 0)
        safi = SAFI_UNICAST;
      else if (strncmp (safi_str, "vpnv4", 5) == 0 || strncmp (safi_str, "vpnv6", 5) == 0)
        safi = SAFI_MPLS_LABELED_VPN;
      else
        {
          vty_out (vty, "%% Invalid subsequent address family %s%s",
                   safi_str, VTY_NEWLINE);
          return CMD_WARNING;
        }
    }
  else
    {
      vty_out (vty, "%% Invalid address family %s%s",
               afi_str, VTY_NEWLINE);
      return CMD_WARNING;
    }

  return bgp_table_stats (vty, bgp, afi, safi);
}

static int
bgp_peer_count_walker (struct thread *t)
{
  struct bgp_node *rn;
  struct peer_pcounts *pc = THREAD_ARG (t);
  const struct peer *peer = pc->peer;

  for (rn = bgp_table_top (pc->table); rn; rn = bgp_route_next (rn))
    {
      struct bgp_adj_in *ain;
      struct bgp_info *ri;

      for (ain = rn->adj_in; ain; ain = ain->next)
        if (ain->peer == peer)
          pc->count[PCOUNT_ADJ_IN]++;

      for (ri = rn->info; ri; ri = ri->next)
        {
          char buf[SU_ADDRSTRLEN];

          if (ri->peer != peer)
            continue;

          pc->count[PCOUNT_ALL]++;

          if (CHECK_FLAG (ri->flags, BGP_INFO_DAMPED))
            pc->count[PCOUNT_DAMPED]++;
          if (CHECK_FLAG (ri->flags, BGP_INFO_HISTORY))
            pc->count[PCOUNT_HISTORY]++;
          if (CHECK_FLAG (ri->flags, BGP_INFO_REMOVED))
            pc->count[PCOUNT_REMOVED]++;
          if (CHECK_FLAG (ri->flags, BGP_INFO_STALE))
            pc->count[PCOUNT_STALE]++;
          if (CHECK_FLAG (ri->flags, BGP_INFO_VALID))
            pc->count[PCOUNT_VALID]++;
          if (!CHECK_FLAG (ri->flags, BGP_INFO_UNUSEABLE))
            pc->count[PCOUNT_PFCNT]++;

          if (CHECK_FLAG (ri->flags, BGP_INFO_COUNTED))
            {
              pc->count[PCOUNT_COUNTED]++;
              if (CHECK_FLAG (ri->flags, BGP_INFO_UNUSEABLE))
                plog_warn (peer->log,
                           "%s [pcount] %s/%d is counted but flags 0x%x",
                           peer->host,
                           inet_ntop(rn->p.family, &rn->p.u.prefix,
                                     buf, SU_ADDRSTRLEN),
                           rn->p.prefixlen,
                           ri->flags);
            }
          else
            {
              if (!CHECK_FLAG (ri->flags, BGP_INFO_UNUSEABLE))
                plog_warn (peer->log,
                           "%s [pcount] %s/%d not counted but flags 0x%x",
                           peer->host,
                           inet_ntop(rn->p.family, &rn->p.u.prefix,
                                     buf, SU_ADDRSTRLEN),
                           rn->p.prefixlen,
                           ri->flags);
            }
        }
    }
  return 0;
}

int
bgp_peer_counts (struct vty *vty, struct peer *peer, afi_t afi, safi_t safi)
{
  struct peer_pcounts pcounts = { .peer = peer };
  unsigned int i;

  if (!peer || !peer->bgp || !peer->afc[afi][safi]
      || !peer->bgp->rib[afi][safi])
    {
      vty_out (vty, "%% No such neighbor or address family%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  memset (&pcounts, 0, sizeof(pcounts));
  pcounts.peer = peer;
  pcounts.table = peer->bgp->rib[afi][safi];

  /* in-place call via thread subsystem so as to record execution time
   * stats for the thread-walk (i.e. ensure this can't be blamed on
   * on just vty_read()).
   */
  thread_execute (bm->master, bgp_peer_count_walker, &pcounts, 0);

  vty_out (vty, "Prefix counts for %s, %s%s",
           peer->host, afi_safi_print (afi, safi), VTY_NEWLINE);
  vty_out (vty, "PfxCt: %ld%s", peer->pcount[afi][safi], VTY_NEWLINE);
  vty_out (vty, "%sCounts from RIB table walk:%s%s",
           VTY_NEWLINE, VTY_NEWLINE, VTY_NEWLINE);

  for (i = 0; i < PCOUNT_MAX; i++)
      vty_out (vty, "%20s: %-10d%s",
               pcount_strs[i], pcounts.count[i], VTY_NEWLINE);

  if (pcounts.count[PCOUNT_PFCNT] != peer->pcount[afi][safi])
    {
      vty_out (vty, "%s [pcount] PfxCt drift!%s",
               peer->host, VTY_NEWLINE);
      vty_out (vty, "Please report this bug, with the above command output%s",
              VTY_NEWLINE);
    }

  return CMD_SUCCESS;
}

/* Show BGP peer's summary information. */
static int
bgp_show_summary (struct vty *vty, struct bgp *bgp, int afi, int safi)
{
  struct peer *peer;
  struct listnode *node, *nnode;
  unsigned int count = 0;
  char timebuf[BGP_UPTIME_LEN];
  int len;

  /* Header string for each address family. */
  static char header[] = "Neighbor        V    AS MsgRcvd MsgSent   TblVer  InQ OutQ Up/Down  State/PfxRcd";

  for (ALL_LIST_ELEMENTS (bgp->peer, node, nnode, peer))
    {
      if (peer->afc[afi][safi])
	{
          if (!count)
            {
              unsigned long ents;
              char memstrbuf[MTYPE_MEMSTR_LEN];

              /* Usage summary and header */
              vty_out (vty,
                       "BGP router identifier %s, local AS number %u%s",
                       inet_ntoa (bgp->router_id), bgp->as, VTY_NEWLINE);

              ents = bgp_table_count (bgp->rib[afi][safi]);
              vty_out (vty, "RIB entries %ld, using %s of memory%s", ents,
                       mtype_memstr (memstrbuf, sizeof (memstrbuf),
                                     ents * sizeof (struct bgp_node)),
                       VTY_NEWLINE);

              /* Peer related usage */
              ents = listcount (bgp->peer);
              vty_out (vty, "Peers %ld, using %s of memory%s",
                       ents,
                       mtype_memstr (memstrbuf, sizeof (memstrbuf),
                                     ents * sizeof (struct peer)),
                       VTY_NEWLINE);

              if ((ents = listcount (bgp->rsclient)))
                vty_out (vty, "RS-Client peers %ld, using %s of memory%s",
                         ents,
                         mtype_memstr (memstrbuf, sizeof (memstrbuf),
                                       ents * sizeof (struct peer)),
                         VTY_NEWLINE);

              if ((ents = listcount (bgp->group)))
                vty_out (vty, "Peer groups %ld, using %s of memory%s", ents,
                         mtype_memstr (memstrbuf, sizeof (memstrbuf),
                                       ents * sizeof (struct peer_group)),
                         VTY_NEWLINE);

              if (CHECK_FLAG (bgp->af_flags[afi][safi], BGP_CONFIG_DAMPENING))
                vty_out (vty, "Dampening enabled.%s", VTY_NEWLINE);
              vty_out (vty, "%s", VTY_NEWLINE);
              vty_out (vty, "%s%s", header, VTY_NEWLINE);
            }

	  count++;

	  len = vty_out (vty, "%s", peer->host);
	  len = 16 - len;
	  if (len < 1)
	    vty_out (vty, "%s%*s", VTY_NEWLINE, 16, " ");
	  else
	    vty_out (vty, "%*s", len, " ");

	  vty_out (vty, "4 ");

	  vty_out (vty, "%5u %7d %7d %8d %4d %4lu ",
		   peer->as,
		   peer->open_in + peer->update_in + peer->keepalive_in
		   + peer->notify_in + peer->refresh_in + peer->dynamic_cap_in,
		   peer->open_out + peer->update_out + peer->keepalive_out
		   + peer->notify_out + peer->refresh_out
		   + peer->dynamic_cap_out,
		   0, 0, (unsigned long) peer->obuf->count);

	  vty_out (vty, "%8s",
		   peer_uptime (peer->uptime, timebuf, BGP_UPTIME_LEN));

	  if (peer->status == Established)
	    {
	      vty_out (vty, " %8ld", peer->pcount[afi][safi]);
	    }
	  else
	    {
	      if (CHECK_FLAG (peer->flags, PEER_FLAG_SHUTDOWN))
		vty_out (vty, " Idle (Admin)");
	      else if (CHECK_FLAG (peer->sflags, PEER_STATUS_PREFIX_OVERFLOW))
		vty_out (vty, " Idle (PfxCt)");
	      else
		vty_out (vty, " %-11s", LOOKUP(bgp_status_msg, peer->status));
	    }

	  vty_out (vty, "%s", VTY_NEWLINE);
	}
    }

  if (count)
    vty_out (vty, "%sTotal number of neighbors %d%s", VTY_NEWLINE,
	     count, VTY_NEWLINE);
  else
    vty_out (vty, "No %s neighbor is configured%s",
	     afi == AFI_IP ? "IPv4" : "IPv6", VTY_NEWLINE);
  return CMD_SUCCESS;
}

int
bgp_show_summary_vty (struct vty *vty, const char *name,
                      afi_t afi, safi_t safi)
{
  struct bgp *bgp;

  if (name)
    {
      bgp = bgp_lookup_by_name (name);

      if (! bgp)
	{
	  vty_out (vty, "%% No such BGP instance exist%s", VTY_NEWLINE);
	  return CMD_WARNING;
	}

      bgp_show_summary (vty, bgp, afi, safi);
      return CMD_SUCCESS;
    }

  bgp = bgp_get_default ();

  if (bgp)
    bgp_show_summary (vty, bgp, afi, safi);

  return CMD_SUCCESS;
}

static int
bgp_write_rsclient_summary (struct vty *vty, struct peer *rsclient,
        afi_t afi, safi_t safi)
{
  char timebuf[BGP_UPTIME_LEN];
  char rmbuf[14];
  const char *rmname;
  struct peer *peer;
  struct listnode *node, *nnode;
  int len;
  int count = 0;

  if (CHECK_FLAG (rsclient->sflags, PEER_STATUS_GROUP))
    {
      for (ALL_LIST_ELEMENTS (rsclient->group->peer, node, nnode, peer))
        {
          count++;
          bgp_write_rsclient_summary (vty, peer, afi, safi);
        }
      return count;
    }

  len = vty_out (vty, "%s", rsclient->host);
  len = 16 - len;

  if (len < 1)
    vty_out (vty, "%s%*s", VTY_NEWLINE, 16, " ");
  else
    vty_out (vty, "%*s", len, " ");

  vty_out (vty, "4 ");

  vty_out (vty, "%11d ", rsclient->as);

  rmname = ROUTE_MAP_EXPORT_NAME(&rsclient->filter[afi][safi]);
  if ( rmname && strlen (rmname) > 13 )
    {
      sprintf (rmbuf, "%13s", "...");
      rmname = strncpy (rmbuf, rmname, 10);
    }
  else if (! rmname)
    rmname = "<none>";
  vty_out (vty, " %13s ", rmname);

  rmname = ROUTE_MAP_IMPORT_NAME(&rsclient->filter[afi][safi]);
  if ( rmname && strlen (rmname) > 13 )
    {
      sprintf (rmbuf, "%13s", "...");
      rmname = strncpy (rmbuf, rmname, 10);
    }
  else if (! rmname)
    rmname = "<none>";
  vty_out (vty, " %13s ", rmname);

  vty_out (vty, "%8s", peer_uptime (rsclient->uptime, timebuf, BGP_UPTIME_LEN));

  if (CHECK_FLAG (rsclient->flags, PEER_FLAG_SHUTDOWN))
    vty_out (vty, " Idle (Admin)");
  else if (CHECK_FLAG (rsclient->sflags, PEER_STATUS_PREFIX_OVERFLOW))
    vty_out (vty, " Idle (PfxCt)");
  else
    vty_out (vty, " %-11s", LOOKUP(bgp_status_msg, rsclient->status));

  vty_out (vty, "%s", VTY_NEWLINE);

  return 1;
}

static int
bgp_show_rsclient_summary (struct vty *vty, struct bgp *bgp,
                           afi_t afi, safi_t safi)
{
  struct peer *peer;
  struct listnode *node, *nnode;
  int count = 0;

  /* Header string for each address family. */
  static char header[] = "Neighbor        V    AS  Export-Policy  Import-Policy  Up/Down  State";

  for (ALL_LIST_ELEMENTS (bgp->rsclient, node, nnode, peer))
    {
      if (peer->afc[afi][safi] &&
         CHECK_FLAG (peer->af_flags[afi][safi], PEER_FLAG_RSERVER_CLIENT))
       {
         if (! count)
           {
             vty_out (vty,
                      "Route Server's BGP router identifier %s%s",
                      inet_ntoa (bgp->router_id), VTY_NEWLINE);
             vty_out (vty,
              "Route Server's local AS number %u%s", bgp->as,
                       VTY_NEWLINE);

             vty_out (vty, "%s", VTY_NEWLINE);
             vty_out (vty, "%s%s", header, VTY_NEWLINE);
           }

         count += bgp_write_rsclient_summary (vty, peer, afi, safi);
       }
    }

  if (count)
    vty_out (vty, "%sTotal number of Route Server Clients %d%s", VTY_NEWLINE,
            count, VTY_NEWLINE);
  else
    vty_out (vty, "No %s Route Server Client is configured%s",
            afi == AFI_IP ? "IPv4" : "IPv6", VTY_NEWLINE);

  return CMD_SUCCESS;
}

int
bgp_show_rsclient_summary_vty (struct vty *vty, const char *name,
                               afi_t afi, safi_t safi)
{
  struct bgp *bgp;

  if (name)
    {
      bgp = bgp_lookup_by_name (name);

      if (! bgp)
       {
         vty_out (vty, "%% No such BGP instance exist%s", VTY_NEWLINE);
         return CMD_WARNING;
       }

      bgp_show_rsclient_summary (vty, bgp, afi, safi);
      return CMD_SUCCESS;
    }

  bgp = bgp_get_default ();

  if (bgp)
    bgp_show_rsclient_summary (vty, bgp, afi, safi);

  return CMD_SUCCESS;
}

static void
bgp_show_peer_afi_orf_cap (struct vty *vty, struct peer *p,
			   afi_t afi, safi_t safi,
			   u_int16_t adv_smcap, u_int16_t adv_rmcap,
			   u_int16_t rcv_smcap, u_int16_t rcv_rmcap)
{
  /* Send-Mode */
  if (CHECK_FLAG (p->af_cap[afi][safi], adv_smcap)
      || CHECK_FLAG (p->af_cap[afi][safi], rcv_smcap))
    {
      vty_out (vty, "      Send-mode: ");
      if (CHECK_FLAG (p->af_cap[afi][safi], adv_smcap))
	vty_out (vty, "advertised");
      if (CHECK_FLAG (p->af_cap[afi][safi], rcv_smcap))
	vty_out (vty, "%sreceived",
		 CHECK_FLAG (p->af_cap[afi][safi], adv_smcap) ?
		 ", " : "");
      vty_out (vty, "%s", VTY_NEWLINE);
    }

  /* Receive-Mode */
  if (CHECK_FLAG (p->af_cap[afi][safi], adv_rmcap)
      || CHECK_FLAG (p->af_cap[afi][safi], rcv_rmcap))
    {
      vty_out (vty, "      Receive-mode: ");
      if (CHECK_FLAG (p->af_cap[afi][safi], adv_rmcap))
	vty_out (vty, "advertised");
      if (CHECK_FLAG (p->af_cap[afi][safi], rcv_rmcap))
	vty_out (vty, "%sreceived",
		 CHECK_FLAG (p->af_cap[afi][safi], adv_rmcap) ?
		 ", " : "");
      vty_out (vty, "%s", VTY_NEWLINE);
    }
}

static void
bgp_show_peer_afi (struct vty *vty, struct peer *p, afi_t afi, safi_t safi)
{
  struct bgp_filter *filter;
  char orf_pfx_name[BUFSIZ];
  int orf_pfx_count;

  filter = &p->filter[afi][safi];

  vty_out (vty, " For address family: %s%s", afi_safi_print (afi, safi),
	   VTY_NEWLINE);

  if (p->af_group[afi][safi])
    vty_out (vty, "  %s peer-group member%s", p->group->name, VTY_NEWLINE);

  if (CHECK_FLAG (p->af_cap[afi][safi], PEER_CAP_ORF_PREFIX_SM_ADV)
      || CHECK_FLAG (p->af_cap[afi][safi], PEER_CAP_ORF_PREFIX_SM_RCV)
      || CHECK_FLAG (p->af_cap[afi][safi], PEER_CAP_ORF_PREFIX_SM_OLD_RCV)
      || CHECK_FLAG (p->af_cap[afi][safi], PEER_CAP_ORF_PREFIX_RM_ADV)
      || CHECK_FLAG (p->af_cap[afi][safi], PEER_CAP_ORF_PREFIX_RM_RCV)
      || CHECK_FLAG (p->af_cap[afi][safi], PEER_CAP_ORF_PREFIX_RM_OLD_RCV))
    vty_out (vty, "  AF-dependant capabilities:%s", VTY_NEWLINE);

  if (CHECK_FLAG (p->af_cap[afi][safi], PEER_CAP_ORF_PREFIX_SM_ADV)
      || CHECK_FLAG (p->af_cap[afi][safi], PEER_CAP_ORF_PREFIX_SM_RCV)
      || CHECK_FLAG (p->af_cap[afi][safi], PEER_CAP_ORF_PREFIX_RM_ADV)
      || CHECK_FLAG (p->af_cap[afi][safi], PEER_CAP_ORF_PREFIX_RM_RCV))
    {
      vty_out (vty, "    Outbound Route Filter (ORF) type (%d) Prefix-list:%s",
	       ORF_TYPE_PREFIX, VTY_NEWLINE);
      bgp_show_peer_afi_orf_cap (vty, p, afi, safi,
				 PEER_CAP_ORF_PREFIX_SM_ADV,
				 PEER_CAP_ORF_PREFIX_RM_ADV,
				 PEER_CAP_ORF_PREFIX_SM_RCV,
				 PEER_CAP_ORF_PREFIX_RM_RCV);
    }
  if (CHECK_FLAG (p->af_cap[afi][safi], PEER_CAP_ORF_PREFIX_SM_ADV)
      || CHECK_FLAG (p->af_cap[afi][safi], PEER_CAP_ORF_PREFIX_SM_OLD_RCV)
      || CHECK_FLAG (p->af_cap[afi][safi], PEER_CAP_ORF_PREFIX_RM_ADV)
      || CHECK_FLAG (p->af_cap[afi][safi], PEER_CAP_ORF_PREFIX_RM_OLD_RCV))
    {
      vty_out (vty, "    Outbound Route Filter (ORF) type (%d) Prefix-list:%s",
	       ORF_TYPE_PREFIX_OLD, VTY_NEWLINE);
      bgp_show_peer_afi_orf_cap (vty, p, afi, safi,
				 PEER_CAP_ORF_PREFIX_SM_ADV,
				 PEER_CAP_ORF_PREFIX_RM_ADV,
				 PEER_CAP_ORF_PREFIX_SM_OLD_RCV,
				 PEER_CAP_ORF_PREFIX_RM_OLD_RCV);
    }

  sprintf (orf_pfx_name, "%s.%d.%d", p->host, afi, safi);
  orf_pfx_count =  prefix_bgp_show_prefix_list (NULL, afi, orf_pfx_name);

  if (CHECK_FLAG (p->af_sflags[afi][safi], PEER_STATUS_ORF_PREFIX_SEND)
      || orf_pfx_count)
    {
      vty_out (vty, "  Outbound Route Filter (ORF):");
      if (CHECK_FLAG (p->af_sflags[afi][safi], PEER_STATUS_ORF_PREFIX_SEND))
	  vty_out (vty, " sent;");
      if (orf_pfx_count)
	vty_out (vty, " received (%d entries)", orf_pfx_count);
      vty_out (vty, "%s", VTY_NEWLINE);
    }
  if (CHECK_FLAG (p->af_sflags[afi][safi], PEER_STATUS_ORF_WAIT_REFRESH))
      vty_out (vty, "  First update is deferred until ORF or ROUTE-REFRESH is received%s", VTY_NEWLINE);

  if (CHECK_FLAG (p->af_flags[afi][safi], PEER_FLAG_REFLECTOR_CLIENT))
    vty_out (vty, "  Route-Reflector Client%s", VTY_NEWLINE);
  if (CHECK_FLAG (p->af_flags[afi][safi], PEER_FLAG_RSERVER_CLIENT))
    vty_out (vty, "  Route-Server Client%s", VTY_NEWLINE);
  if (CHECK_FLAG (p->af_flags[afi][safi], PEER_FLAG_SOFT_RECONFIG))
    vty_out (vty, "  Inbound soft reconfiguration allowed%s", VTY_NEWLINE);
  if (CHECK_FLAG (p->af_flags[afi][safi], PEER_FLAG_REMOVE_PRIVATE_AS))
    vty_out (vty, "  Private AS number removed from updates to this neighbor%s", VTY_NEWLINE);
  if (CHECK_FLAG (p->af_flags[afi][safi], PEER_FLAG_NEXTHOP_SELF))
    vty_out (vty, "  NEXT_HOP is always this router%s", VTY_NEWLINE);
  if (CHECK_FLAG (p->af_flags[afi][safi], PEER_FLAG_AS_PATH_UNCHANGED))
    vty_out (vty, "  AS_PATH is propagated unchanged to this neighbor%s", VTY_NEWLINE);
  if (CHECK_FLAG (p->af_flags[afi][safi], PEER_FLAG_NEXTHOP_UNCHANGED))
    vty_out (vty, "  NEXT_HOP is propagated unchanged to this neighbor%s", VTY_NEWLINE);
  if (CHECK_FLAG (p->af_flags[afi][safi], PEER_FLAG_MED_UNCHANGED))
    vty_out (vty, "  MED is propagated unchanged to this neighbor%s", VTY_NEWLINE);
  if (CHECK_FLAG (p->af_flags[afi][safi], PEER_FLAG_SEND_COMMUNITY)
      || CHECK_FLAG (p->af_flags[afi][safi], PEER_FLAG_SEND_EXT_COMMUNITY))
    {
      vty_out (vty, "  Community attribute sent to this neighbor");
      if (CHECK_FLAG (p->af_flags[afi][safi], PEER_FLAG_SEND_COMMUNITY)
	&& CHECK_FLAG (p->af_flags[afi][safi], PEER_FLAG_SEND_EXT_COMMUNITY))
	vty_out (vty, "(both)%s", VTY_NEWLINE);
      else if (CHECK_FLAG (p->af_flags[afi][safi], PEER_FLAG_SEND_EXT_COMMUNITY))
	vty_out (vty, "(extended)%s", VTY_NEWLINE);
      else
	vty_out (vty, "(standard)%s", VTY_NEWLINE);
    }
  if (CHECK_FLAG (p->af_flags[afi][safi], PEER_FLAG_DEFAULT_ORIGINATE))
    {
      vty_out (vty, "  Default information originate,");

      if (p->default_rmap[afi][safi].name)
	vty_out (vty, " default route-map %s%s,",
		 p->default_rmap[afi][safi].map ? "*" : "",
		 p->default_rmap[afi][safi].name);
      if (CHECK_FLAG (p->af_sflags[afi][safi], PEER_STATUS_DEFAULT_ORIGINATE))
	vty_out (vty, " default sent%s", VTY_NEWLINE);
      else
	vty_out (vty, " default not sent%s", VTY_NEWLINE);
    }

  if (filter->plist[FILTER_IN].name
      || filter->dlist[FILTER_IN].name
      || filter->aslist[FILTER_IN].name
      || filter->map[RMAP_IN].name)
    vty_out (vty, "  Inbound path policy configured%s", VTY_NEWLINE);
  if (filter->plist[FILTER_OUT].name
      || filter->dlist[FILTER_OUT].name
      || filter->aslist[FILTER_OUT].name
      || filter->map[RMAP_OUT].name
      || filter->usmap.name)
    vty_out (vty, "  Outbound path policy configured%s", VTY_NEWLINE);
  if (filter->map[RMAP_IMPORT].name)
    vty_out (vty, "  Import policy for this RS-client configured%s", VTY_NEWLINE);
  if (filter->map[RMAP_EXPORT].name)
    vty_out (vty, "  Export policy for this RS-client configured%s", VTY_NEWLINE);

  /* prefix-list */
  if (filter->plist[FILTER_IN].name)
    vty_out (vty, "  Incoming update prefix filter list is %s%s%s",
	     filter->plist[FILTER_IN].plist ? "*" : "",
	     filter->plist[FILTER_IN].name,
	     VTY_NEWLINE);
  if (filter->plist[FILTER_OUT].name)
    vty_out (vty, "  Outgoing update prefix filter list is %s%s%s",
	     filter->plist[FILTER_OUT].plist ? "*" : "",
	     filter->plist[FILTER_OUT].name,
	     VTY_NEWLINE);

  /* distribute-list */
  if (filter->dlist[FILTER_IN].name)
    vty_out (vty, "  Incoming update network filter list is %s%s%s",
	     filter->dlist[FILTER_IN].alist ? "*" : "",
	     filter->dlist[FILTER_IN].name,
	     VTY_NEWLINE);
  if (filter->dlist[FILTER_OUT].name)
    vty_out (vty, "  Outgoing update network filter list is %s%s%s",
	     filter->dlist[FILTER_OUT].alist ? "*" : "",
	     filter->dlist[FILTER_OUT].name,
	     VTY_NEWLINE);

  /* filter-list. */
  if (filter->aslist[FILTER_IN].name)
    vty_out (vty, "  Incoming update AS path filter list is %s%s%s",
	     filter->aslist[FILTER_IN].aslist ? "*" : "",
	     filter->aslist[FILTER_IN].name,
	     VTY_NEWLINE);
  if (filter->aslist[FILTER_OUT].name)
    vty_out (vty, "  Outgoing update AS path filter list is %s%s%s",
	     filter->aslist[FILTER_OUT].aslist ? "*" : "",
	     filter->aslist[FILTER_OUT].name,
	     VTY_NEWLINE);

  /* route-map. */
  if (filter->map[RMAP_IN].name)
    vty_out (vty, "  Route map for incoming advertisements is %s%s%s",
            filter->map[RMAP_IN].map ? "*" : "",
            filter->map[RMAP_IN].name,
	     VTY_NEWLINE);
  if (filter->map[RMAP_OUT].name)
    vty_out (vty, "  Route map for outgoing advertisements is %s%s%s",
            filter->map[RMAP_OUT].map ? "*" : "",
            filter->map[RMAP_OUT].name,
            VTY_NEWLINE);
  if (filter->map[RMAP_IMPORT].name)
    vty_out (vty, "  Route map for advertisements going into this RS-client's table is %s%s%s",
            filter->map[RMAP_IMPORT].map ? "*" : "",
            filter->map[RMAP_IMPORT].name,
            VTY_NEWLINE);
  if (filter->map[RMAP_EXPORT].name)
    vty_out (vty, "  Route map for advertisements coming from this RS-client is %s%s%s",
            filter->map[RMAP_EXPORT].map ? "*" : "",
            filter->map[RMAP_EXPORT].name,
	     VTY_NEWLINE);

  /* unsuppress-map */
  if (filter->usmap.name)
    vty_out (vty, "  Route map for selective unsuppress is %s%s%s",
	     filter->usmap.map ? "*" : "",
	     filter->usmap.name, VTY_NEWLINE);

  /* Receive prefix count */
  vty_out (vty, "  %ld accepted prefixes%s", p->pcount[afi][safi], VTY_NEWLINE);

  /* Maximum prefix */
  if (CHECK_FLAG (p->af_flags[afi][safi], PEER_FLAG_MAX_PREFIX))
    {
      vty_out (vty, "  Maximum prefixes allowed %ld%s%s", p->pmax[afi][safi],
	       CHECK_FLAG (p->af_flags[afi][safi], PEER_FLAG_MAX_PREFIX_WARNING)
	       ? " (warning-only)" : "", VTY_NEWLINE);
      vty_out (vty, "  Threshold for warning message %d%%",
	       p->pmax_threshold[afi][safi]);
      if (p->pmax_restart[afi][safi])
	vty_out (vty, ", restart interval %d min", p->pmax_restart[afi][safi]);
      vty_out (vty, "%s", VTY_NEWLINE);
    }

  vty_out (vty, "%s", VTY_NEWLINE);
}

void
bgp_show_peer (struct vty *vty, struct peer *p)
{
  struct bgp *bgp;
  char buf1[BUFSIZ];
  char timebuf[BGP_UPTIME_LEN];
  afi_t afi;
  safi_t safi;

  bgp = p->bgp;

  /* Configured IP address. */
  vty_out (vty, "BGP neighbor is %s, ", p->host);
  vty_out (vty, "remote AS %u, ", p->as);
  vty_out (vty, "local AS %u%s, ",
	   p->change_local_as ? p->change_local_as : p->local_as,
	   CHECK_FLAG (p->flags, PEER_FLAG_LOCAL_AS_NO_PREPEND) ?
	   " no-prepend" : "");
  vty_out (vty, "%s link%s",
	   p->as == p->local_as ? "internal" : "external",
	   VTY_NEWLINE);

  /* Description. */
  if (p->desc)
    vty_out (vty, " Description: %s%s", p->desc, VTY_NEWLINE);

  /* Peer-group */
  if (p->group)
    vty_out (vty, " Member of peer-group %s for session parameters%s",
	     p->group->name, VTY_NEWLINE);

  /* Administrative shutdown. */
  if (CHECK_FLAG (p->flags, PEER_FLAG_SHUTDOWN))
    vty_out (vty, " Administratively shut down%s", VTY_NEWLINE);

  /* BGP Version. */
  vty_out (vty, "  BGP version 4");
  vty_out (vty, ", remote router ID %s%s",
	   inet_ntop (AF_INET, &p->remote_id, buf1, BUFSIZ),
	   VTY_NEWLINE);

  /* Confederation */
  if (CHECK_FLAG (bgp->config, BGP_CONFIG_CONFEDERATION)
      && bgp_confederation_peers_check (bgp, p->as))
    vty_out (vty, "  Neighbor under common administration%s", VTY_NEWLINE);

  /* Status. */
  vty_out (vty, "  BGP state = %s",
	   LOOKUP (bgp_status_msg, p->status));
  if (p->status == Established)
    vty_out (vty, ", up for %8s",
	     peer_uptime (p->uptime, timebuf, BGP_UPTIME_LEN));
  else if (p->status == Active)
    {
      if (CHECK_FLAG (p->flags, PEER_FLAG_PASSIVE))
	vty_out (vty, " (passive)");
      else if (CHECK_FLAG (p->sflags, PEER_STATUS_NSF_WAIT))
	vty_out (vty, " (NSF passive)");
    }
  vty_out (vty, "%s", VTY_NEWLINE);

  /* read timer */
  vty_out (vty, "  Last read %s", peer_uptime (p->readtime, timebuf, BGP_UPTIME_LEN));

  /* Configured timer values. */
  vty_out (vty, ", hold time is %d, keepalive interval is %d seconds%s",
	   p->v_holdtime, p->v_keepalive, VTY_NEWLINE);
  if (CHECK_FLAG (p->config, PEER_CONFIG_TIMER))
    {
      vty_out (vty, "  Configured hold time is %d", p->holdtime);
      vty_out (vty, ", keepalive interval is %d seconds%s",
	       p->keepalive, VTY_NEWLINE);
    }

  /* Capability. */
  if (p->status == Established)
    {
      if (p->cap
	  || p->afc_adv[AFI_IP][SAFI_UNICAST]
	  || p->afc_recv[AFI_IP][SAFI_UNICAST]
	  || p->afc_adv[AFI_IP][SAFI_MULTICAST]
	  || p->afc_recv[AFI_IP][SAFI_MULTICAST]
#ifdef HAVE_IPV6
	  || p->afc_adv[AFI_IP6][SAFI_UNICAST]
	  || p->afc_recv[AFI_IP6][SAFI_UNICAST]
	  || p->afc_adv[AFI_IP6][SAFI_MULTICAST]
	  || p->afc_recv[AFI_IP6][SAFI_MULTICAST]
#endif /* HAVE_IPV6 */
	  || p->afc_adv[AFI_IP][SAFI_MPLS_VPN]
	  || p->afc_recv[AFI_IP][SAFI_MPLS_VPN])
	{
	  vty_out (vty, "  Neighbor capabilities:%s", VTY_NEWLINE);

	  /* AS4 */
	  if (CHECK_FLAG (p->cap, PEER_CAP_AS4_RCV)
	      || CHECK_FLAG (p->cap, PEER_CAP_AS4_ADV))
	    {
	      vty_out (vty, "    4 Byte AS:");
	      if (CHECK_FLAG (p->cap, PEER_CAP_AS4_ADV))
		vty_out (vty, " advertised");
	      if (CHECK_FLAG (p->cap, PEER_CAP_AS4_RCV))
		vty_out (vty, " %sreceived",
			 CHECK_FLAG (p->cap, PEER_CAP_AS4_ADV) ? "and " : "");
	      vty_out (vty, "%s", VTY_NEWLINE);
	    }
	  /* Dynamic */
	  if (CHECK_FLAG (p->cap, PEER_CAP_DYNAMIC_RCV)
	      || CHECK_FLAG (p->cap, PEER_CAP_DYNAMIC_ADV))
	    {
	      vty_out (vty, "    Dynamic:");
	      if (CHECK_FLAG (p->cap, PEER_CAP_DYNAMIC_ADV))
		vty_out (vty, " advertised");
	      if (CHECK_FLAG (p->cap, PEER_CAP_DYNAMIC_RCV))
		vty_out (vty, " %sreceived",
			 CHECK_FLAG (p->cap, PEER_CAP_DYNAMIC_ADV) ? "and " : "");
	      vty_out (vty, "%s", VTY_NEWLINE);
	    }

	  /* Route Refresh */
	  if (CHECK_FLAG (p->cap, PEER_CAP_REFRESH_ADV)
	      || CHECK_FLAG (p->cap, PEER_CAP_REFRESH_NEW_RCV)
	      || CHECK_FLAG (p->cap, PEER_CAP_REFRESH_OLD_RCV))
	    {
	      vty_out (vty, "    Route refresh:");
	      if (CHECK_FLAG (p->cap, PEER_CAP_REFRESH_ADV))
		vty_out (vty, " advertised");
	      if (CHECK_FLAG (p->cap, PEER_CAP_REFRESH_NEW_RCV)
		  || CHECK_FLAG (p->cap, PEER_CAP_REFRESH_OLD_RCV))
		vty_out (vty, " %sreceived(%s)",
			 CHECK_FLAG (p->cap, PEER_CAP_REFRESH_ADV) ? "and " : "",
			 (CHECK_FLAG (p->cap, PEER_CAP_REFRESH_OLD_RCV)
			  && CHECK_FLAG (p->cap, PEER_CAP_REFRESH_NEW_RCV)) ?
			 "old & new" : CHECK_FLAG (p->cap, PEER_CAP_REFRESH_OLD_RCV) ? "old" : "new");

	      vty_out (vty, "%s", VTY_NEWLINE);
	    }

	  /* Multiprotocol Extensions */
	  for (afi = AFI_IP ; afi < AFI_MAX ; afi++)
	    for (safi = SAFI_UNICAST ; safi < SAFI_MAX ; safi++)
	      if (p->afc_adv[afi][safi] || p->afc_recv[afi][safi])
		{
		  vty_out (vty, "    Address family %s:", afi_safi_print (afi, safi));
		  if (p->afc_adv[afi][safi])
		    vty_out (vty, " advertised");
		  if (p->afc_recv[afi][safi])
		    vty_out (vty, " %sreceived", p->afc_adv[afi][safi] ? "and " : "");
		  vty_out (vty, "%s", VTY_NEWLINE);
		}

	  /* Gracefull Restart */
	  if (CHECK_FLAG (p->cap, PEER_CAP_RESTART_RCV)
	      || CHECK_FLAG (p->cap, PEER_CAP_RESTART_ADV))
	    {
	      vty_out (vty, "    Graceful Restart Capabilty:");
	      if (CHECK_FLAG (p->cap, PEER_CAP_RESTART_ADV))
		vty_out (vty, " advertised");
	      if (CHECK_FLAG (p->cap, PEER_CAP_RESTART_RCV))
		vty_out (vty, " %sreceived",
			 CHECK_FLAG (p->cap, PEER_CAP_RESTART_ADV) ? "and " : "");
	      vty_out (vty, "%s", VTY_NEWLINE);

	      if (CHECK_FLAG (p->cap, PEER_CAP_RESTART_RCV))
		{
		  int restart_af_count = 0;

		  vty_out (vty, "      Remote Restart timer is %d seconds%s",
			   p->v_gr_restart, VTY_NEWLINE);
		  vty_out (vty, "      Address families by peer:%s        ", VTY_NEWLINE);

		  for (afi = AFI_IP ; afi < AFI_MAX ; afi++)
		    for (safi = SAFI_UNICAST ; safi < SAFI_MAX ; safi++)
		      if (CHECK_FLAG (p->af_cap[afi][safi], PEER_CAP_RESTART_AF_RCV))
			{
			  vty_out (vty, "%s%s(%s)", restart_af_count ? ", " : "",
				   afi_safi_print (afi, safi),
				   CHECK_FLAG (p->af_cap[afi][safi], PEER_CAP_RESTART_AF_PRESERVE_RCV) ?
				   "preserved" : "not preserved");
			  restart_af_count++;
			}
		  if (! restart_af_count)
		    vty_out (vty, "none");
		  vty_out (vty, "%s", VTY_NEWLINE);
		}
	    }
	}
    }

  /* graceful restart information */
  if (CHECK_FLAG (p->cap, PEER_CAP_RESTART_RCV)
      || p->t_gr_restart
      || p->t_gr_stale)
    {
      int eor_send_af_count = 0;
      int eor_receive_af_count = 0;

      vty_out (vty, "  Graceful restart informations:%s", VTY_NEWLINE);
      if (p->status == Established)
	{
	  vty_out (vty, "    End-of-RIB send: ");
	  for (afi = AFI_IP ; afi < AFI_MAX ; afi++)
	    for (safi = SAFI_UNICAST ; safi < SAFI_MAX ; safi++)
	      if (CHECK_FLAG (p->af_sflags[afi][safi], PEER_STATUS_EOR_SEND))
		{
		  vty_out (vty, "%s%s", eor_send_af_count ? ", " : "",
			   afi_safi_print (afi, safi));
		  eor_send_af_count++;
		}
	  vty_out (vty, "%s", VTY_NEWLINE);

	  vty_out (vty, "    End-of-RIB received: ");
	  for (afi = AFI_IP ; afi < AFI_MAX ; afi++)
	    for (safi = SAFI_UNICAST ; safi < SAFI_MAX ; safi++)
	      if (CHECK_FLAG (p->af_sflags[afi][safi], PEER_STATUS_EOR_RECEIVED))
		{
		  vty_out (vty, "%s%s", eor_receive_af_count ? ", " : "",
			   afi_safi_print (afi, safi));
		  eor_receive_af_count++;
		}
	  vty_out (vty, "%s", VTY_NEWLINE);
	}

      if (p->t_gr_restart)
        vty_out (vty, "    The remaining time of restart timer is %ld%s",
                 thread_timer_remain_second (p->t_gr_restart), VTY_NEWLINE);

      if (p->t_gr_stale)
        vty_out (vty, "    The remaining time of stalepath timer is %ld%s",
                 thread_timer_remain_second (p->t_gr_stale), VTY_NEWLINE);
    }

  /* Packet counts. */
  vty_out (vty, "  Message statistics:%s", VTY_NEWLINE);
  vty_out (vty, "    Inq depth is 0%s", VTY_NEWLINE);
  vty_out (vty, "    Outq depth is %lu%s", (unsigned long) p->obuf->count, VTY_NEWLINE);
  vty_out (vty, "                         Sent       Rcvd%s", VTY_NEWLINE);
  vty_out (vty, "    Opens:         %10d %10d%s", p->open_out, p->open_in, VTY_NEWLINE);
  vty_out (vty, "    Notifications: %10d %10d%s", p->notify_out, p->notify_in, VTY_NEWLINE);
  vty_out (vty, "    Updates:       %10d %10d%s", p->update_out, p->update_in, VTY_NEWLINE);
  vty_out (vty, "    Keepalives:    %10d %10d%s", p->keepalive_out, p->keepalive_in, VTY_NEWLINE);
  vty_out (vty, "    Route Refresh: %10d %10d%s", p->refresh_out, p->refresh_in, VTY_NEWLINE);
  vty_out (vty, "    Capability:    %10d %10d%s", p->dynamic_cap_out, p->dynamic_cap_in, VTY_NEWLINE);
  vty_out (vty, "    Total:         %10d %10d%s", p->open_out + p->notify_out +
	   p->update_out + p->keepalive_out + p->refresh_out + p->dynamic_cap_out,
	   p->open_in + p->notify_in + p->update_in + p->keepalive_in + p->refresh_in +
	   p->dynamic_cap_in, VTY_NEWLINE);

  /* advertisement-interval */
  vty_out (vty, "  Minimum time between advertisement runs is %d seconds%s",
	   p->v_routeadv, VTY_NEWLINE);

  /* Update-source. */
  if (p->update_if || p->update_source)
    {
      vty_out (vty, "  Update source is ");
      if (p->update_if)
	vty_out (vty, "%s", p->update_if);
      else if (p->update_source)
	vty_out (vty, "%s",
		 sockunion2str (p->update_source, buf1, SU_ADDRSTRLEN));
      vty_out (vty, "%s", VTY_NEWLINE);
    }

  /* Default weight */
  if (CHECK_FLAG (p->config, PEER_CONFIG_WEIGHT))
    vty_out (vty, "  Default weight %d%s", p->weight,
	     VTY_NEWLINE);

  vty_out (vty, "%s", VTY_NEWLINE);

  /* Address Family Information */
  for (afi = AFI_IP ; afi < AFI_MAX ; afi++)
    for (safi = SAFI_UNICAST ; safi < SAFI_MAX ; safi++)
      if (p->afc[afi][safi])
	bgp_show_peer_afi (vty, p, afi, safi);

  vty_out (vty, "  Connections established %d; dropped %d%s",
	   p->established, p->dropped,
	   VTY_NEWLINE);

  if (! p->dropped)
    vty_out (vty, "  Last reset never%s", VTY_NEWLINE);
  else
    vty_out (vty, "  Last reset %s, due to %s%s",
            peer_uptime (p->resettime, timebuf, BGP_UPTIME_LEN),
            peer_down_str[(int) p->last_reset], VTY_NEWLINE);

  if (CHECK_FLAG (p->sflags, PEER_STATUS_PREFIX_OVERFLOW))
    {
      vty_out (vty, "  Peer had exceeded the max. no. of prefixes configured.%s", VTY_NEWLINE);

      if (p->t_pmax_restart)
	vty_out (vty, "  Reduce the no. of prefix from %s, will restart in %ld seconds%s",
		 p->host, thread_timer_remain_second (p->t_pmax_restart),
		 VTY_NEWLINE);
      else
	vty_out (vty, "  Reduce the no. of prefix and clear ip bgp %s to restore peering%s",
		 p->host, VTY_NEWLINE);
    }

  /* EBGP Multihop and GTSM */
  if (p->sort != BGP_PEER_IBGP)
    {
      if (p->gtsm_hops > 0)
	vty_out (vty, "  External BGP neighbor may be up to %d hops away.%s",
		 p->gtsm_hops, VTY_NEWLINE);
      else if (p->ttl > 1)
	vty_out (vty, "  External BGP neighbor may be up to %d hops away.%s",
		 p->ttl, VTY_NEWLINE);
    }

  /* Local address. */
  if (p->su_local)
    {
      vty_out (vty, "Local host: %s, Local port: %d%s",
	       sockunion2str (p->su_local, buf1, SU_ADDRSTRLEN),
	       ntohs (p->su_local->sin.sin_port),
	       VTY_NEWLINE);
    }

  /* Remote address. */
  if (p->su_remote)
    {
      vty_out (vty, "Foreign host: %s, Foreign port: %d%s",
	       sockunion2str (p->su_remote, buf1, SU_ADDRSTRLEN),
	       ntohs (p->su_remote->sin.sin_port),
	       VTY_NEWLINE);
    }

  /* Nexthop display. */
  if (p->su_local)
    {
      vty_out (vty, "Nexthop: %s%s",
	       inet_ntop (AF_INET, &p->nexthop.v4, buf1, BUFSIZ),
	       VTY_NEWLINE);
#ifdef HAVE_IPV6
      vty_out (vty, "Nexthop global: %s%s",
	       inet_ntop (AF_INET6, &p->nexthop.v6_global, buf1, BUFSIZ),
	       VTY_NEWLINE);
      vty_out (vty, "Nexthop local: %s%s",
	       inet_ntop (AF_INET6, &p->nexthop.v6_local, buf1, BUFSIZ),
	       VTY_NEWLINE);
      vty_out (vty, "BGP connection: %s%s",
	       p->shared_network ? "shared network" : "non shared network",
	       VTY_NEWLINE);
#endif /* HAVE_IPV6 */
    }

  /* Timer information. */
  if (p->t_start)
    vty_out (vty, "Next start timer due in %ld seconds%s",
	     thread_timer_remain_second (p->t_start), VTY_NEWLINE);
  if (p->t_connect)
    vty_out (vty, "Next connect timer due in %ld seconds%s",
	     thread_timer_remain_second (p->t_connect), VTY_NEWLINE);

  vty_out (vty, "Read thread: %s  Write thread: %s%s",
	   p->t_read ? "on" : "off",
	   p->t_write ? "on" : "off",
	   VTY_NEWLINE);

  if (p->notify.code == BGP_NOTIFY_OPEN_ERR
      && p->notify.subcode == BGP_NOTIFY_OPEN_UNSUP_CAPBL)
    bgp_capability_vty_out (vty, p);

  vty_out (vty, "%s", VTY_NEWLINE);
}

static int
bgp_show_neighbor (struct vty *vty, struct bgp *bgp,
		   enum show_type type, union sockunion *su)
{
  struct listnode *node, *nnode;
  struct peer *peer;
  int find = 0;

  for (ALL_LIST_ELEMENTS (bgp->peer, node, nnode, peer))
    {
      switch (type)
	{
	case show_all:
	  bgp_show_peer (vty, peer);
	  break;
	case show_peer:
	  if (sockunion_same (&peer->su, su))
	    {
	      find = 1;
	      bgp_show_peer (vty, peer);
	    }
	  break;
	}
    }

  if (type == show_peer && ! find)
    vty_out (vty, "%% No such neighbor%s", VTY_NEWLINE);

  return CMD_SUCCESS;
}

int
bgp_show_neighbor_vty (struct vty *vty, const char *name,
                       enum show_type type, const char *ip_str)
{
  int ret;
  struct bgp *bgp;
  union sockunion su;

  if (ip_str)
    {
      ret = str2sockunion (ip_str, &su);
      if (ret < 0)
        {
          vty_out (vty, "%% Malformed address: %s%s", ip_str, VTY_NEWLINE);
          return CMD_WARNING;
        }
    }

  if (name)
    {
      bgp = bgp_lookup_by_name (name);

      if (! bgp)
        {
          vty_out (vty, "%% No such BGP instance exist%s", VTY_NEWLINE);
          return CMD_WARNING;
        }

      bgp_show_neighbor (vty, bgp, type, &su);

      return CMD_SUCCESS;
    }

  bgp = bgp_get_default ();

  if (bgp)
    bgp_show_neighbor (vty, bgp, type, &su);

  return CMD_SUCCESS;
}
