CC = g++
CFLAGS = -W -Wall -ansi -pedantic
SRCS = outilsTab5.cpp main.cpp
OBJS = $(SRCS:.cpp = .o)
BIN = TP5
EXT = *.o

all: $(OBJS)
	clear; clear;
	$(CC) -o $(BIN) $(OBJS)

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(EXT) $(BIN)

