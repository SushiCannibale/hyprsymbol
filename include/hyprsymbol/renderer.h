#ifndef RENDERER_H
#define RENDERER_H

#include <hyprsymbol/hyprsymbol.h>

// Everything that is about cairo and rendering / drawing should be done here.
// we'll use frame callbacks to know when to draw on the surface.
void draw_frame(struct client *client);

#endif /* !RENDERER_H */
