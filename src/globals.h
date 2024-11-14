#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdint.h>

#include <wayland-client.h>
#include "../include/wlr-layer-shell-unstable-v1.h"

extern struct wl_compositor *glob_compositor;
extern struct wl_shm *glob_shm;
extern struct zwlr_layer_shell_v1 *glob_layer_shell;

extern struct wl_buffer *buffer;
extern struct wl_surface *surface;
extern int configured;

/* 4*8 bytes pixels */
extern uint32_t *pixels;
#endif /* !GLOBALS_H */
