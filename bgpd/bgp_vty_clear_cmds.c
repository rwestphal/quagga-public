/* Auto-generated from bgp_vty_clear.xml. */
/* Do not edit! */

#include <zebra.h>

#include "command.h"
#include "vty.h"
#include "bgp_vty_clear.h"

DEFUN (clear_bgp_ipv4_safi_all,
       clear_bgp_ipv4_safi_all_cmd,
       "clear bgp ipv4 (unicast|multicast) *",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all peers\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_all_in,
       clear_bgp_ipv4_safi_all_in_cmd,
       "clear bgp ipv4 (unicast|multicast) * in",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_all_in_prefix_filter,
       clear_bgp_ipv4_safi_all_in_prefix_filter_cmd,
       "clear bgp ipv4 (unicast|multicast) * in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_all_out,
       clear_bgp_ipv4_safi_all_out_cmd,
       "clear bgp ipv4 (unicast|multicast) * out",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_all_soft,
       clear_bgp_ipv4_safi_all_soft_cmd,
       "clear bgp ipv4 (unicast|multicast) * soft",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_all_soft_in,
       clear_bgp_ipv4_safi_all_soft_in_cmd,
       "clear bgp ipv4 (unicast|multicast) * soft in",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_all_soft_in_prefix_filter,
       clear_bgp_ipv4_safi_all_soft_in_prefix_filter_cmd,
       "clear bgp ipv4 (unicast|multicast) * soft in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_all_soft_out,
       clear_bgp_ipv4_safi_all_soft_out_cmd,
       "clear bgp ipv4 (unicast|multicast) * soft out",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_all_rsclient,
       clear_bgp_ipv4_safi_all_rsclient_cmd,
       "clear bgp ipv4 (unicast|multicast) * rsclient",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_asn,
       clear_bgp_ipv4_safi_asn_cmd,
       "clear bgp ipv4 (unicast|multicast) <1-4294967295>",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "asn", .value = argv[1] },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_asn_in,
       clear_bgp_ipv4_safi_asn_in_cmd,
       "clear bgp ipv4 (unicast|multicast) <1-4294967295> in",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "asn", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_asn_in_prefix_filter,
       clear_bgp_ipv4_safi_asn_in_prefix_filter_cmd,
       "clear bgp ipv4 (unicast|multicast) <1-4294967295> in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "asn", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_asn_out,
       clear_bgp_ipv4_safi_asn_out_cmd,
       "clear bgp ipv4 (unicast|multicast) <1-4294967295> out",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "asn", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_asn_soft,
       clear_bgp_ipv4_safi_asn_soft_cmd,
       "clear bgp ipv4 (unicast|multicast) <1-4294967295> soft",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "asn", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_asn_soft_in,
       clear_bgp_ipv4_safi_asn_soft_in_cmd,
       "clear bgp ipv4 (unicast|multicast) <1-4294967295> soft in",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "asn", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_asn_soft_in_prefix_filter,
       clear_bgp_ipv4_safi_asn_soft_in_prefix_filter_cmd,
       "clear bgp ipv4 (unicast|multicast) <1-4294967295> soft in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "asn", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_asn_soft_out,
       clear_bgp_ipv4_safi_asn_soft_out_cmd,
       "clear bgp ipv4 (unicast|multicast) <1-4294967295> soft out",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "asn", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_asn_rsclient,
       clear_bgp_ipv4_safi_asn_rsclient_cmd,
       "clear bgp ipv4 (unicast|multicast) <1-4294967295> rsclient",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "asn", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_ipv4,
       clear_bgp_ipv4_safi_ipv4_cmd,
       "clear bgp ipv4 (unicast|multicast) A.B.C.D",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_ipv4_in,
       clear_bgp_ipv4_safi_ipv4_in_cmd,
       "clear bgp ipv4 (unicast|multicast) A.B.C.D in",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_ipv4_in_prefix_filter,
       clear_bgp_ipv4_safi_ipv4_in_prefix_filter_cmd,
       "clear bgp ipv4 (unicast|multicast) A.B.C.D in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_ipv4_out,
       clear_bgp_ipv4_safi_ipv4_out_cmd,
       "clear bgp ipv4 (unicast|multicast) A.B.C.D out",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_ipv4_soft,
       clear_bgp_ipv4_safi_ipv4_soft_cmd,
       "clear bgp ipv4 (unicast|multicast) A.B.C.D soft",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_ipv4_soft_in,
       clear_bgp_ipv4_safi_ipv4_soft_in_cmd,
       "clear bgp ipv4 (unicast|multicast) A.B.C.D soft in",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_ipv4_soft_in_prefix_filter,
       clear_bgp_ipv4_safi_ipv4_soft_in_prefix_filter_cmd,
       "clear bgp ipv4 (unicast|multicast) A.B.C.D soft in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_ipv4_soft_out,
       clear_bgp_ipv4_safi_ipv4_soft_out_cmd,
       "clear bgp ipv4 (unicast|multicast) A.B.C.D soft out",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_ipv4_rsclient,
       clear_bgp_ipv4_safi_ipv4_rsclient_cmd,
       "clear bgp ipv4 (unicast|multicast) A.B.C.D rsclient",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_ipv6,
       clear_bgp_ipv4_safi_ipv6_cmd,
       "clear bgp ipv4 (unicast|multicast) X:X::X:X",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_ipv6_in,
       clear_bgp_ipv4_safi_ipv6_in_cmd,
       "clear bgp ipv4 (unicast|multicast) X:X::X:X in",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_ipv6_in_prefix_filter,
       clear_bgp_ipv4_safi_ipv6_in_prefix_filter_cmd,
       "clear bgp ipv4 (unicast|multicast) X:X::X:X in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_ipv6_out,
       clear_bgp_ipv4_safi_ipv6_out_cmd,
       "clear bgp ipv4 (unicast|multicast) X:X::X:X out",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_ipv6_soft,
       clear_bgp_ipv4_safi_ipv6_soft_cmd,
       "clear bgp ipv4 (unicast|multicast) X:X::X:X soft",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_ipv6_soft_in,
       clear_bgp_ipv4_safi_ipv6_soft_in_cmd,
       "clear bgp ipv4 (unicast|multicast) X:X::X:X soft in",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_ipv6_soft_in_prefix_filter,
       clear_bgp_ipv4_safi_ipv6_soft_in_prefix_filter_cmd,
       "clear bgp ipv4 (unicast|multicast) X:X::X:X soft in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_ipv6_soft_out,
       clear_bgp_ipv4_safi_ipv6_soft_out_cmd,
       "clear bgp ipv4 (unicast|multicast) X:X::X:X soft out",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_ipv6_rsclient,
       clear_bgp_ipv4_safi_ipv6_rsclient_cmd,
       "clear bgp ipv4 (unicast|multicast) X:X::X:X rsclient",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_external,
       clear_bgp_ipv4_safi_external_cmd,
       "clear bgp ipv4 (unicast|multicast) external",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all external peers\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_external_in,
       clear_bgp_ipv4_safi_external_in_cmd,
       "clear bgp ipv4 (unicast|multicast) external in",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_external_in_prefix_filter,
       clear_bgp_ipv4_safi_external_in_prefix_filter_cmd,
       "clear bgp ipv4 (unicast|multicast) external in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_external_out,
       clear_bgp_ipv4_safi_external_out_cmd,
       "clear bgp ipv4 (unicast|multicast) external out",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_external_soft,
       clear_bgp_ipv4_safi_external_soft_cmd,
       "clear bgp ipv4 (unicast|multicast) external soft",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_external_soft_in,
       clear_bgp_ipv4_safi_external_soft_in_cmd,
       "clear bgp ipv4 (unicast|multicast) external soft in",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_external_soft_in_prefix_filter,
       clear_bgp_ipv4_safi_external_soft_in_prefix_filter_cmd,
       "clear bgp ipv4 (unicast|multicast) external soft in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_external_soft_out,
       clear_bgp_ipv4_safi_external_soft_out_cmd,
       "clear bgp ipv4 (unicast|multicast) external soft out",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_external_rsclient,
       clear_bgp_ipv4_safi_external_rsclient_cmd,
       "clear bgp ipv4 (unicast|multicast) external rsclient",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_peer_group_word,
       clear_bgp_ipv4_safi_peer_group_word_cmd,
       "clear bgp ipv4 (unicast|multicast) peer-group WORD",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "peer_group", .value = argv[1] },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_peer_group_word_in,
       clear_bgp_ipv4_safi_peer_group_word_in_cmd,
       "clear bgp ipv4 (unicast|multicast) peer-group WORD in",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "peer_group", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_peer_group_word_in_prefix_filter,
       clear_bgp_ipv4_safi_peer_group_word_in_prefix_filter_cmd,
       "clear bgp ipv4 (unicast|multicast) peer-group WORD in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "peer_group", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_peer_group_word_out,
       clear_bgp_ipv4_safi_peer_group_word_out_cmd,
       "clear bgp ipv4 (unicast|multicast) peer-group WORD out",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "peer_group", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_peer_group_word_soft,
       clear_bgp_ipv4_safi_peer_group_word_soft_cmd,
       "clear bgp ipv4 (unicast|multicast) peer-group WORD soft",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "peer_group", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_peer_group_word_soft_in,
       clear_bgp_ipv4_safi_peer_group_word_soft_in_cmd,
       "clear bgp ipv4 (unicast|multicast) peer-group WORD soft in",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "peer_group", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_peer_group_word_soft_in_prefix_filter,
       clear_bgp_ipv4_safi_peer_group_word_soft_in_prefix_filter_cmd,
       "clear bgp ipv4 (unicast|multicast) peer-group WORD soft in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "peer_group", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_peer_group_word_soft_out,
       clear_bgp_ipv4_safi_peer_group_word_soft_out_cmd,
       "clear bgp ipv4 (unicast|multicast) peer-group WORD soft out",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "peer_group", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_peer_group_word_rsclient,
       clear_bgp_ipv4_safi_peer_group_word_rsclient_cmd,
       "clear bgp ipv4 (unicast|multicast) peer-group WORD rsclient",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "peer_group", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_dampening,
       clear_bgp_ipv4_safi_dampening_cmd,
       "clear bgp ipv4 (unicast|multicast) dampening",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear route flap dampening information\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_dampening_ipv4,
       clear_bgp_ipv4_safi_dampening_ipv4_cmd,
       "clear bgp ipv4 (unicast|multicast) dampening A.B.C.D",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear route flap dampening information\n"
       "Network to clear damping information\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "network", .value = argv[1] },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_dampening_ipv4_in,
       clear_bgp_ipv4_safi_dampening_ipv4_in_cmd,
       "clear bgp ipv4 (unicast|multicast) dampening A.B.C.D in",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear route flap dampening information\n"
       "Network to clear damping information\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "network", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_dampening_ipv4_in_prefix_filter,
       clear_bgp_ipv4_safi_dampening_ipv4_in_prefix_filter_cmd,
       "clear bgp ipv4 (unicast|multicast) dampening A.B.C.D in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear route flap dampening information\n"
       "Network to clear damping information\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "network", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_dampening_ipv4_out,
       clear_bgp_ipv4_safi_dampening_ipv4_out_cmd,
       "clear bgp ipv4 (unicast|multicast) dampening A.B.C.D out",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear route flap dampening information\n"
       "Network to clear damping information\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "network", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_dampening_ipv4_soft,
       clear_bgp_ipv4_safi_dampening_ipv4_soft_cmd,
       "clear bgp ipv4 (unicast|multicast) dampening A.B.C.D soft",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear route flap dampening information\n"
       "Network to clear damping information\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "network", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_dampening_ipv4_soft_in,
       clear_bgp_ipv4_safi_dampening_ipv4_soft_in_cmd,
       "clear bgp ipv4 (unicast|multicast) dampening A.B.C.D soft in",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear route flap dampening information\n"
       "Network to clear damping information\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "network", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_dampening_ipv4_soft_in_prefix_filter,
       clear_bgp_ipv4_safi_dampening_ipv4_soft_in_prefix_filter_cmd,
       "clear bgp ipv4 (unicast|multicast) dampening A.B.C.D soft in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear route flap dampening information\n"
       "Network to clear damping information\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "network", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_dampening_ipv4_soft_out,
       clear_bgp_ipv4_safi_dampening_ipv4_soft_out_cmd,
       "clear bgp ipv4 (unicast|multicast) dampening A.B.C.D soft out",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear route flap dampening information\n"
       "Network to clear damping information\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "network", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_dampening_ipv4_rsclient,
       clear_bgp_ipv4_safi_dampening_ipv4_rsclient_cmd,
       "clear bgp ipv4 (unicast|multicast) dampening A.B.C.D rsclient",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear route flap dampening information\n"
       "Network to clear damping information\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "network", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_dampening_ipv4m,
       clear_bgp_ipv4_safi_dampening_ipv4m_cmd,
       "clear bgp ipv4 (unicast|multicast) dampening A.B.C.D/M",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear route flap dampening information\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "prefix", .value = argv[1] },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_dampening_ipv4m_in,
       clear_bgp_ipv4_safi_dampening_ipv4m_in_cmd,
       "clear bgp ipv4 (unicast|multicast) dampening A.B.C.D/M in",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear route flap dampening information\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "prefix", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_dampening_ipv4m_in_prefix_filter,
       clear_bgp_ipv4_safi_dampening_ipv4m_in_prefix_filter_cmd,
       "clear bgp ipv4 (unicast|multicast) dampening A.B.C.D/M in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear route flap dampening information\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "prefix", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_dampening_ipv4m_out,
       clear_bgp_ipv4_safi_dampening_ipv4m_out_cmd,
       "clear bgp ipv4 (unicast|multicast) dampening A.B.C.D/M out",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear route flap dampening information\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "prefix", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_dampening_ipv4m_soft,
       clear_bgp_ipv4_safi_dampening_ipv4m_soft_cmd,
       "clear bgp ipv4 (unicast|multicast) dampening A.B.C.D/M soft",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear route flap dampening information\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "prefix", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_dampening_ipv4m_soft_in,
       clear_bgp_ipv4_safi_dampening_ipv4m_soft_in_cmd,
       "clear bgp ipv4 (unicast|multicast) dampening A.B.C.D/M soft in",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear route flap dampening information\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "prefix", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_dampening_ipv4m_soft_in_prefix_filter,
       clear_bgp_ipv4_safi_dampening_ipv4m_soft_in_prefix_filter_cmd,
       "clear bgp ipv4 (unicast|multicast) dampening A.B.C.D/M soft in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear route flap dampening information\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "prefix", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_dampening_ipv4m_soft_out,
       clear_bgp_ipv4_safi_dampening_ipv4m_soft_out_cmd,
       "clear bgp ipv4 (unicast|multicast) dampening A.B.C.D/M soft out",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear route flap dampening information\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "prefix", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_bgp_ipv4_safi_dampening_ipv4m_rsclient,
       clear_bgp_ipv4_safi_dampening_ipv4m_rsclient_cmd,
       "clear bgp ipv4 (unicast|multicast) dampening A.B.C.D/M rsclient",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear route flap dampening information\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "prefix", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_all,
       clear_bgp_ipv6_safi_all_cmd,
       "clear bgp ipv6 (unicast|multicast) *",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all peers\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_all_in,
       clear_bgp_ipv6_safi_all_in_cmd,
       "clear bgp ipv6 (unicast|multicast) * in",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_all_in_prefix_filter,
       clear_bgp_ipv6_safi_all_in_prefix_filter_cmd,
       "clear bgp ipv6 (unicast|multicast) * in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_all_out,
       clear_bgp_ipv6_safi_all_out_cmd,
       "clear bgp ipv6 (unicast|multicast) * out",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_all_soft,
       clear_bgp_ipv6_safi_all_soft_cmd,
       "clear bgp ipv6 (unicast|multicast) * soft",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_all_soft_in,
       clear_bgp_ipv6_safi_all_soft_in_cmd,
       "clear bgp ipv6 (unicast|multicast) * soft in",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_all_soft_in_prefix_filter,
       clear_bgp_ipv6_safi_all_soft_in_prefix_filter_cmd,
       "clear bgp ipv6 (unicast|multicast) * soft in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_all_soft_out,
       clear_bgp_ipv6_safi_all_soft_out_cmd,
       "clear bgp ipv6 (unicast|multicast) * soft out",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_all_rsclient,
       clear_bgp_ipv6_safi_all_rsclient_cmd,
       "clear bgp ipv6 (unicast|multicast) * rsclient",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_asn,
       clear_bgp_ipv6_safi_asn_cmd,
       "clear bgp ipv6 (unicast|multicast) <1-4294967295>",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "asn", .value = argv[1] },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_asn_in,
       clear_bgp_ipv6_safi_asn_in_cmd,
       "clear bgp ipv6 (unicast|multicast) <1-4294967295> in",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "asn", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_asn_in_prefix_filter,
       clear_bgp_ipv6_safi_asn_in_prefix_filter_cmd,
       "clear bgp ipv6 (unicast|multicast) <1-4294967295> in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "asn", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_asn_out,
       clear_bgp_ipv6_safi_asn_out_cmd,
       "clear bgp ipv6 (unicast|multicast) <1-4294967295> out",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "asn", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_asn_soft,
       clear_bgp_ipv6_safi_asn_soft_cmd,
       "clear bgp ipv6 (unicast|multicast) <1-4294967295> soft",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "asn", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_asn_soft_in,
       clear_bgp_ipv6_safi_asn_soft_in_cmd,
       "clear bgp ipv6 (unicast|multicast) <1-4294967295> soft in",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "asn", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_asn_soft_in_prefix_filter,
       clear_bgp_ipv6_safi_asn_soft_in_prefix_filter_cmd,
       "clear bgp ipv6 (unicast|multicast) <1-4294967295> soft in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "asn", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_asn_soft_out,
       clear_bgp_ipv6_safi_asn_soft_out_cmd,
       "clear bgp ipv6 (unicast|multicast) <1-4294967295> soft out",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "asn", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_asn_rsclient,
       clear_bgp_ipv6_safi_asn_rsclient_cmd,
       "clear bgp ipv6 (unicast|multicast) <1-4294967295> rsclient",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "asn", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_ipv4,
       clear_bgp_ipv6_safi_ipv4_cmd,
       "clear bgp ipv6 (unicast|multicast) A.B.C.D",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_ipv4_in,
       clear_bgp_ipv6_safi_ipv4_in_cmd,
       "clear bgp ipv6 (unicast|multicast) A.B.C.D in",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_ipv4_in_prefix_filter,
       clear_bgp_ipv6_safi_ipv4_in_prefix_filter_cmd,
       "clear bgp ipv6 (unicast|multicast) A.B.C.D in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_ipv4_out,
       clear_bgp_ipv6_safi_ipv4_out_cmd,
       "clear bgp ipv6 (unicast|multicast) A.B.C.D out",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_ipv4_soft,
       clear_bgp_ipv6_safi_ipv4_soft_cmd,
       "clear bgp ipv6 (unicast|multicast) A.B.C.D soft",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_ipv4_soft_in,
       clear_bgp_ipv6_safi_ipv4_soft_in_cmd,
       "clear bgp ipv6 (unicast|multicast) A.B.C.D soft in",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_ipv4_soft_in_prefix_filter,
       clear_bgp_ipv6_safi_ipv4_soft_in_prefix_filter_cmd,
       "clear bgp ipv6 (unicast|multicast) A.B.C.D soft in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_ipv4_soft_out,
       clear_bgp_ipv6_safi_ipv4_soft_out_cmd,
       "clear bgp ipv6 (unicast|multicast) A.B.C.D soft out",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_ipv4_rsclient,
       clear_bgp_ipv6_safi_ipv4_rsclient_cmd,
       "clear bgp ipv6 (unicast|multicast) A.B.C.D rsclient",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_ipv6,
       clear_bgp_ipv6_safi_ipv6_cmd,
       "clear bgp ipv6 (unicast|multicast) X:X::X:X",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_ipv6_in,
       clear_bgp_ipv6_safi_ipv6_in_cmd,
       "clear bgp ipv6 (unicast|multicast) X:X::X:X in",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_ipv6_in_prefix_filter,
       clear_bgp_ipv6_safi_ipv6_in_prefix_filter_cmd,
       "clear bgp ipv6 (unicast|multicast) X:X::X:X in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_ipv6_out,
       clear_bgp_ipv6_safi_ipv6_out_cmd,
       "clear bgp ipv6 (unicast|multicast) X:X::X:X out",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_ipv6_soft,
       clear_bgp_ipv6_safi_ipv6_soft_cmd,
       "clear bgp ipv6 (unicast|multicast) X:X::X:X soft",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_ipv6_soft_in,
       clear_bgp_ipv6_safi_ipv6_soft_in_cmd,
       "clear bgp ipv6 (unicast|multicast) X:X::X:X soft in",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_ipv6_soft_in_prefix_filter,
       clear_bgp_ipv6_safi_ipv6_soft_in_prefix_filter_cmd,
       "clear bgp ipv6 (unicast|multicast) X:X::X:X soft in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_ipv6_soft_out,
       clear_bgp_ipv6_safi_ipv6_soft_out_cmd,
       "clear bgp ipv6 (unicast|multicast) X:X::X:X soft out",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_ipv6_rsclient,
       clear_bgp_ipv6_safi_ipv6_rsclient_cmd,
       "clear bgp ipv6 (unicast|multicast) X:X::X:X rsclient",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_external,
       clear_bgp_ipv6_safi_external_cmd,
       "clear bgp ipv6 (unicast|multicast) external",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all external peers\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_external_in,
       clear_bgp_ipv6_safi_external_in_cmd,
       "clear bgp ipv6 (unicast|multicast) external in",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_external_in_prefix_filter,
       clear_bgp_ipv6_safi_external_in_prefix_filter_cmd,
       "clear bgp ipv6 (unicast|multicast) external in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_external_out,
       clear_bgp_ipv6_safi_external_out_cmd,
       "clear bgp ipv6 (unicast|multicast) external out",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_external_soft,
       clear_bgp_ipv6_safi_external_soft_cmd,
       "clear bgp ipv6 (unicast|multicast) external soft",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_external_soft_in,
       clear_bgp_ipv6_safi_external_soft_in_cmd,
       "clear bgp ipv6 (unicast|multicast) external soft in",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_external_soft_in_prefix_filter,
       clear_bgp_ipv6_safi_external_soft_in_prefix_filter_cmd,
       "clear bgp ipv6 (unicast|multicast) external soft in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_external_soft_out,
       clear_bgp_ipv6_safi_external_soft_out_cmd,
       "clear bgp ipv6 (unicast|multicast) external soft out",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_external_rsclient,
       clear_bgp_ipv6_safi_external_rsclient_cmd,
       "clear bgp ipv6 (unicast|multicast) external rsclient",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_peer_group_word,
       clear_bgp_ipv6_safi_peer_group_word_cmd,
       "clear bgp ipv6 (unicast|multicast) peer-group WORD",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "peer_group", .value = argv[1] },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_peer_group_word_in,
       clear_bgp_ipv6_safi_peer_group_word_in_cmd,
       "clear bgp ipv6 (unicast|multicast) peer-group WORD in",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "peer_group", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_peer_group_word_in_prefix_filter,
       clear_bgp_ipv6_safi_peer_group_word_in_prefix_filter_cmd,
       "clear bgp ipv6 (unicast|multicast) peer-group WORD in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "peer_group", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_peer_group_word_out,
       clear_bgp_ipv6_safi_peer_group_word_out_cmd,
       "clear bgp ipv6 (unicast|multicast) peer-group WORD out",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "peer_group", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_peer_group_word_soft,
       clear_bgp_ipv6_safi_peer_group_word_soft_cmd,
       "clear bgp ipv6 (unicast|multicast) peer-group WORD soft",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "peer_group", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_peer_group_word_soft_in,
       clear_bgp_ipv6_safi_peer_group_word_soft_in_cmd,
       "clear bgp ipv6 (unicast|multicast) peer-group WORD soft in",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "peer_group", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_peer_group_word_soft_in_prefix_filter,
       clear_bgp_ipv6_safi_peer_group_word_soft_in_prefix_filter_cmd,
       "clear bgp ipv6 (unicast|multicast) peer-group WORD soft in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "peer_group", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_peer_group_word_soft_out,
       clear_bgp_ipv6_safi_peer_group_word_soft_out_cmd,
       "clear bgp ipv6 (unicast|multicast) peer-group WORD soft out",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "peer_group", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_ipv6_safi_peer_group_word_rsclient,
       clear_bgp_ipv6_safi_peer_group_word_rsclient_cmd,
       "clear bgp ipv6 (unicast|multicast) peer-group WORD rsclient",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[0] },
      &(struct vty_arg) { .name = "peer_group", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_all,
       clear_bgp_vpnv4_unicast_all_cmd,
       "clear bgp vpnv4 unicast *",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all peers\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_all_in,
       clear_bgp_vpnv4_unicast_all_in_cmd,
       "clear bgp vpnv4 unicast * in",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_all_in_prefix_filter,
       clear_bgp_vpnv4_unicast_all_in_prefix_filter_cmd,
       "clear bgp vpnv4 unicast * in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_all_out,
       clear_bgp_vpnv4_unicast_all_out_cmd,
       "clear bgp vpnv4 unicast * out",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_all_soft,
       clear_bgp_vpnv4_unicast_all_soft_cmd,
       "clear bgp vpnv4 unicast * soft",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_all_soft_in,
       clear_bgp_vpnv4_unicast_all_soft_in_cmd,
       "clear bgp vpnv4 unicast * soft in",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_all_soft_in_prefix_filter,
       clear_bgp_vpnv4_unicast_all_soft_in_prefix_filter_cmd,
       "clear bgp vpnv4 unicast * soft in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_all_soft_out,
       clear_bgp_vpnv4_unicast_all_soft_out_cmd,
       "clear bgp vpnv4 unicast * soft out",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_all_rsclient,
       clear_bgp_vpnv4_unicast_all_rsclient_cmd,
       "clear bgp vpnv4 unicast * rsclient",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_asn,
       clear_bgp_vpnv4_unicast_asn_cmd,
       "clear bgp vpnv4 unicast <1-4294967295>",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "asn", .value = argv[0] },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_asn_in,
       clear_bgp_vpnv4_unicast_asn_in_cmd,
       "clear bgp vpnv4 unicast <1-4294967295> in",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "asn", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_asn_in_prefix_filter,
       clear_bgp_vpnv4_unicast_asn_in_prefix_filter_cmd,
       "clear bgp vpnv4 unicast <1-4294967295> in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "asn", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_asn_out,
       clear_bgp_vpnv4_unicast_asn_out_cmd,
       "clear bgp vpnv4 unicast <1-4294967295> out",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "asn", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_asn_soft,
       clear_bgp_vpnv4_unicast_asn_soft_cmd,
       "clear bgp vpnv4 unicast <1-4294967295> soft",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "asn", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_asn_soft_in,
       clear_bgp_vpnv4_unicast_asn_soft_in_cmd,
       "clear bgp vpnv4 unicast <1-4294967295> soft in",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "asn", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_asn_soft_in_prefix_filter,
       clear_bgp_vpnv4_unicast_asn_soft_in_prefix_filter_cmd,
       "clear bgp vpnv4 unicast <1-4294967295> soft in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "asn", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_asn_soft_out,
       clear_bgp_vpnv4_unicast_asn_soft_out_cmd,
       "clear bgp vpnv4 unicast <1-4294967295> soft out",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "asn", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_asn_rsclient,
       clear_bgp_vpnv4_unicast_asn_rsclient_cmd,
       "clear bgp vpnv4 unicast <1-4294967295> rsclient",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "asn", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_ipv4,
       clear_bgp_vpnv4_unicast_ipv4_cmd,
       "clear bgp vpnv4 unicast A.B.C.D",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_ipv4_in,
       clear_bgp_vpnv4_unicast_ipv4_in_cmd,
       "clear bgp vpnv4 unicast A.B.C.D in",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_ipv4_in_prefix_filter,
       clear_bgp_vpnv4_unicast_ipv4_in_prefix_filter_cmd,
       "clear bgp vpnv4 unicast A.B.C.D in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_ipv4_out,
       clear_bgp_vpnv4_unicast_ipv4_out_cmd,
       "clear bgp vpnv4 unicast A.B.C.D out",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_ipv4_soft,
       clear_bgp_vpnv4_unicast_ipv4_soft_cmd,
       "clear bgp vpnv4 unicast A.B.C.D soft",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_ipv4_soft_in,
       clear_bgp_vpnv4_unicast_ipv4_soft_in_cmd,
       "clear bgp vpnv4 unicast A.B.C.D soft in",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_ipv4_soft_in_prefix_filter,
       clear_bgp_vpnv4_unicast_ipv4_soft_in_prefix_filter_cmd,
       "clear bgp vpnv4 unicast A.B.C.D soft in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_ipv4_soft_out,
       clear_bgp_vpnv4_unicast_ipv4_soft_out_cmd,
       "clear bgp vpnv4 unicast A.B.C.D soft out",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_ipv4_rsclient,
       clear_bgp_vpnv4_unicast_ipv4_rsclient_cmd,
       "clear bgp vpnv4 unicast A.B.C.D rsclient",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_ipv6,
       clear_bgp_vpnv4_unicast_ipv6_cmd,
       "clear bgp vpnv4 unicast X:X::X:X",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_ipv6_in,
       clear_bgp_vpnv4_unicast_ipv6_in_cmd,
       "clear bgp vpnv4 unicast X:X::X:X in",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_ipv6_in_prefix_filter,
       clear_bgp_vpnv4_unicast_ipv6_in_prefix_filter_cmd,
       "clear bgp vpnv4 unicast X:X::X:X in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_ipv6_out,
       clear_bgp_vpnv4_unicast_ipv6_out_cmd,
       "clear bgp vpnv4 unicast X:X::X:X out",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_ipv6_soft,
       clear_bgp_vpnv4_unicast_ipv6_soft_cmd,
       "clear bgp vpnv4 unicast X:X::X:X soft",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_ipv6_soft_in,
       clear_bgp_vpnv4_unicast_ipv6_soft_in_cmd,
       "clear bgp vpnv4 unicast X:X::X:X soft in",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_ipv6_soft_in_prefix_filter,
       clear_bgp_vpnv4_unicast_ipv6_soft_in_prefix_filter_cmd,
       "clear bgp vpnv4 unicast X:X::X:X soft in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_ipv6_soft_out,
       clear_bgp_vpnv4_unicast_ipv6_soft_out_cmd,
       "clear bgp vpnv4 unicast X:X::X:X soft out",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_ipv6_rsclient,
       clear_bgp_vpnv4_unicast_ipv6_rsclient_cmd,
       "clear bgp vpnv4 unicast X:X::X:X rsclient",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_external,
       clear_bgp_vpnv4_unicast_external_cmd,
       "clear bgp vpnv4 unicast external",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all external peers\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_external_in,
       clear_bgp_vpnv4_unicast_external_in_cmd,
       "clear bgp vpnv4 unicast external in",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_external_in_prefix_filter,
       clear_bgp_vpnv4_unicast_external_in_prefix_filter_cmd,
       "clear bgp vpnv4 unicast external in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_external_out,
       clear_bgp_vpnv4_unicast_external_out_cmd,
       "clear bgp vpnv4 unicast external out",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_external_soft,
       clear_bgp_vpnv4_unicast_external_soft_cmd,
       "clear bgp vpnv4 unicast external soft",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_external_soft_in,
       clear_bgp_vpnv4_unicast_external_soft_in_cmd,
       "clear bgp vpnv4 unicast external soft in",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_external_soft_in_prefix_filter,
       clear_bgp_vpnv4_unicast_external_soft_in_prefix_filter_cmd,
       "clear bgp vpnv4 unicast external soft in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_external_soft_out,
       clear_bgp_vpnv4_unicast_external_soft_out_cmd,
       "clear bgp vpnv4 unicast external soft out",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_external_rsclient,
       clear_bgp_vpnv4_unicast_external_rsclient_cmd,
       "clear bgp vpnv4 unicast external rsclient",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_peer_group_word,
       clear_bgp_vpnv4_unicast_peer_group_word_cmd,
       "clear bgp vpnv4 unicast peer-group WORD",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "peer_group", .value = argv[0] },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_peer_group_word_in,
       clear_bgp_vpnv4_unicast_peer_group_word_in_cmd,
       "clear bgp vpnv4 unicast peer-group WORD in",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "peer_group", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_peer_group_word_in_prefix_filter,
       clear_bgp_vpnv4_unicast_peer_group_word_in_prefix_filter_cmd,
       "clear bgp vpnv4 unicast peer-group WORD in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "peer_group", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_peer_group_word_out,
       clear_bgp_vpnv4_unicast_peer_group_word_out_cmd,
       "clear bgp vpnv4 unicast peer-group WORD out",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "peer_group", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_peer_group_word_soft,
       clear_bgp_vpnv4_unicast_peer_group_word_soft_cmd,
       "clear bgp vpnv4 unicast peer-group WORD soft",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "peer_group", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_peer_group_word_soft_in,
       clear_bgp_vpnv4_unicast_peer_group_word_soft_in_cmd,
       "clear bgp vpnv4 unicast peer-group WORD soft in",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "peer_group", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_peer_group_word_soft_in_prefix_filter,
       clear_bgp_vpnv4_unicast_peer_group_word_soft_in_prefix_filter_cmd,
       "clear bgp vpnv4 unicast peer-group WORD soft in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "peer_group", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_peer_group_word_soft_out,
       clear_bgp_vpnv4_unicast_peer_group_word_soft_out_cmd,
       "clear bgp vpnv4 unicast peer-group WORD soft out",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "peer_group", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_vpnv4_unicast_peer_group_word_rsclient,
       clear_bgp_vpnv4_unicast_peer_group_word_rsclient_cmd,
       "clear bgp vpnv4 unicast peer-group WORD rsclient",
       "Reset functions\n"
       "BGP information\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "peer_group", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_all,
       clear_bgp_view_word_ipv4_safi_all_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) *",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all peers\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_all_in,
       clear_bgp_view_word_ipv4_safi_all_in_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) * in",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_all_in_prefix_filter,
       clear_bgp_view_word_ipv4_safi_all_in_prefix_filter_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) * in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_all_out,
       clear_bgp_view_word_ipv4_safi_all_out_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) * out",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_all_soft,
       clear_bgp_view_word_ipv4_safi_all_soft_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) * soft",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_all_soft_in,
       clear_bgp_view_word_ipv4_safi_all_soft_in_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) * soft in",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_all_soft_in_prefix_filter,
       clear_bgp_view_word_ipv4_safi_all_soft_in_prefix_filter_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) * soft in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_all_soft_out,
       clear_bgp_view_word_ipv4_safi_all_soft_out_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) * soft out",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_all_rsclient,
       clear_bgp_view_word_ipv4_safi_all_rsclient_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) * rsclient",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_asn,
       clear_bgp_view_word_ipv4_safi_asn_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) <1-4294967295>",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "asn", .value = argv[2] },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_asn_in,
       clear_bgp_view_word_ipv4_safi_asn_in_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) <1-4294967295> in",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "asn", .value = argv[2] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_asn_in_prefix_filter,
       clear_bgp_view_word_ipv4_safi_asn_in_prefix_filter_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) <1-4294967295> in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "asn", .value = argv[2] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_asn_out,
       clear_bgp_view_word_ipv4_safi_asn_out_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) <1-4294967295> out",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "asn", .value = argv[2] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_asn_soft,
       clear_bgp_view_word_ipv4_safi_asn_soft_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) <1-4294967295> soft",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "asn", .value = argv[2] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_asn_soft_in,
       clear_bgp_view_word_ipv4_safi_asn_soft_in_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) <1-4294967295> soft in",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "asn", .value = argv[2] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_asn_soft_in_prefix_filter,
       clear_bgp_view_word_ipv4_safi_asn_soft_in_prefix_filter_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) <1-4294967295> soft in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "asn", .value = argv[2] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_asn_soft_out,
       clear_bgp_view_word_ipv4_safi_asn_soft_out_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) <1-4294967295> soft out",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "asn", .value = argv[2] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_asn_rsclient,
       clear_bgp_view_word_ipv4_safi_asn_rsclient_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) <1-4294967295> rsclient",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "asn", .value = argv[2] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_ipv4,
       clear_bgp_view_word_ipv4_safi_ipv4_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) A.B.C.D",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_ipv4_in,
       clear_bgp_view_word_ipv4_safi_ipv4_in_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) A.B.C.D in",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_ipv4_in_prefix_filter,
       clear_bgp_view_word_ipv4_safi_ipv4_in_prefix_filter_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) A.B.C.D in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_ipv4_out,
       clear_bgp_view_word_ipv4_safi_ipv4_out_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) A.B.C.D out",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_ipv4_soft,
       clear_bgp_view_word_ipv4_safi_ipv4_soft_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) A.B.C.D soft",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_ipv4_soft_in,
       clear_bgp_view_word_ipv4_safi_ipv4_soft_in_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) A.B.C.D soft in",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_ipv4_soft_in_prefix_filter,
       clear_bgp_view_word_ipv4_safi_ipv4_soft_in_prefix_filter_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) A.B.C.D soft in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_ipv4_soft_out,
       clear_bgp_view_word_ipv4_safi_ipv4_soft_out_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) A.B.C.D soft out",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_ipv4_rsclient,
       clear_bgp_view_word_ipv4_safi_ipv4_rsclient_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) A.B.C.D rsclient",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_ipv6,
       clear_bgp_view_word_ipv4_safi_ipv6_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) X:X::X:X",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_ipv6_in,
       clear_bgp_view_word_ipv4_safi_ipv6_in_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) X:X::X:X in",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_ipv6_in_prefix_filter,
       clear_bgp_view_word_ipv4_safi_ipv6_in_prefix_filter_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) X:X::X:X in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_ipv6_out,
       clear_bgp_view_word_ipv4_safi_ipv6_out_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) X:X::X:X out",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_ipv6_soft,
       clear_bgp_view_word_ipv4_safi_ipv6_soft_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) X:X::X:X soft",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_ipv6_soft_in,
       clear_bgp_view_word_ipv4_safi_ipv6_soft_in_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) X:X::X:X soft in",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_ipv6_soft_in_prefix_filter,
       clear_bgp_view_word_ipv4_safi_ipv6_soft_in_prefix_filter_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) X:X::X:X soft in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_ipv6_soft_out,
       clear_bgp_view_word_ipv4_safi_ipv6_soft_out_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) X:X::X:X soft out",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_ipv6_rsclient,
       clear_bgp_view_word_ipv4_safi_ipv6_rsclient_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) X:X::X:X rsclient",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_external,
       clear_bgp_view_word_ipv4_safi_external_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) external",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all external peers\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_external_in,
       clear_bgp_view_word_ipv4_safi_external_in_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) external in",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_external_in_prefix_filter,
       clear_bgp_view_word_ipv4_safi_external_in_prefix_filter_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) external in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_external_out,
       clear_bgp_view_word_ipv4_safi_external_out_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) external out",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_external_soft,
       clear_bgp_view_word_ipv4_safi_external_soft_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) external soft",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_external_soft_in,
       clear_bgp_view_word_ipv4_safi_external_soft_in_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) external soft in",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_external_soft_in_prefix_filter,
       clear_bgp_view_word_ipv4_safi_external_soft_in_prefix_filter_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) external soft in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_external_soft_out,
       clear_bgp_view_word_ipv4_safi_external_soft_out_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) external soft out",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_external_rsclient,
       clear_bgp_view_word_ipv4_safi_external_rsclient_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) external rsclient",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_peer_group_word,
       clear_bgp_view_word_ipv4_safi_peer_group_word_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) peer-group WORD",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "peer_group", .value = argv[2] },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_peer_group_word_in,
       clear_bgp_view_word_ipv4_safi_peer_group_word_in_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) peer-group WORD in",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "peer_group", .value = argv[2] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_peer_group_word_in_prefix_filter,
       clear_bgp_view_word_ipv4_safi_peer_group_word_in_prefix_filter_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) peer-group WORD in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "peer_group", .value = argv[2] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_peer_group_word_out,
       clear_bgp_view_word_ipv4_safi_peer_group_word_out_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) peer-group WORD out",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "peer_group", .value = argv[2] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_peer_group_word_soft,
       clear_bgp_view_word_ipv4_safi_peer_group_word_soft_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) peer-group WORD soft",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "peer_group", .value = argv[2] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_peer_group_word_soft_in,
       clear_bgp_view_word_ipv4_safi_peer_group_word_soft_in_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) peer-group WORD soft in",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "peer_group", .value = argv[2] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_peer_group_word_soft_in_prefix_filter,
       clear_bgp_view_word_ipv4_safi_peer_group_word_soft_in_prefix_filter_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) peer-group WORD soft in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "peer_group", .value = argv[2] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_peer_group_word_soft_out,
       clear_bgp_view_word_ipv4_safi_peer_group_word_soft_out_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) peer-group WORD soft out",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "peer_group", .value = argv[2] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_peer_group_word_rsclient,
       clear_bgp_view_word_ipv4_safi_peer_group_word_rsclient_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) peer-group WORD rsclient",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "peer_group", .value = argv[2] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_dampening,
       clear_bgp_view_word_ipv4_safi_dampening_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) dampening",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear route flap dampening information\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_dampening_ipv4,
       clear_bgp_view_word_ipv4_safi_dampening_ipv4_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) dampening A.B.C.D",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear route flap dampening information\n"
       "Network to clear damping information\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "network", .value = argv[2] },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_dampening_ipv4_in,
       clear_bgp_view_word_ipv4_safi_dampening_ipv4_in_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) dampening A.B.C.D in",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear route flap dampening information\n"
       "Network to clear damping information\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "network", .value = argv[2] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_dampening_ipv4_in_prefix_filter,
       clear_bgp_view_word_ipv4_safi_dampening_ipv4_in_prefix_filter_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) dampening A.B.C.D in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear route flap dampening information\n"
       "Network to clear damping information\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "network", .value = argv[2] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_dampening_ipv4_out,
       clear_bgp_view_word_ipv4_safi_dampening_ipv4_out_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) dampening A.B.C.D out",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear route flap dampening information\n"
       "Network to clear damping information\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "network", .value = argv[2] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_dampening_ipv4_soft,
       clear_bgp_view_word_ipv4_safi_dampening_ipv4_soft_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) dampening A.B.C.D soft",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear route flap dampening information\n"
       "Network to clear damping information\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "network", .value = argv[2] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_dampening_ipv4_soft_in,
       clear_bgp_view_word_ipv4_safi_dampening_ipv4_soft_in_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) dampening A.B.C.D soft in",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear route flap dampening information\n"
       "Network to clear damping information\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "network", .value = argv[2] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_dampening_ipv4_soft_in_prefix_filter,
       clear_bgp_view_word_ipv4_safi_dampening_ipv4_soft_in_prefix_filter_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) dampening A.B.C.D soft in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear route flap dampening information\n"
       "Network to clear damping information\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "network", .value = argv[2] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_dampening_ipv4_soft_out,
       clear_bgp_view_word_ipv4_safi_dampening_ipv4_soft_out_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) dampening A.B.C.D soft out",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear route flap dampening information\n"
       "Network to clear damping information\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "network", .value = argv[2] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_dampening_ipv4_rsclient,
       clear_bgp_view_word_ipv4_safi_dampening_ipv4_rsclient_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) dampening A.B.C.D rsclient",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear route flap dampening information\n"
       "Network to clear damping information\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "network", .value = argv[2] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_dampening_ipv4m,
       clear_bgp_view_word_ipv4_safi_dampening_ipv4m_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) dampening A.B.C.D/M",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear route flap dampening information\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "prefix", .value = argv[2] },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_dampening_ipv4m_in,
       clear_bgp_view_word_ipv4_safi_dampening_ipv4m_in_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) dampening A.B.C.D/M in",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear route flap dampening information\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "prefix", .value = argv[2] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_dampening_ipv4m_in_prefix_filter,
       clear_bgp_view_word_ipv4_safi_dampening_ipv4m_in_prefix_filter_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) dampening A.B.C.D/M in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear route flap dampening information\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "prefix", .value = argv[2] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_dampening_ipv4m_out,
       clear_bgp_view_word_ipv4_safi_dampening_ipv4m_out_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) dampening A.B.C.D/M out",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear route flap dampening information\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "prefix", .value = argv[2] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_dampening_ipv4m_soft,
       clear_bgp_view_word_ipv4_safi_dampening_ipv4m_soft_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) dampening A.B.C.D/M soft",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear route flap dampening information\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "prefix", .value = argv[2] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_dampening_ipv4m_soft_in,
       clear_bgp_view_word_ipv4_safi_dampening_ipv4m_soft_in_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) dampening A.B.C.D/M soft in",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear route flap dampening information\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "prefix", .value = argv[2] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_dampening_ipv4m_soft_in_prefix_filter,
       clear_bgp_view_word_ipv4_safi_dampening_ipv4m_soft_in_prefix_filter_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) dampening A.B.C.D/M soft in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear route flap dampening information\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "prefix", .value = argv[2] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_dampening_ipv4m_soft_out,
       clear_bgp_view_word_ipv4_safi_dampening_ipv4m_soft_out_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) dampening A.B.C.D/M soft out",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear route flap dampening information\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "prefix", .value = argv[2] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_bgp_view_word_ipv4_safi_dampening_ipv4m_rsclient,
       clear_bgp_view_word_ipv4_safi_dampening_ipv4m_rsclient_cmd,
       "clear bgp view WORD ipv4 (unicast|multicast) dampening A.B.C.D/M rsclient",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear route flap dampening information\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv4" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "prefix", .value = argv[2] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_all,
       clear_bgp_view_word_ipv6_safi_all_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) *",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all peers\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_all_in,
       clear_bgp_view_word_ipv6_safi_all_in_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) * in",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_all_in_prefix_filter,
       clear_bgp_view_word_ipv6_safi_all_in_prefix_filter_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) * in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_all_out,
       clear_bgp_view_word_ipv6_safi_all_out_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) * out",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_all_soft,
       clear_bgp_view_word_ipv6_safi_all_soft_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) * soft",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_all_soft_in,
       clear_bgp_view_word_ipv6_safi_all_soft_in_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) * soft in",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_all_soft_in_prefix_filter,
       clear_bgp_view_word_ipv6_safi_all_soft_in_prefix_filter_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) * soft in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_all_soft_out,
       clear_bgp_view_word_ipv6_safi_all_soft_out_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) * soft out",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_all_rsclient,
       clear_bgp_view_word_ipv6_safi_all_rsclient_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) * rsclient",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_asn,
       clear_bgp_view_word_ipv6_safi_asn_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) <1-4294967295>",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "asn", .value = argv[2] },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_asn_in,
       clear_bgp_view_word_ipv6_safi_asn_in_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) <1-4294967295> in",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "asn", .value = argv[2] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_asn_in_prefix_filter,
       clear_bgp_view_word_ipv6_safi_asn_in_prefix_filter_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) <1-4294967295> in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "asn", .value = argv[2] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_asn_out,
       clear_bgp_view_word_ipv6_safi_asn_out_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) <1-4294967295> out",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "asn", .value = argv[2] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_asn_soft,
       clear_bgp_view_word_ipv6_safi_asn_soft_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) <1-4294967295> soft",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "asn", .value = argv[2] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_asn_soft_in,
       clear_bgp_view_word_ipv6_safi_asn_soft_in_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) <1-4294967295> soft in",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "asn", .value = argv[2] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_asn_soft_in_prefix_filter,
       clear_bgp_view_word_ipv6_safi_asn_soft_in_prefix_filter_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) <1-4294967295> soft in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "asn", .value = argv[2] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_asn_soft_out,
       clear_bgp_view_word_ipv6_safi_asn_soft_out_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) <1-4294967295> soft out",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "asn", .value = argv[2] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_asn_rsclient,
       clear_bgp_view_word_ipv6_safi_asn_rsclient_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) <1-4294967295> rsclient",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "asn", .value = argv[2] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_ipv4,
       clear_bgp_view_word_ipv6_safi_ipv4_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) A.B.C.D",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_ipv4_in,
       clear_bgp_view_word_ipv6_safi_ipv4_in_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) A.B.C.D in",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_ipv4_in_prefix_filter,
       clear_bgp_view_word_ipv6_safi_ipv4_in_prefix_filter_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) A.B.C.D in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_ipv4_out,
       clear_bgp_view_word_ipv6_safi_ipv4_out_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) A.B.C.D out",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_ipv4_soft,
       clear_bgp_view_word_ipv6_safi_ipv4_soft_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) A.B.C.D soft",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_ipv4_soft_in,
       clear_bgp_view_word_ipv6_safi_ipv4_soft_in_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) A.B.C.D soft in",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_ipv4_soft_in_prefix_filter,
       clear_bgp_view_word_ipv6_safi_ipv4_soft_in_prefix_filter_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) A.B.C.D soft in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_ipv4_soft_out,
       clear_bgp_view_word_ipv6_safi_ipv4_soft_out_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) A.B.C.D soft out",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_ipv4_rsclient,
       clear_bgp_view_word_ipv6_safi_ipv4_rsclient_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) A.B.C.D rsclient",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_ipv6,
       clear_bgp_view_word_ipv6_safi_ipv6_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) X:X::X:X",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_ipv6_in,
       clear_bgp_view_word_ipv6_safi_ipv6_in_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) X:X::X:X in",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_ipv6_in_prefix_filter,
       clear_bgp_view_word_ipv6_safi_ipv6_in_prefix_filter_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) X:X::X:X in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_ipv6_out,
       clear_bgp_view_word_ipv6_safi_ipv6_out_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) X:X::X:X out",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_ipv6_soft,
       clear_bgp_view_word_ipv6_safi_ipv6_soft_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) X:X::X:X soft",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_ipv6_soft_in,
       clear_bgp_view_word_ipv6_safi_ipv6_soft_in_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) X:X::X:X soft in",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_ipv6_soft_in_prefix_filter,
       clear_bgp_view_word_ipv6_safi_ipv6_soft_in_prefix_filter_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) X:X::X:X soft in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_ipv6_soft_out,
       clear_bgp_view_word_ipv6_safi_ipv6_soft_out_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) X:X::X:X soft out",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_ipv6_rsclient,
       clear_bgp_view_word_ipv6_safi_ipv6_rsclient_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) X:X::X:X rsclient",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "address", .value = argv[2] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_external,
       clear_bgp_view_word_ipv6_safi_external_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) external",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all external peers\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_external_in,
       clear_bgp_view_word_ipv6_safi_external_in_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) external in",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_external_in_prefix_filter,
       clear_bgp_view_word_ipv6_safi_external_in_prefix_filter_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) external in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_external_out,
       clear_bgp_view_word_ipv6_safi_external_out_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) external out",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_external_soft,
       clear_bgp_view_word_ipv6_safi_external_soft_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) external soft",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_external_soft_in,
       clear_bgp_view_word_ipv6_safi_external_soft_in_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) external soft in",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_external_soft_in_prefix_filter,
       clear_bgp_view_word_ipv6_safi_external_soft_in_prefix_filter_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) external soft in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_external_soft_out,
       clear_bgp_view_word_ipv6_safi_external_soft_out_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) external soft out",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_external_rsclient,
       clear_bgp_view_word_ipv6_safi_external_rsclient_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) external rsclient",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_peer_group_word,
       clear_bgp_view_word_ipv6_safi_peer_group_word_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) peer-group WORD",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "peer_group", .value = argv[2] },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_peer_group_word_in,
       clear_bgp_view_word_ipv6_safi_peer_group_word_in_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) peer-group WORD in",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "peer_group", .value = argv[2] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_peer_group_word_in_prefix_filter,
       clear_bgp_view_word_ipv6_safi_peer_group_word_in_prefix_filter_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) peer-group WORD in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "peer_group", .value = argv[2] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_peer_group_word_out,
       clear_bgp_view_word_ipv6_safi_peer_group_word_out_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) peer-group WORD out",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "peer_group", .value = argv[2] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_peer_group_word_soft,
       clear_bgp_view_word_ipv6_safi_peer_group_word_soft_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) peer-group WORD soft",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "peer_group", .value = argv[2] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_peer_group_word_soft_in,
       clear_bgp_view_word_ipv6_safi_peer_group_word_soft_in_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) peer-group WORD soft in",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "peer_group", .value = argv[2] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_peer_group_word_soft_in_prefix_filter,
       clear_bgp_view_word_ipv6_safi_peer_group_word_soft_in_prefix_filter_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) peer-group WORD soft in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "peer_group", .value = argv[2] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_peer_group_word_soft_out,
       clear_bgp_view_word_ipv6_safi_peer_group_word_soft_out_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) peer-group WORD soft out",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "peer_group", .value = argv[2] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_view_word_ipv6_safi_peer_group_word_rsclient,
       clear_bgp_view_word_ipv6_safi_peer_group_word_rsclient_cmd,
       "clear bgp view WORD ipv6 (unicast|multicast) peer-group WORD rsclient",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "ipv6" },
      &(struct vty_arg) { .name = "safi", .value = argv[1] },
      &(struct vty_arg) { .name = "peer_group", .value = argv[2] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_all,
       clear_bgp_view_word_vpnv4_unicast_all_cmd,
       "clear bgp view WORD vpnv4 unicast *",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all peers\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_all_in,
       clear_bgp_view_word_vpnv4_unicast_all_in_cmd,
       "clear bgp view WORD vpnv4 unicast * in",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_all_in_prefix_filter,
       clear_bgp_view_word_vpnv4_unicast_all_in_prefix_filter_cmd,
       "clear bgp view WORD vpnv4 unicast * in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_all_out,
       clear_bgp_view_word_vpnv4_unicast_all_out_cmd,
       "clear bgp view WORD vpnv4 unicast * out",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_all_soft,
       clear_bgp_view_word_vpnv4_unicast_all_soft_cmd,
       "clear bgp view WORD vpnv4 unicast * soft",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_all_soft_in,
       clear_bgp_view_word_vpnv4_unicast_all_soft_in_cmd,
       "clear bgp view WORD vpnv4 unicast * soft in",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_all_soft_in_prefix_filter,
       clear_bgp_view_word_vpnv4_unicast_all_soft_in_prefix_filter_cmd,
       "clear bgp view WORD vpnv4 unicast * soft in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_all_soft_out,
       clear_bgp_view_word_vpnv4_unicast_all_soft_out_cmd,
       "clear bgp view WORD vpnv4 unicast * soft out",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_all_rsclient,
       clear_bgp_view_word_vpnv4_unicast_all_rsclient_cmd,
       "clear bgp view WORD vpnv4 unicast * rsclient",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all peers\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_asn,
       clear_bgp_view_word_vpnv4_unicast_asn_cmd,
       "clear bgp view WORD vpnv4 unicast <1-4294967295>",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "asn", .value = argv[1] },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_asn_in,
       clear_bgp_view_word_vpnv4_unicast_asn_in_cmd,
       "clear bgp view WORD vpnv4 unicast <1-4294967295> in",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "asn", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_asn_in_prefix_filter,
       clear_bgp_view_word_vpnv4_unicast_asn_in_prefix_filter_cmd,
       "clear bgp view WORD vpnv4 unicast <1-4294967295> in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "asn", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_asn_out,
       clear_bgp_view_word_vpnv4_unicast_asn_out_cmd,
       "clear bgp view WORD vpnv4 unicast <1-4294967295> out",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "asn", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_asn_soft,
       clear_bgp_view_word_vpnv4_unicast_asn_soft_cmd,
       "clear bgp view WORD vpnv4 unicast <1-4294967295> soft",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "asn", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_asn_soft_in,
       clear_bgp_view_word_vpnv4_unicast_asn_soft_in_cmd,
       "clear bgp view WORD vpnv4 unicast <1-4294967295> soft in",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "asn", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_asn_soft_in_prefix_filter,
       clear_bgp_view_word_vpnv4_unicast_asn_soft_in_prefix_filter_cmd,
       "clear bgp view WORD vpnv4 unicast <1-4294967295> soft in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "asn", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_asn_soft_out,
       clear_bgp_view_word_vpnv4_unicast_asn_soft_out_cmd,
       "clear bgp view WORD vpnv4 unicast <1-4294967295> soft out",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "asn", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_asn_rsclient,
       clear_bgp_view_word_vpnv4_unicast_asn_rsclient_cmd,
       "clear bgp view WORD vpnv4 unicast <1-4294967295> rsclient",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear peers with the AS number\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "asn", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_ipv4,
       clear_bgp_view_word_vpnv4_unicast_ipv4_cmd,
       "clear bgp view WORD vpnv4 unicast A.B.C.D",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_ipv4_in,
       clear_bgp_view_word_vpnv4_unicast_ipv4_in_cmd,
       "clear bgp view WORD vpnv4 unicast A.B.C.D in",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_ipv4_in_prefix_filter,
       clear_bgp_view_word_vpnv4_unicast_ipv4_in_prefix_filter_cmd,
       "clear bgp view WORD vpnv4 unicast A.B.C.D in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_ipv4_out,
       clear_bgp_view_word_vpnv4_unicast_ipv4_out_cmd,
       "clear bgp view WORD vpnv4 unicast A.B.C.D out",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_ipv4_soft,
       clear_bgp_view_word_vpnv4_unicast_ipv4_soft_cmd,
       "clear bgp view WORD vpnv4 unicast A.B.C.D soft",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_ipv4_soft_in,
       clear_bgp_view_word_vpnv4_unicast_ipv4_soft_in_cmd,
       "clear bgp view WORD vpnv4 unicast A.B.C.D soft in",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_ipv4_soft_in_prefix_filter,
       clear_bgp_view_word_vpnv4_unicast_ipv4_soft_in_prefix_filter_cmd,
       "clear bgp view WORD vpnv4 unicast A.B.C.D soft in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_ipv4_soft_out,
       clear_bgp_view_word_vpnv4_unicast_ipv4_soft_out_cmd,
       "clear bgp view WORD vpnv4 unicast A.B.C.D soft out",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_ipv4_rsclient,
       clear_bgp_view_word_vpnv4_unicast_ipv4_rsclient_cmd,
       "clear bgp view WORD vpnv4 unicast A.B.C.D rsclient",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_ipv6,
       clear_bgp_view_word_vpnv4_unicast_ipv6_cmd,
       "clear bgp view WORD vpnv4 unicast X:X::X:X",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_ipv6_in,
       clear_bgp_view_word_vpnv4_unicast_ipv6_in_cmd,
       "clear bgp view WORD vpnv4 unicast X:X::X:X in",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_ipv6_in_prefix_filter,
       clear_bgp_view_word_vpnv4_unicast_ipv6_in_prefix_filter_cmd,
       "clear bgp view WORD vpnv4 unicast X:X::X:X in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_ipv6_out,
       clear_bgp_view_word_vpnv4_unicast_ipv6_out_cmd,
       "clear bgp view WORD vpnv4 unicast X:X::X:X out",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_ipv6_soft,
       clear_bgp_view_word_vpnv4_unicast_ipv6_soft_cmd,
       "clear bgp view WORD vpnv4 unicast X:X::X:X soft",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_ipv6_soft_in,
       clear_bgp_view_word_vpnv4_unicast_ipv6_soft_in_cmd,
       "clear bgp view WORD vpnv4 unicast X:X::X:X soft in",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_ipv6_soft_in_prefix_filter,
       clear_bgp_view_word_vpnv4_unicast_ipv6_soft_in_prefix_filter_cmd,
       "clear bgp view WORD vpnv4 unicast X:X::X:X soft in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_ipv6_soft_out,
       clear_bgp_view_word_vpnv4_unicast_ipv6_soft_out_cmd,
       "clear bgp view WORD vpnv4 unicast X:X::X:X soft out",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_ipv6_rsclient,
       clear_bgp_view_word_vpnv4_unicast_ipv6_rsclient_cmd,
       "clear bgp view WORD vpnv4 unicast X:X::X:X rsclient",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "address", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_external,
       clear_bgp_view_word_vpnv4_unicast_external_cmd,
       "clear bgp view WORD vpnv4 unicast external",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all external peers\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_external_in,
       clear_bgp_view_word_vpnv4_unicast_external_in_cmd,
       "clear bgp view WORD vpnv4 unicast external in",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_external_in_prefix_filter,
       clear_bgp_view_word_vpnv4_unicast_external_in_prefix_filter_cmd,
       "clear bgp view WORD vpnv4 unicast external in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_external_out,
       clear_bgp_view_word_vpnv4_unicast_external_out_cmd,
       "clear bgp view WORD vpnv4 unicast external out",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_external_soft,
       clear_bgp_view_word_vpnv4_unicast_external_soft_cmd,
       "clear bgp view WORD vpnv4 unicast external soft",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_external_soft_in,
       clear_bgp_view_word_vpnv4_unicast_external_soft_in_cmd,
       "clear bgp view WORD vpnv4 unicast external soft in",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_external_soft_in_prefix_filter,
       clear_bgp_view_word_vpnv4_unicast_external_soft_in_prefix_filter_cmd,
       "clear bgp view WORD vpnv4 unicast external soft in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_external_soft_out,
       clear_bgp_view_word_vpnv4_unicast_external_soft_out_cmd,
       "clear bgp view WORD vpnv4 unicast external soft out",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_external_rsclient,
       clear_bgp_view_word_vpnv4_unicast_external_rsclient_cmd,
       "clear bgp view WORD vpnv4 unicast external rsclient",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all external peers\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_peer_group_word,
       clear_bgp_view_word_vpnv4_unicast_peer_group_word_cmd,
       "clear bgp view WORD vpnv4 unicast peer-group WORD",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "peer_group", .value = argv[1] },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_peer_group_word_in,
       clear_bgp_view_word_vpnv4_unicast_peer_group_word_in_cmd,
       "clear bgp view WORD vpnv4 unicast peer-group WORD in",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "peer_group", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_peer_group_word_in_prefix_filter,
       clear_bgp_view_word_vpnv4_unicast_peer_group_word_in_prefix_filter_cmd,
       "clear bgp view WORD vpnv4 unicast peer-group WORD in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "peer_group", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_peer_group_word_out,
       clear_bgp_view_word_vpnv4_unicast_peer_group_word_out_cmd,
       "clear bgp view WORD vpnv4 unicast peer-group WORD out",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "peer_group", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_peer_group_word_soft,
       clear_bgp_view_word_vpnv4_unicast_peer_group_word_soft_cmd,
       "clear bgp view WORD vpnv4 unicast peer-group WORD soft",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "peer_group", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_peer_group_word_soft_in,
       clear_bgp_view_word_vpnv4_unicast_peer_group_word_soft_in_cmd,
       "clear bgp view WORD vpnv4 unicast peer-group WORD soft in",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "peer_group", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_peer_group_word_soft_in_prefix_filter,
       clear_bgp_view_word_vpnv4_unicast_peer_group_word_soft_in_prefix_filter_cmd,
       "clear bgp view WORD vpnv4 unicast peer-group WORD soft in prefix-filter",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "peer_group", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_peer_group_word_soft_out,
       clear_bgp_view_word_vpnv4_unicast_peer_group_word_soft_out_cmd,
       "clear bgp view WORD vpnv4 unicast peer-group WORD soft out",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "peer_group", .value = argv[1] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_bgp_view_word_vpnv4_unicast_peer_group_word_rsclient,
       clear_bgp_view_word_vpnv4_unicast_peer_group_word_rsclient_cmd,
       "clear bgp view WORD vpnv4 unicast peer-group WORD rsclient",
       "Reset functions\n"
       "BGP information\n"
       "BGP view\n"
       "View name\n"
       "Address family\n"
       "Address Family modifier\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "view", .value = argv[0] },
      &(struct vty_arg) { .name = "afi", .value = "vpnv4" },
      &(struct vty_arg) { .name = "safi", .value = "unicast" },
      &(struct vty_arg) { .name = "peer_group", .value = argv[1] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_ip_bgp_all,
       clear_ip_bgp_all_cmd,
       "clear ip bgp *",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear all peers\n")
{
  struct vty_arg *args[] = { NULL };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_ip_bgp_all_in,
       clear_ip_bgp_all_in_cmd,
       "clear ip bgp * in",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear all peers\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_ip_bgp_all_in_prefix_filter,
       clear_ip_bgp_all_in_prefix_filter_cmd,
       "clear ip bgp * in prefix-filter",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear all peers\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_ip_bgp_all_out,
       clear_ip_bgp_all_out_cmd,
       "clear ip bgp * out",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear all peers\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_ip_bgp_all_soft,
       clear_ip_bgp_all_soft_cmd,
       "clear ip bgp * soft",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear all peers\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_ip_bgp_all_soft_in,
       clear_ip_bgp_all_soft_in_cmd,
       "clear ip bgp * soft in",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear all peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_ip_bgp_all_soft_in_prefix_filter,
       clear_ip_bgp_all_soft_in_prefix_filter_cmd,
       "clear ip bgp * soft in prefix-filter",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear all peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_ip_bgp_all_soft_out,
       clear_ip_bgp_all_soft_out_cmd,
       "clear ip bgp * soft out",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear all peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_ip_bgp_all_rsclient,
       clear_ip_bgp_all_rsclient_cmd,
       "clear ip bgp * rsclient",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear all peers\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_all (vty, args);
}

DEFUN (clear_ip_bgp_asn,
       clear_ip_bgp_asn_cmd,
       "clear ip bgp <1-4294967295>",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear peers with the AS number\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "asn", .value = argv[0] },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_ip_bgp_asn_in,
       clear_ip_bgp_asn_in_cmd,
       "clear ip bgp <1-4294967295> in",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "asn", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_ip_bgp_asn_in_prefix_filter,
       clear_ip_bgp_asn_in_prefix_filter_cmd,
       "clear ip bgp <1-4294967295> in prefix-filter",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "asn", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_ip_bgp_asn_out,
       clear_ip_bgp_asn_out_cmd,
       "clear ip bgp <1-4294967295> out",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear peers with the AS number\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "asn", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_ip_bgp_asn_soft,
       clear_ip_bgp_asn_soft_cmd,
       "clear ip bgp <1-4294967295> soft",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "asn", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_ip_bgp_asn_soft_in,
       clear_ip_bgp_asn_soft_in_cmd,
       "clear ip bgp <1-4294967295> soft in",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "asn", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_ip_bgp_asn_soft_in_prefix_filter,
       clear_ip_bgp_asn_soft_in_prefix_filter_cmd,
       "clear ip bgp <1-4294967295> soft in prefix-filter",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "asn", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_ip_bgp_asn_soft_out,
       clear_ip_bgp_asn_soft_out_cmd,
       "clear ip bgp <1-4294967295> soft out",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear peers with the AS number\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "asn", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_ip_bgp_asn_rsclient,
       clear_ip_bgp_asn_rsclient_cmd,
       "clear ip bgp <1-4294967295> rsclient",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear peers with the AS number\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "asn", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_asn (vty, args);
}

DEFUN (clear_ip_bgp_ipv4,
       clear_ip_bgp_ipv4_cmd,
       "clear ip bgp A.B.C.D",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "BGP neighbor address to clear\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_ip_bgp_ipv4_in,
       clear_ip_bgp_ipv4_in_cmd,
       "clear ip bgp A.B.C.D in",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_ip_bgp_ipv4_in_prefix_filter,
       clear_ip_bgp_ipv4_in_prefix_filter_cmd,
       "clear ip bgp A.B.C.D in prefix-filter",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_ip_bgp_ipv4_out,
       clear_ip_bgp_ipv4_out_cmd,
       "clear ip bgp A.B.C.D out",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_ip_bgp_ipv4_soft,
       clear_ip_bgp_ipv4_soft_cmd,
       "clear ip bgp A.B.C.D soft",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_ip_bgp_ipv4_soft_in,
       clear_ip_bgp_ipv4_soft_in_cmd,
       "clear ip bgp A.B.C.D soft in",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_ip_bgp_ipv4_soft_in_prefix_filter,
       clear_ip_bgp_ipv4_soft_in_prefix_filter_cmd,
       "clear ip bgp A.B.C.D soft in prefix-filter",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_ip_bgp_ipv4_soft_out,
       clear_ip_bgp_ipv4_soft_out_cmd,
       "clear ip bgp A.B.C.D soft out",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_ip_bgp_ipv4_rsclient,
       clear_ip_bgp_ipv4_rsclient_cmd,
       "clear ip bgp A.B.C.D rsclient",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_ip_bgp_ipv6,
       clear_ip_bgp_ipv6_cmd,
       "clear ip bgp X:X::X:X",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "BGP neighbor address to clear\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_ip_bgp_ipv6_in,
       clear_ip_bgp_ipv6_in_cmd,
       "clear ip bgp X:X::X:X in",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_ip_bgp_ipv6_in_prefix_filter,
       clear_ip_bgp_ipv6_in_prefix_filter_cmd,
       "clear ip bgp X:X::X:X in prefix-filter",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_ip_bgp_ipv6_out,
       clear_ip_bgp_ipv6_out_cmd,
       "clear ip bgp X:X::X:X out",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_ip_bgp_ipv6_soft,
       clear_ip_bgp_ipv6_soft_cmd,
       "clear ip bgp X:X::X:X soft",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_ip_bgp_ipv6_soft_in,
       clear_ip_bgp_ipv6_soft_in_cmd,
       "clear ip bgp X:X::X:X soft in",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_ip_bgp_ipv6_soft_in_prefix_filter,
       clear_ip_bgp_ipv6_soft_in_prefix_filter_cmd,
       "clear ip bgp X:X::X:X soft in prefix-filter",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_ip_bgp_ipv6_soft_out,
       clear_ip_bgp_ipv6_soft_out_cmd,
       "clear ip bgp X:X::X:X soft out",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_ip_bgp_ipv6_rsclient,
       clear_ip_bgp_ipv6_rsclient_cmd,
       "clear ip bgp X:X::X:X rsclient",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "BGP neighbor address to clear\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "address", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_neighbor (vty, args);
}

DEFUN (clear_ip_bgp_external,
       clear_ip_bgp_external_cmd,
       "clear ip bgp external",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear all external peers\n")
{
  struct vty_arg *args[] = { NULL };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_ip_bgp_external_in,
       clear_ip_bgp_external_in_cmd,
       "clear ip bgp external in",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear all external peers\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_ip_bgp_external_in_prefix_filter,
       clear_ip_bgp_external_in_prefix_filter_cmd,
       "clear ip bgp external in prefix-filter",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear all external peers\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_ip_bgp_external_out,
       clear_ip_bgp_external_out_cmd,
       "clear ip bgp external out",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear all external peers\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_ip_bgp_external_soft,
       clear_ip_bgp_external_soft_cmd,
       "clear ip bgp external soft",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear all external peers\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_ip_bgp_external_soft_in,
       clear_ip_bgp_external_soft_in_cmd,
       "clear ip bgp external soft in",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear all external peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_ip_bgp_external_soft_in_prefix_filter,
       clear_ip_bgp_external_soft_in_prefix_filter_cmd,
       "clear ip bgp external soft in prefix-filter",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear all external peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_ip_bgp_external_soft_out,
       clear_ip_bgp_external_soft_out_cmd,
       "clear ip bgp external soft out",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear all external peers\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_ip_bgp_external_rsclient,
       clear_ip_bgp_external_rsclient_cmd,
       "clear ip bgp external rsclient",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear all external peers\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_external (vty, args);
}

DEFUN (clear_ip_bgp_peer_group_word,
       clear_ip_bgp_peer_group_word_cmd,
       "clear ip bgp peer-group WORD",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "peer_group", .value = argv[0] },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_ip_bgp_peer_group_word_in,
       clear_ip_bgp_peer_group_word_in_cmd,
       "clear ip bgp peer-group WORD in",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "peer_group", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_ip_bgp_peer_group_word_in_prefix_filter,
       clear_ip_bgp_peer_group_word_in_prefix_filter_cmd,
       "clear ip bgp peer-group WORD in prefix-filter",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "peer_group", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_ip_bgp_peer_group_word_out,
       clear_ip_bgp_peer_group_word_out_cmd,
       "clear ip bgp peer-group WORD out",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "peer_group", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_ip_bgp_peer_group_word_soft,
       clear_ip_bgp_peer_group_word_soft_cmd,
       "clear ip bgp peer-group WORD soft",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "peer_group", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_ip_bgp_peer_group_word_soft_in,
       clear_ip_bgp_peer_group_word_soft_in_cmd,
       "clear ip bgp peer-group WORD soft in",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "peer_group", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_ip_bgp_peer_group_word_soft_in_prefix_filter,
       clear_ip_bgp_peer_group_word_soft_in_prefix_filter_cmd,
       "clear ip bgp peer-group WORD soft in prefix-filter",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "peer_group", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_ip_bgp_peer_group_word_soft_out,
       clear_ip_bgp_peer_group_word_soft_out_cmd,
       "clear ip bgp peer-group WORD soft out",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "peer_group", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_ip_bgp_peer_group_word_rsclient,
       clear_ip_bgp_peer_group_word_rsclient_cmd,
       "clear ip bgp peer-group WORD rsclient",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear all members of peer-group\n"
       "BGP peer-group name\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "peer_group", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_peer_group (vty, args);
}

DEFUN (clear_ip_bgp_dampening,
       clear_ip_bgp_dampening_cmd,
       "clear ip bgp dampening",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear route flap dampening information\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_ip_bgp_dampening_ipv4,
       clear_ip_bgp_dampening_ipv4_cmd,
       "clear ip bgp dampening A.B.C.D",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear route flap dampening information\n"
       "Network to clear damping information\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "network", .value = argv[0] },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_ip_bgp_dampening_ipv4_in,
       clear_ip_bgp_dampening_ipv4_in_cmd,
       "clear ip bgp dampening A.B.C.D in",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear route flap dampening information\n"
       "Network to clear damping information\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "network", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_ip_bgp_dampening_ipv4_in_prefix_filter,
       clear_ip_bgp_dampening_ipv4_in_prefix_filter_cmd,
       "clear ip bgp dampening A.B.C.D in prefix-filter",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear route flap dampening information\n"
       "Network to clear damping information\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "network", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_ip_bgp_dampening_ipv4_out,
       clear_ip_bgp_dampening_ipv4_out_cmd,
       "clear ip bgp dampening A.B.C.D out",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear route flap dampening information\n"
       "Network to clear damping information\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "network", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_ip_bgp_dampening_ipv4_soft,
       clear_ip_bgp_dampening_ipv4_soft_cmd,
       "clear ip bgp dampening A.B.C.D soft",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear route flap dampening information\n"
       "Network to clear damping information\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "network", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_ip_bgp_dampening_ipv4_soft_in,
       clear_ip_bgp_dampening_ipv4_soft_in_cmd,
       "clear ip bgp dampening A.B.C.D soft in",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear route flap dampening information\n"
       "Network to clear damping information\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "network", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_ip_bgp_dampening_ipv4_soft_in_prefix_filter,
       clear_ip_bgp_dampening_ipv4_soft_in_prefix_filter_cmd,
       "clear ip bgp dampening A.B.C.D soft in prefix-filter",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear route flap dampening information\n"
       "Network to clear damping information\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "network", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_ip_bgp_dampening_ipv4_soft_out,
       clear_ip_bgp_dampening_ipv4_soft_out_cmd,
       "clear ip bgp dampening A.B.C.D soft out",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear route flap dampening information\n"
       "Network to clear damping information\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "network", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_ip_bgp_dampening_ipv4_rsclient,
       clear_ip_bgp_dampening_ipv4_rsclient_cmd,
       "clear ip bgp dampening A.B.C.D rsclient",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear route flap dampening information\n"
       "Network to clear damping information\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "network", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_ip_bgp_dampening_ipv4m,
       clear_ip_bgp_dampening_ipv4m_cmd,
       "clear ip bgp dampening A.B.C.D/M",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear route flap dampening information\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "prefix", .value = argv[0] },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_ip_bgp_dampening_ipv4m_in,
       clear_ip_bgp_dampening_ipv4m_in_cmd,
       "clear ip bgp dampening A.B.C.D/M in",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear route flap dampening information\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "prefix", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_ip_bgp_dampening_ipv4m_in_prefix_filter,
       clear_ip_bgp_dampening_ipv4m_in_prefix_filter_cmd,
       "clear ip bgp dampening A.B.C.D/M in prefix-filter",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear route flap dampening information\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "prefix", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_ip_bgp_dampening_ipv4m_out,
       clear_ip_bgp_dampening_ipv4m_out_cmd,
       "clear ip bgp dampening A.B.C.D/M out",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear route flap dampening information\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "prefix", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_ip_bgp_dampening_ipv4m_soft,
       clear_ip_bgp_dampening_ipv4m_soft_cmd,
       "clear ip bgp dampening A.B.C.D/M soft",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear route flap dampening information\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Soft reconfig inbound and outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "prefix", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_ip_bgp_dampening_ipv4m_soft_in,
       clear_ip_bgp_dampening_ipv4m_soft_in_cmd,
       "clear ip bgp dampening A.B.C.D/M soft in",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear route flap dampening information\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "prefix", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_ip_bgp_dampening_ipv4m_soft_in_prefix_filter,
       clear_ip_bgp_dampening_ipv4m_soft_in_prefix_filter_cmd,
       "clear ip bgp dampening A.B.C.D/M soft in prefix-filter",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear route flap dampening information\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig inbound updates\n"
       "Push out prefix-list ORF and do inbound soft reconfig\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "prefix", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_in", .value = "in" },
      &(struct vty_arg) { .name = "soft_pefix_filter", .value = "prefix-filter" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_ip_bgp_dampening_ipv4m_soft_out,
       clear_ip_bgp_dampening_ipv4m_soft_out_cmd,
       "clear ip bgp dampening A.B.C.D/M soft out",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear route flap dampening information\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Soft reconfig inbound and outbound updates\n"
       "Soft reconfig outbound updates\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "prefix", .value = argv[0] },
      &(struct vty_arg) { .name = "soft", .value = "soft" },
      &(struct vty_arg) { .name = "soft_out", .value = "out" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

DEFUN (clear_ip_bgp_dampening_ipv4m_rsclient,
       clear_ip_bgp_dampening_ipv4m_rsclient_cmd,
       "clear ip bgp dampening A.B.C.D/M rsclient",
       "Reset functions\n"
       "IP information\n"
       "BGP information\n"
       "Clear route flap dampening information\n"
       "IP prefix <network>/<length>, e.g., 35.0.0.0/8\n"
       "Soft reconfig for rsclient RIB\n")
{
  struct vty_arg *args[] =
    {
      &(struct vty_arg) { .name = "dampening", .value = "dampening" },
      &(struct vty_arg) { .name = "prefix", .value = argv[0] },
      &(struct vty_arg) { .name = "soft_rsclient", .value = "rsclient" },
      NULL
    };
  return bgp_clear_dampening (vty, args);
}

void
bgp_vty_clear_init (void)
{
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_all_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_all_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_all_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_all_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_all_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_all_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_all_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_all_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_all_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_asn_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_asn_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_asn_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_asn_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_asn_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_asn_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_asn_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_asn_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_asn_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_ipv4_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_ipv4_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_ipv4_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_ipv4_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_ipv4_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_ipv4_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_ipv4_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_ipv4_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_ipv4_rsclient_cmd);
#ifdef HAVE_IPV6
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_ipv6_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_ipv6_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_ipv6_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_ipv6_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_ipv6_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_ipv6_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_ipv6_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_ipv6_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_ipv6_rsclient_cmd);
#endif /* HAVE_IPV6 */
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_external_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_external_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_external_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_external_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_external_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_external_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_external_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_external_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_external_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_peer_group_word_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_peer_group_word_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_peer_group_word_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_peer_group_word_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_peer_group_word_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_peer_group_word_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_peer_group_word_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_peer_group_word_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_peer_group_word_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_dampening_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_dampening_ipv4_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_dampening_ipv4_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_dampening_ipv4_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_dampening_ipv4_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_dampening_ipv4_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_dampening_ipv4_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_dampening_ipv4_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_dampening_ipv4_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_dampening_ipv4_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_dampening_ipv4m_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_dampening_ipv4m_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_dampening_ipv4m_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_dampening_ipv4m_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_dampening_ipv4m_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_dampening_ipv4m_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_dampening_ipv4m_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_dampening_ipv4m_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv4_safi_dampening_ipv4m_rsclient_cmd);
#ifdef HAVE_IPV6
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_all_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_all_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_all_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_all_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_all_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_all_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_all_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_all_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_all_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_asn_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_asn_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_asn_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_asn_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_asn_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_asn_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_asn_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_asn_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_asn_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_ipv4_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_ipv4_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_ipv4_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_ipv4_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_ipv4_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_ipv4_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_ipv4_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_ipv4_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_ipv4_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_ipv6_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_ipv6_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_ipv6_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_ipv6_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_ipv6_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_ipv6_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_ipv6_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_ipv6_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_ipv6_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_external_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_external_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_external_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_external_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_external_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_external_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_external_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_external_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_external_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_peer_group_word_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_peer_group_word_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_peer_group_word_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_peer_group_word_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_peer_group_word_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_peer_group_word_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_peer_group_word_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_peer_group_word_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_ipv6_safi_peer_group_word_rsclient_cmd);
#endif /* HAVE_IPV6 */
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_all_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_all_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_all_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_all_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_all_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_all_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_all_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_all_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_all_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_asn_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_asn_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_asn_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_asn_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_asn_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_asn_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_asn_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_asn_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_asn_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_ipv4_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_ipv4_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_ipv4_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_ipv4_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_ipv4_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_ipv4_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_ipv4_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_ipv4_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_ipv4_rsclient_cmd);
#ifdef HAVE_IPV6
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_ipv6_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_ipv6_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_ipv6_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_ipv6_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_ipv6_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_ipv6_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_ipv6_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_ipv6_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_ipv6_rsclient_cmd);
#endif /* HAVE_IPV6 */
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_external_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_external_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_external_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_external_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_external_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_external_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_external_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_external_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_external_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_peer_group_word_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_peer_group_word_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_peer_group_word_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_peer_group_word_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_peer_group_word_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_peer_group_word_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_peer_group_word_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_peer_group_word_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_vpnv4_unicast_peer_group_word_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_all_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_all_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_all_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_all_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_all_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_all_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_all_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_all_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_all_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_asn_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_asn_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_asn_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_asn_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_asn_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_asn_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_asn_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_asn_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_asn_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_ipv4_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_ipv4_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_ipv4_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_ipv4_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_ipv4_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_ipv4_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_ipv4_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_ipv4_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_ipv4_rsclient_cmd);
#ifdef HAVE_IPV6
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_ipv6_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_ipv6_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_ipv6_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_ipv6_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_ipv6_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_ipv6_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_ipv6_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_ipv6_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_ipv6_rsclient_cmd);
#endif /* HAVE_IPV6 */
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_external_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_external_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_external_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_external_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_external_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_external_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_external_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_external_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_external_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_peer_group_word_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_peer_group_word_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_peer_group_word_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_peer_group_word_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_peer_group_word_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_peer_group_word_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_peer_group_word_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_peer_group_word_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_peer_group_word_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_dampening_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_dampening_ipv4_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_dampening_ipv4_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_dampening_ipv4_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_dampening_ipv4_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_dampening_ipv4_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_dampening_ipv4_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_dampening_ipv4_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_dampening_ipv4_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_dampening_ipv4_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_dampening_ipv4m_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_dampening_ipv4m_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_dampening_ipv4m_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_dampening_ipv4m_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_dampening_ipv4m_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_dampening_ipv4m_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_dampening_ipv4m_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_dampening_ipv4m_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv4_safi_dampening_ipv4m_rsclient_cmd);
#ifdef HAVE_IPV6
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_all_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_all_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_all_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_all_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_all_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_all_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_all_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_all_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_all_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_asn_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_asn_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_asn_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_asn_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_asn_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_asn_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_asn_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_asn_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_asn_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_ipv4_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_ipv4_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_ipv4_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_ipv4_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_ipv4_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_ipv4_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_ipv4_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_ipv4_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_ipv4_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_ipv6_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_ipv6_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_ipv6_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_ipv6_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_ipv6_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_ipv6_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_ipv6_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_ipv6_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_ipv6_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_external_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_external_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_external_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_external_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_external_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_external_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_external_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_external_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_external_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_peer_group_word_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_peer_group_word_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_peer_group_word_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_peer_group_word_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_peer_group_word_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_peer_group_word_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_peer_group_word_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_peer_group_word_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_ipv6_safi_peer_group_word_rsclient_cmd);
#endif /* HAVE_IPV6 */
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_all_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_all_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_all_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_all_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_all_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_all_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_all_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_all_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_all_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_asn_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_asn_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_asn_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_asn_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_asn_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_asn_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_asn_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_asn_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_asn_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_ipv4_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_ipv4_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_ipv4_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_ipv4_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_ipv4_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_ipv4_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_ipv4_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_ipv4_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_ipv4_rsclient_cmd);
#ifdef HAVE_IPV6
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_ipv6_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_ipv6_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_ipv6_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_ipv6_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_ipv6_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_ipv6_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_ipv6_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_ipv6_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_ipv6_rsclient_cmd);
#endif /* HAVE_IPV6 */
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_external_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_external_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_external_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_external_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_external_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_external_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_external_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_external_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_external_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_peer_group_word_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_peer_group_word_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_peer_group_word_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_peer_group_word_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_peer_group_word_soft_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_peer_group_word_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_peer_group_word_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_peer_group_word_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_bgp_view_word_vpnv4_unicast_peer_group_word_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_all_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_all_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_all_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_all_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_all_soft_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_all_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_all_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_all_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_all_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_asn_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_asn_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_asn_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_asn_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_asn_soft_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_asn_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_asn_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_asn_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_asn_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_ipv4_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_ipv4_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_ipv4_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_ipv4_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_ipv4_soft_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_ipv4_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_ipv4_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_ipv4_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_ipv4_rsclient_cmd);
#ifdef HAVE_IPV6
  install_element (ENABLE_NODE, &clear_ip_bgp_ipv6_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_ipv6_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_ipv6_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_ipv6_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_ipv6_soft_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_ipv6_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_ipv6_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_ipv6_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_ipv6_rsclient_cmd);
#endif /* HAVE_IPV6 */
  install_element (ENABLE_NODE, &clear_ip_bgp_external_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_external_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_external_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_external_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_external_soft_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_external_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_external_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_external_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_external_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_group_word_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_group_word_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_group_word_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_group_word_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_group_word_soft_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_group_word_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_group_word_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_group_word_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_peer_group_word_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_dampening_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_dampening_ipv4_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_dampening_ipv4_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_dampening_ipv4_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_dampening_ipv4_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_dampening_ipv4_soft_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_dampening_ipv4_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_dampening_ipv4_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_dampening_ipv4_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_dampening_ipv4_rsclient_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_dampening_ipv4m_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_dampening_ipv4m_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_dampening_ipv4m_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_dampening_ipv4m_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_dampening_ipv4m_soft_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_dampening_ipv4m_soft_in_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_dampening_ipv4m_soft_in_prefix_filter_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_dampening_ipv4m_soft_out_cmd);
  install_element (ENABLE_NODE, &clear_ip_bgp_dampening_ipv4m_rsclient_cmd);
}