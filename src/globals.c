#include "globals.h"

struct wl_compositor *glob_compositor             = NULL;
struct wl_shm *glob_shm                           = NULL;
/* Layered shell surface */
struct zwlr_layer_shell_v1 *glob_layer_shell      = NULL;

/* Client's objects */
struct wl_buffer *buffer                          = NULL;
struct wl_surface *surface                        = NULL;
int configured                                    = 0;

uint32_t *pixels                                  = NULL;
