#ifndef HANDLERS_H
#define HANDLERS_H

#include "../include/wlr-layer-shell-unstable-v1.h"
#include <wayland-client.h>

extern const struct wl_registry_listener registry_listener;

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

/* ************************************************ */

extern const struct zwlr_layer_surface_v1_listener zwlr_layer_surface_listener;

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

/* ************************************************ */

#endif /* !HANDLERS_H */
