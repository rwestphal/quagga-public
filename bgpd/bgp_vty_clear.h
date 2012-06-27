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

#ifndef _QUAGGA_BGP_VTY_CLEAR_H
#define _QUAGGA_BGP_VTY_CLEAR_H

#include "bgpd/bgp_vty.h"

/* BGP clear sort. */
enum clear_sort
{
  clear_all,
  clear_peer,
  clear_group,
  clear_external,
  clear_as
};

extern int
bgp_clear_vty (struct vty *vty, const char *name, afi_t afi, safi_t safi,
               enum clear_sort sort, enum bgp_clear_type stype,
               const char *arg);

extern int
bgp_clear_damp_route (struct vty *vty, const char *view_name,
                      const char *ip_str, afi_t afi, safi_t safi,
                      struct prefix_rd *prd, int prefix_check);

#endif /* _QUAGGA_BGP_VTY_CLEAR_H */
