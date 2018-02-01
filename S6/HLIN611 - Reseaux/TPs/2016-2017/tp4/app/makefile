CC = gcc
CFLAGS = -Wall -ansi -std=c99
SOURCES = approlix.c apprifix.c
OBJ = $(SOURCES:.c=.o)
EXECUTABLE = approlix apprifix

all : $(EXECUTABLE)

approlix : approlix.o
	$(CC) $< -o $@

apprifix : apprifix.o
	$(CC) $< -o $@	

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm $(OBJ)
	rm $(EXECUTABLE)
