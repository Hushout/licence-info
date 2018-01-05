CC = gcc
CFLAGS = -Wall -ansi -std=c99
SOURCES = erasthothenes_sieve.c
OBJ = $(SOURCES:.c=.o)
EXECUTABLE = erasthothenes_sieve

all : $(EXECUTABLE)

$(EXECUTABLE) : $(OBJ)
		$(CC) $(OBJ) -o $(EXECUTABLE)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm $(OBJ)
	rm $(EXECUTABLE)
