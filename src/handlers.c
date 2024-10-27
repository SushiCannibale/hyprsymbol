#include "handlers.h"

#include <string.h>

#include "listeners.h"
#include "globals.h"

void registry_global_handler
(
    void *data,
    struct wl_registry *registry,
    uint32_t name,
    const char *interface,
    uint32_t version
) {
    if (strcmp(interface, wl_compositor_interface.name) == 0) {
        glob_compositor = wl_registry_bind(registry, name, &wl_compositor_interface, 3);
    } else if (strcmp(interface, wl_shm_interface.name) == 0) {
        glob_shm = wl_registry_bind(registry, name, &wl_shm_interface, 1);
    } else if (strcmp(interface, xdg_wm_base_interface.name) == 0) {
        glob_xdg_wm = wl_registry_bind(registry, name, &xdg_wm_base_interface, 1);
        xdg_wm_base_add_listener(glob_xdg_wm, &xdg_wm_base_listener, NULL);
    }
}

void registry_global_remove_handler
(
    void *data,
    struct wl_registry *registry,
    uint32_t name
) {}


void xdg_wm_base_ping_handler
(
	void *data,
	struct xdg_wm_base *xdg_wm_base,
	uint32_t serial
) {
	xdg_wm_base_pong(xdg_wm_base, serial);	
}

void xdg_surface_configure_handler
(
	void *data,
	struct xdg_surface *xdg_surface,
	uint32_t serial
) {
	xdg_surface_ack_configure(xdg_surface, serial);
	if (pixels != NULL) {
		wl_surface_commit(surface);
	}

	/* TODO: do the rendering after acknowledge, ending by a wl_surface_commit */
}
