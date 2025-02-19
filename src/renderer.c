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
	// /* Destroy this callback */
	// wl_callback_destroy(callback);

	// /* Request another frame */
	// struct client *client = data;
	// callback = wl_surface_frame(client->wl_surface);
	// wl_callback_add_listener(callback, &wl_surface_frame_listener, client);

	// /* Update scroll amount at 24 pixels per second */
	// if (client->last_frame != 0) {
	// 	int elapsed = time - client->last_frame;
	// 	client->offset += elapsed / 1000.0 * 24;
	// }

	// /* Submit a frame for this event */
	// struct wl_buffer *buffer = draw_frame(client);
	// wl_surface_attach(client->surface, buffer, 0, 0);
	// wl_surface_damage_buffer(client->surface, 0, 0, INT32_MAX, INT32_MAX);
	// wl_surface_commit(client->surface);

	// client->last_frame = time;
	printf("Received `wl_surface_frame_done` { time:%d }", time);
}

/* ************************************************ */

void draw_frame(struct client *client) {
	// int offset = (int)client->offset % 8;
 	// for (size_t y = 0; y < client->height; ++y) {
 	// 	for (size_t x = 0; x < client->width; ++x) {
	// 		if ((x + y / 8 * 8) % 16 < 8) {
	// 			if (((x + offset) + (y + offset) / 8 * 8) % 16 < 8) {
	// 				client->shm_data[y * client->width + x] = 0xFF666666;
	// 			} else {
	// 				client->shm_data[y * client->width + x] = 0xFFEEEEEE;
	// 			}
	// 		}
	// 	}
	// }

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
