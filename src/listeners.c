#include "handlers.h"

const struct wl_registry_listener registry_listener = {
    .global = registry_global_handler,
    .global_remove = registry_global_remove_handler
};

const struct zwlr_layer_surface_v1_listener zwlr_layer_surface_listener = {
	.configure = zwlr_layer_surface_configure_handler,
	.closed = zwlr_layer_surface_closed_handler
};

// const struct xdg_surface_listener xdg_surface_listener = {
// 	.configure = xdg_surface_configure_handler
// };
// 
// const struct xdg_wm_base_listener xdg_wm_base_listener = {
// 	.ping = xdg_wm_base_ping_handler
// };
