
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
#include <err.h>

#include <hyprsymbol/renderer.h>

static int setup_zwlr_surface(struct client *client) {
	/* Give the surface a role */
    client->layer_surface = zwlr_layer_shell_v1_get_layer_surface(
		client->layer_shell,
		client->surface,
		NULL,
		ZWLR_LAYER_SHELL_V1_LAYER_TOP,
		"Hyprsymbol"
	);
	if (client->layer_surface == NULL) {
		errx(1, "unable to get 'layer_surface'.");
		return 1;
	}

	zwlr_layer_surface_v1_set_size(
		client->layer_surface,
		client->width,
		client->height
	);
	zwlr_layer_surface_v1_set_anchor(
		client->layer_surface, 
		ZWLR_LAYER_SURFACE_V1_ANCHOR_BOTTOM | ZWLR_LAYER_SURFACE_V1_ANCHOR_RIGHT
	);

    zwlr_layer_surface_v1_add_listener(
		client->layer_surface,
		&zwlr_layer_surface_listener,
		client
	);

	return 0;
}

static int create_surface(struct client *client) {
	/* Requests a wl_surface */
    client->surface = wl_compositor_create_surface(client->compositor);

	if (client->surface == NULL) {
		errx(1, "unable to bind 'surface'.");
		return 1;
	}

	return 0;
}

static int register_listeners(struct client *client) {
    client->registry = wl_display_get_registry(client->display);
    wl_registry_add_listener(client->registry, &registry_listener, client);

	wl_display_dispatch(client->display);
    wl_display_roundtrip(client->display);

	if (client->compositor == NULL) {
		errx(1, "unable to bind 'compositor'.");
		return 1;
	}

	if (client->shm == NULL) {
		errx(1, "unable to bind 'shm'.");
		return 1;
	}

	if (client->layer_shell == NULL) {
		errx(1, "unable to bind 'layer_shell'.");
		return 1;
	}

	wl_shm_add_listener(
		client->shm,
	&wl_shm_listener,
	client
	);

	return 0;
}

static int connect_to_compositor(struct client *client) {
	client->display = wl_display_connect(NULL);
	if (client->display == NULL) {
		fprintf(stderr, "No display available");
		return 1;
	}

	return 0;
}

int main(void) {
	struct client *client = client_new(200, 200);

	connect_to_compositor(client);
    register_listeners(client);
	create_surface(client);
	setup_zwlr_surface(client);

	
	/* Initial commit before surface attachment, as required */	
    wl_surface_commit(client->surface);

    wl_display_dispatch(client->display);

	/* Creates the buffer and attach it to the surface */
	create_shm_buffer(client);
	wl_surface_attach(client->surface, client->shm_buffer, 0, 0);
	wl_surface_commit(client->surface);

	draw_frame(client);

	while (wl_display_dispatch(client->display) != -1) { }

	zwlr_layer_surface_v1_destroy(client->layer_surface);
	wl_surface_destroy(client->surface);
    wl_display_disconnect(client->display);

	_exit:
	client_free(client);
	return 0;

	_exit_fail:
	client_free(client);
	return EXIT_FAILURE;
}
