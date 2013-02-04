/*
 * Zebra interface for LDP.
 *
 * Copyright (C) 2011-2012 Renato Westphal <rwestphal@inf.ufrgs.br>
 * Copyright (C) 2012-2012 Jorge Boncompte [DTI2] <jorge@dti2.net>
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

#include "prefix.h"
#include "stream.h"
#include "memory.h"
#include "zclient.h"
#include "command.h"
#include "network.h"
#include "log.h"

#include "ldpd.h"
#include "ldpe.h"
#include "lde.h"
#include "ldp_debug.h"

/* All information about zebra.  */
struct zclient *zclient = NULL;
struct zclient *zclient_sync = NULL;

int
ldp_if_enabled (struct iface *iface)
{
  return (iface && ldpd_conf->ldp_enabled
          && iface->if_info
          && iface->if_info->ldp_enabled
          && (iface->flags & IFF_UP)
          && (iface->addr.s_addr != 0));
}

static int
ldp_router_id_update (int command, struct zclient *zclient, zebra_size_t length)
{
  struct prefix router_id;

  zebra_router_id_update_read (zclient->ibuf, &router_id);
  log_zebra ("Zebra rcvd: router id update %s", inet_ntoa (router_id.u.prefix4));

  ldpd_conf->rtr_id.s_addr = router_id.u.prefix4.s_addr;

  return 0;
}

static int
ldp_interface_add (int command, struct zclient *zclient, zebra_size_t length)
{
  struct interface *ifp;
  struct ldp_if_info *if_info;
  struct iface *iface;

  ifp = zebra_interface_add_read (zclient->ibuf);
  if_info = ifp->info;

  if (! if_info->iface)
    {
      iface = if_new (ifp);
      LIST_INSERT_HEAD (&ldpd_conf->iface_list, iface, entry);

      iface->if_info = if_info;
      if_info->iface = iface;

      if_init_ldp (iface);
      log_zebra ("interface add %s index %d flags %lu metric %d mtu %d",
                 ifp->name, ifp->ifindex, ifp->flags, ifp->metric, ifp->mtu);
    }

  return 0;
}

static int
ldp_interface_delete (int command, struct zclient *zclient, zebra_size_t length)
{
  struct interface *ifp;
  struct ldp_if_info *if_info;
  struct iface *iface;

  /* zebra_interface_state_read() updates interface structure in iflist.  */
  ifp = zebra_interface_state_read (zclient->ibuf);
  if (! ifp)
    return 0;

  if_info = ifp->info;
  iface = if_info->iface;
  if (! iface)
    return 0;

  if (ldp_if_enabled (iface))
    ldpe_process (IMSG_IF_DISABLE, 0, iface, sizeof (struct iface));

  if_del (iface);
  if_info->iface = NULL;

  log_zebra ("interface delete %s index %d flags %#llx metric %d mtu %d",
	     ifp->name, ifp->ifindex, (unsigned long long) ifp->flags,
	     ifp->metric, ifp->mtu);

  /* To support pseudo interface do not free interface structure.  */
  /* if_delete (ifp); */
  ifp->ifindex = IFINDEX_INTERNAL;

  return 0;
}

static int
ldp_interface_status_change (int command, struct zclient *zclient, zebra_size_t length)
{
  struct interface *ifp;
  struct ldp_if_info *if_info;
  struct iface *iface;
  int iface_old_flags;

  /* zebra_interface_state_read () updates interface structure in
     iflist. */
  ifp = zebra_interface_state_read (zclient->ibuf);
  if (ifp == NULL)
    return 0;

  if_info = ifp->info;
  iface = if_info->iface;
  if (! iface)
    return 0;

  log_zebra ("interface %s state update", ifp->name);

  iface_old_flags = iface->flags;
  iface->flags = ifp->flags;

  /* notify ldpe about interface link state */
  if (ldpd_conf->ldp_enabled && iface->if_info->ldp_enabled
      && (iface->addr.s_addr != 0))
    {
      if (! (iface_old_flags & IFF_UP) && if_is_up (ifp))
        ldpe_process (IMSG_IF_ENABLE, 0, iface, sizeof (struct iface));
      else if ((iface_old_flags & IFF_UP) && (! if_is_up (ifp)))
        ldpe_process (IMSG_IF_DISABLE, 0, iface, sizeof (struct iface));
    }

  return 0;
}

static u_char
ldp_valid_address(struct in_addr addr)
{
    if(addr.s_addr == INADDR_ANY
       || IPV4_NET127 (ntohl (addr.s_addr))
       || IN_CLASSD (ntohl (addr.s_addr))
       || IPV4_LINKLOCAL (ntohl (addr.s_addr)))
      return 0;

  return 1;
}

static int
ldp_interface_address_add (int command, struct zclient *zclient, zebra_size_t length)
{
  struct connected *ifc;
  struct interface *ifp;
  struct ldp_if_info *if_info;
  struct iface *iface;
  struct in_addr addr;

  ifc = zebra_interface_address_read (command, zclient->ibuf);
  if (ifc == NULL || ifc->address->family != AF_INET)
    return 0;

  ifp = ifc->ifp;
  if_info = ifp->info;
  iface = if_info->iface;
  if (! iface)
    return 0;

  addr = ifc->address->u.prefix4;

  /* Filter invalid addresses.  */
  if (! ldp_valid_address (addr))
    return 0;

  log_zebra ("connected address %s is added", inet_ntoa (addr));

  /* Currently we only support one IP address per interface.  */
  if (iface->addr.s_addr != INADDR_ANY)
    return 0;

  iface->addr = addr;
  ldpe_process (IMSG_ADDRESS_ADD, 0, iface, sizeof (struct iface));

  /* Notify ldpe about interface address.  */
  if (ldp_if_enabled (iface))
    ldpe_process (IMSG_IF_ENABLE, 0, iface, sizeof (struct iface));

  return 0;
}

static int
ldp_interface_address_delete (int command, struct zclient *zclient, zebra_size_t length)
{
  struct connected *ifc;
  struct interface *ifp;
  struct ldp_if_info *if_info;
  struct iface *iface;
  struct in_addr addr;

  ifc = zebra_interface_address_read (command, zclient->ibuf);
  if (ifc == NULL || ifc->address->family != AF_INET)
    return 0;

  ifp = ifc->ifp;
  if_info = ifp->info;
  iface = if_info->iface;
  if (! iface)
    return 0;

  addr = ifc->address->u.prefix4;
  connected_free (ifc);

  /* Filter invalid addresses.  */
  if (! ldp_valid_address (addr))
    return 0;

  log_zebra ("connected address %s is deleted", inet_ntoa (addr));

  if (iface->addr.s_addr == addr.s_addr)
    {
      ldpe_process (IMSG_ADDRESS_DEL, 0, iface, sizeof (struct iface));

      /* Notify ldpe about interface address removal.  */
      if (ldp_if_enabled (iface))
        ldpe_process (IMSG_IF_DISABLE, 0, iface, sizeof (struct iface));

      /* Clear interface address.  */
      iface->addr.s_addr = INADDR_ANY;
    }

  return 0;
}

static int
ldp_zebra_read_ipv4 (int command, struct zclient *zclient, zebra_size_t length)
{
  struct stream *s;
  u_char type;
  u_char message_flags;
  unsigned long ifindex;
  struct in_addr nexthop;
  struct prefix_ipv4 p;
  struct kroute kr;

  s = zclient->ibuf;
  ifindex = 0;
  nexthop.s_addr = 0;

  /* Type, flags, message. */
  type = stream_getc (s);
  stream_getc (s); /* flags, unused. */
  message_flags = stream_getc (s);

  /* IPv4 prefix. */
  memset (&p, 0, sizeof (struct prefix_ipv4));
  p.family = AF_INET;
  p.prefixlen = stream_getc (s);
  stream_get (&p.prefix, s, PSIZE (p.prefixlen));

  /* Do not create bindings for the default route. */
  if (p.prefix.s_addr == 0 && p.prefixlen == 0)
    return 0;

  /* Nexthop, ifindex, distance, metric. */
  if (CHECK_FLAG (message_flags, ZAPI_MESSAGE_NEXTHOP))
    {
      stream_getc (s); /* nexthop_num, unused. */
      nexthop.s_addr = stream_get_ipv4 (s);
    }
  if (CHECK_FLAG (message_flags, ZAPI_MESSAGE_IFINDEX))
    {
      stream_getc (s); /* ifindex_num, unused. */
      ifindex = stream_getl (s);
    }

  /* Not used. */
  if (CHECK_FLAG (message_flags, ZAPI_MESSAGE_DISTANCE))
    stream_getc (s);
  if (CHECK_FLAG (message_flags, ZAPI_MESSAGE_METRIC))
    stream_getl (s);

  kr.prefix.s_addr = p.prefix.s_addr;
  kr.prefixlen = p.prefixlen;
  kr.nexthop.s_addr = nexthop.s_addr;
  kr.ifindex = ifindex;
  kr.local_label = NO_LABEL;
  kr.remote_label = NO_LABEL;
  kr.connected = (type == ZEBRA_ROUTE_CONNECT) ? 1 : 0;

  /* Then fetch IPv4 prefixes. */
  if (command == ZEBRA_IPV4_ROUTE_ADD)
    {
      log_zebra ("kernel add route %s/%u", inet_ntoa (kr.prefix), kr.prefixlen);
      lde_process (IMSG_ZEBRA_NETWORK_ADD, 0, &kr, sizeof(struct kroute));
    }
  else
    {
      log_zebra ("kernel remove route %s/%u", inet_ntoa (kr.prefix), kr.prefixlen);
      lde_process (IMSG_ZEBRA_NETWORK_DEL, 0, &kr, sizeof(struct kroute));
    }

  return 0;
}

static int
ldp_zebra_read_change_input_label (int command, struct zclient *zclient,
                                   zebra_size_t length)
{
  struct stream *s;
  struct prefix_ipv4 p;
  struct kroute kr;
  u_int32_t label;

  s = zclient->ibuf;

  /* IPv4 prefix. */
  memset (&p, 0, sizeof (struct prefix_ipv4));
  p.family = AF_INET;
  p.prefixlen = stream_getc (s);
  stream_get (&p.prefix, s, PSIZE (p.prefixlen));

  /* Prefix input label. */
  label = stream_getl (s);

  kr.prefix.s_addr = p.prefix.s_addr;
  kr.prefixlen = p.prefixlen;
  kr.local_label = label;
  kr.remote_label = NO_LABEL;

  /* Withdraw mappings and advertise the new input label. */
  lde_process (IMSG_ZEBRA_CHANGE_INPUT_LABEL, 0, &kr, sizeof(struct kroute));

  return 0;
}

int
ldp_zebra_send_change_input_label (struct kroute *kr)
{
  struct stream *s;
  int psize;

  /* Reset stream. */
  s = zclient->obuf;
  stream_reset (s);
  zclient_create_header (s, ZEBRA_MPLS_CHANGE_IN_LABEL);

  /* Put prefix information. */
  psize = PSIZE (kr->prefixlen);
  stream_putc (s, kr->prefixlen);
  stream_write (s, (u_char *) &kr->prefix, psize);

  /* Put input label. */
  stream_putl (s, kr->local_label);

  /* Put length at the first point of the stream. */
  stream_putw_at (s, 0, stream_get_endp (s));

  log_zebra ("ldp send input label: %s/%u - %u", inet_ntoa (kr->prefix),
	     kr->prefixlen, kr->local_label);

  return zclient_send_message (zclient);
}

int
ldp_zebra_send_lsp (int command, struct kroute *kr)
{
  struct stream *s;
  int psize;

  /* Reset stream. */
  s = zclient->obuf;
  stream_reset (s);
  zclient_create_header (s, command);

  /* Put prefix information. */
  psize = PSIZE (kr->prefixlen);
  stream_putc (s, kr->prefixlen);
  stream_write (s, (u_char *) &kr->prefix, psize);

  /* Put nexthop. */
  stream_put_in_addr (s, &kr->nexthop);

  /* Put output label. */
  stream_putl (s, kr->remote_label);

  /* Put length at the first point of the stream. */
  stream_putw_at (s, 0, stream_get_endp (s));

  log_zebra ("ldp send lsp: %s/%u - %u - %s", inet_ntoa (kr->prefix),
	     kr->prefixlen, kr->remote_label, inet_ntoa (kr->nexthop));

  return zclient_send_message (zclient);
}

uint32_t
ldp_zebra_request_label (void)
{
  int ret;
  struct stream *s;
  uint16_t length;
  int nbytes;
  u_char marker;
  u_char version;
  uint16_t command;

  if (zclient_sync->sock < 0)
    return 0;

  /* send request */
  s = zclient_sync->obuf;
  stream_reset (s);
  zclient_create_header (s, ZEBRA_MPLS_REQUEST_LABEL);
  stream_putw_at (s, 0, stream_get_endp (s));

  ret = writen (zclient_sync->sock, s->data, stream_get_endp (s));
  if (ret < 0)
    {
      zlog_err ("can't write to zclient_sync->sock");
      close (zclient_sync->sock);
      zclient_sync->sock = -1;
      return 0;
    }
  if (ret == 0)
    {
      zlog_err ("zclient_sync->sock connection closed");
      close (zclient_sync->sock);
      zclient_sync->sock = -1;
      return 0;
    }

  /* read response */
  s = zclient_sync->ibuf;
  stream_reset (s);

  nbytes = stream_read (s, zclient_sync->sock, 2);
  length = stream_getw (s);

  nbytes = stream_read (s, zclient_sync->sock, length - 2);
  marker = stream_getc (s);
  version = stream_getc (s);

  if (version != ZSERV_VERSION || marker != ZEBRA_HEADER_MARKER)
    {
      zlog_err ("%s: socket %d version mismatch, marker %d, version %d",
		__func__, zclient_sync->sock, marker, version);
      return 0;
    }

  command = stream_getw (s);
  if (command != ZEBRA_MPLS_REQUEST_LABEL)
    {
      zlog_err ("%s: unexpected command (%u)", __func__, command);
      return 0;
    }

  return stream_getl (s);
}

static int
ldp_if_new_hook (struct interface *ifp)
{
  struct ldp_if_info *if_info;

  ifp->info = XCALLOC (MTYPE_LDP, sizeof (struct ldp_if_info));
  if_info = ifp->info;
  if_info->transport_addr = TRANSPORT_ADDRESS_ROUTER_ID;

  return 0;
}

static int
ldp_if_delete_hook (struct interface *ifp)
{
  XFREE (MTYPE_TMP, ifp->info);

  return 0;
}

static int
zclient_sync_connect (struct thread *t)
{
  struct zclient *zclient;

  zclient = THREAD_ARG (t);
  zclient->t_connect = NULL;

  if (zclient->sock != -1)
    return 0;

  if (zclient_socket_connect (zclient) < 0)
    return -1;

  return 0;
}

void
ldp_zebra_init (void)
{
  /* Initialize Zebra interface data structure. */
  if_init ();
  if_add_hook (IF_NEW_HOOK, ldp_if_new_hook);
  if_add_hook (IF_DELETE_HOOK, ldp_if_delete_hook);

  /* Set default values. */
  zclient = zclient_new ();
  zclient_init (zclient, ZEBRA_ROUTE_LDP);

  /* The LDP default behavior is to allocate local labels for all non-BGP prefixes */
  memset (zclient->redist, 1, sizeof (zclient->redist));
  zclient->redist[ZEBRA_ROUTE_BGP] = 0;

  /* Initialize special zclient for synchronous message exchanges. */
  zclient_sync = zclient_new ();
  zclient_sync->sock = -1;
  zclient_sync->t_connect = thread_add_event (master, zclient_sync_connect,
					      zclient_sync, 0);

  /* set callbacks */
  zclient->router_id_update = ldp_router_id_update;
  zclient->interface_add = ldp_interface_add;
  zclient->interface_delete = ldp_interface_delete;
  zclient->interface_up = ldp_interface_status_change;
  zclient->interface_down = ldp_interface_status_change;
  zclient->interface_address_add = ldp_interface_address_add;
  zclient->interface_address_delete = ldp_interface_address_delete;
  zclient->ipv4_route_add = ldp_zebra_read_ipv4;
  zclient->ipv4_route_delete = ldp_zebra_read_ipv4;
  zclient->mpls_change_in_label = ldp_zebra_read_change_input_label;
}
