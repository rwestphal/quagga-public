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

#ifndef _QUAGGA_BGP_VTY_SHOW_H
#define _QUAGGA_BGP_VTY_SHOW_H

enum bgp_show_type
{
  bgp_show_type_normal,
  bgp_show_type_regexp,
  bgp_show_type_prefix_list,
  bgp_show_type_filter_list,
  bgp_show_type_route_map,
  bgp_show_type_neighbor,
  bgp_show_type_cidr_only,
  bgp_show_type_prefix_longer,
  bgp_show_type_community_all,
  bgp_show_type_community,
  bgp_show_type_community_exact,
  bgp_show_type_community_list,
  bgp_show_type_community_list_exact,
  bgp_show_type_flap_statistics,
  bgp_show_type_flap_address,
  bgp_show_type_flap_prefix,
  bgp_show_type_flap_cidr_only,
  bgp_show_type_flap_regexp,
  bgp_show_type_flap_filter_list,
  bgp_show_type_flap_prefix_list,
  bgp_show_type_flap_prefix_longer,
  bgp_show_type_flap_route_map,
  bgp_show_type_flap_neighbor,
  bgp_show_type_dampend_paths,
  bgp_show_type_damp_neighbor
};

enum bgp_stats
{
  BGP_STATS_MAXBITLEN = 0,
  BGP_STATS_RIB,
  BGP_STATS_PREFIXES,
  BGP_STATS_TOTPLEN,
  BGP_STATS_UNAGGREGATEABLE,
  BGP_STATS_MAX_AGGREGATEABLE,
  BGP_STATS_AGGREGATES,
  BGP_STATS_SPACE,
  BGP_STATS_ASPATH_COUNT,
  BGP_STATS_ASPATH_MAXHOPS,
  BGP_STATS_ASPATH_TOTHOPS,
  BGP_STATS_ASPATH_MAXSIZE,
  BGP_STATS_ASPATH_TOTSIZE,
  BGP_STATS_ASN_HIGHEST,
  BGP_STATS_MAX,
};

struct bgp_table_stats
{
  struct bgp_table *table;
  unsigned long long counts[BGP_STATS_MAX];
};

enum bgp_pcounts
{
  PCOUNT_ADJ_IN = 0,
  PCOUNT_DAMPED,
  PCOUNT_REMOVED,
  PCOUNT_HISTORY,
  PCOUNT_STALE,
  PCOUNT_VALID,
  PCOUNT_ALL,
  PCOUNT_COUNTED,
  PCOUNT_PFCNT, /* the figure we display to users */
  PCOUNT_MAX,
};

struct peer_pcounts
{
  unsigned int count[PCOUNT_MAX];
  const struct peer *peer;
  const struct bgp_table *table;
};

/* Show BGP peer's information. */
enum show_type
{
  show_all,
  show_peer
};

extern int bgp_show (struct vty *, struct bgp *, afi_t, safi_t,
                     enum bgp_show_type, void *);
extern int bgp_show_route (struct vty *, const char *, const char *, afi_t,
                           safi_t, struct prefix_rd *, int);

extern int bgp_show_regexp (struct vty *vty, int argc, const char **argv, afi_t afi,
		 safi_t safi, enum bgp_show_type type);

extern int bgp_show_prefix_list (struct vty *vty, const char *prefix_list_str, afi_t afi,
		      safi_t safi, enum bgp_show_type type);

extern int bgp_show_filter_list (struct vty *vty, const char *filter, afi_t afi,
		      safi_t safi, enum bgp_show_type type);

extern int bgp_show_route_map (struct vty *vty, const char *rmap_str, afi_t afi,
		    safi_t safi, enum bgp_show_type type);

extern int bgp_show_community (struct vty *vty, const char *view_name, int argc,
		    const char **argv, int exact, afi_t afi, safi_t safi);

extern int bgp_show_community_list (struct vty *vty, const char *com, int exact,
			 afi_t afi, safi_t safi);

extern int bgp_show_prefix_longer (struct vty *vty, const char *prefix, afi_t afi,
			safi_t safi, enum bgp_show_type type);

extern struct peer *peer_lookup_in_view (struct vty *vty, const char *view_name,
                     const char *ip_str);

extern int bgp_table_stats_vty (struct vty *vty, const char *name,
                     const char *afi_str, const char *safi_str);

extern int bgp_peer_counts (struct vty *vty, struct peer *peer, afi_t afi, safi_t safi);

extern int peer_adj_routes (struct vty *vty, struct peer *peer, afi_t afi, safi_t safi, int in);

extern int bgp_show_neighbor_route (struct vty *vty, struct peer *peer, afi_t afi,
			 safi_t safi, enum bgp_show_type type);

extern int bgp_show_table (struct vty *vty, struct bgp_table *table, struct in_addr *router_id,
	  enum bgp_show_type type, void *output_arg);

extern int show_adj_route_vpn (struct vty *vty, struct peer *peer, struct prefix_rd *prd);

extern int bgp_show_mpls_vpn (struct vty *vty, struct prefix_rd *prd, enum bgp_show_type type,
		   void *output_arg, int tags);

extern int
bgp_show_route_in_table (struct vty *vty, struct bgp *bgp,
                         struct bgp_table *rib, const char *ip_str,
                         afi_t afi, safi_t safi, struct prefix_rd *prd,
                         int prefix_check);

extern int
bgp_show_summary_vty (struct vty *vty, const char *name,
                      afi_t afi, safi_t safi);

extern int
bgp_show_neighbor_vty (struct vty *vty, const char *name,
                       enum show_type type, const char *ip_str);

extern int
bgp_show_rsclient_summary_vty (struct vty *vty, const char *name,
                               afi_t afi, safi_t safi);

extern void
bgp_show_peer (struct vty *vty, struct peer *p);

#endif /* _QUAGGA_BGP_VTY_SHOW_H */
