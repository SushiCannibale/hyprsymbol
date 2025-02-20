
#include "wlr-layer-shell-unstable-v1.h"
#include <wayland-client-core.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <hyprsymbol/hyprsymbol.h>
#include <hyprsymbol/shm.h>

#include <err.h>

#include <hyprsymbol/renderer.h>
#include <wayland-client-protocol.h>

static int setup_zwlr_surface(struct client *client) {
	zwlr_layer_surface_v1_set_size(client->wl_surface_role, client->width, client->height);
	zwlr_layer_surface_v1_set_anchor(client->wl_surface_role, ZWLR_LAYER_SURFACE_V1_ANCHOR_BOTTOM | ZWLR_LAYER_SURFACE_V1_ANCHOR_RIGHT);
	return 0;
}

static int register_zwlr_listener(struct client *client) {
	zwlr_layer_surface_v1_add_listener(
		client->wl_surface_role,
		&zwlr_layer_surface_listener,
		client
	);
	return 0;
}

static int create_surface_role(struct client *client) {
    client->wl_surface_role = zwlr_layer_shell_v1_get_layer_surface(
		client->zwlr_layer_shell,
		client->wl_surface,
		NULL,
		ZWLR_LAYER_SHELL_V1_LAYER_TOP,
		"hyprsymbol"
	);
	if (client->wl_surface_role == NULL) {
		errx(1, "Can't get 'zwlr_surface_layer' role.");
		return 1;
	}

	return 0;
}

static int register_shm_listener(struct client *client) {
	wl_shm_add_listener(
		client->wl_shm,
	&wl_shm_listener,
	client
	);
	return 0;
}

static int register_first_frame_callback(struct client *client) {
	struct wl_callback *callback = wl_surface_frame(client->wl_surface);
	wl_callback_add_listener(callback, &wl_surface_frame_listener, client);
	return 0;
}

static int create_surface(struct client *client) {
	/* Requests a wl_surface */
    client->wl_surface = wl_compositor_create_surface(client->compositor);

	if (client->wl_surface == NULL) {
		errx(1, "Can't get 'surface' created.");
		return 1;
	}

	return 0;
}

static int register_globals(struct client *client) {
    client->registry = wl_display_get_registry(client->display);
    wl_registry_add_listener(client->registry, &registry_listener, client);

	/* Wayland is asynchronous. We need to wait for the initial set of globals to appear */
    wl_display_roundtrip(client->display);

	if (client->compositor == NULL) {
		errx(1, "Can't get 'compositor' registry.");
		return 1;
	}

	if (client->wl_shm == NULL) {
		errx(1, "Can't get 'shm' registry.");
		return 1;
	}

	if (client->zwlr_layer_shell == NULL) {
		errx(1, "Can't get 'zwlr_layer_shell' registry.");
		return 1;
	}

	return 0;
}

static int client_connect(struct client *client) {
	client->display = wl_display_connect(NULL);
	if (client->display == NULL) {
		fprintf(stderr, "No display available");
		return 1;
	}

	return 0;
}

int main(void) {
	struct client *client = client_new(200, 200);

	client_connect(client);
    register_globals(client);

	create_shm_pool(client);
	create_shm_buffer(client);
	register_shm_listener(client);

	create_surface(client);
	create_surface_role(client);
	register_zwlr_listener(client);

	setup_zwlr_surface(client);

	register_first_frame_callback(client);
	setup_renderer(client);

	/* Signal that the surface is ready to be configured */
    wl_surface_commit(client->wl_surface);

	/* Ensures all the requests/events have been handled */
	wl_display_roundtrip(client->display);

	/* Attaches the buffer freshly created from the pool 
	(starting at (0, 0), it covers the whole shm pool) */
	wl_surface_attach(client->wl_surface, client->shm_buffer, 0, 0);

	// wl_surface_attach(client->wl_surface, client->shm_buffer, 0, 0);
	wl_surface_commit(client->wl_surface);

	while (1) {
		wl_display_dispatch(client->display);
	}

	// client_destroy(client);
	return 0;
}
