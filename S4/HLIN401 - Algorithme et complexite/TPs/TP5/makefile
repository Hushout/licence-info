CC = g++
CFLAGS = -W -Wall
SRCS = AB.cpp SortieLatex.cpp
OBJS = $(SRCS:.cpp = .o)
BIN = AB
EXT = *.o

all: $(OBJS)
	clear
	clear
	$(CC) -o $(BIN) $(OBJS)

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(EXT) $(BIN)

