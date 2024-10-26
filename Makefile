CC=gcc
CFLAGS=-Wall -Wextra -Wvla -std=c99 -Iinclude -g3
LDLIBS=`pkg-config --libs wayland-client`

SRC=include/wayland-client.c src/main.c
TESTS=
LIB=

BIN=main

OBJ_SRC=${SRC:.c=.o}

all: $(OBJ_SRC)
	$(CC) -c include/wayland-client.c
	$(CC) $(LDFLAGS) $(LDLIBS) $(OBJ_SRC) -o $(BIN)


scan:
	wayland-scanner client-header protocols/wayland.xml include/wayland-client.h
	wayland-scanner private-code protocols/wayland.xml include/wayland-client.c

clean:
	$(RM) $(BIN) $(OBJ_SRC) include/wayland-client.h include/wayland-client.c
