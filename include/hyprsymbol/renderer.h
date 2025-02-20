#ifndef RENDERER_H
#define RENDERER_H

#include <hyprsymbol/hyprsymbol.h>

extern const struct wl_callback_listener wl_surface_frame_listener;

void wl_surface_frame_done
(
    void *data, 
    struct wl_callback *callback, 
    uint32_t time
);

void setup_renderer(struct client *client);

void draw_frame(struct client *client);

#endif /* !RENDERER_H */
