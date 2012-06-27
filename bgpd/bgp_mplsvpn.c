/* MPLS-VPN
   Copyright (C) 2000 Kunihiro Ishiguro <kunihiro@zebra.org>

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
#include "log.h"
#include "memory.h"
#include "stream.h"

#include "bgpd/bgpd.h"
#include "bgpd/bgp_debug.h"
#include "bgpd/bgp_table.h"
#include "bgpd/bgp_route.h"
#include "bgpd/bgp_attr.h"
#include "bgpd/bgp_mplsvpn.h"

u_int16_t
decode_rd_type (u_char *pnt)
{
  u_int16_t v;
  
  v = ((u_int16_t) *pnt++ << 8);
  v |= (u_int16_t) *pnt;
  return v;
}

u_int32_t
decode_label (u_char *pnt)
{
  u_int32_t l;

  l = ((u_int32_t) *pnt++ << 12);
  l |= (u_int32_t) *pnt++ << 4;
  l |= (u_int32_t) ((*pnt & 0xf0) >> 4);
  return l;
}

void
decode_rd_as (u_char *pnt, struct rd_as *rd_as)
{
  rd_as->as = (u_int16_t) *pnt++ << 8;
  rd_as->as |= (u_int16_t) *pnt++;
  
  rd_as->val = ((u_int32_t) *pnt++ << 24);
  rd_as->val |= ((u_int32_t) *pnt++ << 16);
  rd_as->val |= ((u_int32_t) *pnt++ << 8);
  rd_as->val |= (u_int32_t) *pnt;
}

void
decode_rd_ip (u_char *pnt, struct rd_ip *rd_ip)
{
  memcpy (&rd_ip->ip, pnt, 4);
  pnt += 4;
  
  rd_ip->val = ((u_int16_t) *pnt++ << 8);
  rd_ip->val |= (u_int16_t) *pnt;
}

void
decode_rd_as4 (u_char *pnt, struct rd_as4 *rd_as4)
{
  rd_as4->as4 = ((u_int32_t) *pnt++ << 24);
  rd_as4->as4 |= ((u_int32_t) *pnt++ << 16);
  rd_as4->as4 |= ((u_int32_t) *pnt++ << 8);
  rd_as4->as4 |= (u_int32_t) *pnt++;

  rd_as4->val = (u_int16_t) *pnt++ << 8;
  rd_as4->val |= (u_int16_t) *pnt;
}

int
bgp_nlri_parse_vpnv4 (struct peer *peer, struct attr *attr, 
		      struct bgp_nlri *packet)
{
  u_char *pnt;
  u_char *lim;
  struct prefix p;
  int psize;
  int prefixlen;
  u_int32_t label;
  u_int16_t type;
  struct rd_as rd_as;
  struct rd_ip rd_ip;
  struct rd_as4 rd_as4;
  struct prefix_rd prd;
  u_char *labelpnt;

  /* Check peer status. */
  if (peer->status != Established)
    return 0;
  
  /* Make prefix_rd */
  prd.family = AF_UNSPEC;
  prd.prefixlen = 64;

  pnt = packet->nlri;
  lim = pnt + packet->length;

  for (; pnt < lim; pnt += psize)
    {
      /* Clear prefix structure. */
      memset (&p, 0, sizeof (struct prefix));

      /* Fetch prefix length. */
      prefixlen = *pnt++;
      p.family = AF_INET;
      psize = PSIZE (prefixlen);

      if (prefixlen < 88)
	{
	  zlog_err ("prefix length is less than 88: %d", prefixlen);
	  return -1;
	}

      label = decode_label (pnt);

      /* Copyr label to prefix. */
      labelpnt = pnt;;

      /* Copy routing distinguisher to rd. */
      memcpy (&prd.val, pnt + 3, 8);

      /* Decode RD type. */
      type = decode_rd_type (pnt + 3);

      /* Decode RD value. */
      if (type == RD_TYPE_AS)
	decode_rd_as (pnt + 5, &rd_as);
      else if (type == RD_TYPE_IP)
	decode_rd_ip (pnt + 5, &rd_ip);
      else if (type == RD_TYPE_AS4)
	decode_rd_as4 (pnt + 5, &rd_as4);
      else
	{
	  zlog_err ("Invalid RD type %d", type);
	  return -1;
	}

      p.prefixlen = prefixlen - 88;
      memcpy (&p.u.prefix, pnt + 11, psize - 11);

#if 0
      /* Received Logging - this don't belong here. */
      if (BGP_DEBUG (update, UPDATE_IN))
	{
	  char buf[RD_ADDRSTRLEN];

	  zlog (peer->log, LOG_DEBUG, "%s rcvd %s:%s/%d, label %u", peer->host,
		prefix_rd2str (&prd, buf, RD_ADDRSTRLEN), inet_ntoa (p.u.prefix4),
		p.prefixlen, label);
	}
#endif /* 0 */

      if (pnt + psize > lim)
	return -1;

      if (attr)
	bgp_update (peer, &p, attr, AFI_IP, SAFI_MPLS_VPN,
		    ZEBRA_ROUTE_BGP, BGP_ROUTE_NORMAL, &prd, labelpnt, 0);
      else
	bgp_withdraw (peer, &p, attr, AFI_IP, SAFI_MPLS_VPN,
		      ZEBRA_ROUTE_BGP, BGP_ROUTE_NORMAL, &prd, labelpnt);
    }

  /* Packet length consistency check. */
  if (pnt != lim)
    return -1;

  return 0;
}

int
str2prefix_rd (const char *str, struct prefix_rd *prd)
{
  int ret;
  char *colon;
  struct stream *s;
  char *first_half;
  char *second_half;
  char *endptr = NULL;
  struct in_addr addr;
  unsigned long v1;
  unsigned long v2;

  prd->family = AF_UNSPEC;
  prd->prefixlen = 64;

  colon = strchr (str, ':');
  if (! colon)
    return 0;

  first_half = XMALLOC (MTYPE_TMP, (colon - str) + 1);
  memcpy (first_half, str, (colon - str));
  first_half[colon - str] = '\0';
  second_half = colon + 1;

  s = stream_new (8);

  /* RD type 0 */
  if (! strchr (first_half, '.'))
    {
      stream_putw (s, RD_TYPE_AS);

      errno = 0;
      v1 = strtoul (first_half, &endptr, 10);
      if (*endptr != '\0' || errno || v1 > UINT16_MAX)
        goto error;

      errno = 0;
      v2 = strtoul (second_half, &endptr, 10);
      if (*endptr != '\0' || errno || v2 > UINT32_MAX)
        goto error;

      stream_putw (s, (u_int16_t) v1);
      stream_putl (s, v2);
    }
  /* RD type 1 */
  else
    {
      /* Use inet_pton to allow only the IPv4 dotted-quad notation. */
      ret = inet_pton (AF_INET, first_half, &addr);
      if (ret != 1)
        goto error;

      stream_putw (s, RD_TYPE_IP);

      errno = 0;
      v2 = strtoul (second_half, &endptr, 10);
      if (*endptr != '\0' || errno || v2 > UINT16_MAX)
        goto error;

      stream_put_in_addr (s, &addr);
      stream_putw (s, (u_int16_t) v2);
    }
  memcpy (prd->val, s->data, 8);

  stream_free (s);
  XFREE (MTYPE_TMP, first_half);
  return 1;

error:
  stream_free (s);
  XFREE (MTYPE_TMP, first_half);
  return 0;
}

char *
prefix_rd2str (struct prefix_rd *prd, char *buf, size_t size)
{
  u_char *pnt;
  u_int16_t type;
  struct rd_as rd_as;
  struct rd_ip rd_ip;
  struct rd_as4 rd_as4;

  if (size < RD_ADDRSTRLEN)
    return NULL;

  pnt = prd->val;

  type = decode_rd_type (pnt);

  if (type == RD_TYPE_AS)
    {
      decode_rd_as (pnt + 2, &rd_as);
      snprintf (buf, size, "%u:%u", rd_as.as, rd_as.val);
      return buf;
    }
  else if (type == RD_TYPE_IP)
    {
      decode_rd_ip (pnt + 2, &rd_ip);
      snprintf (buf, size, "%s:%u", inet_ntoa (rd_ip.ip), rd_ip.val);
      return buf;
    }
  else if (type == RD_TYPE_AS4)
    {
      decode_rd_as4 (pnt + 2, &rd_as4);
      snprintf (buf, size, "%u:%u", rd_as4.as4, rd_as4.val);
      return buf;
    }

  return NULL;
}
