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

#include <zebra.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "prefix.h"
#include "log.h"
#include "sockunion.h"
#include "linklist.h"
#include "thread.h"
#include "vty.h"

#include "bgpd/bgpd.h"
#include "bgpd/bgp_netflow.h"
#include "bgpd/bgp_aspath.h"
#include "bgpd/bgp_debug.h"
#include "bgpd/bgp_route.h"
#include "bgpd/bgp_table.h"

static int
bgp_netflow_get_origin_as (struct bgp_info *ri, as_t **as)
{
  struct assegment *seg;

  seg = ri->attr->aspath->segments;
  if (! seg)
    return -1;

  /* Last AS. */
  *as = seg->as + (seg->length - 1);

  return 0;
}

static int
bgp_netflow_get_peer_as (struct bgp_info *ri, as_t **as)
{
  struct assegment *seg;

  seg = ri->attr->aspath->segments;
  if (! seg)
    return -1;

  /* First AS. */
  *as = seg->as;

  return 0;
}

static int
bgp_netflow_get_nexthop_ipv4 (struct bgp_info *ri, struct in_addr **nexthop)
{
  *nexthop = &ri->attr->nexthop;

  return 0;
}

static int
bgp_netflow_handle_request (struct thread *thread)
{
  int sock;
  ssize_t n;
  struct netflow_req req;
  struct netflow_res res = { .success = -1 };
  struct bgp *bgp;
  struct bgp_node *rn;
  struct bgp_info *ri;
  as_t *as;
  struct in_addr *nexthop;

  /* Get socket. */
  sock = THREAD_FD (thread);
  if (sock < 0)
    {
      zlog_err ("Netflow socket is negative value %d", sock);
      return -1;
    }

  /* Receive request. */
  n = recv (sock, &req, sizeof (struct netflow_req), 0);
  if (n < (ssize_t) sizeof (struct netflow_req))
    goto end;

  /* Initialize BGP variables. */
  bgp = bgp_get_default ();
  if (! bgp)
    goto end;

  rn = bgp_node_match_ipv4 (bgp->rib[AFI_IP][SAFI_UNICAST], &req.addr);
  if (! rn)
    goto end;

  for (ri = rn->info; ri; ri = ri->next)
    if (CHECK_FLAG (ri->flags, BGP_INFO_SELECTED))
      break;
  if (! ri)
    goto end;

  /* Handle request. */
  switch (req.type)
    {
      case BGP_AS:
        res.success = bgp_netflow_get_origin_as (ri, &as);
        if (res.success == 0)
          res.u.as = *as;
        break;
      case BGP_PEERAS:
        res.success = bgp_netflow_get_peer_as (ri, &as);
        if (res.success == 0)
          res.u.as = *as;
        break;
      case BGP_NEXTHOP_IPV4:
        res.success = bgp_netflow_get_nexthop_ipv4 (ri, &nexthop);
        if (res.success == 0)
          res.u.nexthop = *nexthop;
        break;
      default:
        break;
    }

end:
  send (sock, &res, sizeof (struct netflow_res), 0);
  close (sock);

  return 0;
}

static int
bgp_netflow_accept (struct thread *thread)
{
  union sockunion su;
  int accept_sock;
  int sock;

  accept_sock = THREAD_FD (thread);
  if (accept_sock < 0)
    {
      zlog_err ("accept_sock is negative value %d", accept_sock);
      return -1;
    }
  thread_add_read (master, bgp_netflow_accept, NULL, accept_sock);

  /* Accept client connection. */
  sock = sockunion_accept (accept_sock, &su);
  if (sock < 0)
    {
      zlog_err ("BGP Netflow socket accept failed (%s)", safe_strerror (errno));
      return -1;
    }

  thread_add_read (master, bgp_netflow_handle_request, NULL, sock);

  return 0;
}

void
bgp_netflow_socket (void)
{
  int sock;
  struct sockaddr_un servaddr;
  int ret;

  sock = socket (AF_UNIX, SOCK_STREAM, 0);
  if (sock < 0)
    {
      zlog_err ("Cannot create unix stream socket: %s", safe_strerror(errno));
      return;
    }

  unlink (BGP_NETFLOW_SOCKET);
  memset (&servaddr, 0, sizeof (struct sockaddr_in));
  servaddr.sun_family = AF_UNIX;
  strcpy (servaddr.sun_path, BGP_NETFLOW_SOCKET);

  ret = bind (sock, (struct sockaddr *) &servaddr, sizeof (struct sockaddr_un));
  if (ret < 0)
    {
      zlog_err ("Cannot bind path %s: %s", BGP_NETFLOW_SOCKET, safe_strerror (errno));
      close (sock);
      return;
    }

  ret = listen (sock, 5);
  if (ret < 0)
    {
      zlog_err ("listen(fd %d) failed: %s", sock, safe_strerror (errno));
      close (sock);
      return;
    }

  thread_add_read (master, bgp_netflow_accept, NULL, sock);
}
