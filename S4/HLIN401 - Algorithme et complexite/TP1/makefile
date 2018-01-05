CC = g++
CFLAGS = -W -Wall
SRCS = Q1.cpp
OBJS = $(SRCS:.cpp = .o)
BIN = R1
EXT = *.o

all: $(OBJS)
	clear
	clear
	$(CC) -o $(BIN) $(OBJS)

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(EXT) $(BIN)

