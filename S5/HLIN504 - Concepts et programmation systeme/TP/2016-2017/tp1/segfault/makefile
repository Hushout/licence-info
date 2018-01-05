CC = gcc
CFLAGS = -Wall -ansi -std=c99
SOURCES = segfault.c
OBJ = $(SOURCES:.c=.o)
EXECUTABLE = segfault

all : $(EXECUTABLE)

$(EXECUTABLE) : $(OBJ)
		$(CC) $(OBJ) -g -o $(EXECUTABLE)

$(OBJ) :
	$(CC) $(CFLAGS) $(SOURCES) -g  -c

clean :
	rm $(OBJ)
	rm $(EXECUTABLE)
