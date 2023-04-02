CC=gcc
CFLAGS=-Ig.

install:
	${CC} ${CFLAGS} src/chess.c src/board.c src/move.c src/pieces.c -o chess.o
