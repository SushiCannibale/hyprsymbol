#include "wlr-layer-shell-unstable-v1.h"
#include <hyprsymbol/hyprsymbol.h>
#include <hyprsymbol/utils.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

struct client *client_new(size_t width, size_t height) {
    struct client *client = calloc(1, sizeof(*client));
    client->width = width;
    client->height = height;
    return client;
}

// void client_destroy(struct client *client) {
//     munmap(client->shm_buffer, client->width * client->height * 4);

//     zwlr_layer_shell_v1_destroy(client->layer_shell);
//     zwlr_layer_surface_v1_destroy(client->layer_surface);
//     wl_shm_destroy(client->shm);
//     wl_registry_destroy(client->registry);
// 	wl_surface_destroy(client->surface);
//     wl_compositor_destroy(client->compositor);
//     wl_display_disconnect(client->display);

//     free(client);
// }

/* ************************************************ */

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
        client->compositor = wl_registry_bind(registry, name, &wl_compositor_interface, version);
    } else if (strcmp(interface, wl_shm_interface.name) == 0) {
        client->wl_shm = wl_registry_bind(registry, name, &wl_shm_interface, version);
    } else if (strcmp(interface, zwlr_layer_shell_v1_interface.name) == 0) {
        client->zwlr_layer_shell = wl_registry_bind(registry, name, &zwlr_layer_shell_v1_interface, version);
    }
}

void registry_global_remove_handler
(
    UNUSED void *data,
    UNUSED struct wl_registry *registry,
    UNUSED uint32_t name
) {
    
}

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
    zwlr_layer_surface_v1_set_size(
        client->wl_surface_role, 
        width, 
        height);
	zwlr_layer_surface_v1_set_anchor(
        client->wl_surface_role,
		ZWLR_LAYER_SURFACE_V1_ANCHOR_BOTTOM | ZWLR_LAYER_SURFACE_V1_ANCHOR_RIGHT);

	zwlr_layer_surface_v1_ack_configure(zwlr_layer_surface, serial);
}

void zwlr_layer_surface_closed_handler
(
	UNUSED void *data,
	UNUSED struct zwlr_layer_surface_v1 *zwlr_layer_surface_v1
) {

}
