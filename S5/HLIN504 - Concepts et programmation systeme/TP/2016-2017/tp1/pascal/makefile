CC = gcc
CFLAGS = -Wall -ansi -std=c99
SOURCES = pascal.c
OBJ = $(SOURCES:.c=.o)
EXECUTABLE = pascal

all : $(EXECUTABLE)

$(EXECUTABLE) : $(OBJ)
		$(CC) $(OBJ) -o $(EXECUTABLE)

$(OBJ) :
	$(CC) $(CFLAGS) $(SOURCES) -c

clean :
	rm $(OBJ)
	rm $(EXECUTABLE)
