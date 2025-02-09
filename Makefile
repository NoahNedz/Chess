CC=gcc
CFLAGS=-g


install:
	${CC} ${CFLAGS} src/chess.c src/display.c src/move.c src/pieces.c -o chess
