CC=g++
CFLAGS=-std=gnu++11 -O2 -Wall -Wextra -Wpedantic

all:
	$(CC) -o brainfuck brainfuck.cpp $(CFLAGS)
