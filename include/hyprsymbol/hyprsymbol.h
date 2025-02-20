#ifndef HYPRSYMBOL_H
#define HYPRSYMBOL_H

#include <stdint.h>
#include <wayland-client-core.h>
#include <wayland-client-protocol.h>
#include <cairo.h>
#include <wlr-layer-shell-unstable-v1.h>

struct client {
    struct wl_display *display;
    struct wl_compositor *compositor;
    struct wl_registry *registry;

    /* ******************************* SURFACE ****************************** */
    struct wl_surface *wl_surface;
    struct zwlr_layer_surface_v1 *wl_surface_role;
    struct zwlr_layer_shell_v1 *zwlr_layer_shell;

    /* ******************************* MEMORY ******************************* */
    struct wl_shm *wl_shm;
    struct wl_shm_pool *shm_pool;
    struct wl_buffer *shm_buffer;
    unsigned char *pool_data;

    /* ****************************** RENDERING ***************************** */
    cairo_t *cr;
    cairo_surface_t *cr_surface;

    /* ******************************* OTHERS ******************************* */
    int width;
    int height;
    float offset;
    int last_frame;
};

struct client *client_new(int width, int height);
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
