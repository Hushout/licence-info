CC = gcc
CFLAGS = -Wall -ansi -std=c99
SOURCES = parrot.c parrot_server.c
OBJ = $(SOURCES:.c=.o)
EXECUTABLE = parrot parrot_server

all : $(EXECUTABLE)

parrot : parrot.o
	$(CC) $< -o $@

parrot_server : parrot_server.o
	$(CC) $< -o $@	

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm $(OBJ)
	rm $(EXECUTABLE)
