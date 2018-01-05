CC = g++
CFLAGS = -W -Wall
SRCS = Arbo.cpp
OBJS = $(SRCS:.cpp = .o)
BIN = arbo
EXT = *.o

all: $(OBJS)
	clear
	clear
	$(CC) -o $(BIN) $(OBJS)

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(EXT) $(BIN)

