CC = gcc
CFLAGS = -Wall -ansi -std=c99
SOURCES = genproc1.c
OBJ = $(SOURCES:.c=.o)
EXECUTABLE = genproc1

all : $(EXECUTABLE)

$(EXECUTABLE) : $(OBJ)
		$(CC) $(OBJ) -o $(EXECUTABLE)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm $(OBJ)
	rm $(EXECUTABLE)
