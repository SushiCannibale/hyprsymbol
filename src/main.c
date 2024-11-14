
#define _POSIX_C_SOURCE 200112L

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "hyprsymbol.h"
#include "handlers.h"

// #include "xdg-shell.h"
#include "../include/wlr-layer-shell-unstable-v1.h"
#include <wayland-client.h>

#define TITLE "UwU"

struct wl_buffer *create_shm_buffer(struct client *client, int width, int height) {
	int size = width * height * 4;
	int stride = width * 4;

	char name[] = "/hyprsymbol-XXXX";
	size_t len = strlen(name);
	for (int i = len-4; i < 4; i++) {
		name[i] = (rand() % 10) + '0';
	}

	/* Opens a shared memory space using the created file */
	int fd = shm_open(name, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH);
	if (fd < 0) {
		return NULL;
	}

	shm_unlink(name);
	ftruncate(fd, size);
	
	client->pixels = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (client->pixels == NULL) {
		close(fd);
		return NULL;
	}
	struct wl_shm_pool *pool = wl_shm_create_pool(client->shm, fd, size);
	struct wl_buffer *buffer = wl_shm_pool_create_buffer(pool, 0, width, height, stride, WL_SHM_FORMAT_XRGB8888);

	wl_shm_pool_destroy(pool);
	close(fd);
	
	return buffer;
}

/**
 * Writes some data to the shared memory object for the buffer to render.
 */
static void draw(struct client *client) {
	memset(client->pixels, 0, 200 * 200 * 4);
}

int main() {
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

	/* Requests a wl_surface and convert it to a layered surface */
    client.surface = wl_compositor_create_surface(client.compositor);
    client.layer_surface = zwlr_layer_shell_v1_get_layer_surface(
			client.layer_shell,
		   	client.surface,
		   	NULL,
		   	ZWLR_LAYER_SHELL_V1_LAYER_TOP,
			TITLE
		);
	zwlr_layer_surface_v1_set_size(client.layer_surface, 200, 200);
	zwlr_layer_surface_v1_set_anchor(client.layer_surface, 
		ZWLR_LAYER_SURFACE_V1_ANCHOR_BOTTOM | ZWLR_LAYER_SURFACE_V1_ANCHOR_RIGHT);

    zwlr_layer_surface_v1_add_listener(client.layer_surface, &zwlr_layer_surface_listener, &client);
	/* Initial commit before surface attachment, as required */	
    wl_surface_commit(client.surface);

    while (wl_display_dispatch(client.display) != -1) { }

	/* Creates the buffer and attach it to the surface */
    client.buffer = create_shm_buffer(&client, 200, 200);
    if (client.buffer == NULL) {
    	return EXIT_FAILURE;
    }

	draw(&client);

	/* Ask for rendering */
	wl_surface_attach(client.surface, client.buffer, 0, 0);
	// wl_surface_damage(surface, 0, 0, 200, 200);
	wl_surface_commit(client.surface);

	while (wl_display_dispatch(client.display) != -1 && !client.configured) { }

	zwlr_layer_surface_v1_destroy(client.layer_surface);
	wl_surface_destroy(client.surface);
    wl_display_disconnect(client.display);
	return 0;
}
