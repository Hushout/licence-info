CC = g++
CFLAGS = -W -Wall
SRCS = population-vivante-v3.cpp tableau-cellule.cpp cellule.cpp main.cpp
OBJS = $(SRCS:.cpp = .o)
BIN = population-main
EXT = *.o

all: $(OBJS)
	$(CC) -o $(BIN) $(OBJS)

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(EXT) $(BIN)

