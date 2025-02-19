#include <hyprsymbol/hyprsymbol.h>
#include <hyprsymbol/shm.h>

#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

#include <wayland-client-protocol.h>
#include <hyprsymbol/utils.h>

const struct wl_shm_listener wl_shm_listener = {
    .format = wl_shm_format_handler
};

void wl_shm_format_handler
(
	UNUSED void *data,
	UNUSED struct wl_shm *wl_shm,
	UNUSED uint32_t format
) {
	/* Hints on which formats are available */
}

int create_shm_pool(struct client *client) {
	size_t size = client->width * client->height * 4;
	/* Opens an anonymous file that lives in RAM */
	int fd = memfd_create("hyprsymbol", 0);
	ftruncate(fd, size);

	client->pool_data = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	client->shm_pool = wl_shm_create_pool(client->wl_shm, fd, size);
	return 0;
}

int create_shm_buffer(struct client *client) {
	client->shm_buffer = wl_shm_pool_create_buffer(
		client->shm_pool, 
		0, 
		client->width, 
		client->height,
		client->width * 4,
		WL_SHM_FORMAT_ARGB8888
	);
	memset(client->pool_data, 0xFF, client->width * client->height * 4);
	return 0;
}
