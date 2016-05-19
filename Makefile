CC=g++
CFLAGS=-O2 -Wall -Wextra -Wpedantic

all:
	$(CC) -o brainfuck brainfuck.cpp $(CFLAGS)
