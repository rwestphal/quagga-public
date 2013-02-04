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

#ifndef _ZEBRA_MPLS_LIB_H
#define _ZEBRA_MPLS_LIB_H

#include "prefix.h"
#include "if.h"

#define NO_LABEL UINT_MAX
#define MPLS_IPV4_EXPLICIT_NULL 0
#define MPLS_IMPLICIT_NULL      3

enum mpls_lsp_t
{
  MPLS_LSP_STATIC,
  MPLS_LSP_LDP
};

struct mpls_lsp
{
  struct interface *ifp;
  struct in_addr addr;
  uint32_t remote_label;
  int installed;
};

struct label_bindings
{
  uint32_t static_in_label;
  uint32_t ldp_in_label;
  uint32_t selected_in_label;
  struct list *static_lsps;
  struct list *ldp_lsps;
  struct list *selected_lsps;
  int no_label_installed;
};

/* mpls_lib.c */
extern int mpls_enabled;

extern void mpls_init (void);
extern void mpls_close (void);

extern uint32_t mpls_allocate_local_label (void);
extern struct route_node *route_node_get_mpls (struct prefix *);
extern struct rib *zebra_route_node_active (struct route_node *rn);

extern void mpls_prefix_set_static_input_label (struct prefix *, uint32_t label);
extern void mpls_prefix_set_ldp_input_label (struct prefix *p, uint32_t label);

extern void mpls_prefix_add_lsp (enum mpls_lsp_t, struct prefix *, struct in_addr, uint32_t);
extern void mpls_prefix_remove_lsp (enum mpls_lsp_t, struct prefix *, struct in_addr);

extern void mpls_route_install_hook (struct route_node *);
extern void mpls_route_uninstall_hook (struct route_node *);
extern void mpls_lib_update (void);

/* mpls_vty.c */
extern void mpls_vty_init (void);

/* OS dependant functions */
extern int mpls_kernel_enable_interface (struct interface *);
extern int mpls_kernel_disable_interface (struct interface *);
extern int mpls_kernel_install_ilm (uint32_t, struct mpls_lsp *);
extern int mpls_kernel_uninstall_ilm (uint32_t, struct mpls_lsp *);
extern void mpls_kernel_init (void);
extern void mpls_kernel_exit (void);

#ifdef GNU_LINUX
#ifndef AF_MPLS
#define AF_MPLS	28
#endif
#ifndef RTA_MPLS
#define RTA_MPLS 17
#endif
#ifndef IFF_MPLS
#define IFF_MPLS 0x80000
#endif
#endif /* GNU_LINUX */

#endif /* _ZEBRA_MPLS_VTY_H */
