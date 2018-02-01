CC = gcc
CFLAGS = -Wall -ansi -std=c99
SOURCES = src/tcp_client.c src/tcp_server.c
EXECUTABLE = tcp_client tcp_server

all : $(EXECUTABLE)

tcp_client : obj/tcp_client.o
	$(CC) $< -o $@

tcp_server : obj/tcp_server.o
	$(CC) $< -o $@

obj/%.o : src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm client_files/*
	rm obj/*
	rm $(EXECUTABLE)
