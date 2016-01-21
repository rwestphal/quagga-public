/*
 * Copyright (c) 2005 Claudio Jeker <claudio@openbsd.org>
 * Copyright (c) 2004, 2008 Esben Norby <norby@openbsd.org>
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
#include <lib/version.h>
#include <lib/log.h>

#include "vty.h"
#include "getopt.h"
#include "command.h"
#include "memory.h"
#include "privs.h"
#include "sigevent.h"
#include "prefix.h"
#include "zclient.h"

#include "ldpd.h"
#include "ldpe.h"
#include "lde.h"
#include "ldp_debug.h"

void	main_sig_handler(int, short, void *);
void	ldpd_shutdown(void);
struct ldpd_conf	*ldpd_conf = NULL;

/* ldpd options, we use GNU getopt library. */
struct option longopts[] = {
	{ "daemon",      no_argument,       NULL, 'd'},
	{ "config_file", required_argument, NULL, 'f'},
	{ "pid_file",    required_argument, NULL, 'i'},
	{ "help",        no_argument,       NULL, 'h'},
	{ "vty_addr",    required_argument, NULL, 'A'},
	{ "vty_port",    required_argument, NULL, 'P'},
	{ "version",     no_argument,       NULL, 'v'},
	{ "dryrun",      no_argument,       NULL, 'C'},
	{ 0 }
};

/* configuration filename and directory. */
char			 config_default[] = SYSCONFDIR LDPD_DEFAULT_CONFIG;

/* master of threads. */
struct thread_master	*master;

/* manually specified configuration file name.  */
char 			*config_file = NULL;

/* process ID saved for use by init system */
static const char 	*pid_file = PATH_LDPD_PID;

/* VTY port number and address.  */
int 			 vty_port = LDP_VTY_PORT;
char 			*vty_addr = NULL;

/* SIGINT / SIGTERM handler. */
static void
sigint(void)
{
	zlog_notice ("Terminating on signal");
	ldpd_shutdown();
}

static void
sighup(void)
{
	zlog_info ("SIGHUP received");

	/* reload config file. */
	vty_read_config (config_file, config_default);
}

struct quagga_signal_t ldp_signals[] =
{
	{
		.signal = SIGHUP,
		.handler = &sighup,
	},
	{
		.signal = SIGINT,
		.handler = &sigint,
	},
	{
		.signal = SIGTERM,
		.handler = &sigint,
	},
};

/* privileges */
static zebra_capabilities_t _caps_p [] =
{
	ZCAP_BIND,
	ZCAP_NET_RAW,
};

struct zebra_privs_t ldpd_privs =
{
#if defined(QUAGGA_USER) && defined(QUAGGA_GROUP)
	.user = QUAGGA_USER,
	.group = QUAGGA_GROUP,
#endif
#ifdef VTY_GROUP
	.vty_group = VTY_GROUP,
#endif
	.caps_p = _caps_p,
	.cap_num_p = sizeof(_caps_p)/sizeof(_caps_p[0]),
	.cap_num_i = 0,
};

/* Help information display. */
static void
usage (char *progname, int status)
{
	if (status != 0) {
		fprintf(stderr, "Try `%s --help' for more information.\n",
			progname);
	} else {
		printf("Usage : %s [OPTION...]\n\
Daemon which manages LDP.\n\n\
-d, --daemon       Runs in daemon mode\n\
-f, --config_file  Set configuration file name\n\
-i, --pid_file     Set process identifier file name\n\
-A, --vty_addr     Set vty's bind address\n\
-P, --vty_port     Set vty's port number\n\
-C, --dryrun       Check configuration for validity and exit\n\
-v, --version      Print program version\n\
-h, --help         Display this help and exit\n\
\n\
Report bugs to %s\n", progname, ZEBRA_BUG_ADDRESS);
	}

	exit(status);
}

int
main(int argc, char *argv[])
{
	char		*p;
	int		 daemon_mode = 0;
	int		 dryrun = 0;
	char		*progname;
	struct thread	 thread;

	/* set umask before anything for security */
	umask (0027);

	/* get program name. */
	progname = ((p = strrchr (argv[0], '/')) ? ++p : argv[0]);

	/* first of all we need logging init. */
	zlog_default = openzlog (progname, ZLOG_LDP, LOG_NDELAY, LOG_DAEMON);

	/* command line option parse. */
	while (1) {
		int opt;

		opt = getopt_long(argc, argv, "df:i:hA:P:u:g:rvC", longopts, 0);

		if (opt == EOF)
			break;

		switch(opt) {
		case 0:
			break;
		case 'd':
			daemon_mode = 1;
			break;
		case 'f':
			config_file = optarg;
			break;
		case 'A':
			vty_addr = optarg;
			break;
		case 'i':
			pid_file = optarg;
			break;
		case 'P':
			/*
			 * deal with atoi() returning 0 on failure, and ldpd not
			 * listening on ldp port...
			 */
			if (strcmp(optarg, "0") == 0) {
				vty_port = 0;
				break;
			}
			vty_port = atoi(optarg);
			if (vty_port <= 0 || vty_port > 0xffff)
				vty_port = LDP_VTY_PORT;
			break;
		case 'C':
			dryrun = 1;
			break;
		case 'v':
			print_version(progname);
			exit(0);
			break;
		case 'h':
			usage(progname, 0);
			break;
		default:
			usage(progname, 1);
			break;
		}
	}

	/* prepare master thread */
	master = thread_master_create();

	/* library initialization */
	zprivs_init (&ldpd_privs);
	signal_init (master, array_size(ldp_signals), ldp_signals);
	cmd_init(1);
	vty_init(master);
	memory_init();

	/* zebra related initialization */
	ldp_zebra_init ();

	/* ldp vty commands */
	ldp_vty_init ();

	/* sort all installed commands */
	sort_node();

	/* create global configuration structure */
	ldpd_conf = XCALLOC(MTYPE_LDP, sizeof(struct ldpd_conf));
	ldpd_conf->ldp_enabled = 1;
	ldpd_conf->mode = (MODE_DIST_INDEPENDENT | MODE_RET_LIBERAL |
			   MODE_ADV_UNSOLICITED);
	ldpd_conf->holdtime = DEFAULT_HOLDTIME;
	ldpd_conf->keepalive = DEFAULT_KEEPALIVE;
	ldpd_conf->hello_interval = DEFAULT_HELLO_INTERVAL;

	/* start lde and ldpe engines */
	lde();
	ldpe();

	/* get configuration file */
	vty_read_config(config_file, config_default);

	/* start execution only if not in dry-run mode */
	if(dryrun)
		return (0);

	/* change to the daemon program */
	if (daemon_mode && daemon (0, 0) < 0) {
		zlog_err("LDPd daemon failed: %s", strerror(errno));
		exit (1);
	}

	/* pid file create */
	pid_output(pid_file);

	/* create VTY's socket */
	vty_serv_sock(vty_addr, vty_port, LDP_VTYSH_PATH);

	/* main loop */
	while (thread_fetch (master, &thread))
	  thread_call (&thread);

	ldpd_shutdown();
	/* NOTREACHED */
	return (0);
}

void
ldpd_shutdown(void)
{
	struct iface		*iface;
	struct interface	*ifp;
	struct listnode		*node, *nnode;
	extern struct zclient	*zclient;

	zprivs_terminate (&ldpd_privs);

	/* stop all interfaces */
	LIST_FOREACH(iface, &ldpd_conf->iface_list, entry) {
		if (!ldp_if_enabled(iface))
			continue;

		if (if_fsm(iface, IF_EVT_DOWN)) {
			zlog_debug("error stopping interface %s", iface->name);
		}
	}

	for (ALL_LIST_ELEMENTS (iflist, node, nnode, ifp))
		if_delete (ifp);
	list_free (iflist);

	/* LDP related stuff */
	lde_nbr_clear();
	nbr_clear();
	rt_clear();
	XFREE(MTYPE_LDP, pkt_ptr);
	close(ldpd_conf->ldp_session_socket);
	XFREE(MTYPE_LDP, ldpd_conf);

	/* quagga framework related stuff */
	cmd_terminate();
	vty_terminate();
	if (zclient)
		zclient_free(zclient);
	if (master)
		thread_master_free(master);
	if (zlog_default)
		closezlog(zlog_default);

	exit(0);
}

/* ARGSUSED */
void
ldpd_process(int type, void *data, u_int16_t datalen)
{
	struct kroute *kr;

	switch (type) {
	case IMSG_ZEBRA_CHANGE_INPUT_LABEL:
	case IMSG_ZEBRA_ADD_LSP:
	case IMSG_ZEBRA_DELETE_LSP:
		if (datalen != sizeof(struct kroute))
			fatalx("invalid size of OE request");
		kr = data;
		switch (type) {
		case IMSG_ZEBRA_CHANGE_INPUT_LABEL:
			ldp_zebra_send_change_input_label(kr);
			break;
		case IMSG_ZEBRA_ADD_LSP:
			ldp_zebra_send_lsp(ZEBRA_MPLS_ADD_LSP, kr);
			break;
		case IMSG_ZEBRA_DELETE_LSP:
			ldp_zebra_send_lsp(ZEBRA_MPLS_DELETE_LSP, kr);
			break;
		}
		break;
	default:
		zlog_debug("ldpd_process: error handling imsg %d", type);
		break;
	}
}

void
evbuf_enqueue(struct evbuf *eb, struct ibuf *buf)
{
	ibuf_close(&eb->wbuf, buf);
	evbuf_event_add(eb);
}

void
evbuf_event_add(struct evbuf *eb)
{
	if (eb->wbuf.queued)
		THREAD_WRITE_ON(master, eb->t_write, eb->handler, eb->arg,
				eb->wbuf.fd);
}

void
evbuf_init(struct evbuf *eb, int fd, int (*handler)(struct thread *),
	   void *arg)
{
	msgbuf_init(&eb->wbuf);
	eb->wbuf.fd = fd;
	eb->handler = handler;
	eb->arg = arg;
}

void
evbuf_clear(struct evbuf *eb)
{
	THREAD_WRITE_OFF(eb->t_write);
	msgbuf_clear(&eb->wbuf);
	eb->wbuf.fd = -1;
}

void
session_socket_blockmode(int fd, enum blockmodes bm)
{
	int	flags;

	if ((flags = fcntl(fd, F_GETFL, 0)) == -1)
		fatal("fcntl F_GETFL");

	if (bm == BM_NONBLOCK)
		flags |= O_NONBLOCK;
	else
		flags &= ~O_NONBLOCK;

	if ((flags = fcntl(fd, F_SETFL, flags)) == -1)
		fatal("fcntl F_SETFL");
}
