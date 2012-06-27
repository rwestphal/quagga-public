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
      vty_out (vty, "%% BGP: Enable %s address family for the neighbor %s%s",
	       afi_safi_print (afi, safi), peer->host, VTY_NEWLINE);
      break;
    case BGP_ERR_SOFT_RECONFIG_UNCONFIGURED:
      vty_out (vty, "%% BGP: Inbound soft reconfig for %s not possible as it%s      "
	       "has neither refresh capability, nor inbound soft reconfig%s",
	       peer->host, VTY_NEWLINE, VTY_NEWLINE);
      break;
    default:
      break;
    }
}

static enum bgp_clear_type
bgp_clear_type (struct vty_arg *args[])
{
  if (vty_get_arg_value (args, "soft_in"))
    return BGP_CLEAR_SOFT_IN;
  else if (vty_get_arg_value (args, "soft_out"))
    return BGP_CLEAR_SOFT_OUT;
  else if (vty_get_arg_value (args, "soft_pefix_filter"))
    return BGP_CLEAR_SOFT_IN_ORF_PREFIX;
  else if (vty_get_arg_value (args, "soft"))
    return BGP_CLEAR_SOFT_BOTH;
  else if (vty_get_arg_value (args, "soft_rsclient"))
    return BGP_CLEAR_SOFT_RSCLIENT;

  return BGP_CLEAR_SOFT_NONE;
}

int
bgp_clear_all (struct vty *vty, struct vty_arg *args[])
{
  afi_t afi;
  safi_t safi;
  const char *view;
  struct bgp *bgp;
  enum bgp_clear_type stype;
  struct peer *peer;
  struct listnode *node;
  int ret;

  if (vty_get_arg_afi_safi (vty, args, &afi, &safi) < 0)
    return CMD_WARNING;
  view = vty_get_arg_value (args, "view");
  bgp = vty_bgp_get (vty, view);
  if (! bgp)
    return CMD_WARNING;
  stype = bgp_clear_type (args);

  for (ALL_LIST_ELEMENTS_RO (bgp->peer, node, peer))
    {
      if (stype == BGP_CLEAR_SOFT_NONE)
	ret = peer_clear (peer);
      else
	ret = peer_clear_soft (peer, afi, safi, stype);

      if (ret < 0 && ret != BGP_ERR_AF_UNCONFIGURED)
	bgp_clear_vty_error (vty, peer, afi, safi, ret);
    }

  return CMD_SUCCESS;
}

int
bgp_clear_asn (struct vty *vty, struct vty_arg *args[])
{
  afi_t afi;
  safi_t safi;
  const char *view;
  struct bgp *bgp;
  const char *as_str;
  enum bgp_clear_type stype;
  struct peer *peer;
  struct listnode *node;
  as_t as;
  int find = 0;
  int ret;

  if (vty_get_arg_afi_safi (vty, args, &afi, &safi) < 0)
    return CMD_WARNING;
  view = vty_get_arg_value (args, "view");
  bgp = vty_bgp_get (vty, view);
  if (! bgp)
    return CMD_WARNING;
  stype = bgp_clear_type (args);
  as_str = vty_get_arg_value (args, "asn");

  VTY_GET_INTEGER_RANGE ("AS", as, as_str, 1, BGP_AS4_MAX);

  for (ALL_LIST_ELEMENTS_RO (bgp->peer, node, peer))
    {
      if (peer->as != as)
	continue;

      find = 1;
      if (stype == BGP_CLEAR_SOFT_NONE)
	ret = peer_clear (peer);
      else
	ret = peer_clear_soft (peer, afi, safi, stype);

      if (ret < 0 && ret != BGP_ERR_AF_UNCONFIGURED)
	bgp_clear_vty_error (vty, peer, afi, safi, ret);
    }
  if (! find)
    vty_out (vty, "%% BGP: No peer is configured with AS %s%s", as_str,
	     VTY_NEWLINE);

  return CMD_SUCCESS;
}

int
bgp_clear_neighbor (struct vty *vty, struct vty_arg *args[])
{
  afi_t afi;
  safi_t safi;
  const char *view;
  struct bgp *bgp;
  const char *addr_str;
  enum bgp_clear_type stype;
  struct peer *peer;
  union sockunion su;
  int ret;

  if (vty_get_arg_afi_safi (vty, args, &afi, &safi) < 0)
    return CMD_WARNING;
  view = vty_get_arg_value (args, "view");
  bgp = vty_bgp_get (vty, view);
  if (! bgp)
    return CMD_WARNING;
  stype = bgp_clear_type (args);
  addr_str = vty_get_arg_value (args, "address");

  /* Make sockunion for lookup. */
  ret = str2sockunion (addr_str, &su);
  if (ret < 0)
    {
      vty_out (vty, "%% Malformed address: %s%s", addr_str, VTY_NEWLINE);
      return CMD_WARNING;
    }
  peer = peer_lookup (bgp, &su);
  if (! peer)
    {
      vty_out (vty, "%% BGP: Unknown neighbor - \"%s\"%s", addr_str, VTY_NEWLINE);
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

int
bgp_clear_external (struct vty *vty, struct vty_arg *args[])
{
  afi_t afi;
  safi_t safi;
  const char *view;
  struct bgp *bgp;
  enum bgp_clear_type stype;
  struct peer *peer;
  struct listnode *node;
  int ret;

  if (vty_get_arg_afi_safi (vty, args, &afi, &safi) < 0)
    return CMD_WARNING;
  view = vty_get_arg_value (args, "view");
  bgp = vty_bgp_get (vty, view);
  if (! bgp)
    return CMD_WARNING;
  stype = bgp_clear_type (args);

  for (ALL_LIST_ELEMENTS_RO (bgp->peer, node, peer))
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

int
bgp_clear_peer_group (struct vty *vty, struct vty_arg *args[])
{
  afi_t afi;
  safi_t safi;
  const char *view;
  struct bgp *bgp;
  const char *group_str;
  enum bgp_clear_type stype;
  struct peer *peer;
  struct listnode *node;
  struct peer_group *group;
  int ret;

  if (vty_get_arg_afi_safi (vty, args, &afi, &safi) < 0)
    return CMD_WARNING;
  view = vty_get_arg_value (args, "view");
  bgp = vty_bgp_get (vty, view);
  if (! bgp)
    return CMD_WARNING;
  stype = bgp_clear_type (args);
  group_str = vty_get_arg_value (args, "peer_group");

  group = peer_group_lookup (bgp, group_str);
  if (! group)
    {
      vty_out (vty, "%% BGP: No such peer-group %s%s", group_str, VTY_NEWLINE);
      return CMD_WARNING;
    }

  for (ALL_LIST_ELEMENTS_RO (group->peer, node, peer))
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

int
bgp_clear_dampening (struct vty *vty, struct vty_arg *args[])
{
  afi_t afi;
  safi_t safi;
  const char *view;
  struct bgp *bgp;
  const char *prefix_str;
  const char *network_str;
  struct prefix match;
  struct bgp_node *rn;
  struct bgp_info *ri;
  struct bgp_info *ri_temp;
  int ret;

  if (vty_get_arg_afi_safi (vty, args, &afi, &safi) < 0)
    return CMD_WARNING;
  view = vty_get_arg_value (args, "view");
  bgp = vty_bgp_get (vty, view);
  if (! bgp)
    return CMD_WARNING;

  prefix_str = vty_get_arg_value (args, "prefix");
  network_str = vty_get_arg_value (args, "network");
  if (! prefix_str && ! network_str)
    {
      bgp_damp_info_clean ();
      return CMD_SUCCESS;
    }

  /* Check IP address argument. */
  ret = str2prefix (prefix_str ? prefix_str : network_str, &match);
  if (! ret)
    {
      vty_out (vty, "%% address is malformed%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  match.family = afi2family (afi);

  if ((rn = bgp_node_match (bgp->rib[afi][safi], &match)) != NULL)
    {
      if (network_str || rn->p.prefixlen == match.prefixlen)
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

  return CMD_SUCCESS;
}
