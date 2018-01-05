CC = g++
CFLAGS = -Wall
SRCS = main.cpp
OBJS = $(SRCS:.cpp = .o)
BIN = abr
EXT = *.o

all: $(OBJS)
	clear; clear;	
	$(CC) -o $(BIN) $(OBJS)

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(EXT) $(BIN)

