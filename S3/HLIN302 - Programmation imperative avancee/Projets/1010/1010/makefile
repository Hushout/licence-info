CC = g++
FLAGS = -W -Wall -g
LIB = -lncurses
SRCS = main.cpp matrice.cpp piece.cpp window.cpp grille.cpp tenten.cpp setdepiece.cpp score.cpp
OBJS = $(SRCS:.cpp = .o)
BIN = 1010
SUPR = *.o

$(BIN): $(OBJS)
	clear; clear;
	$(CC) $(FLAGS) $(OBJS) -o $(BIN) $(LIB)

%.o: %.cpp
	$(CC) $(FLAGS) -c $@ $<

clean:
	rm $(FLAGS)
