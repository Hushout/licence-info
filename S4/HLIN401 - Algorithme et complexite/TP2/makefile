CC = g++
CFLAGS = -W -Wall
SRCS = SolutionsFonctionMysterieuses.cpp fonctionMysterieuses.o
OBJS = $(SRCS:.cpp = .o)
BIN = test
EXT = *.o

all: $(OBJS)
	clear
	clear
	$(CC) -o $(BIN) $(OBJS)

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(EXT) $(BIN)

