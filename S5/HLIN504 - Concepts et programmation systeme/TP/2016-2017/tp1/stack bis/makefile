CC = gcc
CFLAGS = -Wall -ansi -std=c99
SOURCES = stack_bis.c
OBJ = $(SOURCES:.c=.o)
EXECUTABLE = stack_bis

all : $(EXECUTABLE)

$(EXECUTABLE) : $(OBJ)
		$(CC) $(OBJ) -o $(EXECUTABLE)

$(OBJ) :
	$(CC) $(CFLAGS) $(SOURCES) -c

clean :
	rm $(OBJ)
	rm $(EXECUTABLE)
