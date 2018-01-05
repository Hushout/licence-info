CC = g++
CFLAGS = -W -Wall
SRCS = main.cpp AB.cpp Tas.cpp SortieLatex.cpp
OBJS = $(SRCS:.cpp = .o)
BIN = tas
EXT = *.o

all: $(OBJS)
	clear
	clear
	$(CC) -o $(BIN) $(OBJS)

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(EXT) $(BIN)

