/*
 * BGP Netflow
 *
 * Copyright (C) 2012 Renato Westphal <renatow@digistar.com.br>
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

#ifndef _QUAGGA_BGP_NETFLOW_H
#define _QUAGGA_BGP_NETFLOW_H

#define BGP_NETFLOW_SOCKET "/var/run/bgp_netflow"

enum NETFLOW_REQ_TYPE
{
  BGP_AS = 0, /* Origin AS */
  BGP_PEERAS,
  BGP_NEXTHOP_IPV4
};

struct netflow_req
{
  enum NETFLOW_REQ_TYPE type;
  struct in_addr addr;
};

struct netflow_res
{
  int success;
  union
    {
      as_t as;
      struct in_addr nexthop;
    } u;
};

extern void bgp_netflow_socket (void);

#endif /* _QUAGGA_BGP_NETFLOW_H */
