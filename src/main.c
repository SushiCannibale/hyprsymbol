#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
#include <wayland-util.h>
#include <wayland-client.h>
//#include <wayland-server.h>
//#include <wayland-client-protocol.h>
//#include <wayland-egl.h>
//#include <EGL/egl.h>

//#include <cairo/cairo.h>

/* Notre taff va être de dire au compositeur ce qu'il doit faire
** avec nos requests (ex. où placer nos fenêtres etc...)
*/
int main() {
	struct wl_display* display = wl_display_connect(NULL);
	if (!display) {
		fprintf(stderr, "Failed to connect to Wayland display\n");
		return 1;
	}

	fprintf(stdout, "Successfully connected to Wayland display\n");
	wl_display_disconnect(display);
	return 0;
}
