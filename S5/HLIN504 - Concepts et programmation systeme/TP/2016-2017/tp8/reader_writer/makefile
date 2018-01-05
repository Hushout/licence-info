CC = gcc
CFLAGS = -Wall -ansi -std=c99
SOURCES = reader.c writer.c
OBJ = $(SOURCES:.c=.o)
EXECUTABLE = reader writer

all : $(EXECUTABLE)

reader : reader.o
	$(CC) $< -o $@

writer : writer.o
	$(CC) $< -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm $(OBJ)
	rm $(EXECUTABLE)
