#include <hyprsymbol/handlers.h>
#include <hyprsymbol/utils.h>

#include <string.h>
#include <wayland-client-protocol.h>
#include <stdbool.h>

#include <hyprsymbol/hyprsymbol.h>

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
    UNUSED uint32_t version
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
    UNUSED void *data,
    UNUSED struct wl_registry *registry,
    UNUSED uint32_t name
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
    zwlr_layer_surface_v1_set_size(client->layer_surface, width, height);
	zwlr_layer_surface_v1_set_anchor(client->layer_surface, 
		ZWLR_LAYER_SURFACE_V1_ANCHOR_BOTTOM | ZWLR_LAYER_SURFACE_V1_ANCHOR_RIGHT);

    wl_surface_commit(client->surface);
}

void zwlr_layer_surface_closed_handler
(
	UNUSED void *data,
	UNUSED struct zwlr_layer_surface_v1 *zwlr_layer_surface_v1
) {
	
}

/* ************************************************ */

const struct wl_callback_listener wl_surface_frame_listener = {
	.done = wl_surface_frame_done,
};

void wl_surface_frame_done
(
    void *data, 
    struct wl_callback *callback, 
    uint32_t time
) {
	/* Destroy this callback */
	wl_callback_destroy(callback);

	/* Request another frame */
	struct client *client = data;
	callback = wl_surface_frame(client->surface);
	wl_callback_add_listener(callback, &wl_surface_frame_listener, client);

	/* Update scroll amount at 24 pixels per second */
	if (state->last_frame != 0) {
		int elapsed = time - state->last_frame;
		state->offset += elapsed / 1000.0 * 24;
	}

	/* Submit a frame for this event */
	struct wl_buffer *buffer = draw_frame(state);
	wl_surface_attach(state->wl_surface, buffer, 0, 0);
	wl_surface_damage_buffer(state->wl_surface, 0, 0, INT32_MAX, INT32_MAX);
	wl_surface_commit(state->wl_surface);

	state->last_frame = time;
}

/* ************************************************ */

const struct wl_shm_listener wl_shm_listener = {
    .format = wl_shm_format_handler
};

void wl_shm_format_handler
(
	UNUSED void *data,
	UNUSED struct wl_shm *wl_shm,
	UNUSED uint32_t format
) {
    // struct client *client = data;
    // client->format = format;
}