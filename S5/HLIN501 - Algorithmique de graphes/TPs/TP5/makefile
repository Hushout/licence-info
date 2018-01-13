CC = g++
CFLAGS = -W -Wall
SRCS = tp5.cc
OBJS = $(SRCS:.cc = .o)
BIN = tp5
EXT = *.o

all: $(OBJS)
	clear;
	clear;
	$(CC) $(OBJS) $(CFLAGS) -o $(BIN)

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(EXT) $(BIN)

