/* Auto-generated from bgp_vty_show.xml. */
/* Do not edit! */

#include <zebra.h>

#include "command.h"
#include "vty.h"
#include "bgp_vty_show.h"

DEFUN (show_bgp_ipv4_safi,
       show_bgp_ipv4_safi_cmd,
       "show bgp ipv4 (unicast|multicast)",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      NULL
    };
  return bgp_show_normal (vty, args);
}

DEFUN (show_bgp_ipv4_safi_filter_list_word,
       show_bgp_ipv4_safi_filter_list_word_cmd,
       "show bgp ipv4 (unicast|multicast) filter-list WORD",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes conforming to the filter-list\n"
       "Regular expression access list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "filter-list", .value = argv[1] },
      NULL
    };
  return bgp_show_filter_list (vty, args);
}

DEFUN (show_bgp_ipv4_safi_prefix_list_word,
       show_bgp_ipv4_safi_prefix_list_word_cmd,
       "show bgp ipv4 (unicast|multicast) prefix-list WORD",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes conforming to the prefix-list\n"
       "IP prefix-list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "prefix-list", .value = argv[1] },
      NULL
    };
  return bgp_show_prefix_list (vty, args);
}

DEFUN (show_bgp_ipv4_safi_regexp_line,
       show_bgp_ipv4_safi_regexp_line_cmd,
       "show bgp ipv4 (unicast|multicast) regexp .LINE",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the AS path regular expression\n"
       "A regular-expression to match the BGP AS paths\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "expr", .argc = argc - 1, .argv = argv + 1 },
      NULL
    };
  return bgp_show_regexp (vty, args);
}

DEFUN (show_bgp_ipv4_safi_route_map_word,
       show_bgp_ipv4_safi_route_map_word_cmd,
       "show bgp ipv4 (unicast|multicast) route-map WORD",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the route-map\n"
       "A route-map to match on\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "route-map", .value = argv[1] },
      NULL
    };
  return bgp_show_route_map (vty, args);
}

DEFUN (show_bgp_ipv4_safi_community,
       show_bgp_ipv4_safi_community_cmd,
       "show bgp ipv4 (unicast|multicast) community",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the communities\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      NULL
    };
  return bgp_show_community (vty, args);
}

DEFUN (show_bgp_ipv4_safi_community_community,
       show_bgp_ipv4_safi_community_community_cmd,
       "show bgp ipv4 (unicast|multicast) community (AA:NN|local-AS|no-advertise|no-export)",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "community", .value = argv[1] },
      NULL
    };
  return bgp_show_community (vty, args);
}

DEFUN (show_bgp_ipv4_safi_community_community_exact_match,
       show_bgp_ipv4_safi_community_community_exact_match_cmd,
       "show bgp ipv4 (unicast|multicast) community (AA:NN|local-AS|no-advertise|no-export) exact-match",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "Exact match of the communities\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "community", .value = argv[1] },
      &(struct vty_arg) { .name = "exact-match", .value = "exact-match" },
      NULL
    };
  return bgp_show_community (vty, args);
}

DEFUN (show_bgp_ipv4_safi_community_list_clist,
       show_bgp_ipv4_safi_community_list_clist_cmd,
       "show bgp ipv4 (unicast|multicast) community-list <1-500>",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the community-list\n"
       "community-list number\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "clist", .value = argv[1] },
      NULL
    };
  return bgp_show_community_list (vty, args);
}

DEFUN (show_bgp_ipv4_safi_community_list_clist_exact_match,
       show_bgp_ipv4_safi_community_list_clist_exact_match_cmd,
       "show bgp ipv4 (unicast|multicast) community-list <1-500> exact-match",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the community-list\n"
       "community-list number\n"
       "Exact match of the communities\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "clist", .value = argv[1] },
      &(struct vty_arg) { .name = "exact-match", .value = "exact-match" },
      NULL
    };
  return bgp_show_community_list (vty, args);
}

DEFUN (show_bgp_ipv4_safi_community_list_word,
       show_bgp_ipv4_safi_community_list_word_cmd,
       "show bgp ipv4 (unicast|multicast) community-list WORD",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the community-list\n"
       "extcommunity-list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "clist", .value = argv[1] },
      NULL
    };
  return bgp_show_community_list (vty, args);
}

DEFUN (show_bgp_ipv4_safi_community_list_word_exact_match,
       show_bgp_ipv4_safi_community_list_word_exact_match_cmd,
       "show bgp ipv4 (unicast|multicast) community-list WORD exact-match",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the community-list\n"
       "extcommunity-list name\n"
       "Exact match of the communities\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "clist", .value = argv[1] },
      &(struct vty_arg) { .name = "exact-match", .value = "exact-match" },
      NULL
    };
  return bgp_show_community_list (vty, args);
}

DEFUN (show_bgp_ipv4_safi_extcommunity_list_word,
       show_bgp_ipv4_safi_extcommunity_list_word_cmd,
       "show bgp ipv4 (unicast|multicast) extcommunity-list WORD",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the extcommunity-list\n"
       "extcommunity-list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "ext_clist", .value = argv[1] },
      NULL
    };
  return bgp_show_ext_community_list (vty, args);
}

DEFUN (show_bgp_ipv4_safi_neighbors,
       show_bgp_ipv4_safi_neighbors_cmd,
       "show bgp ipv4 (unicast|multicast) neighbors",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      NULL
    };
  return bgp_show_neighbor (vty, args);
}

DEFUN (show_bgp_ipv4_safi_neighbors_ipv4,
       show_bgp_ipv4_safi_neighbors_ipv4_cmd,
       "show bgp ipv4 (unicast|multicast) neighbors A.B.C.D",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_show_neighbor (vty, args);
}

DEFUN (show_bgp_ipv4_safi_neighbors_ipv4_advertised_routes,
       show_bgp_ipv4_safi_neighbors_ipv4_advertised_routes_cmd,
       "show bgp ipv4 (unicast|multicast) neighbors A.B.C.D advertised-routes",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the routes advertised to a BGP neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_show_adj (vty, args);
}

DEFUN (show_bgp_ipv4_safi_neighbors_ipv4_received_prefix_filter,
       show_bgp_ipv4_safi_neighbors_ipv4_received_prefix_filter_cmd,
       "show bgp ipv4 (unicast|multicast) neighbors A.B.C.D received prefix-filter",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display information received from a BGP neighbor\n"
       "Display the prefixlist filter\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_show_received_prefix_filter (vty, args);
}

DEFUN (show_bgp_ipv4_safi_neighbors_ipv4_received_routes,
       show_bgp_ipv4_safi_neighbors_ipv4_received_routes_cmd,
       "show bgp ipv4 (unicast|multicast) neighbors A.B.C.D received-routes",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the received routes from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "received", .value = "received-routes" },
      NULL
    };
  return bgp_show_adj (vty, args);
}

DEFUN (show_bgp_ipv4_safi_neighbors_ipv4_routes,
       show_bgp_ipv4_safi_neighbors_ipv4_routes_cmd,
       "show bgp ipv4 (unicast|multicast) neighbors A.B.C.D routes",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display routes learned from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_show_neighbor_route (vty, args);
}

DEFUN (show_bgp_ipv4_safi_neighbors_ipv6,
       show_bgp_ipv4_safi_neighbors_ipv6_cmd,
       "show bgp ipv4 (unicast|multicast) neighbors X:X::X:X",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_show_neighbor (vty, args);
}

DEFUN (show_bgp_ipv4_safi_neighbors_ipv6_advertised_routes,
       show_bgp_ipv4_safi_neighbors_ipv6_advertised_routes_cmd,
       "show bgp ipv4 (unicast|multicast) neighbors X:X::X:X advertised-routes",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the routes advertised to a BGP neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_show_adj (vty, args);
}

DEFUN (show_bgp_ipv4_safi_neighbors_ipv6_received_prefix_filter,
       show_bgp_ipv4_safi_neighbors_ipv6_received_prefix_filter_cmd,
       "show bgp ipv4 (unicast|multicast) neighbors X:X::X:X received prefix-filter",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display information received from a BGP neighbor\n"
       "Display the prefixlist filter\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_show_received_prefix_filter (vty, args);
}

DEFUN (show_bgp_ipv4_safi_neighbors_ipv6_received_routes,
       show_bgp_ipv4_safi_neighbors_ipv6_received_routes_cmd,
       "show bgp ipv4 (unicast|multicast) neighbors X:X::X:X received-routes",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the received routes from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "received", .value = "received-routes" },
      NULL
    };
  return bgp_show_adj (vty, args);
}

DEFUN (show_bgp_ipv4_safi_neighbors_ipv6_routes,
       show_bgp_ipv4_safi_neighbors_ipv6_routes_cmd,
       "show bgp ipv4 (unicast|multicast) neighbors X:X::X:X routes",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display routes learned from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_show_neighbor_route (vty, args);
}

DEFUN (show_bgp_ipv4_safi_paths,
       show_bgp_ipv4_safi_paths_cmd,
       "show bgp ipv4 (unicast|multicast) paths",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Path information\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      NULL
    };
  return bgp_show_paths (vty, args);
}

DEFUN (show_bgp_ipv4_safi_summary,
       show_bgp_ipv4_safi_summary_cmd,
       "show bgp ipv4 (unicast|multicast) summary",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Summary of BGP neighbor status\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      NULL
    };
  return bgp_show_summary (vty, args);
}

DEFUN (show_bgp_ipv4_safi_dampening_dampened_paths,
       show_bgp_ipv4_safi_dampening_dampened_paths_cmd,
       "show bgp ipv4 (unicast|multicast) dampening dampened-paths",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display detailed information about dampening\n"
       "Display paths suppressed due to dampening\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "dampened-paths", .value = "dampened-paths" },
      NULL
    };
  return bgp_show_normal (vty, args);
}

DEFUN (show_bgp_ipv4_safi_dampening_flap_statistics,
       show_bgp_ipv4_safi_dampening_flap_statistics_cmd,
       "show bgp ipv4 (unicast|multicast) dampening flap-statistics",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display detailed information about dampening\n"
       "Display flap statistics of routes\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "flap-statistics", .value = "flap-statistics" },
      NULL
    };
  return bgp_show_normal (vty, args);
}

DEFUN (show_bgp_ipv4_safi_dampening_flap_statistics_filter_list_word,
       show_bgp_ipv4_safi_dampening_flap_statistics_filter_list_word_cmd,
       "show bgp ipv4 (unicast|multicast) dampening flap-statistics filter-list WORD",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display detailed information about dampening\n"
       "Display flap statistics of routes\n"
       "Display routes conforming to the filter-list\n"
       "Regular expression access list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "flap-statistics", .value = "flap-statistics" },
      &(struct vty_arg) { .name = "filter-list", .value = argv[1] },
      NULL
    };
  return bgp_show_filter_list (vty, args);
}

DEFUN (show_bgp_ipv4_safi_dampening_flap_statistics_prefix_list_word,
       show_bgp_ipv4_safi_dampening_flap_statistics_prefix_list_word_cmd,
       "show bgp ipv4 (unicast|multicast) dampening flap-statistics prefix-list WORD",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display detailed information about dampening\n"
       "Display flap statistics of routes\n"
       "Display routes conforming to the prefix-list\n"
       "IP prefix-list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "flap-statistics", .value = "flap-statistics" },
      &(struct vty_arg) { .name = "prefix-list", .value = argv[1] },
      NULL
    };
  return bgp_show_prefix_list (vty, args);
}

DEFUN (show_bgp_ipv4_safi_dampening_flap_statistics_regexp_line,
       show_bgp_ipv4_safi_dampening_flap_statistics_regexp_line_cmd,
       "show bgp ipv4 (unicast|multicast) dampening flap-statistics regexp .LINE",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display detailed information about dampening\n"
       "Display flap statistics of routes\n"
       "Display routes matching the AS path regular expression\n"
       "A regular-expression to match the BGP AS paths\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "flap-statistics", .value = "flap-statistics" },
      &(struct vty_arg) { .name = "expr", .argc = argc - 1, .argv = argv + 1 },
      NULL
    };
  return bgp_show_regexp (vty, args);
}

DEFUN (show_bgp_ipv4_safi_dampening_flap_statistics_route_map_word,
       show_bgp_ipv4_safi_dampening_flap_statistics_route_map_word_cmd,
       "show bgp ipv4 (unicast|multicast) dampening flap-statistics route-map WORD",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display detailed information about dampening\n"
       "Display flap statistics of routes\n"
       "Display routes matching the route-map\n"
       "A route-map to match on\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "flap-statistics", .value = "flap-statistics" },
      &(struct vty_arg) { .name = "route-map", .value = argv[1] },
      NULL
    };
  return bgp_show_route_map (vty, args);
}

DEFUN (show_bgp_ipv4_safi_dampening_flap_statistics_cidr_only,
       show_bgp_ipv4_safi_dampening_flap_statistics_cidr_only_cmd,
       "show bgp ipv4 (unicast|multicast) dampening flap-statistics cidr-only",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display detailed information about dampening\n"
       "Display flap statistics of routes\n"
       "Display only routes with non-natural netmasks\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "flap-statistics", .value = "flap-statistics" },
      &(struct vty_arg) { .name = "cidr", .value = "cidr-only" },
      NULL
    };
  return bgp_show_cidr_only (vty, args);
}

DEFUN (show_bgp_ipv4_safi_dampening_flap_statistics_ipv4,
       show_bgp_ipv4_safi_dampening_flap_statistics_ipv4_cmd,
       "show bgp ipv4 (unicast|multicast) dampening flap-statistics A.B.C.D",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display detailed information about dampening\n"
       "Display flap statistics of routes\n"
       "Network in the BGP routing table to display\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "flap-statistics", .value = "flap-statistics" },
      &(struct vty_arg) { .name = "network", .value = argv[1] },
      NULL
    };
  return bgp_show_route_flap (vty, args);
}

DEFUN (show_bgp_ipv4_safi_dampening_flap_statistics_ipv4m,
       show_bgp_ipv4_safi_dampening_flap_statistics_ipv4m_cmd,
       "show bgp ipv4 (unicast|multicast) dampening flap-statistics A.B.C.D/M",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display detailed information about dampening\n"
       "Display flap statistics of routes\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "flap-statistics", .value = "flap-statistics" },
      &(struct vty_arg) { .name = "prefix", .value = argv[1] },
      NULL
    };
  return bgp_show_route_flap (vty, args);
}

DEFUN (show_bgp_ipv4_safi_dampening_flap_statistics_ipv4m_longer_prefixes,
       show_bgp_ipv4_safi_dampening_flap_statistics_ipv4m_longer_prefixes_cmd,
       "show bgp ipv4 (unicast|multicast) dampening flap-statistics A.B.C.D/M longer-prefixes",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display detailed information about dampening\n"
       "Display flap statistics of routes\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Display route and more specific routes\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "flap-statistics", .value = "flap-statistics" },
      &(struct vty_arg) { .name = "prefix", .value = argv[1] },
      NULL
    };
  return bgp_show_prefix_longer (vty, args);
}

DEFUN (show_bgp_ipv4_safi_neighbors_ipv4_dampened_routes,
       show_bgp_ipv4_safi_neighbors_ipv4_dampened_routes_cmd,
       "show bgp ipv4 (unicast|multicast) neighbors A.B.C.D dampened-routes",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the dampened routes received from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "dampened-routes", .value = "dampened-routes" },
      NULL
    };
  return bgp_show_neighbor_route (vty, args);
}

DEFUN (show_bgp_ipv4_safi_neighbors_ipv4_flap_statistics,
       show_bgp_ipv4_safi_neighbors_ipv4_flap_statistics_cmd,
       "show bgp ipv4 (unicast|multicast) neighbors A.B.C.D flap-statistics",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display flap statistics of the routes learned from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "flap-statistics", .value = "flap-statistics" },
      NULL
    };
  return bgp_show_neighbor_route (vty, args);
}

DEFUN (show_bgp_ipv4_safi_cidr_only,
       show_bgp_ipv4_safi_cidr_only_cmd,
       "show bgp ipv4 (unicast|multicast) cidr-only",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display only routes with non-natural netmasks\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "cidr", .value = "cidr-only" },
      NULL
    };
  return bgp_show_cidr_only (vty, args);
}

DEFUN (show_bgp_ipv4_safi_ipv4,
       show_bgp_ipv4_safi_ipv4_cmd,
       "show bgp ipv4 (unicast|multicast) A.B.C.D",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Network in the BGP routing table to display\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "network", .value = argv[1] },
      NULL
    };
  return bgp_show_route (vty, args);
}

DEFUN (show_bgp_ipv4_safi_ipv4m,
       show_bgp_ipv4_safi_ipv4m_cmd,
       "show bgp ipv4 (unicast|multicast) A.B.C.D/M",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "prefix", .value = argv[1] },
      NULL
    };
  return bgp_show_route (vty, args);
}

DEFUN (show_bgp_ipv4_safi_ipv4m_longer_prefixes,
       show_bgp_ipv4_safi_ipv4m_longer_prefixes_cmd,
       "show bgp ipv4 (unicast|multicast) A.B.C.D/M longer-prefixes",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Display route and more specific routes\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "prefix", .value = argv[1] },
      NULL
    };
  return bgp_show_prefix_longer (vty, args);
}

DEFUN (show_bgp_ipv4_safi_statistics,
       show_bgp_ipv4_safi_statistics_cmd,
       "show bgp ipv4 (unicast|multicast) statistics",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP RIB advertisement statistics\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      NULL
    };
  return bgp_show_stats (vty, args);
}

DEFUN (show_bgp_ipv4_safi_neighbors_ipv4_prefix_counts,
       show_bgp_ipv4_safi_neighbors_ipv4_prefix_counts_cmd,
       "show bgp ipv4 (unicast|multicast) neighbors A.B.C.D prefix-counts",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display detailed prefix count information\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_peer_counts (vty, args);
}

DEFUN (show_bgp_ipv4_safi_neighbors_ipv6_prefix_counts,
       show_bgp_ipv4_safi_neighbors_ipv6_prefix_counts_cmd,
       "show bgp ipv4 (unicast|multicast) neighbors X:X::X:X prefix-counts",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display detailed prefix count information\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_peer_counts (vty, args);
}

DEFUN (show_bgp_ipv6_safi,
       show_bgp_ipv6_safi_cmd,
       "show bgp ipv6 (unicast|multicast)",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      NULL
    };
  return bgp_show_normal (vty, args);
}

DEFUN (show_bgp_ipv6_safi_filter_list_word,
       show_bgp_ipv6_safi_filter_list_word_cmd,
       "show bgp ipv6 (unicast|multicast) filter-list WORD",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes conforming to the filter-list\n"
       "Regular expression access list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "filter-list", .value = argv[1] },
      NULL
    };
  return bgp_show_filter_list (vty, args);
}

DEFUN (show_bgp_ipv6_safi_prefix_list_word,
       show_bgp_ipv6_safi_prefix_list_word_cmd,
       "show bgp ipv6 (unicast|multicast) prefix-list WORD",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes conforming to the prefix-list\n"
       "IP prefix-list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "prefix-list", .value = argv[1] },
      NULL
    };
  return bgp_show_prefix_list (vty, args);
}

DEFUN (show_bgp_ipv6_safi_regexp_line,
       show_bgp_ipv6_safi_regexp_line_cmd,
       "show bgp ipv6 (unicast|multicast) regexp .LINE",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the AS path regular expression\n"
       "A regular-expression to match the BGP AS paths\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "expr", .argc = argc - 1, .argv = argv + 1 },
      NULL
    };
  return bgp_show_regexp (vty, args);
}

DEFUN (show_bgp_ipv6_safi_route_map_word,
       show_bgp_ipv6_safi_route_map_word_cmd,
       "show bgp ipv6 (unicast|multicast) route-map WORD",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the route-map\n"
       "A route-map to match on\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "route-map", .value = argv[1] },
      NULL
    };
  return bgp_show_route_map (vty, args);
}

DEFUN (show_bgp_ipv6_safi_community,
       show_bgp_ipv6_safi_community_cmd,
       "show bgp ipv6 (unicast|multicast) community",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the communities\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      NULL
    };
  return bgp_show_community (vty, args);
}

DEFUN (show_bgp_ipv6_safi_community_community,
       show_bgp_ipv6_safi_community_community_cmd,
       "show bgp ipv6 (unicast|multicast) community (AA:NN|local-AS|no-advertise|no-export)",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "community", .value = argv[1] },
      NULL
    };
  return bgp_show_community (vty, args);
}

DEFUN (show_bgp_ipv6_safi_community_community_exact_match,
       show_bgp_ipv6_safi_community_community_exact_match_cmd,
       "show bgp ipv6 (unicast|multicast) community (AA:NN|local-AS|no-advertise|no-export) exact-match",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "Exact match of the communities\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "community", .value = argv[1] },
      &(struct vty_arg) { .name = "exact-match", .value = "exact-match" },
      NULL
    };
  return bgp_show_community (vty, args);
}

DEFUN (show_bgp_ipv6_safi_community_list_clist,
       show_bgp_ipv6_safi_community_list_clist_cmd,
       "show bgp ipv6 (unicast|multicast) community-list <1-500>",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the community-list\n"
       "community-list number\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "clist", .value = argv[1] },
      NULL
    };
  return bgp_show_community_list (vty, args);
}

DEFUN (show_bgp_ipv6_safi_community_list_clist_exact_match,
       show_bgp_ipv6_safi_community_list_clist_exact_match_cmd,
       "show bgp ipv6 (unicast|multicast) community-list <1-500> exact-match",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the community-list\n"
       "community-list number\n"
       "Exact match of the communities\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "clist", .value = argv[1] },
      &(struct vty_arg) { .name = "exact-match", .value = "exact-match" },
      NULL
    };
  return bgp_show_community_list (vty, args);
}

DEFUN (show_bgp_ipv6_safi_community_list_word,
       show_bgp_ipv6_safi_community_list_word_cmd,
       "show bgp ipv6 (unicast|multicast) community-list WORD",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the community-list\n"
       "extcommunity-list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "clist", .value = argv[1] },
      NULL
    };
  return bgp_show_community_list (vty, args);
}

DEFUN (show_bgp_ipv6_safi_community_list_word_exact_match,
       show_bgp_ipv6_safi_community_list_word_exact_match_cmd,
       "show bgp ipv6 (unicast|multicast) community-list WORD exact-match",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the community-list\n"
       "extcommunity-list name\n"
       "Exact match of the communities\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "clist", .value = argv[1] },
      &(struct vty_arg) { .name = "exact-match", .value = "exact-match" },
      NULL
    };
  return bgp_show_community_list (vty, args);
}

DEFUN (show_bgp_ipv6_safi_extcommunity_list_word,
       show_bgp_ipv6_safi_extcommunity_list_word_cmd,
       "show bgp ipv6 (unicast|multicast) extcommunity-list WORD",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the extcommunity-list\n"
       "extcommunity-list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "ext_clist", .value = argv[1] },
      NULL
    };
  return bgp_show_ext_community_list (vty, args);
}

DEFUN (show_bgp_ipv6_safi_neighbors,
       show_bgp_ipv6_safi_neighbors_cmd,
       "show bgp ipv6 (unicast|multicast) neighbors",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      NULL
    };
  return bgp_show_neighbor (vty, args);
}

DEFUN (show_bgp_ipv6_safi_neighbors_ipv4,
       show_bgp_ipv6_safi_neighbors_ipv4_cmd,
       "show bgp ipv6 (unicast|multicast) neighbors A.B.C.D",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_show_neighbor (vty, args);
}

DEFUN (show_bgp_ipv6_safi_neighbors_ipv4_advertised_routes,
       show_bgp_ipv6_safi_neighbors_ipv4_advertised_routes_cmd,
       "show bgp ipv6 (unicast|multicast) neighbors A.B.C.D advertised-routes",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the routes advertised to a BGP neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_show_adj (vty, args);
}

DEFUN (show_bgp_ipv6_safi_neighbors_ipv4_received_prefix_filter,
       show_bgp_ipv6_safi_neighbors_ipv4_received_prefix_filter_cmd,
       "show bgp ipv6 (unicast|multicast) neighbors A.B.C.D received prefix-filter",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display information received from a BGP neighbor\n"
       "Display the prefixlist filter\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_show_received_prefix_filter (vty, args);
}

DEFUN (show_bgp_ipv6_safi_neighbors_ipv4_received_routes,
       show_bgp_ipv6_safi_neighbors_ipv4_received_routes_cmd,
       "show bgp ipv6 (unicast|multicast) neighbors A.B.C.D received-routes",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the received routes from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "received", .value = "received-routes" },
      NULL
    };
  return bgp_show_adj (vty, args);
}

DEFUN (show_bgp_ipv6_safi_neighbors_ipv4_routes,
       show_bgp_ipv6_safi_neighbors_ipv4_routes_cmd,
       "show bgp ipv6 (unicast|multicast) neighbors A.B.C.D routes",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display routes learned from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_show_neighbor_route (vty, args);
}

DEFUN (show_bgp_ipv6_safi_neighbors_ipv6,
       show_bgp_ipv6_safi_neighbors_ipv6_cmd,
       "show bgp ipv6 (unicast|multicast) neighbors X:X::X:X",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_show_neighbor (vty, args);
}

DEFUN (show_bgp_ipv6_safi_neighbors_ipv6_advertised_routes,
       show_bgp_ipv6_safi_neighbors_ipv6_advertised_routes_cmd,
       "show bgp ipv6 (unicast|multicast) neighbors X:X::X:X advertised-routes",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the routes advertised to a BGP neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_show_adj (vty, args);
}

DEFUN (show_bgp_ipv6_safi_neighbors_ipv6_received_prefix_filter,
       show_bgp_ipv6_safi_neighbors_ipv6_received_prefix_filter_cmd,
       "show bgp ipv6 (unicast|multicast) neighbors X:X::X:X received prefix-filter",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display information received from a BGP neighbor\n"
       "Display the prefixlist filter\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_show_received_prefix_filter (vty, args);
}

DEFUN (show_bgp_ipv6_safi_neighbors_ipv6_received_routes,
       show_bgp_ipv6_safi_neighbors_ipv6_received_routes_cmd,
       "show bgp ipv6 (unicast|multicast) neighbors X:X::X:X received-routes",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the received routes from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "received", .value = "received-routes" },
      NULL
    };
  return bgp_show_adj (vty, args);
}

DEFUN (show_bgp_ipv6_safi_neighbors_ipv6_routes,
       show_bgp_ipv6_safi_neighbors_ipv6_routes_cmd,
       "show bgp ipv6 (unicast|multicast) neighbors X:X::X:X routes",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display routes learned from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_show_neighbor_route (vty, args);
}

DEFUN (show_bgp_ipv6_safi_paths,
       show_bgp_ipv6_safi_paths_cmd,
       "show bgp ipv6 (unicast|multicast) paths",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Path information\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      NULL
    };
  return bgp_show_paths (vty, args);
}

DEFUN (show_bgp_ipv6_safi_summary,
       show_bgp_ipv6_safi_summary_cmd,
       "show bgp ipv6 (unicast|multicast) summary",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Summary of BGP neighbor status\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      NULL
    };
  return bgp_show_summary (vty, args);
}

DEFUN (show_bgp_ipv6_safi_ipv6m,
       show_bgp_ipv6_safi_ipv6m_cmd,
       "show bgp ipv6 (unicast|multicast) X:X::X:X/M",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Network in the BGP routing table to display\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "prefix", .value = argv[1] },
      NULL
    };
  return bgp_show_route (vty, args);
}

DEFUN (show_bgp_ipv6_safi_ipv6m_longer_prefixes,
       show_bgp_ipv6_safi_ipv6m_longer_prefixes_cmd,
       "show bgp ipv6 (unicast|multicast) X:X::X:X/M longer-prefixes",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Network in the BGP routing table to display\n"
       "Display route and more specific routes\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "prefix", .value = argv[1] },
      NULL
    };
  return bgp_show_prefix_longer (vty, args);
}

DEFUN (show_bgp_ipv6_safi_statistics,
       show_bgp_ipv6_safi_statistics_cmd,
       "show bgp ipv6 (unicast|multicast) statistics",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP RIB advertisement statistics\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      NULL
    };
  return bgp_show_stats (vty, args);
}

DEFUN (show_bgp_ipv6_safi_neighbors_ipv4_prefix_counts,
       show_bgp_ipv6_safi_neighbors_ipv4_prefix_counts_cmd,
       "show bgp ipv6 (unicast|multicast) neighbors A.B.C.D prefix-counts",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display detailed prefix count information\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_peer_counts (vty, args);
}

DEFUN (show_bgp_ipv6_safi_neighbors_ipv6_prefix_counts,
       show_bgp_ipv6_safi_neighbors_ipv6_prefix_counts_cmd,
       "show bgp ipv6 (unicast|multicast) neighbors X:X::X:X prefix-counts",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display detailed prefix count information\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_peer_counts (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_all,
       show_bgp_vpnv4_unicast_all_cmd,
       "show bgp vpnv4 unicast all",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      NULL
    };
  return bgp_show_normal (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_all_filter_list_word,
       show_bgp_vpnv4_unicast_all_filter_list_word_cmd,
       "show bgp vpnv4 unicast all filter-list WORD",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Display routes conforming to the filter-list\n"
       "Regular expression access list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "filter-list", .value = argv[0] },
      NULL
    };
  return bgp_show_filter_list (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_all_prefix_list_word,
       show_bgp_vpnv4_unicast_all_prefix_list_word_cmd,
       "show bgp vpnv4 unicast all prefix-list WORD",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Display routes conforming to the prefix-list\n"
       "IP prefix-list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "prefix-list", .value = argv[0] },
      NULL
    };
  return bgp_show_prefix_list (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_all_regexp_line,
       show_bgp_vpnv4_unicast_all_regexp_line_cmd,
       "show bgp vpnv4 unicast all regexp .LINE",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Display routes matching the AS path regular expression\n"
       "A regular-expression to match the BGP AS paths\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "expr", .argc = argc, .argv = argv },
      NULL
    };
  return bgp_show_regexp (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_all_route_map_word,
       show_bgp_vpnv4_unicast_all_route_map_word_cmd,
       "show bgp vpnv4 unicast all route-map WORD",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Display routes matching the route-map\n"
       "A route-map to match on\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "route-map", .value = argv[0] },
      NULL
    };
  return bgp_show_route_map (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_all_community,
       show_bgp_vpnv4_unicast_all_community_cmd,
       "show bgp vpnv4 unicast all community",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Display routes matching the communities\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      NULL
    };
  return bgp_show_community (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_all_community_community,
       show_bgp_vpnv4_unicast_all_community_community_cmd,
       "show bgp vpnv4 unicast all community (AA:NN|local-AS|no-advertise|no-export)",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "community", .value = argv[0] },
      NULL
    };
  return bgp_show_community (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_all_community_community_exact_match,
       show_bgp_vpnv4_unicast_all_community_community_exact_match_cmd,
       "show bgp vpnv4 unicast all community (AA:NN|local-AS|no-advertise|no-export) exact-match",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "Exact match of the communities\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "community", .value = argv[0] },
      &(struct vty_arg) { .name = "exact-match", .value = "exact-match" },
      NULL
    };
  return bgp_show_community (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_all_community_list_clist,
       show_bgp_vpnv4_unicast_all_community_list_clist_cmd,
       "show bgp vpnv4 unicast all community-list <1-500>",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Display routes matching the community-list\n"
       "community-list number\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "clist", .value = argv[0] },
      NULL
    };
  return bgp_show_community_list (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_all_community_list_clist_exact_match,
       show_bgp_vpnv4_unicast_all_community_list_clist_exact_match_cmd,
       "show bgp vpnv4 unicast all community-list <1-500> exact-match",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Display routes matching the community-list\n"
       "community-list number\n"
       "Exact match of the communities\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "clist", .value = argv[0] },
      &(struct vty_arg) { .name = "exact-match", .value = "exact-match" },
      NULL
    };
  return bgp_show_community_list (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_all_community_list_word,
       show_bgp_vpnv4_unicast_all_community_list_word_cmd,
       "show bgp vpnv4 unicast all community-list WORD",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Display routes matching the community-list\n"
       "extcommunity-list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "clist", .value = argv[0] },
      NULL
    };
  return bgp_show_community_list (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_all_community_list_word_exact_match,
       show_bgp_vpnv4_unicast_all_community_list_word_exact_match_cmd,
       "show bgp vpnv4 unicast all community-list WORD exact-match",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Display routes matching the community-list\n"
       "extcommunity-list name\n"
       "Exact match of the communities\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "clist", .value = argv[0] },
      &(struct vty_arg) { .name = "exact-match", .value = "exact-match" },
      NULL
    };
  return bgp_show_community_list (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_all_extcommunity_list_word,
       show_bgp_vpnv4_unicast_all_extcommunity_list_word_cmd,
       "show bgp vpnv4 unicast all extcommunity-list WORD",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Display routes matching the extcommunity-list\n"
       "extcommunity-list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "ext_clist", .value = argv[0] },
      NULL
    };
  return bgp_show_ext_community_list (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_all_neighbors,
       show_bgp_vpnv4_unicast_all_neighbors_cmd,
       "show bgp vpnv4 unicast all neighbors",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Detailed information on TCP and BGP neighbor connections\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      NULL
    };
  return bgp_show_neighbor (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_all_neighbors_ipv4,
       show_bgp_vpnv4_unicast_all_neighbors_ipv4_cmd,
       "show bgp vpnv4 unicast all neighbors A.B.C.D",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      NULL
    };
  return bgp_show_neighbor (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_all_neighbors_ipv4_advertised_routes,
       show_bgp_vpnv4_unicast_all_neighbors_ipv4_advertised_routes_cmd,
       "show bgp vpnv4 unicast all neighbors A.B.C.D advertised-routes",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the routes advertised to a BGP neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      NULL
    };
  return bgp_show_adj (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_all_neighbors_ipv4_received_prefix_filter,
       show_bgp_vpnv4_unicast_all_neighbors_ipv4_received_prefix_filter_cmd,
       "show bgp vpnv4 unicast all neighbors A.B.C.D received prefix-filter",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display information received from a BGP neighbor\n"
       "Display the prefixlist filter\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      NULL
    };
  return bgp_show_received_prefix_filter (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_all_neighbors_ipv4_received_routes,
       show_bgp_vpnv4_unicast_all_neighbors_ipv4_received_routes_cmd,
       "show bgp vpnv4 unicast all neighbors A.B.C.D received-routes",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the received routes from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      &(struct vty_arg) { .name = "received", .value = "received-routes" },
      NULL
    };
  return bgp_show_adj (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_all_neighbors_ipv4_routes,
       show_bgp_vpnv4_unicast_all_neighbors_ipv4_routes_cmd,
       "show bgp vpnv4 unicast all neighbors A.B.C.D routes",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display routes learned from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      NULL
    };
  return bgp_show_neighbor_route (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_all_neighbors_ipv6,
       show_bgp_vpnv4_unicast_all_neighbors_ipv6_cmd,
       "show bgp vpnv4 unicast all neighbors X:X::X:X",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      NULL
    };
  return bgp_show_neighbor (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_all_neighbors_ipv6_advertised_routes,
       show_bgp_vpnv4_unicast_all_neighbors_ipv6_advertised_routes_cmd,
       "show bgp vpnv4 unicast all neighbors X:X::X:X advertised-routes",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the routes advertised to a BGP neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      NULL
    };
  return bgp_show_adj (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_all_neighbors_ipv6_received_prefix_filter,
       show_bgp_vpnv4_unicast_all_neighbors_ipv6_received_prefix_filter_cmd,
       "show bgp vpnv4 unicast all neighbors X:X::X:X received prefix-filter",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display information received from a BGP neighbor\n"
       "Display the prefixlist filter\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      NULL
    };
  return bgp_show_received_prefix_filter (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_all_neighbors_ipv6_received_routes,
       show_bgp_vpnv4_unicast_all_neighbors_ipv6_received_routes_cmd,
       "show bgp vpnv4 unicast all neighbors X:X::X:X received-routes",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the received routes from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      &(struct vty_arg) { .name = "received", .value = "received-routes" },
      NULL
    };
  return bgp_show_adj (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_all_neighbors_ipv6_routes,
       show_bgp_vpnv4_unicast_all_neighbors_ipv6_routes_cmd,
       "show bgp vpnv4 unicast all neighbors X:X::X:X routes",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display routes learned from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      NULL
    };
  return bgp_show_neighbor_route (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_all_paths,
       show_bgp_vpnv4_unicast_all_paths_cmd,
       "show bgp vpnv4 unicast all paths",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Path information\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      NULL
    };
  return bgp_show_paths (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_all_summary,
       show_bgp_vpnv4_unicast_all_summary_cmd,
       "show bgp vpnv4 unicast all summary",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Summary of BGP neighbor status\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      NULL
    };
  return bgp_show_summary (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_all_cidr_only,
       show_bgp_vpnv4_unicast_all_cidr_only_cmd,
       "show bgp vpnv4 unicast all cidr-only",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Display only routes with non-natural netmasks\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "cidr", .value = "cidr-only" },
      NULL
    };
  return bgp_show_cidr_only (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_all_ipv4,
       show_bgp_vpnv4_unicast_all_ipv4_cmd,
       "show bgp vpnv4 unicast all A.B.C.D",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Network in the BGP routing table to display\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "network", .value = argv[0] },
      NULL
    };
  return bgp_show_route (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_all_ipv4m,
       show_bgp_vpnv4_unicast_all_ipv4m_cmd,
       "show bgp vpnv4 unicast all A.B.C.D/M",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "prefix", .value = argv[0] },
      NULL
    };
  return bgp_show_route (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_all_ipv4m_longer_prefixes,
       show_bgp_vpnv4_unicast_all_ipv4m_longer_prefixes_cmd,
       "show bgp vpnv4 unicast all A.B.C.D/M longer-prefixes",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Display route and more specific routes\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "prefix", .value = argv[0] },
      NULL
    };
  return bgp_show_prefix_longer (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_all_labels,
       show_bgp_vpnv4_unicast_all_labels_cmd,
       "show bgp vpnv4 unicast all labels",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Display BGP labels for prefixes\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      NULL
    };
  return bgp_show_labels (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_rd_rd,
       show_bgp_vpnv4_unicast_rd_rd_cmd,
       "show bgp vpnv4 unicast rd ASN:nn_or_IP-address:nn",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[0] },
      NULL
    };
  return bgp_show_normal (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_rd_rd_filter_list_word,
       show_bgp_vpnv4_unicast_rd_rd_filter_list_word_cmd,
       "show bgp vpnv4 unicast rd ASN:nn_or_IP-address:nn filter-list WORD",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Display routes conforming to the filter-list\n"
       "Regular expression access list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[0] },
      &(struct vty_arg) { .name = "filter-list", .value = argv[1] },
      NULL
    };
  return bgp_show_filter_list (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_rd_rd_prefix_list_word,
       show_bgp_vpnv4_unicast_rd_rd_prefix_list_word_cmd,
       "show bgp vpnv4 unicast rd ASN:nn_or_IP-address:nn prefix-list WORD",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Display routes conforming to the prefix-list\n"
       "IP prefix-list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[0] },
      &(struct vty_arg) { .name = "prefix-list", .value = argv[1] },
      NULL
    };
  return bgp_show_prefix_list (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_rd_rd_regexp_line,
       show_bgp_vpnv4_unicast_rd_rd_regexp_line_cmd,
       "show bgp vpnv4 unicast rd ASN:nn_or_IP-address:nn regexp .LINE",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Display routes matching the AS path regular expression\n"
       "A regular-expression to match the BGP AS paths\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[0] },
      &(struct vty_arg) { .name = "expr", .argc = argc - 1, .argv = argv + 1 },
      NULL
    };
  return bgp_show_regexp (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_rd_rd_route_map_word,
       show_bgp_vpnv4_unicast_rd_rd_route_map_word_cmd,
       "show bgp vpnv4 unicast rd ASN:nn_or_IP-address:nn route-map WORD",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Display routes matching the route-map\n"
       "A route-map to match on\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[0] },
      &(struct vty_arg) { .name = "route-map", .value = argv[1] },
      NULL
    };
  return bgp_show_route_map (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_rd_rd_community,
       show_bgp_vpnv4_unicast_rd_rd_community_cmd,
       "show bgp vpnv4 unicast rd ASN:nn_or_IP-address:nn community",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Display routes matching the communities\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[0] },
      NULL
    };
  return bgp_show_community (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_rd_rd_community_community,
       show_bgp_vpnv4_unicast_rd_rd_community_community_cmd,
       "show bgp vpnv4 unicast rd ASN:nn_or_IP-address:nn community (AA:NN|local-AS|no-advertise|no-export)",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[0] },
      &(struct vty_arg) { .name = "community", .value = argv[1] },
      NULL
    };
  return bgp_show_community (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_rd_rd_community_community_exact_match,
       show_bgp_vpnv4_unicast_rd_rd_community_community_exact_match_cmd,
       "show bgp vpnv4 unicast rd ASN:nn_or_IP-address:nn community (AA:NN|local-AS|no-advertise|no-export) exact-match",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "Exact match of the communities\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[0] },
      &(struct vty_arg) { .name = "community", .value = argv[1] },
      &(struct vty_arg) { .name = "exact-match", .value = "exact-match" },
      NULL
    };
  return bgp_show_community (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_rd_rd_community_list_clist,
       show_bgp_vpnv4_unicast_rd_rd_community_list_clist_cmd,
       "show bgp vpnv4 unicast rd ASN:nn_or_IP-address:nn community-list <1-500>",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Display routes matching the community-list\n"
       "community-list number\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[0] },
      &(struct vty_arg) { .name = "clist", .value = argv[1] },
      NULL
    };
  return bgp_show_community_list (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_rd_rd_community_list_clist_exact_match,
       show_bgp_vpnv4_unicast_rd_rd_community_list_clist_exact_match_cmd,
       "show bgp vpnv4 unicast rd ASN:nn_or_IP-address:nn community-list <1-500> exact-match",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Display routes matching the community-list\n"
       "community-list number\n"
       "Exact match of the communities\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[0] },
      &(struct vty_arg) { .name = "clist", .value = argv[1] },
      &(struct vty_arg) { .name = "exact-match", .value = "exact-match" },
      NULL
    };
  return bgp_show_community_list (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_rd_rd_community_list_word,
       show_bgp_vpnv4_unicast_rd_rd_community_list_word_cmd,
       "show bgp vpnv4 unicast rd ASN:nn_or_IP-address:nn community-list WORD",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Display routes matching the community-list\n"
       "extcommunity-list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[0] },
      &(struct vty_arg) { .name = "clist", .value = argv[1] },
      NULL
    };
  return bgp_show_community_list (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_rd_rd_community_list_word_exact_match,
       show_bgp_vpnv4_unicast_rd_rd_community_list_word_exact_match_cmd,
       "show bgp vpnv4 unicast rd ASN:nn_or_IP-address:nn community-list WORD exact-match",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Display routes matching the community-list\n"
       "extcommunity-list name\n"
       "Exact match of the communities\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[0] },
      &(struct vty_arg) { .name = "clist", .value = argv[1] },
      &(struct vty_arg) { .name = "exact-match", .value = "exact-match" },
      NULL
    };
  return bgp_show_community_list (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_rd_rd_extcommunity_list_word,
       show_bgp_vpnv4_unicast_rd_rd_extcommunity_list_word_cmd,
       "show bgp vpnv4 unicast rd ASN:nn_or_IP-address:nn extcommunity-list WORD",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Display routes matching the extcommunity-list\n"
       "extcommunity-list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[0] },
      &(struct vty_arg) { .name = "ext_clist", .value = argv[1] },
      NULL
    };
  return bgp_show_ext_community_list (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_rd_rd_neighbors,
       show_bgp_vpnv4_unicast_rd_rd_neighbors_cmd,
       "show bgp vpnv4 unicast rd ASN:nn_or_IP-address:nn neighbors",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Detailed information on TCP and BGP neighbor connections\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[0] },
      NULL
    };
  return bgp_show_neighbor (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv4,
       show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv4_cmd,
       "show bgp vpnv4 unicast rd ASN:nn_or_IP-address:nn neighbors A.B.C.D",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_show_neighbor (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv4_advertised_routes,
       show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv4_advertised_routes_cmd,
       "show bgp vpnv4 unicast rd ASN:nn_or_IP-address:nn neighbors A.B.C.D advertised-routes",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the routes advertised to a BGP neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_show_adj (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv4_received_prefix_filter,
       show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv4_received_prefix_filter_cmd,
       "show bgp vpnv4 unicast rd ASN:nn_or_IP-address:nn neighbors A.B.C.D received prefix-filter",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display information received from a BGP neighbor\n"
       "Display the prefixlist filter\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_show_received_prefix_filter (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv4_received_routes,
       show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv4_received_routes_cmd,
       "show bgp vpnv4 unicast rd ASN:nn_or_IP-address:nn neighbors A.B.C.D received-routes",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the received routes from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "received", .value = "received-routes" },
      NULL
    };
  return bgp_show_adj (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv4_routes,
       show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv4_routes_cmd,
       "show bgp vpnv4 unicast rd ASN:nn_or_IP-address:nn neighbors A.B.C.D routes",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display routes learned from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_show_neighbor_route (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv6,
       show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv6_cmd,
       "show bgp vpnv4 unicast rd ASN:nn_or_IP-address:nn neighbors X:X::X:X",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_show_neighbor (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv6_advertised_routes,
       show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv6_advertised_routes_cmd,
       "show bgp vpnv4 unicast rd ASN:nn_or_IP-address:nn neighbors X:X::X:X advertised-routes",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the routes advertised to a BGP neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_show_adj (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv6_received_prefix_filter,
       show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv6_received_prefix_filter_cmd,
       "show bgp vpnv4 unicast rd ASN:nn_or_IP-address:nn neighbors X:X::X:X received prefix-filter",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display information received from a BGP neighbor\n"
       "Display the prefixlist filter\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_show_received_prefix_filter (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv6_received_routes,
       show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv6_received_routes_cmd,
       "show bgp vpnv4 unicast rd ASN:nn_or_IP-address:nn neighbors X:X::X:X received-routes",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the received routes from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "received", .value = "received-routes" },
      NULL
    };
  return bgp_show_adj (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv6_routes,
       show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv6_routes_cmd,
       "show bgp vpnv4 unicast rd ASN:nn_or_IP-address:nn neighbors X:X::X:X routes",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display routes learned from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_show_neighbor_route (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_rd_rd_paths,
       show_bgp_vpnv4_unicast_rd_rd_paths_cmd,
       "show bgp vpnv4 unicast rd ASN:nn_or_IP-address:nn paths",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Path information\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[0] },
      NULL
    };
  return bgp_show_paths (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_rd_rd_summary,
       show_bgp_vpnv4_unicast_rd_rd_summary_cmd,
       "show bgp vpnv4 unicast rd ASN:nn_or_IP-address:nn summary",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Summary of BGP neighbor status\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[0] },
      NULL
    };
  return bgp_show_summary (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_rd_rd_cidr_only,
       show_bgp_vpnv4_unicast_rd_rd_cidr_only_cmd,
       "show bgp vpnv4 unicast rd ASN:nn_or_IP-address:nn cidr-only",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Display only routes with non-natural netmasks\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[0] },
      &(struct vty_arg) { .name = "cidr", .value = "cidr-only" },
      NULL
    };
  return bgp_show_cidr_only (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_rd_rd_ipv4,
       show_bgp_vpnv4_unicast_rd_rd_ipv4_cmd,
       "show bgp vpnv4 unicast rd ASN:nn_or_IP-address:nn A.B.C.D",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Network in the BGP routing table to display\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[0] },
      &(struct vty_arg) { .name = "network", .value = argv[1] },
      NULL
    };
  return bgp_show_route (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_rd_rd_ipv4m,
       show_bgp_vpnv4_unicast_rd_rd_ipv4m_cmd,
       "show bgp vpnv4 unicast rd ASN:nn_or_IP-address:nn A.B.C.D/M",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[0] },
      &(struct vty_arg) { .name = "prefix", .value = argv[1] },
      NULL
    };
  return bgp_show_route (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_rd_rd_ipv4m_longer_prefixes,
       show_bgp_vpnv4_unicast_rd_rd_ipv4m_longer_prefixes_cmd,
       "show bgp vpnv4 unicast rd ASN:nn_or_IP-address:nn A.B.C.D/M longer-prefixes",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Display route and more specific routes\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[0] },
      &(struct vty_arg) { .name = "prefix", .value = argv[1] },
      NULL
    };
  return bgp_show_prefix_longer (vty, args);
}

DEFUN (show_bgp_vpnv4_unicast_rd_rd_labels,
       show_bgp_vpnv4_unicast_rd_rd_labels_cmd,
       "show bgp vpnv4 unicast rd ASN:nn_or_IP-address:nn labels",
       "Show running system information\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Display BGP labels for prefixes\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[0] },
      NULL
    };
  return bgp_show_labels (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi,
       show_bgp_view_word_ipv4_safi_cmd,
       "show bgp view WORD ipv4 (unicast|multicast)",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      NULL
    };
  return bgp_show_normal (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_filter_list_word,
       show_bgp_view_word_ipv4_safi_filter_list_word_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) filter-list WORD",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes conforming to the filter-list\n"
       "Regular expression access list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "filter-list", .value = argv[2] },
      NULL
    };
  return bgp_show_filter_list (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_prefix_list_word,
       show_bgp_view_word_ipv4_safi_prefix_list_word_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) prefix-list WORD",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes conforming to the prefix-list\n"
       "IP prefix-list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "prefix-list", .value = argv[2] },
      NULL
    };
  return bgp_show_prefix_list (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_regexp_line,
       show_bgp_view_word_ipv4_safi_regexp_line_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) regexp .LINE",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the AS path regular expression\n"
       "A regular-expression to match the BGP AS paths\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "expr", .argc = argc - 2, .argv = argv + 2 },
      NULL
    };
  return bgp_show_regexp (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_route_map_word,
       show_bgp_view_word_ipv4_safi_route_map_word_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) route-map WORD",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the route-map\n"
       "A route-map to match on\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "route-map", .value = argv[2] },
      NULL
    };
  return bgp_show_route_map (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_community,
       show_bgp_view_word_ipv4_safi_community_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) community",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the communities\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      NULL
    };
  return bgp_show_community (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_community_community,
       show_bgp_view_word_ipv4_safi_community_community_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) community (AA:NN|local-AS|no-advertise|no-export)",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "community", .value = argv[2] },
      NULL
    };
  return bgp_show_community (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_community_community_exact_match,
       show_bgp_view_word_ipv4_safi_community_community_exact_match_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) community (AA:NN|local-AS|no-advertise|no-export) exact-match",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "Exact match of the communities\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "community", .value = argv[2] },
      &(struct vty_arg) { .name = "exact-match", .value = "exact-match" },
      NULL
    };
  return bgp_show_community (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_community_list_clist,
       show_bgp_view_word_ipv4_safi_community_list_clist_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) community-list <1-500>",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the community-list\n"
       "community-list number\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "clist", .value = argv[2] },
      NULL
    };
  return bgp_show_community_list (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_community_list_clist_exact_match,
       show_bgp_view_word_ipv4_safi_community_list_clist_exact_match_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) community-list <1-500> exact-match",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the community-list\n"
       "community-list number\n"
       "Exact match of the communities\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "clist", .value = argv[2] },
      &(struct vty_arg) { .name = "exact-match", .value = "exact-match" },
      NULL
    };
  return bgp_show_community_list (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_community_list_word,
       show_bgp_view_word_ipv4_safi_community_list_word_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) community-list WORD",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the community-list\n"
       "extcommunity-list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "clist", .value = argv[2] },
      NULL
    };
  return bgp_show_community_list (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_community_list_word_exact_match,
       show_bgp_view_word_ipv4_safi_community_list_word_exact_match_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) community-list WORD exact-match",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the community-list\n"
       "extcommunity-list name\n"
       "Exact match of the communities\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "clist", .value = argv[2] },
      &(struct vty_arg) { .name = "exact-match", .value = "exact-match" },
      NULL
    };
  return bgp_show_community_list (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_extcommunity_list_word,
       show_bgp_view_word_ipv4_safi_extcommunity_list_word_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) extcommunity-list WORD",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the extcommunity-list\n"
       "extcommunity-list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "ext_clist", .value = argv[2] },
      NULL
    };
  return bgp_show_ext_community_list (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_neighbors,
       show_bgp_view_word_ipv4_safi_neighbors_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) neighbors",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      NULL
    };
  return bgp_show_neighbor (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_neighbors_ipv4,
       show_bgp_view_word_ipv4_safi_neighbors_ipv4_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) neighbors A.B.C.D",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      NULL
    };
  return bgp_show_neighbor (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_neighbors_ipv4_advertised_routes,
       show_bgp_view_word_ipv4_safi_neighbors_ipv4_advertised_routes_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) neighbors A.B.C.D advertised-routes",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the routes advertised to a BGP neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      NULL
    };
  return bgp_show_adj (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_neighbors_ipv4_received_prefix_filter,
       show_bgp_view_word_ipv4_safi_neighbors_ipv4_received_prefix_filter_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) neighbors A.B.C.D received prefix-filter",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display information received from a BGP neighbor\n"
       "Display the prefixlist filter\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      NULL
    };
  return bgp_show_received_prefix_filter (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_neighbors_ipv4_received_routes,
       show_bgp_view_word_ipv4_safi_neighbors_ipv4_received_routes_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) neighbors A.B.C.D received-routes",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the received routes from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      &(struct vty_arg) { .name = "received", .value = "received-routes" },
      NULL
    };
  return bgp_show_adj (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_neighbors_ipv4_routes,
       show_bgp_view_word_ipv4_safi_neighbors_ipv4_routes_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) neighbors A.B.C.D routes",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display routes learned from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      NULL
    };
  return bgp_show_neighbor_route (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_neighbors_ipv6,
       show_bgp_view_word_ipv4_safi_neighbors_ipv6_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) neighbors X:X::X:X",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      NULL
    };
  return bgp_show_neighbor (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_neighbors_ipv6_advertised_routes,
       show_bgp_view_word_ipv4_safi_neighbors_ipv6_advertised_routes_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) neighbors X:X::X:X advertised-routes",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the routes advertised to a BGP neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      NULL
    };
  return bgp_show_adj (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_neighbors_ipv6_received_prefix_filter,
       show_bgp_view_word_ipv4_safi_neighbors_ipv6_received_prefix_filter_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) neighbors X:X::X:X received prefix-filter",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display information received from a BGP neighbor\n"
       "Display the prefixlist filter\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      NULL
    };
  return bgp_show_received_prefix_filter (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_neighbors_ipv6_received_routes,
       show_bgp_view_word_ipv4_safi_neighbors_ipv6_received_routes_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) neighbors X:X::X:X received-routes",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the received routes from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      &(struct vty_arg) { .name = "received", .value = "received-routes" },
      NULL
    };
  return bgp_show_adj (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_neighbors_ipv6_routes,
       show_bgp_view_word_ipv4_safi_neighbors_ipv6_routes_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) neighbors X:X::X:X routes",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display routes learned from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      NULL
    };
  return bgp_show_neighbor_route (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_paths,
       show_bgp_view_word_ipv4_safi_paths_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) paths",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Path information\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      NULL
    };
  return bgp_show_paths (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_summary,
       show_bgp_view_word_ipv4_safi_summary_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) summary",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Summary of BGP neighbor status\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      NULL
    };
  return bgp_show_summary (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_dampening_dampened_paths,
       show_bgp_view_word_ipv4_safi_dampening_dampened_paths_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) dampening dampened-paths",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display detailed information about dampening\n"
       "Display paths suppressed due to dampening\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "dampened-paths", .value = "dampened-paths" },
      NULL
    };
  return bgp_show_normal (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_dampening_flap_statistics,
       show_bgp_view_word_ipv4_safi_dampening_flap_statistics_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) dampening flap-statistics",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display detailed information about dampening\n"
       "Display flap statistics of routes\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "flap-statistics", .value = "flap-statistics" },
      NULL
    };
  return bgp_show_normal (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_dampening_flap_statistics_filter_list_word,
       show_bgp_view_word_ipv4_safi_dampening_flap_statistics_filter_list_word_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) dampening flap-statistics filter-list WORD",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display detailed information about dampening\n"
       "Display flap statistics of routes\n"
       "Display routes conforming to the filter-list\n"
       "Regular expression access list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "flap-statistics", .value = "flap-statistics" },
      &(struct vty_arg) { .name = "filter-list", .value = argv[2] },
      NULL
    };
  return bgp_show_filter_list (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_dampening_flap_statistics_prefix_list_word,
       show_bgp_view_word_ipv4_safi_dampening_flap_statistics_prefix_list_word_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) dampening flap-statistics prefix-list WORD",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display detailed information about dampening\n"
       "Display flap statistics of routes\n"
       "Display routes conforming to the prefix-list\n"
       "IP prefix-list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "flap-statistics", .value = "flap-statistics" },
      &(struct vty_arg) { .name = "prefix-list", .value = argv[2] },
      NULL
    };
  return bgp_show_prefix_list (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_dampening_flap_statistics_regexp_line,
       show_bgp_view_word_ipv4_safi_dampening_flap_statistics_regexp_line_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) dampening flap-statistics regexp .LINE",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display detailed information about dampening\n"
       "Display flap statistics of routes\n"
       "Display routes matching the AS path regular expression\n"
       "A regular-expression to match the BGP AS paths\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "flap-statistics", .value = "flap-statistics" },
      &(struct vty_arg) { .name = "expr", .argc = argc - 2, .argv = argv + 2 },
      NULL
    };
  return bgp_show_regexp (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_dampening_flap_statistics_route_map_word,
       show_bgp_view_word_ipv4_safi_dampening_flap_statistics_route_map_word_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) dampening flap-statistics route-map WORD",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display detailed information about dampening\n"
       "Display flap statistics of routes\n"
       "Display routes matching the route-map\n"
       "A route-map to match on\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "flap-statistics", .value = "flap-statistics" },
      &(struct vty_arg) { .name = "route-map", .value = argv[2] },
      NULL
    };
  return bgp_show_route_map (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_dampening_flap_statistics_cidr_only,
       show_bgp_view_word_ipv4_safi_dampening_flap_statistics_cidr_only_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) dampening flap-statistics cidr-only",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display detailed information about dampening\n"
       "Display flap statistics of routes\n"
       "Display only routes with non-natural netmasks\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "flap-statistics", .value = "flap-statistics" },
      &(struct vty_arg) { .name = "cidr", .value = "cidr-only" },
      NULL
    };
  return bgp_show_cidr_only (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_dampening_flap_statistics_ipv4,
       show_bgp_view_word_ipv4_safi_dampening_flap_statistics_ipv4_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) dampening flap-statistics A.B.C.D",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display detailed information about dampening\n"
       "Display flap statistics of routes\n"
       "Network in the BGP routing table to display\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "flap-statistics", .value = "flap-statistics" },
      &(struct vty_arg) { .name = "network", .value = argv[2] },
      NULL
    };
  return bgp_show_route_flap (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_dampening_flap_statistics_ipv4m,
       show_bgp_view_word_ipv4_safi_dampening_flap_statistics_ipv4m_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) dampening flap-statistics A.B.C.D/M",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display detailed information about dampening\n"
       "Display flap statistics of routes\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "flap-statistics", .value = "flap-statistics" },
      &(struct vty_arg) { .name = "prefix", .value = argv[2] },
      NULL
    };
  return bgp_show_route_flap (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_dampening_flap_statistics_ipv4m_longer_prefixes,
       show_bgp_view_word_ipv4_safi_dampening_flap_statistics_ipv4m_longer_prefixes_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) dampening flap-statistics A.B.C.D/M longer-prefixes",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display detailed information about dampening\n"
       "Display flap statistics of routes\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Display route and more specific routes\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "flap-statistics", .value = "flap-statistics" },
      &(struct vty_arg) { .name = "prefix", .value = argv[2] },
      NULL
    };
  return bgp_show_prefix_longer (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_neighbors_ipv4_dampened_routes,
       show_bgp_view_word_ipv4_safi_neighbors_ipv4_dampened_routes_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) neighbors A.B.C.D dampened-routes",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the dampened routes received from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      &(struct vty_arg) { .name = "dampened-routes", .value = "dampened-routes" },
      NULL
    };
  return bgp_show_neighbor_route (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_neighbors_ipv4_flap_statistics,
       show_bgp_view_word_ipv4_safi_neighbors_ipv4_flap_statistics_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) neighbors A.B.C.D flap-statistics",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display flap statistics of the routes learned from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      &(struct vty_arg) { .name = "flap-statistics", .value = "flap-statistics" },
      NULL
    };
  return bgp_show_neighbor_route (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_cidr_only,
       show_bgp_view_word_ipv4_safi_cidr_only_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) cidr-only",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display only routes with non-natural netmasks\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "cidr", .value = "cidr-only" },
      NULL
    };
  return bgp_show_cidr_only (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_ipv4,
       show_bgp_view_word_ipv4_safi_ipv4_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) A.B.C.D",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Network in the BGP routing table to display\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "network", .value = argv[2] },
      NULL
    };
  return bgp_show_route (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_ipv4m,
       show_bgp_view_word_ipv4_safi_ipv4m_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) A.B.C.D/M",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "prefix", .value = argv[2] },
      NULL
    };
  return bgp_show_route (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_ipv4m_longer_prefixes,
       show_bgp_view_word_ipv4_safi_ipv4m_longer_prefixes_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) A.B.C.D/M longer-prefixes",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Display route and more specific routes\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "prefix", .value = argv[2] },
      NULL
    };
  return bgp_show_prefix_longer (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_statistics,
       show_bgp_view_word_ipv4_safi_statistics_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) statistics",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP RIB advertisement statistics\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      NULL
    };
  return bgp_show_stats (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_neighbors_ipv4_prefix_counts,
       show_bgp_view_word_ipv4_safi_neighbors_ipv4_prefix_counts_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) neighbors A.B.C.D prefix-counts",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display detailed prefix count information\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      NULL
    };
  return bgp_peer_counts (vty, args);
}

DEFUN (show_bgp_view_word_ipv4_safi_neighbors_ipv6_prefix_counts,
       show_bgp_view_word_ipv4_safi_neighbors_ipv6_prefix_counts_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) neighbors X:X::X:X prefix-counts",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display detailed prefix count information\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      NULL
    };
  return bgp_peer_counts (vty, args);
}

DEFUN (show_bgp_view_word_ipv6_safi,
       show_bgp_view_word_ipv6_safi_cmd,
       "show bgp view WORD ipv6 (unicast|multicast)",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      NULL
    };
  return bgp_show_normal (vty, args);
}

DEFUN (show_bgp_view_word_ipv6_safi_filter_list_word,
       show_bgp_view_word_ipv6_safi_filter_list_word_cmd,
       "show bgp view WORD ipv6 (unicast|multicast) filter-list WORD",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes conforming to the filter-list\n"
       "Regular expression access list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "filter-list", .value = argv[2] },
      NULL
    };
  return bgp_show_filter_list (vty, args);
}

DEFUN (show_bgp_view_word_ipv6_safi_prefix_list_word,
       show_bgp_view_word_ipv6_safi_prefix_list_word_cmd,
       "show bgp view WORD ipv6 (unicast|multicast) prefix-list WORD",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes conforming to the prefix-list\n"
       "IP prefix-list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "prefix-list", .value = argv[2] },
      NULL
    };
  return bgp_show_prefix_list (vty, args);
}

DEFUN (show_bgp_view_word_ipv6_safi_regexp_line,
       show_bgp_view_word_ipv6_safi_regexp_line_cmd,
       "show bgp view WORD ipv6 (unicast|multicast) regexp .LINE",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the AS path regular expression\n"
       "A regular-expression to match the BGP AS paths\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "expr", .argc = argc - 2, .argv = argv + 2 },
      NULL
    };
  return bgp_show_regexp (vty, args);
}

DEFUN (show_bgp_view_word_ipv6_safi_route_map_word,
       show_bgp_view_word_ipv6_safi_route_map_word_cmd,
       "show bgp view WORD ipv6 (unicast|multicast) route-map WORD",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the route-map\n"
       "A route-map to match on\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "route-map", .value = argv[2] },
      NULL
    };
  return bgp_show_route_map (vty, args);
}

DEFUN (show_bgp_view_word_ipv6_safi_community,
       show_bgp_view_word_ipv6_safi_community_cmd,
       "show bgp view WORD ipv6 (unicast|multicast) community",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the communities\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      NULL
    };
  return bgp_show_community (vty, args);
}

DEFUN (show_bgp_view_word_ipv6_safi_community_community,
       show_bgp_view_word_ipv6_safi_community_community_cmd,
       "show bgp view WORD ipv6 (unicast|multicast) community (AA:NN|local-AS|no-advertise|no-export)",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "community", .value = argv[2] },
      NULL
    };
  return bgp_show_community (vty, args);
}

DEFUN (show_bgp_view_word_ipv6_safi_community_community_exact_match,
       show_bgp_view_word_ipv6_safi_community_community_exact_match_cmd,
       "show bgp view WORD ipv6 (unicast|multicast) community (AA:NN|local-AS|no-advertise|no-export) exact-match",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "Exact match of the communities\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "community", .value = argv[2] },
      &(struct vty_arg) { .name = "exact-match", .value = "exact-match" },
      NULL
    };
  return bgp_show_community (vty, args);
}

DEFUN (show_bgp_view_word_ipv6_safi_community_list_clist,
       show_bgp_view_word_ipv6_safi_community_list_clist_cmd,
       "show bgp view WORD ipv6 (unicast|multicast) community-list <1-500>",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the community-list\n"
       "community-list number\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "clist", .value = argv[2] },
      NULL
    };
  return bgp_show_community_list (vty, args);
}

DEFUN (show_bgp_view_word_ipv6_safi_community_list_clist_exact_match,
       show_bgp_view_word_ipv6_safi_community_list_clist_exact_match_cmd,
       "show bgp view WORD ipv6 (unicast|multicast) community-list <1-500> exact-match",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the community-list\n"
       "community-list number\n"
       "Exact match of the communities\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "clist", .value = argv[2] },
      &(struct vty_arg) { .name = "exact-match", .value = "exact-match" },
      NULL
    };
  return bgp_show_community_list (vty, args);
}

DEFUN (show_bgp_view_word_ipv6_safi_community_list_word,
       show_bgp_view_word_ipv6_safi_community_list_word_cmd,
       "show bgp view WORD ipv6 (unicast|multicast) community-list WORD",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the community-list\n"
       "extcommunity-list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "clist", .value = argv[2] },
      NULL
    };
  return bgp_show_community_list (vty, args);
}

DEFUN (show_bgp_view_word_ipv6_safi_community_list_word_exact_match,
       show_bgp_view_word_ipv6_safi_community_list_word_exact_match_cmd,
       "show bgp view WORD ipv6 (unicast|multicast) community-list WORD exact-match",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the community-list\n"
       "extcommunity-list name\n"
       "Exact match of the communities\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "clist", .value = argv[2] },
      &(struct vty_arg) { .name = "exact-match", .value = "exact-match" },
      NULL
    };
  return bgp_show_community_list (vty, args);
}

DEFUN (show_bgp_view_word_ipv6_safi_extcommunity_list_word,
       show_bgp_view_word_ipv6_safi_extcommunity_list_word_cmd,
       "show bgp view WORD ipv6 (unicast|multicast) extcommunity-list WORD",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the extcommunity-list\n"
       "extcommunity-list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "ext_clist", .value = argv[2] },
      NULL
    };
  return bgp_show_ext_community_list (vty, args);
}

DEFUN (show_bgp_view_word_ipv6_safi_neighbors,
       show_bgp_view_word_ipv6_safi_neighbors_cmd,
       "show bgp view WORD ipv6 (unicast|multicast) neighbors",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      NULL
    };
  return bgp_show_neighbor (vty, args);
}

DEFUN (show_bgp_view_word_ipv6_safi_neighbors_ipv4,
       show_bgp_view_word_ipv6_safi_neighbors_ipv4_cmd,
       "show bgp view WORD ipv6 (unicast|multicast) neighbors A.B.C.D",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      NULL
    };
  return bgp_show_neighbor (vty, args);
}

DEFUN (show_bgp_view_word_ipv6_safi_neighbors_ipv4_advertised_routes,
       show_bgp_view_word_ipv6_safi_neighbors_ipv4_advertised_routes_cmd,
       "show bgp view WORD ipv6 (unicast|multicast) neighbors A.B.C.D advertised-routes",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the routes advertised to a BGP neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      NULL
    };
  return bgp_show_adj (vty, args);
}

DEFUN (show_bgp_view_word_ipv6_safi_neighbors_ipv4_received_prefix_filter,
       show_bgp_view_word_ipv6_safi_neighbors_ipv4_received_prefix_filter_cmd,
       "show bgp view WORD ipv6 (unicast|multicast) neighbors A.B.C.D received prefix-filter",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display information received from a BGP neighbor\n"
       "Display the prefixlist filter\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      NULL
    };
  return bgp_show_received_prefix_filter (vty, args);
}

DEFUN (show_bgp_view_word_ipv6_safi_neighbors_ipv4_received_routes,
       show_bgp_view_word_ipv6_safi_neighbors_ipv4_received_routes_cmd,
       "show bgp view WORD ipv6 (unicast|multicast) neighbors A.B.C.D received-routes",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the received routes from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      &(struct vty_arg) { .name = "received", .value = "received-routes" },
      NULL
    };
  return bgp_show_adj (vty, args);
}

DEFUN (show_bgp_view_word_ipv6_safi_neighbors_ipv4_routes,
       show_bgp_view_word_ipv6_safi_neighbors_ipv4_routes_cmd,
       "show bgp view WORD ipv6 (unicast|multicast) neighbors A.B.C.D routes",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display routes learned from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      NULL
    };
  return bgp_show_neighbor_route (vty, args);
}

DEFUN (show_bgp_view_word_ipv6_safi_neighbors_ipv6,
       show_bgp_view_word_ipv6_safi_neighbors_ipv6_cmd,
       "show bgp view WORD ipv6 (unicast|multicast) neighbors X:X::X:X",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      NULL
    };
  return bgp_show_neighbor (vty, args);
}

DEFUN (show_bgp_view_word_ipv6_safi_neighbors_ipv6_advertised_routes,
       show_bgp_view_word_ipv6_safi_neighbors_ipv6_advertised_routes_cmd,
       "show bgp view WORD ipv6 (unicast|multicast) neighbors X:X::X:X advertised-routes",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the routes advertised to a BGP neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      NULL
    };
  return bgp_show_adj (vty, args);
}

DEFUN (show_bgp_view_word_ipv6_safi_neighbors_ipv6_received_prefix_filter,
       show_bgp_view_word_ipv6_safi_neighbors_ipv6_received_prefix_filter_cmd,
       "show bgp view WORD ipv6 (unicast|multicast) neighbors X:X::X:X received prefix-filter",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display information received from a BGP neighbor\n"
       "Display the prefixlist filter\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      NULL
    };
  return bgp_show_received_prefix_filter (vty, args);
}

DEFUN (show_bgp_view_word_ipv6_safi_neighbors_ipv6_received_routes,
       show_bgp_view_word_ipv6_safi_neighbors_ipv6_received_routes_cmd,
       "show bgp view WORD ipv6 (unicast|multicast) neighbors X:X::X:X received-routes",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the received routes from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      &(struct vty_arg) { .name = "received", .value = "received-routes" },
      NULL
    };
  return bgp_show_adj (vty, args);
}

DEFUN (show_bgp_view_word_ipv6_safi_neighbors_ipv6_routes,
       show_bgp_view_word_ipv6_safi_neighbors_ipv6_routes_cmd,
       "show bgp view WORD ipv6 (unicast|multicast) neighbors X:X::X:X routes",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display routes learned from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      NULL
    };
  return bgp_show_neighbor_route (vty, args);
}

DEFUN (show_bgp_view_word_ipv6_safi_paths,
       show_bgp_view_word_ipv6_safi_paths_cmd,
       "show bgp view WORD ipv6 (unicast|multicast) paths",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Path information\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      NULL
    };
  return bgp_show_paths (vty, args);
}

DEFUN (show_bgp_view_word_ipv6_safi_summary,
       show_bgp_view_word_ipv6_safi_summary_cmd,
       "show bgp view WORD ipv6 (unicast|multicast) summary",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Summary of BGP neighbor status\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      NULL
    };
  return bgp_show_summary (vty, args);
}

DEFUN (show_bgp_view_word_ipv6_safi_ipv6m,
       show_bgp_view_word_ipv6_safi_ipv6m_cmd,
       "show bgp view WORD ipv6 (unicast|multicast) X:X::X:X/M",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Network in the BGP routing table to display\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "prefix", .value = argv[2] },
      NULL
    };
  return bgp_show_route (vty, args);
}

DEFUN (show_bgp_view_word_ipv6_safi_ipv6m_longer_prefixes,
       show_bgp_view_word_ipv6_safi_ipv6m_longer_prefixes_cmd,
       "show bgp view WORD ipv6 (unicast|multicast) X:X::X:X/M longer-prefixes",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Network in the BGP routing table to display\n"
       "Display route and more specific routes\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "prefix", .value = argv[2] },
      NULL
    };
  return bgp_show_prefix_longer (vty, args);
}

DEFUN (show_bgp_view_word_ipv6_safi_statistics,
       show_bgp_view_word_ipv6_safi_statistics_cmd,
       "show bgp view WORD ipv6 (unicast|multicast) statistics",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP RIB advertisement statistics\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      NULL
    };
  return bgp_show_stats (vty, args);
}

DEFUN (show_bgp_view_word_ipv6_safi_neighbors_ipv4_prefix_counts,
       show_bgp_view_word_ipv6_safi_neighbors_ipv4_prefix_counts_cmd,
       "show bgp view WORD ipv6 (unicast|multicast) neighbors A.B.C.D prefix-counts",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display detailed prefix count information\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      NULL
    };
  return bgp_peer_counts (vty, args);
}

DEFUN (show_bgp_view_word_ipv6_safi_neighbors_ipv6_prefix_counts,
       show_bgp_view_word_ipv6_safi_neighbors_ipv6_prefix_counts_cmd,
       "show bgp view WORD ipv6 (unicast|multicast) neighbors X:X::X:X prefix-counts",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display detailed prefix count information\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      NULL
    };
  return bgp_peer_counts (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_all,
       show_bgp_view_word_vpnv4_unicast_all_cmd,
       "show bgp view WORD vpnv4 unicast all",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      NULL
    };
  return bgp_show_normal (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_all_filter_list_word,
       show_bgp_view_word_vpnv4_unicast_all_filter_list_word_cmd,
       "show bgp view WORD vpnv4 unicast all filter-list WORD",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Display routes conforming to the filter-list\n"
       "Regular expression access list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "filter-list", .value = argv[1] },
      NULL
    };
  return bgp_show_filter_list (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_all_prefix_list_word,
       show_bgp_view_word_vpnv4_unicast_all_prefix_list_word_cmd,
       "show bgp view WORD vpnv4 unicast all prefix-list WORD",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Display routes conforming to the prefix-list\n"
       "IP prefix-list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "prefix-list", .value = argv[1] },
      NULL
    };
  return bgp_show_prefix_list (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_all_regexp_line,
       show_bgp_view_word_vpnv4_unicast_all_regexp_line_cmd,
       "show bgp view WORD vpnv4 unicast all regexp .LINE",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Display routes matching the AS path regular expression\n"
       "A regular-expression to match the BGP AS paths\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "expr", .argc = argc - 1, .argv = argv + 1 },
      NULL
    };
  return bgp_show_regexp (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_all_route_map_word,
       show_bgp_view_word_vpnv4_unicast_all_route_map_word_cmd,
       "show bgp view WORD vpnv4 unicast all route-map WORD",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Display routes matching the route-map\n"
       "A route-map to match on\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "route-map", .value = argv[1] },
      NULL
    };
  return bgp_show_route_map (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_all_community,
       show_bgp_view_word_vpnv4_unicast_all_community_cmd,
       "show bgp view WORD vpnv4 unicast all community",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Display routes matching the communities\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      NULL
    };
  return bgp_show_community (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_all_community_community,
       show_bgp_view_word_vpnv4_unicast_all_community_community_cmd,
       "show bgp view WORD vpnv4 unicast all community (AA:NN|local-AS|no-advertise|no-export)",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "community", .value = argv[1] },
      NULL
    };
  return bgp_show_community (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_all_community_community_exact_match,
       show_bgp_view_word_vpnv4_unicast_all_community_community_exact_match_cmd,
       "show bgp view WORD vpnv4 unicast all community (AA:NN|local-AS|no-advertise|no-export) exact-match",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "Exact match of the communities\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "community", .value = argv[1] },
      &(struct vty_arg) { .name = "exact-match", .value = "exact-match" },
      NULL
    };
  return bgp_show_community (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_all_community_list_clist,
       show_bgp_view_word_vpnv4_unicast_all_community_list_clist_cmd,
       "show bgp view WORD vpnv4 unicast all community-list <1-500>",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Display routes matching the community-list\n"
       "community-list number\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "clist", .value = argv[1] },
      NULL
    };
  return bgp_show_community_list (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_all_community_list_clist_exact_match,
       show_bgp_view_word_vpnv4_unicast_all_community_list_clist_exact_match_cmd,
       "show bgp view WORD vpnv4 unicast all community-list <1-500> exact-match",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Display routes matching the community-list\n"
       "community-list number\n"
       "Exact match of the communities\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "clist", .value = argv[1] },
      &(struct vty_arg) { .name = "exact-match", .value = "exact-match" },
      NULL
    };
  return bgp_show_community_list (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_all_community_list_word,
       show_bgp_view_word_vpnv4_unicast_all_community_list_word_cmd,
       "show bgp view WORD vpnv4 unicast all community-list WORD",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Display routes matching the community-list\n"
       "extcommunity-list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "clist", .value = argv[1] },
      NULL
    };
  return bgp_show_community_list (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_all_community_list_word_exact_match,
       show_bgp_view_word_vpnv4_unicast_all_community_list_word_exact_match_cmd,
       "show bgp view WORD vpnv4 unicast all community-list WORD exact-match",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Display routes matching the community-list\n"
       "extcommunity-list name\n"
       "Exact match of the communities\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "clist", .value = argv[1] },
      &(struct vty_arg) { .name = "exact-match", .value = "exact-match" },
      NULL
    };
  return bgp_show_community_list (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_all_extcommunity_list_word,
       show_bgp_view_word_vpnv4_unicast_all_extcommunity_list_word_cmd,
       "show bgp view WORD vpnv4 unicast all extcommunity-list WORD",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Display routes matching the extcommunity-list\n"
       "extcommunity-list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "ext_clist", .value = argv[1] },
      NULL
    };
  return bgp_show_ext_community_list (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_all_neighbors,
       show_bgp_view_word_vpnv4_unicast_all_neighbors_cmd,
       "show bgp view WORD vpnv4 unicast all neighbors",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Detailed information on TCP and BGP neighbor connections\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      NULL
    };
  return bgp_show_neighbor (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv4,
       show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv4_cmd,
       "show bgp view WORD vpnv4 unicast all neighbors A.B.C.D",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_show_neighbor (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv4_advertised_routes,
       show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv4_advertised_routes_cmd,
       "show bgp view WORD vpnv4 unicast all neighbors A.B.C.D advertised-routes",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the routes advertised to a BGP neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_show_adj (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv4_received_prefix_filter,
       show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv4_received_prefix_filter_cmd,
       "show bgp view WORD vpnv4 unicast all neighbors A.B.C.D received prefix-filter",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display information received from a BGP neighbor\n"
       "Display the prefixlist filter\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_show_received_prefix_filter (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv4_received_routes,
       show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv4_received_routes_cmd,
       "show bgp view WORD vpnv4 unicast all neighbors A.B.C.D received-routes",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the received routes from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "received", .value = "received-routes" },
      NULL
    };
  return bgp_show_adj (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv4_routes,
       show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv4_routes_cmd,
       "show bgp view WORD vpnv4 unicast all neighbors A.B.C.D routes",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display routes learned from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_show_neighbor_route (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv6,
       show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv6_cmd,
       "show bgp view WORD vpnv4 unicast all neighbors X:X::X:X",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_show_neighbor (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv6_advertised_routes,
       show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv6_advertised_routes_cmd,
       "show bgp view WORD vpnv4 unicast all neighbors X:X::X:X advertised-routes",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the routes advertised to a BGP neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_show_adj (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv6_received_prefix_filter,
       show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv6_received_prefix_filter_cmd,
       "show bgp view WORD vpnv4 unicast all neighbors X:X::X:X received prefix-filter",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display information received from a BGP neighbor\n"
       "Display the prefixlist filter\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_show_received_prefix_filter (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv6_received_routes,
       show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv6_received_routes_cmd,
       "show bgp view WORD vpnv4 unicast all neighbors X:X::X:X received-routes",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the received routes from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "received", .value = "received-routes" },
      NULL
    };
  return bgp_show_adj (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv6_routes,
       show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv6_routes_cmd,
       "show bgp view WORD vpnv4 unicast all neighbors X:X::X:X routes",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display routes learned from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_show_neighbor_route (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_all_paths,
       show_bgp_view_word_vpnv4_unicast_all_paths_cmd,
       "show bgp view WORD vpnv4 unicast all paths",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Path information\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      NULL
    };
  return bgp_show_paths (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_all_summary,
       show_bgp_view_word_vpnv4_unicast_all_summary_cmd,
       "show bgp view WORD vpnv4 unicast all summary",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Summary of BGP neighbor status\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      NULL
    };
  return bgp_show_summary (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_all_cidr_only,
       show_bgp_view_word_vpnv4_unicast_all_cidr_only_cmd,
       "show bgp view WORD vpnv4 unicast all cidr-only",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Display only routes with non-natural netmasks\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "cidr", .value = "cidr-only" },
      NULL
    };
  return bgp_show_cidr_only (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_all_ipv4,
       show_bgp_view_word_vpnv4_unicast_all_ipv4_cmd,
       "show bgp view WORD vpnv4 unicast all A.B.C.D",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Network in the BGP routing table to display\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "network", .value = argv[1] },
      NULL
    };
  return bgp_show_route (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_all_ipv4m,
       show_bgp_view_word_vpnv4_unicast_all_ipv4m_cmd,
       "show bgp view WORD vpnv4 unicast all A.B.C.D/M",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "prefix", .value = argv[1] },
      NULL
    };
  return bgp_show_route (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_all_ipv4m_longer_prefixes,
       show_bgp_view_word_vpnv4_unicast_all_ipv4m_longer_prefixes_cmd,
       "show bgp view WORD vpnv4 unicast all A.B.C.D/M longer-prefixes",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Display route and more specific routes\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "prefix", .value = argv[1] },
      NULL
    };
  return bgp_show_prefix_longer (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_all_labels,
       show_bgp_view_word_vpnv4_unicast_all_labels_cmd,
       "show bgp view WORD vpnv4 unicast all labels",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information about all VPN NLRIs\n"
       "Display BGP labels for prefixes\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      NULL
    };
  return bgp_show_labels (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_rd_rd,
       show_bgp_view_word_vpnv4_unicast_rd_rd_cmd,
       "show bgp view WORD vpnv4 unicast rd ASN:nn_or_IP-address:nn",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[1] },
      NULL
    };
  return bgp_show_normal (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_rd_rd_filter_list_word,
       show_bgp_view_word_vpnv4_unicast_rd_rd_filter_list_word_cmd,
       "show bgp view WORD vpnv4 unicast rd ASN:nn_or_IP-address:nn filter-list WORD",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Display routes conforming to the filter-list\n"
       "Regular expression access list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[1] },
      &(struct vty_arg) { .name = "filter-list", .value = argv[2] },
      NULL
    };
  return bgp_show_filter_list (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_rd_rd_prefix_list_word,
       show_bgp_view_word_vpnv4_unicast_rd_rd_prefix_list_word_cmd,
       "show bgp view WORD vpnv4 unicast rd ASN:nn_or_IP-address:nn prefix-list WORD",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Display routes conforming to the prefix-list\n"
       "IP prefix-list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[1] },
      &(struct vty_arg) { .name = "prefix-list", .value = argv[2] },
      NULL
    };
  return bgp_show_prefix_list (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_rd_rd_regexp_line,
       show_bgp_view_word_vpnv4_unicast_rd_rd_regexp_line_cmd,
       "show bgp view WORD vpnv4 unicast rd ASN:nn_or_IP-address:nn regexp .LINE",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Display routes matching the AS path regular expression\n"
       "A regular-expression to match the BGP AS paths\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[1] },
      &(struct vty_arg) { .name = "expr", .argc = argc - 2, .argv = argv + 2 },
      NULL
    };
  return bgp_show_regexp (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_rd_rd_route_map_word,
       show_bgp_view_word_vpnv4_unicast_rd_rd_route_map_word_cmd,
       "show bgp view WORD vpnv4 unicast rd ASN:nn_or_IP-address:nn route-map WORD",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Display routes matching the route-map\n"
       "A route-map to match on\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[1] },
      &(struct vty_arg) { .name = "route-map", .value = argv[2] },
      NULL
    };
  return bgp_show_route_map (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_rd_rd_community,
       show_bgp_view_word_vpnv4_unicast_rd_rd_community_cmd,
       "show bgp view WORD vpnv4 unicast rd ASN:nn_or_IP-address:nn community",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Display routes matching the communities\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[1] },
      NULL
    };
  return bgp_show_community (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_rd_rd_community_community,
       show_bgp_view_word_vpnv4_unicast_rd_rd_community_community_cmd,
       "show bgp view WORD vpnv4 unicast rd ASN:nn_or_IP-address:nn community (AA:NN|local-AS|no-advertise|no-export)",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[1] },
      &(struct vty_arg) { .name = "community", .value = argv[2] },
      NULL
    };
  return bgp_show_community (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_rd_rd_community_community_exact_match,
       show_bgp_view_word_vpnv4_unicast_rd_rd_community_community_exact_match_cmd,
       "show bgp view WORD vpnv4 unicast rd ASN:nn_or_IP-address:nn community (AA:NN|local-AS|no-advertise|no-export) exact-match",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "Exact match of the communities\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[1] },
      &(struct vty_arg) { .name = "community", .value = argv[2] },
      &(struct vty_arg) { .name = "exact-match", .value = "exact-match" },
      NULL
    };
  return bgp_show_community (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_rd_rd_community_list_clist,
       show_bgp_view_word_vpnv4_unicast_rd_rd_community_list_clist_cmd,
       "show bgp view WORD vpnv4 unicast rd ASN:nn_or_IP-address:nn community-list <1-500>",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Display routes matching the community-list\n"
       "community-list number\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[1] },
      &(struct vty_arg) { .name = "clist", .value = argv[2] },
      NULL
    };
  return bgp_show_community_list (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_rd_rd_community_list_clist_exact_match,
       show_bgp_view_word_vpnv4_unicast_rd_rd_community_list_clist_exact_match_cmd,
       "show bgp view WORD vpnv4 unicast rd ASN:nn_or_IP-address:nn community-list <1-500> exact-match",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Display routes matching the community-list\n"
       "community-list number\n"
       "Exact match of the communities\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[1] },
      &(struct vty_arg) { .name = "clist", .value = argv[2] },
      &(struct vty_arg) { .name = "exact-match", .value = "exact-match" },
      NULL
    };
  return bgp_show_community_list (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_rd_rd_community_list_word,
       show_bgp_view_word_vpnv4_unicast_rd_rd_community_list_word_cmd,
       "show bgp view WORD vpnv4 unicast rd ASN:nn_or_IP-address:nn community-list WORD",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Display routes matching the community-list\n"
       "extcommunity-list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[1] },
      &(struct vty_arg) { .name = "clist", .value = argv[2] },
      NULL
    };
  return bgp_show_community_list (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_rd_rd_community_list_word_exact_match,
       show_bgp_view_word_vpnv4_unicast_rd_rd_community_list_word_exact_match_cmd,
       "show bgp view WORD vpnv4 unicast rd ASN:nn_or_IP-address:nn community-list WORD exact-match",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Display routes matching the community-list\n"
       "extcommunity-list name\n"
       "Exact match of the communities\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[1] },
      &(struct vty_arg) { .name = "clist", .value = argv[2] },
      &(struct vty_arg) { .name = "exact-match", .value = "exact-match" },
      NULL
    };
  return bgp_show_community_list (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_rd_rd_extcommunity_list_word,
       show_bgp_view_word_vpnv4_unicast_rd_rd_extcommunity_list_word_cmd,
       "show bgp view WORD vpnv4 unicast rd ASN:nn_or_IP-address:nn extcommunity-list WORD",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Display routes matching the extcommunity-list\n"
       "extcommunity-list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[1] },
      &(struct vty_arg) { .name = "ext_clist", .value = argv[2] },
      NULL
    };
  return bgp_show_ext_community_list (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors,
       show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_cmd,
       "show bgp view WORD vpnv4 unicast rd ASN:nn_or_IP-address:nn neighbors",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Detailed information on TCP and BGP neighbor connections\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[1] },
      NULL
    };
  return bgp_show_neighbor (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv4,
       show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv4_cmd,
       "show bgp view WORD vpnv4 unicast rd ASN:nn_or_IP-address:nn neighbors A.B.C.D",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      NULL
    };
  return bgp_show_neighbor (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv4_advertised_routes,
       show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv4_advertised_routes_cmd,
       "show bgp view WORD vpnv4 unicast rd ASN:nn_or_IP-address:nn neighbors A.B.C.D advertised-routes",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the routes advertised to a BGP neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      NULL
    };
  return bgp_show_adj (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv4_received_prefix_filter,
       show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv4_received_prefix_filter_cmd,
       "show bgp view WORD vpnv4 unicast rd ASN:nn_or_IP-address:nn neighbors A.B.C.D received prefix-filter",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display information received from a BGP neighbor\n"
       "Display the prefixlist filter\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      NULL
    };
  return bgp_show_received_prefix_filter (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv4_received_routes,
       show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv4_received_routes_cmd,
       "show bgp view WORD vpnv4 unicast rd ASN:nn_or_IP-address:nn neighbors A.B.C.D received-routes",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the received routes from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      &(struct vty_arg) { .name = "received", .value = "received-routes" },
      NULL
    };
  return bgp_show_adj (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv4_routes,
       show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv4_routes_cmd,
       "show bgp view WORD vpnv4 unicast rd ASN:nn_or_IP-address:nn neighbors A.B.C.D routes",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display routes learned from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      NULL
    };
  return bgp_show_neighbor_route (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv6,
       show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv6_cmd,
       "show bgp view WORD vpnv4 unicast rd ASN:nn_or_IP-address:nn neighbors X:X::X:X",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      NULL
    };
  return bgp_show_neighbor (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv6_advertised_routes,
       show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv6_advertised_routes_cmd,
       "show bgp view WORD vpnv4 unicast rd ASN:nn_or_IP-address:nn neighbors X:X::X:X advertised-routes",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the routes advertised to a BGP neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      NULL
    };
  return bgp_show_adj (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv6_received_prefix_filter,
       show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv6_received_prefix_filter_cmd,
       "show bgp view WORD vpnv4 unicast rd ASN:nn_or_IP-address:nn neighbors X:X::X:X received prefix-filter",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display information received from a BGP neighbor\n"
       "Display the prefixlist filter\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      NULL
    };
  return bgp_show_received_prefix_filter (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv6_received_routes,
       show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv6_received_routes_cmd,
       "show bgp view WORD vpnv4 unicast rd ASN:nn_or_IP-address:nn neighbors X:X::X:X received-routes",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the received routes from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      &(struct vty_arg) { .name = "received", .value = "received-routes" },
      NULL
    };
  return bgp_show_adj (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv6_routes,
       show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv6_routes_cmd,
       "show bgp view WORD vpnv4 unicast rd ASN:nn_or_IP-address:nn neighbors X:X::X:X routes",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display routes learned from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      NULL
    };
  return bgp_show_neighbor_route (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_rd_rd_paths,
       show_bgp_view_word_vpnv4_unicast_rd_rd_paths_cmd,
       "show bgp view WORD vpnv4 unicast rd ASN:nn_or_IP-address:nn paths",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Path information\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[1] },
      NULL
    };
  return bgp_show_paths (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_rd_rd_summary,
       show_bgp_view_word_vpnv4_unicast_rd_rd_summary_cmd,
       "show bgp view WORD vpnv4 unicast rd ASN:nn_or_IP-address:nn summary",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Summary of BGP neighbor status\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[1] },
      NULL
    };
  return bgp_show_summary (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_rd_rd_cidr_only,
       show_bgp_view_word_vpnv4_unicast_rd_rd_cidr_only_cmd,
       "show bgp view WORD vpnv4 unicast rd ASN:nn_or_IP-address:nn cidr-only",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Display only routes with non-natural netmasks\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[1] },
      &(struct vty_arg) { .name = "cidr", .value = "cidr-only" },
      NULL
    };
  return bgp_show_cidr_only (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_rd_rd_ipv4,
       show_bgp_view_word_vpnv4_unicast_rd_rd_ipv4_cmd,
       "show bgp view WORD vpnv4 unicast rd ASN:nn_or_IP-address:nn A.B.C.D",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Network in the BGP routing table to display\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[1] },
      &(struct vty_arg) { .name = "network", .value = argv[2] },
      NULL
    };
  return bgp_show_route (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_rd_rd_ipv4m,
       show_bgp_view_word_vpnv4_unicast_rd_rd_ipv4m_cmd,
       "show bgp view WORD vpnv4 unicast rd ASN:nn_or_IP-address:nn A.B.C.D/M",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[1] },
      &(struct vty_arg) { .name = "prefix", .value = argv[2] },
      NULL
    };
  return bgp_show_route (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_rd_rd_ipv4m_longer_prefixes,
       show_bgp_view_word_vpnv4_unicast_rd_rd_ipv4m_longer_prefixes_cmd,
       "show bgp view WORD vpnv4 unicast rd ASN:nn_or_IP-address:nn A.B.C.D/M longer-prefixes",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Display route and more specific routes\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[1] },
      &(struct vty_arg) { .name = "prefix", .value = argv[2] },
      NULL
    };
  return bgp_show_prefix_longer (vty, args);
}

DEFUN (show_bgp_view_word_vpnv4_unicast_rd_rd_labels,
       show_bgp_view_word_vpnv4_unicast_rd_rd_labels_cmd,
       "show bgp view WORD vpnv4 unicast rd ASN:nn_or_IP-address:nn labels",
       "Show running system information\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Display BGP labels for prefixes\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "rd", .value = argv[1] },
      NULL
    };
  return bgp_show_labels (vty, args);
}

DEFUN (show_ip_bgp,
       show_ip_bgp_cmd,
       "show ip bgp",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n")
{
  struct vty_arg *args[] = { NULL };
  return bgp_show_normal (vty, args);
}

DEFUN (show_ip_bgp_filter_list_word,
       show_ip_bgp_filter_list_word_cmd,
       "show ip bgp filter-list WORD",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Display routes conforming to the filter-list\n"
       "Regular expression access list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "filter-list", .value = argv[0] },
      NULL
    };
  return bgp_show_filter_list (vty, args);
}

DEFUN (show_ip_bgp_prefix_list_word,
       show_ip_bgp_prefix_list_word_cmd,
       "show ip bgp prefix-list WORD",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Display routes conforming to the prefix-list\n"
       "IP prefix-list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "prefix-list", .value = argv[0] },
      NULL
    };
  return bgp_show_prefix_list (vty, args);
}

DEFUN (show_ip_bgp_regexp_line,
       show_ip_bgp_regexp_line_cmd,
       "show ip bgp regexp .LINE",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Display routes matching the AS path regular expression\n"
       "A regular-expression to match the BGP AS paths\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "expr", .argc = argc, .argv = argv },
      NULL
    };
  return bgp_show_regexp (vty, args);
}

DEFUN (show_ip_bgp_route_map_word,
       show_ip_bgp_route_map_word_cmd,
       "show ip bgp route-map WORD",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Display routes matching the route-map\n"
       "A route-map to match on\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "route-map", .value = argv[0] },
      NULL
    };
  return bgp_show_route_map (vty, args);
}

DEFUN (show_ip_bgp_community,
       show_ip_bgp_community_cmd,
       "show ip bgp community",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Display routes matching the communities\n")
{
  struct vty_arg *args[] = { NULL };
  return bgp_show_community (vty, args);
}

DEFUN (show_ip_bgp_community_community,
       show_ip_bgp_community_community_cmd,
       "show ip bgp community (AA:NN|local-AS|no-advertise|no-export)",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "community", .value = argv[0] },
      NULL
    };
  return bgp_show_community (vty, args);
}

DEFUN (show_ip_bgp_community_community_exact_match,
       show_ip_bgp_community_community_exact_match_cmd,
       "show ip bgp community (AA:NN|local-AS|no-advertise|no-export) exact-match",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "Exact match of the communities\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "community", .value = argv[0] },
      &(struct vty_arg) { .name = "exact-match", .value = "exact-match" },
      NULL
    };
  return bgp_show_community (vty, args);
}

DEFUN (show_ip_bgp_community_list_clist,
       show_ip_bgp_community_list_clist_cmd,
       "show ip bgp community-list <1-500>",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Display routes matching the community-list\n"
       "community-list number\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "clist", .value = argv[0] },
      NULL
    };
  return bgp_show_community_list (vty, args);
}

DEFUN (show_ip_bgp_community_list_clist_exact_match,
       show_ip_bgp_community_list_clist_exact_match_cmd,
       "show ip bgp community-list <1-500> exact-match",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Display routes matching the community-list\n"
       "community-list number\n"
       "Exact match of the communities\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "clist", .value = argv[0] },
      &(struct vty_arg) { .name = "exact-match", .value = "exact-match" },
      NULL
    };
  return bgp_show_community_list (vty, args);
}

DEFUN (show_ip_bgp_community_list_word,
       show_ip_bgp_community_list_word_cmd,
       "show ip bgp community-list WORD",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Display routes matching the community-list\n"
       "extcommunity-list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "clist", .value = argv[0] },
      NULL
    };
  return bgp_show_community_list (vty, args);
}

DEFUN (show_ip_bgp_community_list_word_exact_match,
       show_ip_bgp_community_list_word_exact_match_cmd,
       "show ip bgp community-list WORD exact-match",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Display routes matching the community-list\n"
       "extcommunity-list name\n"
       "Exact match of the communities\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "clist", .value = argv[0] },
      &(struct vty_arg) { .name = "exact-match", .value = "exact-match" },
      NULL
    };
  return bgp_show_community_list (vty, args);
}

DEFUN (show_ip_bgp_extcommunity_list_word,
       show_ip_bgp_extcommunity_list_word_cmd,
       "show ip bgp extcommunity-list WORD",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Display routes matching the extcommunity-list\n"
       "extcommunity-list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "ext_clist", .value = argv[0] },
      NULL
    };
  return bgp_show_ext_community_list (vty, args);
}

DEFUN (show_ip_bgp_neighbors,
       show_ip_bgp_neighbors_cmd,
       "show ip bgp neighbors",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Detailed information on TCP and BGP neighbor connections\n")
{
  struct vty_arg *args[] = { NULL };
  return bgp_show_neighbor (vty, args);
}

DEFUN (show_ip_bgp_neighbors_ipv4,
       show_ip_bgp_neighbors_ipv4_cmd,
       "show ip bgp neighbors A.B.C.D",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      NULL
    };
  return bgp_show_neighbor (vty, args);
}

DEFUN (show_ip_bgp_neighbors_ipv4_advertised_routes,
       show_ip_bgp_neighbors_ipv4_advertised_routes_cmd,
       "show ip bgp neighbors A.B.C.D advertised-routes",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the routes advertised to a BGP neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      NULL
    };
  return bgp_show_adj (vty, args);
}

DEFUN (show_ip_bgp_neighbors_ipv4_received_prefix_filter,
       show_ip_bgp_neighbors_ipv4_received_prefix_filter_cmd,
       "show ip bgp neighbors A.B.C.D received prefix-filter",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display information received from a BGP neighbor\n"
       "Display the prefixlist filter\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      NULL
    };
  return bgp_show_received_prefix_filter (vty, args);
}

DEFUN (show_ip_bgp_neighbors_ipv4_received_routes,
       show_ip_bgp_neighbors_ipv4_received_routes_cmd,
       "show ip bgp neighbors A.B.C.D received-routes",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the received routes from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      &(struct vty_arg) { .name = "received", .value = "received-routes" },
      NULL
    };
  return bgp_show_adj (vty, args);
}

DEFUN (show_ip_bgp_neighbors_ipv4_routes,
       show_ip_bgp_neighbors_ipv4_routes_cmd,
       "show ip bgp neighbors A.B.C.D routes",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display routes learned from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      NULL
    };
  return bgp_show_neighbor_route (vty, args);
}

DEFUN (show_ip_bgp_neighbors_ipv6,
       show_ip_bgp_neighbors_ipv6_cmd,
       "show ip bgp neighbors X:X::X:X",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      NULL
    };
  return bgp_show_neighbor (vty, args);
}

DEFUN (show_ip_bgp_neighbors_ipv6_advertised_routes,
       show_ip_bgp_neighbors_ipv6_advertised_routes_cmd,
       "show ip bgp neighbors X:X::X:X advertised-routes",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the routes advertised to a BGP neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      NULL
    };
  return bgp_show_adj (vty, args);
}

DEFUN (show_ip_bgp_neighbors_ipv6_received_prefix_filter,
       show_ip_bgp_neighbors_ipv6_received_prefix_filter_cmd,
       "show ip bgp neighbors X:X::X:X received prefix-filter",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display information received from a BGP neighbor\n"
       "Display the prefixlist filter\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      NULL
    };
  return bgp_show_received_prefix_filter (vty, args);
}

DEFUN (show_ip_bgp_neighbors_ipv6_received_routes,
       show_ip_bgp_neighbors_ipv6_received_routes_cmd,
       "show ip bgp neighbors X:X::X:X received-routes",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the received routes from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      &(struct vty_arg) { .name = "received", .value = "received-routes" },
      NULL
    };
  return bgp_show_adj (vty, args);
}

DEFUN (show_ip_bgp_neighbors_ipv6_routes,
       show_ip_bgp_neighbors_ipv6_routes_cmd,
       "show ip bgp neighbors X:X::X:X routes",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display routes learned from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      NULL
    };
  return bgp_show_neighbor_route (vty, args);
}

DEFUN (show_ip_bgp_paths,
       show_ip_bgp_paths_cmd,
       "show ip bgp paths",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Path information\n")
{
  struct vty_arg *args[] = { NULL };
  return bgp_show_paths (vty, args);
}

DEFUN (show_ip_bgp_summary,
       show_ip_bgp_summary_cmd,
       "show ip bgp summary",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Summary of BGP neighbor status\n")
{
  struct vty_arg *args[] = { NULL };
  return bgp_show_summary (vty, args);
}

DEFUN (show_ip_bgp_dampening_dampened_paths,
       show_ip_bgp_dampening_dampened_paths_cmd,
       "show ip bgp dampening dampened-paths",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Display detailed information about dampening\n"
       "Display paths suppressed due to dampening\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "dampened-paths", .value = "dampened-paths" },
      NULL
    };
  return bgp_show_normal (vty, args);
}

DEFUN (show_ip_bgp_dampening_flap_statistics,
       show_ip_bgp_dampening_flap_statistics_cmd,
       "show ip bgp dampening flap-statistics",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Display detailed information about dampening\n"
       "Display flap statistics of routes\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "flap-statistics", .value = "flap-statistics" },
      NULL
    };
  return bgp_show_normal (vty, args);
}

DEFUN (show_ip_bgp_dampening_flap_statistics_filter_list_word,
       show_ip_bgp_dampening_flap_statistics_filter_list_word_cmd,
       "show ip bgp dampening flap-statistics filter-list WORD",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Display detailed information about dampening\n"
       "Display flap statistics of routes\n"
       "Display routes conforming to the filter-list\n"
       "Regular expression access list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "flap-statistics", .value = "flap-statistics" },
      &(struct vty_arg) { .name = "filter-list", .value = argv[0] },
      NULL
    };
  return bgp_show_filter_list (vty, args);
}

DEFUN (show_ip_bgp_dampening_flap_statistics_prefix_list_word,
       show_ip_bgp_dampening_flap_statistics_prefix_list_word_cmd,
       "show ip bgp dampening flap-statistics prefix-list WORD",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Display detailed information about dampening\n"
       "Display flap statistics of routes\n"
       "Display routes conforming to the prefix-list\n"
       "IP prefix-list name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "flap-statistics", .value = "flap-statistics" },
      &(struct vty_arg) { .name = "prefix-list", .value = argv[0] },
      NULL
    };
  return bgp_show_prefix_list (vty, args);
}

DEFUN (show_ip_bgp_dampening_flap_statistics_regexp_line,
       show_ip_bgp_dampening_flap_statistics_regexp_line_cmd,
       "show ip bgp dampening flap-statistics regexp .LINE",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Display detailed information about dampening\n"
       "Display flap statistics of routes\n"
       "Display routes matching the AS path regular expression\n"
       "A regular-expression to match the BGP AS paths\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "flap-statistics", .value = "flap-statistics" },
      &(struct vty_arg) { .name = "expr", .argc = argc, .argv = argv },
      NULL
    };
  return bgp_show_regexp (vty, args);
}

DEFUN (show_ip_bgp_dampening_flap_statistics_route_map_word,
       show_ip_bgp_dampening_flap_statistics_route_map_word_cmd,
       "show ip bgp dampening flap-statistics route-map WORD",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Display detailed information about dampening\n"
       "Display flap statistics of routes\n"
       "Display routes matching the route-map\n"
       "A route-map to match on\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "flap-statistics", .value = "flap-statistics" },
      &(struct vty_arg) { .name = "route-map", .value = argv[0] },
      NULL
    };
  return bgp_show_route_map (vty, args);
}

DEFUN (show_ip_bgp_dampening_flap_statistics_cidr_only,
       show_ip_bgp_dampening_flap_statistics_cidr_only_cmd,
       "show ip bgp dampening flap-statistics cidr-only",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Display detailed information about dampening\n"
       "Display flap statistics of routes\n"
       "Display only routes with non-natural netmasks\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "flap-statistics", .value = "flap-statistics" },
      &(struct vty_arg) { .name = "cidr", .value = "cidr-only" },
      NULL
    };
  return bgp_show_cidr_only (vty, args);
}

DEFUN (show_ip_bgp_dampening_flap_statistics_ipv4,
       show_ip_bgp_dampening_flap_statistics_ipv4_cmd,
       "show ip bgp dampening flap-statistics A.B.C.D",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Display detailed information about dampening\n"
       "Display flap statistics of routes\n"
       "Network in the BGP routing table to display\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "flap-statistics", .value = "flap-statistics" },
      &(struct vty_arg) { .name = "network", .value = argv[0] },
      NULL
    };
  return bgp_show_route_flap (vty, args);
}

DEFUN (show_ip_bgp_dampening_flap_statistics_ipv4m,
       show_ip_bgp_dampening_flap_statistics_ipv4m_cmd,
       "show ip bgp dampening flap-statistics A.B.C.D/M",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Display detailed information about dampening\n"
       "Display flap statistics of routes\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "flap-statistics", .value = "flap-statistics" },
      &(struct vty_arg) { .name = "prefix", .value = argv[0] },
      NULL
    };
  return bgp_show_route_flap (vty, args);
}

DEFUN (show_ip_bgp_dampening_flap_statistics_ipv4m_longer_prefixes,
       show_ip_bgp_dampening_flap_statistics_ipv4m_longer_prefixes_cmd,
       "show ip bgp dampening flap-statistics A.B.C.D/M longer-prefixes",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Display detailed information about dampening\n"
       "Display flap statistics of routes\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Display route and more specific routes\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "flap-statistics", .value = "flap-statistics" },
      &(struct vty_arg) { .name = "prefix", .value = argv[0] },
      NULL
    };
  return bgp_show_prefix_longer (vty, args);
}

DEFUN (show_ip_bgp_neighbors_ipv4_dampened_routes,
       show_ip_bgp_neighbors_ipv4_dampened_routes_cmd,
       "show ip bgp neighbors A.B.C.D dampened-routes",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the dampened routes received from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      &(struct vty_arg) { .name = "dampened-routes", .value = "dampened-routes" },
      NULL
    };
  return bgp_show_neighbor_route (vty, args);
}

DEFUN (show_ip_bgp_neighbors_ipv4_flap_statistics,
       show_ip_bgp_neighbors_ipv4_flap_statistics_cmd,
       "show ip bgp neighbors A.B.C.D flap-statistics",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display flap statistics of the routes learned from neighbor\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      &(struct vty_arg) { .name = "flap-statistics", .value = "flap-statistics" },
      NULL
    };
  return bgp_show_neighbor_route (vty, args);
}

DEFUN (show_ip_bgp_cidr_only,
       show_ip_bgp_cidr_only_cmd,
       "show ip bgp cidr-only",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Display only routes with non-natural netmasks\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "cidr", .value = "cidr-only" },
      NULL
    };
  return bgp_show_cidr_only (vty, args);
}

DEFUN (show_ip_bgp_ipv4,
       show_ip_bgp_ipv4_cmd,
       "show ip bgp A.B.C.D",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Network in the BGP routing table to display\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "network", .value = argv[0] },
      NULL
    };
  return bgp_show_route (vty, args);
}

DEFUN (show_ip_bgp_ipv4m,
       show_ip_bgp_ipv4m_cmd,
       "show ip bgp A.B.C.D/M",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "prefix", .value = argv[0] },
      NULL
    };
  return bgp_show_route (vty, args);
}

DEFUN (show_ip_bgp_ipv4m_longer_prefixes,
       show_ip_bgp_ipv4m_longer_prefixes_cmd,
       "show ip bgp A.B.C.D/M longer-prefixes",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Display route and more specific routes\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "prefix", .value = argv[0] },
      NULL
    };
  return bgp_show_prefix_longer (vty, args);
}

DEFUN (show_ip_bgp_statistics,
       show_ip_bgp_statistics_cmd,
       "show ip bgp statistics",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "BGP RIB advertisement statistics\n")
{
  struct vty_arg *args[] = { NULL };
  return bgp_show_stats (vty, args);
}

DEFUN (show_ip_bgp_neighbors_ipv4_prefix_counts,
       show_ip_bgp_neighbors_ipv4_prefix_counts_cmd,
       "show ip bgp neighbors A.B.C.D prefix-counts",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display detailed prefix count information\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      NULL
    };
  return bgp_peer_counts (vty, args);
}

DEFUN (show_ip_bgp_neighbors_ipv6_prefix_counts,
       show_ip_bgp_neighbors_ipv6_prefix_counts_cmd,
       "show ip bgp neighbors X:X::X:X prefix-counts",
       "Show running system information\n"
       "IP information\n"
       "BGP information\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display detailed prefix count information\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      NULL
    };
  return bgp_peer_counts (vty, args);
}

void
bgp_vty_show_init (void)
{
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_filter_list_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_filter_list_word_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_filter_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_prefix_list_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_prefix_list_word_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_prefix_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_regexp_line_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_regexp_line_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_regexp_line_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_route_map_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_route_map_word_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_route_map_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_community_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_community_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_community_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_community_community_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_community_community_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_community_community_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_community_community_exact_match_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_community_community_exact_match_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_community_community_exact_match_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_community_list_clist_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_community_list_clist_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_community_list_clist_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_community_list_clist_exact_match_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_community_list_clist_exact_match_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_community_list_clist_exact_match_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_community_list_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_community_list_word_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_community_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_community_list_word_exact_match_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_community_list_word_exact_match_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_community_list_word_exact_match_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_extcommunity_list_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_extcommunity_list_word_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_extcommunity_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_neighbors_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_neighbors_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_neighbors_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_neighbors_ipv4_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_neighbors_ipv4_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_neighbors_ipv4_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_neighbors_ipv4_advertised_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_neighbors_ipv4_advertised_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_neighbors_ipv4_advertised_routes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_neighbors_ipv4_received_prefix_filter_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_neighbors_ipv4_received_prefix_filter_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_neighbors_ipv4_received_prefix_filter_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_neighbors_ipv4_received_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_neighbors_ipv4_received_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_neighbors_ipv4_received_routes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_neighbors_ipv4_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_neighbors_ipv4_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_neighbors_ipv4_routes_cmd);
#ifdef HAVE_IPV6
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_neighbors_ipv6_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_neighbors_ipv6_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_neighbors_ipv6_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_neighbors_ipv6_advertised_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_neighbors_ipv6_advertised_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_neighbors_ipv6_advertised_routes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_neighbors_ipv6_received_prefix_filter_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_neighbors_ipv6_received_prefix_filter_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_neighbors_ipv6_received_prefix_filter_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_neighbors_ipv6_received_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_neighbors_ipv6_received_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_neighbors_ipv6_received_routes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_neighbors_ipv6_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_neighbors_ipv6_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_neighbors_ipv6_routes_cmd);
#endif /* HAVE_IPV6 */
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_paths_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_paths_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_paths_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_summary_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_summary_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_summary_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_dampening_dampened_paths_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_dampening_dampened_paths_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_dampening_dampened_paths_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_dampening_flap_statistics_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_dampening_flap_statistics_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_dampening_flap_statistics_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_dampening_flap_statistics_filter_list_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_dampening_flap_statistics_filter_list_word_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_dampening_flap_statistics_filter_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_dampening_flap_statistics_prefix_list_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_dampening_flap_statistics_prefix_list_word_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_dampening_flap_statistics_prefix_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_dampening_flap_statistics_regexp_line_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_dampening_flap_statistics_regexp_line_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_dampening_flap_statistics_regexp_line_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_dampening_flap_statistics_route_map_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_dampening_flap_statistics_route_map_word_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_dampening_flap_statistics_route_map_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_dampening_flap_statistics_cidr_only_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_dampening_flap_statistics_cidr_only_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_dampening_flap_statistics_cidr_only_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_dampening_flap_statistics_ipv4_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_dampening_flap_statistics_ipv4_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_dampening_flap_statistics_ipv4_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_dampening_flap_statistics_ipv4m_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_dampening_flap_statistics_ipv4m_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_dampening_flap_statistics_ipv4m_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_dampening_flap_statistics_ipv4m_longer_prefixes_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_dampening_flap_statistics_ipv4m_longer_prefixes_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_dampening_flap_statistics_ipv4m_longer_prefixes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_neighbors_ipv4_dampened_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_neighbors_ipv4_dampened_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_neighbors_ipv4_dampened_routes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_neighbors_ipv4_flap_statistics_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_neighbors_ipv4_flap_statistics_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_neighbors_ipv4_flap_statistics_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_cidr_only_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_cidr_only_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_cidr_only_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_ipv4_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_ipv4_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_ipv4_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_ipv4m_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_ipv4m_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_ipv4m_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_ipv4m_longer_prefixes_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_ipv4m_longer_prefixes_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_ipv4m_longer_prefixes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_statistics_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_statistics_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_statistics_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_neighbors_ipv4_prefix_counts_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_neighbors_ipv4_prefix_counts_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_neighbors_ipv4_prefix_counts_cmd);
#ifdef HAVE_IPV6
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_neighbors_ipv6_prefix_counts_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_neighbors_ipv6_prefix_counts_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_neighbors_ipv6_prefix_counts_cmd);
#endif /* HAVE_IPV6 */
#ifdef HAVE_IPV6
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_safi_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_safi_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_safi_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_safi_filter_list_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_safi_filter_list_word_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_safi_filter_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_safi_prefix_list_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_safi_prefix_list_word_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_safi_prefix_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_safi_regexp_line_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_safi_regexp_line_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_safi_regexp_line_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_safi_route_map_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_safi_route_map_word_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_safi_route_map_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_safi_community_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_safi_community_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_safi_community_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_safi_community_community_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_safi_community_community_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_safi_community_community_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_safi_community_community_exact_match_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_safi_community_community_exact_match_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_safi_community_community_exact_match_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_safi_community_list_clist_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_safi_community_list_clist_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_safi_community_list_clist_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_safi_community_list_clist_exact_match_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_safi_community_list_clist_exact_match_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_safi_community_list_clist_exact_match_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_safi_community_list_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_safi_community_list_word_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_safi_community_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_safi_community_list_word_exact_match_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_safi_community_list_word_exact_match_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_safi_community_list_word_exact_match_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_safi_extcommunity_list_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_safi_extcommunity_list_word_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_safi_extcommunity_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_safi_neighbors_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_safi_neighbors_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_safi_neighbors_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_safi_neighbors_ipv4_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_safi_neighbors_ipv4_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_safi_neighbors_ipv4_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_safi_neighbors_ipv4_advertised_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_safi_neighbors_ipv4_advertised_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_safi_neighbors_ipv4_advertised_routes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_safi_neighbors_ipv4_received_prefix_filter_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_safi_neighbors_ipv4_received_prefix_filter_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_safi_neighbors_ipv4_received_prefix_filter_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_safi_neighbors_ipv4_received_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_safi_neighbors_ipv4_received_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_safi_neighbors_ipv4_received_routes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_safi_neighbors_ipv4_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_safi_neighbors_ipv4_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_safi_neighbors_ipv4_routes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_safi_neighbors_ipv6_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_safi_neighbors_ipv6_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_safi_neighbors_ipv6_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_safi_neighbors_ipv6_advertised_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_safi_neighbors_ipv6_advertised_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_safi_neighbors_ipv6_advertised_routes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_safi_neighbors_ipv6_received_prefix_filter_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_safi_neighbors_ipv6_received_prefix_filter_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_safi_neighbors_ipv6_received_prefix_filter_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_safi_neighbors_ipv6_received_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_safi_neighbors_ipv6_received_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_safi_neighbors_ipv6_received_routes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_safi_neighbors_ipv6_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_safi_neighbors_ipv6_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_safi_neighbors_ipv6_routes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_safi_paths_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_safi_paths_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_safi_paths_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_safi_summary_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_safi_summary_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_safi_summary_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_safi_ipv6m_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_safi_ipv6m_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_safi_ipv6m_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_safi_ipv6m_longer_prefixes_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_safi_ipv6m_longer_prefixes_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_safi_ipv6m_longer_prefixes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_safi_statistics_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_safi_statistics_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_safi_statistics_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_safi_neighbors_ipv4_prefix_counts_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_safi_neighbors_ipv4_prefix_counts_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_safi_neighbors_ipv4_prefix_counts_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_safi_neighbors_ipv6_prefix_counts_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_safi_neighbors_ipv6_prefix_counts_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_safi_neighbors_ipv6_prefix_counts_cmd);
#endif /* HAVE_IPV6 */
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_all_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_all_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_all_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_all_filter_list_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_all_filter_list_word_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_all_filter_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_all_prefix_list_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_all_prefix_list_word_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_all_prefix_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_all_regexp_line_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_all_regexp_line_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_all_regexp_line_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_all_route_map_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_all_route_map_word_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_all_route_map_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_all_community_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_all_community_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_all_community_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_all_community_community_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_all_community_community_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_all_community_community_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_all_community_community_exact_match_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_all_community_community_exact_match_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_all_community_community_exact_match_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_all_community_list_clist_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_all_community_list_clist_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_all_community_list_clist_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_all_community_list_clist_exact_match_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_all_community_list_clist_exact_match_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_all_community_list_clist_exact_match_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_all_community_list_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_all_community_list_word_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_all_community_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_all_community_list_word_exact_match_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_all_community_list_word_exact_match_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_all_community_list_word_exact_match_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_all_extcommunity_list_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_all_extcommunity_list_word_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_all_extcommunity_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_all_neighbors_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_all_neighbors_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_all_neighbors_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_all_neighbors_ipv4_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_all_neighbors_ipv4_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_all_neighbors_ipv4_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_all_neighbors_ipv4_advertised_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_all_neighbors_ipv4_advertised_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_all_neighbors_ipv4_advertised_routes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_all_neighbors_ipv4_received_prefix_filter_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_all_neighbors_ipv4_received_prefix_filter_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_all_neighbors_ipv4_received_prefix_filter_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_all_neighbors_ipv4_received_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_all_neighbors_ipv4_received_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_all_neighbors_ipv4_received_routes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_all_neighbors_ipv4_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_all_neighbors_ipv4_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_all_neighbors_ipv4_routes_cmd);
#ifdef HAVE_IPV6
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_all_neighbors_ipv6_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_all_neighbors_ipv6_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_all_neighbors_ipv6_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_all_neighbors_ipv6_advertised_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_all_neighbors_ipv6_advertised_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_all_neighbors_ipv6_advertised_routes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_all_neighbors_ipv6_received_prefix_filter_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_all_neighbors_ipv6_received_prefix_filter_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_all_neighbors_ipv6_received_prefix_filter_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_all_neighbors_ipv6_received_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_all_neighbors_ipv6_received_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_all_neighbors_ipv6_received_routes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_all_neighbors_ipv6_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_all_neighbors_ipv6_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_all_neighbors_ipv6_routes_cmd);
#endif /* HAVE_IPV6 */
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_all_paths_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_all_paths_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_all_paths_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_all_summary_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_all_summary_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_all_summary_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_all_cidr_only_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_all_cidr_only_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_all_cidr_only_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_all_ipv4_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_all_ipv4_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_all_ipv4_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_all_ipv4m_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_all_ipv4m_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_all_ipv4m_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_all_ipv4m_longer_prefixes_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_all_ipv4m_longer_prefixes_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_all_ipv4m_longer_prefixes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_all_labels_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_all_labels_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_all_labels_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_rd_rd_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_rd_rd_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_rd_rd_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_rd_rd_filter_list_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_rd_rd_filter_list_word_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_rd_rd_filter_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_rd_rd_prefix_list_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_rd_rd_prefix_list_word_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_rd_rd_prefix_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_rd_rd_regexp_line_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_rd_rd_regexp_line_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_rd_rd_regexp_line_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_rd_rd_route_map_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_rd_rd_route_map_word_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_rd_rd_route_map_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_rd_rd_community_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_rd_rd_community_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_rd_rd_community_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_rd_rd_community_community_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_rd_rd_community_community_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_rd_rd_community_community_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_rd_rd_community_community_exact_match_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_rd_rd_community_community_exact_match_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_rd_rd_community_community_exact_match_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_rd_rd_community_list_clist_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_rd_rd_community_list_clist_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_rd_rd_community_list_clist_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_rd_rd_community_list_clist_exact_match_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_rd_rd_community_list_clist_exact_match_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_rd_rd_community_list_clist_exact_match_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_rd_rd_community_list_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_rd_rd_community_list_word_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_rd_rd_community_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_rd_rd_community_list_word_exact_match_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_rd_rd_community_list_word_exact_match_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_rd_rd_community_list_word_exact_match_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_rd_rd_extcommunity_list_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_rd_rd_extcommunity_list_word_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_rd_rd_extcommunity_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_rd_rd_neighbors_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_rd_rd_neighbors_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_rd_rd_neighbors_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv4_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv4_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv4_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv4_advertised_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv4_advertised_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv4_advertised_routes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv4_received_prefix_filter_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv4_received_prefix_filter_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv4_received_prefix_filter_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv4_received_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv4_received_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv4_received_routes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv4_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv4_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv4_routes_cmd);
#ifdef HAVE_IPV6
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv6_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv6_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv6_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv6_advertised_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv6_advertised_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv6_advertised_routes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv6_received_prefix_filter_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv6_received_prefix_filter_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv6_received_prefix_filter_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv6_received_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv6_received_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv6_received_routes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv6_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv6_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_rd_rd_neighbors_ipv6_routes_cmd);
#endif /* HAVE_IPV6 */
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_rd_rd_paths_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_rd_rd_paths_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_rd_rd_paths_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_rd_rd_summary_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_rd_rd_summary_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_rd_rd_summary_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_rd_rd_cidr_only_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_rd_rd_cidr_only_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_rd_rd_cidr_only_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_rd_rd_ipv4_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_rd_rd_ipv4_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_rd_rd_ipv4_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_rd_rd_ipv4m_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_rd_rd_ipv4m_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_rd_rd_ipv4m_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_rd_rd_ipv4m_longer_prefixes_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_rd_rd_ipv4m_longer_prefixes_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_rd_rd_ipv4m_longer_prefixes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_vpnv4_unicast_rd_rd_labels_cmd);
  install_element (ENABLE_NODE, &show_bgp_vpnv4_unicast_rd_rd_labels_cmd);
  install_element (VIEW_NODE, &show_bgp_vpnv4_unicast_rd_rd_labels_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_filter_list_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_filter_list_word_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_filter_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_prefix_list_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_prefix_list_word_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_prefix_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_regexp_line_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_regexp_line_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_regexp_line_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_route_map_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_route_map_word_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_route_map_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_community_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_community_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_community_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_community_community_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_community_community_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_community_community_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_community_community_exact_match_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_community_community_exact_match_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_community_community_exact_match_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_community_list_clist_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_community_list_clist_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_community_list_clist_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_community_list_clist_exact_match_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_community_list_clist_exact_match_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_community_list_clist_exact_match_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_community_list_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_community_list_word_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_community_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_community_list_word_exact_match_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_community_list_word_exact_match_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_community_list_word_exact_match_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_extcommunity_list_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_extcommunity_list_word_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_extcommunity_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_neighbors_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_neighbors_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_neighbors_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv4_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv4_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv4_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv4_advertised_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv4_advertised_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv4_advertised_routes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv4_received_prefix_filter_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv4_received_prefix_filter_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv4_received_prefix_filter_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv4_received_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv4_received_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv4_received_routes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv4_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv4_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv4_routes_cmd);
#ifdef HAVE_IPV6
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv6_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv6_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv6_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv6_advertised_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv6_advertised_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv6_advertised_routes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv6_received_prefix_filter_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv6_received_prefix_filter_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv6_received_prefix_filter_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv6_received_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv6_received_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv6_received_routes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv6_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv6_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv6_routes_cmd);
#endif /* HAVE_IPV6 */
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_paths_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_paths_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_paths_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_summary_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_summary_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_summary_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_dampening_dampened_paths_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_dampening_dampened_paths_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_dampening_dampened_paths_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_dampening_flap_statistics_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_dampening_flap_statistics_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_dampening_flap_statistics_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_dampening_flap_statistics_filter_list_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_dampening_flap_statistics_filter_list_word_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_dampening_flap_statistics_filter_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_dampening_flap_statistics_prefix_list_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_dampening_flap_statistics_prefix_list_word_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_dampening_flap_statistics_prefix_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_dampening_flap_statistics_regexp_line_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_dampening_flap_statistics_regexp_line_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_dampening_flap_statistics_regexp_line_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_dampening_flap_statistics_route_map_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_dampening_flap_statistics_route_map_word_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_dampening_flap_statistics_route_map_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_dampening_flap_statistics_cidr_only_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_dampening_flap_statistics_cidr_only_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_dampening_flap_statistics_cidr_only_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_dampening_flap_statistics_ipv4_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_dampening_flap_statistics_ipv4_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_dampening_flap_statistics_ipv4_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_dampening_flap_statistics_ipv4m_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_dampening_flap_statistics_ipv4m_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_dampening_flap_statistics_ipv4m_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_dampening_flap_statistics_ipv4m_longer_prefixes_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_dampening_flap_statistics_ipv4m_longer_prefixes_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_dampening_flap_statistics_ipv4m_longer_prefixes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv4_dampened_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv4_dampened_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv4_dampened_routes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv4_flap_statistics_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv4_flap_statistics_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv4_flap_statistics_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_cidr_only_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_cidr_only_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_cidr_only_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_ipv4_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_ipv4_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_ipv4_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_ipv4m_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_ipv4m_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_ipv4m_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_ipv4m_longer_prefixes_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_ipv4m_longer_prefixes_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_ipv4m_longer_prefixes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_statistics_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_statistics_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_statistics_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv4_prefix_counts_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv4_prefix_counts_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv4_prefix_counts_cmd);
#ifdef HAVE_IPV6
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv6_prefix_counts_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv6_prefix_counts_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv4_safi_neighbors_ipv6_prefix_counts_cmd);
#endif /* HAVE_IPV6 */
#ifdef HAVE_IPV6
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv6_safi_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv6_safi_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv6_safi_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv6_safi_filter_list_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv6_safi_filter_list_word_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv6_safi_filter_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv6_safi_prefix_list_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv6_safi_prefix_list_word_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv6_safi_prefix_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv6_safi_regexp_line_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv6_safi_regexp_line_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv6_safi_regexp_line_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv6_safi_route_map_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv6_safi_route_map_word_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv6_safi_route_map_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv6_safi_community_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv6_safi_community_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv6_safi_community_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv6_safi_community_community_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv6_safi_community_community_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv6_safi_community_community_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv6_safi_community_community_exact_match_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv6_safi_community_community_exact_match_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv6_safi_community_community_exact_match_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv6_safi_community_list_clist_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv6_safi_community_list_clist_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv6_safi_community_list_clist_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv6_safi_community_list_clist_exact_match_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv6_safi_community_list_clist_exact_match_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv6_safi_community_list_clist_exact_match_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv6_safi_community_list_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv6_safi_community_list_word_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv6_safi_community_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv6_safi_community_list_word_exact_match_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv6_safi_community_list_word_exact_match_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv6_safi_community_list_word_exact_match_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv6_safi_extcommunity_list_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv6_safi_extcommunity_list_word_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv6_safi_extcommunity_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv6_safi_neighbors_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv6_safi_neighbors_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv6_safi_neighbors_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv6_safi_neighbors_ipv4_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv6_safi_neighbors_ipv4_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv6_safi_neighbors_ipv4_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv6_safi_neighbors_ipv4_advertised_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv6_safi_neighbors_ipv4_advertised_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv6_safi_neighbors_ipv4_advertised_routes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv6_safi_neighbors_ipv4_received_prefix_filter_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv6_safi_neighbors_ipv4_received_prefix_filter_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv6_safi_neighbors_ipv4_received_prefix_filter_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv6_safi_neighbors_ipv4_received_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv6_safi_neighbors_ipv4_received_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv6_safi_neighbors_ipv4_received_routes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv6_safi_neighbors_ipv4_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv6_safi_neighbors_ipv4_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv6_safi_neighbors_ipv4_routes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv6_safi_neighbors_ipv6_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv6_safi_neighbors_ipv6_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv6_safi_neighbors_ipv6_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv6_safi_neighbors_ipv6_advertised_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv6_safi_neighbors_ipv6_advertised_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv6_safi_neighbors_ipv6_advertised_routes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv6_safi_neighbors_ipv6_received_prefix_filter_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv6_safi_neighbors_ipv6_received_prefix_filter_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv6_safi_neighbors_ipv6_received_prefix_filter_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv6_safi_neighbors_ipv6_received_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv6_safi_neighbors_ipv6_received_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv6_safi_neighbors_ipv6_received_routes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv6_safi_neighbors_ipv6_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv6_safi_neighbors_ipv6_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv6_safi_neighbors_ipv6_routes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv6_safi_paths_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv6_safi_paths_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv6_safi_paths_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv6_safi_summary_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv6_safi_summary_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv6_safi_summary_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv6_safi_ipv6m_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv6_safi_ipv6m_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv6_safi_ipv6m_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv6_safi_ipv6m_longer_prefixes_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv6_safi_ipv6m_longer_prefixes_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv6_safi_ipv6m_longer_prefixes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv6_safi_statistics_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv6_safi_statistics_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv6_safi_statistics_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv6_safi_neighbors_ipv4_prefix_counts_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv6_safi_neighbors_ipv4_prefix_counts_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv6_safi_neighbors_ipv4_prefix_counts_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_ipv6_safi_neighbors_ipv6_prefix_counts_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_ipv6_safi_neighbors_ipv6_prefix_counts_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_ipv6_safi_neighbors_ipv6_prefix_counts_cmd);
#endif /* HAVE_IPV6 */
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_all_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_all_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_all_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_all_filter_list_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_all_filter_list_word_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_all_filter_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_all_prefix_list_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_all_prefix_list_word_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_all_prefix_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_all_regexp_line_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_all_regexp_line_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_all_regexp_line_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_all_route_map_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_all_route_map_word_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_all_route_map_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_all_community_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_all_community_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_all_community_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_all_community_community_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_all_community_community_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_all_community_community_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_all_community_community_exact_match_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_all_community_community_exact_match_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_all_community_community_exact_match_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_all_community_list_clist_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_all_community_list_clist_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_all_community_list_clist_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_all_community_list_clist_exact_match_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_all_community_list_clist_exact_match_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_all_community_list_clist_exact_match_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_all_community_list_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_all_community_list_word_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_all_community_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_all_community_list_word_exact_match_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_all_community_list_word_exact_match_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_all_community_list_word_exact_match_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_all_extcommunity_list_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_all_extcommunity_list_word_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_all_extcommunity_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_all_neighbors_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_all_neighbors_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_all_neighbors_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv4_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv4_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv4_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv4_advertised_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv4_advertised_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv4_advertised_routes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv4_received_prefix_filter_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv4_received_prefix_filter_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv4_received_prefix_filter_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv4_received_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv4_received_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv4_received_routes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv4_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv4_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv4_routes_cmd);
#ifdef HAVE_IPV6
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv6_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv6_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv6_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv6_advertised_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv6_advertised_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv6_advertised_routes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv6_received_prefix_filter_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv6_received_prefix_filter_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv6_received_prefix_filter_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv6_received_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv6_received_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv6_received_routes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv6_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv6_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_all_neighbors_ipv6_routes_cmd);
#endif /* HAVE_IPV6 */
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_all_paths_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_all_paths_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_all_paths_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_all_summary_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_all_summary_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_all_summary_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_all_cidr_only_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_all_cidr_only_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_all_cidr_only_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_all_ipv4_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_all_ipv4_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_all_ipv4_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_all_ipv4m_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_all_ipv4m_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_all_ipv4m_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_all_ipv4m_longer_prefixes_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_all_ipv4m_longer_prefixes_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_all_ipv4m_longer_prefixes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_all_labels_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_all_labels_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_all_labels_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_filter_list_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_filter_list_word_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_filter_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_prefix_list_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_prefix_list_word_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_prefix_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_regexp_line_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_regexp_line_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_regexp_line_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_route_map_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_route_map_word_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_route_map_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_community_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_community_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_community_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_community_community_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_community_community_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_community_community_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_community_community_exact_match_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_community_community_exact_match_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_community_community_exact_match_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_community_list_clist_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_community_list_clist_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_community_list_clist_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_community_list_clist_exact_match_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_community_list_clist_exact_match_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_community_list_clist_exact_match_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_community_list_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_community_list_word_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_community_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_community_list_word_exact_match_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_community_list_word_exact_match_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_community_list_word_exact_match_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_extcommunity_list_word_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_extcommunity_list_word_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_extcommunity_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv4_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv4_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv4_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv4_advertised_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv4_advertised_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv4_advertised_routes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv4_received_prefix_filter_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv4_received_prefix_filter_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv4_received_prefix_filter_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv4_received_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv4_received_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv4_received_routes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv4_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv4_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv4_routes_cmd);
#ifdef HAVE_IPV6
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv6_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv6_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv6_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv6_advertised_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv6_advertised_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv6_advertised_routes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv6_received_prefix_filter_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv6_received_prefix_filter_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv6_received_prefix_filter_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv6_received_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv6_received_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv6_received_routes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv6_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv6_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_neighbors_ipv6_routes_cmd);
#endif /* HAVE_IPV6 */
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_paths_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_paths_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_paths_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_summary_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_summary_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_summary_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_cidr_only_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_cidr_only_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_cidr_only_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_ipv4_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_ipv4_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_ipv4_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_ipv4m_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_ipv4m_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_ipv4m_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_ipv4m_longer_prefixes_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_ipv4m_longer_prefixes_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_ipv4m_longer_prefixes_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_labels_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_labels_cmd);
  install_element (VIEW_NODE, &show_bgp_view_word_vpnv4_unicast_rd_rd_labels_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_filter_list_word_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_filter_list_word_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_filter_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_prefix_list_word_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_prefix_list_word_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_prefix_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_regexp_line_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_regexp_line_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_regexp_line_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_route_map_word_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_route_map_word_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_route_map_word_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_community_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_community_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_community_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_community_community_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_community_community_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_community_community_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_community_community_exact_match_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_community_community_exact_match_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_community_community_exact_match_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_community_list_clist_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_community_list_clist_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_community_list_clist_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_community_list_clist_exact_match_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_community_list_clist_exact_match_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_community_list_clist_exact_match_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_community_list_word_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_community_list_word_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_community_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_community_list_word_exact_match_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_community_list_word_exact_match_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_community_list_word_exact_match_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_extcommunity_list_word_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_extcommunity_list_word_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_extcommunity_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_neighbors_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_neighbors_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_neighbors_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_neighbors_ipv4_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_neighbors_ipv4_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_neighbors_ipv4_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_neighbors_ipv4_advertised_routes_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_neighbors_ipv4_advertised_routes_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_neighbors_ipv4_advertised_routes_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_neighbors_ipv4_received_prefix_filter_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_neighbors_ipv4_received_prefix_filter_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_neighbors_ipv4_received_prefix_filter_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_neighbors_ipv4_received_routes_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_neighbors_ipv4_received_routes_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_neighbors_ipv4_received_routes_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_neighbors_ipv4_routes_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_neighbors_ipv4_routes_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_neighbors_ipv4_routes_cmd);
#ifdef HAVE_IPV6
  install_element (RESTRICTED_NODE, &show_ip_bgp_neighbors_ipv6_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_neighbors_ipv6_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_neighbors_ipv6_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_neighbors_ipv6_advertised_routes_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_neighbors_ipv6_advertised_routes_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_neighbors_ipv6_advertised_routes_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_neighbors_ipv6_received_prefix_filter_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_neighbors_ipv6_received_prefix_filter_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_neighbors_ipv6_received_prefix_filter_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_neighbors_ipv6_received_routes_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_neighbors_ipv6_received_routes_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_neighbors_ipv6_received_routes_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_neighbors_ipv6_routes_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_neighbors_ipv6_routes_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_neighbors_ipv6_routes_cmd);
#endif /* HAVE_IPV6 */
  install_element (RESTRICTED_NODE, &show_ip_bgp_paths_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_paths_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_paths_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_summary_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_summary_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_summary_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_dampening_dampened_paths_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_dampening_dampened_paths_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_dampening_dampened_paths_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_dampening_flap_statistics_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_dampening_flap_statistics_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_dampening_flap_statistics_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_dampening_flap_statistics_filter_list_word_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_dampening_flap_statistics_filter_list_word_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_dampening_flap_statistics_filter_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_dampening_flap_statistics_prefix_list_word_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_dampening_flap_statistics_prefix_list_word_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_dampening_flap_statistics_prefix_list_word_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_dampening_flap_statistics_regexp_line_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_dampening_flap_statistics_regexp_line_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_dampening_flap_statistics_regexp_line_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_dampening_flap_statistics_route_map_word_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_dampening_flap_statistics_route_map_word_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_dampening_flap_statistics_route_map_word_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_dampening_flap_statistics_cidr_only_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_dampening_flap_statistics_cidr_only_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_dampening_flap_statistics_cidr_only_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_dampening_flap_statistics_ipv4_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_dampening_flap_statistics_ipv4_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_dampening_flap_statistics_ipv4_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_dampening_flap_statistics_ipv4m_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_dampening_flap_statistics_ipv4m_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_dampening_flap_statistics_ipv4m_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_dampening_flap_statistics_ipv4m_longer_prefixes_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_dampening_flap_statistics_ipv4m_longer_prefixes_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_dampening_flap_statistics_ipv4m_longer_prefixes_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_neighbors_ipv4_dampened_routes_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_neighbors_ipv4_dampened_routes_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_neighbors_ipv4_dampened_routes_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_neighbors_ipv4_flap_statistics_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_neighbors_ipv4_flap_statistics_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_neighbors_ipv4_flap_statistics_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_cidr_only_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_cidr_only_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_cidr_only_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_ipv4_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_ipv4_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_ipv4_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_ipv4m_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_ipv4m_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_ipv4m_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_ipv4m_longer_prefixes_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_ipv4m_longer_prefixes_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_ipv4m_longer_prefixes_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_statistics_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_statistics_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_statistics_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_neighbors_ipv4_prefix_counts_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_neighbors_ipv4_prefix_counts_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_neighbors_ipv4_prefix_counts_cmd);
#ifdef HAVE_IPV6
  install_element (RESTRICTED_NODE, &show_ip_bgp_neighbors_ipv6_prefix_counts_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_neighbors_ipv6_prefix_counts_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_neighbors_ipv6_prefix_counts_cmd);
#endif /* HAVE_IPV6 */
}