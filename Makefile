BIN=hyprsymbol

CC=gcc
CFLAGS=-Wall -Wextra -Wvla -std=c99 -Iinclude -g3
LDLIBS=`pkg-config --libs wayland-client`

SRC=lib/xdg-shell.c lib/wlr-layer-shell-unstable-v1.c \
	src/listeners.c src/handlers.c src/globals.c \
	src/main.c

OBJ_SRC=${SRC:.c=.o}

all: $(OBJ_SRC)
	$(CC) $(LDFLAGS) $(LDLIBS) $(OBJ_SRC) -o $(BIN)

clean:
	$(RM) $(BIN) 
	$(RM) $(OBJ_SRC) 
