CC=gcc
CFLAGS=-Wall -Wextra -Wvla -std=c99 -g3
LDLIBS=`pkg-config --libs wayland-client`

SRC=src/main.c
TESTS=
LIB=

BIN=main

OBJ_SRC=${SRC:.c=.o}

all: $(OBJ_SRC)
	$(CC) $(LDFLAGS) $(LDLIBS) $(OBJ_SRC) -o $(BIN)

clean:
	$(RM) $(BIN) $(OBJ_SRC)
