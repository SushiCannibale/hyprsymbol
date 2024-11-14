#include "handlers.h"

#include <string.h>
#include <wayland-client-protocol.h>
#include <stdbool.h>

#include "hyprsymbol.h"

const struct wl_registry_listener registry_listener = {
    .global = registry_global_handler,
    .global_remove = registry_global_remove_handler
};

void registry_global_handler
(
    void *data,
    struct wl_registry *registry,
    uint32_t name,
    const char *interface,
    uint32_t version
) {
    struct client *client = data;
    if (strcmp(interface, wl_compositor_interface.name) == 0) {
        client->compositor = wl_registry_bind(registry, name, &wl_compositor_interface, 3);
    } else if (strcmp(interface, wl_shm_interface.name) == 0) {
        client->shm = wl_registry_bind(registry, name, &wl_shm_interface, 1);
    } else if (strcmp(interface, zwlr_layer_shell_v1_interface.name) == 0) {
        client->layer_shell = wl_registry_bind(registry, name, &zwlr_layer_shell_v1_interface, 1);
    }
}

void registry_global_remove_handler
(
    void *data,
    struct wl_registry *registry,
    uint32_t name
) { }

/* ************************************************ */

const struct zwlr_layer_surface_v1_listener zwlr_layer_surface_listener = {
	.configure = zwlr_layer_surface_configure_handler,
	.closed = zwlr_layer_surface_closed_handler
};

void zwlr_layer_surface_configure_handler
(
	void *data,
	struct zwlr_layer_surface_v1 *zwlr_layer_surface,
	uint32_t serial,
	uint32_t width,
	uint32_t height
) {
    struct client *client = data;
	zwlr_layer_surface_v1_ack_configure(zwlr_layer_surface, serial);
    if (!client->configured) {
        client->configured = true;
    }

    wl_surface_commit(client->surface);
    /* TODO: Check if resizing is needed */
}

void zwlr_layer_surface_closed_handler
(
	void *data,
	struct zwlr_layer_surface_v1 *zwlr_layer_surface_v1
) {
	
}

/* ************************************************ */