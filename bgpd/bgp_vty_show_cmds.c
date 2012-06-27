/* BGP VTY interface.
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
#include "bgpd/bgp_vty.h"
#include "bgpd/bgp_mpath.h"
#include "bgpd/bgp_vty_show.h"

/* BGP route print out function. */
DEFUN (show_ip_bgp,
       show_ip_bgp_cmd,
       "show ip bgp",
       SHOW_STR
       IP_STR
       BGP_STR)
{
  return bgp_show (vty, NULL, AFI_IP, SAFI_UNICAST, bgp_show_type_normal, NULL);
}

DEFUN (show_ip_bgp_ipv4,
       show_ip_bgp_ipv4_cmd,
       "show ip bgp ipv4 (unicast|multicast)",
       SHOW_STR
       IP_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n")
{
  if (strncmp (argv[0], "m", 1) == 0)
    return bgp_show (vty, NULL, AFI_IP, SAFI_MULTICAST, bgp_show_type_normal,
                     NULL);

  return bgp_show (vty, NULL, AFI_IP, SAFI_UNICAST, bgp_show_type_normal, NULL);
}

ALIAS (show_ip_bgp_ipv4,
       show_bgp_ipv4_safi_cmd,
       "show bgp ipv4 (unicast|multicast)",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n")

DEFUN (show_ip_bgp_route,
       show_ip_bgp_route_cmd,
       "show ip bgp A.B.C.D",
       SHOW_STR
       IP_STR
       BGP_STR
       "Network in the BGP routing table to display\n")
{
  return bgp_show_route (vty, NULL, argv[0], AFI_IP, SAFI_UNICAST, NULL, 0);
}

DEFUN (show_ip_bgp_ipv4_route,
       show_ip_bgp_ipv4_route_cmd,
       "show ip bgp ipv4 (unicast|multicast) A.B.C.D",
       SHOW_STR
       IP_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Network in the BGP routing table to display\n")
{
  if (strncmp (argv[0], "m", 1) == 0)
    return bgp_show_route (vty, NULL, argv[1], AFI_IP, SAFI_MULTICAST, NULL, 0);

  return bgp_show_route (vty, NULL, argv[1], AFI_IP, SAFI_UNICAST, NULL, 0);
}

ALIAS (show_ip_bgp_ipv4_route,
       show_bgp_ipv4_safi_route_cmd,
       "show bgp ipv4 (unicast|multicast) A.B.C.D",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Network in the BGP routing table to display\n")

DEFUN (show_ip_bgp_vpnv4_all_route,
       show_ip_bgp_vpnv4_all_route_cmd,
       "show ip bgp vpnv4 all A.B.C.D",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display VPNv4 NLRI specific information\n"
       "Display information about all VPNv4 NLRIs\n"
       "Network in the BGP routing table to display\n")
{
  return bgp_show_route (vty, NULL, argv[0], AFI_IP, SAFI_MPLS_VPN, NULL, 0);
}

DEFUN (show_ip_bgp_vpnv4_rd_route,
       show_ip_bgp_vpnv4_rd_route_cmd,
       "show ip bgp vpnv4 rd ASN:nn_or_IP-address:nn A.B.C.D",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display VPNv4 NLRI specific information\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Network in the BGP routing table to display\n")
{
  int ret;
  struct prefix_rd prd;

  ret = str2prefix_rd (argv[0], &prd);
  if (! ret)
    {
      vty_out (vty, "%% Malformed Route Distinguisher%s", VTY_NEWLINE);
      return CMD_WARNING;
    }
  return bgp_show_route (vty, NULL, argv[1], AFI_IP, SAFI_MPLS_VPN, &prd, 0);
}

DEFUN (show_ip_bgp_prefix,
       show_ip_bgp_prefix_cmd,
       "show ip bgp A.B.C.D/M",
       SHOW_STR
       IP_STR
       BGP_STR
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n")
{
  return bgp_show_route (vty, NULL, argv[0], AFI_IP, SAFI_UNICAST, NULL, 1);
}

DEFUN (show_ip_bgp_ipv4_prefix,
       show_ip_bgp_ipv4_prefix_cmd,
       "show ip bgp ipv4 (unicast|multicast) A.B.C.D/M",
       SHOW_STR
       IP_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n")
{
  if (strncmp (argv[0], "m", 1) == 0)
    return bgp_show_route (vty, NULL, argv[1], AFI_IP, SAFI_MULTICAST, NULL, 1);

  return bgp_show_route (vty, NULL, argv[1], AFI_IP, SAFI_UNICAST, NULL, 1);
}

ALIAS (show_ip_bgp_ipv4_prefix,
       show_bgp_ipv4_safi_prefix_cmd,
       "show bgp ipv4 (unicast|multicast) A.B.C.D/M",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n")

DEFUN (show_ip_bgp_vpnv4_all_prefix,
       show_ip_bgp_vpnv4_all_prefix_cmd,
       "show ip bgp vpnv4 all A.B.C.D/M",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display VPNv4 NLRI specific information\n"
       "Display information about all VPNv4 NLRIs\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n")
{
  return bgp_show_route (vty, NULL, argv[0], AFI_IP, SAFI_MPLS_VPN, NULL, 1);
}

DEFUN (show_ip_bgp_vpnv4_rd_prefix,
       show_ip_bgp_vpnv4_rd_prefix_cmd,
       "show ip bgp vpnv4 rd ASN:nn_or_IP-address:nn A.B.C.D/M",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display VPNv4 NLRI specific information\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n")
{
  int ret;
  struct prefix_rd prd;

  ret = str2prefix_rd (argv[0], &prd);
  if (! ret)
    {
      vty_out (vty, "%% Malformed Route Distinguisher%s", VTY_NEWLINE);
      return CMD_WARNING;
    }
  return bgp_show_route (vty, NULL, argv[1], AFI_IP, SAFI_MPLS_VPN, &prd, 1);
}

DEFUN (show_ip_bgp_view,
       show_ip_bgp_view_cmd,
       "show ip bgp view WORD",
       SHOW_STR
       IP_STR
       BGP_STR
       "BGP view\n"
       "BGP view name\n")
{
  struct bgp *bgp;

  /* BGP structure lookup. */
  bgp = bgp_lookup_by_name (argv[0]);
  if (bgp == NULL)
	{
	  vty_out (vty, "Can't find BGP view %s%s", argv[0], VTY_NEWLINE);
	  return CMD_WARNING;
	}

  return bgp_show (vty, bgp, AFI_IP, SAFI_UNICAST, bgp_show_type_normal, NULL);
}

DEFUN (show_ip_bgp_view_route,
       show_ip_bgp_view_route_cmd,
       "show ip bgp view WORD A.B.C.D",
       SHOW_STR
       IP_STR
       BGP_STR
       "BGP view\n"
       "BGP view name\n"
       "Network in the BGP routing table to display\n")
{
  return bgp_show_route (vty, argv[0], argv[1], AFI_IP, SAFI_UNICAST, NULL, 0);
}

DEFUN (show_ip_bgp_view_prefix,
       show_ip_bgp_view_prefix_cmd,
       "show ip bgp view WORD A.B.C.D/M",
       SHOW_STR
       IP_STR
       BGP_STR
       "BGP view\n"
       "BGP view name\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n")
{
  return bgp_show_route (vty, argv[0], argv[1], AFI_IP, SAFI_UNICAST, NULL, 1);
}

#ifdef HAVE_IPV6
DEFUN (show_bgp,
       show_bgp_cmd,
       "show bgp",
       SHOW_STR
       BGP_STR)
{
  return bgp_show (vty, NULL, AFI_IP6, SAFI_UNICAST, bgp_show_type_normal,
                   NULL);
}

ALIAS (show_bgp,
       show_bgp_ipv6_cmd,
       "show bgp ipv6",
       SHOW_STR
       BGP_STR
       "Address family\n")

DEFUN (show_bgp_ipv6_safi,
       show_bgp_ipv6_safi_cmd,
       "show bgp ipv6 (unicast|multicast)",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n")
{
  if (strncmp (argv[0], "m", 1) == 0)
    return bgp_show (vty, NULL, AFI_IP6, SAFI_MULTICAST, bgp_show_type_normal,
                     NULL);

  return bgp_show (vty, NULL, AFI_IP6, SAFI_UNICAST, bgp_show_type_normal, NULL);
}

/* old command */
DEFUN (show_ipv6_bgp,
       show_ipv6_bgp_cmd,
       "show ipv6 bgp",
       SHOW_STR
       IP_STR
       BGP_STR)
{
  return bgp_show (vty, NULL, AFI_IP6, SAFI_UNICAST, bgp_show_type_normal,
                   NULL);
}

DEFUN (show_bgp_route,
       show_bgp_route_cmd,
       "show bgp X:X::X:X",
       SHOW_STR
       BGP_STR
       "Network in the BGP routing table to display\n")
{
  return bgp_show_route (vty, NULL, argv[0], AFI_IP6, SAFI_UNICAST, NULL, 0);
}

ALIAS (show_bgp_route,
       show_bgp_ipv6_route_cmd,
       "show bgp ipv6 X:X::X:X",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Network in the BGP routing table to display\n")

DEFUN (show_bgp_ipv6_safi_route,
       show_bgp_ipv6_safi_route_cmd,
       "show bgp ipv6 (unicast|multicast) X:X::X:X",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Network in the BGP routing table to display\n")
{
  if (strncmp (argv[0], "m", 1) == 0)
    return bgp_show_route (vty, NULL, argv[1], AFI_IP6, SAFI_MULTICAST, NULL, 0);

  return bgp_show_route (vty, NULL, argv[1], AFI_IP6, SAFI_UNICAST, NULL, 0);
}

/* old command */
DEFUN (show_ipv6_bgp_route,
       show_ipv6_bgp_route_cmd,
       "show ipv6 bgp X:X::X:X",
       SHOW_STR
       IP_STR
       BGP_STR
       "Network in the BGP routing table to display\n")
{
  return bgp_show_route (vty, NULL, argv[0], AFI_IP6, SAFI_UNICAST, NULL, 0);
}

DEFUN (show_bgp_prefix,
       show_bgp_prefix_cmd,
       "show bgp X:X::X:X/M",
       SHOW_STR
       BGP_STR
       "IPv6 prefix <network>/<length>\n")
{
  return bgp_show_route (vty, NULL, argv[0], AFI_IP6, SAFI_UNICAST, NULL, 1);
}

ALIAS (show_bgp_prefix,
       show_bgp_ipv6_prefix_cmd,
       "show bgp ipv6 X:X::X:X/M",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "IPv6 prefix <network>/<length>\n")

DEFUN (show_bgp_ipv6_safi_prefix,
       show_bgp_ipv6_safi_prefix_cmd,
       "show bgp ipv6 (unicast|multicast) X:X::X:X/M",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "IPv6 prefix <network>/<length>, e.g., 3ffe::/16\n")
{
  if (strncmp (argv[0], "m", 1) == 0)
    return bgp_show_route (vty, NULL, argv[1], AFI_IP6, SAFI_MULTICAST, NULL, 1);

  return bgp_show_route (vty, NULL, argv[1], AFI_IP6, SAFI_UNICAST, NULL, 1);
}

/* old command */
DEFUN (show_ipv6_bgp_prefix,
       show_ipv6_bgp_prefix_cmd,
       "show ipv6 bgp X:X::X:X/M",
       SHOW_STR
       IP_STR
       BGP_STR
       "IPv6 prefix <network>/<length>, e.g., 3ffe::/16\n")
{
  return bgp_show_route (vty, NULL, argv[0], AFI_IP6, SAFI_UNICAST, NULL, 1);
}

DEFUN (show_bgp_view,
       show_bgp_view_cmd,
       "show bgp view WORD",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "View name\n")
{
  struct bgp *bgp;

  /* BGP structure lookup. */
  bgp = bgp_lookup_by_name (argv[0]);
  if (bgp == NULL)
	{
	  vty_out (vty, "Can't find BGP view %s%s", argv[0], VTY_NEWLINE);
	  return CMD_WARNING;
	}

  return bgp_show (vty, bgp, AFI_IP6, SAFI_UNICAST, bgp_show_type_normal, NULL);
}

ALIAS (show_bgp_view,
       show_bgp_view_ipv6_cmd,
       "show bgp view WORD ipv6",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "View name\n"
       "Address family\n")

DEFUN (show_bgp_view_route,
       show_bgp_view_route_cmd,
       "show bgp view WORD X:X::X:X",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "View name\n"
       "Network in the BGP routing table to display\n")
{
  return bgp_show_route (vty, argv[0], argv[1], AFI_IP6, SAFI_UNICAST, NULL, 0);
}

ALIAS (show_bgp_view_route,
       show_bgp_view_ipv6_route_cmd,
       "show bgp view WORD ipv6 X:X::X:X",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Network in the BGP routing table to display\n")

DEFUN (show_bgp_view_prefix,
       show_bgp_view_prefix_cmd,
       "show bgp view WORD X:X::X:X/M",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "View name\n"
       "IPv6 prefix <network>/<length>\n")
{
  return bgp_show_route (vty, argv[0], argv[1], AFI_IP6, SAFI_UNICAST, NULL, 1);
}

ALIAS (show_bgp_view_prefix,
       show_bgp_view_ipv6_prefix_cmd,
       "show bgp view WORD ipv6 X:X::X:X/M",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "IPv6 prefix <network>/<length>\n")

/* old command */
DEFUN (show_ipv6_mbgp,
       show_ipv6_mbgp_cmd,
       "show ipv6 mbgp",
       SHOW_STR
       IP_STR
       MBGP_STR)
{
  return bgp_show (vty, NULL, AFI_IP6, SAFI_MULTICAST, bgp_show_type_normal,
                   NULL);
}

/* old command */
DEFUN (show_ipv6_mbgp_route,
       show_ipv6_mbgp_route_cmd,
       "show ipv6 mbgp X:X::X:X",
       SHOW_STR
       IP_STR
       MBGP_STR
       "Network in the MBGP routing table to display\n")
{
  return bgp_show_route (vty, NULL, argv[0], AFI_IP6, SAFI_MULTICAST, NULL, 0);
}

/* old command */
DEFUN (show_ipv6_mbgp_prefix,
       show_ipv6_mbgp_prefix_cmd,
       "show ipv6 mbgp X:X::X:X/M",
       SHOW_STR
       IP_STR
       MBGP_STR
       "IPv6 prefix <network>/<length>, e.g., 3ffe::/16\n")
{
  return bgp_show_route (vty, NULL, argv[0], AFI_IP6, SAFI_MULTICAST, NULL, 1);
}
#endif

DEFUN (show_ip_bgp_regexp,
       show_ip_bgp_regexp_cmd,
       "show ip bgp regexp .LINE",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display routes matching the AS path regular expression\n"
       "A regular-expression to match the BGP AS paths\n")
{
  return bgp_show_regexp (vty, argc, argv, AFI_IP, SAFI_UNICAST,
			  bgp_show_type_regexp);
}

DEFUN (show_ip_bgp_flap_regexp,
       show_ip_bgp_flap_regexp_cmd,
       "show ip bgp flap-statistics regexp .LINE",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display flap statistics of routes\n"
       "Display routes matching the AS path regular expression\n"
       "A regular-expression to match the BGP AS paths\n")
{
  return bgp_show_regexp (vty, argc, argv, AFI_IP, SAFI_UNICAST,
			  bgp_show_type_flap_regexp);
}

DEFUN (show_ip_bgp_ipv4_regexp,
       show_ip_bgp_ipv4_regexp_cmd,
       "show ip bgp ipv4 (unicast|multicast) regexp .LINE",
       SHOW_STR
       IP_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the AS path regular expression\n"
       "A regular-expression to match the BGP AS paths\n")
{
  if (strncmp (argv[0], "m", 1) == 0)
    return bgp_show_regexp (vty, argc, argv, AFI_IP, SAFI_MULTICAST,
			    bgp_show_type_regexp);

  return bgp_show_regexp (vty, argc, argv, AFI_IP, SAFI_UNICAST,
			  bgp_show_type_regexp);
}

#ifdef HAVE_IPV6
DEFUN (show_bgp_regexp,
       show_bgp_regexp_cmd,
       "show bgp regexp .LINE",
       SHOW_STR
       BGP_STR
       "Display routes matching the AS path regular expression\n"
       "A regular-expression to match the BGP AS paths\n")
{
  return bgp_show_regexp (vty, argc, argv, AFI_IP6, SAFI_UNICAST,
			  bgp_show_type_regexp);
}

ALIAS (show_bgp_regexp,
       show_bgp_ipv6_regexp_cmd,
       "show bgp ipv6 regexp .LINE",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Display routes matching the AS path regular expression\n"
       "A regular-expression to match the BGP AS paths\n")

/* old command */
DEFUN (show_ipv6_bgp_regexp,
       show_ipv6_bgp_regexp_cmd,
       "show ipv6 bgp regexp .LINE",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display routes matching the AS path regular expression\n"
       "A regular-expression to match the BGP AS paths\n")
{
  return bgp_show_regexp (vty, argc, argv, AFI_IP6, SAFI_UNICAST,
			  bgp_show_type_regexp);
}

/* old command */
DEFUN (show_ipv6_mbgp_regexp,
       show_ipv6_mbgp_regexp_cmd,
       "show ipv6 mbgp regexp .LINE",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display routes matching the AS path regular expression\n"
       "A regular-expression to match the MBGP AS paths\n")
{
  return bgp_show_regexp (vty, argc, argv, AFI_IP6, SAFI_MULTICAST,
			  bgp_show_type_regexp);
}
#endif /* HAVE_IPV6 */

DEFUN (show_ip_bgp_prefix_list,
       show_ip_bgp_prefix_list_cmd,
       "show ip bgp prefix-list WORD",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display routes conforming to the prefix-list\n"
       "IP prefix-list name\n")
{
  return bgp_show_prefix_list (vty, argv[0], AFI_IP, SAFI_UNICAST,
			       bgp_show_type_prefix_list);
}

DEFUN (show_ip_bgp_flap_prefix_list,
       show_ip_bgp_flap_prefix_list_cmd,
       "show ip bgp flap-statistics prefix-list WORD",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display flap statistics of routes\n"
       "Display routes conforming to the prefix-list\n"
       "IP prefix-list name\n")
{
  return bgp_show_prefix_list (vty, argv[0], AFI_IP, SAFI_UNICAST,
			       bgp_show_type_flap_prefix_list);
}

DEFUN (show_ip_bgp_ipv4_prefix_list,
       show_ip_bgp_ipv4_prefix_list_cmd,
       "show ip bgp ipv4 (unicast|multicast) prefix-list WORD",
       SHOW_STR
       IP_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes conforming to the prefix-list\n"
       "IP prefix-list name\n")
{
  if (strncmp (argv[0], "m", 1) == 0)
    return bgp_show_prefix_list (vty, argv[1], AFI_IP, SAFI_MULTICAST,
			         bgp_show_type_prefix_list);

  return bgp_show_prefix_list (vty, argv[1], AFI_IP, SAFI_UNICAST,
			       bgp_show_type_prefix_list);
}

#ifdef HAVE_IPV6
DEFUN (show_bgp_prefix_list,
       show_bgp_prefix_list_cmd,
       "show bgp prefix-list WORD",
       SHOW_STR
       BGP_STR
       "Display routes conforming to the prefix-list\n"
       "IPv6 prefix-list name\n")
{
  return bgp_show_prefix_list (vty, argv[0], AFI_IP6, SAFI_UNICAST,
			       bgp_show_type_prefix_list);
}

ALIAS (show_bgp_prefix_list,
       show_bgp_ipv6_prefix_list_cmd,
       "show bgp ipv6 prefix-list WORD",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Display routes conforming to the prefix-list\n"
       "IPv6 prefix-list name\n")

/* old command */
DEFUN (show_ipv6_bgp_prefix_list,
       show_ipv6_bgp_prefix_list_cmd,
       "show ipv6 bgp prefix-list WORD",
       SHOW_STR
       IPV6_STR
       BGP_STR
       "Display routes matching the prefix-list\n"
       "IPv6 prefix-list name\n")
{
  return bgp_show_prefix_list (vty, argv[0], AFI_IP6, SAFI_UNICAST,
			       bgp_show_type_prefix_list);
}

/* old command */
DEFUN (show_ipv6_mbgp_prefix_list,
       show_ipv6_mbgp_prefix_list_cmd,
       "show ipv6 mbgp prefix-list WORD",
       SHOW_STR
       IPV6_STR
       MBGP_STR
       "Display routes matching the prefix-list\n"
       "IPv6 prefix-list name\n")
{
  return bgp_show_prefix_list (vty, argv[0], AFI_IP6, SAFI_MULTICAST,
			       bgp_show_type_prefix_list);
}
#endif /* HAVE_IPV6 */

DEFUN (show_ip_bgp_filter_list,
       show_ip_bgp_filter_list_cmd,
       "show ip bgp filter-list WORD",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display routes conforming to the filter-list\n"
       "Regular expression access list name\n")
{
  return bgp_show_filter_list (vty, argv[0], AFI_IP, SAFI_UNICAST,
			       bgp_show_type_filter_list);
}

DEFUN (show_ip_bgp_flap_filter_list,
       show_ip_bgp_flap_filter_list_cmd,
       "show ip bgp flap-statistics filter-list WORD",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display flap statistics of routes\n"
       "Display routes conforming to the filter-list\n"
       "Regular expression access list name\n")
{
  return bgp_show_filter_list (vty, argv[0], AFI_IP, SAFI_UNICAST,
			       bgp_show_type_flap_filter_list);
}

DEFUN (show_ip_bgp_ipv4_filter_list,
       show_ip_bgp_ipv4_filter_list_cmd,
       "show ip bgp ipv4 (unicast|multicast) filter-list WORD",
       SHOW_STR
       IP_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes conforming to the filter-list\n"
       "Regular expression access list name\n")
{
  if (strncmp (argv[0], "m", 1) == 0)
    return bgp_show_filter_list (vty, argv[1], AFI_IP, SAFI_MULTICAST,
			         bgp_show_type_filter_list);

  return bgp_show_filter_list (vty, argv[1], AFI_IP, SAFI_UNICAST,
			       bgp_show_type_filter_list);
}

#ifdef HAVE_IPV6
DEFUN (show_bgp_filter_list,
       show_bgp_filter_list_cmd,
       "show bgp filter-list WORD",
       SHOW_STR
       BGP_STR
       "Display routes conforming to the filter-list\n"
       "Regular expression access list name\n")
{
  return bgp_show_filter_list (vty, argv[0], AFI_IP6, SAFI_UNICAST,
			       bgp_show_type_filter_list);
}

ALIAS (show_bgp_filter_list,
       show_bgp_ipv6_filter_list_cmd,
       "show bgp ipv6 filter-list WORD",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Display routes conforming to the filter-list\n"
       "Regular expression access list name\n")

/* old command */
DEFUN (show_ipv6_bgp_filter_list,
       show_ipv6_bgp_filter_list_cmd,
       "show ipv6 bgp filter-list WORD",
       SHOW_STR
       IPV6_STR
       BGP_STR
       "Display routes conforming to the filter-list\n"
       "Regular expression access list name\n")
{
  return bgp_show_filter_list (vty, argv[0], AFI_IP6, SAFI_UNICAST,
			       bgp_show_type_filter_list);
}

/* old command */
DEFUN (show_ipv6_mbgp_filter_list,
       show_ipv6_mbgp_filter_list_cmd,
       "show ipv6 mbgp filter-list WORD",
       SHOW_STR
       IPV6_STR
       MBGP_STR
       "Display routes conforming to the filter-list\n"
       "Regular expression access list name\n")
{
  return bgp_show_filter_list (vty, argv[0], AFI_IP6, SAFI_MULTICAST,
			       bgp_show_type_filter_list);
}
#endif /* HAVE_IPV6 */

DEFUN (show_ip_bgp_route_map,
       show_ip_bgp_route_map_cmd,
       "show ip bgp route-map WORD",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display routes matching the route-map\n"
       "A route-map to match on\n")
{
  return bgp_show_route_map (vty, argv[0], AFI_IP, SAFI_UNICAST,
			     bgp_show_type_route_map);
}

DEFUN (show_ip_bgp_flap_route_map,
       show_ip_bgp_flap_route_map_cmd,
       "show ip bgp flap-statistics route-map WORD",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display flap statistics of routes\n"
       "Display routes matching the route-map\n"
       "A route-map to match on\n")
{
  return bgp_show_route_map (vty, argv[0], AFI_IP, SAFI_UNICAST,
			     bgp_show_type_flap_route_map);
}

DEFUN (show_ip_bgp_ipv4_route_map,
       show_ip_bgp_ipv4_route_map_cmd,
       "show ip bgp ipv4 (unicast|multicast) route-map WORD",
       SHOW_STR
       IP_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the route-map\n"
       "A route-map to match on\n")
{
  if (strncmp (argv[0], "m", 1) == 0)
    return bgp_show_route_map (vty, argv[1], AFI_IP, SAFI_MULTICAST,
			       bgp_show_type_route_map);

  return bgp_show_route_map (vty, argv[1], AFI_IP, SAFI_UNICAST,
			     bgp_show_type_route_map);
}

DEFUN (show_bgp_route_map,
       show_bgp_route_map_cmd,
       "show bgp route-map WORD",
       SHOW_STR
       BGP_STR
       "Display routes matching the route-map\n"
       "A route-map to match on\n")
{
  return bgp_show_route_map (vty, argv[0], AFI_IP6, SAFI_UNICAST,
			     bgp_show_type_route_map);
}

ALIAS (show_bgp_route_map,
       show_bgp_ipv6_route_map_cmd,
       "show bgp ipv6 route-map WORD",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Display routes matching the route-map\n"
       "A route-map to match on\n")

DEFUN (show_ip_bgp_cidr_only,
       show_ip_bgp_cidr_only_cmd,
       "show ip bgp cidr-only",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display only routes with non-natural netmasks\n")
{
    return bgp_show (vty, NULL, AFI_IP, SAFI_UNICAST,
		     bgp_show_type_cidr_only, NULL);
}

DEFUN (show_ip_bgp_flap_cidr_only,
       show_ip_bgp_flap_cidr_only_cmd,
       "show ip bgp flap-statistics cidr-only",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display flap statistics of routes\n"
       "Display only routes with non-natural netmasks\n")
{
  return bgp_show (vty, NULL, AFI_IP, SAFI_UNICAST,
		   bgp_show_type_flap_cidr_only, NULL);
}

DEFUN (show_ip_bgp_ipv4_cidr_only,
       show_ip_bgp_ipv4_cidr_only_cmd,
       "show ip bgp ipv4 (unicast|multicast) cidr-only",
       SHOW_STR
       IP_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display only routes with non-natural netmasks\n")
{
  if (strncmp (argv[0], "m", 1) == 0)
    return bgp_show (vty, NULL, AFI_IP, SAFI_MULTICAST,
		     bgp_show_type_cidr_only, NULL);

  return bgp_show (vty, NULL, AFI_IP, SAFI_UNICAST,
		     bgp_show_type_cidr_only, NULL);
}

DEFUN (show_ip_bgp_community_all,
       show_ip_bgp_community_all_cmd,
       "show ip bgp community",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display routes matching the communities\n")
{
  return bgp_show (vty, NULL, AFI_IP, SAFI_UNICAST,
		     bgp_show_type_community_all, NULL);
}

DEFUN (show_ip_bgp_ipv4_community_all,
       show_ip_bgp_ipv4_community_all_cmd,
       "show ip bgp ipv4 (unicast|multicast) community",
       SHOW_STR
       IP_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the communities\n")
{
  if (strncmp (argv[0], "m", 1) == 0)
    return bgp_show (vty, NULL, AFI_IP, SAFI_MULTICAST,
		     bgp_show_type_community_all, NULL);

  return bgp_show (vty, NULL, AFI_IP, SAFI_UNICAST,
		   bgp_show_type_community_all, NULL);
}

#ifdef HAVE_IPV6
DEFUN (show_bgp_community_all,
       show_bgp_community_all_cmd,
       "show bgp community",
       SHOW_STR
       BGP_STR
       "Display routes matching the communities\n")
{
  return bgp_show (vty, NULL, AFI_IP6, SAFI_UNICAST,
		   bgp_show_type_community_all, NULL);
}

ALIAS (show_bgp_community_all,
       show_bgp_ipv6_community_all_cmd,
       "show bgp ipv6 community",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Display routes matching the communities\n")

/* old command */
DEFUN (show_ipv6_bgp_community_all,
       show_ipv6_bgp_community_all_cmd,
       "show ipv6 bgp community",
       SHOW_STR
       IPV6_STR
       BGP_STR
       "Display routes matching the communities\n")
{
  return bgp_show (vty, NULL, AFI_IP6, SAFI_UNICAST,
		   bgp_show_type_community_all, NULL);
}

/* old command */
DEFUN (show_ipv6_mbgp_community_all,
       show_ipv6_mbgp_community_all_cmd,
       "show ipv6 mbgp community",
       SHOW_STR
       IPV6_STR
       MBGP_STR
       "Display routes matching the communities\n")
{
  return bgp_show (vty, NULL, AFI_IP6, SAFI_MULTICAST,
		   bgp_show_type_community_all, NULL);
}
#endif /* HAVE_IPV6 */

DEFUN (show_ip_bgp_community,
       show_ip_bgp_community_cmd,
       "show ip bgp community (AA:NN|local-AS|no-advertise|no-export)",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n")
{
  return bgp_show_community (vty, NULL, argc, argv, 0, AFI_IP, SAFI_UNICAST);
}

ALIAS (show_ip_bgp_community,
       show_ip_bgp_community2_cmd,
       "show ip bgp community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export)",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n")

ALIAS (show_ip_bgp_community,
       show_ip_bgp_community3_cmd,
       "show ip bgp community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export)",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n")

ALIAS (show_ip_bgp_community,
       show_ip_bgp_community4_cmd,
       "show ip bgp community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export)",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n")

DEFUN (show_ip_bgp_ipv4_community,
       show_ip_bgp_ipv4_community_cmd,
       "show ip bgp ipv4 (unicast|multicast) community (AA:NN|local-AS|no-advertise|no-export)",
       SHOW_STR
       IP_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n")
{
  if (strncmp (argv[0], "m", 1) == 0)
    return bgp_show_community (vty, NULL, argc, argv, 0, AFI_IP, SAFI_MULTICAST);

  return bgp_show_community (vty, NULL, argc, argv, 0, AFI_IP, SAFI_UNICAST);
}

ALIAS (show_ip_bgp_ipv4_community,
       show_ip_bgp_ipv4_community2_cmd,
       "show ip bgp ipv4 (unicast|multicast) community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export)",
       SHOW_STR
       IP_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n")

ALIAS (show_ip_bgp_ipv4_community,
       show_ip_bgp_ipv4_community3_cmd,
       "show ip bgp ipv4 (unicast|multicast) community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export)",
       SHOW_STR
       IP_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n")

ALIAS (show_ip_bgp_ipv4_community,
       show_ip_bgp_ipv4_community4_cmd,
       "show ip bgp ipv4 (unicast|multicast) community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export)",
       SHOW_STR
       IP_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n")

DEFUN (show_bgp_view_afi_safi_community_all,
       show_bgp_view_afi_safi_community_all_cmd,
#ifdef HAVE_IPV6
       "show bgp view WORD (ipv4|ipv6) (unicast|multicast) community",
#else
       "show bgp view WORD ipv4 (unicast|multicast) community",
#endif
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "BGP view name\n"
       "Address family\n"
#ifdef HAVE_IPV6
       "Address family\n"
#endif
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes containing communities\n")
{
  int afi;
  int safi;
  struct bgp *bgp;

  /* BGP structure lookup. */
  bgp = bgp_lookup_by_name (argv[0]);
  if (bgp == NULL)
    {
      vty_out (vty, "Can't find BGP view %s%s", argv[0], VTY_NEWLINE);
      return CMD_WARNING;
    }

#ifdef HAVE_IPV6
  afi = (strncmp (argv[1], "ipv6", 4) == 0) ? AFI_IP6 : AFI_IP;
  safi = (strncmp (argv[2], "m", 1) == 0) ? SAFI_MULTICAST : SAFI_UNICAST;
#else
  afi = AFI_IP;
  safi = (strncmp (argv[1], "m", 1) == 0) ? SAFI_MULTICAST : SAFI_UNICAST;
#endif
  return bgp_show (vty, bgp, afi, safi, bgp_show_type_community_all, NULL);
}

DEFUN (show_bgp_view_afi_safi_community,
       show_bgp_view_afi_safi_community_cmd,
#ifdef HAVE_IPV6
       "show bgp view WORD (ipv4|ipv6) (unicast|multicast) community (AA:NN|local-AS|no-advertise|no-export)",
#else
       "show bgp view WORD ipv4 (unicast|multicast) community (AA:NN|local-AS|no-advertise|no-export)",
#endif
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "BGP view name\n"
       "Address family\n"
#ifdef HAVE_IPV6
       "Address family\n"
#endif
       "Address family modifier\n"
       "Address family modifier\n"
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n")
{
  int afi;
  int safi;

#ifdef HAVE_IPV6
  afi = (strncmp (argv[1], "ipv6", 4) == 0) ? AFI_IP6 : AFI_IP;
  safi = (strncmp (argv[2], "m", 1) == 0) ? SAFI_MULTICAST : SAFI_UNICAST;
  return bgp_show_community (vty, argv[0], argc-3, &argv[3], 0, afi, safi);
#else
  afi = AFI_IP;
  safi = (strncmp (argv[1], "m", 1) == 0) ? SAFI_MULTICAST : SAFI_UNICAST;
  return bgp_show_community (vty, argv[0], argc-2, &argv[2], 0, afi, safi);
#endif
}

ALIAS (show_bgp_view_afi_safi_community,
       show_bgp_view_afi_safi_community2_cmd,
#ifdef HAVE_IPV6
       "show bgp view WORD (ipv4|ipv6) (unicast|multicast) community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export)",
#else
       "show bgp view WORD ipv4 (unicast|multicast) community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export)",
#endif
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "BGP view name\n"
       "Address family\n"
#ifdef HAVE_IPV6
       "Address family\n"
#endif
       "Address family modifier\n"
       "Address family modifier\n"
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n")

ALIAS (show_bgp_view_afi_safi_community,
       show_bgp_view_afi_safi_community3_cmd,
#ifdef HAVE_IPV6
       "show bgp view WORD (ipv4|ipv6) (unicast|multicast) community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export)",
#else
       "show bgp view WORD ipv4 (unicast|multicast) community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export)",
#endif
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "BGP view name\n"
       "Address family\n"
#ifdef HAVE_IPV6
       "Address family\n"
#endif
       "Address family modifier\n"
       "Address family modifier\n"
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n")

ALIAS (show_bgp_view_afi_safi_community,
       show_bgp_view_afi_safi_community4_cmd,
#ifdef HAVE_IPV6
       "show bgp view WORD (ipv4|ipv6) (unicast|multicast) community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export)",
#else
       "show bgp view WORD ipv4 (unicast|multicast) community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export)",
#endif
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "BGP view name\n"
       "Address family\n"
#ifdef HAVE_IPV6
       "Address family\n"
#endif
       "Address family modifier\n"
       "Address family modifier\n"
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n")

DEFUN (show_ip_bgp_community_exact,
       show_ip_bgp_community_exact_cmd,
       "show ip bgp community (AA:NN|local-AS|no-advertise|no-export) exact-match",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "Exact match of the communities")
{
  return bgp_show_community (vty, NULL, argc, argv, 1, AFI_IP, SAFI_UNICAST);
}

ALIAS (show_ip_bgp_community_exact,
       show_ip_bgp_community2_exact_cmd,
       "show ip bgp community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) exact-match",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "Exact match of the communities")

ALIAS (show_ip_bgp_community_exact,
       show_ip_bgp_community3_exact_cmd,
       "show ip bgp community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) exact-match",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "Exact match of the communities")

ALIAS (show_ip_bgp_community_exact,
       show_ip_bgp_community4_exact_cmd,
       "show ip bgp community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) exact-match",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "Exact match of the communities")

DEFUN (show_ip_bgp_ipv4_community_exact,
       show_ip_bgp_ipv4_community_exact_cmd,
       "show ip bgp ipv4 (unicast|multicast) community (AA:NN|local-AS|no-advertise|no-export) exact-match",
       SHOW_STR
       IP_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "Exact match of the communities")
{
  if (strncmp (argv[0], "m", 1) == 0)
    return bgp_show_community (vty, NULL, argc, argv, 1, AFI_IP, SAFI_MULTICAST);

  return bgp_show_community (vty, NULL, argc, argv, 1, AFI_IP, SAFI_UNICAST);
}

ALIAS (show_ip_bgp_ipv4_community_exact,
       show_ip_bgp_ipv4_community2_exact_cmd,
       "show ip bgp ipv4 (unicast|multicast) community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) exact-match",
       SHOW_STR
       IP_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "Exact match of the communities")

ALIAS (show_ip_bgp_ipv4_community_exact,
       show_ip_bgp_ipv4_community3_exact_cmd,
       "show ip bgp ipv4 (unicast|multicast) community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) exact-match",
       SHOW_STR
       IP_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "Exact match of the communities")

ALIAS (show_ip_bgp_ipv4_community_exact,
       show_ip_bgp_ipv4_community4_exact_cmd,
       "show ip bgp ipv4 (unicast|multicast) community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) exact-match",
       SHOW_STR
       IP_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "Exact match of the communities")

#ifdef HAVE_IPV6
DEFUN (show_bgp_community,
       show_bgp_community_cmd,
       "show bgp community (AA:NN|local-AS|no-advertise|no-export)",
       SHOW_STR
       BGP_STR
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n")
{
  return bgp_show_community (vty, NULL, argc, argv, 0, AFI_IP6, SAFI_UNICAST);
}

ALIAS (show_bgp_community,
       show_bgp_ipv6_community_cmd,
       "show bgp ipv6 community (AA:NN|local-AS|no-advertise|no-export)",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n")

ALIAS (show_bgp_community,
       show_bgp_community2_cmd,
       "show bgp community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export)",
       SHOW_STR
       BGP_STR
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n")

ALIAS (show_bgp_community,
       show_bgp_ipv6_community2_cmd,
       "show bgp ipv6 community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export)",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n")

ALIAS (show_bgp_community,
       show_bgp_community3_cmd,
       "show bgp community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export)",
       SHOW_STR
       BGP_STR
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n")

ALIAS (show_bgp_community,
       show_bgp_ipv6_community3_cmd,
       "show bgp ipv6 community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export)",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n")

ALIAS (show_bgp_community,
       show_bgp_community4_cmd,
       "show bgp community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export)",
       SHOW_STR
       BGP_STR
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n")

ALIAS (show_bgp_community,
       show_bgp_ipv6_community4_cmd,
       "show bgp ipv6 community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export)",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n")

/* old command */
DEFUN (show_ipv6_bgp_community,
       show_ipv6_bgp_community_cmd,
       "show ipv6 bgp community (AA:NN|local-AS|no-advertise|no-export)",
       SHOW_STR
       IPV6_STR
       BGP_STR
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n")
{
  return bgp_show_community (vty, NULL, argc, argv, 0, AFI_IP6, SAFI_UNICAST);
}

/* old command */
ALIAS (show_ipv6_bgp_community,
       show_ipv6_bgp_community2_cmd,
       "show ipv6 bgp community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export)",
       SHOW_STR
       IPV6_STR
       BGP_STR
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n")

/* old command */
ALIAS (show_ipv6_bgp_community,
       show_ipv6_bgp_community3_cmd,
       "show ipv6 bgp community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export)",
       SHOW_STR
       IPV6_STR
       BGP_STR
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n")

/* old command */
ALIAS (show_ipv6_bgp_community,
       show_ipv6_bgp_community4_cmd,
       "show ipv6 bgp community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export)",
       SHOW_STR
       IPV6_STR
       BGP_STR
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n")

DEFUN (show_bgp_community_exact,
       show_bgp_community_exact_cmd,
       "show bgp community (AA:NN|local-AS|no-advertise|no-export) exact-match",
       SHOW_STR
       BGP_STR
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "Exact match of the communities")
{
  return bgp_show_community (vty, NULL, argc, argv, 1, AFI_IP6, SAFI_UNICAST);
}

ALIAS (show_bgp_community_exact,
       show_bgp_ipv6_community_exact_cmd,
       "show bgp ipv6 community (AA:NN|local-AS|no-advertise|no-export) exact-match",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "Exact match of the communities")

ALIAS (show_bgp_community_exact,
       show_bgp_community2_exact_cmd,
       "show bgp community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) exact-match",
       SHOW_STR
       BGP_STR
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "Exact match of the communities")

ALIAS (show_bgp_community_exact,
       show_bgp_ipv6_community2_exact_cmd,
       "show bgp ipv6 community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) exact-match",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "Exact match of the communities")

ALIAS (show_bgp_community_exact,
       show_bgp_community3_exact_cmd,
       "show bgp community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) exact-match",
       SHOW_STR
       BGP_STR
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "Exact match of the communities")

ALIAS (show_bgp_community_exact,
       show_bgp_ipv6_community3_exact_cmd,
       "show bgp ipv6 community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) exact-match",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "Exact match of the communities")

ALIAS (show_bgp_community_exact,
       show_bgp_community4_exact_cmd,
       "show bgp community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) exact-match",
       SHOW_STR
       BGP_STR
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "Exact match of the communities")

ALIAS (show_bgp_community_exact,
       show_bgp_ipv6_community4_exact_cmd,
       "show bgp ipv6 community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) exact-match",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "Exact match of the communities")

/* old command */
DEFUN (show_ipv6_bgp_community_exact,
       show_ipv6_bgp_community_exact_cmd,
       "show ipv6 bgp community (AA:NN|local-AS|no-advertise|no-export) exact-match",
       SHOW_STR
       IPV6_STR
       BGP_STR
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "Exact match of the communities")
{
  return bgp_show_community (vty, NULL, argc, argv, 1, AFI_IP6, SAFI_UNICAST);
}

/* old command */
ALIAS (show_ipv6_bgp_community_exact,
       show_ipv6_bgp_community2_exact_cmd,
       "show ipv6 bgp community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) exact-match",
       SHOW_STR
       IPV6_STR
       BGP_STR
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "Exact match of the communities")

/* old command */
ALIAS (show_ipv6_bgp_community_exact,
       show_ipv6_bgp_community3_exact_cmd,
       "show ipv6 bgp community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) exact-match",
       SHOW_STR
       IPV6_STR
       BGP_STR
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "Exact match of the communities")

/* old command */
ALIAS (show_ipv6_bgp_community_exact,
       show_ipv6_bgp_community4_exact_cmd,
       "show ipv6 bgp community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) exact-match",
       SHOW_STR
       IPV6_STR
       BGP_STR
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "Exact match of the communities")

/* old command */
DEFUN (show_ipv6_mbgp_community,
       show_ipv6_mbgp_community_cmd,
       "show ipv6 mbgp community (AA:NN|local-AS|no-advertise|no-export)",
       SHOW_STR
       IPV6_STR
       MBGP_STR
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n")
{
  return bgp_show_community (vty, NULL, argc, argv, 0, AFI_IP6, SAFI_MULTICAST);
}

/* old command */
ALIAS (show_ipv6_mbgp_community,
       show_ipv6_mbgp_community2_cmd,
       "show ipv6 mbgp community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export)",
       SHOW_STR
       IPV6_STR
       MBGP_STR
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n")

/* old command */
ALIAS (show_ipv6_mbgp_community,
       show_ipv6_mbgp_community3_cmd,
       "show ipv6 mbgp community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export)",
       SHOW_STR
       IPV6_STR
       MBGP_STR
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n")

/* old command */
ALIAS (show_ipv6_mbgp_community,
       show_ipv6_mbgp_community4_cmd,
       "show ipv6 mbgp community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export)",
       SHOW_STR
       IPV6_STR
       MBGP_STR
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n")

/* old command */
DEFUN (show_ipv6_mbgp_community_exact,
       show_ipv6_mbgp_community_exact_cmd,
       "show ipv6 mbgp community (AA:NN|local-AS|no-advertise|no-export) exact-match",
       SHOW_STR
       IPV6_STR
       MBGP_STR
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "Exact match of the communities")
{
  return bgp_show_community (vty, NULL, argc, argv, 1, AFI_IP6, SAFI_MULTICAST);
}

/* old command */
ALIAS (show_ipv6_mbgp_community_exact,
       show_ipv6_mbgp_community2_exact_cmd,
       "show ipv6 mbgp community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) exact-match",
       SHOW_STR
       IPV6_STR
       MBGP_STR
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "Exact match of the communities")

/* old command */
ALIAS (show_ipv6_mbgp_community_exact,
       show_ipv6_mbgp_community3_exact_cmd,
       "show ipv6 mbgp community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) exact-match",
       SHOW_STR
       IPV6_STR
       MBGP_STR
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "Exact match of the communities")

/* old command */
ALIAS (show_ipv6_mbgp_community_exact,
       show_ipv6_mbgp_community4_exact_cmd,
       "show ipv6 mbgp community (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) (AA:NN|local-AS|no-advertise|no-export) exact-match",
       SHOW_STR
       IPV6_STR
       MBGP_STR
       "Display routes matching the communities\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "community number\n"
       "Do not send outside local AS (well-known community)\n"
       "Do not advertise to any peer (well-known community)\n"
       "Do not export to next AS (well-known community)\n"
       "Exact match of the communities")
#endif /* HAVE_IPV6 */

DEFUN (show_ip_bgp_community_list,
       show_ip_bgp_community_list_cmd,
       "show ip bgp community-list (<1-500>|WORD)",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display routes matching the community-list\n"
       "community-list number\n"
       "community-list name\n")
{
  return bgp_show_community_list (vty, argv[0], 0, AFI_IP, SAFI_UNICAST);
}

DEFUN (show_ip_bgp_ipv4_community_list,
       show_ip_bgp_ipv4_community_list_cmd,
       "show ip bgp ipv4 (unicast|multicast) community-list (<1-500>|WORD)",
       SHOW_STR
       IP_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the community-list\n"
       "community-list number\n"
       "community-list name\n")
{
  if (strncmp (argv[0], "m", 1) == 0)
    return bgp_show_community_list (vty, argv[1], 0, AFI_IP, SAFI_MULTICAST);

  return bgp_show_community_list (vty, argv[1], 0, AFI_IP, SAFI_UNICAST);
}

DEFUN (show_ip_bgp_community_list_exact,
       show_ip_bgp_community_list_exact_cmd,
       "show ip bgp community-list (<1-500>|WORD) exact-match",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display routes matching the community-list\n"
       "community-list number\n"
       "community-list name\n"
       "Exact match of the communities\n")
{
  return bgp_show_community_list (vty, argv[0], 1, AFI_IP, SAFI_UNICAST);
}

DEFUN (show_ip_bgp_ipv4_community_list_exact,
       show_ip_bgp_ipv4_community_list_exact_cmd,
       "show ip bgp ipv4 (unicast|multicast) community-list (<1-500>|WORD) exact-match",
       SHOW_STR
       IP_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Display routes matching the community-list\n"
       "community-list number\n"
       "community-list name\n"
       "Exact match of the communities\n")
{
  if (strncmp (argv[0], "m", 1) == 0)
    return bgp_show_community_list (vty, argv[1], 1, AFI_IP, SAFI_MULTICAST);

  return bgp_show_community_list (vty, argv[1], 1, AFI_IP, SAFI_UNICAST);
}

#ifdef HAVE_IPV6
DEFUN (show_bgp_community_list,
       show_bgp_community_list_cmd,
       "show bgp community-list (<1-500>|WORD)",
       SHOW_STR
       BGP_STR
       "Display routes matching the community-list\n"
       "community-list number\n"
       "community-list name\n")
{
  return bgp_show_community_list (vty, argv[0], 0, AFI_IP6, SAFI_UNICAST);
}

ALIAS (show_bgp_community_list,
       show_bgp_ipv6_community_list_cmd,
       "show bgp ipv6 community-list (<1-500>|WORD)",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Display routes matching the community-list\n"
       "community-list number\n"
       "community-list name\n")

/* old command */
DEFUN (show_ipv6_bgp_community_list,
       show_ipv6_bgp_community_list_cmd,
       "show ipv6 bgp community-list WORD",
       SHOW_STR
       IPV6_STR
       BGP_STR
       "Display routes matching the community-list\n"
       "community-list name\n")
{
  return bgp_show_community_list (vty, argv[0], 0, AFI_IP6, SAFI_UNICAST);
}

/* old command */
DEFUN (show_ipv6_mbgp_community_list,
       show_ipv6_mbgp_community_list_cmd,
       "show ipv6 mbgp community-list WORD",
       SHOW_STR
       IPV6_STR
       MBGP_STR
       "Display routes matching the community-list\n"
       "community-list name\n")
{
  return bgp_show_community_list (vty, argv[0], 0, AFI_IP6, SAFI_MULTICAST);
}

DEFUN (show_bgp_community_list_exact,
       show_bgp_community_list_exact_cmd,
       "show bgp community-list (<1-500>|WORD) exact-match",
       SHOW_STR
       BGP_STR
       "Display routes matching the community-list\n"
       "community-list number\n"
       "community-list name\n"
       "Exact match of the communities\n")
{
  return bgp_show_community_list (vty, argv[0], 1, AFI_IP6, SAFI_UNICAST);
}

ALIAS (show_bgp_community_list_exact,
       show_bgp_ipv6_community_list_exact_cmd,
       "show bgp ipv6 community-list (<1-500>|WORD) exact-match",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Display routes matching the community-list\n"
       "community-list number\n"
       "community-list name\n"
       "Exact match of the communities\n")

/* old command */
DEFUN (show_ipv6_bgp_community_list_exact,
       show_ipv6_bgp_community_list_exact_cmd,
       "show ipv6 bgp community-list WORD exact-match",
       SHOW_STR
       IPV6_STR
       BGP_STR
       "Display routes matching the community-list\n"
       "community-list name\n"
       "Exact match of the communities\n")
{
  return bgp_show_community_list (vty, argv[0], 1, AFI_IP6, SAFI_UNICAST);
}

/* old command */
DEFUN (show_ipv6_mbgp_community_list_exact,
       show_ipv6_mbgp_community_list_exact_cmd,
       "show ipv6 mbgp community-list WORD exact-match",
       SHOW_STR
       IPV6_STR
       MBGP_STR
       "Display routes matching the community-list\n"
       "community-list name\n"
       "Exact match of the communities\n")
{
  return bgp_show_community_list (vty, argv[0], 1, AFI_IP6, SAFI_MULTICAST);
}
#endif /* HAVE_IPV6 */

DEFUN (show_ip_bgp_prefix_longer,
       show_ip_bgp_prefix_longer_cmd,
       "show ip bgp A.B.C.D/M longer-prefixes",
       SHOW_STR
       IP_STR
       BGP_STR
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Display route and more specific routes\n")
{
  return bgp_show_prefix_longer (vty, argv[0], AFI_IP, SAFI_UNICAST,
				 bgp_show_type_prefix_longer);
}

DEFUN (show_ip_bgp_flap_prefix_longer,
       show_ip_bgp_flap_prefix_longer_cmd,
       "show ip bgp flap-statistics A.B.C.D/M longer-prefixes",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display flap statistics of routes\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Display route and more specific routes\n")
{
  return bgp_show_prefix_longer (vty, argv[0], AFI_IP, SAFI_UNICAST,
				 bgp_show_type_flap_prefix_longer);
}

DEFUN (show_ip_bgp_ipv4_prefix_longer,
       show_ip_bgp_ipv4_prefix_longer_cmd,
       "show ip bgp ipv4 (unicast|multicast) A.B.C.D/M longer-prefixes",
       SHOW_STR
       IP_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Display route and more specific routes\n")
{
  if (strncmp (argv[0], "m", 1) == 0)
    return bgp_show_prefix_longer (vty, argv[1], AFI_IP, SAFI_MULTICAST,
				   bgp_show_type_prefix_longer);

  return bgp_show_prefix_longer (vty, argv[1], AFI_IP, SAFI_UNICAST,
				 bgp_show_type_prefix_longer);
}

DEFUN (show_ip_bgp_flap_address,
       show_ip_bgp_flap_address_cmd,
       "show ip bgp flap-statistics A.B.C.D",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display flap statistics of routes\n"
       "Network in the BGP routing table to display\n")
{
  return bgp_show_prefix_longer (vty, argv[0], AFI_IP, SAFI_UNICAST,
				 bgp_show_type_flap_address);
}

DEFUN (show_ip_bgp_flap_prefix,
       show_ip_bgp_flap_prefix_cmd,
       "show ip bgp flap-statistics A.B.C.D/M",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display flap statistics of routes\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n")
{
  return bgp_show_prefix_longer (vty, argv[0], AFI_IP, SAFI_UNICAST,
				 bgp_show_type_flap_prefix);
}
#ifdef HAVE_IPV6
DEFUN (show_bgp_prefix_longer,
       show_bgp_prefix_longer_cmd,
       "show bgp X:X::X:X/M longer-prefixes",
       SHOW_STR
       BGP_STR
       "IPv6 prefix <network>/<length>\n"
       "Display route and more specific routes\n")
{
  return bgp_show_prefix_longer (vty, argv[0], AFI_IP6, SAFI_UNICAST,
				 bgp_show_type_prefix_longer);
}

ALIAS (show_bgp_prefix_longer,
       show_bgp_ipv6_prefix_longer_cmd,
       "show bgp ipv6 X:X::X:X/M longer-prefixes",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "IPv6 prefix <network>/<length>\n"
       "Display route and more specific routes\n")

/* old command */
DEFUN (show_ipv6_bgp_prefix_longer,
       show_ipv6_bgp_prefix_longer_cmd,
       "show ipv6 bgp X:X::X:X/M longer-prefixes",
       SHOW_STR
       IPV6_STR
       BGP_STR
       "IPv6 prefix <network>/<length>, e.g., 3ffe::/16\n"
       "Display route and more specific routes\n")
{
  return bgp_show_prefix_longer (vty, argv[0], AFI_IP6, SAFI_UNICAST,
				 bgp_show_type_prefix_longer);
}

/* old command */
DEFUN (show_ipv6_mbgp_prefix_longer,
       show_ipv6_mbgp_prefix_longer_cmd,
       "show ipv6 mbgp X:X::X:X/M longer-prefixes",
       SHOW_STR
       IPV6_STR
       MBGP_STR
       "IPv6 prefix <network>/<length>, e.g., 3ffe::/16\n"
       "Display route and more specific routes\n")
{
  return bgp_show_prefix_longer (vty, argv[0], AFI_IP6, SAFI_MULTICAST,
				 bgp_show_type_prefix_longer);
}
#endif /* HAVE_IPV6 */

DEFUN (show_bgp_statistics,
       show_bgp_statistics_cmd,
       "show bgp (ipv4|ipv6) (unicast|multicast) statistics",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP RIB advertisement statistics\n")
{
  return bgp_table_stats_vty (vty, NULL, argv[0], argv[1]);
}

ALIAS (show_bgp_statistics,
       show_bgp_statistics_vpnv4_cmd,
       "show bgp (ipv4) (vpnv4) statistics",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "BGP RIB advertisement statistics\n")

DEFUN (show_bgp_statistics_view,
       show_bgp_statistics_view_cmd,
       "show bgp view WORD (ipv4|ipv6) (unicast|multicast) statistics",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "Address family\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP RIB advertisement statistics\n")
{
  return bgp_table_stats_vty (vty, NULL, argv[0], argv[1]);
}

ALIAS (show_bgp_statistics_view,
       show_bgp_statistics_view_vpnv4_cmd,
       "show bgp view WORD (ipv4) (vpnv4) statistics",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "Address family\n"
       "Address Family modifier\n"
       "BGP RIB advertisement statistics\n")

DEFUN (show_ip_bgp_neighbor_prefix_counts,
       show_ip_bgp_neighbor_prefix_counts_cmd,
       "show ip bgp neighbors (A.B.C.D|X:X::X:X) prefix-counts",
       SHOW_STR
       IP_STR
       BGP_STR
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display detailed prefix count information\n")
{
  struct peer *peer;

  peer = peer_lookup_in_view (vty, NULL, argv[0]);
  if (! peer)
    return CMD_WARNING;

  return bgp_peer_counts (vty, peer, AFI_IP, SAFI_UNICAST);
}

DEFUN (show_bgp_ipv6_neighbor_prefix_counts,
       show_bgp_ipv6_neighbor_prefix_counts_cmd,
       "show bgp ipv6 neighbors (A.B.C.D|X:X::X:X) prefix-counts",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display detailed prefix count information\n")
{
  struct peer *peer;

  peer = peer_lookup_in_view (vty, NULL, argv[0]);
  if (! peer)
    return CMD_WARNING;

  return bgp_peer_counts (vty, peer, AFI_IP6, SAFI_UNICAST);
}

DEFUN (show_ip_bgp_ipv4_neighbor_prefix_counts,
       show_ip_bgp_ipv4_neighbor_prefix_counts_cmd,
       "show ip bgp ipv4 (unicast|multicast) neighbors (A.B.C.D|X:X::X:X) prefix-counts",
       SHOW_STR
       IP_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display detailed prefix count information\n")
{
  struct peer *peer;

  peer = peer_lookup_in_view (vty, NULL, argv[1]);
  if (! peer)
    return CMD_WARNING;

  if (strncmp (argv[0], "m", 1) == 0)
    return bgp_peer_counts (vty, peer, AFI_IP, SAFI_MULTICAST);

  return bgp_peer_counts (vty, peer, AFI_IP, SAFI_UNICAST);
}

DEFUN (show_ip_bgp_vpnv4_neighbor_prefix_counts,
       show_ip_bgp_vpnv4_neighbor_prefix_counts_cmd,
       "show ip bgp vpnv4 all neighbors (A.B.C.D|X:X::X:X) prefix-counts",
       SHOW_STR
       IP_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display detailed prefix count information\n")
{
  struct peer *peer;

  peer = peer_lookup_in_view (vty, NULL, argv[0]);
  if (! peer)
    return CMD_WARNING;

  return bgp_peer_counts (vty, peer, AFI_IP, SAFI_MPLS_VPN);
}

DEFUN (show_ip_bgp_view_neighbor_advertised_route,
       show_ip_bgp_view_neighbor_advertised_route_cmd,
       "show ip bgp view WORD neighbors (A.B.C.D|X:X::X:X) advertised-routes",
       SHOW_STR
       IP_STR
       BGP_STR
       "BGP view\n"
       "View name\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display the routes advertised to a BGP neighbor\n")
{
  struct peer *peer;

  if (argc == 2)
    peer = peer_lookup_in_view (vty, argv[0], argv[1]);
  else
    peer = peer_lookup_in_view (vty, NULL, argv[0]);

  if (! peer)
    return CMD_WARNING;

  return peer_adj_routes (vty, peer, AFI_IP, SAFI_UNICAST, 0);
}

ALIAS (show_ip_bgp_view_neighbor_advertised_route,
       show_ip_bgp_neighbor_advertised_route_cmd,
       "show ip bgp neighbors (A.B.C.D|X:X::X:X) advertised-routes",
       SHOW_STR
       IP_STR
       BGP_STR
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display the routes advertised to a BGP neighbor\n")

DEFUN (show_ip_bgp_ipv4_neighbor_advertised_route,
       show_ip_bgp_ipv4_neighbor_advertised_route_cmd,
       "show ip bgp ipv4 (unicast|multicast) neighbors (A.B.C.D|X:X::X:X) advertised-routes",
       SHOW_STR
       IP_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display the routes advertised to a BGP neighbor\n")
{
  struct peer *peer;

  peer = peer_lookup_in_view (vty, NULL, argv[1]);
  if (! peer)
    return CMD_WARNING;

  if (strncmp (argv[0], "m", 1) == 0)
    return peer_adj_routes (vty, peer, AFI_IP, SAFI_MULTICAST, 0);

  return peer_adj_routes (vty, peer, AFI_IP, SAFI_UNICAST, 0);
}

#ifdef HAVE_IPV6
DEFUN (show_bgp_view_neighbor_advertised_route,
       show_bgp_view_neighbor_advertised_route_cmd,
       "show bgp view WORD neighbors (A.B.C.D|X:X::X:X) advertised-routes",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "View name\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display the routes advertised to a BGP neighbor\n")
{
  struct peer *peer;

  if (argc == 2)
    peer = peer_lookup_in_view (vty, argv[0], argv[1]);
  else
    peer = peer_lookup_in_view (vty, NULL, argv[0]);

  if (! peer)
    return CMD_WARNING;

  return peer_adj_routes (vty, peer, AFI_IP6, SAFI_UNICAST, 0);
}

ALIAS (show_bgp_view_neighbor_advertised_route,
       show_bgp_view_ipv6_neighbor_advertised_route_cmd,
       "show bgp view WORD ipv6 neighbors (A.B.C.D|X:X::X:X) advertised-routes",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display the routes advertised to a BGP neighbor\n")

DEFUN (show_bgp_view_neighbor_received_routes,
       show_bgp_view_neighbor_received_routes_cmd,
       "show bgp view WORD neighbors (A.B.C.D|X:X::X:X) received-routes",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "View name\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display the received routes from neighbor\n")
{
  struct peer *peer;

  if (argc == 2)
    peer = peer_lookup_in_view (vty, argv[0], argv[1]);
  else
    peer = peer_lookup_in_view (vty, NULL, argv[0]);

  if (! peer)
    return CMD_WARNING;

  return peer_adj_routes (vty, peer, AFI_IP6, SAFI_UNICAST, 1);
}

ALIAS (show_bgp_view_neighbor_received_routes,
       show_bgp_view_ipv6_neighbor_received_routes_cmd,
       "show bgp view WORD ipv6 neighbors (A.B.C.D|X:X::X:X) received-routes",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display the received routes from neighbor\n")

ALIAS (show_bgp_view_neighbor_advertised_route,
       show_bgp_neighbor_advertised_route_cmd,
       "show bgp neighbors (A.B.C.D|X:X::X:X) advertised-routes",
       SHOW_STR
       BGP_STR
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display the routes advertised to a BGP neighbor\n")

ALIAS (show_bgp_view_neighbor_advertised_route,
       show_bgp_ipv6_neighbor_advertised_route_cmd,
       "show bgp ipv6 neighbors (A.B.C.D|X:X::X:X) advertised-routes",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display the routes advertised to a BGP neighbor\n")

/* old command */
ALIAS (show_bgp_view_neighbor_advertised_route,
       ipv6_bgp_neighbor_advertised_route_cmd,
       "show ipv6 bgp neighbors (A.B.C.D|X:X::X:X) advertised-routes",
       SHOW_STR
       IPV6_STR
       BGP_STR
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display the routes advertised to a BGP neighbor\n")

/* old command */
DEFUN (ipv6_mbgp_neighbor_advertised_route,
       ipv6_mbgp_neighbor_advertised_route_cmd,
       "show ipv6 mbgp neighbors (A.B.C.D|X:X::X:X) advertised-routes",
       SHOW_STR
       IPV6_STR
       MBGP_STR
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display the routes advertised to a BGP neighbor\n")
{
  struct peer *peer;

  peer = peer_lookup_in_view (vty, NULL, argv[0]);
  if (! peer)
    return CMD_WARNING;

  return peer_adj_routes (vty, peer, AFI_IP6, SAFI_MULTICAST, 0);
}
#endif /* HAVE_IPV6 */

DEFUN (show_ip_bgp_view_neighbor_received_routes,
       show_ip_bgp_view_neighbor_received_routes_cmd,
       "show ip bgp view WORD neighbors (A.B.C.D|X:X::X:X) received-routes",
       SHOW_STR
       IP_STR
       BGP_STR
       "BGP view\n"
       "View name\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display the received routes from neighbor\n")
{
  struct peer *peer;

  if (argc == 2)
    peer = peer_lookup_in_view (vty, argv[0], argv[1]);
  else
    peer = peer_lookup_in_view (vty, NULL, argv[0]);

  if (! peer)
    return CMD_WARNING;

  return peer_adj_routes (vty, peer, AFI_IP, SAFI_UNICAST, 1);
}

ALIAS (show_ip_bgp_view_neighbor_received_routes,
       show_ip_bgp_neighbor_received_routes_cmd,
       "show ip bgp neighbors (A.B.C.D|X:X::X:X) received-routes",
       SHOW_STR
       IP_STR
       BGP_STR
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display the received routes from neighbor\n")

DEFUN (show_ip_bgp_ipv4_neighbor_received_routes,
       show_ip_bgp_ipv4_neighbor_received_routes_cmd,
       "show ip bgp ipv4 (unicast|multicast) neighbors (A.B.C.D|X:X::X:X) received-routes",
       SHOW_STR
       IP_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display the received routes from neighbor\n")
{
  struct peer *peer;

  peer = peer_lookup_in_view (vty, NULL, argv[1]);
  if (! peer)
    return CMD_WARNING;

  if (strncmp (argv[0], "m", 1) == 0)
    return peer_adj_routes (vty, peer, AFI_IP, SAFI_MULTICAST, 1);

  return peer_adj_routes (vty, peer, AFI_IP, SAFI_UNICAST, 1);
}

DEFUN (show_bgp_view_afi_safi_neighbor_adv_recd_routes,
       show_bgp_view_afi_safi_neighbor_adv_recd_routes_cmd,
#ifdef HAVE_IPV6
       "show bgp view WORD (ipv4|ipv6) (unicast|multicast) neighbors (A.B.C.D|X:X::X:X) (advertised-routes|received-routes)",
#else
       "show bgp view WORD ipv4 (unicast|multicast) neighbors (A.B.C.D|X:X::X:X) (advertised-routes|received-routes)",
#endif
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "BGP view name\n"
       "Address family\n"
#ifdef HAVE_IPV6
       "Address family\n"
#endif
       "Address family modifier\n"
       "Address family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display the advertised routes to neighbor\n"
       "Display the received routes from neighbor\n")
{
  int afi;
  int safi;
  int in;
  struct peer *peer;

#ifdef HAVE_IPV6
    peer = peer_lookup_in_view (vty, argv[0], argv[3]);
#else
    peer = peer_lookup_in_view (vty, argv[0], argv[2]);
#endif

  if (! peer)
    return CMD_WARNING;

#ifdef HAVE_IPV6
  afi = (strncmp (argv[1], "ipv6", 4) == 0) ? AFI_IP6 : AFI_IP;
  safi = (strncmp (argv[2], "m", 1) == 0) ? SAFI_MULTICAST : SAFI_UNICAST;
  in = (strncmp (argv[4], "r", 1) == 0) ? 1 : 0;
#else
  afi = AFI_IP;
  safi = (strncmp (argv[1], "m", 1) == 0) ? SAFI_MULTICAST : SAFI_UNICAST;
  in = (strncmp (argv[3], "r", 1) == 0) ? 1 : 0;
#endif

  return peer_adj_routes (vty, peer, afi, safi, in);
}

DEFUN (show_ip_bgp_neighbor_received_prefix_filter,
       show_ip_bgp_neighbor_received_prefix_filter_cmd,
       "show ip bgp neighbors (A.B.C.D|X:X::X:X) received prefix-filter",
       SHOW_STR
       IP_STR
       BGP_STR
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display information received from a BGP neighbor\n"
       "Display the prefixlist filter\n")
{
  char name[BUFSIZ];
  union sockunion su;
  struct peer *peer;
  int count, ret;

  ret = str2sockunion (argv[0], &su);
  if (ret < 0)
    {
      vty_out (vty, "Malformed address: %s%s", argv[0], VTY_NEWLINE);
      return CMD_WARNING;
    }

  peer = peer_lookup (NULL, &su);
  if (! peer)
    return CMD_WARNING;

  sprintf (name, "%s.%d.%d", peer->host, AFI_IP, SAFI_UNICAST);
  count =  prefix_bgp_show_prefix_list (NULL, AFI_IP, name);
  if (count)
    {
      vty_out (vty, "Address family: IPv4 Unicast%s", VTY_NEWLINE);
      prefix_bgp_show_prefix_list (vty, AFI_IP, name);
    }

  return CMD_SUCCESS;
}

DEFUN (show_ip_bgp_ipv4_neighbor_received_prefix_filter,
       show_ip_bgp_ipv4_neighbor_received_prefix_filter_cmd,
       "show ip bgp ipv4 (unicast|multicast) neighbors (A.B.C.D|X:X::X:X) received prefix-filter",
       SHOW_STR
       IP_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display information received from a BGP neighbor\n"
       "Display the prefixlist filter\n")
{
  char name[BUFSIZ];
  union sockunion su;
  struct peer *peer;
  int count, ret;

  ret = str2sockunion (argv[1], &su);
  if (ret < 0)
    {
      vty_out (vty, "Malformed address: %s%s", argv[1], VTY_NEWLINE);
      return CMD_WARNING;
    }

  peer = peer_lookup (NULL, &su);
  if (! peer)
    return CMD_WARNING;

  if (strncmp (argv[0], "m", 1) == 0)
    {
      sprintf (name, "%s.%d.%d", peer->host, AFI_IP, SAFI_MULTICAST);
      count =  prefix_bgp_show_prefix_list (NULL, AFI_IP, name);
      if (count)
	{
	  vty_out (vty, "Address family: IPv4 Multicast%s", VTY_NEWLINE);
	  prefix_bgp_show_prefix_list (vty, AFI_IP, name);
	}
    }
  else
    {
      sprintf (name, "%s.%d.%d", peer->host, AFI_IP, SAFI_UNICAST);
      count =  prefix_bgp_show_prefix_list (NULL, AFI_IP, name);
      if (count)
	{
	  vty_out (vty, "Address family: IPv4 Unicast%s", VTY_NEWLINE);
	  prefix_bgp_show_prefix_list (vty, AFI_IP, name);
	}
    }

  return CMD_SUCCESS;
}


#ifdef HAVE_IPV6
ALIAS (show_bgp_view_neighbor_received_routes,
       show_bgp_neighbor_received_routes_cmd,
       "show bgp neighbors (A.B.C.D|X:X::X:X) received-routes",
       SHOW_STR
       BGP_STR
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display the received routes from neighbor\n")

ALIAS (show_bgp_view_neighbor_received_routes,
       show_bgp_ipv6_neighbor_received_routes_cmd,
       "show bgp ipv6 neighbors (A.B.C.D|X:X::X:X) received-routes",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display the received routes from neighbor\n")

DEFUN (show_bgp_neighbor_received_prefix_filter,
       show_bgp_neighbor_received_prefix_filter_cmd,
       "show bgp neighbors (A.B.C.D|X:X::X:X) received prefix-filter",
       SHOW_STR
       BGP_STR
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display information received from a BGP neighbor\n"
       "Display the prefixlist filter\n")
{
  char name[BUFSIZ];
  union sockunion su;
  struct peer *peer;
  int count, ret;

  ret = str2sockunion (argv[0], &su);
  if (ret < 0)
    {
      vty_out (vty, "Malformed address: %s%s", argv[0], VTY_NEWLINE);
      return CMD_WARNING;
    }

  peer = peer_lookup (NULL, &su);
  if (! peer)
    return CMD_WARNING;

  sprintf (name, "%s.%d.%d", peer->host, AFI_IP6, SAFI_UNICAST);
  count =  prefix_bgp_show_prefix_list (NULL, AFI_IP6, name);
  if (count)
    {
      vty_out (vty, "Address family: IPv6 Unicast%s", VTY_NEWLINE);
      prefix_bgp_show_prefix_list (vty, AFI_IP6, name);
    }

  return CMD_SUCCESS;
}

ALIAS (show_bgp_neighbor_received_prefix_filter,
       show_bgp_ipv6_neighbor_received_prefix_filter_cmd,
       "show bgp ipv6 neighbors (A.B.C.D|X:X::X:X) received prefix-filter",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display information received from a BGP neighbor\n"
       "Display the prefixlist filter\n")

/* old command */
ALIAS (show_bgp_view_neighbor_received_routes,
       ipv6_bgp_neighbor_received_routes_cmd,
       "show ipv6 bgp neighbors (A.B.C.D|X:X::X:X) received-routes",
       SHOW_STR
       IPV6_STR
       BGP_STR
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display the received routes from neighbor\n")

/* old command */
DEFUN (ipv6_mbgp_neighbor_received_routes,
       ipv6_mbgp_neighbor_received_routes_cmd,
       "show ipv6 mbgp neighbors (A.B.C.D|X:X::X:X) received-routes",
       SHOW_STR
       IPV6_STR
       MBGP_STR
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display the received routes from neighbor\n")
{
  struct peer *peer;

  peer = peer_lookup_in_view (vty, NULL, argv[0]);
  if (! peer)
    return CMD_WARNING;

  return peer_adj_routes (vty, peer, AFI_IP6, SAFI_MULTICAST, 1);
}

DEFUN (show_bgp_view_neighbor_received_prefix_filter,
       show_bgp_view_neighbor_received_prefix_filter_cmd,
       "show bgp view WORD neighbors (A.B.C.D|X:X::X:X) received prefix-filter",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "View name\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display information received from a BGP neighbor\n"
       "Display the prefixlist filter\n")
{
  char name[BUFSIZ];
  union sockunion su;
  struct peer *peer;
  struct bgp *bgp;
  int count, ret;

  /* BGP structure lookup. */
  bgp = bgp_lookup_by_name (argv[0]);
  if (bgp == NULL)
  {
	  vty_out (vty, "Can't find BGP view %s%s", argv[0], VTY_NEWLINE);
	  return CMD_WARNING;
	}

  ret = str2sockunion (argv[1], &su);
  if (ret < 0)
    {
      vty_out (vty, "Malformed address: %s%s", argv[1], VTY_NEWLINE);
      return CMD_WARNING;
    }

  peer = peer_lookup (bgp, &su);
  if (! peer)
    return CMD_WARNING;

  sprintf (name, "%s.%d.%d", peer->host, AFI_IP6, SAFI_UNICAST);
  count =  prefix_bgp_show_prefix_list (NULL, AFI_IP6, name);
  if (count)
    {
      vty_out (vty, "Address family: IPv6 Unicast%s", VTY_NEWLINE);
      prefix_bgp_show_prefix_list (vty, AFI_IP6, name);
    }

  return CMD_SUCCESS;
}

ALIAS (show_bgp_view_neighbor_received_prefix_filter,
       show_bgp_view_ipv6_neighbor_received_prefix_filter_cmd,
       "show bgp view WORD ipv6 neighbors (A.B.C.D|X:X::X:X) received prefix-filter",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display information received from a BGP neighbor\n"
       "Display the prefixlist filter\n")
#endif /* HAVE_IPV6 */

DEFUN (show_ip_bgp_neighbor_routes,
       show_ip_bgp_neighbor_routes_cmd,
       "show ip bgp neighbors (A.B.C.D|X:X::X:X) routes",
       SHOW_STR
       IP_STR
       BGP_STR
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display routes learned from neighbor\n")
{
  struct peer *peer;

  peer = peer_lookup_in_view (vty, NULL, argv[0]);
  if (! peer)
    return CMD_WARNING;

  return bgp_show_neighbor_route (vty, peer, AFI_IP, SAFI_UNICAST,
				  bgp_show_type_neighbor);
}

DEFUN (show_ip_bgp_neighbor_flap,
       show_ip_bgp_neighbor_flap_cmd,
       "show ip bgp neighbors (A.B.C.D|X:X::X:X) flap-statistics",
       SHOW_STR
       IP_STR
       BGP_STR
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display flap statistics of the routes learned from neighbor\n")
{
  struct peer *peer;

  peer = peer_lookup_in_view (vty, NULL, argv[0]);
  if (! peer)
    return CMD_WARNING;

  return bgp_show_neighbor_route (vty, peer, AFI_IP, SAFI_UNICAST,
				  bgp_show_type_flap_neighbor);
}

DEFUN (show_ip_bgp_neighbor_damp,
       show_ip_bgp_neighbor_damp_cmd,
       "show ip bgp neighbors (A.B.C.D|X:X::X:X) dampened-routes",
       SHOW_STR
       IP_STR
       BGP_STR
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display the dampened routes received from neighbor\n")
{
  struct peer *peer;

  peer = peer_lookup_in_view (vty, NULL, argv[0]);
  if (! peer)
    return CMD_WARNING;

  return bgp_show_neighbor_route (vty, peer, AFI_IP, SAFI_UNICAST,
				  bgp_show_type_damp_neighbor);
}

DEFUN (show_ip_bgp_ipv4_neighbor_routes,
       show_ip_bgp_ipv4_neighbor_routes_cmd,
       "show ip bgp ipv4 (unicast|multicast) neighbors (A.B.C.D|X:X::X:X) routes",
       SHOW_STR
       IP_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display routes learned from neighbor\n")
{
  struct peer *peer;

  peer = peer_lookup_in_view (vty, NULL, argv[1]);
  if (! peer)
    return CMD_WARNING;

  if (strncmp (argv[0], "m", 1) == 0)
    return bgp_show_neighbor_route (vty, peer, AFI_IP, SAFI_MULTICAST,
				    bgp_show_type_neighbor);

  return bgp_show_neighbor_route (vty, peer, AFI_IP, SAFI_UNICAST,
				  bgp_show_type_neighbor);
}

DEFUN (show_ip_bgp_view_rsclient,
       show_ip_bgp_view_rsclient_cmd,
       "show ip bgp view WORD rsclient (A.B.C.D|X:X::X:X)",
       SHOW_STR
       IP_STR
       BGP_STR
       "BGP view\n"
       "BGP view name\n"
       "Information about Route Server Client\n"
       NEIGHBOR_ADDR_STR)
{
  struct bgp_table *table;
  struct peer *peer;

  if (argc == 2)
    peer = peer_lookup_in_view (vty, argv[0], argv[1]);
  else
    peer = peer_lookup_in_view (vty, NULL, argv[0]);

  if (! peer)
    return CMD_WARNING;

  if (! peer->afc[AFI_IP][SAFI_UNICAST])
    {
      vty_out (vty, "%% Activate the neighbor for the address family first%s",
            VTY_NEWLINE);
      return CMD_WARNING;
    }

  if ( ! CHECK_FLAG (peer->af_flags[AFI_IP][SAFI_UNICAST],
              PEER_FLAG_RSERVER_CLIENT))
    {
      vty_out (vty, "%% Neighbor is not a Route-Server client%s",
            VTY_NEWLINE);
      return CMD_WARNING;
    }

  table = peer->rib[AFI_IP][SAFI_UNICAST];

  return bgp_show_table (vty, table, &peer->remote_id, bgp_show_type_normal, NULL);
}

ALIAS (show_ip_bgp_view_rsclient,
       show_ip_bgp_rsclient_cmd,
       "show ip bgp rsclient (A.B.C.D|X:X::X:X)",
       SHOW_STR
       IP_STR
       BGP_STR
       "Information about Route Server Client\n"
       NEIGHBOR_ADDR_STR)

DEFUN (show_bgp_view_ipv4_safi_rsclient,
       show_bgp_view_ipv4_safi_rsclient_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) rsclient (A.B.C.D|X:X::X:X)",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "BGP view name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Information about Route Server Client\n"
       NEIGHBOR_ADDR_STR)
{
  struct bgp_table *table;
  struct peer *peer;
  safi_t safi;

  if (argc == 3) {
    peer = peer_lookup_in_view (vty, argv[0], argv[2]);
    safi = (strncmp (argv[1], "m", 1) == 0) ? SAFI_MULTICAST : SAFI_UNICAST;
  } else {
    peer = peer_lookup_in_view (vty, NULL, argv[1]);
    safi = (strncmp (argv[0], "m", 1) == 0) ? SAFI_MULTICAST : SAFI_UNICAST;
  }

  if (! peer)
    return CMD_WARNING;

  if (! peer->afc[AFI_IP][safi])
    {
      vty_out (vty, "%% Activate the neighbor for the address family first%s",
            VTY_NEWLINE);
      return CMD_WARNING;
    }

  if ( ! CHECK_FLAG (peer->af_flags[AFI_IP][safi],
              PEER_FLAG_RSERVER_CLIENT))
    {
      vty_out (vty, "%% Neighbor is not a Route-Server client%s",
            VTY_NEWLINE);
      return CMD_WARNING;
    }

  table = peer->rib[AFI_IP][safi];

  return bgp_show_table (vty, table, &peer->remote_id, bgp_show_type_normal, NULL);
}

ALIAS (show_bgp_view_ipv4_safi_rsclient,
       show_bgp_ipv4_safi_rsclient_cmd,
       "show bgp ipv4 (unicast|multicast) rsclient (A.B.C.D|X:X::X:X)",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Information about Route Server Client\n"
       NEIGHBOR_ADDR_STR)

DEFUN (show_ip_bgp_view_rsclient_route,
       show_ip_bgp_view_rsclient_route_cmd,
       "show ip bgp view WORD rsclient (A.B.C.D|X:X::X:X) A.B.C.D",
       SHOW_STR
       IP_STR
       BGP_STR
       "BGP view\n"
       "BGP view name\n"
       "Information about Route Server Client\n"
       NEIGHBOR_ADDR_STR
       "Network in the BGP routing table to display\n")
{
  struct bgp *bgp;
  struct peer *peer;

  /* BGP structure lookup. */
  if (argc == 3)
    {
      bgp = bgp_lookup_by_name (argv[0]);
      if (bgp == NULL)
	{
	  vty_out (vty, "Can't find BGP view %s%s", argv[0], VTY_NEWLINE);
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

  if (argc == 3)
    peer = peer_lookup_in_view (vty, argv[0], argv[1]);
  else
    peer = peer_lookup_in_view (vty, NULL, argv[0]);

  if (! peer)
    return CMD_WARNING;

  if (! peer->afc[AFI_IP][SAFI_UNICAST])
    {
      vty_out (vty, "%% Activate the neighbor for the address family first%s",
            VTY_NEWLINE);
      return CMD_WARNING;
}

  if ( ! CHECK_FLAG (peer->af_flags[AFI_IP][SAFI_UNICAST],
              PEER_FLAG_RSERVER_CLIENT))
    {
      vty_out (vty, "%% Neighbor is not a Route-Server client%s",
            VTY_NEWLINE);
      return CMD_WARNING;
    }

  return bgp_show_route_in_table (vty, bgp, peer->rib[AFI_IP][SAFI_UNICAST],
                                  (argc == 3) ? argv[2] : argv[1],
                                  AFI_IP, SAFI_UNICAST, NULL, 0);
}

ALIAS (show_ip_bgp_view_rsclient_route,
       show_ip_bgp_rsclient_route_cmd,
       "show ip bgp rsclient (A.B.C.D|X:X::X:X) A.B.C.D",
       SHOW_STR
       IP_STR
       BGP_STR
       "Information about Route Server Client\n"
       NEIGHBOR_ADDR_STR
       "Network in the BGP routing table to display\n")

DEFUN (show_bgp_view_ipv4_safi_rsclient_route,
       show_bgp_view_ipv4_safi_rsclient_route_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) rsclient (A.B.C.D|X:X::X:X) A.B.C.D",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "BGP view name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Information about Route Server Client\n"
       NEIGHBOR_ADDR_STR
       "Network in the BGP routing table to display\n")
{
  struct bgp *bgp;
  struct peer *peer;
  safi_t safi;

  /* BGP structure lookup. */
  if (argc == 4)
    {
      bgp = bgp_lookup_by_name (argv[0]);
      if (bgp == NULL)
	{
	  vty_out (vty, "Can't find BGP view %s%s", argv[0], VTY_NEWLINE);
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

  if (argc == 4) {
    peer = peer_lookup_in_view (vty, argv[0], argv[2]);
    safi = (strncmp (argv[1], "m", 1) == 0) ? SAFI_MULTICAST : SAFI_UNICAST;
  } else {
    peer = peer_lookup_in_view (vty, NULL, argv[1]);
    safi = (strncmp (argv[0], "m", 1) == 0) ? SAFI_MULTICAST : SAFI_UNICAST;
  }

  if (! peer)
    return CMD_WARNING;

  if (! peer->afc[AFI_IP][safi])
    {
      vty_out (vty, "%% Activate the neighbor for the address family first%s",
            VTY_NEWLINE);
      return CMD_WARNING;
}

  if ( ! CHECK_FLAG (peer->af_flags[AFI_IP][safi],
              PEER_FLAG_RSERVER_CLIENT))
    {
      vty_out (vty, "%% Neighbor is not a Route-Server client%s",
            VTY_NEWLINE);
      return CMD_WARNING;
    }

  return bgp_show_route_in_table (vty, bgp, peer->rib[AFI_IP][safi],
                                  (argc == 4) ? argv[3] : argv[2],
                                  AFI_IP, safi, NULL, 0);
}

ALIAS (show_bgp_view_ipv4_safi_rsclient_route,
       show_bgp_ipv4_safi_rsclient_route_cmd,
       "show bgp ipv4 (unicast|multicast) rsclient (A.B.C.D|X:X::X:X) A.B.C.D",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Information about Route Server Client\n"
       NEIGHBOR_ADDR_STR
       "Network in the BGP routing table to display\n")

DEFUN (show_ip_bgp_view_rsclient_prefix,
       show_ip_bgp_view_rsclient_prefix_cmd,
       "show ip bgp view WORD rsclient (A.B.C.D|X:X::X:X) A.B.C.D/M",
       SHOW_STR
       IP_STR
       BGP_STR
       "BGP view\n"
       "BGP view name\n"
       "Information about Route Server Client\n"
       NEIGHBOR_ADDR_STR
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n")
{
  struct bgp *bgp;
  struct peer *peer;

  /* BGP structure lookup. */
  if (argc == 3)
    {
      bgp = bgp_lookup_by_name (argv[0]);
      if (bgp == NULL)
	{
	  vty_out (vty, "Can't find BGP view %s%s", argv[0], VTY_NEWLINE);
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

  if (argc == 3)
    peer = peer_lookup_in_view (vty, argv[0], argv[1]);
  else
  peer = peer_lookup_in_view (vty, NULL, argv[0]);

  if (! peer)
    return CMD_WARNING;

  if (! peer->afc[AFI_IP][SAFI_UNICAST])
    {
      vty_out (vty, "%% Activate the neighbor for the address family first%s",
            VTY_NEWLINE);
      return CMD_WARNING;
}

  if ( ! CHECK_FLAG (peer->af_flags[AFI_IP][SAFI_UNICAST],
              PEER_FLAG_RSERVER_CLIENT))
{
      vty_out (vty, "%% Neighbor is not a Route-Server client%s",
            VTY_NEWLINE);
    return CMD_WARNING;
    }

  return bgp_show_route_in_table (vty, bgp, peer->rib[AFI_IP][SAFI_UNICAST],
                                  (argc == 3) ? argv[2] : argv[1],
                                  AFI_IP, SAFI_UNICAST, NULL, 1);
}

ALIAS (show_ip_bgp_view_rsclient_prefix,
       show_ip_bgp_rsclient_prefix_cmd,
       "show ip bgp rsclient (A.B.C.D|X:X::X:X) A.B.C.D/M",
       SHOW_STR
       IP_STR
       BGP_STR
       "Information about Route Server Client\n"
       NEIGHBOR_ADDR_STR
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n")

DEFUN (show_bgp_view_ipv4_safi_rsclient_prefix,
       show_bgp_view_ipv4_safi_rsclient_prefix_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) rsclient (A.B.C.D|X:X::X:X) A.B.C.D/M",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "BGP view name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Information about Route Server Client\n"
       NEIGHBOR_ADDR_STR
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n")
{
  struct bgp *bgp;
  struct peer *peer;
  safi_t safi;

  /* BGP structure lookup. */
  if (argc == 4)
    {
      bgp = bgp_lookup_by_name (argv[0]);
      if (bgp == NULL)
	{
	  vty_out (vty, "Can't find BGP view %s%s", argv[0], VTY_NEWLINE);
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

  if (argc == 4) {
    peer = peer_lookup_in_view (vty, argv[0], argv[2]);
    safi = (strncmp (argv[1], "m", 1) == 0) ? SAFI_MULTICAST : SAFI_UNICAST;
  } else {
    peer = peer_lookup_in_view (vty, NULL, argv[1]);
    safi = (strncmp (argv[0], "m", 1) == 0) ? SAFI_MULTICAST : SAFI_UNICAST;
  }

  if (! peer)
    return CMD_WARNING;

  if (! peer->afc[AFI_IP][safi])
    {
      vty_out (vty, "%% Activate the neighbor for the address family first%s",
            VTY_NEWLINE);
      return CMD_WARNING;
}

  if ( ! CHECK_FLAG (peer->af_flags[AFI_IP][safi],
              PEER_FLAG_RSERVER_CLIENT))
{
      vty_out (vty, "%% Neighbor is not a Route-Server client%s",
            VTY_NEWLINE);
    return CMD_WARNING;
    }

  return bgp_show_route_in_table (vty, bgp, peer->rib[AFI_IP][safi],
                                  (argc == 4) ? argv[3] : argv[2],
                                  AFI_IP, safi, NULL, 1);
}

ALIAS (show_bgp_view_ipv4_safi_rsclient_prefix,
       show_bgp_ipv4_safi_rsclient_prefix_cmd,
       "show bgp ipv4 (unicast|multicast) rsclient (A.B.C.D|X:X::X:X) A.B.C.D/M",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Information about Route Server Client\n"
       NEIGHBOR_ADDR_STR
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n")

#ifdef HAVE_IPV6
DEFUN (show_bgp_view_neighbor_routes,
       show_bgp_view_neighbor_routes_cmd,
       "show bgp view WORD neighbors (A.B.C.D|X:X::X:X) routes",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "BGP view name\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display routes learned from neighbor\n")
{
  struct peer *peer;

  if (argc == 2)
    peer = peer_lookup_in_view (vty, argv[0], argv[1]);
  else
    peer = peer_lookup_in_view (vty, NULL, argv[0]);

  if (! peer)
    return CMD_WARNING;

  return bgp_show_neighbor_route (vty, peer, AFI_IP6, SAFI_UNICAST,
				  bgp_show_type_neighbor);
}

ALIAS (show_bgp_view_neighbor_routes,
       show_bgp_view_ipv6_neighbor_routes_cmd,
       "show bgp view WORD ipv6 neighbors (A.B.C.D|X:X::X:X) routes",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "BGP view name\n"
       "Address family\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display routes learned from neighbor\n")

DEFUN (show_bgp_view_neighbor_damp,
       show_bgp_view_neighbor_damp_cmd,
       "show bgp view WORD neighbors (A.B.C.D|X:X::X:X) dampened-routes",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "BGP view name\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display the dampened routes received from neighbor\n")
{
  struct peer *peer;

  if (argc == 2)
    peer = peer_lookup_in_view (vty, argv[0], argv[1]);
  else
    peer = peer_lookup_in_view (vty, NULL, argv[0]);

  if (! peer)
    return CMD_WARNING;

  return bgp_show_neighbor_route (vty, peer, AFI_IP6, SAFI_UNICAST,
				  bgp_show_type_damp_neighbor);
}

ALIAS (show_bgp_view_neighbor_damp,
       show_bgp_view_ipv6_neighbor_damp_cmd,
       "show bgp view WORD ipv6 neighbors (A.B.C.D|X:X::X:X) dampened-routes",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "BGP view name\n"
       "Address family\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display the dampened routes received from neighbor\n")

DEFUN (show_bgp_view_neighbor_flap,
       show_bgp_view_neighbor_flap_cmd,
       "show bgp view WORD neighbors (A.B.C.D|X:X::X:X) flap-statistics",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "BGP view name\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display flap statistics of the routes learned from neighbor\n")
{
  struct peer *peer;

  if (argc == 2)
    peer = peer_lookup_in_view (vty, argv[0], argv[1]);
  else
    peer = peer_lookup_in_view (vty, NULL, argv[0]);

  if (! peer)
    return CMD_WARNING;

  return bgp_show_neighbor_route (vty, peer, AFI_IP6, SAFI_UNICAST,
				  bgp_show_type_flap_neighbor);
}

ALIAS (show_bgp_view_neighbor_flap,
       show_bgp_view_ipv6_neighbor_flap_cmd,
       "show bgp view WORD ipv6 neighbors (A.B.C.D|X:X::X:X) flap-statistics",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "BGP view name\n"
       "Address family\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display flap statistics of the routes learned from neighbor\n")

ALIAS (show_bgp_view_neighbor_routes,
       show_bgp_neighbor_routes_cmd,
       "show bgp neighbors (A.B.C.D|X:X::X:X) routes",
       SHOW_STR
       BGP_STR
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display routes learned from neighbor\n")


ALIAS (show_bgp_view_neighbor_routes,
       show_bgp_ipv6_neighbor_routes_cmd,
       "show bgp ipv6 neighbors (A.B.C.D|X:X::X:X) routes",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display routes learned from neighbor\n")

/* old command */
ALIAS (show_bgp_view_neighbor_routes,
       ipv6_bgp_neighbor_routes_cmd,
       "show ipv6 bgp neighbors (A.B.C.D|X:X::X:X) routes",
       SHOW_STR
       IPV6_STR
       BGP_STR
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display routes learned from neighbor\n")

/* old command */
DEFUN (ipv6_mbgp_neighbor_routes,
       ipv6_mbgp_neighbor_routes_cmd,
       "show ipv6 mbgp neighbors (A.B.C.D|X:X::X:X) routes",
       SHOW_STR
       IPV6_STR
       MBGP_STR
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display routes learned from neighbor\n")
{
  struct peer *peer;

  peer = peer_lookup_in_view (vty, NULL, argv[0]);
  if (! peer)
    return CMD_WARNING;

  return bgp_show_neighbor_route (vty, peer, AFI_IP6, SAFI_MULTICAST,
				  bgp_show_type_neighbor);
}

ALIAS (show_bgp_view_neighbor_flap,
       show_bgp_neighbor_flap_cmd,
       "show bgp neighbors (A.B.C.D|X:X::X:X) flap-statistics",
       SHOW_STR
       BGP_STR
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display flap statistics of the routes learned from neighbor\n")

ALIAS (show_bgp_view_neighbor_flap,
       show_bgp_ipv6_neighbor_flap_cmd,
       "show bgp ipv6 neighbors (A.B.C.D|X:X::X:X) flap-statistics",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display flap statistics of the routes learned from neighbor\n")

ALIAS (show_bgp_view_neighbor_damp,
       show_bgp_neighbor_damp_cmd,
       "show bgp neighbors (A.B.C.D|X:X::X:X) dampened-routes",
       SHOW_STR
       BGP_STR
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display the dampened routes received from neighbor\n")

ALIAS (show_bgp_view_neighbor_damp,
       show_bgp_ipv6_neighbor_damp_cmd,
       "show bgp ipv6 neighbors (A.B.C.D|X:X::X:X) dampened-routes",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n"
       "Display the dampened routes received from neighbor\n")

DEFUN (show_bgp_view_rsclient,
       show_bgp_view_rsclient_cmd,
       "show bgp view WORD rsclient (A.B.C.D|X:X::X:X)",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "BGP view name\n"
       "Information about Route Server Client\n"
       NEIGHBOR_ADDR_STR)
{
  struct bgp_table *table;
  struct peer *peer;

  if (argc == 2)
    peer = peer_lookup_in_view (vty, argv[0], argv[1]);
  else
    peer = peer_lookup_in_view (vty, NULL, argv[0]);

  if (! peer)
    return CMD_WARNING;

  if (! peer->afc[AFI_IP6][SAFI_UNICAST])
    {
      vty_out (vty, "%% Activate the neighbor for the address family first%s",
            VTY_NEWLINE);
      return CMD_WARNING;
    }

  if ( ! CHECK_FLAG (peer->af_flags[AFI_IP6][SAFI_UNICAST],
              PEER_FLAG_RSERVER_CLIENT))
    {
      vty_out (vty, "%% Neighbor is not a Route-Server client%s",
            VTY_NEWLINE);
      return CMD_WARNING;
    }

  table = peer->rib[AFI_IP6][SAFI_UNICAST];

  return bgp_show_table (vty, table, &peer->remote_id, bgp_show_type_normal, NULL);
}

ALIAS (show_bgp_view_rsclient,
       show_bgp_rsclient_cmd,
       "show bgp rsclient (A.B.C.D|X:X::X:X)",
       SHOW_STR
       BGP_STR
       "Information about Route Server Client\n"
       NEIGHBOR_ADDR_STR)

DEFUN (show_bgp_view_ipv6_safi_rsclient,
       show_bgp_view_ipv6_safi_rsclient_cmd,
       "show bgp view WORD ipv6 (unicast|multicast) rsclient (A.B.C.D|X:X::X:X)",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "BGP view name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Information about Route Server Client\n"
       NEIGHBOR_ADDR_STR)
{
  struct bgp_table *table;
  struct peer *peer;
  safi_t safi;

  if (argc == 3) {
    peer = peer_lookup_in_view (vty, argv[0], argv[2]);
    safi = (strncmp (argv[1], "m", 1) == 0) ? SAFI_MULTICAST : SAFI_UNICAST;
  } else {
    peer = peer_lookup_in_view (vty, NULL, argv[1]);
    safi = (strncmp (argv[0], "m", 1) == 0) ? SAFI_MULTICAST : SAFI_UNICAST;
  }

  if (! peer)
    return CMD_WARNING;

  if (! peer->afc[AFI_IP6][safi])
    {
      vty_out (vty, "%% Activate the neighbor for the address family first%s",
            VTY_NEWLINE);
      return CMD_WARNING;
    }

  if ( ! CHECK_FLAG (peer->af_flags[AFI_IP6][safi],
              PEER_FLAG_RSERVER_CLIENT))
    {
      vty_out (vty, "%% Neighbor is not a Route-Server client%s",
            VTY_NEWLINE);
      return CMD_WARNING;
    }

  table = peer->rib[AFI_IP6][safi];

  return bgp_show_table (vty, table, &peer->remote_id, bgp_show_type_normal, NULL);
}

ALIAS (show_bgp_view_ipv6_safi_rsclient,
       show_bgp_ipv6_safi_rsclient_cmd,
       "show bgp ipv6 (unicast|multicast) rsclient (A.B.C.D|X:X::X:X)",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Information about Route Server Client\n"
       NEIGHBOR_ADDR_STR)

DEFUN (show_bgp_view_rsclient_route,
       show_bgp_view_rsclient_route_cmd,
       "show bgp view WORD rsclient (A.B.C.D|X:X::X:X) X:X::X:X",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "BGP view name\n"
       "Information about Route Server Client\n"
       NEIGHBOR_ADDR_STR
       "Network in the BGP routing table to display\n")
{
  struct bgp *bgp;
  struct peer *peer;

  /* BGP structure lookup. */
  if (argc == 3)
    {
      bgp = bgp_lookup_by_name (argv[0]);
      if (bgp == NULL)
        {
          vty_out (vty, "Can't find BGP view %s%s", argv[0], VTY_NEWLINE);
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

  if (argc == 3)
    peer = peer_lookup_in_view (vty, argv[0], argv[1]);
  else
    peer = peer_lookup_in_view (vty, NULL, argv[0]);

  if (! peer)
    return CMD_WARNING;

  if (! peer->afc[AFI_IP6][SAFI_UNICAST])
    {
      vty_out (vty, "%% Activate the neighbor for the address family first%s",
            VTY_NEWLINE);
      return CMD_WARNING;
    }

  if ( ! CHECK_FLAG (peer->af_flags[AFI_IP6][SAFI_UNICAST],
              PEER_FLAG_RSERVER_CLIENT))
    {
      vty_out (vty, "%% Neighbor is not a Route-Server client%s",
            VTY_NEWLINE);
      return CMD_WARNING;
    }

  return bgp_show_route_in_table (vty, bgp, peer->rib[AFI_IP6][SAFI_UNICAST],
                                  (argc == 3) ? argv[2] : argv[1],
                                  AFI_IP6, SAFI_UNICAST, NULL, 0);
}

ALIAS (show_bgp_view_rsclient_route,
       show_bgp_rsclient_route_cmd,
       "show bgp rsclient (A.B.C.D|X:X::X:X) X:X::X:X",
       SHOW_STR
       BGP_STR
       "Information about Route Server Client\n"
       NEIGHBOR_ADDR_STR
       "Network in the BGP routing table to display\n")

DEFUN (show_bgp_view_ipv6_safi_rsclient_route,
       show_bgp_view_ipv6_safi_rsclient_route_cmd,
       "show bgp view WORD ipv6 (unicast|multicast) rsclient (A.B.C.D|X:X::X:X) X:X::X:X",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "BGP view name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Information about Route Server Client\n"
       NEIGHBOR_ADDR_STR
       "Network in the BGP routing table to display\n")
{
  struct bgp *bgp;
  struct peer *peer;
  safi_t safi;

  /* BGP structure lookup. */
  if (argc == 4)
    {
      bgp = bgp_lookup_by_name (argv[0]);
      if (bgp == NULL)
	{
	  vty_out (vty, "Can't find BGP view %s%s", argv[0], VTY_NEWLINE);
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

  if (argc == 4) {
    peer = peer_lookup_in_view (vty, argv[0], argv[2]);
    safi = (strncmp (argv[1], "m", 1) == 0) ? SAFI_MULTICAST : SAFI_UNICAST;
  } else {
    peer = peer_lookup_in_view (vty, NULL, argv[1]);
    safi = (strncmp (argv[0], "m", 1) == 0) ? SAFI_MULTICAST : SAFI_UNICAST;
  }

  if (! peer)
    return CMD_WARNING;

  if (! peer->afc[AFI_IP6][safi])
    {
      vty_out (vty, "%% Activate the neighbor for the address family first%s",
            VTY_NEWLINE);
      return CMD_WARNING;
}

  if ( ! CHECK_FLAG (peer->af_flags[AFI_IP6][safi],
              PEER_FLAG_RSERVER_CLIENT))
    {
      vty_out (vty, "%% Neighbor is not a Route-Server client%s",
            VTY_NEWLINE);
      return CMD_WARNING;
    }

  return bgp_show_route_in_table (vty, bgp, peer->rib[AFI_IP6][safi],
                                  (argc == 4) ? argv[3] : argv[2],
                                  AFI_IP6, safi, NULL, 0);
}

ALIAS (show_bgp_view_ipv6_safi_rsclient_route,
       show_bgp_ipv6_safi_rsclient_route_cmd,
       "show bgp ipv6 (unicast|multicast) rsclient (A.B.C.D|X:X::X:X) X:X::X:X",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Information about Route Server Client\n"
       NEIGHBOR_ADDR_STR
       "Network in the BGP routing table to display\n")

DEFUN (show_bgp_view_rsclient_prefix,
       show_bgp_view_rsclient_prefix_cmd,
       "show bgp view WORD rsclient (A.B.C.D|X:X::X:X) X:X::X:X/M",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "BGP view name\n"
       "Information about Route Server Client\n"
       NEIGHBOR_ADDR_STR
       "IPv6 prefix <network>/<length>, e.g., 3ffe::/16\n")
{
  struct bgp *bgp;
  struct peer *peer;

  /* BGP structure lookup. */
  if (argc == 3)
    {
      bgp = bgp_lookup_by_name (argv[0]);
      if (bgp == NULL)
        {
          vty_out (vty, "Can't find BGP view %s%s", argv[0], VTY_NEWLINE);
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

  if (argc == 3)
    peer = peer_lookup_in_view (vty, argv[0], argv[1]);
  else
    peer = peer_lookup_in_view (vty, NULL, argv[0]);

  if (! peer)
    return CMD_WARNING;

  if (! peer->afc[AFI_IP6][SAFI_UNICAST])
    {
      vty_out (vty, "%% Activate the neighbor for the address family first%s",
            VTY_NEWLINE);
      return CMD_WARNING;
    }

  if ( ! CHECK_FLAG (peer->af_flags[AFI_IP6][SAFI_UNICAST],
              PEER_FLAG_RSERVER_CLIENT))
    {
      vty_out (vty, "%% Neighbor is not a Route-Server client%s",
            VTY_NEWLINE);
      return CMD_WARNING;
    }

  return bgp_show_route_in_table (vty, bgp, peer->rib[AFI_IP6][SAFI_UNICAST],
                                  (argc == 3) ? argv[2] : argv[1],
                                  AFI_IP6, SAFI_UNICAST, NULL, 1);
}

ALIAS (show_bgp_view_rsclient_prefix,
       show_bgp_rsclient_prefix_cmd,
       "show bgp rsclient (A.B.C.D|X:X::X:X) X:X::X:X/M",
       SHOW_STR
       BGP_STR
       "Information about Route Server Client\n"
       NEIGHBOR_ADDR_STR
       "IPv6 prefix <network>/<length>, e.g., 3ffe::/16\n")

DEFUN (show_bgp_view_ipv6_safi_rsclient_prefix,
       show_bgp_view_ipv6_safi_rsclient_prefix_cmd,
       "show bgp view WORD ipv6 (unicast|multicast) rsclient (A.B.C.D|X:X::X:X) X:X::X:X/M",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "BGP view name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Information about Route Server Client\n"
       NEIGHBOR_ADDR_STR
       "IP prefix <network>/<length>, e.g., 3ffe::/16\n")
{
  struct bgp *bgp;
  struct peer *peer;
  safi_t safi;

  /* BGP structure lookup. */
  if (argc == 4)
    {
      bgp = bgp_lookup_by_name (argv[0]);
      if (bgp == NULL)
	{
	  vty_out (vty, "Can't find BGP view %s%s", argv[0], VTY_NEWLINE);
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

  if (argc == 4) {
    peer = peer_lookup_in_view (vty, argv[0], argv[2]);
    safi = (strncmp (argv[1], "m", 1) == 0) ? SAFI_MULTICAST : SAFI_UNICAST;
  } else {
    peer = peer_lookup_in_view (vty, NULL, argv[1]);
    safi = (strncmp (argv[0], "m", 1) == 0) ? SAFI_MULTICAST : SAFI_UNICAST;
  }

  if (! peer)
    return CMD_WARNING;

  if (! peer->afc[AFI_IP6][safi])
    {
      vty_out (vty, "%% Activate the neighbor for the address family first%s",
            VTY_NEWLINE);
      return CMD_WARNING;
}

  if ( ! CHECK_FLAG (peer->af_flags[AFI_IP6][safi],
              PEER_FLAG_RSERVER_CLIENT))
{
      vty_out (vty, "%% Neighbor is not a Route-Server client%s",
            VTY_NEWLINE);
    return CMD_WARNING;
    }

  return bgp_show_route_in_table (vty, bgp, peer->rib[AFI_IP6][safi],
                                  (argc == 4) ? argv[3] : argv[2],
                                  AFI_IP6, safi, NULL, 1);
}

ALIAS (show_bgp_view_ipv6_safi_rsclient_prefix,
       show_bgp_ipv6_safi_rsclient_prefix_cmd,
       "show bgp ipv6 (unicast|multicast) rsclient (A.B.C.D|X:X::X:X) X:X::X:X/M",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Information about Route Server Client\n"
       NEIGHBOR_ADDR_STR
       "IP prefix <network>/<length>, e.g., 3ffe::/16\n")

#endif /* HAVE_IPV6 */

DEFUN (show_ip_bgp_dampened_paths,
       show_ip_bgp_dampened_paths_cmd,
       "show ip bgp dampened-paths",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display paths suppressed due to dampening\n")
{
  return bgp_show (vty, NULL, AFI_IP, SAFI_UNICAST, bgp_show_type_dampend_paths,
                   NULL);
}

DEFUN (show_ip_bgp_flap_statistics,
       show_ip_bgp_flap_statistics_cmd,
       "show ip bgp flap-statistics",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display flap statistics of routes\n")
{
  return bgp_show (vty, NULL, AFI_IP, SAFI_UNICAST,
                   bgp_show_type_flap_statistics, NULL);
}

DEFUN (show_ip_bgp_vpnv4_all,
       show_ip_bgp_vpnv4_all_cmd,
       "show ip bgp vpnv4 all",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display VPNv4 NLRI specific information\n"
       "Display information about all VPNv4 NLRIs\n")
{
  return bgp_show_mpls_vpn (vty, NULL, bgp_show_type_normal, NULL, 0);
}

DEFUN (show_ip_bgp_vpnv4_rd,
       show_ip_bgp_vpnv4_rd_cmd,
       "show ip bgp vpnv4 rd ASN:nn_or_IP-address:nn",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display VPNv4 NLRI specific information\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n")
{
  int ret;
  struct prefix_rd prd;

  ret = str2prefix_rd (argv[0], &prd);
  if (! ret)
    {
      vty_out (vty, "%% Malformed Route Distinguisher%s", VTY_NEWLINE);
      return CMD_WARNING;
    }
  return bgp_show_mpls_vpn (vty, &prd, bgp_show_type_normal, NULL, 0);
}

DEFUN (show_ip_bgp_vpnv4_all_tags,
       show_ip_bgp_vpnv4_all_tags_cmd,
       "show ip bgp vpnv4 all tags",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display VPNv4 NLRI specific information\n"
       "Display information about all VPNv4 NLRIs\n"
       "Display BGP tags for prefixes\n")
{
  return bgp_show_mpls_vpn (vty, NULL, bgp_show_type_normal, NULL,  1);
}

DEFUN (show_ip_bgp_vpnv4_rd_tags,
       show_ip_bgp_vpnv4_rd_tags_cmd,
       "show ip bgp vpnv4 rd ASN:nn_or_IP-address:nn tags",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display VPNv4 NLRI specific information\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Display BGP tags for prefixes\n")
{
  int ret;
  struct prefix_rd prd;

  ret = str2prefix_rd (argv[0], &prd);
  if (! ret)
    {
      vty_out (vty, "%% Malformed Route Distinguisher%s", VTY_NEWLINE);
      return CMD_WARNING;
    }
  return bgp_show_mpls_vpn (vty, &prd, bgp_show_type_normal, NULL, 1);
}

DEFUN (show_ip_bgp_vpnv4_all_neighbor_routes,
       show_ip_bgp_vpnv4_all_neighbor_routes_cmd,
       "show ip bgp vpnv4 all neighbors A.B.C.D routes",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display VPNv4 NLRI specific information\n"
       "Display information about all VPNv4 NLRIs\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display routes learned from neighbor\n")
{
  union sockunion su;
  struct peer *peer;
  int ret;

  ret = str2sockunion (argv[0], &su);
  if (ret < 0)
    {
      vty_out (vty, "Malformed address: %s%s", argv[0], VTY_NEWLINE);
      return CMD_WARNING;
    }

  peer = peer_lookup (NULL, &su);
  if (! peer || ! peer->afc[AFI_IP][SAFI_MPLS_VPN])
    {
      vty_out (vty, "%% No such neighbor or address family%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  return bgp_show_mpls_vpn (vty, NULL, bgp_show_type_neighbor, &su, 0);
}

DEFUN (show_ip_bgp_vpnv4_rd_neighbor_routes,
       show_ip_bgp_vpnv4_rd_neighbor_routes_cmd,
       "show ip bgp vpnv4 rd ASN:nn_or_IP-address:nn neighbors A.B.C.D routes",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display VPNv4 NLRI specific information\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display routes learned from neighbor\n")
{
  int ret;
  union sockunion su;
  struct peer *peer;
  struct prefix_rd prd;

  ret = str2prefix_rd (argv[0], &prd);
  if (! ret)
    {
      vty_out (vty, "%% Malformed Route Distinguisher%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  ret = str2sockunion (argv[1], &su);
  if (ret < 0)
    {
      vty_out (vty, "Malformed address: %s%s", argv[0], VTY_NEWLINE);
      return CMD_WARNING;
    }

  peer = peer_lookup (NULL, &su);
  if (! peer || ! peer->afc[AFI_IP][SAFI_MPLS_VPN])
    {
      vty_out (vty, "%% No such neighbor or address family%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  return bgp_show_mpls_vpn (vty, &prd, bgp_show_type_neighbor, &su, 0);
}

DEFUN (show_ip_bgp_vpnv4_all_neighbor_advertised_routes,
       show_ip_bgp_vpnv4_all_neighbor_advertised_routes_cmd,
       "show ip bgp vpnv4 all neighbors A.B.C.D advertised-routes",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display VPNv4 NLRI specific information\n"
       "Display information about all VPNv4 NLRIs\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the routes advertised to a BGP neighbor\n")
{
  int ret;
  struct peer *peer;
  union sockunion su;

  ret = str2sockunion (argv[0], &su);
  if (ret < 0)
    {
      vty_out (vty, "%% Malformed address: %s%s", argv[0], VTY_NEWLINE);
      return CMD_WARNING;
    }
  peer = peer_lookup (NULL, &su);
  if (! peer || ! peer->afc[AFI_IP][SAFI_MPLS_VPN])
    {
      vty_out (vty, "%% No such neighbor or address family%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  return show_adj_route_vpn (vty, peer, NULL);
}

DEFUN (show_ip_bgp_vpnv4_rd_neighbor_advertised_routes,
       show_ip_bgp_vpnv4_rd_neighbor_advertised_routes_cmd,
       "show ip bgp vpnv4 rd ASN:nn_or_IP-address:nn neighbors A.B.C.D advertised-routes",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display VPNv4 NLRI specific information\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Display the routes advertised to a BGP neighbor\n")
{
  int ret;
  struct peer *peer;
  struct prefix_rd prd;
  union sockunion su;

  ret = str2sockunion (argv[1], &su);
  if (ret < 0)
    {
      vty_out (vty, "%% Malformed address: %s%s", argv[0], VTY_NEWLINE);
      return CMD_WARNING;
    }
  peer = peer_lookup (NULL, &su);
  if (! peer || ! peer->afc[AFI_IP][SAFI_MPLS_VPN])
    {
      vty_out (vty, "%% No such neighbor or address family%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  ret = str2prefix_rd (argv[0], &prd);
  if (! ret)
    {
      vty_out (vty, "%% Malformed Route Distinguisher%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  return show_adj_route_vpn (vty, peer, &prd);
}

// =======

/* `show ip bgp summary' commands. */
DEFUN (show_ip_bgp_summary,
       show_ip_bgp_summary_cmd,
       "show ip bgp summary",
       SHOW_STR
       IP_STR
       BGP_STR
       "Summary of BGP neighbor status\n")
{
  return bgp_show_summary_vty (vty, NULL, AFI_IP, SAFI_UNICAST);
}

DEFUN (show_ip_bgp_instance_summary,
       show_ip_bgp_instance_summary_cmd,
       "show ip bgp view WORD summary",
       SHOW_STR
       IP_STR
       BGP_STR
       "BGP view\n"
       "View name\n"
       "Summary of BGP neighbor status\n")
{
  return bgp_show_summary_vty (vty, argv[0], AFI_IP, SAFI_UNICAST);
}

DEFUN (show_ip_bgp_ipv4_summary,
       show_ip_bgp_ipv4_summary_cmd,
       "show ip bgp ipv4 (unicast|multicast) summary",
       SHOW_STR
       IP_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Summary of BGP neighbor status\n")
{
  if (strncmp (argv[0], "m", 1) == 0)
    return bgp_show_summary_vty (vty, NULL, AFI_IP, SAFI_MULTICAST);

  return bgp_show_summary_vty (vty, NULL, AFI_IP, SAFI_UNICAST);
}

ALIAS (show_ip_bgp_ipv4_summary,
       show_bgp_ipv4_safi_summary_cmd,
       "show bgp ipv4 (unicast|multicast) summary",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Summary of BGP neighbor status\n")

DEFUN (show_ip_bgp_instance_ipv4_summary,
       show_ip_bgp_instance_ipv4_summary_cmd,
       "show ip bgp view WORD ipv4 (unicast|multicast) summary",
       SHOW_STR
       IP_STR
       BGP_STR
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Summary of BGP neighbor status\n")
{
  if (strncmp (argv[1], "m", 1) == 0)
    return bgp_show_summary_vty (vty, argv[0], AFI_IP, SAFI_MULTICAST);
  else
    return bgp_show_summary_vty (vty, argv[0], AFI_IP, SAFI_UNICAST);
}

ALIAS (show_ip_bgp_instance_ipv4_summary,
       show_bgp_instance_ipv4_safi_summary_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) summary",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Summary of BGP neighbor status\n")

DEFUN (show_ip_bgp_vpnv4_all_summary,
       show_ip_bgp_vpnv4_all_summary_cmd,
       "show ip bgp vpnv4 all summary",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display VPNv4 NLRI specific information\n"
       "Display information about all VPNv4 NLRIs\n"
       "Summary of BGP neighbor status\n")
{
  return bgp_show_summary_vty (vty, NULL, AFI_IP, SAFI_MPLS_VPN);
}

DEFUN (show_ip_bgp_vpnv4_rd_summary,
       show_ip_bgp_vpnv4_rd_summary_cmd,
       "show ip bgp vpnv4 rd ASN:nn_or_IP-address:nn summary",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display VPNv4 NLRI specific information\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Summary of BGP neighbor status\n")
{
  int ret;
  struct prefix_rd prd;

  ret = str2prefix_rd (argv[0], &prd);
  if (! ret)
    {
      vty_out (vty, "%% Malformed Route Distinguisher%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  return bgp_show_summary_vty (vty, NULL, AFI_IP, SAFI_MPLS_VPN);
}

#ifdef HAVE_IPV6
DEFUN (show_bgp_summary,
       show_bgp_summary_cmd,
       "show bgp summary",
       SHOW_STR
       BGP_STR
       "Summary of BGP neighbor status\n")
{
  return bgp_show_summary_vty (vty, NULL, AFI_IP6, SAFI_UNICAST);
}

DEFUN (show_bgp_instance_summary,
       show_bgp_instance_summary_cmd,
       "show bgp view WORD summary",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "View name\n"
       "Summary of BGP neighbor status\n")
{
  return bgp_show_summary_vty (vty, argv[0], AFI_IP6, SAFI_UNICAST);
}

ALIAS (show_bgp_summary,
       show_bgp_ipv6_summary_cmd,
       "show bgp ipv6 summary",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Summary of BGP neighbor status\n")

ALIAS (show_bgp_instance_summary,
       show_bgp_instance_ipv6_summary_cmd,
       "show bgp view WORD ipv6 summary",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Summary of BGP neighbor status\n")

DEFUN (show_bgp_ipv6_safi_summary,
       show_bgp_ipv6_safi_summary_cmd,
       "show bgp ipv6 (unicast|multicast) summary",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Summary of BGP neighbor status\n")
{
  if (strncmp (argv[0], "m", 1) == 0)
    return bgp_show_summary_vty (vty, NULL, AFI_IP6, SAFI_MULTICAST);

  return bgp_show_summary_vty (vty, NULL, AFI_IP6, SAFI_UNICAST);
}

DEFUN (show_bgp_instance_ipv6_safi_summary,
       show_bgp_instance_ipv6_safi_summary_cmd,
       "show bgp view WORD ipv6 (unicast|multicast) summary",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Summary of BGP neighbor status\n")
{
  if (strncmp (argv[1], "m", 1) == 0)
    return bgp_show_summary_vty (vty, argv[0], AFI_IP6, SAFI_MULTICAST);

  return bgp_show_summary_vty (vty, argv[0], AFI_IP6, SAFI_UNICAST);
}

/* old command */
DEFUN (show_ipv6_bgp_summary,
       show_ipv6_bgp_summary_cmd,
       "show ipv6 bgp summary",
       SHOW_STR
       IPV6_STR
       BGP_STR
       "Summary of BGP neighbor status\n")
{
  return bgp_show_summary_vty (vty, NULL, AFI_IP6, SAFI_UNICAST);
}

/* old command */
DEFUN (show_ipv6_mbgp_summary,
       show_ipv6_mbgp_summary_cmd,
       "show ipv6 mbgp summary",
       SHOW_STR
       IPV6_STR
       MBGP_STR
       "Summary of BGP neighbor status\n")
{
  return bgp_show_summary_vty (vty, NULL, AFI_IP6, SAFI_MULTICAST);
}
#endif /* HAVE_IPV6 */

/* "show ip bgp neighbors" commands.  */
DEFUN (show_ip_bgp_neighbors,
       show_ip_bgp_neighbors_cmd,
       "show ip bgp neighbors",
       SHOW_STR
       IP_STR
       BGP_STR
       "Detailed information on TCP and BGP neighbor connections\n")
{
  return bgp_show_neighbor_vty (vty, NULL, show_all, NULL);
}

ALIAS (show_ip_bgp_neighbors,
       show_ip_bgp_ipv4_neighbors_cmd,
       "show ip bgp ipv4 (unicast|multicast) neighbors",
       SHOW_STR
       IP_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n")

ALIAS (show_ip_bgp_neighbors,
       show_ip_bgp_vpnv4_all_neighbors_cmd,
       "show ip bgp vpnv4 all neighbors",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display VPNv4 NLRI specific information\n"
       "Display information about all VPNv4 NLRIs\n"
       "Detailed information on TCP and BGP neighbor connections\n")

ALIAS (show_ip_bgp_neighbors,
       show_ip_bgp_vpnv4_rd_neighbors_cmd,
       "show ip bgp vpnv4 rd ASN:nn_or_IP-address:nn neighbors",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display VPNv4 NLRI specific information\n"
       "Display information for a route distinguisher\n"
       "VPN Route Distinguisher\n"
       "Detailed information on TCP and BGP neighbor connections\n")

ALIAS (show_ip_bgp_neighbors,
       show_bgp_neighbors_cmd,
       "show bgp neighbors",
       SHOW_STR
       BGP_STR
       "Detailed information on TCP and BGP neighbor connections\n")

ALIAS (show_ip_bgp_neighbors,
       show_bgp_ipv6_neighbors_cmd,
       "show bgp ipv6 neighbors",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Detailed information on TCP and BGP neighbor connections\n")

DEFUN (show_ip_bgp_neighbors_peer,
       show_ip_bgp_neighbors_peer_cmd,
       "show ip bgp neighbors (A.B.C.D|X:X::X:X)",
       SHOW_STR
       IP_STR
       BGP_STR
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n")
{
  return bgp_show_neighbor_vty (vty, NULL, show_peer, argv[argc - 1]);
}

ALIAS (show_ip_bgp_neighbors_peer,
       show_ip_bgp_ipv4_neighbors_peer_cmd,
       "show ip bgp ipv4 (unicast|multicast) neighbors (A.B.C.D|X:X::X:X)",
       SHOW_STR
       IP_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n")

ALIAS (show_ip_bgp_neighbors_peer,
       show_ip_bgp_vpnv4_all_neighbors_peer_cmd,
       "show ip bgp vpnv4 all neighbors A.B.C.D",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display VPNv4 NLRI specific information\n"
       "Display information about all VPNv4 NLRIs\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n")

ALIAS (show_ip_bgp_neighbors_peer,
       show_ip_bgp_vpnv4_rd_neighbors_peer_cmd,
       "show ip bgp vpnv4 rd ASN:nn_or_IP-address:nn neighbors A.B.C.D",
       SHOW_STR
       IP_STR
       BGP_STR
       "Display VPNv4 NLRI specific information\n"
       "Display information about all VPNv4 NLRIs\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n")

ALIAS (show_ip_bgp_neighbors_peer,
       show_bgp_neighbors_peer_cmd,
       "show bgp neighbors (A.B.C.D|X:X::X:X)",
       SHOW_STR
       BGP_STR
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n")

ALIAS (show_ip_bgp_neighbors_peer,
       show_bgp_ipv6_neighbors_peer_cmd,
       "show bgp ipv6 neighbors (A.B.C.D|X:X::X:X)",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n")

DEFUN (show_ip_bgp_instance_neighbors,
       show_ip_bgp_instance_neighbors_cmd,
       "show ip bgp view WORD neighbors",
       SHOW_STR
       IP_STR
       BGP_STR
       "BGP view\n"
       "View name\n"
       "Detailed information on TCP and BGP neighbor connections\n")
{
  return bgp_show_neighbor_vty (vty, argv[0], show_all, NULL);
}

ALIAS (show_ip_bgp_instance_neighbors,
       show_bgp_instance_neighbors_cmd,
       "show bgp view WORD neighbors",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "View name\n"
       "Detailed information on TCP and BGP neighbor connections\n")

ALIAS (show_ip_bgp_instance_neighbors,
       show_bgp_instance_ipv6_neighbors_cmd,
       "show bgp view WORD ipv6 neighbors",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Detailed information on TCP and BGP neighbor connections\n")

DEFUN (show_ip_bgp_instance_neighbors_peer,
       show_ip_bgp_instance_neighbors_peer_cmd,
       "show ip bgp view WORD neighbors (A.B.C.D|X:X::X:X)",
       SHOW_STR
       IP_STR
       BGP_STR
       "BGP view\n"
       "View name\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n")
{
  return bgp_show_neighbor_vty (vty, argv[0], show_peer, argv[1]);
}

ALIAS (show_ip_bgp_instance_neighbors_peer,
       show_bgp_instance_neighbors_peer_cmd,
       "show bgp view WORD neighbors (A.B.C.D|X:X::X:X)",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "View name\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n")

ALIAS (show_ip_bgp_instance_neighbors_peer,
       show_bgp_instance_ipv6_neighbors_peer_cmd,
       "show bgp view WORD ipv6 neighbors (A.B.C.D|X:X::X:X)",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Detailed information on TCP and BGP neighbor connections\n"
       "Neighbor to display information about\n"
       "Neighbor to display information about\n")

/* Show BGP's AS paths internal data.  There are both `show ip bgp
   paths' and `show ip mbgp paths'.  Those functions results are the
   same.*/
DEFUN (show_ip_bgp_paths,
       show_ip_bgp_paths_cmd,
       "show ip bgp paths",
       SHOW_STR
       IP_STR
       BGP_STR
       "Path information\n")
{
  vty_out (vty, "Address Refcnt Path%s", VTY_NEWLINE);
  aspath_print_all_vty (vty);
  return CMD_SUCCESS;
}

DEFUN (show_ip_bgp_ipv4_paths,
       show_ip_bgp_ipv4_paths_cmd,
       "show ip bgp ipv4 (unicast|multicast) paths",
       SHOW_STR
       IP_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Path information\n")
{
  vty_out (vty, "Address Refcnt Path\r\n");
  aspath_print_all_vty (vty);

  return CMD_SUCCESS;
}

/* 'show bgp rsclient' commands. */
DEFUN (show_ip_bgp_rsclient_summary,
       show_ip_bgp_rsclient_summary_cmd,
       "show ip bgp rsclient summary",
       SHOW_STR
       IP_STR
       BGP_STR
       "Information about Route Server Clients\n"
       "Summary of all Route Server Clients\n")
{
  return bgp_show_rsclient_summary_vty (vty, NULL, AFI_IP, SAFI_UNICAST);
}

DEFUN (show_ip_bgp_instance_rsclient_summary,
       show_ip_bgp_instance_rsclient_summary_cmd,
       "show ip bgp view WORD rsclient summary",
       SHOW_STR
       IP_STR
       BGP_STR
       "BGP view\n"
       "View name\n"
       "Information about Route Server Clients\n"
       "Summary of all Route Server Clients\n")
{
  return bgp_show_rsclient_summary_vty (vty, argv[0], AFI_IP, SAFI_UNICAST);
}

DEFUN (show_ip_bgp_ipv4_rsclient_summary,
      show_ip_bgp_ipv4_rsclient_summary_cmd,
      "show ip bgp ipv4 (unicast|multicast) rsclient summary",
       SHOW_STR
       IP_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Information about Route Server Clients\n"
       "Summary of all Route Server Clients\n")
{
  if (strncmp (argv[0], "m", 1) == 0)
    return bgp_show_rsclient_summary_vty (vty, NULL, AFI_IP, SAFI_MULTICAST);

  return bgp_show_rsclient_summary_vty (vty, NULL, AFI_IP, SAFI_UNICAST);
}

DEFUN (show_ip_bgp_instance_ipv4_rsclient_summary,
      show_ip_bgp_instance_ipv4_rsclient_summary_cmd,
      "show ip bgp view WORD ipv4 (unicast|multicast) rsclient summary",
       SHOW_STR
       IP_STR
       BGP_STR
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Information about Route Server Clients\n"
       "Summary of all Route Server Clients\n")
{
  if (strncmp (argv[1], "m", 1) == 0)
    return bgp_show_rsclient_summary_vty (vty, argv[0], AFI_IP, SAFI_MULTICAST);

  return bgp_show_rsclient_summary_vty (vty, argv[0], AFI_IP, SAFI_UNICAST);
}

DEFUN (show_bgp_instance_ipv4_safi_rsclient_summary,
       show_bgp_instance_ipv4_safi_rsclient_summary_cmd,
       "show bgp view WORD ipv4 (unicast|multicast) rsclient summary",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Information about Route Server Clients\n"
       "Summary of all Route Server Clients\n")
{
  safi_t safi;

  if (argc == 2) {
    safi = (strncmp (argv[1], "m", 1) == 0) ? SAFI_MULTICAST : SAFI_UNICAST;
    return bgp_show_rsclient_summary_vty (vty, argv[0], AFI_IP, safi);
  } else {
    safi = (strncmp (argv[0], "m", 1) == 0) ? SAFI_MULTICAST : SAFI_UNICAST;
    return bgp_show_rsclient_summary_vty (vty, NULL, AFI_IP, safi);
  }
}

ALIAS (show_bgp_instance_ipv4_safi_rsclient_summary,
       show_bgp_ipv4_safi_rsclient_summary_cmd,
       "show bgp ipv4 (unicast|multicast) rsclient summary",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Information about Route Server Clients\n"
       "Summary of all Route Server Clients\n")

#ifdef HAVE_IPV6
DEFUN (show_bgp_rsclient_summary,
       show_bgp_rsclient_summary_cmd,
       "show bgp rsclient summary",
       SHOW_STR
       BGP_STR
       "Information about Route Server Clients\n"
       "Summary of all Route Server Clients\n")
{
  return bgp_show_rsclient_summary_vty (vty, NULL, AFI_IP6, SAFI_UNICAST);
}

DEFUN (show_bgp_instance_rsclient_summary,
       show_bgp_instance_rsclient_summary_cmd,
       "show bgp view WORD rsclient summary",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "View name\n"
       "Information about Route Server Clients\n"
       "Summary of all Route Server Clients\n")
{
  return bgp_show_rsclient_summary_vty (vty, argv[0], AFI_IP6, SAFI_UNICAST);
}

ALIAS (show_bgp_rsclient_summary,
      show_bgp_ipv6_rsclient_summary_cmd,
      "show bgp ipv6 rsclient summary",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Information about Route Server Clients\n"
       "Summary of all Route Server Clients\n")

ALIAS (show_bgp_instance_rsclient_summary,
      show_bgp_instance_ipv6_rsclient_summary_cmd,
       "show bgp view WORD ipv6 rsclient summary",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Information about Route Server Clients\n"
       "Summary of all Route Server Clients\n")

DEFUN (show_bgp_instance_ipv6_safi_rsclient_summary,
       show_bgp_instance_ipv6_safi_rsclient_summary_cmd,
       "show bgp view WORD ipv6 (unicast|multicast) rsclient summary",
       SHOW_STR
       BGP_STR
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Information about Route Server Clients\n"
       "Summary of all Route Server Clients\n")
{
  safi_t safi;

  if (argc == 2) {
    safi = (strncmp (argv[1], "m", 1) == 0) ? SAFI_MULTICAST : SAFI_UNICAST;
    return bgp_show_rsclient_summary_vty (vty, argv[0], AFI_IP6, safi);
  } else {
    safi = (strncmp (argv[0], "m", 1) == 0) ? SAFI_MULTICAST : SAFI_UNICAST;
    return bgp_show_rsclient_summary_vty (vty, NULL, AFI_IP6, safi);
  }
}

ALIAS (show_bgp_instance_ipv6_safi_rsclient_summary,
       show_bgp_ipv6_safi_rsclient_summary_cmd,
       "show bgp ipv6 (unicast|multicast) rsclient summary",
       SHOW_STR
       BGP_STR
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Information about Route Server Clients\n"
       "Summary of all Route Server Clients\n")

#endif /* HAVE IPV6 */

void
bgp_vty_show_init (void)
{
  install_element (VIEW_NODE, &show_ip_bgp_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_ipv4_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_route_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_ipv4_route_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_route_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_vpnv4_all_route_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_vpnv4_rd_route_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_prefix_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_ipv4_prefix_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_prefix_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_vpnv4_all_prefix_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_vpnv4_rd_prefix_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_view_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_view_route_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_view_prefix_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_regexp_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_ipv4_regexp_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_prefix_list_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_ipv4_prefix_list_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_filter_list_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_ipv4_filter_list_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_route_map_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_ipv4_route_map_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_cidr_only_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_ipv4_cidr_only_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_community_all_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_ipv4_community_all_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_community_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_community2_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_community3_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_community4_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_ipv4_community_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_ipv4_community2_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_ipv4_community3_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_ipv4_community4_cmd);
  install_element (VIEW_NODE, &show_bgp_view_afi_safi_community_all_cmd);
  install_element (VIEW_NODE, &show_bgp_view_afi_safi_community_cmd);
  install_element (VIEW_NODE, &show_bgp_view_afi_safi_community2_cmd);
  install_element (VIEW_NODE, &show_bgp_view_afi_safi_community3_cmd);
  install_element (VIEW_NODE, &show_bgp_view_afi_safi_community4_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_community_exact_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_community2_exact_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_community3_exact_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_community4_exact_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_ipv4_community_exact_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_ipv4_community2_exact_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_ipv4_community3_exact_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_ipv4_community4_exact_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_community_list_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_ipv4_community_list_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_community_list_exact_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_ipv4_community_list_exact_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_prefix_longer_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_ipv4_prefix_longer_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_neighbor_advertised_route_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_ipv4_neighbor_advertised_route_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_neighbor_received_routes_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_ipv4_neighbor_received_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_view_afi_safi_neighbor_adv_recd_routes_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_neighbor_routes_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_ipv4_neighbor_routes_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_neighbor_received_prefix_filter_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_ipv4_neighbor_received_prefix_filter_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_dampened_paths_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_flap_statistics_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_flap_address_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_flap_prefix_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_flap_cidr_only_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_flap_regexp_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_flap_filter_list_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_flap_prefix_list_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_flap_prefix_longer_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_flap_route_map_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_neighbor_flap_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_neighbor_damp_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_rsclient_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_rsclient_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_rsclient_route_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_rsclient_route_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_rsclient_prefix_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_rsclient_prefix_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_view_neighbor_advertised_route_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_view_neighbor_received_routes_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_view_rsclient_cmd);
  install_element (VIEW_NODE, &show_bgp_view_ipv4_safi_rsclient_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_view_rsclient_route_cmd);
  install_element (VIEW_NODE, &show_bgp_view_ipv4_safi_rsclient_route_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_view_rsclient_prefix_cmd);
  install_element (VIEW_NODE, &show_bgp_view_ipv4_safi_rsclient_prefix_cmd);

  /* Restricted node: VIEW_NODE - (set of dangerous commands) */
  install_element (RESTRICTED_NODE, &show_ip_bgp_route_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_ipv4_route_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_route_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_vpnv4_rd_route_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_prefix_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_ipv4_prefix_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_prefix_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_vpnv4_all_prefix_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_vpnv4_rd_prefix_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_view_route_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_view_prefix_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_community_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_community2_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_community3_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_community4_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_ipv4_community_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_ipv4_community2_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_ipv4_community3_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_ipv4_community4_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_afi_safi_community_all_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_afi_safi_community_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_afi_safi_community2_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_afi_safi_community3_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_afi_safi_community4_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_community_exact_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_community2_exact_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_community3_exact_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_community4_exact_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_ipv4_community_exact_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_ipv4_community2_exact_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_ipv4_community3_exact_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_ipv4_community4_exact_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_rsclient_route_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_rsclient_route_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_rsclient_prefix_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_rsclient_prefix_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_view_rsclient_route_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_ipv4_safi_rsclient_route_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_view_rsclient_prefix_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_ipv4_safi_rsclient_prefix_cmd);

  install_element (ENABLE_NODE, &show_ip_bgp_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_ipv4_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_route_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_ipv4_route_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_route_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_vpnv4_all_route_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_vpnv4_rd_route_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_prefix_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_ipv4_prefix_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_prefix_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_vpnv4_all_prefix_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_vpnv4_rd_prefix_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_view_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_view_route_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_view_prefix_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_regexp_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_ipv4_regexp_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_prefix_list_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_ipv4_prefix_list_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_filter_list_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_ipv4_filter_list_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_route_map_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_ipv4_route_map_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_cidr_only_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_ipv4_cidr_only_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_community_all_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_ipv4_community_all_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_community_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_community2_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_community3_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_community4_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_ipv4_community_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_ipv4_community2_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_ipv4_community3_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_ipv4_community4_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_afi_safi_community_all_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_afi_safi_community_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_afi_safi_community2_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_afi_safi_community3_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_afi_safi_community4_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_community_exact_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_community2_exact_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_community3_exact_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_community4_exact_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_ipv4_community_exact_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_ipv4_community2_exact_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_ipv4_community3_exact_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_ipv4_community4_exact_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_community_list_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_ipv4_community_list_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_community_list_exact_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_ipv4_community_list_exact_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_prefix_longer_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_ipv4_prefix_longer_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_neighbor_advertised_route_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_ipv4_neighbor_advertised_route_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_neighbor_received_routes_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_ipv4_neighbor_received_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_afi_safi_neighbor_adv_recd_routes_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_neighbor_routes_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_ipv4_neighbor_routes_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_neighbor_received_prefix_filter_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_ipv4_neighbor_received_prefix_filter_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_dampened_paths_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_flap_statistics_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_flap_address_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_flap_prefix_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_flap_cidr_only_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_flap_regexp_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_flap_filter_list_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_flap_prefix_list_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_flap_prefix_longer_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_flap_route_map_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_neighbor_flap_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_neighbor_damp_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_rsclient_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_rsclient_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_rsclient_route_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_rsclient_route_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_rsclient_prefix_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_rsclient_prefix_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_view_neighbor_advertised_route_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_view_neighbor_received_routes_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_view_rsclient_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_ipv4_safi_rsclient_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_view_rsclient_route_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_ipv4_safi_rsclient_route_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_view_rsclient_prefix_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_ipv4_safi_rsclient_prefix_cmd);

  /* prefix count */
  install_element (ENABLE_NODE, &show_ip_bgp_neighbor_prefix_counts_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_ipv4_neighbor_prefix_counts_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_vpnv4_neighbor_prefix_counts_cmd);
#ifdef HAVE_IPV6
  install_element (ENABLE_NODE, &show_bgp_ipv6_neighbor_prefix_counts_cmd);

  install_element (VIEW_NODE, &show_bgp_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_safi_cmd);
  install_element (VIEW_NODE, &show_bgp_route_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_route_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_safi_route_cmd);
  install_element (VIEW_NODE, &show_bgp_prefix_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_prefix_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_safi_prefix_cmd);
  install_element (VIEW_NODE, &show_bgp_regexp_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_regexp_cmd);
  install_element (VIEW_NODE, &show_bgp_prefix_list_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_prefix_list_cmd);
  install_element (VIEW_NODE, &show_bgp_filter_list_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_filter_list_cmd);
  install_element (VIEW_NODE, &show_bgp_route_map_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_route_map_cmd);
  install_element (VIEW_NODE, &show_bgp_community_all_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_community_all_cmd);
  install_element (VIEW_NODE, &show_bgp_community_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_community_cmd);
  install_element (VIEW_NODE, &show_bgp_community2_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_community2_cmd);
  install_element (VIEW_NODE, &show_bgp_community3_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_community3_cmd);
  install_element (VIEW_NODE, &show_bgp_community4_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_community4_cmd);
  install_element (VIEW_NODE, &show_bgp_community_exact_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_community_exact_cmd);
  install_element (VIEW_NODE, &show_bgp_community2_exact_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_community2_exact_cmd);
  install_element (VIEW_NODE, &show_bgp_community3_exact_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_community3_exact_cmd);
  install_element (VIEW_NODE, &show_bgp_community4_exact_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_community4_exact_cmd);
  install_element (VIEW_NODE, &show_bgp_community_list_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_community_list_cmd);
  install_element (VIEW_NODE, &show_bgp_community_list_exact_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_community_list_exact_cmd);
  install_element (VIEW_NODE, &show_bgp_prefix_longer_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_prefix_longer_cmd);
  install_element (VIEW_NODE, &show_bgp_neighbor_advertised_route_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_neighbor_advertised_route_cmd);
  install_element (VIEW_NODE, &show_bgp_neighbor_received_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_neighbor_received_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_neighbor_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_neighbor_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_neighbor_received_prefix_filter_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_neighbor_received_prefix_filter_cmd);
  install_element (VIEW_NODE, &show_bgp_neighbor_flap_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_neighbor_flap_cmd);
  install_element (VIEW_NODE, &show_bgp_neighbor_damp_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_neighbor_damp_cmd);
  install_element (VIEW_NODE, &show_bgp_rsclient_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_safi_rsclient_cmd);
  install_element (VIEW_NODE, &show_bgp_rsclient_route_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_safi_rsclient_route_cmd);
  install_element (VIEW_NODE, &show_bgp_rsclient_prefix_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_safi_rsclient_prefix_cmd);
  install_element (VIEW_NODE, &show_bgp_view_cmd);
  install_element (VIEW_NODE, &show_bgp_view_ipv6_cmd);
  install_element (VIEW_NODE, &show_bgp_view_route_cmd);
  install_element (VIEW_NODE, &show_bgp_view_ipv6_route_cmd);
  install_element (VIEW_NODE, &show_bgp_view_prefix_cmd);
  install_element (VIEW_NODE, &show_bgp_view_ipv6_prefix_cmd);
  install_element (VIEW_NODE, &show_bgp_view_neighbor_advertised_route_cmd);
  install_element (VIEW_NODE, &show_bgp_view_ipv6_neighbor_advertised_route_cmd);
  install_element (VIEW_NODE, &show_bgp_view_neighbor_received_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_view_ipv6_neighbor_received_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_view_neighbor_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_view_ipv6_neighbor_routes_cmd);
  install_element (VIEW_NODE, &show_bgp_view_neighbor_received_prefix_filter_cmd);
  install_element (VIEW_NODE, &show_bgp_view_ipv6_neighbor_received_prefix_filter_cmd);
  install_element (VIEW_NODE, &show_bgp_view_neighbor_flap_cmd);
  install_element (VIEW_NODE, &show_bgp_view_ipv6_neighbor_flap_cmd);
  install_element (VIEW_NODE, &show_bgp_view_neighbor_damp_cmd);
  install_element (VIEW_NODE, &show_bgp_view_ipv6_neighbor_damp_cmd);
  install_element (VIEW_NODE, &show_bgp_view_rsclient_cmd);
  install_element (VIEW_NODE, &show_bgp_view_ipv6_safi_rsclient_cmd);
  install_element (VIEW_NODE, &show_bgp_view_rsclient_route_cmd);
  install_element (VIEW_NODE, &show_bgp_view_ipv6_safi_rsclient_route_cmd);
  install_element (VIEW_NODE, &show_bgp_view_rsclient_prefix_cmd);
  install_element (VIEW_NODE, &show_bgp_view_ipv6_safi_rsclient_prefix_cmd);

  /* Restricted:
   * VIEW_NODE - (set of dangerous commands) - (commands dependent on prev)
   */
  install_element (RESTRICTED_NODE, &show_bgp_route_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_route_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_safi_route_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_prefix_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_prefix_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_safi_prefix_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_community_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_community_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_community2_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_community2_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_community3_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_community3_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_community4_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_community4_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_community_exact_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_community_exact_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_community2_exact_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_community2_exact_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_community3_exact_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_community3_exact_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_community4_exact_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_community4_exact_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_rsclient_route_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_safi_rsclient_route_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_rsclient_prefix_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_safi_rsclient_prefix_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_route_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_ipv6_route_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_prefix_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_ipv6_prefix_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_neighbor_received_prefix_filter_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_ipv6_neighbor_received_prefix_filter_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_rsclient_route_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_ipv6_safi_rsclient_route_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_rsclient_prefix_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_view_ipv6_safi_rsclient_prefix_cmd);

  install_element (ENABLE_NODE, &show_bgp_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_safi_cmd);
  install_element (ENABLE_NODE, &show_bgp_route_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_route_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_safi_route_cmd);
  install_element (ENABLE_NODE, &show_bgp_prefix_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_prefix_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_safi_prefix_cmd);
  install_element (ENABLE_NODE, &show_bgp_regexp_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_regexp_cmd);
  install_element (ENABLE_NODE, &show_bgp_prefix_list_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_prefix_list_cmd);
  install_element (ENABLE_NODE, &show_bgp_filter_list_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_filter_list_cmd);
  install_element (ENABLE_NODE, &show_bgp_route_map_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_route_map_cmd);
  install_element (ENABLE_NODE, &show_bgp_community_all_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_community_all_cmd);
  install_element (ENABLE_NODE, &show_bgp_community_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_community_cmd);
  install_element (ENABLE_NODE, &show_bgp_community2_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_community2_cmd);
  install_element (ENABLE_NODE, &show_bgp_community3_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_community3_cmd);
  install_element (ENABLE_NODE, &show_bgp_community4_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_community4_cmd);
  install_element (ENABLE_NODE, &show_bgp_community_exact_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_community_exact_cmd);
  install_element (ENABLE_NODE, &show_bgp_community2_exact_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_community2_exact_cmd);
  install_element (ENABLE_NODE, &show_bgp_community3_exact_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_community3_exact_cmd);
  install_element (ENABLE_NODE, &show_bgp_community4_exact_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_community4_exact_cmd);
  install_element (ENABLE_NODE, &show_bgp_community_list_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_community_list_cmd);
  install_element (ENABLE_NODE, &show_bgp_community_list_exact_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_community_list_exact_cmd);
  install_element (ENABLE_NODE, &show_bgp_prefix_longer_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_prefix_longer_cmd);
  install_element (ENABLE_NODE, &show_bgp_neighbor_advertised_route_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_neighbor_advertised_route_cmd);
  install_element (ENABLE_NODE, &show_bgp_neighbor_received_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_neighbor_received_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_neighbor_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_neighbor_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_neighbor_received_prefix_filter_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_neighbor_received_prefix_filter_cmd);
  install_element (ENABLE_NODE, &show_bgp_neighbor_flap_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_neighbor_flap_cmd);
  install_element (ENABLE_NODE, &show_bgp_neighbor_damp_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_neighbor_damp_cmd);
  install_element (ENABLE_NODE, &show_bgp_rsclient_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_safi_rsclient_cmd);
  install_element (ENABLE_NODE, &show_bgp_rsclient_route_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_safi_rsclient_route_cmd);
  install_element (ENABLE_NODE, &show_bgp_rsclient_prefix_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_safi_rsclient_prefix_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_ipv6_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_route_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_ipv6_route_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_prefix_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_ipv6_prefix_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_neighbor_advertised_route_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_ipv6_neighbor_advertised_route_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_neighbor_received_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_ipv6_neighbor_received_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_neighbor_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_ipv6_neighbor_routes_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_neighbor_received_prefix_filter_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_ipv6_neighbor_received_prefix_filter_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_neighbor_flap_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_ipv6_neighbor_flap_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_neighbor_damp_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_ipv6_neighbor_damp_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_rsclient_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_ipv6_safi_rsclient_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_rsclient_route_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_ipv6_safi_rsclient_route_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_rsclient_prefix_cmd);
  install_element (ENABLE_NODE, &show_bgp_view_ipv6_safi_rsclient_prefix_cmd);

  /* Statistics */
  install_element (ENABLE_NODE, &show_bgp_statistics_cmd);
  install_element (ENABLE_NODE, &show_bgp_statistics_vpnv4_cmd);
  install_element (ENABLE_NODE, &show_bgp_statistics_view_cmd);
  install_element (ENABLE_NODE, &show_bgp_statistics_view_vpnv4_cmd);

  /* old command */
  install_element (VIEW_NODE, &show_ipv6_bgp_cmd);
  install_element (VIEW_NODE, &show_ipv6_bgp_route_cmd);
  install_element (VIEW_NODE, &show_ipv6_bgp_prefix_cmd);
  install_element (VIEW_NODE, &show_ipv6_bgp_regexp_cmd);
  install_element (VIEW_NODE, &show_ipv6_bgp_prefix_list_cmd);
  install_element (VIEW_NODE, &show_ipv6_bgp_filter_list_cmd);
  install_element (VIEW_NODE, &show_ipv6_bgp_community_all_cmd);
  install_element (VIEW_NODE, &show_ipv6_bgp_community_cmd);
  install_element (VIEW_NODE, &show_ipv6_bgp_community2_cmd);
  install_element (VIEW_NODE, &show_ipv6_bgp_community3_cmd);
  install_element (VIEW_NODE, &show_ipv6_bgp_community4_cmd);
  install_element (VIEW_NODE, &show_ipv6_bgp_community_exact_cmd);
  install_element (VIEW_NODE, &show_ipv6_bgp_community2_exact_cmd);
  install_element (VIEW_NODE, &show_ipv6_bgp_community3_exact_cmd);
  install_element (VIEW_NODE, &show_ipv6_bgp_community4_exact_cmd);
  install_element (VIEW_NODE, &show_ipv6_bgp_community_list_cmd);
  install_element (VIEW_NODE, &show_ipv6_bgp_community_list_exact_cmd);
  install_element (VIEW_NODE, &show_ipv6_bgp_prefix_longer_cmd);
  install_element (VIEW_NODE, &show_ipv6_mbgp_cmd);
  install_element (VIEW_NODE, &show_ipv6_mbgp_route_cmd);
  install_element (VIEW_NODE, &show_ipv6_mbgp_prefix_cmd);
  install_element (VIEW_NODE, &show_ipv6_mbgp_regexp_cmd);
  install_element (VIEW_NODE, &show_ipv6_mbgp_prefix_list_cmd);
  install_element (VIEW_NODE, &show_ipv6_mbgp_filter_list_cmd);
  install_element (VIEW_NODE, &show_ipv6_mbgp_community_all_cmd);
  install_element (VIEW_NODE, &show_ipv6_mbgp_community_cmd);
  install_element (VIEW_NODE, &show_ipv6_mbgp_community2_cmd);
  install_element (VIEW_NODE, &show_ipv6_mbgp_community3_cmd);
  install_element (VIEW_NODE, &show_ipv6_mbgp_community4_cmd);
  install_element (VIEW_NODE, &show_ipv6_mbgp_community_exact_cmd);
  install_element (VIEW_NODE, &show_ipv6_mbgp_community2_exact_cmd);
  install_element (VIEW_NODE, &show_ipv6_mbgp_community3_exact_cmd);
  install_element (VIEW_NODE, &show_ipv6_mbgp_community4_exact_cmd);
  install_element (VIEW_NODE, &show_ipv6_mbgp_community_list_cmd);
  install_element (VIEW_NODE, &show_ipv6_mbgp_community_list_exact_cmd);
  install_element (VIEW_NODE, &show_ipv6_mbgp_prefix_longer_cmd);

  /* old command */
  install_element (ENABLE_NODE, &show_ipv6_bgp_cmd);
  install_element (ENABLE_NODE, &show_ipv6_bgp_route_cmd);
  install_element (ENABLE_NODE, &show_ipv6_bgp_prefix_cmd);
  install_element (ENABLE_NODE, &show_ipv6_bgp_regexp_cmd);
  install_element (ENABLE_NODE, &show_ipv6_bgp_prefix_list_cmd);
  install_element (ENABLE_NODE, &show_ipv6_bgp_filter_list_cmd);
  install_element (ENABLE_NODE, &show_ipv6_bgp_community_all_cmd);
  install_element (ENABLE_NODE, &show_ipv6_bgp_community_cmd);
  install_element (ENABLE_NODE, &show_ipv6_bgp_community2_cmd);
  install_element (ENABLE_NODE, &show_ipv6_bgp_community3_cmd);
  install_element (ENABLE_NODE, &show_ipv6_bgp_community4_cmd);
  install_element (ENABLE_NODE, &show_ipv6_bgp_community_exact_cmd);
  install_element (ENABLE_NODE, &show_ipv6_bgp_community2_exact_cmd);
  install_element (ENABLE_NODE, &show_ipv6_bgp_community3_exact_cmd);
  install_element (ENABLE_NODE, &show_ipv6_bgp_community4_exact_cmd);
  install_element (ENABLE_NODE, &show_ipv6_bgp_community_list_cmd);
  install_element (ENABLE_NODE, &show_ipv6_bgp_community_list_exact_cmd);
  install_element (ENABLE_NODE, &show_ipv6_bgp_prefix_longer_cmd);
  install_element (ENABLE_NODE, &show_ipv6_mbgp_cmd);
  install_element (ENABLE_NODE, &show_ipv6_mbgp_route_cmd);
  install_element (ENABLE_NODE, &show_ipv6_mbgp_prefix_cmd);
  install_element (ENABLE_NODE, &show_ipv6_mbgp_regexp_cmd);
  install_element (ENABLE_NODE, &show_ipv6_mbgp_prefix_list_cmd);
  install_element (ENABLE_NODE, &show_ipv6_mbgp_filter_list_cmd);
  install_element (ENABLE_NODE, &show_ipv6_mbgp_community_all_cmd);
  install_element (ENABLE_NODE, &show_ipv6_mbgp_community_cmd);
  install_element (ENABLE_NODE, &show_ipv6_mbgp_community2_cmd);
  install_element (ENABLE_NODE, &show_ipv6_mbgp_community3_cmd);
  install_element (ENABLE_NODE, &show_ipv6_mbgp_community4_cmd);
  install_element (ENABLE_NODE, &show_ipv6_mbgp_community_exact_cmd);
  install_element (ENABLE_NODE, &show_ipv6_mbgp_community2_exact_cmd);
  install_element (ENABLE_NODE, &show_ipv6_mbgp_community3_exact_cmd);
  install_element (ENABLE_NODE, &show_ipv6_mbgp_community4_exact_cmd);
  install_element (ENABLE_NODE, &show_ipv6_mbgp_community_list_cmd);
  install_element (ENABLE_NODE, &show_ipv6_mbgp_community_list_exact_cmd);
  install_element (ENABLE_NODE, &show_ipv6_mbgp_prefix_longer_cmd);

  /* old command */
  install_element (VIEW_NODE, &ipv6_bgp_neighbor_advertised_route_cmd);
  install_element (ENABLE_NODE, &ipv6_bgp_neighbor_advertised_route_cmd);
  install_element (VIEW_NODE, &ipv6_mbgp_neighbor_advertised_route_cmd);
  install_element (ENABLE_NODE, &ipv6_mbgp_neighbor_advertised_route_cmd);

  /* old command */
  install_element (VIEW_NODE, &ipv6_bgp_neighbor_received_routes_cmd);
  install_element (ENABLE_NODE, &ipv6_bgp_neighbor_received_routes_cmd);
  install_element (VIEW_NODE, &ipv6_mbgp_neighbor_received_routes_cmd);
  install_element (ENABLE_NODE, &ipv6_mbgp_neighbor_received_routes_cmd);

  /* old command */
  install_element (VIEW_NODE, &ipv6_bgp_neighbor_routes_cmd);
  install_element (ENABLE_NODE, &ipv6_bgp_neighbor_routes_cmd);
  install_element (VIEW_NODE, &ipv6_mbgp_neighbor_routes_cmd);
  install_element (ENABLE_NODE, &ipv6_mbgp_neighbor_routes_cmd);
#endif /* HAVE_IPV6 */

  install_element (VIEW_NODE, &show_ip_bgp_vpnv4_all_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_vpnv4_rd_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_vpnv4_all_tags_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_vpnv4_rd_tags_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_vpnv4_all_neighbor_routes_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_vpnv4_rd_neighbor_routes_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_vpnv4_all_neighbor_advertised_routes_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_vpnv4_rd_neighbor_advertised_routes_cmd);

  install_element (ENABLE_NODE, &show_ip_bgp_vpnv4_all_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_vpnv4_rd_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_vpnv4_all_tags_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_vpnv4_rd_tags_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_vpnv4_all_neighbor_routes_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_vpnv4_rd_neighbor_routes_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_vpnv4_all_neighbor_advertised_routes_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_vpnv4_rd_neighbor_advertised_routes_cmd);

  // ===

  /* "show ip bgp summary" commands. */
  install_element (VIEW_NODE, &show_ip_bgp_summary_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_instance_summary_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_ipv4_summary_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_summary_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_instance_ipv4_summary_cmd);
  install_element (VIEW_NODE, &show_bgp_instance_ipv4_safi_summary_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_vpnv4_all_summary_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_vpnv4_rd_summary_cmd);
#ifdef HAVE_IPV6
  install_element (VIEW_NODE, &show_bgp_summary_cmd);
  install_element (VIEW_NODE, &show_bgp_instance_summary_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_summary_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_safi_summary_cmd);
  install_element (VIEW_NODE, &show_bgp_instance_ipv6_summary_cmd);
  install_element (VIEW_NODE, &show_bgp_instance_ipv6_safi_summary_cmd);
#endif /* HAVE_IPV6 */
  install_element (RESTRICTED_NODE, &show_ip_bgp_summary_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_instance_summary_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_ipv4_summary_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_summary_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_instance_ipv4_summary_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_instance_ipv4_safi_summary_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_vpnv4_all_summary_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_vpnv4_rd_summary_cmd);
#ifdef HAVE_IPV6
  install_element (RESTRICTED_NODE, &show_bgp_summary_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_instance_summary_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_summary_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_safi_summary_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_instance_ipv6_summary_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_instance_ipv6_safi_summary_cmd);
#endif /* HAVE_IPV6 */
  install_element (ENABLE_NODE, &show_ip_bgp_summary_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_instance_summary_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_ipv4_summary_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_summary_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_instance_ipv4_summary_cmd);
  install_element (ENABLE_NODE, &show_bgp_instance_ipv4_safi_summary_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_vpnv4_all_summary_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_vpnv4_rd_summary_cmd);
#ifdef HAVE_IPV6
  install_element (ENABLE_NODE, &show_bgp_summary_cmd);
  install_element (ENABLE_NODE, &show_bgp_instance_summary_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_summary_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_safi_summary_cmd);
  install_element (ENABLE_NODE, &show_bgp_instance_ipv6_summary_cmd);
  install_element (ENABLE_NODE, &show_bgp_instance_ipv6_safi_summary_cmd);
#endif /* HAVE_IPV6 */

  /* "show ip bgp neighbors" commands. */
  install_element (VIEW_NODE, &show_ip_bgp_neighbors_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_ipv4_neighbors_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_neighbors_peer_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_ipv4_neighbors_peer_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_vpnv4_all_neighbors_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_vpnv4_rd_neighbors_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_vpnv4_all_neighbors_peer_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_vpnv4_rd_neighbors_peer_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_instance_neighbors_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_instance_neighbors_peer_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_neighbors_peer_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_ipv4_neighbors_peer_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_vpnv4_all_neighbors_peer_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_vpnv4_rd_neighbors_peer_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_instance_neighbors_peer_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_neighbors_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_ipv4_neighbors_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_neighbors_peer_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_ipv4_neighbors_peer_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_vpnv4_all_neighbors_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_vpnv4_rd_neighbors_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_vpnv4_all_neighbors_peer_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_vpnv4_rd_neighbors_peer_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_instance_neighbors_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_instance_neighbors_peer_cmd);

#ifdef HAVE_IPV6
  install_element (VIEW_NODE, &show_bgp_neighbors_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_neighbors_cmd);
  install_element (VIEW_NODE, &show_bgp_neighbors_peer_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_neighbors_peer_cmd);
  install_element (VIEW_NODE, &show_bgp_instance_neighbors_cmd);
  install_element (VIEW_NODE, &show_bgp_instance_ipv6_neighbors_cmd);
  install_element (VIEW_NODE, &show_bgp_instance_neighbors_peer_cmd);
  install_element (VIEW_NODE, &show_bgp_instance_ipv6_neighbors_peer_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_neighbors_peer_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_neighbors_peer_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_instance_neighbors_peer_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_instance_ipv6_neighbors_peer_cmd);
  install_element (ENABLE_NODE, &show_bgp_neighbors_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_neighbors_cmd);
  install_element (ENABLE_NODE, &show_bgp_neighbors_peer_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_neighbors_peer_cmd);
  install_element (ENABLE_NODE, &show_bgp_instance_neighbors_cmd);
  install_element (ENABLE_NODE, &show_bgp_instance_ipv6_neighbors_cmd);
  install_element (ENABLE_NODE, &show_bgp_instance_neighbors_peer_cmd);
  install_element (ENABLE_NODE, &show_bgp_instance_ipv6_neighbors_peer_cmd);

  /* Old commands.  */
  install_element (VIEW_NODE, &show_ipv6_bgp_summary_cmd);
  install_element (VIEW_NODE, &show_ipv6_mbgp_summary_cmd);
  install_element (ENABLE_NODE, &show_ipv6_bgp_summary_cmd);
  install_element (ENABLE_NODE, &show_ipv6_mbgp_summary_cmd);
#endif /* HAVE_IPV6 */

  /* "show ip bgp rsclient" commands. */
  install_element (VIEW_NODE, &show_ip_bgp_rsclient_summary_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_instance_rsclient_summary_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_ipv4_rsclient_summary_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_instance_ipv4_rsclient_summary_cmd);
  install_element (VIEW_NODE, &show_bgp_instance_ipv4_safi_rsclient_summary_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv4_safi_rsclient_summary_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_rsclient_summary_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_instance_rsclient_summary_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_ipv4_rsclient_summary_cmd);
  install_element (RESTRICTED_NODE, &show_ip_bgp_instance_ipv4_rsclient_summary_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_instance_ipv4_safi_rsclient_summary_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv4_safi_rsclient_summary_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_rsclient_summary_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_instance_rsclient_summary_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_ipv4_rsclient_summary_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_instance_ipv4_rsclient_summary_cmd);
  install_element (ENABLE_NODE, &show_bgp_instance_ipv4_safi_rsclient_summary_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv4_safi_rsclient_summary_cmd);

#ifdef HAVE_IPV6
  install_element (VIEW_NODE, &show_bgp_rsclient_summary_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_rsclient_summary_cmd);
  install_element (VIEW_NODE, &show_bgp_instance_rsclient_summary_cmd);
  install_element (VIEW_NODE, &show_bgp_instance_ipv6_rsclient_summary_cmd);
  install_element (VIEW_NODE, &show_bgp_instance_ipv6_safi_rsclient_summary_cmd);
  install_element (VIEW_NODE, &show_bgp_ipv6_safi_rsclient_summary_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_rsclient_summary_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_rsclient_summary_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_instance_rsclient_summary_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_instance_ipv6_rsclient_summary_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_instance_ipv6_safi_rsclient_summary_cmd);
  install_element (RESTRICTED_NODE, &show_bgp_ipv6_safi_rsclient_summary_cmd);
  install_element (ENABLE_NODE, &show_bgp_rsclient_summary_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_rsclient_summary_cmd);
  install_element (ENABLE_NODE, &show_bgp_instance_rsclient_summary_cmd);
  install_element (ENABLE_NODE, &show_bgp_instance_ipv6_rsclient_summary_cmd);
  install_element (ENABLE_NODE, &show_bgp_instance_ipv6_safi_rsclient_summary_cmd);
  install_element (ENABLE_NODE, &show_bgp_ipv6_safi_rsclient_summary_cmd);
#endif /* HAVE_IPV6 */

  /* "show ip bgp paths" commands. */
  install_element (VIEW_NODE, &show_ip_bgp_paths_cmd);
  install_element (VIEW_NODE, &show_ip_bgp_ipv4_paths_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_paths_cmd);
  install_element (ENABLE_NODE, &show_ip_bgp_ipv4_paths_cmd);
}
