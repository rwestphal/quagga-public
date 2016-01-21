/* Header file exported by rt_netlink.c to zebra.
 * Copyright (C) 1997, 98, 99 Kunihiro Ishiguro
 *
 * This file is part of GNU Zebra.
 *
 * GNU Zebra is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2, or (at your option) any
 * later version.
 *
 * GNU Zebra is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Zebra; see the file COPYING.  If not, write to the Free
 * Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 */

#ifndef _ZEBRA_RT_NETLINK_H
#define _ZEBRA_RT_NETLINK_H

#ifdef HAVE_NETLINK

#define NL_PKT_BUF_SIZE 8192

#define NLMSG_TAIL(nmsg) \
	((struct rtattr *) (((char *) (nmsg)) + NLMSG_ALIGN((nmsg)->nlmsg_len)))

struct nlsock
{
  int sock;
  int seq;
  struct sockaddr_nl snl;
  const char *name;
};

extern int
netlink_socket (struct nlsock *nl, unsigned long groups);
extern int
netlink_talk (struct nlmsghdr *n, struct nlsock *nl);

extern int
addraw_l (struct nlmsghdr *n, int maxlen, void *data, int alen);
extern int
addattr32 (struct nlmsghdr *n, int maxlen, int type, int data);
extern int
addattr_l (struct nlmsghdr *n, int maxlen, int type, void *data, int alen);

static inline struct rtattr *
addattr_nest (struct nlmsghdr *n, int maxlen, int type)
{
  struct rtattr *nest = (struct rtattr *) NLMSG_TAIL(n);
  addattr_l (n, maxlen, type, NULL, 0);
  return nest;
}

static inline int
addattr_nest_end (struct nlmsghdr *n, struct rtattr *nest)
{
  nest->rta_len = (void *)NLMSG_TAIL(n) - (void *)nest;
  return n->nlmsg_len;
}

extern int
rta_addattr_l (struct rtattr *rta, int maxlen, int type, void *data, int alen);

extern const char *
nl_msg_type_to_str (uint16_t msg_type);

extern const char *
nl_rtproto_to_str (u_char rtproto);


#endif /* HAVE_NETLINK */

#endif /* _ZEBRA_RT_NETLINK_H */
