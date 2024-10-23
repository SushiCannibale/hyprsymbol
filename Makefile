CC=gcc
CFLAGS=-Wall -Wextra -Wvla -std=c99 -g3 `pkg-config --cflags gtk4`
LDLIBS=`pkg-config --libs gtk4`

SRC=src/main.c src/hyprsymbol.c
TESTS=
LIB=

BIN=main

OBJ_SRC=${SRC:.c=.o}

all: $(OBJ_SRC)
	$(CC) $(LDFLAGS) $(LDLIBS) $(OBJ_SRC) -o $(BIN)

clean:
	$(RM) $(BIN) $(OBJ_SRC)
