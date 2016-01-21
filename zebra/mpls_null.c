#include <zebra.h>

#include "if.h"

#include "zebra/mpls_lib.h"

int mpls_kernel_enable_interface (struct interface *ifp) { return 0; };
int mpls_kernel_disable_interface (struct interface *ifp) { return 0; };
int mpls_kernel_install_ilm (u_int32_t in_label, struct mpls_lsp *lsp) { return 0; }
int mpls_kernel_uninstall_ilm (u_int32_t in_label, struct mpls_lsp *lsp) { return 0; }
void mpls_kernel_init (void) {}
void mpls_kernel_exit (void) {}
