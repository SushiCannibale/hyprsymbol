#ifndef HANDLERS_H
#define HANDLERS_H

#include "wlr-layer-shell-unstable-v1.h"
#include <wayland-client.h>

void registry_global_handler
(
    void *data,
    struct wl_registry *registry,
    uint32_t name,
    const char *interface,
    uint32_t version
);

void registry_global_remove_handler
(
    void *data,
    struct wl_registry *registry,
    uint32_t name
);

void zwlr_layer_surface_configure_handler
(
	void *data,
	struct zwlr_layer_surface_v1 *zwlr_layer_surface_v1,
	uint32_t serial,
	uint32_t width,
	uint32_t height
);

void zwlr_layer_surface_closed_handler
(
	void *data,
	struct zwlr_layer_surface_v1 *zwlr_layer_surface_v1
);

// void xdg_surface_configure_handler
// (
// 	void *data,
// 	struct xdg_surface *xdg_surface,
// 	uint32_t serial
// );

// void xdg_wm_base_ping_handler
// (
// 	void *data,
// 	struct xdg_wm_base *xdg_wm_base,
// 	uint32_t serial
// );

#endif /* !HANDLERS_H */
