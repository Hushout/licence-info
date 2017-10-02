CC = gcc
CFLAGS = -Wall -ansi -std=c99
SOURCES = factorial.c
OBJ = $(SOURCES:.c=.o)
EXECUTABLE = factorial

all : $(EXECUTABLE)

$(EXECUTABLE) : $(OBJ)
		$(CC) $(OBJ) -o $(EXECUTABLE)

$(OBJ) :
	$(CC) $(CFLAGS) $(SOURCES) -c

clean :
	rm $(OBJ)
	rm $(EXECUTABLE)
