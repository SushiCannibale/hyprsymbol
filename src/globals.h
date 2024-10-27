#ifndef GLOBALS_H
#define GLOBALS_H

#include <wayland-client.h>
#include "xdg-shell.h"

extern struct wl_compositor *glob_compositor;
extern struct wl_shm *glob_shm;
/* Allows conversion from wl_surface into window */
extern struct xdg_wm_base *glob_xdg_wm;

extern struct wl_buffer *buffer;
extern struct wl_surface *surface;

extern unsigned char *pixels;
#endif /* !GLOBALS_H */
