#ifndef SHM_H
#define SHM_H

#include <stddef.h>

#include <hyprsymbol/hyprsymbol.h>

/**
 * Create a buffer from a shared memory pool and assign it to the client.
 */
int create_shm_buffer(struct client *client);

#endif /* !SHM_H */
