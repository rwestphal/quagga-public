/*
 * MPLS CLI for zebra daemon.
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

#include "vty.h"
#include "linklist.h"
#include "prefix.h"
#include "memory.h"
#include "command.h"

#include "zebra/interface.h"
#include "zebra/mpls_lib.h"

static int
vty_get_prefix (struct vty *vty, const char *prefix_str, const char *mask_str,
                struct prefix *p)
{
  struct in_addr mask;

  if (str2prefix (prefix_str, p) <= 0)
    {
      vty_out (vty, "%% Malformed address%s", VTY_NEWLINE);
      return -1;
    }

  if (mask_str)
    {
      if (inet_aton (mask_str, &mask) == 0)
        {
          vty_out (vty, "%% Malformed address%s", VTY_NEWLINE);
          return -1;
        }
      p->prefixlen = ip_masklen (mask);
    }

  /* Apply mask for given prefix. */
  apply_mask (p);

  return 0;
}

static const char *
vty_label_str (uint32_t label, char *str, int brief)
{
  if (label == MPLS_IMPLICIT_NULL)
    {
      if (brief)
        strcpy (str, "imp-null");
      else
        strcpy (str, "implicit-null");
    }
  else if (label == MPLS_IPV4_EXPLICIT_NULL)
    {
      if (brief)
        strcpy (str, "exp-null");
      else
        strcpy (str, "explicit-null");
    }
  else
    sprintf (str, "%u", label);

  return str;
}

static uint32_t
vty_label_value (const char *label_str)
{
  if (strcmp (label_str, "explicit-null") == 0)
    return MPLS_IPV4_EXPLICIT_NULL;
  else if (strcmp (label_str, "implicit-null") == 0)
    return MPLS_IMPLICIT_NULL;

  return strtoul (label_str, NULL, 10);
}

static int
vty_mpls_static_binding_input (struct vty *vty, int add_cmd, const char *prefix_str,
                               const char *mask_str, const char *label_str)
{
  struct prefix p;
  struct route_node *rn;
  struct label_bindings *lb;
  uint32_t label = 0;

  if (vty_get_prefix (vty, prefix_str, mask_str, &p) < 0)
    return CMD_WARNING;
  if (label_str)
    label = vty_label_value (label_str);

  rn = route_node_get_mpls (&p);
  lb = rn->mpls;

  if (add_cmd && lb->static_in_label != label)
    mpls_prefix_set_static_input_label (&p, label);
  else if (! add_cmd && lb->static_in_label != NO_LABEL)
    {
      if (! label_str || lb->static_in_label == label)
        mpls_prefix_set_static_input_label (&p, NO_LABEL);
    }

  return CMD_SUCCESS;
}

static int
vty_mpls_static_binding_output (struct vty *vty, int add_cmd, const char *prefix_str,
                                const char *mask_str, const char *nexthop_str,
                                const char *label_str)
{
  struct prefix p;
  struct in_addr nexthop;

  if (vty_get_prefix (vty, prefix_str, mask_str, &p) < 0)
    return CMD_WARNING;

  if (inet_aton (nexthop_str, &nexthop) == 0)
    {
      vty_out (vty, "%% Malformed address%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  if (add_cmd)
    mpls_prefix_add_lsp (MPLS_LSP_STATIC, &p, nexthop,
			 vty_label_value (label_str));
  else
    mpls_prefix_remove_lsp (MPLS_LSP_STATIC, &p, nexthop);

  return CMD_SUCCESS;
}

/* Remove all static LSPs for the given prefix.  */
static int
vty_mpls_static_binding_output_remove_all (struct vty *vty,
                                           const char *prefix_str,
                                           const char *mask_str)
{
  struct prefix p;
  struct route_node *rn;
  struct label_bindings *lb;
  struct mpls_lsp *lsp;
  struct listnode *node, *nnode;

  if (vty_get_prefix (vty, prefix_str, mask_str, &p) < 0)
    return CMD_WARNING;

  rn = route_node_get_mpls (&p);
  lb = rn->mpls;

  for (ALL_LIST_ELEMENTS (lb->static_lsps, node, nnode, lsp))
    mpls_prefix_remove_lsp (MPLS_LSP_STATIC, &p, lsp->addr);

  return CMD_SUCCESS;
}

/* "mpls ip" commands.  */
DEFUN (mpls_ip,
       mpls_ip_cmd,
       "mpls ip",
       "Configure MPLS parameters\n"
       "Dynamic MPLS forwarding for IP\n")
{
  struct listnode *node;
  struct interface *ifp;
  struct zebra_if *zebra_if;

  if (mpls_enabled)
    return CMD_SUCCESS;

  for (ALL_LIST_ELEMENTS_RO (iflist, node, ifp))
    {
      zebra_if = ifp->info;
      if (zebra_if->mpls_enabled)
	mpls_kernel_enable_interface (ifp);
    }

  mpls_enabled = 1;
  mpls_lib_update ();

  return CMD_SUCCESS;
}

DEFUN (no_mpls_ip,
       no_mpls_ip_cmd,
       "no mpls ip",
       NO_STR
       "Configure MPLS parameters\n"
       "Dynamic MPLS forwarding for IP\n")
{
  struct listnode *node;
  struct interface *ifp;
  struct zebra_if *zebra_if;

  if (! mpls_enabled)
    return CMD_SUCCESS;

  mpls_enabled = 0;
  mpls_lib_update ();

  for (ALL_LIST_ELEMENTS_RO (iflist, node, ifp))
    {
      zebra_if = ifp->info;
      if (zebra_if->mpls_enabled)
	mpls_kernel_disable_interface (ifp);
    }

  return CMD_SUCCESS;
}

/* "mpls static binding ipv4 A.B.C.D A.B.C.D input" commands.  */
DEFUN (mpls_static_binding_input,
       mpls_static_binding_input_cmd,
       "mpls static binding ipv4 A.B.C.D/M input <16-1048575>",
       "Configure MPLS parameters\n"
       "MPLS static applications\n"
       "Establish static label bindings\n"
       "Bind IPv4 destination with label\n"
       "Destination prefix (e.g. 10.0.0.0/8)\n"
       "Incoming (local) label\n"
       "Label Value\n")
{
  return vty_mpls_static_binding_input (vty, 1, argv[0], NULL, argv[1]);
}

ALIAS (mpls_static_binding_input,
       mpls_static_binding_input_implicit_cmd,
       "mpls static binding ipv4 A.B.C.D/M <16-1048575>",
       "Configure MPLS parameters\n"
       "MPLS static applications\n"
       "Establish static label bindings\n"
       "Bind IPv4 destination with label\n"
       "Destination prefix (e.g. 10.0.0.0/8)\n"
       "Label Value\n")

DEFUN (no_mpls_static_binding_input_label,
       no_mpls_static_binding_input_label_cmd,
       "no mpls static binding ipv4 A.B.C.D/M input <16-1048575>",
       NO_STR
       "Configure MPLS parameters\n"
       "MPLS static applications\n"
       "Establish static label bindings\n"
       "Bind IPv4 destination with label\n"
       "Destination prefix (e.g. 10.0.0.0/8)\n"
       "Incoming (local) label\n"
       "Label Value\n")
{
  return vty_mpls_static_binding_input (vty, 0, argv[0], NULL, argv[1]);
}

ALIAS (no_mpls_static_binding_input_label,
       no_mpls_static_binding_input_implicit_cmd,
       "no mpls static binding ipv4 A.B.C.D/M <16-1048575>",
       NO_STR
       "Configure MPLS parameters\n"
       "MPLS static applications\n"
       "Establish static label bindings\n"
       "Bind IPv4 destination with label\n"
       "Destination prefix (e.g. 10.0.0.0/8)\n"
       "Incoming (local) label\n"
       "Label Value\n")

DEFUN (no_mpls_static_binding_input,
       no_mpls_static_binding_input_cmd,
       "no mpls static binding ipv4 A.B.C.D/M input",
       NO_STR
       "Configure MPLS parameters\n"
       "MPLS static applications\n"
       "Establish static label bindings\n"
       "Bind IPv4 destination with label\n"
       "Destination prefix (e.g. 10.0.0.0/8)\n"
       "Incoming (local) label\n"
       "Label Value\n")
{
  return vty_mpls_static_binding_input (vty, 0, argv[0], NULL, NULL);
}

DEFUN (mpls_static_binding_mask_input,
       mpls_static_binding_mask_input_cmd,
       "mpls static binding ipv4 A.B.C.D A.B.C.D input <16-1048575>",
       "Configure MPLS parameters\n"
       "MPLS static applications\n"
       "Establish static label bindings\n"
       "Bind IPv4 destination with label\n"
       "Destination prefix\n"
       "Destination prefix mask\n"
       "Incoming (local) label\n"
       "Label Value\n")
{
  return vty_mpls_static_binding_input (vty, 1, argv[0], argv[1], argv[2]);
}

ALIAS (mpls_static_binding_mask_input,
       mpls_static_binding_mask_input_implicit_cmd,
       "mpls static binding ipv4 A.B.C.D A.B.C.D <16-1048575>",
       "Configure MPLS parameters\n"
       "MPLS static applications\n"
       "Establish static label bindings\n"
       "Bind IPv4 destination with label\n"
       "Destination prefix\n"
       "Destination prefix mask\n"
       "Label Value\n")

DEFUN (no_mpls_static_binding_mask_input_label,
       no_mpls_static_binding_mask_input_label_cmd,
       "no mpls static binding ipv4 A.B.C.D A.B.C.D input <16-1048575>",
       NO_STR
       "Configure MPLS parameters\n"
       "MPLS static applications\n"
       "Establish static label bindings\n"
       "Bind IPv4 destination with label\n"
       "Destination prefix\n"
       "Destination prefix mask\n"
       "Incoming (local) label\n"
       "Label Value\n")
{
  return vty_mpls_static_binding_input (vty, 0, argv[0], argv[1], argv[2]);
}

ALIAS (no_mpls_static_binding_mask_input_label,
       no_mpls_static_binding_mask_input_implicit_cmd,
       "no mpls static binding ipv4 A.B.C.D A.B.C.D <16-1048575>",
       NO_STR
       "Configure MPLS parameters\n"
       "MPLS static applications\n"
       "Establish static label bindings\n"
       "Bind IPv4 destination with label\n"
       "Destination prefix\n"
       "Destination prefix mask\n"
       "Incoming (local) label\n"
       "Label Value\n")

DEFUN (no_mpls_static_binding_mask_input,
       no_mpls_static_binding_mask_input_cmd,
       "no mpls static binding ipv4 A.B.C.D A.B.C.D input",
       NO_STR
       "Configure MPLS parameters\n"
       "MPLS static applications\n"
       "Establish static label bindings\n"
       "Bind IPv4 destination with label\n"
       "Destination prefix\n"
       "Destination prefix mask\n"
       "Incoming (local) label\n"
       "Label Value\n")
{
  return vty_mpls_static_binding_input (vty, 0, argv[0], argv[1], NULL);
}

/* "mpls static binding ipv4 A.B.C.D A.B.C.D output" commands.  */
DEFUN (mpls_static_binding_output,
       mpls_static_binding_output_cmd,
       "mpls static binding ipv4 A.B.C.D/M output A.B.C.D (<16-1048575>|explicit-null|implicit-null)",
       "Configure MPLS parameters\n"
       "MPLS static applications\n"
       "Establish static label bindings\n"
       "Bind IPv4 destination with label\n"
       "Destination prefix (e.g. 10.0.0.0/8)\n"
       "Outgoing (remote) label\n"
       "Destination next hop\n"
       "Label Value\n"
       "IETF MPLS IPv4 explicit null label (0)\n"
       "IETF MPLS implicit null label (3)\n")
{
  return vty_mpls_static_binding_output (vty, 1, argv[0], NULL, argv[1], argv[2]);
}

DEFUN (no_mpls_static_binding_output,
       no_mpls_static_binding_output_cmd,
       "no mpls static binding ipv4 A.B.C.D/M output A.B.C.D (<16-1048575>|explicit-null|implicit-null)",
       NO_STR
       "Configure MPLS parameters\n"
       "MPLS static applications\n"
       "Establish static label bindings\n"
       "Bind IPv4 destination with label\n"
       "Destination prefix (e.g. 10.0.0.0/8)\n"
       "Outgoing (remote) label\n"
       "Destination next hop\n"
       "Label Value\n"
       "IETF MPLS IPv4 explicit null label (0)\n"
       "IETF MPLS implicit null label (3)\n")
{
  /* The label value is ignored, the next hop address is enough to identify
     the correct LSP.  */
  return vty_mpls_static_binding_output (vty, 0, argv[0], NULL, argv[1], NULL);
}

DEFUN (no_mpls_static_binding_output2,
       no_mpls_static_binding_output2_cmd,
       "no mpls static binding ipv4 A.B.C.D/M output A.B.C.D",
       NO_STR
       "Configure MPLS parameters\n"
       "MPLS static applications\n"
       "Establish static label bindings\n"
       "Bind IPv4 destination with label\n"
       "Destination prefix (e.g. 10.0.0.0/8)\n"
       "Outgoing (remote) label\n"
       "Destination next hop\n")
{
  return vty_mpls_static_binding_output (vty, 0, argv[0], NULL, argv[1], NULL);
}

DEFUN (no_mpls_static_binding_output3,
       no_mpls_static_binding_output3_cmd,
       "no mpls static binding ipv4 A.B.C.D/M output",
       NO_STR
       "Configure MPLS parameters\n"
       "MPLS static applications\n"
       "Establish static label bindings\n"
       "Bind IPv4 destination with label\n"
       "Destination prefix (e.g. 10.0.0.0/8)\n"
       "Outgoing (remote) label\n")
{
  return vty_mpls_static_binding_output_remove_all (vty, argv[0], NULL);
}

DEFUN (no_mpls_static_binding,
       no_mpls_static_binding_cmd,
       "no mpls static binding ipv4 A.B.C.D/M",
       NO_STR
       "Configure MPLS parameters\n"
       "MPLS static applications\n"
       "Establish static label bindings\n"
       "Bind IPv4 destination with label\n"
       "Destination prefix (e.g. 10.0.0.0/8)\n")
{
  int ret1;
  int ret2;

  ret1 = vty_mpls_static_binding_input (vty, 0, argv[0], NULL, NULL);
  ret2 = vty_mpls_static_binding_output_remove_all (vty, argv[0], NULL);

  if (ret1 == CMD_SUCCESS && ret2 == CMD_SUCCESS)
    return CMD_SUCCESS;
  else
    return CMD_WARNING;
}

DEFUN (mpls_static_binding_mask_output,
       mpls_static_binding_mask_output_cmd,
       "mpls static binding ipv4 A.B.C.D A.B.C.D output A.B.C.D (<16-1048575>|explicit-null|implicit-null)",
       "Configure MPLS parameters\n"
       "MPLS static applications\n"
       "Establish static label bindings\n"
       "Bind IPv4 destination with label\n"
       "Destination prefix\n"
       "Destination prefix mask\n"
       "Outgoing (remote) label\n"
       "Destination next hop\n"
       "Label Value\n"
       "IETF MPLS IPv4 explicit null label (0)\n"
       "IETF MPLS implicit null label (3)\n")
{
  return vty_mpls_static_binding_output (vty, 1, argv[0], argv[1], argv[2], argv[3]);
}

DEFUN (no_mpls_static_binding_mask_output,
       no_mpls_static_binding_mask_output_cmd,
       "no mpls static binding ipv4 A.B.C.D A.B.C.D output A.B.C.D (<16-1048575>|explicit-null|implicit-null)",
       NO_STR
       "Configure MPLS parameters\n"
       "MPLS static applications\n"
       "Establish static label bindings\n"
       "Bind IPv4 destination with label\n"
       "Destination prefix\n"
       "Destination prefix mask\n"
       "Outgoing (remote) label\n"
       "Destination next hop\n"
       "Label Value\n"
       "IETF MPLS IPv4 explicit null label (0)\n"
       "IETF MPLS implicit null label (3)\n")
{
  /* The label value is ignored, the next hop address is enough to identify
     the correct LSP.  */
  return vty_mpls_static_binding_output (vty, 0, argv[0], argv[1], argv[2], NULL);
}

DEFUN (no_mpls_static_binding_mask_output2,
       no_mpls_static_binding_mask_output2_cmd,
       "no mpls static binding ipv4 A.B.C.D A.B.C.D output A.B.C.D",
       NO_STR
       "Configure MPLS parameters\n"
       "MPLS static applications\n"
       "Establish static label bindings\n"
       "Bind IPv4 destination with label\n"
       "Destination prefix\n"
       "Destination prefix mask\n"
       "Outgoing (remote) label\n"
       "Destination next hop\n")
{
  return vty_mpls_static_binding_output (vty, 0, argv[0], argv[1], argv[2], NULL);
}

DEFUN (no_mpls_static_binding_mask_output3,
       no_mpls_static_binding_mask_output3_cmd,
       "no mpls static binding ipv4 A.B.C.D A.B.C.D output",
       NO_STR
       "Configure MPLS parameters\n"
       "MPLS static applications\n"
       "Establish static label bindings\n"
       "Bind IPv4 destination with label\n"
       "Destination prefix\n"
       "Destination prefix mask\n"
       "Outgoing (remote) label\n")
{
  return vty_mpls_static_binding_output_remove_all (vty, argv[0], argv[1]);
}

DEFUN (no_mpls_static_binding_mask,
       no_mpls_static_binding_mask_cmd,
       "no mpls static binding ipv4 A.B.C.D A.B.C.D",
       NO_STR
       "Configure MPLS parameters\n"
       "MPLS static applications\n"
       "Establish static label bindings\n"
       "Bind IPv4 destination with label\n"
       "Destination prefix\n"
       "Destination prefix mask\n")
{
  int ret1;
  int ret2;

  ret1 = vty_mpls_static_binding_input (vty, 0, argv[0], argv[1], NULL);
  ret2 = vty_mpls_static_binding_output_remove_all (vty, argv[0], argv[1]);

  if (ret1 == CMD_SUCCESS && ret2 == CMD_SUCCESS)
    return CMD_SUCCESS;

  return CMD_WARNING;
}

/* "show mpls" commands.  */
#define SHOW_MPLS_FORWARDING_HEADER \
  "Local  Outgoing    Prefix            Outgoing   Next Hop%s" \
  "label  label       or Tunnel Id      interface%s"

DEFUN (show_mpls_forwarding_table,
       show_mpls_forwarding_table_cmd,
       "show mpls forwarding-table",
       SHOW_STR
       "MPLS information\n"
       "Show the Label Forwarding Table\n")
{
  struct route_table *table;
  struct route_node *rn;
  struct label_bindings *lb;
  struct listnode *node;
  struct mpls_lsp *lsp;
  char prefix_buf[64];
  int first = 1;

  table = vrf_table (AFI_IP, SAFI_UNICAST, 0);
  if (! table)
    return CMD_WARNING;

  for (rn = route_top (table); rn; rn = route_next (rn))
    if (rn->mpls && zebra_route_node_active (rn))
      {
        lb = rn->mpls;
        if (lb && lb->selected_in_label != NO_LABEL
	    && lb->selected_in_label != MPLS_IMPLICIT_NULL)
	  {
	    if (first)
	      vty_out (vty, SHOW_MPLS_FORWARDING_HEADER, VTY_NEWLINE,
		       VTY_NEWLINE);
	    first = 0;

	    prefix2str (&rn->p, prefix_buf, sizeof (prefix_buf));
            vty_out (vty, "%-7u", lb->selected_in_label);

	    for  (ALL_LIST_ELEMENTS_RO (lb->selected_lsps, node, lsp))
	      {
		if (lsp->remote_label == MPLS_IMPLICIT_NULL)
		  vty_out (vty, "%-12s", "Pop");
		else
		  vty_out (vty, "%-12u", lsp->remote_label);
		vty_out (vty, "%-18s", prefix_buf);
		vty_out (vty, "%-11s", lsp->ifp->name);
		vty_out (vty, "%s%s", inet_ntoa (lsp->addr), VTY_NEWLINE);
		if (node->next)
		  vty_out (vty, "%-7s", "");
	      }

	    if (list_isempty (lb->selected_lsps))
	      {
                vty_out (vty, "%-12s", "No Label");
                vty_out (vty, "%-18s", prefix_buf);
                vty_out (vty, "%-11s", "-");
                vty_out (vty, "%s%s", "-", VTY_NEWLINE);
	      }
         }
      }

  return CMD_SUCCESS;
}

DEFUN (show_mpls_ip_binding_table,
       show_mpls_ip_binding_table_cmd,
       "show mpls ip binding",
       SHOW_STR
       "MPLS information\n"
       "MPLS IP information\n"
       "Show the MPLS IP Label Information Base (LIB)\n")
{
  struct route_table *table;
  struct route_node *rn;
  struct label_bindings *lb;
  struct listnode *node;
  struct mpls_lsp *lsp;
  char prefix_buf[64];
  char label_buf[16];

  table = vrf_table (AFI_IP, SAFI_UNICAST, 0);
  if (! table)
    return CMD_WARNING;

  for (rn = route_top (table); rn; rn = route_next (rn))
    if (rn->mpls && zebra_route_node_active (rn))
      {
        lb = rn->mpls;

        if (lb->selected_in_label == NO_LABEL
            && list_isempty(lb->selected_lsps))
          continue;

        prefix2str (&rn->p, prefix_buf, sizeof (prefix_buf));
        vty_out (vty, "  %s%s", prefix_buf, VTY_NEWLINE);

        if (lb->selected_in_label != NO_LABEL)
          vty_out (vty, "        in label:     %s%s",
                   vty_label_str (lb->selected_in_label, label_buf, 1),
                   VTY_NEWLINE);

        for  (ALL_LIST_ELEMENTS_RO (lb->selected_lsps, node, lsp))
          vty_out (vty, "        out label:    %-10slsr: %s:0%s",
                   vty_label_str (lsp->remote_label, label_buf, 1),
                   inet_ntoa (lsp->addr), VTY_NEWLINE);
      }

  return CMD_SUCCESS;
}

DEFUN (show_mpls_static_binding,
       show_mpls_static_binding_cmd,
       "show mpls static binding",
       SHOW_STR
       "MPLS information\n"
       "Show MPLS static information\n"
       "Show static label bindings\n")
{
  struct route_table *table;
  struct route_node *rn;
  struct label_bindings *lb;
  struct mpls_lsp *lsp;
  struct listnode *node;
  char prefix_buf[64];
  char label_buf[16];
  int i = 0;

  table = vrf_table (AFI_IP, SAFI_UNICAST, 0);
  if (! table)
    return CMD_WARNING;

  for (rn = route_top (table); rn; rn = route_next (rn))
    if (rn->mpls)
      {
        lb = rn->mpls;

        if (lb->static_in_label == NO_LABEL && list_isempty (lb->static_lsps))
          continue;

        prefix2str (&rn->p, prefix_buf, sizeof (prefix_buf));
        vty_out (vty, "%s: ", prefix_buf);

        vty_out (vty, "Incoming label: ");
        if (lb->static_in_label != NO_LABEL)
          vty_out (vty, "%u%s", lb->static_in_label, VTY_NEWLINE);
        else
          vty_out (vty, "none;%s", VTY_NEWLINE);

        vty_out (vty, "  Outgoing labels:");
        if (list_isempty (lb->static_lsps))
          vty_out (vty, "  None");
        else
          {
            for (ALL_LIST_ELEMENTS_RO (lb->static_lsps, node, lsp))
              {
                if (i++ % 2 == 0)
                  vty_out (vty, "%s", VTY_NEWLINE);
		else
                  vty_out (vty, "%-5s", "");
                vty_out (vty, "     %-22s%s", inet_ntoa (lsp->addr),
                         vty_label_str(lsp->remote_label, label_buf, 0));
              }
          }
        vty_out (vty, "%s", VTY_NEWLINE);
      }

  return CMD_SUCCESS;
}

/* Write MPLS configuration.  */
static int
mpls_config_write (struct vty *vty)
{
  struct route_table *table;
  struct route_node *rn;
  struct label_bindings *lb;
  struct mpls_lsp *lsp;
  struct listnode *node;
  char prefix_buf[64];
  char label_buf[16];

  /* "mpls ip".  */
  if (! mpls_enabled)
    vty_out (vty, "no mpls ip%s!%s", VTY_NEWLINE, VTY_NEWLINE);

  /* "mpls static binding ipv4".  */
  table = vrf_table (AFI_IP, SAFI_UNICAST, 0);
  if (! table)
    return CMD_WARNING;

  for (rn = route_top (table); rn; rn = route_next (rn))
    if (rn->mpls)
      {
        lb = rn->mpls;

        if (lb->static_in_label == NO_LABEL && list_isempty (lb->static_lsps))
          continue;

        prefix2str (&rn->p, prefix_buf, sizeof (prefix_buf));
        if (lb->static_in_label != NO_LABEL)
          vty_out (vty, "mpls static binding ipv4 %s input %u%s", prefix_buf,
                   lb->static_in_label, VTY_NEWLINE);

        for (ALL_LIST_ELEMENTS_RO (lb->static_lsps, node, lsp))
          vty_out (vty, "mpls static binding ipv4 %s output %s %s%s", prefix_buf,
                   inet_ntoa (lsp->addr),
                   vty_label_str (lsp->remote_label, label_buf, 0), VTY_NEWLINE);
      }

  vty_out (vty, "!%s", VTY_NEWLINE);

  return 0;
}

static
struct cmd_node mpls_node =
{
  MPLS_NODE,
  "",
  1
};

void
mpls_vty_init (void)
{
  /* Install configuration write function. */
  install_node (&mpls_node, mpls_config_write);

  /* "mpls ip" commands.  */
  install_element (CONFIG_NODE, &mpls_ip_cmd);
  install_element (CONFIG_NODE, &no_mpls_ip_cmd);

  /* "mpls static binding ipv4 A.B.C.D A.B.C.D input" commands.  */
  install_element (CONFIG_NODE, &mpls_static_binding_input_cmd);
  install_element (CONFIG_NODE, &mpls_static_binding_input_implicit_cmd);
  install_element (CONFIG_NODE, &no_mpls_static_binding_input_label_cmd);
  install_element (CONFIG_NODE, &no_mpls_static_binding_input_implicit_cmd);
  install_element (CONFIG_NODE, &no_mpls_static_binding_input_cmd);
  install_element (CONFIG_NODE, &mpls_static_binding_mask_input_cmd);
  install_element (CONFIG_NODE, &mpls_static_binding_mask_input_implicit_cmd);
  install_element (CONFIG_NODE, &no_mpls_static_binding_mask_input_label_cmd);
  install_element (CONFIG_NODE, &no_mpls_static_binding_mask_input_implicit_cmd);
  install_element (CONFIG_NODE, &no_mpls_static_binding_mask_input_cmd);

  /* "mpls static binding ipv4 A.B.C.D A.B.C.D output" commands.  */
  install_element (CONFIG_NODE, &mpls_static_binding_output_cmd);
  install_element (CONFIG_NODE, &no_mpls_static_binding_output_cmd);
  install_element (CONFIG_NODE, &no_mpls_static_binding_output2_cmd);
  install_element (CONFIG_NODE, &no_mpls_static_binding_output3_cmd);
  install_element (CONFIG_NODE, &no_mpls_static_binding_cmd);
  install_element (CONFIG_NODE, &mpls_static_binding_mask_output_cmd);
  install_element (CONFIG_NODE, &no_mpls_static_binding_mask_output_cmd);
  install_element (CONFIG_NODE, &no_mpls_static_binding_mask_output2_cmd);
  install_element (CONFIG_NODE, &no_mpls_static_binding_mask_output3_cmd);
  install_element (CONFIG_NODE, &no_mpls_static_binding_mask_cmd);

  /* "show mpls" commands.  */
  install_element (VIEW_NODE, &show_mpls_forwarding_table_cmd);
  install_element (VIEW_NODE, &show_mpls_ip_binding_table_cmd);
  install_element (VIEW_NODE, &show_mpls_static_binding_cmd);
  install_element (ENABLE_NODE, &show_mpls_forwarding_table_cmd);
  install_element (ENABLE_NODE, &show_mpls_ip_binding_table_cmd);
  install_element (ENABLE_NODE, &show_mpls_static_binding_cmd);
}
