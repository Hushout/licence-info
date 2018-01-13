CC = g++
CFLAGS = -Wall -ansi -std=c++11
SOURCES = array_functions.cc Affichage.cc tp2.cc
OBJ = $(SOURCES:.cc=.o)
EXECUTABLE = tp2

all : $(EXECUTABLE)
	rm $(OBJ)

$(EXECUTABLE) : $(OBJ)
		$(CC) $(OBJ) -o $(EXECUTABLE)

$(OBJ) :
	$(CC) $(CFLAGS) $(SOURCES) -c

clean :
	rm $(OBJ)
	rm $(EXECUTABLE)
