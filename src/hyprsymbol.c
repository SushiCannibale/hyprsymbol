#include <hyprsymbol/hyprsymbol.h>

#include <stdlib.h>

struct client *client_new(size_t width, size_t height) {
    struct client *client = calloc(1, sizeof(*client));
    client->width = width;
    client->height = height;
    return client;
}

void client_free(struct client *client) {
    free(client);
}
