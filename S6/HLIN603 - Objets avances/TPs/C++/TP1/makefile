CC = g++
CFLAGS = -W -Wall
SRCS = Strophe.cpp Vers.cpp main.cpp
OBJS = $(SRCS:.cpp = .o)
BIN = TP1
EXT = *.o

all: $(OBJS)
	clear;
	$(CC) -o $(BIN) $(OBJS)

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(EXT) $(BIN)

