#include <hyprsymbol/renderer.h>
#include <hyprsymbol/utils.h>

#include <stdio.h>

const struct wl_callback_listener wl_surface_frame_listener = {
	.done = wl_surface_frame_done,
};

void wl_surface_frame_done
(
    UNUSED void *data, 
    UNUSED struct wl_callback *callback, 
    UNUSED uint32_t time
) {
	struct client *client = data;
	wl_callback_destroy(callback);

	/* Request another frame */
	callback = wl_surface_frame(client->wl_surface);
	wl_callback_add_listener(callback, &wl_surface_frame_listener, client);

	/* Update scroll amount at 24 pixels per second */
	if (client->last_frame != 0) {
		int elapsed = time - client->last_frame;
		client->offset += elapsed / 1000.0 * 24;
	}

	/* Submit a frame for this event */
	draw_frame(client);
	wl_surface_attach(client->wl_surface, client->shm_buffer, 0, 0);
	wl_surface_damage_buffer(client->wl_surface, 0, 0, client->width, client->height);
	wl_surface_commit(client->wl_surface);

	client->last_frame = time;
	printf("Received `wl_surface_frame_done` { time:%d }\n", time);
}

/* ************************************************ */

void set_rgb(struct pixel *pixel, unsigned char r, unsigned char g, unsigned char b) {
	pixel->alpha = 0xFF;
	pixel->red = r;
	pixel->green = g;
	pixel->blue = b;
}

void draw_frame(struct client *client) {
	int offset = (int)client->offset % 8;
 	for (size_t y = 0; y < client->height; ++y) {
 		for (size_t x = 0; x < client->width; ++x) {
			struct pixel *pixel = (struct pixel *)(client->pool_data + y*4*client->width + x * 4);

			if (((x + offset) + (y + offset) / 8 * 8) % 16 < 8) {
				set_rgb(pixel, 0x66, 0x66, 0x66);
 			} else {
				set_rgb(pixel, 0xEE, 0xEE, 0xEE);
			}
		}
	}

	// memset(client->shm_data, 100, 200 * 200 * 4);
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
