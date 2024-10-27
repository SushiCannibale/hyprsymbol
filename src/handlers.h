#ifndef HANDLERS_H
#define HANDLERS_H

#include "xdg-shell.h"
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

void xdg_surface_configure_handler
(
	void *data,
	struct xdg_surface *xdg_surface,
	uint32_t serial
);

void xdg_wm_base_ping_handler
(
	void *data,
	struct xdg_wm_base *xdg_wm_base,
	uint32_t serial
);

#endif /* !HANDLERS_H */
