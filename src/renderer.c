#include <hyprsymbol/renderer.h>

#include <string.h>

void draw_frame(struct client *client) {
	memset(client->shm_data, 100, 200 * 200 * 4);
    // cairo_surface_t *surface = cairo_image_surface_create(
    //     CAIRO_FORMAT_ARGB32, 200, 200);
    // client->cairo = cairo_create(surface);

    // cairo_select_font_face(client->cairo, "serif", CAIRO_FONT_SLANT_NORMAL,
    //     CAIRO_FONT_WEIGHT_BOLD);
    // cairo_set_font_size(client->cairo, 24.0);
    // cairo_set_source_rgb(client->cairo, 0.0, 0.0, 1.0);
    // cairo_move_to(client->cairo, 10.0, 50.0);
    // cairo_show_text(client->cairo, "Hello, world!");

    // cairo_destroy(client->cairo);
    // cairo_surface_write_to_png(surface, "hello.png");
    // cairo_surface_destroy(surface);
    // return 0;
	// memset(client->pixels, 0, 200 * 200 * 4);
}
