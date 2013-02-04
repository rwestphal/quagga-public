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

#ifndef _LOG_H_
#define	_LOG_H_

#include <stdarg.h>

#include "log.h"

/* LDP debug event flags. */
#define LDP_DEBUG_EVENT   0x01

/* LDP debug packet flags. */
#define LDP_DEBUG_PACKET  0x01
#define LDP_DEBUG_SEND    0x20
#define LDP_DEBUG_RECV    0x40

/* LDP debug zebra flags. */
#define LDP_DEBUG_ZEBRA   0x01

/* Debug related macro. */
#define IS_LDP_DEBUG_EVENT  (ldp_debug_event & LDP_DEBUG_EVENT)

#define IS_LDP_DEBUG_PACKET (ldp_debug_packet & LDP_DEBUG_PACKET)
#define IS_LDP_DEBUG_SEND   (ldp_debug_packet & LDP_DEBUG_SEND)
#define IS_LDP_DEBUG_RECV   (ldp_debug_packet & LDP_DEBUG_RECV)

#define IS_LDP_DEBUG_ZEBRA  (ldp_debug_zebra & LDP_DEBUG_ZEBRA)

extern unsigned long ldp_debug_event;
extern unsigned long ldp_debug_packet;
extern unsigned long ldp_debug_zebra;

struct map;

#define		 log_event(msg, ...)			\
do {							\
	if (IS_LDP_DEBUG_EVENT)				\
		zlog_debug (msg, __VA_ARGS__);		\
} while (0)

#define		 log_pkt_send(msg, ...)			\
do {							\
	if (IS_LDP_DEBUG_SEND)				\
		zlog_debug (msg, __VA_ARGS__);		\
} while (0)

#define		 log_pkt_recv(msg, ...)			\
do {							\
	if (IS_LDP_DEBUG_RECV)				\
		zlog_debug (msg, __VA_ARGS__);		\
} while (0)

#define		 log_zebra(msg, ...)			\
do {							\
	if (IS_LDP_DEBUG_ZEBRA)				\
		zlog_debug (msg, __VA_ARGS__);		\
} while (0)

void		 fatal(const char *);
void		 fatalx(const char *);
const char	*nbr_state_name(int);
const char	*if_state_name(int);
const char	*notification_name(u_int32_t);
const char	*log_fec(struct map *);
void		 ldp_debug_init(void);

#endif /* _LOG_H_ */
