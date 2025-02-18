#ifndef HYPRSYMBOL_H
#define HYPRSYMBOL_H

#include <stdint.h>
#include <wayland-client-core.h>
#include <wayland-client-protocol.h>
#include <cairo.h>
#include <wlr-layer-shell-unstable-v1.h>

struct client {
    size_t width;
    size_t height;

    struct wl_display *display;
    struct wl_registry *registry;
    struct wl_compositor *compositor;
    struct wl_shm *shm;

    int last_frame;
    float offset;

    /**
     * @brief The pool of memory shared between the server and the client.
     * This is where all the pixel data is stored on the disk. 
     * The pool must be accessed through the usage of a wl_buffer, not directly
     */

    /**
     * @brief The buffer used for the drawing operation.
     * Buffer issued from the shared memory pool.
     * It is the object to which the client make rendering calls when necessary
     */
    struct wl_buffer *shm_buffer;
    /**
     * The mass of pixels available to the client
     */
    char *shm_data;

    struct zwlr_layer_shell_v1 *layer_shell;
    struct zwlr_layer_surface_v1 *layer_surface;
    struct wl_surface *surface;
    int configured;

    cairo_t *cairo;
    cairo_surface_t *cairo_surface;
    // uint32_t format;
};

struct client *client_new(size_t width, size_t height);
void client_destroy(struct client *client);

/* ************************************************ */

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

#endif /* !HYPRSYMBOL_H */
