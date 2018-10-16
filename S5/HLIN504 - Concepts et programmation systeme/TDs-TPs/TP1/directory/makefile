CC = gcc
CFLAGS = -Wall -ansi -std=c99
SOURCES = directory.c
OBJ = $(SOURCES:.c=.o)
EXECUTABLE = directory

all : $(EXECUTABLE)

$(EXECUTABLE) : $(OBJ)
		$(CC) $(OBJ) -o $(EXECUTABLE)

$(OBJ) :
	$(CC) $(CFLAGS) $(SOURCES) -c

clean :
	rm $(OBJ)
	rm $(EXECUTABLE)
