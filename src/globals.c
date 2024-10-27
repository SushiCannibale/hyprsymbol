#include "globals.h"

/* Gloal objects (singletons) */
struct wl_compositor *glob_compositor = NULL;
struct wl_shm *glob_shm               = NULL;
/* Allows conversion from wl_surface into window */
struct xdg_wm_base *glob_xdg_wm       = NULL;

/* Client's objects */
struct wl_buffer *buffer              = NULL;
struct wl_surface *surface            = NULL;
int configured                        = 0;

uint32_t *pixels                 = NULL;
