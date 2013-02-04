/*
 * Copyright (c) 2003, 2004 Henning Brauer <henning@openbsd.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <zebra.h>

#include "command.h"
#include "vty.h"

#include "ldpd.h"
#include "ldp_debug.h"

/* For debug statement. */
unsigned long ldp_debug_event = 0;
unsigned long ldp_debug_packet = 0;
unsigned long ldp_debug_zebra = 0;

void
fatal(const char *emsg)
{
	if (errno)
		zlog_err("fatal: %s: %s", emsg, strerror(errno));
	else
		zlog_err("fatal: %s", emsg);

	exit(1);
}

void
fatalx(const char *emsg)
{
	errno = 0;
	fatal(emsg);
}

/* names */
const char *
nbr_state_name(int state)
{
	switch (state) {
	case NBR_STA_DOWN:
		return ("DOWN");
	case NBR_STA_PRESENT:
		return ("PRESENT");
	case NBR_STA_INITIAL:
		return ("INITIALIZED");
	case NBR_STA_OPENREC:
		return ("OPENREC");
	case NBR_STA_OPENSENT:
		return ("OPENSENT");
	case NBR_STA_OPER:
		return ("OPERATIONAL");
	default:
		return ("UNKNW");
	}
}

const char *
if_state_name(int state)
{
	switch (state) {
	case IF_STA_DOWN:
		return ("DOWN");
	case IF_STA_LOOPBACK:
		return ("LOOP");
	case IF_STA_ACTIVE:
		return ("ACTIVE");
	default:
		return ("UNKNW");
	}
}

const char *
notification_name(u_int32_t status)
{
	static char buf[16];

	switch (status) {
	case S_SUCCESS:
		return ("Success");
	case S_BAD_LDP_ID:
		return ("Bad LDP Identifier");
	case S_BAD_PROTO_VER:
		return ("Bad Protocol Version");
	case S_BAD_PDU_LEN:
		return ("Bad PDU Length");
	case S_UNKNOWN_MSG:
		return ("Unknown Message Type");
	case S_BAD_MSG_LEN:
		return ("Bad Message Length");
	case S_UNKNOWN_TLV:
		return ("Unknown TLV");
	case S_BAD_TLV_LEN:
		return ("Bad TLV Length");
	case S_BAD_TLV_VAL:
		return ("Malformed TLV Value");
	case S_HOLDTIME_EXP:
		return ("Hold Timer Expired");
	case S_SHUTDOWN:
		return ("Shutdown");
	case S_LOOP_DETECTED:
		return ("Loop Detected");
	case S_UNKNOWN_FEC:
		return ("Unknown FEC");
	case S_NO_ROUTE:
		return ("No Route");
	case S_NO_LABEL_RES:
		return ("No Label Resources");
	case S_AVAILABLE:
		return ("Label Resources Available");
	case S_NO_HELLO:
		return ("Session Rejected, No Hello");
	case S_PARM_ADV_MODE:
		return ("Rejected Advertisement Mode Parameter");
	case S_MAX_PDU_LEN:
		return ("Rejected Max PDU Length Parameter");
	case S_PARM_L_RANGE:
		return ("Rejected Label Range Parameter");
	case S_KEEPALIVE_TMR:
		return ("KeepAlive Timer Expired");
	case S_LAB_REQ_ABRT:
		return ("Label Request Aborted");
	case S_MISS_MSG:
		return ("Missing Message Parameters");
	case S_UNSUP_ADDR:
		return ("Unsupported Address Family");
	case S_KEEPALIVE_BAD:
		return ("Bad KeepAlive Time");
	case S_INTERN_ERR:
		return ("Internal Error");
	default:
		snprintf(buf, sizeof(buf), "[%08x]", status);
		return (buf);
	}
}

const char *
log_fec(struct map *map)
 {
	static char	buf[32];
	char		pstr[32];

	if (snprintf(buf, sizeof(buf), "%s/%u",
	    inet_ntop(AF_INET, &map->prefix, pstr, sizeof(pstr)),
	    map->prefixlen) == -1)
		return ("???");

	return (buf);
}

DEFUN (show_debugging_mpls_ldp,
       show_debugging_mpls_ldp_cmd,
       "show debugging mpls ldp",
       SHOW_STR
       DEBUG_STR
       "MPLS debug\n"
       LDP_STR)
{
  vty_out (vty, "LDP debugging status:%s", VTY_NEWLINE);

  if (IS_LDP_DEBUG_EVENT)
    vty_out (vty, "  LDP event debugging is on%s", VTY_NEWLINE);

  if (IS_LDP_DEBUG_PACKET)
    {
      if (IS_LDP_DEBUG_SEND && IS_LDP_DEBUG_RECV)
	{
	  vty_out (vty, "  LDP packet debugging is on%s",
		   VTY_NEWLINE);
	}
      else
	{
	  if (IS_LDP_DEBUG_SEND)
	    vty_out (vty, "  LDP packet send debugging is on%s",
		     VTY_NEWLINE);
	  else
	    vty_out (vty, "  LDP packet receive debugging is on%s",
		     VTY_NEWLINE);
	}
    }

  if (IS_LDP_DEBUG_ZEBRA)
    vty_out (vty, "  LDP zebra debugging is on%s", VTY_NEWLINE);

  return CMD_SUCCESS;
}

DEFUN (debug_mpls_ldp_events,
       debug_mpls_ldp_events_cmd,
       "debug mpls ldp events",
       DEBUG_STR
      "MPLS debug\n"
       LDP_STR
       "LDP events\n")
{
  ldp_debug_event = LDP_DEBUG_EVENT;
  return CMD_WARNING;
}

DEFUN (debug_mpls_ldp_packet,
       debug_mpls_ldp_packet_cmd,
       "debug mpls ldp packet",
       DEBUG_STR
      "MPLS debug\n"
       LDP_STR
       "LDP packet\n")
{
  ldp_debug_packet = LDP_DEBUG_PACKET;
  ldp_debug_packet |= LDP_DEBUG_SEND;
  ldp_debug_packet |= LDP_DEBUG_RECV;
  return CMD_SUCCESS;
}

DEFUN (debug_mpls_ldp_packet_direct,
       debug_mpls_ldp_packet_direct_cmd,
       "debug mpls ldp packet (recv|send)",
       DEBUG_STR
      "MPLS debug\n"
       LDP_STR
       "LDP packet\n"
       "LDP receive packet\n"
       "LDP send packet\n")
{
  ldp_debug_packet |= LDP_DEBUG_PACKET;
  if (strncmp ("send", argv[0], strlen (argv[0])) == 0)
    ldp_debug_packet |= LDP_DEBUG_SEND;
  if (strncmp ("recv", argv[0], strlen (argv[0])) == 0)
    ldp_debug_packet |= LDP_DEBUG_RECV;
  return CMD_SUCCESS;
}

DEFUN (debug_mpls_ldp_zebra,
       debug_mpls_ldp_zebra_cmd,
       "debug mpls ldp zebra",
       DEBUG_STR
      "MPLS debug\n"
       LDP_STR
       "LDP and ZEBRA communication\n")
{
  ldp_debug_zebra = LDP_DEBUG_ZEBRA;
  return CMD_WARNING;
}

DEFUN (no_debug_mpls_ldp_events,
       no_debug_mpls_ldp_events_cmd,
       "no debug mpls ldp events",
       NO_STR
       DEBUG_STR
      "MPLS debug\n"
       LDP_STR
       "LDP events\n")
{
  ldp_debug_event = 0;
  return CMD_SUCCESS;
}

DEFUN (no_debug_mpls_ldp_packet,
       no_debug_mpls_ldp_packet_cmd,
       "no debug mpls ldp packet",
       NO_STR
       DEBUG_STR
      "MPLS debug\n"
       LDP_STR
       "LDP packet\n")
{
  ldp_debug_packet = 0;
  return CMD_SUCCESS;
}

DEFUN (no_debug_mpls_ldp_packet_direct,
       no_debug_mpls_ldp_packet_direct_cmd,
       "no debug mpls ldp packet (recv|send)",
       NO_STR
       DEBUG_STR
      "MPLS debug\n"
       LDP_STR
       "LDP packet\n"
       "LDP option set for receive packet\n"
       "LDP option set for send packet\n")
{
  if (strncmp ("send", argv[0], strlen (argv[0])) == 0)
    {
      if (IS_LDP_DEBUG_RECV)
       ldp_debug_packet &= ~LDP_DEBUG_SEND;
      else
       ldp_debug_packet = 0;
    }
  else if (strncmp ("recv", argv[0], strlen (argv[0])) == 0)
    {
      if (IS_LDP_DEBUG_SEND)
       ldp_debug_packet &= ~LDP_DEBUG_RECV;
      else
       ldp_debug_packet = 0;
    }
  return CMD_SUCCESS;
}

DEFUN (no_debug_mpls_ldp_zebra,
       no_debug_mpls_ldp_zebra_cmd,
       "no debug mpls ldp zebra",
       NO_STR
       DEBUG_STR
      "MPLS debug\n"
       LDP_STR
       "LDP and ZEBRA communication\n")
{
  ldp_debug_zebra = 0;
  return CMD_WARNING;
}

/* Debug node. */
static struct cmd_node debug_node =
{
  DEBUG_NODE,
  "",
  1
};

static int
config_write_debug (struct vty *vty)
{
  int write = 0;

  if (IS_LDP_DEBUG_EVENT)
    {
      vty_out (vty, "debug mpls ldp events%s", VTY_NEWLINE);
      write++;
    }
  if (IS_LDP_DEBUG_PACKET)
    {
      if (IS_LDP_DEBUG_SEND && IS_LDP_DEBUG_RECV)
        {
          vty_out (vty, "debug mpls ldp packet%s",
                   VTY_NEWLINE);
          write++;
        }
      else
	{
          if (IS_LDP_DEBUG_SEND)
	    vty_out (vty, "debug mpls ldp packet send%s",
                     VTY_NEWLINE);
          else
            vty_out (vty, "debug mpls ldp packet recv%s",
                     VTY_NEWLINE);
            write++;
        }
    }
  if (IS_LDP_DEBUG_ZEBRA)
    {
      vty_out (vty, "debug mpls ldp zebra%s", VTY_NEWLINE);
      write++;
    }
  return write;
}

void
ldp_debug_init (void)
{
  ldp_debug_event = 0;
  ldp_debug_packet = 0;
  ldp_debug_zebra = 0;

  install_node (&debug_node, config_write_debug);

  install_element (ENABLE_NODE, &show_debugging_mpls_ldp_cmd);
  install_element (ENABLE_NODE, &debug_mpls_ldp_events_cmd);
  install_element (ENABLE_NODE, &debug_mpls_ldp_packet_cmd);
  install_element (ENABLE_NODE, &debug_mpls_ldp_packet_direct_cmd);
  install_element (ENABLE_NODE, &debug_mpls_ldp_zebra_cmd);
  install_element (ENABLE_NODE, &no_debug_mpls_ldp_events_cmd);
  install_element (ENABLE_NODE, &no_debug_mpls_ldp_packet_cmd);
  install_element (ENABLE_NODE, &no_debug_mpls_ldp_packet_direct_cmd);
  install_element (ENABLE_NODE, &no_debug_mpls_ldp_zebra_cmd);

  install_element (CONFIG_NODE, &debug_mpls_ldp_events_cmd);
  install_element (CONFIG_NODE, &debug_mpls_ldp_packet_cmd);
  install_element (CONFIG_NODE, &debug_mpls_ldp_packet_direct_cmd);
  install_element (CONFIG_NODE, &debug_mpls_ldp_zebra_cmd);
  install_element (CONFIG_NODE, &no_debug_mpls_ldp_events_cmd);
  install_element (CONFIG_NODE, &no_debug_mpls_ldp_packet_cmd);
  install_element (CONFIG_NODE, &no_debug_mpls_ldp_packet_direct_cmd);
  install_element (CONFIG_NODE, &no_debug_mpls_ldp_zebra_cmd);
}
