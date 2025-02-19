#ifndef SHM_H
#define SHM_H

#include <stddef.h>

#include <hyprsymbol/hyprsymbol.h>

extern const struct wl_shm_listener wl_shm_listener;

void wl_shm_format_handler
(
	void *data,
	struct wl_shm *wl_shm,
	uint32_t format
);

/**
 * @brief Creates the memory space that will be shared with the server.
 */
int create_shm_pool(struct client *client);

/**
 * @brief Creates a buffer from the pool
 */
int create_shm_buffer(struct client *client);

#endif /* !SHM_H */
