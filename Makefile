BIN=hyprsymbol

CC=gcc
CFLAGS=-Wall -Wextra -Wvla -std=c99 -Iinclude -g3
LDLIBS=`pkg-config --libs wayland-client`

SRC=lib/xdg-shell.c \
	src/listeners.c src/handlers.c src/globals.c \
	src/main.c

OBJ_SRC=${SRC:.c=.o}

all: $(OBJ_SRC)
	$(CC) $(LDFLAGS) $(LDLIBS) $(OBJ_SRC) -o $(BIN)

protocols:
	wayland-scanner client-header protocols/xdg-shell.xml include/xdg-shell.h
	wayland-scanner private-code  protocols/xdg-shell.xml lib/xdg-shell.c

clean:
	$(RM) $(BIN) 
	$(RM) $(OBJ_SRC) 
