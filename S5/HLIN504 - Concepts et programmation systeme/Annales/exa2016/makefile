CC = gcc
CFLAGS = -Wall -ansi -std=c99
SOURCES = tree_size.c count.c
OBJ = $(SOURCES:.c=.o)
EXECUTABLE = tree_size count

all : $(EXECUTABLE)

tree_size : tree_size.o
		$(CC) $< -o $@

count : count.o
		$(CC) $< -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm $(OBJ)
	rm $(EXECUTABLE)
