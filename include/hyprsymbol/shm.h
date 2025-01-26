#ifndef SHM_H
#define SHM_H

#include <stddef.h>

#include <hyprsymbol/hyprsymbol.h>

/**
 * @brief Create a buffer from a shared memory pool and assign it to the client.
 * @param client 
 * @param width 
 * @param height 
 * @return int
 */
int create_shm_buffer(struct client *client, int width, int height);

#endif /* !SHM_H */
