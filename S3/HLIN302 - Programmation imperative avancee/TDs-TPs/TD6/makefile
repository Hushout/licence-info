CC = g++
CFLAGS = -W -Wall
SRCS = tableau-cellule.cpp cellule.cpp main-1.cpp
OBJS = $(SRCS:.cpp = .o)
BIN = rechDicoCell
EXT = *.o

all: $(OBJS)
	$(CC) -o $(BIN) $(OBJS)

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(EXT) $(BIN)

