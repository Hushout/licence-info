CC = gcc
CFLAGS = -Wall -ansi -std=c99
SOURCES = alea.c es.c jeu.c
DEP = -lcrypt
OBJ = $(SOURCES:.c=.o)
EXECUTABLE = jeu

all : $(EXECUTABLE)

$(EXECUTABLE) : $(OBJ)
		$(CC) $(OBJ) -o $(EXECUTABLE)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm $(OBJ)
	rm $(EXECUTABLE)
