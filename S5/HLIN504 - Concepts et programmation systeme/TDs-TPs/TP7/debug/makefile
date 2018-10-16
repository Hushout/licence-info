CC = gcc
CFLAGS = -Wall -ansi -std=c99
SOURCES = debug.c test_debug.c
OBJ = $(SOURCES:.c=.o)
EXECUTABLE = debug

all : $(EXECUTABLE)

$(EXECUTABLE) : $(OBJ)
		$(CC) $(OBJ) -o $(EXECUTABLE)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm $(OBJ)
	rm $(EXECUTABLE)
