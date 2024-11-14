#include "handlers.h"

#include <string.h>

#include "globals.h"

/**
 * Fetches the globals from the Compositor
 */
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
    } else if (strcmp(interface, zwlr_layer_shell_v1_interface.name) == 0) {
        glob_layer_shell = wl_registry_bind(registry, name, &zwlr_layer_shell_v1_interface, 1);
    }
}

void registry_global_remove_handler
(
    void *data,
    struct wl_registry *registry,
    uint32_t name
) { }


void zwlr_layer_surface_configure_handler
(
	void *data,
	struct zwlr_layer_surface_v1 *zwlr_layer_surface,
	uint32_t serial,
	uint32_t width,
	uint32_t height
) {
	zwlr_layer_surface_v1_ack_configure(zwlr_layer_surface, serial);
	if (!configured) {
		configured = 1;
	}

	wl_surface_commit(surface);
}

void zwlr_layer_surface_closed_handler
(
	void *data,
	struct zwlr_layer_surface_v1 *zwlr_layer_surface_v1
) {
	
}

// void xdg_surface_configure_handler
// (
// 	void *data,
// 	struct xdg_surface *xdg_surface,
// 	uint32_t serial
// ) {
// 	xdg_surface_ack_configure(xdg_surface, serial);
// 	if (configured) {
// 		wl_surface_commit(surface);
// 	} else {
// 		configured = 1;
// 	}
// 	/* TODO: do the rendering after acknowledge, ending by a wl_surface_commit */
// }
