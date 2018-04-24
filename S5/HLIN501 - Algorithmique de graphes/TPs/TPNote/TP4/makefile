CC = g++
CFLAGS = -W -Wall
SRCS = tp4.cc Affichage.cc
OBJS = $(SRCS:.cc = .o)
BIN = tp4
EXT = *.o

all: $(OBJS)
	clear;
	clear;
	$(CC) $(OBJS) $(CFLAGS) -o $(BIN)

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(EXT) $(BIN)

