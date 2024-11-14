#ifndef HYPRSYMBOL_H
#define HYPRSYMBOL_H

#include <stdint.h>
#include <wayland-client-core.h>
#include <wayland-client-protocol.h>
#include "../include/wlr-layer-shell-unstable-v1.h"

struct client {
    /* Global objects */
    struct wl_display *display;
    struct wl_registry *registry;
    struct wl_compositor *compositor;
    struct wl_shm *shm;
    struct zwlr_layer_shell_v1 *layer_shell;

    /* Client objects */
    struct wl_buffer *buffer;
    struct zwlr_layer_surface_v1 *layer_surface;
    struct wl_surface *surface;
    int configured;

    /* 4 channels, 8 bytes each */
    uint32_t *pixels;
};

#endif /* !HYPRSYMBOL_H */