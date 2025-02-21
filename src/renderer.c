#include "cairo.h"
#include "pango/pango-layout.h"
#include "pango/pango-types.h"
#include <hyprsymbol/renderer.h>
#include <hyprsymbol/utils.h>
#include <stdio.h>

#include <pango/pangocairo.h>

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

void setup_renderer(struct client *client) {
	client->cr_surface = cairo_image_surface_create_for_data(
		client->pool_data, 
		CAIRO_FORMAT_ARGB32, 
			client->width, 
		client->height, 
		client->width * 4);
	client->cr = cairo_create(client->cr_surface);
}

void draw_frame(struct client *client) {
	int w = client->width;
	int h = client->height;

	cairo_t *cr = client->cr;
	// cairo_text_extents_t te;
	// cairo_font_extents_t fe;

	// cairo_font_extents(cr, &fe);
	// cairo_select_font_face(cr, "JetBrainsMonoNerdFont-Regular", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	PangoLayout *pl = pango_cairo_create_layout(cr);

	cairo_set_source_rgb(cr, 0x0, 0, 0);
	pango_layout_set_text(pl, "😀", -1);
	pango_layout_get_size(pl, &w, &h);
	cairo_move_to(cr, (w / PANGO_SCALE) / 2, (h / PANGO_SCALE) / 2);

	pango_cairo_show_layout(cr, pl);
}
