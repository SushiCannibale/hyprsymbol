#ifndef HYPRSYMBOL_H
#define HYPRSYMBOL_H

#include <stdint.h>
#include <wayland-client-core.h>
#include <wayland-client-protocol.h>
#include <cairo.h>
#include <wlr-layer-shell-unstable-v1.h>

struct client {
    struct wl_display *display;
    struct wl_registry *registry;
    struct wl_compositor *compositor;
    struct wl_shm *shm;

    /**
     * @brief The pool of memory shared between the server and the client.
     * This is where all the pixel data is stored on the disk. 
     * The pool must be accessed through the usage of a wl_buffer, not directly
     */
    // struct wl_shm_pool* shm_pool;

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
    struct wl_surface *surface; // why do we have 2 surfaces ?
    int configured;

    cairo_t *cairo;
    cairo_surface_t *cairo_surface;
    // uint32_t format;
};

#endif /* !HYPRSYMBOL_H */
