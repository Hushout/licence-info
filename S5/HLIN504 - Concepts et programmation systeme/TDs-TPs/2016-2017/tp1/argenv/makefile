CC = gcc
CFLAGS = -Wall -ansi -std=c99
SOURCES = argenv.c
OBJ = $(SOURCES:.c=.o)
EXECUTABLE = argenv

all : $(EXECUTABLE)

$(EXECUTABLE) : $(OBJ)
		$(CC) $(OBJ) -o $(EXECUTABLE)

$(OBJ) :
	$(CC) $(CFLAGS) $(SOURCES) -c

clean :
	rm $(OBJ)
	rm $(EXECUTABLE)
