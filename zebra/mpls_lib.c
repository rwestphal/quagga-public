/*
 * MPLS Label Information Base for zebra daemon.
 *
 * Copyright (C) 2004 James R. Leu <jleu@mindspring.com>
 * Copyright (C) 2011 Renato Westphal <rwestphal@inf.ufrgs.br>
 *
 * This file is part of Quagga routing suite.
 *
 * Quagga is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2, or (at your option) any
 * later version.
 *
 * Quagga is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Zebra; see the file COPYING.  If not, write to the Free
 * Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 */

#include <zebra.h>

#include "linklist.h"
#include "memory.h"
#include "prefix.h"
#include "if.h"

#include "zebra/rt.h"
#include "zebra/interface.h"
#include "zebra/mpls_lib.h"

int mpls_enabled;
extern struct zebra_t zebrad;

/* LDP and BGP should request MPLS labels to Zebra to avoid conflicts. */
uint32_t
mpls_allocate_local_label (void)
{
#define MPLS_LABEL_RESERVED_MAX 15
#define MPLS_LABEL_MAX		((1 << 20) - 1)
  static uint32_t label = MPLS_LABEL_RESERVED_MAX;

  if (++label > MPLS_LABEL_MAX)
    label = MPLS_LABEL_RESERVED_MAX + 1;

  return label;
}

static int
if_mpls_enabled (struct interface *ifp)
{
  struct zebra_if *zebra_if = ifp->info;
  return zebra_if->mpls_enabled && mpls_enabled;
}

struct route_node *
route_node_get_mpls (struct prefix *p)
{
  struct route_table *table;
  struct route_node *rn;
  struct label_bindings *lb;

  table = vrf_table (AFI_IP, SAFI_UNICAST, 0);
  if (! table)
    return NULL;

  rn = route_node_get (table, p);
  if (! rn->mpls)
    {
      lb = XCALLOC (MTYPE_MPLS_BINDINGS, sizeof (struct label_bindings));
      lb->static_in_label = NO_LABEL;
      lb->ldp_in_label = NO_LABEL;
      lb->selected_in_label = NO_LABEL;
      lb->static_lsps = list_new ();
      lb->ldp_lsps = list_new ();
      lb->selected_lsps = list_new ();
      rn->mpls = lb;
    }

  return rn;
}

static void
route_node_free_mpls (struct route_node *rn)
{
  struct label_bindings *lb;

  lb = rn->mpls;
  if (! lb)
    return;

  /* The three lists below must already be empty. */
  list_free (lb->static_lsps);
  list_free (lb->ldp_lsps);
  list_free (lb->selected_lsps);
  XFREE (MTYPE_MPLS_BINDINGS, rn->mpls);
}

/* Return the selected route of the given IP prefix */
struct rib *
zebra_route_node_active (struct route_node *rn)
{
  struct rib *rib;

  RNODE_FOREACH_RIB (rn, rib)
    if (CHECK_FLAG (rib->flags, ZEBRA_FLAG_SELECTED)
        && rib->distance != DISTANCE_INFINITY)
      return rib;

  return NULL;
}

static void
mpls_install_lsps (struct label_bindings *lb)
{
  struct listnode *node;
  struct mpls_lsp *lsp;

  /* Disconsider FECs with undefined MPLS input label. */
  if (lb->selected_in_label == NO_LABEL)
    return;

  /* Disconsider FECs with Implicit Null as the MPLS input label. */
  if (lb->selected_in_label == MPLS_IMPLICIT_NULL)
    return;

  /* Special case: there's no output label defined for this FEC.
   * When a packet arrives with this FEC's input label, the kernel should
   * remove the packets's MPLS stack and perform a layer-3 lookup. */
  if (list_isempty (lb->selected_lsps))
    {
      if (! lb->no_label_installed &&
	  mpls_kernel_install_ilm (lb->selected_in_label, NULL) >= 0)
	lb->no_label_installed = 1;
      return;
    }

  for (ALL_LIST_ELEMENTS_RO (lb->selected_lsps, node, lsp))
    {
      if (! lsp->installed &&
	  mpls_kernel_install_ilm (lb->selected_in_label, lsp) >= 0)
	lsp->installed = 1;
#ifdef GNU_LINUX
      /* HACK: MPLS-Linux supports multipath only for IP->MPLS bindings. */
      break;
#endif
    }
}

static void
mpls_uninstall_lsps (struct label_bindings *lb)
{
  struct listnode *node;
  struct mpls_lsp *lsp;

  if (lb->selected_in_label == NO_LABEL ||
      lb->selected_in_label == MPLS_IMPLICIT_NULL)
    return;

  if (list_isempty (lb->selected_lsps))
    {
      if (lb->no_label_installed &&
	  mpls_kernel_uninstall_ilm (lb->selected_in_label, NULL) >= 0)
      lb->no_label_installed = 0;
      return;
    }

  for (ALL_LIST_ELEMENTS_RO (lb->selected_lsps, node, lsp))
    if (lsp->installed &&
	mpls_kernel_uninstall_ilm (lb->selected_in_label, lsp) >= 0)
      lsp->installed = 0;
}

static void
mpls_prefix_select_input_label (struct label_bindings *lb, int connected)
{
  /* The static assigned input label takes precedence against
   * the LDP assigned input label.
   * It shouldn't be possible to assign static input labels for
   * connected prefixes to guarantee PHP behavior. */
  if (lb->static_in_label != NO_LABEL && !connected)
    lb->selected_in_label = lb->static_in_label;
  else if (lb->ldp_in_label != NO_LABEL)
    lb->selected_in_label = lb->ldp_in_label;
  else
    lb->selected_in_label = NO_LABEL;
}

static void
mpls_prefix_update_input_label (struct route_node *rn)
{
  struct rib *rib;
  struct label_bindings *lb;

  rib = zebra_route_node_active (rn);
  lb = rn->mpls;
  if (rib)
    mpls_uninstall_lsps (lb);

  mpls_prefix_select_input_label (lb, rib && RIB_SYSTEM_ROUTE (rib));

  /* Update LFIB. */
  if (rib)
    mpls_install_lsps (lb);

  /* Free mpls information if possible */
  if (lb->static_in_label == NO_LABEL &&
      lb->ldp_in_label == NO_LABEL &&
      list_isempty (lb->static_lsps) && list_isempty (lb->ldp_lsps))
    route_node_free_mpls (rn);
}

/* Set the static input label for a given IP prefix.  */
void
mpls_prefix_set_static_input_label (struct prefix *p, uint32_t label)
{
  struct route_node *rn;
  struct label_bindings *lb;
  struct listnode *node;
  struct zserv *client;

  rn = route_node_get_mpls (p);
  lb = rn->mpls;
  lb->static_in_label = label;
  mpls_prefix_update_input_label (rn);

  /* LDP should use the static local binding.  */
  for (ALL_LIST_ELEMENTS_RO (zebrad.client_list, node, client))
    if (client->redist_mpls)
      zsend_prefix_in_label (client, rn);
}

/* Set the LDP input label for a given IP prefix.  */
void
mpls_prefix_set_ldp_input_label (struct prefix *p, uint32_t label)
{
  struct route_node *rn;
  struct label_bindings *lb;

  rn = route_node_get_mpls (p);
  lb = rn->mpls;
  lb->ldp_in_label = label;
  mpls_prefix_update_input_label (rn);
}

/* Choose the valid MPLS LSPs for the given IP prefix.  */
static void
mpls_prefix_update_lsps (struct route_node *rn)
{
  struct label_bindings *lb;
  struct rib *rib;
  struct nexthop *nexthop;
  struct listnode *node;
  struct mpls_lsp *lsp;
  struct in_addr addr;

  lb = rn->mpls;
  if (! lb)
    return;

  rib = zebra_route_node_active (rn);
  if (! rib)
    return;

  mpls_uninstall_lsps (lb);

  /* Update input label (this is necessary to handle changes in the selected
   * route type to or from connected - very unusual but possible). */
  mpls_prefix_select_input_label (lb, rib && RIB_SYSTEM_ROUTE (rib));

  /* Update list of selected lsps. */
  list_delete_all_node (lb->selected_lsps);
  for (nexthop = rib->nexthop; nexthop; nexthop = nexthop->next)
    {
      if (! CHECK_FLAG (nexthop->flags, NEXTHOP_FLAG_ACTIVE))
	continue;

      if (! CHECK_FLAG (nexthop->flags, NEXTHOP_FLAG_RECURSIVE) &&
	  (nexthop->type == NEXTHOP_TYPE_IPV4 ||
	   nexthop->type == NEXTHOP_TYPE_IPV4_IFINDEX ||
	   nexthop->type == NEXTHOP_TYPE_IPV4_IFNAME))
	addr.s_addr = nexthop->gate.ipv4.s_addr;
      else if (CHECK_FLAG (nexthop->flags, NEXTHOP_FLAG_RECURSIVE) &&
	       (nexthop->rtype == NEXTHOP_TYPE_IPV4 ||
		nexthop->rtype == NEXTHOP_TYPE_IPV4_IFINDEX ||
		nexthop->rtype == NEXTHOP_TYPE_IPV4_IFNAME))
	addr.s_addr = nexthop->rgate.ipv4.s_addr;
      else
	continue;

      /* LDP LSPs take precedence against static LSPs */
      for (ALL_LIST_ELEMENTS_RO (lb->ldp_lsps, node, lsp))
	if (lsp->addr.s_addr == addr.s_addr)
	  {
	    lsp->ifp = if_lookup_address (lsp->addr);
	    if (!lsp->ifp || !if_mpls_enabled (lsp->ifp))
	      continue;

	    nexthop->lsp = lsp;
	    listnode_add (lb->selected_lsps, lsp);
	    goto nexthop_next;
	  }
      for (ALL_LIST_ELEMENTS_RO (lb->static_lsps, node, lsp))
	if (lsp->addr.s_addr == addr.s_addr)
	  {
	    lsp->ifp = if_lookup_address (lsp->addr);
	    if (!lsp->ifp || !if_mpls_enabled (lsp->ifp))
	      continue;

	    nexthop->lsp = lsp;
	    listnode_add (lb->selected_lsps, lsp);
	    goto nexthop_next;
	  }
      nexthop->lsp = NULL;

nexthop_next:;
    }

  /* Update LFIB/FIB */
  mpls_install_lsps (lb);
  kernel_change_ipv4 (&rn->p, rib);
}

/* Add a static MPLS LSP for a given IP prefix.  */
void
mpls_prefix_add_lsp (enum mpls_lsp_t type, struct prefix *p,
		     struct in_addr nexthop, uint32_t label)
{
  struct route_node *rn;
  struct label_bindings *lb;
  struct mpls_lsp *lsp;
  struct list *lsp_list = NULL;
  struct listnode *node, *nnode;

  rn = route_node_get_mpls (p);
  lb = rn->mpls;

  switch (type)
    {
    case MPLS_LSP_STATIC:
      lsp_list = lb->static_lsps;
      break;
    case MPLS_LSP_LDP:
      lsp_list = lb->ldp_lsps;
      break;
    }

  /* For each prefix/nexhop combination, there must be only
     one MPLS output label.  */
  for (ALL_LIST_ELEMENTS (lsp_list, node, nnode, lsp))
    if (lsp->addr.s_addr == nexthop.s_addr)
      {
        /* If this LSP already exists, then return.  */
        if (lsp->remote_label == label)
          return;

        /* Remove previous LSP.  */
	mpls_prefix_remove_lsp (type, p, nexthop);
	break;
      }

  /* Create MPLS LSP.  */
  lsp = XCALLOC (MTYPE_MPLS_LSP, sizeof (struct mpls_lsp));
  lsp->addr = nexthop;
  lsp->remote_label = label;
  listnode_add (lsp_list, lsp);

  mpls_prefix_update_lsps (rn);
}

/* Remove a static MPLS LSP for a given IP prefix.  */
void
mpls_prefix_remove_lsp (enum mpls_lsp_t type, struct prefix *p,
			struct in_addr nexthop)
{
  struct route_node *rn;
  struct label_bindings *lb;
  struct mpls_lsp *lsp;
  struct list *lsp_list = NULL;
  struct listnode *node;

  rn = route_node_get_mpls (p);
  lb = rn->mpls;

  switch (type)
    {
    case MPLS_LSP_STATIC:
      lsp_list = lb->static_lsps;
      break;
    case MPLS_LSP_LDP:
      lsp_list = lb->ldp_lsps;
      break;
    }

  for (ALL_LIST_ELEMENTS_RO (lsp_list, node, lsp))
    if (lsp->addr.s_addr == nexthop.s_addr)
      break;
  if (! lsp)
    return;

  listnode_delete (lsp_list, lsp);
  mpls_prefix_update_lsps (rn);
  XFREE (MTYPE_MPLS_LSP, lsp);

  /* Free mpls information if possible */
  if (lb->static_in_label == NO_LABEL &&
      lb->ldp_in_label == NO_LABEL &&
      list_isempty (lb->static_lsps) && list_isempty (lb->ldp_lsps))
    route_node_free_mpls (rn);
}

/* Hook function called after a route is installed.  */
void
mpls_route_install_hook (struct route_node *rn)
{
  mpls_prefix_update_lsps (rn);
}

/* Hook function called after a route is uninstalled.  */
void
mpls_route_uninstall_hook (struct route_node *rn)
{
  struct label_bindings *lb;

  lb = rn->mpls;
  if (! lb)
    return;

  mpls_uninstall_lsps (lb);
}

void
mpls_lib_update (void)
{
  struct route_node *rn;
  struct route_table *table;

  table = vrf_table (AFI_IP, SAFI_UNICAST, 0);
  if (table)
    for (rn = route_top (table); rn; rn = route_next (rn))
      mpls_prefix_update_lsps (rn);
}

/* Initialize global data structures.  */
void
mpls_init (void)
{
  mpls_enabled = 1;
}

/* Clear all created MPLS LSPs.  */
void
mpls_close (void)
{
  struct route_table *table;
  struct route_node *rn;
  struct label_bindings *lb;
  struct listnode *node, *nnode;
  struct mpls_lsp *lsp;

  /* Remove all installed MPLS IP bindings.  */
  table = vrf_table (AFI_IP, SAFI_UNICAST, 0);
  if (table)
    for (rn = route_top (table); rn; rn = route_next (rn))
      if (rn->mpls)
	{
	  struct rib *rib;
	  struct nexthop *nexthop;

	  rib = zebra_route_node_active (rn);
	  if (! rib)
	    continue;

	  lb = rn->mpls;

	  /* Remove IP->MPLS bindings. */
	  for (nexthop = rib->nexthop; nexthop; nexthop = nexthop->next)
	    nexthop->lsp = NULL;
	  kernel_change_ipv4 (&rn->p, rib);

	  /* Remove MPLS->MPLS mappings. */
	  mpls_uninstall_lsps (lb);
	  list_delete_all_node (lb->selected_lsps);
	  for (ALL_LIST_ELEMENTS (lb->static_lsps, node, nnode, lsp))
	    {
	      listnode_delete (lb->static_lsps, lsp);
	      XFREE (MTYPE_MPLS_LSP, lsp);
	    }
	  for (ALL_LIST_ELEMENTS (lb->ldp_lsps, node, nnode, lsp))
	    {
	      listnode_delete (lb->ldp_lsps, lsp);
	      XFREE (MTYPE_MPLS_LSP, lsp);
	    }

	  route_node_free_mpls (rn);
	}

  /* Close netlink/route sockets.  */
  mpls_kernel_exit ();
}
