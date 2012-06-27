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

#include "command.h"
#include "prefix.h"

#include "bgpd/bgpd.h"
#include "bgpd/bgp_damp.h"
#include "bgpd/bgp_vty.h"
#include "bgpd/bgp_vty_clear.h"

DEFUN (clear_ip_bgp_all,
       clear_ip_bgp_all_cmd,
       "clear ip bgp *",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all peers\n")
{
  if (argc == 1)
    return bgp_clear_vty (vty, argv[0], 0, 0, clear_all, BGP_CLEAR_SOFT_NONE, NULL);

  return bgp_clear_vty (vty, NULL, 0, 0, clear_all, BGP_CLEAR_SOFT_NONE, NULL);
}

ALIAS (clear_ip_bgp_all,
       clear_bgp_all_cmd,
       "clear bgp *",
       CLEAR_STR
       BGP_STR
       "Clear all peers\n")

ALIAS (clear_ip_bgp_all,
       clear_bgp_ipv6_all_cmd,
       "clear bgp ipv6 *",
       CLEAR_STR
       BGP_STR
       "Address family\n"
       "Clear all peers\n")

ALIAS (clear_ip_bgp_all,
       clear_ip_bgp_instance_all_cmd,
       "clear ip bgp view WORD *",
       CLEAR_STR
       IP_STR
       BGP_STR
       "BGP view\n"
       "view name\n"
       "Clear all peers\n")

ALIAS (clear_ip_bgp_all,
       clear_bgp_instance_all_cmd,
       "clear bgp view WORD *",
       CLEAR_STR
       BGP_STR
       "BGP view\n"
       "view name\n"
       "Clear all peers\n")

DEFUN (clear_ip_bgp_peer,
       clear_ip_bgp_peer_cmd,
       "clear ip bgp (A.B.C.D|X:X::X:X)",
       CLEAR_STR
       IP_STR
       BGP_STR
       "BGP neighbor IP address to clear\n"
       "BGP IPv6 neighbor to clear\n")
{
  return bgp_clear_vty (vty, NULL, 0, 0, clear_peer, BGP_CLEAR_SOFT_NONE, argv[0]);
}

ALIAS (clear_ip_bgp_peer,
       clear_bgp_peer_cmd,
       "clear bgp (A.B.C.D|X:X::X:X)",
       CLEAR_STR
       BGP_STR
       "BGP neighbor address to clear\n"
       "BGP IPv6 neighbor to clear\n")

ALIAS (clear_ip_bgp_peer,
       clear_bgp_ipv6_peer_cmd,
       "clear bgp ipv6 (A.B.C.D|X:X::X:X)",
       CLEAR_STR
       BGP_STR
       "Address family\n"
       "BGP neighbor address to clear\n"
       "BGP IPv6 neighbor to clear\n")

DEFUN (clear_ip_bgp_peer_group,
       clear_ip_bgp_peer_group_cmd,
       "clear ip bgp peer-group WORD",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all members of peer-group\n"
       "BGP peer-group name\n")
{
  return bgp_clear_vty (vty, NULL, 0, 0, clear_group, BGP_CLEAR_SOFT_NONE, argv[0]);
}

ALIAS (clear_ip_bgp_peer_group,
       clear_bgp_peer_group_cmd,
       "clear bgp peer-group WORD",
       CLEAR_STR
       BGP_STR
       "Clear all members of peer-group\n"
       "BGP peer-group name\n")

ALIAS (clear_ip_bgp_peer_group,
       clear_bgp_ipv6_peer_group_cmd,
       "clear bgp ipv6 peer-group WORD",
       CLEAR_STR
       BGP_STR
       "Address family\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n")

DEFUN (clear_ip_bgp_external,
       clear_ip_bgp_external_cmd,
       "clear ip bgp external",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all external peers\n")
{
  return bgp_clear_vty (vty, NULL, 0, 0, clear_external, BGP_CLEAR_SOFT_NONE, NULL);
}

ALIAS (clear_ip_bgp_external,
       clear_bgp_external_cmd,
       "clear bgp external",
       CLEAR_STR
       BGP_STR
       "Clear all external peers\n")

ALIAS (clear_ip_bgp_external,
       clear_bgp_ipv6_external_cmd,
       "clear bgp ipv6 external",
       CLEAR_STR
       BGP_STR
       "Address family\n"
       "Clear all external peers\n")

DEFUN (clear_ip_bgp_as,
       clear_ip_bgp_as_cmd,
       "clear ip bgp " CMD_AS_RANGE,
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear peers with the AS number\n")
{
  return bgp_clear_vty (vty, NULL, 0, 0, clear_as, BGP_CLEAR_SOFT_NONE, argv[0]);
}

ALIAS (clear_ip_bgp_as,
       clear_bgp_as_cmd,
       "clear bgp " CMD_AS_RANGE,
       CLEAR_STR
       BGP_STR
       "Clear peers with the AS number\n")

ALIAS (clear_ip_bgp_as,
       clear_bgp_ipv6_as_cmd,
       "clear bgp ipv6 " CMD_AS_RANGE,
       CLEAR_STR
       BGP_STR
       "Address family\n"
       "Clear peers with the AS number\n")

/* Outbound soft-reconfiguration */
DEFUN (clear_ip_bgp_all_soft_out,
       clear_ip_bgp_all_soft_out_cmd,
       "clear ip bgp * soft out",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all peers\n"
       "Soft reconfig\n"
       "Soft reconfig outbound update\n")
{
  if (argc == 1)
    return bgp_clear_vty (vty, argv[0], AFI_IP, SAFI_UNICAST, clear_all,
                          BGP_CLEAR_SOFT_OUT, NULL);

  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_all,
			BGP_CLEAR_SOFT_OUT, NULL);
}

ALIAS (clear_ip_bgp_all_soft_out,
       clear_ip_bgp_all_out_cmd,
       "clear ip bgp * out",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all peers\n"
       "Soft reconfig outbound update\n")

ALIAS (clear_ip_bgp_all_soft_out,
       clear_ip_bgp_instance_all_soft_out_cmd,
       "clear ip bgp view WORD * soft out",
       CLEAR_STR
       IP_STR
       BGP_STR
       "BGP view\n"
       "view name\n"
       "Clear all peers\n"
       "Soft reconfig\n"
       "Soft reconfig outbound update\n")

DEFUN (clear_ip_bgp_all_ipv4_soft_out,
       clear_ip_bgp_all_ipv4_soft_out_cmd,
       "clear ip bgp * ipv4 (unicast|multicast) soft out",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all peers\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Soft reconfig\n"
       "Soft reconfig outbound update\n")
{
  if (strncmp (argv[0], "m", 1) == 0)
    return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_MULTICAST, clear_all,
			  BGP_CLEAR_SOFT_OUT, NULL);

  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_all,
			BGP_CLEAR_SOFT_OUT, NULL);
}

ALIAS (clear_ip_bgp_all_ipv4_soft_out,
       clear_ip_bgp_all_ipv4_out_cmd,
       "clear ip bgp * ipv4 (unicast|multicast) out",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all peers\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Soft reconfig outbound update\n")

DEFUN (clear_ip_bgp_instance_all_ipv4_soft_out,
       clear_ip_bgp_instance_all_ipv4_soft_out_cmd,
       "clear ip bgp view WORD * ipv4 (unicast|multicast) soft out",
       CLEAR_STR
       IP_STR
       BGP_STR
       "BGP view\n"
       "view name\n"
       "Clear all peers\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Soft reconfig outbound update\n")
{
  if (strncmp (argv[1], "m", 1) == 0)
    return bgp_clear_vty (vty, argv[0], AFI_IP, SAFI_MULTICAST, clear_all,
                          BGP_CLEAR_SOFT_OUT, NULL);

  return bgp_clear_vty (vty, argv[0], AFI_IP, SAFI_UNICAST, clear_all,
                        BGP_CLEAR_SOFT_OUT, NULL);
}

DEFUN (clear_ip_bgp_all_vpnv4_soft_out,
       clear_ip_bgp_all_vpnv4_soft_out_cmd,
       "clear ip bgp * vpnv4 unicast soft out",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all peers\n"
       "Address family\n"
       "Address Family Modifier\n"
       "Soft reconfig\n"
       "Soft reconfig outbound update\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_MPLS_VPN, clear_all,
			BGP_CLEAR_SOFT_OUT, NULL);
}

ALIAS (clear_ip_bgp_all_vpnv4_soft_out,
       clear_ip_bgp_all_vpnv4_out_cmd,
       "clear ip bgp * vpnv4 unicast out",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all peers\n"
       "Address family\n"
       "Address Family Modifier\n"
       "Soft reconfig outbound update\n")

DEFUN (clear_bgp_all_soft_out,
       clear_bgp_all_soft_out_cmd,
       "clear bgp * soft out",
       CLEAR_STR
       BGP_STR
       "Clear all peers\n"
       "Soft reconfig\n"
       "Soft reconfig outbound update\n")
{
  if (argc == 1)
    return bgp_clear_vty (vty, argv[0], AFI_IP6, SAFI_UNICAST, clear_all,
                          BGP_CLEAR_SOFT_OUT, NULL);

  return bgp_clear_vty (vty, NULL, AFI_IP6, SAFI_UNICAST, clear_all,
			BGP_CLEAR_SOFT_OUT, NULL);
}

ALIAS (clear_bgp_all_soft_out,
       clear_bgp_instance_all_soft_out_cmd,
       "clear bgp view WORD * soft out",
       CLEAR_STR
       BGP_STR
       "BGP view\n"
       "view name\n"
       "Clear all peers\n"
       "Soft reconfig\n"
       "Soft reconfig outbound update\n")

ALIAS (clear_bgp_all_soft_out,
       clear_bgp_all_out_cmd,
       "clear bgp * out",
       CLEAR_STR
       BGP_STR
       "Clear all peers\n"
       "Soft reconfig outbound update\n")

ALIAS (clear_bgp_all_soft_out,
       clear_bgp_ipv6_all_soft_out_cmd,
       "clear bgp ipv6 * soft out",
       CLEAR_STR
       BGP_STR
       "Address family\n"
       "Clear all peers\n"
       "Soft reconfig\n"
       "Soft reconfig outbound update\n")

ALIAS (clear_bgp_all_soft_out,
       clear_bgp_ipv6_all_out_cmd,
       "clear bgp ipv6 * out",
       CLEAR_STR
       BGP_STR
       "Address family\n"
       "Clear all peers\n"
       "Soft reconfig outbound update\n")

DEFUN (clear_ip_bgp_peer_soft_out,
       clear_ip_bgp_peer_soft_out_cmd,
       "clear ip bgp A.B.C.D soft out",
       CLEAR_STR
       IP_STR
       BGP_STR
       "BGP neighbor address to clear\n"
       "Soft reconfig\n"
       "Soft reconfig outbound update\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_peer,
			BGP_CLEAR_SOFT_OUT, argv[0]);
}

ALIAS (clear_ip_bgp_peer_soft_out,
       clear_ip_bgp_peer_out_cmd,
       "clear ip bgp A.B.C.D out",
       CLEAR_STR
       IP_STR
       BGP_STR
       "BGP neighbor address to clear\n"
       "Soft reconfig outbound update\n")

DEFUN (clear_ip_bgp_peer_ipv4_soft_out,
       clear_ip_bgp_peer_ipv4_soft_out_cmd,
       "clear ip bgp A.B.C.D ipv4 (unicast|multicast) soft out",
       CLEAR_STR
       IP_STR
       BGP_STR
       "BGP neighbor address to clear\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Soft reconfig\n"
       "Soft reconfig outbound update\n")
{
  if (strncmp (argv[1], "m", 1) == 0)
    return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_MULTICAST, clear_peer,
			  BGP_CLEAR_SOFT_OUT, argv[0]);

  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_peer,
			BGP_CLEAR_SOFT_OUT, argv[0]);
}

ALIAS (clear_ip_bgp_peer_ipv4_soft_out,
       clear_ip_bgp_peer_ipv4_out_cmd,
       "clear ip bgp A.B.C.D ipv4 (unicast|multicast) out",
       CLEAR_STR
       IP_STR
       BGP_STR
       "BGP neighbor address to clear\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Soft reconfig outbound update\n")

DEFUN (clear_ip_bgp_peer_vpnv4_soft_out,
       clear_ip_bgp_peer_vpnv4_soft_out_cmd,
       "clear ip bgp A.B.C.D vpnv4 unicast soft out",
       CLEAR_STR
       IP_STR
       BGP_STR
       "BGP neighbor address to clear\n"
       "Address family\n"
       "Address Family Modifier\n"
       "Soft reconfig\n"
       "Soft reconfig outbound update\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_MPLS_VPN, clear_peer,
			BGP_CLEAR_SOFT_OUT, argv[0]);
}

ALIAS (clear_ip_bgp_peer_vpnv4_soft_out,
       clear_ip_bgp_peer_vpnv4_out_cmd,
       "clear ip bgp A.B.C.D vpnv4 unicast out",
       CLEAR_STR
       IP_STR
       BGP_STR
       "BGP neighbor address to clear\n"
       "Address family\n"
       "Address Family Modifier\n"
       "Soft reconfig outbound update\n")

DEFUN (clear_bgp_peer_soft_out,
       clear_bgp_peer_soft_out_cmd,
       "clear bgp (A.B.C.D|X:X::X:X) soft out",
       CLEAR_STR
       BGP_STR
       "BGP neighbor address to clear\n"
       "BGP IPv6 neighbor to clear\n"
       "Soft reconfig\n"
       "Soft reconfig outbound update\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP6, SAFI_UNICAST, clear_peer,
			BGP_CLEAR_SOFT_OUT, argv[0]);
}

ALIAS (clear_bgp_peer_soft_out,
       clear_bgp_ipv6_peer_soft_out_cmd,
       "clear bgp ipv6 (A.B.C.D|X:X::X:X) soft out",
       CLEAR_STR
       BGP_STR
       "Address family\n"
       "BGP neighbor address to clear\n"
       "BGP IPv6 neighbor to clear\n"
       "Soft reconfig\n"
       "Soft reconfig outbound update\n")

ALIAS (clear_bgp_peer_soft_out,
       clear_bgp_peer_out_cmd,
       "clear bgp (A.B.C.D|X:X::X:X) out",
       CLEAR_STR
       BGP_STR
       "BGP neighbor address to clear\n"
       "BGP IPv6 neighbor to clear\n"
       "Soft reconfig outbound update\n")

ALIAS (clear_bgp_peer_soft_out,
       clear_bgp_ipv6_peer_out_cmd,
       "clear bgp ipv6 (A.B.C.D|X:X::X:X) out",
       CLEAR_STR
       BGP_STR
       "Address family\n"
       "BGP neighbor address to clear\n"
       "BGP IPv6 neighbor to clear\n"
       "Soft reconfig outbound update\n")

DEFUN (clear_ip_bgp_peer_group_soft_out,
       clear_ip_bgp_peer_group_soft_out_cmd,
       "clear ip bgp peer-group WORD soft out",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig\n"
       "Soft reconfig outbound update\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_group,
			BGP_CLEAR_SOFT_OUT, argv[0]);
}

ALIAS (clear_ip_bgp_peer_group_soft_out,
       clear_ip_bgp_peer_group_out_cmd,
       "clear ip bgp peer-group WORD out",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig outbound update\n")

DEFUN (clear_ip_bgp_peer_group_ipv4_soft_out,
       clear_ip_bgp_peer_group_ipv4_soft_out_cmd,
       "clear ip bgp peer-group WORD ipv4 (unicast|multicast) soft out",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Soft reconfig\n"
       "Soft reconfig outbound update\n")
{
  if (strncmp (argv[1], "m", 1) == 0)
    return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_MULTICAST, clear_group,
			  BGP_CLEAR_SOFT_OUT, argv[0]);

  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_group,
			BGP_CLEAR_SOFT_OUT, argv[0]);
}

ALIAS (clear_ip_bgp_peer_group_ipv4_soft_out,
       clear_ip_bgp_peer_group_ipv4_out_cmd,
       "clear ip bgp peer-group WORD ipv4 (unicast|multicast) out",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Soft reconfig outbound update\n")

DEFUN (clear_bgp_peer_group_soft_out,
       clear_bgp_peer_group_soft_out_cmd,
       "clear bgp peer-group WORD soft out",
       CLEAR_STR
       BGP_STR
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig\n"
       "Soft reconfig outbound update\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP6, SAFI_UNICAST, clear_group,
			BGP_CLEAR_SOFT_OUT, argv[0]);
}

ALIAS (clear_bgp_peer_group_soft_out,
       clear_bgp_ipv6_peer_group_soft_out_cmd,
       "clear bgp ipv6 peer-group WORD soft out",
       CLEAR_STR
       BGP_STR
       "Address family\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig\n"
       "Soft reconfig outbound update\n")

ALIAS (clear_bgp_peer_group_soft_out,
       clear_bgp_peer_group_out_cmd,
       "clear bgp peer-group WORD out",
       CLEAR_STR
       BGP_STR
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig outbound update\n")

ALIAS (clear_bgp_peer_group_soft_out,
       clear_bgp_ipv6_peer_group_out_cmd,
       "clear bgp ipv6 peer-group WORD out",
       CLEAR_STR
       BGP_STR
       "Address family\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig outbound update\n")

DEFUN (clear_ip_bgp_external_soft_out,
       clear_ip_bgp_external_soft_out_cmd,
       "clear ip bgp external soft out",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all external peers\n"
       "Soft reconfig\n"
       "Soft reconfig outbound update\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_external,
			BGP_CLEAR_SOFT_OUT, NULL);
}

ALIAS (clear_ip_bgp_external_soft_out,
       clear_ip_bgp_external_out_cmd,
       "clear ip bgp external out",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all external peers\n"
       "Soft reconfig outbound update\n")

DEFUN (clear_ip_bgp_external_ipv4_soft_out,
       clear_ip_bgp_external_ipv4_soft_out_cmd,
       "clear ip bgp external ipv4 (unicast|multicast) soft out",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all external peers\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Soft reconfig\n"
       "Soft reconfig outbound update\n")
{
  if (strncmp (argv[0], "m", 1) == 0)
    return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_MULTICAST, clear_external,
			  BGP_CLEAR_SOFT_OUT, NULL);

  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_external,
			BGP_CLEAR_SOFT_OUT, NULL);
}

ALIAS (clear_ip_bgp_external_ipv4_soft_out,
       clear_ip_bgp_external_ipv4_out_cmd,
       "clear ip bgp external ipv4 (unicast|multicast) out",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all external peers\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Soft reconfig outbound update\n")

DEFUN (clear_bgp_external_soft_out,
       clear_bgp_external_soft_out_cmd,
       "clear bgp external soft out",
       CLEAR_STR
       BGP_STR
       "Clear all external peers\n"
       "Soft reconfig\n"
       "Soft reconfig outbound update\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP6, SAFI_UNICAST, clear_external,
			BGP_CLEAR_SOFT_OUT, NULL);
}

ALIAS (clear_bgp_external_soft_out,
       clear_bgp_ipv6_external_soft_out_cmd,
       "clear bgp ipv6 external soft out",
       CLEAR_STR
       BGP_STR
       "Address family\n"
       "Clear all external peers\n"
       "Soft reconfig\n"
       "Soft reconfig outbound update\n")

ALIAS (clear_bgp_external_soft_out,
       clear_bgp_external_out_cmd,
       "clear bgp external out",
       CLEAR_STR
       BGP_STR
       "Clear all external peers\n"
       "Soft reconfig outbound update\n")

ALIAS (clear_bgp_external_soft_out,
       clear_bgp_ipv6_external_out_cmd,
       "clear bgp ipv6 external WORD out",
       CLEAR_STR
       BGP_STR
       "Address family\n"
       "Clear all external peers\n"
       "Soft reconfig outbound update\n")

DEFUN (clear_ip_bgp_as_soft_out,
       clear_ip_bgp_as_soft_out_cmd,
       "clear ip bgp " CMD_AS_RANGE " soft out",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear peers with the AS number\n"
       "Soft reconfig\n"
       "Soft reconfig outbound update\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_as,
			BGP_CLEAR_SOFT_OUT, argv[0]);
}

ALIAS (clear_ip_bgp_as_soft_out,
       clear_ip_bgp_as_out_cmd,
       "clear ip bgp " CMD_AS_RANGE " out",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear peers with the AS number\n"
       "Soft reconfig outbound update\n")

DEFUN (clear_ip_bgp_as_ipv4_soft_out,
       clear_ip_bgp_as_ipv4_soft_out_cmd,
       "clear ip bgp " CMD_AS_RANGE " ipv4 (unicast|multicast) soft out",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear peers with the AS number\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Soft reconfig\n"
       "Soft reconfig outbound update\n")
{
  if (strncmp (argv[1], "m", 1) == 0)
    return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_MULTICAST, clear_as,
			  BGP_CLEAR_SOFT_OUT, argv[0]);

  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_as,
			BGP_CLEAR_SOFT_OUT, argv[0]);
}

ALIAS (clear_ip_bgp_as_ipv4_soft_out,
       clear_ip_bgp_as_ipv4_out_cmd,
       "clear ip bgp " CMD_AS_RANGE " ipv4 (unicast|multicast) out",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear peers with the AS number\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Soft reconfig outbound update\n")

DEFUN (clear_ip_bgp_as_vpnv4_soft_out,
       clear_ip_bgp_as_vpnv4_soft_out_cmd,
       "clear ip bgp " CMD_AS_RANGE " vpnv4 unicast soft out",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear peers with the AS number\n"
       "Address family\n"
       "Address Family modifier\n"
       "Soft reconfig\n"
       "Soft reconfig outbound update\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_MPLS_VPN, clear_as,
			BGP_CLEAR_SOFT_OUT, argv[0]);
}

ALIAS (clear_ip_bgp_as_vpnv4_soft_out,
       clear_ip_bgp_as_vpnv4_out_cmd,
       "clear ip bgp " CMD_AS_RANGE " vpnv4 unicast out",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear peers with the AS number\n"
       "Address family\n"
       "Address Family modifier\n"
       "Soft reconfig outbound update\n")

DEFUN (clear_bgp_as_soft_out,
       clear_bgp_as_soft_out_cmd,
       "clear bgp " CMD_AS_RANGE " soft out",
       CLEAR_STR
       BGP_STR
       "Clear peers with the AS number\n"
       "Soft reconfig\n"
       "Soft reconfig outbound update\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP6, SAFI_UNICAST, clear_as,
			BGP_CLEAR_SOFT_OUT, argv[0]);
}

ALIAS (clear_bgp_as_soft_out,
       clear_bgp_ipv6_as_soft_out_cmd,
       "clear bgp ipv6 " CMD_AS_RANGE " soft out",
       CLEAR_STR
       BGP_STR
       "Address family\n"
       "Clear peers with the AS number\n"
       "Soft reconfig\n"
       "Soft reconfig outbound update\n")

ALIAS (clear_bgp_as_soft_out,
       clear_bgp_as_out_cmd,
       "clear bgp " CMD_AS_RANGE " out",
       CLEAR_STR
       BGP_STR
       "Clear peers with the AS number\n"
       "Soft reconfig outbound update\n")

ALIAS (clear_bgp_as_soft_out,
       clear_bgp_ipv6_as_out_cmd,
       "clear bgp ipv6 " CMD_AS_RANGE " out",
       CLEAR_STR
       BGP_STR
       "Address family\n"
       "Clear peers with the AS number\n"
       "Soft reconfig outbound update\n")

/* Inbound soft-reconfiguration */
DEFUN (clear_ip_bgp_all_soft_in,
       clear_ip_bgp_all_soft_in_cmd,
       "clear ip bgp * soft in",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all peers\n"
       "Soft reconfig\n"
       "Soft reconfig inbound update\n")
{
  if (argc == 1)
    return bgp_clear_vty (vty, argv[0], AFI_IP, SAFI_UNICAST, clear_all,
                          BGP_CLEAR_SOFT_IN, NULL);

  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_all,
			BGP_CLEAR_SOFT_IN, NULL);
}

ALIAS (clear_ip_bgp_all_soft_in,
       clear_ip_bgp_instance_all_soft_in_cmd,
       "clear ip bgp view WORD * soft in",
       CLEAR_STR
       IP_STR
       BGP_STR
       "BGP view\n"
       "view name\n"
       "Clear all peers\n"
       "Soft reconfig\n"
       "Soft reconfig inbound update\n")

ALIAS (clear_ip_bgp_all_soft_in,
       clear_ip_bgp_all_in_cmd,
       "clear ip bgp * in",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all peers\n"
       "Soft reconfig inbound update\n")

DEFUN (clear_ip_bgp_all_in_prefix_filter,
       clear_ip_bgp_all_in_prefix_filter_cmd,
       "clear ip bgp * in prefix-filter",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all peers\n"
       "Soft reconfig inbound update\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  if (argc== 1)
    return bgp_clear_vty (vty, argv[0], AFI_IP, SAFI_UNICAST, clear_all,
                          BGP_CLEAR_SOFT_IN_ORF_PREFIX, NULL);

  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_all,
			BGP_CLEAR_SOFT_IN_ORF_PREFIX, NULL);
}

ALIAS (clear_ip_bgp_all_in_prefix_filter,
       clear_ip_bgp_instance_all_in_prefix_filter_cmd,
       "clear ip bgp view WORD * in prefix-filter",
       CLEAR_STR
       IP_STR
       BGP_STR
       "BGP view\n"
       "view name\n"
       "Clear all peers\n"
       "Soft reconfig inbound update\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")


DEFUN (clear_ip_bgp_all_ipv4_soft_in,
       clear_ip_bgp_all_ipv4_soft_in_cmd,
       "clear ip bgp * ipv4 (unicast|multicast) soft in",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all peers\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Soft reconfig\n"
       "Soft reconfig inbound update\n")
{
  if (strncmp (argv[0], "m", 1) == 0)
    return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_MULTICAST, clear_all,
			  BGP_CLEAR_SOFT_IN, NULL);

  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_all,
			BGP_CLEAR_SOFT_IN, NULL);
}

ALIAS (clear_ip_bgp_all_ipv4_soft_in,
       clear_ip_bgp_all_ipv4_in_cmd,
       "clear ip bgp * ipv4 (unicast|multicast) in",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all peers\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Soft reconfig inbound update\n")

DEFUN (clear_ip_bgp_instance_all_ipv4_soft_in,
       clear_ip_bgp_instance_all_ipv4_soft_in_cmd,
       "clear ip bgp view WORD * ipv4 (unicast|multicast) soft in",
       CLEAR_STR
       IP_STR
       BGP_STR
       "BGP view\n"
       "view name\n"
       "Clear all peers\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Soft reconfig\n"
       "Soft reconfig inbound update\n")
{
  if (strncmp (argv[1], "m", 1) == 0)
    return bgp_clear_vty (vty, argv[0], AFI_IP, SAFI_MULTICAST, clear_all,
                          BGP_CLEAR_SOFT_IN, NULL);

  return bgp_clear_vty (vty, argv[0], AFI_IP, SAFI_UNICAST, clear_all,
                        BGP_CLEAR_SOFT_IN, NULL);
}

DEFUN (clear_ip_bgp_all_ipv4_in_prefix_filter,
       clear_ip_bgp_all_ipv4_in_prefix_filter_cmd,
       "clear ip bgp * ipv4 (unicast|multicast) in prefix-filter",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all peers\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Soft reconfig inbound update\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  if (strncmp (argv[0], "m", 1) == 0)
    return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_MULTICAST, clear_all,
			  BGP_CLEAR_SOFT_IN_ORF_PREFIX, NULL);

  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_all,
			BGP_CLEAR_SOFT_IN_ORF_PREFIX, NULL);
}

DEFUN (clear_ip_bgp_instance_all_ipv4_in_prefix_filter,
       clear_ip_bgp_instance_all_ipv4_in_prefix_filter_cmd,
       "clear ip bgp view WORD * ipv4 (unicast|multicast) in prefix-filter",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all peers\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Soft reconfig inbound update\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  if (strncmp (argv[1], "m", 1) == 0)
    return bgp_clear_vty (vty, argv[0], AFI_IP, SAFI_MULTICAST, clear_all,
                          BGP_CLEAR_SOFT_IN_ORF_PREFIX, NULL);

  return bgp_clear_vty (vty, argv[0], AFI_IP, SAFI_UNICAST, clear_all,
                        BGP_CLEAR_SOFT_IN_ORF_PREFIX, NULL);
}

DEFUN (clear_ip_bgp_all_vpnv4_soft_in,
       clear_ip_bgp_all_vpnv4_soft_in_cmd,
       "clear ip bgp * vpnv4 unicast soft in",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all peers\n"
       "Address family\n"
       "Address Family Modifier\n"
       "Soft reconfig\n"
       "Soft reconfig inbound update\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_MPLS_VPN, clear_all,
			BGP_CLEAR_SOFT_IN, NULL);
}

ALIAS (clear_ip_bgp_all_vpnv4_soft_in,
       clear_ip_bgp_all_vpnv4_in_cmd,
       "clear ip bgp * vpnv4 unicast in",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all peers\n"
       "Address family\n"
       "Address Family Modifier\n"
       "Soft reconfig inbound update\n")

DEFUN (clear_bgp_all_soft_in,
       clear_bgp_all_soft_in_cmd,
       "clear bgp * soft in",
       CLEAR_STR
       BGP_STR
       "Clear all peers\n"
       "Soft reconfig\n"
       "Soft reconfig inbound update\n")
{
  if (argc == 1)
    return bgp_clear_vty (vty, argv[0], AFI_IP6, SAFI_UNICAST, clear_all,
                        BGP_CLEAR_SOFT_IN, NULL);

  return bgp_clear_vty (vty, NULL, AFI_IP6, SAFI_UNICAST, clear_all,
			BGP_CLEAR_SOFT_IN, NULL);
}

ALIAS (clear_bgp_all_soft_in,
       clear_bgp_instance_all_soft_in_cmd,
       "clear bgp view WORD * soft in",
       CLEAR_STR
       BGP_STR
       "BGP view\n"
       "view name\n"
       "Clear all peers\n"
       "Soft reconfig\n"
       "Soft reconfig inbound update\n")

ALIAS (clear_bgp_all_soft_in,
       clear_bgp_ipv6_all_soft_in_cmd,
       "clear bgp ipv6 * soft in",
       CLEAR_STR
       BGP_STR
       "Address family\n"
       "Clear all peers\n"
       "Soft reconfig\n"
       "Soft reconfig inbound update\n")

ALIAS (clear_bgp_all_soft_in,
       clear_bgp_all_in_cmd,
       "clear bgp * in",
       CLEAR_STR
       BGP_STR
       "Clear all peers\n"
       "Soft reconfig inbound update\n")

ALIAS (clear_bgp_all_soft_in,
       clear_bgp_ipv6_all_in_cmd,
       "clear bgp ipv6 * in",
       CLEAR_STR
       BGP_STR
       "Address family\n"
       "Clear all peers\n"
       "Soft reconfig inbound update\n")

DEFUN (clear_bgp_all_in_prefix_filter,
       clear_bgp_all_in_prefix_filter_cmd,
       "clear bgp * in prefix-filter",
       CLEAR_STR
       BGP_STR
       "Clear all peers\n"
       "Soft reconfig inbound update\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP6, SAFI_UNICAST, clear_all,
			BGP_CLEAR_SOFT_IN_ORF_PREFIX, NULL);
}

ALIAS (clear_bgp_all_in_prefix_filter,
       clear_bgp_ipv6_all_in_prefix_filter_cmd,
       "clear bgp ipv6 * in prefix-filter",
       CLEAR_STR
       BGP_STR
       "Address family\n"
       "Clear all peers\n"
       "Soft reconfig inbound update\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")

DEFUN (clear_ip_bgp_peer_soft_in,
       clear_ip_bgp_peer_soft_in_cmd,
       "clear ip bgp A.B.C.D soft in",
       CLEAR_STR
       IP_STR
       BGP_STR
       "BGP neighbor address to clear\n"
       "Soft reconfig\n"
       "Soft reconfig inbound update\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_peer,
			BGP_CLEAR_SOFT_IN, argv[0]);
}

ALIAS (clear_ip_bgp_peer_soft_in,
       clear_ip_bgp_peer_in_cmd,
       "clear ip bgp A.B.C.D in",
       CLEAR_STR
       IP_STR
       BGP_STR
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound update\n")

DEFUN (clear_ip_bgp_peer_in_prefix_filter,
       clear_ip_bgp_peer_in_prefix_filter_cmd,
       "clear ip bgp A.B.C.D in prefix-filter",
       CLEAR_STR
       IP_STR
       BGP_STR
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound update\n"
       "Push out the existing ORF prefix-list\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_peer,
			BGP_CLEAR_SOFT_IN_ORF_PREFIX, argv[0]);
}

DEFUN (clear_ip_bgp_peer_ipv4_soft_in,
       clear_ip_bgp_peer_ipv4_soft_in_cmd,
       "clear ip bgp A.B.C.D ipv4 (unicast|multicast) soft in",
       CLEAR_STR
       IP_STR
       BGP_STR
       "BGP neighbor address to clear\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Soft reconfig\n"
       "Soft reconfig inbound update\n")
{
  if (strncmp (argv[1], "m", 1) == 0)
    return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_MULTICAST, clear_peer,
			  BGP_CLEAR_SOFT_IN, argv[0]);

  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_peer,
			BGP_CLEAR_SOFT_IN, argv[0]);
}

ALIAS (clear_ip_bgp_peer_ipv4_soft_in,
       clear_ip_bgp_peer_ipv4_in_cmd,
       "clear ip bgp A.B.C.D ipv4 (unicast|multicast) in",
       CLEAR_STR
       IP_STR
       BGP_STR
       "BGP neighbor address to clear\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Soft reconfig inbound update\n")

DEFUN (clear_ip_bgp_peer_ipv4_in_prefix_filter,
       clear_ip_bgp_peer_ipv4_in_prefix_filter_cmd,
       "clear ip bgp A.B.C.D ipv4 (unicast|multicast) in prefix-filter",
       CLEAR_STR
       IP_STR
       BGP_STR
       "BGP neighbor address to clear\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Soft reconfig inbound update\n"
       "Push out the existing ORF prefix-list\n")
{
  if (strncmp (argv[1], "m", 1) == 0)
    return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_MULTICAST, clear_peer,
			  BGP_CLEAR_SOFT_IN_ORF_PREFIX, argv[0]);

  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_peer,
			BGP_CLEAR_SOFT_IN_ORF_PREFIX, argv[0]);
}

DEFUN (clear_ip_bgp_peer_vpnv4_soft_in,
       clear_ip_bgp_peer_vpnv4_soft_in_cmd,
       "clear ip bgp A.B.C.D vpnv4 unicast soft in",
       CLEAR_STR
       IP_STR
       BGP_STR
       "BGP neighbor address to clear\n"
       "Address family\n"
       "Address Family Modifier\n"
       "Soft reconfig\n"
       "Soft reconfig inbound update\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_MPLS_VPN, clear_peer,
			BGP_CLEAR_SOFT_IN, argv[0]);
}

ALIAS (clear_ip_bgp_peer_vpnv4_soft_in,
       clear_ip_bgp_peer_vpnv4_in_cmd,
       "clear ip bgp A.B.C.D vpnv4 unicast in",
       CLEAR_STR
       IP_STR
       BGP_STR
       "BGP neighbor address to clear\n"
       "Address family\n"
       "Address Family Modifier\n"
       "Soft reconfig inbound update\n")

DEFUN (clear_bgp_peer_soft_in,
       clear_bgp_peer_soft_in_cmd,
       "clear bgp (A.B.C.D|X:X::X:X) soft in",
       CLEAR_STR
       BGP_STR
       "BGP neighbor address to clear\n"
       "BGP IPv6 neighbor to clear\n"
       "Soft reconfig\n"
       "Soft reconfig inbound update\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP6, SAFI_UNICAST, clear_peer,
			BGP_CLEAR_SOFT_IN, argv[0]);
}

ALIAS (clear_bgp_peer_soft_in,
       clear_bgp_ipv6_peer_soft_in_cmd,
       "clear bgp ipv6 (A.B.C.D|X:X::X:X) soft in",
       CLEAR_STR
       BGP_STR
       "Address family\n"
       "BGP neighbor address to clear\n"
       "BGP IPv6 neighbor to clear\n"
       "Soft reconfig\n"
       "Soft reconfig inbound update\n")

ALIAS (clear_bgp_peer_soft_in,
       clear_bgp_peer_in_cmd,
       "clear bgp (A.B.C.D|X:X::X:X) in",
       CLEAR_STR
       BGP_STR
       "BGP neighbor address to clear\n"
       "BGP IPv6 neighbor to clear\n"
       "Soft reconfig inbound update\n")

ALIAS (clear_bgp_peer_soft_in,
       clear_bgp_ipv6_peer_in_cmd,
       "clear bgp ipv6 (A.B.C.D|X:X::X:X) in",
       CLEAR_STR
       BGP_STR
       "Address family\n"
       "BGP neighbor address to clear\n"
       "BGP IPv6 neighbor to clear\n"
       "Soft reconfig inbound update\n")

DEFUN (clear_bgp_peer_in_prefix_filter,
       clear_bgp_peer_in_prefix_filter_cmd,
       "clear bgp (A.B.C.D|X:X::X:X) in prefix-filter",
       CLEAR_STR
       BGP_STR
       "BGP neighbor address to clear\n"
       "BGP IPv6 neighbor to clear\n"
       "Soft reconfig inbound update\n"
       "Push out the existing ORF prefix-list\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP6, SAFI_UNICAST, clear_peer,
			BGP_CLEAR_SOFT_IN_ORF_PREFIX, argv[0]);
}

ALIAS (clear_bgp_peer_in_prefix_filter,
       clear_bgp_ipv6_peer_in_prefix_filter_cmd,
       "clear bgp ipv6 (A.B.C.D|X:X::X:X) in prefix-filter",
       CLEAR_STR
       BGP_STR
       "Address family\n"
       "BGP neighbor address to clear\n"
       "BGP IPv6 neighbor to clear\n"
       "Soft reconfig inbound update\n"
       "Push out the existing ORF prefix-list\n")

DEFUN (clear_ip_bgp_peer_group_soft_in,
       clear_ip_bgp_peer_group_soft_in_cmd,
       "clear ip bgp peer-group WORD soft in",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig\n"
       "Soft reconfig inbound update\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_group,
			BGP_CLEAR_SOFT_IN, argv[0]);
}

ALIAS (clear_ip_bgp_peer_group_soft_in,
       clear_ip_bgp_peer_group_in_cmd,
       "clear ip bgp peer-group WORD in",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound update\n")

DEFUN (clear_ip_bgp_peer_group_in_prefix_filter,
       clear_ip_bgp_peer_group_in_prefix_filter_cmd,
       "clear ip bgp peer-group WORD in prefix-filter",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound update\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_group,
			BGP_CLEAR_SOFT_IN_ORF_PREFIX, argv[0]);
}

DEFUN (clear_ip_bgp_peer_group_ipv4_soft_in,
       clear_ip_bgp_peer_group_ipv4_soft_in_cmd,
       "clear ip bgp peer-group WORD ipv4 (unicast|multicast) soft in",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Soft reconfig\n"
       "Soft reconfig inbound update\n")
{
  if (strncmp (argv[1], "m", 1) == 0)
    return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_MULTICAST, clear_group,
			  BGP_CLEAR_SOFT_IN, argv[0]);

  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_group,
			BGP_CLEAR_SOFT_IN, argv[0]);
}

ALIAS (clear_ip_bgp_peer_group_ipv4_soft_in,
       clear_ip_bgp_peer_group_ipv4_in_cmd,
       "clear ip bgp peer-group WORD ipv4 (unicast|multicast) in",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Soft reconfig inbound update\n")

DEFUN (clear_ip_bgp_peer_group_ipv4_in_prefix_filter,
       clear_ip_bgp_peer_group_ipv4_in_prefix_filter_cmd,
       "clear ip bgp peer-group WORD ipv4 (unicast|multicast) in prefix-filter",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Soft reconfig inbound update\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  if (strncmp (argv[1], "m", 1) == 0)
    return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_MULTICAST, clear_group,
			  BGP_CLEAR_SOFT_IN_ORF_PREFIX, argv[0]);

  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_group,
			BGP_CLEAR_SOFT_IN_ORF_PREFIX, argv[0]);
}

DEFUN (clear_bgp_peer_group_soft_in,
       clear_bgp_peer_group_soft_in_cmd,
       "clear bgp peer-group WORD soft in",
       CLEAR_STR
       BGP_STR
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig\n"
       "Soft reconfig inbound update\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP6, SAFI_UNICAST, clear_group,
			BGP_CLEAR_SOFT_IN, argv[0]);
}

ALIAS (clear_bgp_peer_group_soft_in,
       clear_bgp_ipv6_peer_group_soft_in_cmd,
       "clear bgp ipv6 peer-group WORD soft in",
       CLEAR_STR
       BGP_STR
       "Address family\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig\n"
       "Soft reconfig inbound update\n")

ALIAS (clear_bgp_peer_group_soft_in,
       clear_bgp_peer_group_in_cmd,
       "clear bgp peer-group WORD in",
       CLEAR_STR
       BGP_STR
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound update\n")

ALIAS (clear_bgp_peer_group_soft_in,
       clear_bgp_ipv6_peer_group_in_cmd,
       "clear bgp ipv6 peer-group WORD in",
       CLEAR_STR
       BGP_STR
       "Address family\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound update\n")

DEFUN (clear_bgp_peer_group_in_prefix_filter,
       clear_bgp_peer_group_in_prefix_filter_cmd,
       "clear bgp peer-group WORD in prefix-filter",
       CLEAR_STR
       BGP_STR
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound update\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP6, SAFI_UNICAST, clear_group,
			BGP_CLEAR_SOFT_IN_ORF_PREFIX, argv[0]);
}

ALIAS (clear_bgp_peer_group_in_prefix_filter,
       clear_bgp_ipv6_peer_group_in_prefix_filter_cmd,
       "clear bgp ipv6 peer-group WORD in prefix-filter",
       CLEAR_STR
       BGP_STR
       "Address family\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound update\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")

DEFUN (clear_ip_bgp_external_soft_in,
       clear_ip_bgp_external_soft_in_cmd,
       "clear ip bgp external soft in",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all external peers\n"
       "Soft reconfig\n"
       "Soft reconfig inbound update\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_external,
			BGP_CLEAR_SOFT_IN, NULL);
}

ALIAS (clear_ip_bgp_external_soft_in,
       clear_ip_bgp_external_in_cmd,
       "clear ip bgp external in",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all external peers\n"
       "Soft reconfig inbound update\n")

DEFUN (clear_ip_bgp_external_in_prefix_filter,
       clear_ip_bgp_external_in_prefix_filter_cmd,
       "clear ip bgp external in prefix-filter",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all external peers\n"
       "Soft reconfig inbound update\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_external,
			BGP_CLEAR_SOFT_IN_ORF_PREFIX, NULL);
}

DEFUN (clear_ip_bgp_external_ipv4_soft_in,
       clear_ip_bgp_external_ipv4_soft_in_cmd,
       "clear ip bgp external ipv4 (unicast|multicast) soft in",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all external peers\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Soft reconfig\n"
       "Soft reconfig inbound update\n")
{
  if (strncmp (argv[0], "m", 1) == 0)
    return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_MULTICAST, clear_external,
			  BGP_CLEAR_SOFT_IN, NULL);

  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_external,
			BGP_CLEAR_SOFT_IN, NULL);
}

ALIAS (clear_ip_bgp_external_ipv4_soft_in,
       clear_ip_bgp_external_ipv4_in_cmd,
       "clear ip bgp external ipv4 (unicast|multicast) in",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all external peers\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Soft reconfig inbound update\n")

DEFUN (clear_ip_bgp_external_ipv4_in_prefix_filter,
       clear_ip_bgp_external_ipv4_in_prefix_filter_cmd,
       "clear ip bgp external ipv4 (unicast|multicast) in prefix-filter",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all external peers\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Soft reconfig inbound update\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  if (strncmp (argv[0], "m", 1) == 0)
    return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_MULTICAST, clear_external,
			  BGP_CLEAR_SOFT_IN_ORF_PREFIX, NULL);

  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_external,
			BGP_CLEAR_SOFT_IN_ORF_PREFIX, NULL);
}

DEFUN (clear_bgp_external_soft_in,
       clear_bgp_external_soft_in_cmd,
       "clear bgp external soft in",
       CLEAR_STR
       BGP_STR
       "Clear all external peers\n"
       "Soft reconfig\n"
       "Soft reconfig inbound update\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP6, SAFI_UNICAST, clear_external,
			BGP_CLEAR_SOFT_IN, NULL);
}

ALIAS (clear_bgp_external_soft_in,
       clear_bgp_ipv6_external_soft_in_cmd,
       "clear bgp ipv6 external soft in",
       CLEAR_STR
       BGP_STR
       "Address family\n"
       "Clear all external peers\n"
       "Soft reconfig\n"
       "Soft reconfig inbound update\n")

ALIAS (clear_bgp_external_soft_in,
       clear_bgp_external_in_cmd,
       "clear bgp external in",
       CLEAR_STR
       BGP_STR
       "Clear all external peers\n"
       "Soft reconfig inbound update\n")

ALIAS (clear_bgp_external_soft_in,
       clear_bgp_ipv6_external_in_cmd,
       "clear bgp ipv6 external WORD in",
       CLEAR_STR
       BGP_STR
       "Address family\n"
       "Clear all external peers\n"
       "Soft reconfig inbound update\n")

DEFUN (clear_bgp_external_in_prefix_filter,
       clear_bgp_external_in_prefix_filter_cmd,
       "clear bgp external in prefix-filter",
       CLEAR_STR
       BGP_STR
       "Clear all external peers\n"
       "Soft reconfig inbound update\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP6, SAFI_UNICAST, clear_external,
			BGP_CLEAR_SOFT_IN_ORF_PREFIX, NULL);
}

ALIAS (clear_bgp_external_in_prefix_filter,
       clear_bgp_ipv6_external_in_prefix_filter_cmd,
       "clear bgp ipv6 external in prefix-filter",
       CLEAR_STR
       BGP_STR
       "Address family\n"
       "Clear all external peers\n"
       "Soft reconfig inbound update\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")

DEFUN (clear_ip_bgp_as_soft_in,
       clear_ip_bgp_as_soft_in_cmd,
       "clear ip bgp " CMD_AS_RANGE " soft in",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear peers with the AS number\n"
       "Soft reconfig\n"
       "Soft reconfig inbound update\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_as,
			BGP_CLEAR_SOFT_IN, argv[0]);
}

ALIAS (clear_ip_bgp_as_soft_in,
       clear_ip_bgp_as_in_cmd,
       "clear ip bgp " CMD_AS_RANGE " in",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear peers with the AS number\n"
       "Soft reconfig inbound update\n")

DEFUN (clear_ip_bgp_as_in_prefix_filter,
       clear_ip_bgp_as_in_prefix_filter_cmd,
       "clear ip bgp " CMD_AS_RANGE " in prefix-filter",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear peers with the AS number\n"
       "Soft reconfig inbound update\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_as,
			BGP_CLEAR_SOFT_IN_ORF_PREFIX, argv[0]);
}

DEFUN (clear_ip_bgp_as_ipv4_soft_in,
       clear_ip_bgp_as_ipv4_soft_in_cmd,
       "clear ip bgp " CMD_AS_RANGE " ipv4 (unicast|multicast) soft in",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear peers with the AS number\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Soft reconfig\n"
       "Soft reconfig inbound update\n")
{
  if (strncmp (argv[1], "m", 1) == 0)
    return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_MULTICAST, clear_as,
			  BGP_CLEAR_SOFT_IN, argv[0]);

  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_as,
			BGP_CLEAR_SOFT_IN, argv[0]);
}

ALIAS (clear_ip_bgp_as_ipv4_soft_in,
       clear_ip_bgp_as_ipv4_in_cmd,
       "clear ip bgp " CMD_AS_RANGE " ipv4 (unicast|multicast) in",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear peers with the AS number\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Soft reconfig inbound update\n")

DEFUN (clear_ip_bgp_as_ipv4_in_prefix_filter,
       clear_ip_bgp_as_ipv4_in_prefix_filter_cmd,
       "clear ip bgp " CMD_AS_RANGE " ipv4 (unicast|multicast) in prefix-filter",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear peers with the AS number\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Soft reconfig inbound update\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  if (strncmp (argv[1], "m", 1) == 0)
    return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_MULTICAST, clear_as,
			  BGP_CLEAR_SOFT_IN_ORF_PREFIX, argv[0]);

  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_as,
			BGP_CLEAR_SOFT_IN_ORF_PREFIX, argv[0]);
}

DEFUN (clear_ip_bgp_as_vpnv4_soft_in,
       clear_ip_bgp_as_vpnv4_soft_in_cmd,
       "clear ip bgp " CMD_AS_RANGE " vpnv4 unicast soft in",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear peers with the AS number\n"
       "Address family\n"
       "Address Family modifier\n"
       "Soft reconfig\n"
       "Soft reconfig inbound update\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_MPLS_VPN, clear_as,
			BGP_CLEAR_SOFT_IN, argv[0]);
}

ALIAS (clear_ip_bgp_as_vpnv4_soft_in,
       clear_ip_bgp_as_vpnv4_in_cmd,
       "clear ip bgp " CMD_AS_RANGE " vpnv4 unicast in",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear peers with the AS number\n"
       "Address family\n"
       "Address Family modifier\n"
       "Soft reconfig inbound update\n")

DEFUN (clear_bgp_as_soft_in,
       clear_bgp_as_soft_in_cmd,
       "clear bgp " CMD_AS_RANGE " soft in",
       CLEAR_STR
       BGP_STR
       "Clear peers with the AS number\n"
       "Soft reconfig\n"
       "Soft reconfig inbound update\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP6, SAFI_UNICAST, clear_as,
			BGP_CLEAR_SOFT_IN, argv[0]);
}

ALIAS (clear_bgp_as_soft_in,
       clear_bgp_ipv6_as_soft_in_cmd,
       "clear bgp ipv6 " CMD_AS_RANGE " soft in",
       CLEAR_STR
       BGP_STR
       "Address family\n"
       "Clear peers with the AS number\n"
       "Soft reconfig\n"
       "Soft reconfig inbound update\n")

ALIAS (clear_bgp_as_soft_in,
       clear_bgp_as_in_cmd,
       "clear bgp " CMD_AS_RANGE " in",
       CLEAR_STR
       BGP_STR
       "Clear peers with the AS number\n"
       "Soft reconfig inbound update\n")

ALIAS (clear_bgp_as_soft_in,
       clear_bgp_ipv6_as_in_cmd,
       "clear bgp ipv6 " CMD_AS_RANGE " in",
       CLEAR_STR
       BGP_STR
       "Address family\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound update\n")

DEFUN (clear_bgp_as_in_prefix_filter,
       clear_bgp_as_in_prefix_filter_cmd,
       "clear bgp " CMD_AS_RANGE " in prefix-filter",
       CLEAR_STR
       BGP_STR
       "Clear peers with the AS number\n"
       "Soft reconfig inbound update\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP6, SAFI_UNICAST, clear_as,
			BGP_CLEAR_SOFT_IN_ORF_PREFIX, argv[0]);
}

ALIAS (clear_bgp_as_in_prefix_filter,
       clear_bgp_ipv6_as_in_prefix_filter_cmd,
       "clear bgp ipv6 " CMD_AS_RANGE " in prefix-filter",
       CLEAR_STR
       BGP_STR
       "Address family\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound update\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")

/* Both soft-reconfiguration */
DEFUN (clear_ip_bgp_all_soft,
       clear_ip_bgp_all_soft_cmd,
       "clear ip bgp * soft",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all peers\n"
       "Soft reconfig\n")
{
  if (argc == 1)
    return bgp_clear_vty (vty, argv[0], AFI_IP, SAFI_UNICAST, clear_all,
                        BGP_CLEAR_SOFT_BOTH, NULL);

  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_all,
			BGP_CLEAR_SOFT_BOTH, NULL);
}

ALIAS (clear_ip_bgp_all_soft,
       clear_ip_bgp_instance_all_soft_cmd,
       "clear ip bgp view WORD * soft",
       CLEAR_STR
       IP_STR
       BGP_STR
       "BGP view\n"
       "view name\n"
       "Clear all peers\n"
       "Soft reconfig\n")


DEFUN (clear_ip_bgp_all_ipv4_soft,
       clear_ip_bgp_all_ipv4_soft_cmd,
       "clear ip bgp * ipv4 (unicast|multicast) soft",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all peers\n"
       "Address family\n"
       "Address Family Modifier\n"
       "Address Family Modifier\n"
       "Soft reconfig\n")
{
  if (strncmp (argv[0], "m", 1) == 0)
    return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_MULTICAST, clear_all,
			  BGP_CLEAR_SOFT_BOTH, NULL);

  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_all,
			BGP_CLEAR_SOFT_BOTH, NULL);
}

DEFUN (clear_ip_bgp_instance_all_ipv4_soft,
       clear_ip_bgp_instance_all_ipv4_soft_cmd,
       "clear ip bgp view WORD * ipv4 (unicast|multicast) soft",
       CLEAR_STR
       IP_STR
       BGP_STR
       "BGP view\n"
       "view name\n"
       "Clear all peers\n"
       "Address family\n"
       "Address Family Modifier\n"
       "Address Family Modifier\n"
       "Soft reconfig\n")
{
  if (strncmp (argv[1], "m", 1) == 0)
    return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_MULTICAST, clear_all,
                          BGP_CLEAR_SOFT_BOTH, NULL);

  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_all,
                        BGP_CLEAR_SOFT_BOTH, NULL);
}

DEFUN (clear_ip_bgp_all_vpnv4_soft,
       clear_ip_bgp_all_vpnv4_soft_cmd,
       "clear ip bgp * vpnv4 unicast soft",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all peers\n"
       "Address family\n"
       "Address Family Modifier\n"
       "Soft reconfig\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_MPLS_VPN, clear_all,
			BGP_CLEAR_SOFT_BOTH, argv[0]);
}

DEFUN (clear_bgp_all_soft,
       clear_bgp_all_soft_cmd,
       "clear bgp * soft",
       CLEAR_STR
       BGP_STR
       "Clear all peers\n"
       "Soft reconfig\n")
{
  if (argc == 1)
    return bgp_clear_vty (vty, argv[0], AFI_IP6, SAFI_UNICAST, clear_all,
                        BGP_CLEAR_SOFT_BOTH, argv[0]);

  return bgp_clear_vty (vty, NULL, AFI_IP6, SAFI_UNICAST, clear_all,
			BGP_CLEAR_SOFT_BOTH, argv[0]);
}

ALIAS (clear_bgp_all_soft,
       clear_bgp_instance_all_soft_cmd,
       "clear bgp view WORD * soft",
       CLEAR_STR
       BGP_STR
       "BGP view\n"
       "view name\n"
       "Clear all peers\n"
       "Soft reconfig\n")

ALIAS (clear_bgp_all_soft,
       clear_bgp_ipv6_all_soft_cmd,
       "clear bgp ipv6 * soft",
       CLEAR_STR
       BGP_STR
       "Address family\n"
       "Clear all peers\n"
       "Soft reconfig\n")

DEFUN (clear_ip_bgp_peer_soft,
       clear_ip_bgp_peer_soft_cmd,
       "clear ip bgp A.B.C.D soft",
       CLEAR_STR
       IP_STR
       BGP_STR
       "BGP neighbor address to clear\n"
       "Soft reconfig\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_peer,
			BGP_CLEAR_SOFT_BOTH, argv[0]);
}

DEFUN (clear_ip_bgp_peer_ipv4_soft,
       clear_ip_bgp_peer_ipv4_soft_cmd,
       "clear ip bgp A.B.C.D ipv4 (unicast|multicast) soft",
       CLEAR_STR
       IP_STR
       BGP_STR
       "BGP neighbor address to clear\n"
       "Address family\n"
       "Address Family Modifier\n"
       "Address Family Modifier\n"
       "Soft reconfig\n")
{
  if (strncmp (argv[1], "m", 1) == 0)
    return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_MULTICAST, clear_peer,
			  BGP_CLEAR_SOFT_BOTH, argv[0]);

  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_peer,
			BGP_CLEAR_SOFT_BOTH, argv[0]);
}

DEFUN (clear_ip_bgp_peer_vpnv4_soft,
       clear_ip_bgp_peer_vpnv4_soft_cmd,
       "clear ip bgp A.B.C.D vpnv4 unicast soft",
       CLEAR_STR
       IP_STR
       BGP_STR
       "BGP neighbor address to clear\n"
       "Address family\n"
       "Address Family Modifier\n"
       "Soft reconfig\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_MPLS_VPN, clear_peer,
			BGP_CLEAR_SOFT_BOTH, argv[0]);
}

DEFUN (clear_bgp_peer_soft,
       clear_bgp_peer_soft_cmd,
       "clear bgp (A.B.C.D|X:X::X:X) soft",
       CLEAR_STR
       BGP_STR
       "BGP neighbor address to clear\n"
       "BGP IPv6 neighbor to clear\n"
       "Soft reconfig\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP6, SAFI_UNICAST, clear_peer,
			BGP_CLEAR_SOFT_BOTH, argv[0]);
}

ALIAS (clear_bgp_peer_soft,
       clear_bgp_ipv6_peer_soft_cmd,
       "clear bgp ipv6 (A.B.C.D|X:X::X:X) soft",
       CLEAR_STR
       BGP_STR
       "Address family\n"
       "BGP neighbor address to clear\n"
       "BGP IPv6 neighbor to clear\n"
       "Soft reconfig\n")

DEFUN (clear_ip_bgp_peer_group_soft,
       clear_ip_bgp_peer_group_soft_cmd,
       "clear ip bgp peer-group WORD soft",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_group,
			BGP_CLEAR_SOFT_BOTH, argv[0]);
}

DEFUN (clear_ip_bgp_peer_group_ipv4_soft,
       clear_ip_bgp_peer_group_ipv4_soft_cmd,
       "clear ip bgp peer-group WORD ipv4 (unicast|multicast) soft",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Soft reconfig\n")
{
  if (strncmp (argv[1], "m", 1) == 0)
    return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_MULTICAST, clear_group,
			  BGP_CLEAR_SOFT_BOTH, argv[0]);

  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_group,
			BGP_CLEAR_SOFT_BOTH, argv[0]);
}

DEFUN (clear_bgp_peer_group_soft,
       clear_bgp_peer_group_soft_cmd,
       "clear bgp peer-group WORD soft",
       CLEAR_STR
       BGP_STR
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP6, SAFI_UNICAST, clear_group,
			BGP_CLEAR_SOFT_BOTH, argv[0]);
}

ALIAS (clear_bgp_peer_group_soft,
       clear_bgp_ipv6_peer_group_soft_cmd,
       "clear bgp ipv6 peer-group WORD soft",
       CLEAR_STR
       BGP_STR
       "Address family\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig\n")

DEFUN (clear_ip_bgp_external_soft,
       clear_ip_bgp_external_soft_cmd,
       "clear ip bgp external soft",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all external peers\n"
       "Soft reconfig\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_external,
			BGP_CLEAR_SOFT_BOTH, NULL);
}

DEFUN (clear_ip_bgp_external_ipv4_soft,
       clear_ip_bgp_external_ipv4_soft_cmd,
       "clear ip bgp external ipv4 (unicast|multicast) soft",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all external peers\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Soft reconfig\n")
{
  if (strncmp (argv[0], "m", 1) == 0)
    return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_MULTICAST, clear_external,
			  BGP_CLEAR_SOFT_BOTH, NULL);

  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_external,
			BGP_CLEAR_SOFT_BOTH, NULL);
}

DEFUN (clear_bgp_external_soft,
       clear_bgp_external_soft_cmd,
       "clear bgp external soft",
       CLEAR_STR
       BGP_STR
       "Clear all external peers\n"
       "Soft reconfig\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP6, SAFI_UNICAST, clear_external,
			BGP_CLEAR_SOFT_BOTH, NULL);
}

ALIAS (clear_bgp_external_soft,
       clear_bgp_ipv6_external_soft_cmd,
       "clear bgp ipv6 external soft",
       CLEAR_STR
       BGP_STR
       "Address family\n"
       "Clear all external peers\n"
       "Soft reconfig\n")

DEFUN (clear_ip_bgp_as_soft,
       clear_ip_bgp_as_soft_cmd,
       "clear ip bgp " CMD_AS_RANGE " soft",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear peers with the AS number\n"
       "Soft reconfig\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_as,
			BGP_CLEAR_SOFT_BOTH, argv[0]);
}

DEFUN (clear_ip_bgp_as_ipv4_soft,
       clear_ip_bgp_as_ipv4_soft_cmd,
       "clear ip bgp " CMD_AS_RANGE " ipv4 (unicast|multicast) soft",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear peers with the AS number\n"
       "Address family\n"
       "Address Family Modifier\n"
       "Address Family Modifier\n"
       "Soft reconfig\n")
{
  if (strncmp (argv[1], "m", 1) == 0)
    return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_MULTICAST, clear_as,
			  BGP_CLEAR_SOFT_BOTH, argv[0]);

  return bgp_clear_vty (vty, NULL,AFI_IP, SAFI_UNICAST, clear_as,
			BGP_CLEAR_SOFT_BOTH, argv[0]);
}

DEFUN (clear_ip_bgp_as_vpnv4_soft,
       clear_ip_bgp_as_vpnv4_soft_cmd,
       "clear ip bgp " CMD_AS_RANGE " vpnv4 unicast soft",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear peers with the AS number\n"
       "Address family\n"
       "Address Family Modifier\n"
       "Soft reconfig\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_MPLS_VPN, clear_as,
			BGP_CLEAR_SOFT_BOTH, argv[0]);
}

DEFUN (clear_bgp_as_soft,
       clear_bgp_as_soft_cmd,
       "clear bgp " CMD_AS_RANGE " soft",
       CLEAR_STR
       BGP_STR
       "Clear peers with the AS number\n"
       "Soft reconfig\n")
{
  return bgp_clear_vty (vty, NULL, AFI_IP6, SAFI_UNICAST, clear_as,
			BGP_CLEAR_SOFT_BOTH, argv[0]);
}

ALIAS (clear_bgp_as_soft,
       clear_bgp_ipv6_as_soft_cmd,
       "clear bgp ipv6 " CMD_AS_RANGE " soft",
       CLEAR_STR
       BGP_STR
       "Address family\n"
       "Clear peers with the AS number\n"
       "Soft reconfig\n")

/* RS-client soft reconfiguration. */
#ifdef HAVE_IPV6
DEFUN (clear_bgp_all_rsclient,
       clear_bgp_all_rsclient_cmd,
       "clear bgp * rsclient",
       CLEAR_STR
       BGP_STR
       "Clear all peers\n"
       "Soft reconfig for rsclient RIB\n")
{
  if (argc == 1)
    return bgp_clear_vty (vty, argv[0], AFI_IP6, SAFI_UNICAST, clear_all,
                          BGP_CLEAR_SOFT_RSCLIENT, NULL);

  return bgp_clear_vty (vty, NULL, AFI_IP6, SAFI_UNICAST, clear_all,
                        BGP_CLEAR_SOFT_RSCLIENT, NULL);
}

ALIAS (clear_bgp_all_rsclient,
       clear_bgp_ipv6_all_rsclient_cmd,
       "clear bgp ipv6 * rsclient",
       CLEAR_STR
       BGP_STR
       "Address family\n"
       "Clear all peers\n"
       "Soft reconfig for rsclient RIB\n")

ALIAS (clear_bgp_all_rsclient,
       clear_bgp_instance_all_rsclient_cmd,
       "clear bgp view WORD * rsclient",
       CLEAR_STR
       BGP_STR
       "BGP view\n"
       "view name\n"
       "Clear all peers\n"
       "Soft reconfig for rsclient RIB\n")

ALIAS (clear_bgp_all_rsclient,
       clear_bgp_ipv6_instance_all_rsclient_cmd,
       "clear bgp ipv6 view WORD * rsclient",
       CLEAR_STR
       BGP_STR
       "Address family\n"
       "BGP view\n"
       "view name\n"
       "Clear all peers\n"
       "Soft reconfig for rsclient RIB\n")
#endif /* HAVE_IPV6 */

DEFUN (clear_ip_bgp_all_rsclient,
       clear_ip_bgp_all_rsclient_cmd,
       "clear ip bgp * rsclient",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear all peers\n"
       "Soft reconfig for rsclient RIB\n")
{
  if (argc == 1)
    return bgp_clear_vty (vty, argv[0], AFI_IP, SAFI_UNICAST, clear_all,
                          BGP_CLEAR_SOFT_RSCLIENT, NULL);

  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_all,
                        BGP_CLEAR_SOFT_RSCLIENT, NULL);
}

ALIAS (clear_ip_bgp_all_rsclient,
       clear_ip_bgp_instance_all_rsclient_cmd,
       "clear ip bgp view WORD * rsclient",
       CLEAR_STR
       IP_STR
       BGP_STR
       "BGP view\n"
       "view name\n"
       "Clear all peers\n"
       "Soft reconfig for rsclient RIB\n")

#ifdef HAVE_IPV6
DEFUN (clear_bgp_peer_rsclient,
       clear_bgp_peer_rsclient_cmd,
       "clear bgp (A.B.C.D|X:X::X:X) rsclient",
       CLEAR_STR
       BGP_STR
       "BGP neighbor IP address to clear\n"
       "BGP IPv6 neighbor to clear\n"
       "Soft reconfig for rsclient RIB\n")
{
  if (argc == 2)
    return bgp_clear_vty (vty, argv[0], AFI_IP6, SAFI_UNICAST, clear_peer,
                          BGP_CLEAR_SOFT_RSCLIENT, argv[1]);

  return bgp_clear_vty (vty, NULL, AFI_IP6, SAFI_UNICAST, clear_peer,
                        BGP_CLEAR_SOFT_RSCLIENT, argv[0]);
}

ALIAS (clear_bgp_peer_rsclient,
       clear_bgp_ipv6_peer_rsclient_cmd,
       "clear bgp ipv6 (A.B.C.D|X:X::X:X) rsclient",
       CLEAR_STR
       BGP_STR
       "Address family\n"
       "BGP neighbor IP address to clear\n"
       "BGP IPv6 neighbor to clear\n"
       "Soft reconfig for rsclient RIB\n")

ALIAS (clear_bgp_peer_rsclient,
       clear_bgp_instance_peer_rsclient_cmd,
       "clear bgp view WORD (A.B.C.D|X:X::X:X) rsclient",
       CLEAR_STR
       BGP_STR
       "BGP view\n"
       "view name\n"
       "BGP neighbor IP address to clear\n"
       "BGP IPv6 neighbor to clear\n"
       "Soft reconfig for rsclient RIB\n")

ALIAS (clear_bgp_peer_rsclient,
       clear_bgp_ipv6_instance_peer_rsclient_cmd,
       "clear bgp ipv6 view WORD (A.B.C.D|X:X::X:X) rsclient",
       CLEAR_STR
       BGP_STR
       "Address family\n"
       "BGP view\n"
       "view name\n"
       "BGP neighbor IP address to clear\n"
       "BGP IPv6 neighbor to clear\n"
       "Soft reconfig for rsclient RIB\n")
#endif /* HAVE_IPV6 */

DEFUN (clear_ip_bgp_peer_rsclient,
       clear_ip_bgp_peer_rsclient_cmd,
       "clear ip bgp (A.B.C.D|X:X::X:X) rsclient",
       CLEAR_STR
       IP_STR
       BGP_STR
       "BGP neighbor IP address to clear\n"
       "BGP IPv6 neighbor to clear\n"
       "Soft reconfig for rsclient RIB\n")
{
  if (argc == 2)
    return bgp_clear_vty (vty, argv[0], AFI_IP, SAFI_UNICAST, clear_peer,
                          BGP_CLEAR_SOFT_RSCLIENT, argv[1]);

  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_UNICAST, clear_peer,
                        BGP_CLEAR_SOFT_RSCLIENT, argv[0]);
}

ALIAS (clear_ip_bgp_peer_rsclient,
       clear_ip_bgp_instance_peer_rsclient_cmd,
       "clear ip bgp view WORD (A.B.C.D|X:X::X:X) rsclient",
       CLEAR_STR
       IP_STR
       BGP_STR
       "BGP view\n"
       "view name\n"
       "BGP neighbor IP address to clear\n"
       "BGP IPv6 neighbor to clear\n"
       "Soft reconfig for rsclient RIB\n")

DEFUN (clear_ip_bgp_dampening,
       clear_ip_bgp_dampening_cmd,
       "clear ip bgp dampening",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear route flap dampening information\n")
{
  bgp_damp_info_clean ();
  return CMD_SUCCESS;
}

DEFUN (clear_ip_bgp_dampening_prefix,
       clear_ip_bgp_dampening_prefix_cmd,
       "clear ip bgp dampening A.B.C.D/M",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear route flap dampening information\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n")
{
  return bgp_clear_damp_route (vty, NULL, argv[0], AFI_IP,
			       SAFI_UNICAST, NULL, 1);
}

DEFUN (clear_ip_bgp_dampening_address,
       clear_ip_bgp_dampening_address_cmd,
       "clear ip bgp dampening A.B.C.D",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear route flap dampening information\n"
       "Network to clear damping information\n")
{
  return bgp_clear_damp_route (vty, NULL, argv[0], AFI_IP,
			       SAFI_UNICAST, NULL, 0);
}

DEFUN (clear_ip_bgp_dampening_address_mask,
       clear_ip_bgp_dampening_address_mask_cmd,
       "clear ip bgp dampening A.B.C.D A.B.C.D",
       CLEAR_STR
       IP_STR
       BGP_STR
       "Clear route flap dampening information\n"
       "Network to clear damping information\n"
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

  return bgp_clear_damp_route (vty, NULL, prefix_str, AFI_IP,
			       SAFI_UNICAST, NULL, 0);
}

void
bgp_vty_clear_init (void)
{
  /* "clear ip bgp commands" */
  install_element (ENABLE_NODE, &clear_ip_bgp_all_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_instance_all_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_as_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_group_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_external_cmd);
#ifdef HAVE_IPV6
  install_element (ENABLE_NODE, &clear_bgp_all_cmd);
  install_element (ENABLE_NODE, &clear_bgp_instance_all_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_all_cmd);
  install_element (ENABLE_NODE, &clear_bgp_peer_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_peer_cmd);
  install_element (ENABLE_NODE, &clear_bgp_peer_group_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_peer_group_cmd);
  install_element (ENABLE_NODE, &clear_bgp_external_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_external_cmd);
  install_element (ENABLE_NODE, &clear_bgp_as_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_as_cmd);
#endif /* HAVE_IPV6 */

  /* "clear ip bgp neighbor soft in" */
  install_element (ENABLE_NODE, &clear_ip_bgp_all_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_instance_all_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_all_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_all_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_instance_all_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_group_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_group_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_group_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_external_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_external_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_external_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_as_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_as_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_as_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_all_ipv4_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_instance_all_ipv4_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_all_ipv4_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_all_ipv4_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_instance_all_ipv4_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_ipv4_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_ipv4_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_ipv4_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_group_ipv4_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_group_ipv4_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_group_ipv4_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_external_ipv4_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_external_ipv4_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_external_ipv4_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_as_ipv4_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_as_ipv4_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_as_ipv4_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_all_vpnv4_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_all_vpnv4_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_vpnv4_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_vpnv4_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_as_vpnv4_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_as_vpnv4_in_cmd);
#ifdef HAVE_IPV6
  install_element (ENABLE_NODE, &clear_bgp_all_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_instance_all_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_all_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_all_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_peer_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_peer_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_peer_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_peer_group_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_peer_group_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_peer_group_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_external_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_external_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_external_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_as_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_as_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_as_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_all_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_all_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_all_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_peer_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_peer_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_peer_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_peer_group_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_peer_group_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_peer_group_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_external_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_external_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_external_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_as_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_as_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_as_in_prefix_filter_cmd);
#endif /* HAVE_IPV6 */

  /* "clear ip bgp neighbor soft out" */
  install_element (ENABLE_NODE, &clear_ip_bgp_all_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_instance_all_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_all_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_group_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_group_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_external_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_external_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_as_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_as_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_all_ipv4_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_instance_all_ipv4_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_all_ipv4_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_ipv4_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_ipv4_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_group_ipv4_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_group_ipv4_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_external_ipv4_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_external_ipv4_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_as_ipv4_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_as_ipv4_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_all_vpnv4_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_all_vpnv4_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_vpnv4_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_vpnv4_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_as_vpnv4_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_as_vpnv4_out_cmd);
#ifdef HAVE_IPV6
  install_element (ENABLE_NODE, &clear_bgp_all_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_instance_all_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_all_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_peer_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_peer_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_peer_group_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_peer_group_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_external_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_external_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_as_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_as_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_all_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_all_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_peer_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_peer_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_peer_group_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_peer_group_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_external_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_external_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_as_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_as_out_cmd);
#endif /* HAVE_IPV6 */

  /* "clear ip bgp neighbor soft" */
  install_element (ENABLE_NODE, &clear_ip_bgp_all_soft_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_instance_all_soft_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_soft_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_group_soft_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_external_soft_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_as_soft_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_all_ipv4_soft_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_instance_all_ipv4_soft_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_ipv4_soft_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_group_ipv4_soft_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_external_ipv4_soft_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_as_ipv4_soft_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_all_vpnv4_soft_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_vpnv4_soft_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_as_vpnv4_soft_cmd);
#ifdef HAVE_IPV6
  install_element (ENABLE_NODE, &clear_bgp_all_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_instance_all_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_peer_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_peer_group_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_external_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_as_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_all_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_peer_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_peer_group_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_external_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_as_soft_cmd);
#endif /* HAVE_IPV6 */

  /* "clear ip bgp neighbor rsclient" */
  install_element (ENABLE_NODE, &clear_ip_bgp_all_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_instance_all_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_instance_peer_rsclient_cmd);
#ifdef HAVE_IPV6
  install_element (ENABLE_NODE, &clear_bgp_all_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_bgp_instance_all_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_all_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_instance_all_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_bgp_peer_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_bgp_instance_peer_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_peer_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_instance_peer_rsclient_cmd);
#endif /* HAVE_IPV6 */

 /* BGP dampening clear commands */
  install_element (ENABLE_NODE, &clear_ip_bgp_dampening_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_dampening_prefix_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_dampening_address_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_dampening_address_mask_cmd);
}
