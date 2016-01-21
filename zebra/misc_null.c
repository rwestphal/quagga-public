#include <zebra.h>

#include "prefix.h"
#include "zebra/rtadv.h"
#include "zebra/irdp.h"
#include "zebra/interface.h"
#include "zebra/zebra_fpm.h"
#ifdef HAVE_MPLS
#include "zebra/mpls_lib.h"
#endif

void ifstat_update_proc (void) { return; }
#ifdef HAVE_SYS_WEAK_ALIAS_PRAGMA
#pragma weak rtadv_config_write = ifstat_update_proc
#pragma weak irdp_config_write = ifstat_update_proc
#pragma weak ifstat_update_sysctl = ifstat_update_proc
#else
void rtadv_config_write (struct vty *vty, struct interface *ifp) { return; }
void irdp_config_write (struct vty *vty, struct interface *ifp) { return; }
void ifstat_update_sysctl (void) { return; }
#endif

void
zfpm_trigger_update (struct route_node *rn, const char *reason)
{
  return;
}

#ifdef HAVE_MPLS
int mpls_enabled;
void mpls_route_install_hook (struct route_node *rn) { return; }
void mpls_route_uninstall_hook (struct route_node *rn) { return; }
void mpls_lib_update () {}
#endif
