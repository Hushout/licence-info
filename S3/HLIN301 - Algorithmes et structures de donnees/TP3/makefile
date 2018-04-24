CC = g++
CFLAGS = -Wall -ansi -pedantic
SRCS = fichierTP3.cpp progListeSC.cpp main.cpp
OBJS = $(SRCS:.cpp = .o)
BIN = TP3
EXT = *.o

all: $(OBJS)
	clear; clear;
	$(CC) -o $(BIN) $(OBJS)

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(EXT) $(BIN)

