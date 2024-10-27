
#define _POSIX_C_SOURCE 200112L

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "globals.h"
#include "handlers.h"
#include "listeners.h"

// #include "xdg-shell.h"
#include "wlr-layer-shell-unstable-v1.h"
#include <wayland-client.h>

struct wl_buffer *create_shm_buffer(uint32_t **data, int width, int height) {
	int size = width * height * 4;
	int stride = width * 4;

	char name[] = "/hyprsymbol-XXXX";
	size_t len = strlen(name);
	for (int i = len-4; i < 4; i++) {
		name[i] = (rand() % 10) + '0';
	}

	/* Opens a shared memory space through using the created file */
	int fd = shm_open(name, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH);
	if (fd < 0) {
		return NULL;
	}

	shm_unlink(name);
	ftruncate(fd, size);
	
	*data = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	struct wl_shm_pool *pool = wl_shm_create_pool(glob_shm, fd, size);
	struct wl_buffer *buffer = wl_shm_pool_create_buffer(pool, 0, width, height, stride, WL_SHM_FORMAT_XRGB8888);

	wl_shm_pool_destroy(pool);
	close(fd);
	
	return buffer;
}

int main() {
    struct wl_display *display = wl_display_connect(NULL);
	if (display == NULL) {
		fprintf(stderr, "No display available");
		return 1;
	}
	
    /* Fetch the list of globals we are interested in */
    struct wl_registry *registry = wl_display_get_registry(display);
    wl_registry_add_listener(registry, &registry_listener, NULL);
    wl_display_roundtrip(display);

    if (glob_compositor == NULL || glob_shm == NULL || glob_zwlr_layer_shell == NULL) {
		fprintf(stderr, "compositor, shm or zwlr_layer_shell global(s) undefined");
    	return 1;
    }

	/* Requests a wl_surface and convert it to a toplevel window */
    surface = wl_compositor_create_surface(glob_compositor);
    struct zwlr_layer_surface_v1 *zwlr_layer_surface = 
	   	zwlr_layer_shell_v1_get_layer_surface(
		   	glob_zwlr_layer_shell,
		   	surface,
		   	NULL,
		   	ZWLR_LAYER_SHELL_V1_LAYER_TOP,
			"=UwU="
		);
	zwlr_layer_surface_v1_set_anchor(zwlr_layer_surface, 1 | 2 | 4 | 8);

    zwlr_layer_surface_v1_add_listener(zwlr_layer_surface, &zwlr_layer_surface_listener, NULL);
	/* Initial commit before surface attachment, as required */	
    wl_surface_commit(surface);

   	/* TODO: move this in a proper event handler */
    while (wl_display_dispatch(display) != -1 && !configured) { }

	/* Creates the buffer and attach it to the surface */
    buffer = create_shm_buffer(&pixels, 200, 200);
    if (buffer == NULL) {
		/* Cannot create buffer */
    	return 1;
    }

	/* Fills the buffer with something (just to see) */
	memset(pixels, 0, 200 * 200 * 4);
	// for (int y = 0; y < 200; ++y) {
	//   for (int x = 0; x < 200; ++x) {
	//     if ((x + y / 8 * 8) % 16 < 8) {
	//       pixels[y * 200 + x] = 0xFF666666;
	//     } else {
	//       pixels[y * 200 + x] = 0xFFEEEEEE;
	//     }
	//   }
	// }

	wl_surface_attach(surface, buffer, 0, 0);
	wl_surface_damage(surface, 0, 0, UINT32_MAX, UINT32_MAX);
	wl_surface_commit(surface);

	while (wl_display_dispatch(display) != -1) { }

	// xdg_toplevel_destroy(xdg_toplevel);
	// xdg_surface_destroy(xdg_surface);
	zwlr_layer_surface_v1_destroy(zwlr_layer_surface);
	wl_surface_destroy(surface);
    wl_display_disconnect(display);
	return 0;
}
