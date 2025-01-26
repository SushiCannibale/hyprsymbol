
#include <wayland-client-core.h>
// #define _POSIX_C_SOURCE 200112L

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <hyprsymbol/hyprsymbol.h>
#include <hyprsymbol/handlers.h>
#include <hyprsymbol/shm.h>

// #include <wlr-layer-shell-unstable-v1.h>
// #include <wayland-client.h>
// #include <wayland-client-protocol.h>

#include <cairo/cairo.h>

size_t WIDTH = 200;
size_t HEIGHT = 200;

/**
 * Writes some data to the shared memory object for the buffer to render.
 */
static void draw(struct client *client) {
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

int main(void) {
	struct client client = { 0 };

    client.display = wl_display_connect(NULL);
	if (client.display == NULL) {
		fprintf(stderr, "No display available");
		return EXIT_FAILURE;
	}
	
    /* Fetch the list of globals we are interested in */
    client.registry = wl_display_get_registry(client.display);
    wl_registry_add_listener(client.registry, &registry_listener, &client);
    wl_display_roundtrip(client.display);

	if (client.compositor == NULL) {
		fprintf(stderr, "unable to bind to 'compositor'.");
		return EXIT_FAILURE;
	}

	if (client.shm == NULL) {
		fprintf(stderr, "unable to bind to 'shm'.");
		return EXIT_FAILURE;
	}

	if (client.layer_shell == NULL) {
		fprintf(stderr, "unable to bind to 'layer_shell'.");
		return EXIT_FAILURE;
	}

	/* Requests a wl_surface */
    client.surface = wl_compositor_create_surface(client.compositor);

	/* Give the surface a role */
    client.layer_surface = zwlr_layer_shell_v1_get_layer_surface(
			client.layer_shell,
		   	client.surface,
		   	NULL,
		   	ZWLR_LAYER_SHELL_V1_LAYER_TOP,
			"Hyprsymbol"
		);
	zwlr_layer_surface_v1_set_size(client.layer_surface, WIDTH, HEIGHT);
	zwlr_layer_surface_v1_set_anchor(client.layer_surface, 
		ZWLR_LAYER_SURFACE_V1_ANCHOR_BOTTOM | ZWLR_LAYER_SURFACE_V1_ANCHOR_RIGHT);

    zwlr_layer_surface_v1_add_listener(client.layer_surface, &zwlr_layer_surface_listener, &client);
	wl_shm_add_listener(client.shm, &wl_shm_listener, &client);
	/* Initial commit before surface attachment, as required */	
    wl_surface_commit(client.surface);

    wl_display_dispatch(client.display);

	/* Creates the buffer and attach it to the surface */
	create_shm_buffer(&client, WIDTH, HEIGHT);
	wl_surface_attach(client.surface, client.shm_buffer, 0, 0);
	wl_surface_commit(client.surface);

	draw(&client);

	while (wl_display_dispatch(client.display) != -1) { }

	zwlr_layer_surface_v1_destroy(client.layer_surface);
	wl_surface_destroy(client.surface);
    wl_display_disconnect(client.display);
	return 0;
}
