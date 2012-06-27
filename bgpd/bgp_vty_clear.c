/* Functions used by the "clear bgp ..." CLI commands.
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
#include "bgpd/bgp_advertise.h"
#include "bgpd/bgp_aspath.h"
#include "bgpd/bgp_nexthop.h"
#include "bgpd/bgp_damp.h"
#include "bgpd/bgp_route.h"
#include "bgpd/bgp_table.h"
#include "bgpd/bgp_vty.h"
#include "bgpd/bgp_vty_clear.h"

static void
bgp_clear_vty_error (struct vty *vty, struct peer *peer, afi_t afi,
		     safi_t safi, int error)
{
  switch (error)
    {
    case BGP_ERR_AF_UNCONFIGURED:
      vty_out (vty,
	       "%%BGP: Enable %s %s address family for the neighbor %s%s",
	       afi == AFI_IP6 ? "IPv6" : safi == SAFI_MPLS_VPN ? "VPNv4" : "IPv4",
	       safi == SAFI_MULTICAST ? "Multicast" : "Unicast",
	       peer->host, VTY_NEWLINE);
      break;
    case BGP_ERR_SOFT_RECONFIG_UNCONFIGURED:
      vty_out (vty, "%%BGP: Inbound soft reconfig for %s not possible as it%s      has neither refresh capability, nor inbound soft reconfig%s", peer->host, VTY_NEWLINE, VTY_NEWLINE);
      break;
    default:
      break;
    }
}

/* `clear ip bgp' functions. */
static int
bgp_clear (struct vty *vty, struct bgp *bgp,  afi_t afi, safi_t safi,
           enum clear_sort sort,enum bgp_clear_type stype, const char *arg)
{
  int ret;
  struct peer *peer;
  struct listnode *node, *nnode;

  /* Clear all neighbors. */
  if (sort == clear_all)
    {
      for (ALL_LIST_ELEMENTS (bgp->peer, node, nnode, peer))
	{
	  if (stype == BGP_CLEAR_SOFT_NONE)
	    ret = peer_clear (peer);
	  else
	    ret = peer_clear_soft (peer, afi, safi, stype);

	  if (ret < 0)
	    bgp_clear_vty_error (vty, peer, afi, safi, ret);
	}
      return CMD_SUCCESS;
    }

  /* Clear specified neighbors. */
  if (sort == clear_peer)
    {
      union sockunion su;
      int ret;

      /* Make sockunion for lookup. */
      ret = str2sockunion (arg, &su);
      if (ret < 0)
	{
	  vty_out (vty, "Malformed address: %s%s", arg, VTY_NEWLINE);
	  return CMD_WARNING;
	}
      peer = peer_lookup (bgp, &su);
      if (! peer)
	{
	  vty_out (vty, "%%BGP: Unknown neighbor - \"%s\"%s", arg, VTY_NEWLINE);
	  return CMD_WARNING;
	}

      if (stype == BGP_CLEAR_SOFT_NONE)
	ret = peer_clear (peer);
      else
	ret = peer_clear_soft (peer, afi, safi, stype);

      if (ret < 0)
	bgp_clear_vty_error (vty, peer, afi, safi, ret);

      return CMD_SUCCESS;
    }

  /* Clear all peer-group members. */
  if (sort == clear_group)
    {
      struct peer_group *group;

      group = peer_group_lookup (bgp, arg);
      if (! group)
	{
	  vty_out (vty, "%%BGP: No such peer-group %s%s", arg, VTY_NEWLINE);
	  return CMD_WARNING;
	}

      for (ALL_LIST_ELEMENTS (group->peer, node, nnode, peer))
	{
	  if (stype == BGP_CLEAR_SOFT_NONE)
	    {
	      ret = peer_clear (peer);
	      continue;
	    }

	  if (! peer->af_group[afi][safi])
	    continue;

	  ret = peer_clear_soft (peer, afi, safi, stype);

	  if (ret < 0)
	    bgp_clear_vty_error (vty, peer, afi, safi, ret);
	}
      return CMD_SUCCESS;
    }

  if (sort == clear_external)
    {
      for (ALL_LIST_ELEMENTS (bgp->peer, node, nnode, peer))
	{
	  if (peer->sort == BGP_PEER_IBGP)
	    continue;

	  if (stype == BGP_CLEAR_SOFT_NONE)
	    ret = peer_clear (peer);
	  else
	    ret = peer_clear_soft (peer, afi, safi, stype);

	  if (ret < 0)
	    bgp_clear_vty_error (vty, peer, afi, safi, ret);
	}
      return CMD_SUCCESS;
    }

  if (sort == clear_as)
    {
      as_t as;
      int find = 0;

      VTY_GET_INTEGER_RANGE ("AS", as, arg, 1, BGP_AS4_MAX);

      for (ALL_LIST_ELEMENTS (bgp->peer, node, nnode, peer))
	{
	  if (peer->as != as)
	    continue;

	  find = 1;
	  if (stype == BGP_CLEAR_SOFT_NONE)
	    ret = peer_clear (peer);
	  else
	    ret = peer_clear_soft (peer, afi, safi, stype);

	  if (ret < 0)
	    bgp_clear_vty_error (vty, peer, afi, safi, ret);
	}
      if (! find)
	vty_out (vty, "%%BGP: No peer is configured with AS %s%s", arg,
		 VTY_NEWLINE);
      return CMD_SUCCESS;
    }

  return CMD_SUCCESS;
}

int
bgp_clear_vty (struct vty *vty, const char *name, afi_t afi, safi_t safi,
               enum clear_sort sort, enum bgp_clear_type stype,
               const char *arg)
{
  struct bgp *bgp;

  /* BGP structure lookup. */
  if (name)
    {
      bgp = bgp_lookup_by_name (name);
      if (bgp == NULL)
        {
          vty_out (vty, "Can't find BGP view %s%s", name, VTY_NEWLINE);
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

  return bgp_clear (vty, bgp, afi, safi, sort, stype, arg);
}

/* Display specified route of BGP table. */
int
bgp_clear_damp_route (struct vty *vty, const char *view_name,
                      const char *ip_str, afi_t afi, safi_t safi,
                      struct prefix_rd *prd, int prefix_check)
{
  int ret;
  struct prefix match;
  struct bgp_node *rn;
  struct bgp_node *rm;
  struct bgp_info *ri;
  struct bgp_info *ri_temp;
  struct bgp *bgp;
  struct bgp_table *table;

  /* BGP structure lookup. */
  if (view_name)
    {
      bgp = bgp_lookup_by_name (view_name);
      if (bgp == NULL)
	{
	  vty_out (vty, "%% Can't find BGP view %s%s", view_name, VTY_NEWLINE);
	  return CMD_WARNING;
	}
    }
  else
    {
      bgp = bgp_get_default ();
      if (bgp == NULL)
	{
	  vty_out (vty, "%% No BGP process is configured%s", VTY_NEWLINE);
	  return CMD_WARNING;
	}
    }

  /* Check IP address argument. */
  ret = str2prefix (ip_str, &match);
  if (! ret)
    {
      vty_out (vty, "%% address is malformed%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  match.family = afi2family (afi);

  if (safi == SAFI_MPLS_VPN)
    {
      for (rn = bgp_table_top (bgp->rib[AFI_IP][SAFI_MPLS_VPN]); rn; rn = bgp_route_next (rn))
        {
          if (prd && memcmp (rn->p.u.val, prd->val, 8) != 0)
            continue;

	  if ((table = rn->info) != NULL)
	    if ((rm = bgp_node_match (table, &match)) != NULL)
              {
                if (! prefix_check || rm->p.prefixlen == match.prefixlen)
                  {
                    ri = rm->info;
                    while (ri)
                      {
                        if (ri->extra && ri->extra->damp_info)
                          {
                            ri_temp = ri->next;
                            bgp_damp_info_free (ri->extra->damp_info, 1);
                            ri = ri_temp;
                          }
                        else
                          ri = ri->next;
                      }
                  }

                bgp_unlock_node (rm);
              }
        }
    }
  else
    {
      if ((rn = bgp_node_match (bgp->rib[afi][safi], &match)) != NULL)
        {
          if (! prefix_check || rn->p.prefixlen == match.prefixlen)
            {
              ri = rn->info;
              while (ri)
                {
                  if (ri->extra && ri->extra->damp_info)
                    {
                      ri_temp = ri->next;
                      bgp_damp_info_free (ri->extra->damp_info, 1);
                      ri = ri_temp;
                    }
                  else
                    ri = ri->next;
                }
            }

          bgp_unlock_node (rn);
        }
    }

  return CMD_SUCCESS;
}
