# Makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

checkers: main.c checkers.c bit_functions.c checkers.h bit_functions.h
	$(CC) $(CFLAGS) -o checkers main.c checkers.c bit_functions.c

clean:
	rm -f checkers

run: checkers
	./checkers
