#include <hyprsymbol/hyprsymbol.h>
#include <hyprsymbol/shm.h>

#include <errno.h>
#include <stdio.h>
#include <sys/mman.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

#include <wayland-client-protocol.h>

static void randname(char *buf)
{
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	long r = ts.tv_nsec;
	for (int i = 0; i < 6; i++) {
		buf[i] = 'A'+(r&15)+(r&16)*2;
		r >>= 5;
	}
}

static int create_shm_file(void)
{
	int retries = 100;
	do {
		char name[] = "/wl_shm-XXXXXX";
		randname(name + sizeof(name) - 7);
		--retries;
		int fd = shm_open(name, O_RDWR | O_CREAT | O_EXCL, 0600);
		if (fd >= 0) {
			shm_unlink(name);
			return fd;
		}
	} while (retries > 0 && errno == EEXIST);
	return -1;
}

static int allocate_shm_file(size_t size)
{
	int fd = create_shm_file();
	if (fd < 0)
		return -1;
	int ret;
	do {
		ret = ftruncate(fd, size);
	} while (ret < 0 && errno == EINTR);
	if (ret < 0) {
		close(fd);
		return -1;
	}
	return fd;
}

int create_shm_buffer(struct client *client) {
	size_t stride = client->width * 4; // ARGB - 4 bytes per pixel
	size_t pool_size = stride * client->height;
	
	int fd = allocate_shm_file(pool_size);
	if (fd < 0) {
		return 1;
	}
	client->shm_data = mmap(NULL, pool_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (client->shm_data == MAP_FAILED) {
		fprintf(stderr, "mmap failed !");
		close(fd);
		return 1;
	}
	struct wl_shm_pool *shm_pool = wl_shm_create_pool(client->shm, fd, pool_size);
	client->shm_buffer = wl_shm_pool_create_buffer(shm_pool, 0, client->width, client->height, stride, WL_SHM_FORMAT_ARGB8888);
	wl_shm_pool_destroy(shm_pool);
	return 0;
}
