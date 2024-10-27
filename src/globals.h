#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdint.h>

#include <wayland-client.h>
#include "xdg-shell.h"

extern struct wl_compositor *glob_compositor;
extern struct wl_shm *glob_shm;
/* Allows conversion from wl_surface into window */
extern struct xdg_wm_base *glob_xdg_wm;

extern struct wl_buffer *buffer;
extern struct wl_surface *surface;
extern int configured;

/* 4*8 bytes pixels */
extern uint32_t *pixels;
#endif /* !GLOBALS_H */
