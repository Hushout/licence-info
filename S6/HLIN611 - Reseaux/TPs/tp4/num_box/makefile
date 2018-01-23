CC = gcc
CFLAGS = -Wall -ansi -std=c99
SOURCES = num_box.c
OBJ = $(SOURCES:.c=.o)
EXECUTABLE = num_box

all : $(EXECUTABLE)

num_box : num_box.o
		$(CC) $< -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm $(OBJ)
	rm $(EXECUTABLE)
