#include "handlers.h"

const struct wl_registry_listener registry_listener = {
    .global = registry_global_handler,
    .global_remove = registry_global_remove_handler
};

const struct xdg_surface_listener xdg_surface_listener = {
	.configure = xdg_surface_configure_handler
};

const struct xdg_wm_base_listener xdg_wm_base_listener = {
	.ping = xdg_wm_base_ping_handler
};
