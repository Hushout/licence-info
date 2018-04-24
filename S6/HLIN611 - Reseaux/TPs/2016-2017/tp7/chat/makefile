CC = gcc
CFLAGS = -Wall -ansi -std=c99
SOURCES = src/client.c src/server.c
EXECUTABLE = client server

all : $(EXECUTABLE)

client : obj/client.o
	$(CC) $< -o $@

server : obj/server.o
	$(CC) $< -o $@

obj/%.o : src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm obj/*
	rm $(EXECUTABLE)
