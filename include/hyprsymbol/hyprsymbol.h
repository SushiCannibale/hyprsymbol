#ifndef HYPRSYMBOL_H
#define HYPRSYMBOL_H

#include <stdint.h>
#include <wayland-client-core.h>
#include <wayland-client-protocol.h>
#include <cairo.h>
#include <wlr-layer-shell-unstable-v1.h>

struct client {
    struct wl_display *display;

    /* globals */
    struct wl_registry *registry;
    struct wl_compositor *compositor;

    /**
     * @brief The registry for zwlr-relative events
     * 
     */
    struct zwlr_layer_shell_v1 *zwlr_layer_shell;

    struct wl_shm *wl_shm;

    /**
     * @brief All the memory from which could be created buffers.
     * The pool is mmaped both by the client and the server. Buffers are 
     * therefore pointers to sections of this pool.
     */
    struct wl_shm_pool *shm_pool;

    /* The role of the wl_surface */
    struct zwlr_layer_surface_v1 *wl_surface_role;
    struct wl_surface *wl_surface;

    size_t width;
    size_t height;
    unsigned char *pool_data;
    // int last_frame;
    // float offset;

    /**
     * @brief The buffer used for the drawing operation.
     * Buffer issued from the shared memory pool.
     * It is the object to which the client make rendering calls when necessary
     */
    struct wl_buffer *shm_buffer;

    // struct wl_surface *surface;
    // int configured;

    // cairo_t *cairo;
    // cairo_surface_t *cairo_surface;
    // uint32_t format;
};

struct client *client_new(size_t width, size_t height);
// void client_destroy(struct client *client);

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
