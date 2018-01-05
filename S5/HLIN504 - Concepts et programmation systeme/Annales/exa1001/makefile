CC = gcc
CFLAGS = -Wall -ansi -std=c99
SOURCES = tel.c
OBJ = $(SOURCES:.c=.o)
EXECUTABLE = tel

all : $(EXECUTABLE)

$(EXECUTABLE) : $(OBJ)
		$(CC) $(OBJ) -o $(EXECUTABLE)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm $(OBJ)
	rm $(EXECUTABLE)
