CC = g++
CFLAGS = -W -Wall
SRCS = TriOutilsSimples.cpp 
OBJS = $(SRCS:.cpp = .o)
BIN = tri
EXT = *.o

all: $(OBJS)
	clear
	clear
	$(CC) -o $(BIN) $(OBJS)

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(EXT) $(BIN)

