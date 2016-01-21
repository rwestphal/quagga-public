/*
 * LDP VTY interface.
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

#include "command.h"
#include "prefix.h"
#include "log.h"
#include "memory.h"
#include "if.h"
#include "privs.h"
#include "sockunion.h"
#include "linklist.h"
#include "vty.h"

#include "ldpd/ldpd.h"
#include "ldpd/ldpe.h"
#include "ldpd/lde.h"
#include "ldpd/ldp_debug.h"

extern struct nbr_addr_head nbrs_by_addr;
extern struct fec_tree rt;
RB_PROTOTYPE(nbr_addr_head, nbr, addr_tree, nbr_addr_compare)
RB_PROTOTYPE(fec_tree, fec, entry, fec_compare)

static const char *
vty_label_str (uint32_t label, char *str)
{
  if (label == MPLS_IMPLICIT_NULL)
    strcpy (str, "imp-null");
  else if (label == MPLS_IPV4_EXPLICIT_NULL)
    strcpy (str, "exp-null");
  else
    sprintf (str, "%u", label);

  return str;
}

static const char *
vty_time2str (time_t t)
{
  char         *buf;
  static char   tfbuf[TF_BUFS][TF_LEN];
  static int    idx = 0;
  unsigned int  sec, min, hrs, day, week;

  if (t == 0)
       return ("00:00:00");

  buf = tfbuf[idx++];
  if (idx == TF_BUFS)
       idx = 0;

  week = t;

  sec = week % 60;
  week /= 60;
  min = week % 60;
  week /= 60;
  hrs = week % 24;
  week /= 24;
  day = week % 7;
  week /= 7;

  if (week > 0)
       snprintf(buf, TF_LEN, "%02uw%01ud%02uh", week, day, hrs);
  else if (day > 0)
       snprintf(buf, TF_LEN, "%01ud%02uh%02um", day, hrs, min);
  else
       snprintf(buf, TF_LEN, "%02u:%02u:%02u", hrs, min, sec);

  return (buf);
}

static int
vty_show_mpls_ldp_bindings (struct vty *vty, const char *prefix, int local,
                            const char *local_label, const char *remote_label,
                            const char *neighbor, int detail)
{
  struct fec *f;
  struct rt_node *rn;
  struct lde_map *me;
  char label_buf[16];
  struct prefix p;
  u_int32_t llabel = 0;
  u_int32_t rlabel = 0;
  struct in_addr nbr_addr;
  int show;
  int show_detail_header;
  int ret;

  if (prefix)
    {
      ret = str2prefix (prefix, &p);
      if (ret <= 0)
        {
          vty_out (vty, "%% Malformed address%s", VTY_NEWLINE);
          return CMD_WARNING;
        }
    }

  if (local_label)
    llabel = atoi (local_label);

  if (remote_label)
    rlabel = atoi (remote_label);

  if (neighbor)
    {
      ret = inet_aton (neighbor, &nbr_addr);
      if (ret == 0)
        {
          vty_out (vty, "%% Malformed LDP neighbor address%s", VTY_NEWLINE);
          return CMD_WARNING;
        }
    }

  RB_FOREACH(f, fec_tree, &rt)
    {
      rn = (struct rt_node *) f;
      show = 0;
      show_detail_header = 1;

      if (prefix
          && (rn->fec.prefix.s_addr != p.u.prefix4.s_addr
              || rn->fec.prefixlen != p.prefixlen))
        continue;

      if (local_label && llabel != rn->local_label)
        continue;

      if (remote_label)
        {
          LIST_FOREACH(me, &rn->downstream, entry)
            if (rlabel == me->label)
              {
                show = 1;
                break;
              }
          if (!show)
            continue;
        }

      if (neighbor)
        {
          LIST_FOREACH(me, &rn->downstream, entry)
            if (me->nexthop->id.s_addr == nbr_addr.s_addr)
              {
                show = 1;
                break;
              }
          if (!show)
            continue;
        }

      vty_out (vty, "  lib entry: %s/%u%s", inet_ntoa (rn->fec.prefix),
               rn->fec.prefixlen, VTY_NEWLINE);

      if (! remote_label)
        if (rn->local_label != NO_LABEL
            && ((! local_label)
                || (local_label && llabel == rn->local_label)))
          {
            vty_out (vty, "        local binding:  label: %s%s",
                     vty_label_str (rn->local_label, label_buf), VTY_NEWLINE);

            if (detail)
              {
                LIST_FOREACH(me, &rn->upstream, entry)
                  {
                    if (show_detail_header)
                      {
                        vty_out (vty, "          Advertised to:%s", VTY_NEWLINE);
                        show_detail_header = 0;
                      }
                    vty_out (vty, "          %s", inet_ntoa (me->nexthop->id));
                  }
                vty_out (vty, "%s", VTY_NEWLINE);
              }
          }

      if (local || local_label)
        continue;

      LIST_FOREACH(me, &rn->downstream, entry)
        {
          if (remote_label && rlabel != me->label)
            continue;

          if (neighbor && me->nexthop->id.s_addr != nbr_addr.s_addr)
            continue;

          vty_out (vty, "        remote binding: lsr: %s:0, label: %s%s",
                   inet_ntoa (me->nexthop->id), vty_label_str (me->label, label_buf),
                   VTY_NEWLINE);
        }
    }

  return CMD_SUCCESS;
}

DEFUN (mpls_ip,
       mpls_ip_cmd,
       "mpls ip",
       "Configure MPLS parameters\n"
       "Dynamic MPLS forwarding for IP\n")
{
  struct iface *iface;

  if (ldpd_conf->ldp_enabled)
    return CMD_SUCCESS;

  ldpd_conf->ldp_enabled = 1;

  LIST_FOREACH(iface, &ldpd_conf->iface_list, entry)
    {
      if (ldp_if_enabled (iface))
        ldpe_process (IMSG_IF_ENABLE, 0, iface, sizeof (struct iface));
    }

  return CMD_SUCCESS;
}

DEFUN (no_mpls_ip,
       no_mpls_ip_cmd,
       "no mpls ip",
       NO_STR
       "Configure MPLS parameters\n"
       "Dynamic MPLS forwarding for IP\n")
{
  struct iface *iface;

  if (! ldpd_conf->ldp_enabled)
    return CMD_SUCCESS;

  LIST_FOREACH(iface, &ldpd_conf->iface_list, entry)
    {
      if (ldp_if_enabled (iface))
        ldpe_process (IMSG_IF_DISABLE, 0, iface, sizeof (struct iface));
    }

  ldpd_conf->ldp_enabled = 0;

  return CMD_SUCCESS;
}

DEFUN (mpls_ip_if,
       mpls_ip_if_cmd,
       "mpls ip",
       "Configure MPLS interface parameters\n"
       "Configure dynamic MPLS forwarding for IP\n")
{
  struct interface *ifp;
  struct ldp_if_info *if_info;
  struct iface *iface;

  ifp = (struct interface *) vty->index;
  if_info = ifp->info;

  if (if_info->ldp_enabled)
    return CMD_SUCCESS;

  if_info->ldp_enabled = 1;
  iface = if_info->iface;
  if (ldp_if_enabled (iface))
    ldpe_process (IMSG_IF_ENABLE, 0, iface, sizeof (struct iface));

  return CMD_SUCCESS;
}

DEFUN (no_mpls_ip_if,
       no_mpls_ip_if_cmd,
       "no mpls ip",
       NO_STR
       "Configure MPLS interface parameters\n"
       "Configure dynamic MPLS forwarding for IP\n")
{
  struct interface *ifp;
  struct ldp_if_info *if_info;
  struct iface *iface;

  ifp = (struct interface *) vty->index;
  if_info = ifp->info;

  if (! if_info->ldp_enabled)
    return CMD_SUCCESS;

  iface = if_info->iface;
  if (ldp_if_enabled (iface))
    ldpe_process (IMSG_IF_DISABLE, 0, iface, sizeof (struct iface));

  if_info->ldp_enabled = 0;

  return CMD_SUCCESS;
}

DEFUN (mpls_ldp_discovery_hello_holdtime,
       mpls_ldp_discovery_hello_holdtime_cmd,
       "mpls ldp discovery hello holdtime <1-65535>",
       "Configure MPLS parameters\n"
       "Label Distribution Protocol\n"
       "LDP discovery\n"
       "LDP discovery Hello\n"
       "LDP discovery Hello holdtime\n"
       "Holdtime in seconds\n")
{
  ldpd_conf->holdtime = atoi(argv[0]);
  return CMD_SUCCESS;
}

DEFUN (mpls_ldp_discovery_hello_interval,
       mpls_ldp_discovery_hello_interval_cmd,
       "mpls ldp discovery hello interval <1-65535>",
       "Configure MPLS parameters\n"
       "Label Distribution Protocol\n"
       "LDP discovery\n"
       "LDP discovery Hello\n"
       "LDP discovery Hello interval\n"
       "Hello interval in seconds\n")
{
  ldpd_conf->hello_interval = atoi(argv[0]);
  return CMD_SUCCESS;
}

DEFUN (no_mpls_ldp_discovery_hello_holdtime,
       no_mpls_ldp_discovery_hello_holdtime_cmd,
       "no mpls ldp discovery hello holdtime",
       NO_STR
       "Configure MPLS parameters\n"
       "Label Distribution Protocol\n"
       "LDP discovery\n"
       "LDP discovery Hello\n"
       "LDP discovery Hello holdtime\n")
{
  ldpd_conf->holdtime = DEFAULT_HOLDTIME;
  return CMD_SUCCESS;
}

ALIAS (no_mpls_ldp_discovery_hello_holdtime,
       no_mpls_ldp_discovery_hello_holdtime_value_cmd,
       "no mpls ldp discovery hello holdtime <1-65535>",
       NO_STR
       "Configure MPLS parameters\n"
       "Label Distribution Protocol\n"
       "LDP discovery\n"
       "LDP discovery Hello\n"
       "LDP discovery Hello holdtime\n"
       "Holdtime in seconds\n")

DEFUN (no_mpls_ldp_discovery_hello_interval,
       no_mpls_ldp_discovery_hello_interval_cmd,
       "no mpls ldp discovery hello interval",
       NO_STR
       "Configure MPLS parameters\n"
       "Label Distribution Protocol\n"
       "LDP discovery\n"
       "LDP discovery Hello\n"
       "LDP discovery Hello interval\n")
{
  ldpd_conf->hello_interval = DEFAULT_HELLO_INTERVAL;
  return CMD_SUCCESS;
}

ALIAS (no_mpls_ldp_discovery_hello_interval,
       no_mpls_ldp_discovery_hello_interval_value_cmd,
       "no mpls ldp discovery hello interval <1-65535>",
       NO_STR
       "Configure MPLS parameters\n"
       "Label Distribution Protocol\n"
       "LDP discovery\n"
       "LDP discovery Hello\n"
       "LDP discovery Hello interval\n"
       "Hello interval in seconds\n")

DEFUN (mpls_ldp_holdtime,
       mpls_ldp_holdtime_cmd,
       "mpls ldp holdtime <15-2147483>",
       "Configure MPLS parameters\n"
       "Label Distribution Protocol\n"
       "LDP session holdtime\n"
       "Holdtime in seconds\n")
{
  ldpd_conf->keepalive = atoi(argv[0]);
  vty_out (vty, "%% Previously established sessions may not use "
                "the new holdtime%s", VTY_NEWLINE);

  return CMD_SUCCESS;
}

DEFUN (no_mpls_ldp_holdtime,
       no_mpls_ldp_holdtime_cmd,
       "no mpls ldp holdtime",
       NO_STR
       "Configure MPLS parameters\n"
       "Label Distribution Protocol\n"
       "LDP session holdtime\n")
{
  ldpd_conf->keepalive = DEFAULT_KEEPALIVE;
  vty_out (vty, "%% Previously established sessions may not use "
                "the new holdtime%s", VTY_NEWLINE);

  return CMD_SUCCESS;
}

ALIAS (no_mpls_ldp_holdtime,
       no_mpls_ldp_holdtime_value_cmd,
       "no mpls ldp holdtime <15-2147483>",
       NO_STR
       "Configure MPLS parameters\n"
       "Label Distribution Protocol\n"
       "LDP session holdtime\n"
       "Holdtime in seconds\n")

DEFUN (mpls_ldp_discovery_transport_address,
       mpls_ldp_discovery_transport_address_cmd,
       "mpls ldp discovery transport-address (A.B.C.D|interface)",
       "Configure MPLS parameters\n"
       "Configure Label Distribution Protocol (LDP) parameters\n"
       "Configure interface LDP Discovery parameters\n"
       "Specify interface LDP transport address\n"
       "IP address to use for LDP transport address\n"
       "Use interface address for LDP transport address\n")
{
  int ret;
  struct interface *ifp;
  struct ldp_if_info *if_info;
  struct prefix p;

  ifp = (struct interface *) vty->index;
  if_info = ifp->info;

  ret = str2prefix (argv[0], &p);
  if (ret <= 0)
    {
      if_info->transport_addr = TRANSPORT_ADDRESS_INTERFACE;
    }
  else
    {
      if_info->transport_addr = TRANSPORT_ADDRESS_STATIC_IP;
      if_info->transport_addr_static_ip = p.u.prefix4;
    }

  return CMD_SUCCESS;
}

DEFUN (no_mpls_ldp_discovery_transport_address,
       no_mpls_ldp_discovery_transport_address_cmd,
       "no mpls ldp discovery transport-address)",
       NO_STR
       "Configure MPLS parameters\n"
       "Configure Label Distribution Protocol (LDP) parameters\n"
       "Configure interface LDP Discovery parameters\n"
       "Specify interface LDP transport address\n")
{
  struct interface *ifp;
  struct ldp_if_info *if_info;

  ifp = (struct interface *) vty->index;
  if_info = ifp->info;
  if_info->transport_addr = TRANSPORT_ADDRESS_ROUTER_ID;

  return CMD_SUCCESS;
}

ALIAS (no_mpls_ldp_discovery_transport_address,
       no_mpls_ldp_discovery_transport_address_value_cmd,
       "no mpls ldp discovery transport-address (A.B.C.D|interface)",
       NO_STR
       "Configure MPLS parameters\n"
       "Configure Label Distribution Protocol (LDP) parameters\n"
       "Configure interface LDP Discovery parameters\n"
       "Specify interface LDP transport address\n"
       "IP address to use for LDP transport address\n"
       "Use interface address for LDP transport address\n")

DEFUN (mpls_ldp_neighbor_explicit_null,
       mpls_ldp_neighbor_explicit_null_cmd,
       "mpls ldp explicit-null",
       "Configure MPLS parameters\n"
       "Configure Label Distribution Protocol (LDP) parameters\n"
       "Advertise Explicit Null label in place of Implicit Null\n")
{
  SET_FLAG (ldpd_conf->opts, LDPD_OPT_EXPLICIT_NULL);
  return CMD_SUCCESS;
}

DEFUN (no_mpls_ldp_neighbor_explicit_null,
       no_mpls_ldp_neighbor_explicit_null_cmd,
       "no mpls ldp explicit-null",
       NO_STR
       "Configure MPLS parameters\n"
       "Configure Label Distribution Protocol (LDP) parameters\n"
       "Advertise Explicit Null label in place of Implicit Null\n")
{
  UNSET_FLAG (ldpd_conf->opts, LDPD_OPT_EXPLICIT_NULL);
  return CMD_SUCCESS;
}

DEFUN (show_mpls_ldp_bindings,
       show_mpls_ldp_bindings_cmd,
       "show mpls ldp bindings",
       SHOW_STR
       "MPLS information\n"
       "MPLS IP information\n"
       "Show the MPLS IP Label Information Base (LIB)\n")
{
  return vty_show_mpls_ldp_bindings (vty, NULL, 0, NULL, NULL, NULL, 0);
}

DEFUN (show_mpls_ldp_bindings_prefix,
       show_mpls_ldp_bindings_prefix_cmd,
       "show mpls ldp bindings A.B.C.D/M",
       SHOW_STR
       "MPLS information\n"
       "MPLS IP information\n"
       "Show the MPLS IP Label Information Base (LIB)\n"
       "Destination prefix\n")
{
  return vty_show_mpls_ldp_bindings (vty, argv[0], 0, NULL, NULL, NULL, 0);
}

DEFUN (show_mpls_ldp_bindings_detail,
       show_mpls_ldp_bindings_detail_cmd,
       "show mpls ldp bindings detail",
       SHOW_STR
       "MPLS information\n"
       "MPLS IP information\n"
       "Show the MPLS IP Label Information Base (LIB)\n"
       "Show detailed information\n")
{
  return vty_show_mpls_ldp_bindings (vty, NULL, 0, NULL, NULL, NULL, 1);
}

DEFUN (show_mpls_ldp_bindings_local,
       show_mpls_ldp_bindings_local_cmd,
       "show mpls ldp bindings local",
       SHOW_STR
       "MPLS information\n"
       "MPLS IP information\n"
       "Show the MPLS IP Label Information Base (LIB)\n"
       "Display only locally assigned labels\n")
{
  return vty_show_mpls_ldp_bindings (vty, NULL, 1, NULL, NULL, NULL, 0);
}

DEFUN (show_mpls_ldp_bindings_local_label,
       show_mpls_ldp_bindings_local_label_cmd,
       "show mpls ldp bindings local-label <0-1048575>",
       SHOW_STR
       "MPLS information\n"
       "MPLS IP information\n"
       "Show the MPLS IP Label Information Base (LIB)\n"
       "Match locally assigned label values\n"
       "Locally assigned label value\n")
{
  return vty_show_mpls_ldp_bindings (vty, NULL, 0, argv[0], NULL, NULL, 0);
}

DEFUN (show_mpls_ldp_bindings_neighbor,
       show_mpls_ldp_bindings_neighbor_cmd,
       "show mpls ldp bindings neighbor A.B.C.D",
       SHOW_STR
       "MPLS information\n"
       "MPLS IP information\n"
       "Show the MPLS IP Label Information Base (LIB)\n"
       "Display labels from LDP neighbor\n"
       "IP adjacency address\n")
{
  return vty_show_mpls_ldp_bindings (vty, NULL, 0, NULL, NULL, argv[0], 0);
}

DEFUN (show_mpls_ldp_bindings_remote_label,
       show_mpls_ldp_bindings_remote_label_cmd,
       "show mpls ldp bindings remote-label <0-1048575>",
       SHOW_STR
       "MPLS information\n"
       "MPLS IP information\n"
       "Show the MPLS IP Label Information Base (LIB)\n"
       "Match remotely assigned label values\n"
       "Remotely assigned label value\n")
{
  return vty_show_mpls_ldp_bindings (vty, NULL, 0, NULL, argv[0], NULL, 0);
}

DEFUN (show_mpls_ldp_discovery,
       show_mpls_ldp_discovery_cmd,
       "show mpls ldp discovery",
       SHOW_STR
       "MPLS information\n"
       "MPLS IP information\n"
       "Display sources for locally generated LDP Discovery Hello PDUs\n")
{
  struct iface *iface;
  struct nbr *nbr;
  int write = 0;


  LIST_FOREACH(iface, &ldpd_conf->iface_list, entry)
    LIST_FOREACH(nbr, &iface->nbr_list, entry)
      {
        write = 1;
        break;
      }

  if (! write)
    return CMD_SUCCESS;

  vty_out (vty, " Local LDP Identifier:%s", VTY_NEWLINE);
  vty_out (vty, "    %s:0%s", inet_ntoa (ldpd_conf->rtr_id), VTY_NEWLINE);
  vty_out (vty, "    Discovery Sources:%s", VTY_NEWLINE);
  vty_out (vty, "    Interfaces:%s", VTY_NEWLINE);

  LIST_FOREACH(iface, &ldpd_conf->iface_list, entry)
    {
      if (LIST_EMPTY (&iface->nbr_list))
        continue;

      vty_out (vty, "        %s (ldp): xmit/recv%s", iface->name, VTY_NEWLINE);
      LIST_FOREACH(nbr, &iface->nbr_list, entry)
        vty_out (vty, "            LDP Id: %s:0%s", inet_ntoa (nbr->id), VTY_NEWLINE);
    }

  return CMD_SUCCESS;
}

DEFUN (show_mpls_ldp_neighbor,
       show_mpls_ldp_neighbor_cmd,
       "show mpls ldp neighbor [IFNAME]",
       SHOW_STR
       "MPLS information\n"
       "MPLS IP information\n"
       "Display LDP neighbor information\n"
       IFNAME_STR)
{
  struct nbr *nbr;
  struct lde_nbr *ln;
  struct lde_nbr_address *address;;
  struct timeval now;
  time_t uptime;
  char buf1[INET_ADDRSTRLEN];
  char buf2[INET_ADDRSTRLEN];

  gettimeofday (&now, NULL);

  RB_FOREACH (nbr, nbr_addr_head, &nbrs_by_addr)
    {
      if (argc && strcmp (nbr->iface->name, argv[0]) != 0)
        continue;

      if (nbr->state == NBR_STA_PRESENT)
        continue;

      ln = lde_nbr_find (nbr->peerid);
      uptime = now.tv_sec - nbr->uptime;

      vty_out (vty, "    Peer LDP Ident: %s:0; Local LDP Ident %s:0%s",
               inet_ntop (AF_INET, &nbr->id, buf1, INET_ADDRSTRLEN),
               inet_ntop (AF_INET, &ldpd_conf->rtr_id, buf2, INET_ADDRSTRLEN),
               VTY_NEWLINE);
      vty_out (vty, "        TCP connection: %s.%u - %s.%u%s",
               inet_ntop (AF_INET, &nbr->remote_addr, buf1, INET_ADDRSTRLEN),
               nbr->remote_port, inet_ntop (AF_INET, &nbr->local_addr, buf2, INET_ADDRSTRLEN),
               nbr->local_port, VTY_NEWLINE);
      vty_out (vty, "        state: %s; Msgs sent/rcvd: %u/%u; Downstream%s",
               nbr_state_name (nbr->state), nbr->msgs_sent, nbr->msgs_rcvd,
               VTY_NEWLINE);
      vty_out (vty, "        Up time: %s%s",
               nbr->uptime ? vty_time2str (uptime) : "00:00:00", VTY_NEWLINE);
      vty_out (vty, "        LDP discovery sources:%s", VTY_NEWLINE);
      vty_out (vty, "          %s, Src IP addr: %s%s", nbr->iface->name,
               inet_ntoa (nbr->hello_addr), VTY_NEWLINE);

      vty_out (vty, "        Addresses bound to peer LDP Ident:%s", VTY_NEWLINE);
      if (ln)
        {
          TAILQ_FOREACH (address, &ln->addr_list, entry)
            vty_out (vty, "          %s", inet_ntoa (address->addr));
        }
      vty_out (vty, "%s", VTY_NEWLINE);
    }

  return CMD_SUCCESS;
}

static int
ldp_config_write (struct vty *vty)
{
  if (! ldpd_conf->ldp_enabled)
    vty_out (vty, "no mpls ip%s", VTY_NEWLINE);

  if (CHECK_FLAG (ldpd_conf->opts, LDPD_OPT_EXPLICIT_NULL))
    vty_out (vty, "mpls ldp explicit-null%s", VTY_NEWLINE);

  if (ldpd_conf->keepalive != DEFAULT_KEEPALIVE)
    vty_out (vty, "mpls ldp holdtime %d%s", ldpd_conf->keepalive,
             VTY_NEWLINE);

  if (ldpd_conf->hello_interval != DEFAULT_HELLO_INTERVAL)
    vty_out (vty, "mpls ldp discovery hello interval %d%s", ldpd_conf->hello_interval,
             VTY_NEWLINE);

  if (ldpd_conf->holdtime != DEFAULT_HOLDTIME)
    vty_out (vty, "mpls ldp discovery hello holdtime %d%s", ldpd_conf->holdtime,
             VTY_NEWLINE);

  vty_out (vty, "!%s", VTY_NEWLINE);

  return 0;
}

static int
ldp_interface_config_write (struct vty *vty)
{
  struct listnode *node;
  struct interface *ifp;

  for (ALL_LIST_ELEMENTS_RO (iflist, node, ifp))
    {
      struct ldp_if_info *if_info;

      if_info = ifp->info;

      vty_out (vty, "interface %s%s", ifp->name,
	       VTY_NEWLINE);

      if (ifp->desc)
	vty_out (vty, " description %s%s", ifp->desc,
		 VTY_NEWLINE);

      if (if_info->ldp_enabled)
	vty_out (vty, " mpls ip%s", VTY_NEWLINE);

      if (if_info->transport_addr == TRANSPORT_ADDRESS_INTERFACE)
	vty_out (vty, " mpls ldp discovery transport-address interface%s", VTY_NEWLINE);

      else if (if_info->transport_addr == TRANSPORT_ADDRESS_STATIC_IP)
	vty_out (vty, " mpls ldp discovery transport-address %s%s",
                 inet_ntoa(if_info->transport_addr_static_ip), VTY_NEWLINE);

      vty_out (vty, "!%s", VTY_NEWLINE);
    }

  return 0;
}

static struct cmd_node ldp_node =
{
  LDP_NODE,
  "",
  1
};

/* ldpd's interface node.  */
static struct cmd_node interface_node =
{
  INTERFACE_NODE,
  "%s(config-if)# ",
  1
};

void
ldp_vty_init (void)
{
  /* Install LDP top node.  */
  install_node (&ldp_node, ldp_config_write);
  install_default (LDP_NODE);

  /* Install interface node.  */
  install_node (&interface_node, ldp_interface_config_write);
  install_default (INTERFACE_NODE);

  /* "interface" commands.  */
  install_element (CONFIG_NODE, &interface_cmd);
  install_element (CONFIG_NODE, &no_interface_cmd);

  /* "description" commands.  */
  install_element (INTERFACE_NODE, &interface_desc_cmd);
  install_element (INTERFACE_NODE, &no_interface_desc_cmd);

  /* "mpls ip" commands.  */
  install_element (CONFIG_NODE, &mpls_ip_cmd);
  install_element (CONFIG_NODE, &no_mpls_ip_cmd);
  install_element (INTERFACE_NODE, &mpls_ip_if_cmd);
  install_element (INTERFACE_NODE, &no_mpls_ip_if_cmd);

  /* "mpls ldp discovery hello" commands.  */
  install_element (CONFIG_NODE, &mpls_ldp_discovery_hello_holdtime_cmd);
  install_element (CONFIG_NODE, &mpls_ldp_discovery_hello_interval_cmd);
  install_element (CONFIG_NODE, &no_mpls_ldp_discovery_hello_holdtime_cmd);
  install_element (CONFIG_NODE, &no_mpls_ldp_discovery_hello_holdtime_value_cmd);
  install_element (CONFIG_NODE, &no_mpls_ldp_discovery_hello_interval_cmd);
  install_element (CONFIG_NODE, &no_mpls_ldp_discovery_hello_interval_value_cmd);

  /* "mpls ldp holdtime" commands.  */
  install_element (CONFIG_NODE, &mpls_ldp_holdtime_cmd);
  install_element (CONFIG_NODE, &no_mpls_ldp_holdtime_cmd);
  install_element (CONFIG_NODE, &no_mpls_ldp_holdtime_value_cmd);

  /* "mpls ldp discovery transport-address" commands.  */
  install_element (INTERFACE_NODE, &mpls_ldp_discovery_transport_address_cmd);
  install_element (INTERFACE_NODE, &no_mpls_ldp_discovery_transport_address_cmd);
  install_element (INTERFACE_NODE, &no_mpls_ldp_discovery_transport_address_value_cmd);

  /* "mpls ldp explicit-null" commands.  */
  install_element (CONFIG_NODE, &mpls_ldp_neighbor_explicit_null_cmd);
  install_element (CONFIG_NODE, &no_mpls_ldp_neighbor_explicit_null_cmd);

  /* "show mpls ldp" commands.  */
  install_element (VIEW_NODE, &show_mpls_ldp_bindings_cmd);
  install_element (ENABLE_NODE, &show_mpls_ldp_bindings_cmd);
  install_element (VIEW_NODE, &show_mpls_ldp_bindings_prefix_cmd);
  install_element (ENABLE_NODE, &show_mpls_ldp_bindings_prefix_cmd);
  install_element (VIEW_NODE, &show_mpls_ldp_bindings_detail_cmd);
  install_element (ENABLE_NODE, &show_mpls_ldp_bindings_detail_cmd);
  install_element (VIEW_NODE, &show_mpls_ldp_bindings_local_cmd);
  install_element (ENABLE_NODE, &show_mpls_ldp_bindings_local_cmd);
  install_element (VIEW_NODE, &show_mpls_ldp_bindings_local_label_cmd);
  install_element (ENABLE_NODE, &show_mpls_ldp_bindings_local_label_cmd);
  install_element (VIEW_NODE, &show_mpls_ldp_bindings_neighbor_cmd);
  install_element (ENABLE_NODE, &show_mpls_ldp_bindings_neighbor_cmd);
  install_element (VIEW_NODE, &show_mpls_ldp_bindings_remote_label_cmd);
  install_element (ENABLE_NODE, &show_mpls_ldp_bindings_remote_label_cmd);
  install_element (VIEW_NODE, &show_mpls_ldp_neighbor_cmd);
  install_element (ENABLE_NODE, &show_mpls_ldp_neighbor_cmd);
  install_element (VIEW_NODE, &show_mpls_ldp_discovery_cmd);
  install_element (ENABLE_NODE, &show_mpls_ldp_discovery_cmd);

  /* Debug related init. */
  ldp_debug_init ();
}
