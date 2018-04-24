CC = g++
CFLAGS = -W -Wall
SRCS = tp3.cpp
OBJS = $(SRCS:.cc = .o)
BIN = tp3
EXT = *.o

all: $(OBJS)
	clear;
	clear;
	$(CC) $(OBJS) $(CFLAGS) -o $(BIN)

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(EXT) $(BIN)

