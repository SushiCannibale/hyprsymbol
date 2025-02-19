#ifndef RENDERER_H
#define RENDERER_H

#include <hyprsymbol/hyprsymbol.h>

struct pixel {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char alpha;
};

extern const struct wl_callback_listener wl_surface_frame_listener;

/**
 * Asks the compositor for a new frame because the 
 * current one is ready to be drawn
 */
void wl_surface_frame_done
(
    void *data, 
    struct wl_callback *callback, 
    uint32_t time
);

// Everything that is about cairo and rendering / drawing should be done here.
// we'll use frame callbacks to know when to draw on the surface.
void draw_frame(struct client *client);

#endif /* !RENDERER_H */
