## Process this file with automake to produce Makefile.in.

INCLUDES = @INCLUDES@ -I.. -I$(top_srcdir) -I$(top_srcdir)/lib
DEFS = @DEFS@ -DSYSCONFDIR=\"$(sysconfdir)/\"
INSTALL_SDATA=@INSTALL@ -m 600

AM_CFLAGS = $(PICFLAGS)
AM_LDFLAGS = $(PILDFLAGS)

noinst_LIBRARIES = libimsg.a
sbin_PROGRAMS = ldpd

libimsg_a_SOURCES = \
	imsg-buffer.c  imsg.c

ldpd_SOURCES = \
	address.c hello.c init.c interface.c keepalive.c labelmapping.c \
	lde.c lde_lib.c ldpd.c ldpe.c ldp_debug.c neighbor.c notification.c \
	packet.c ldp_zebra.c ldp_vty.c

noinst_HEADERS = \
	lde.h  ldpd.h  ldpe.h  ldp.h  ldp_debug.h imsg.h

ldpd_LDADD = libimsg.a ../lib/libzebra.la @LIBCAP@

sysconf_DATA = ldpd.conf.sample
