CC = g++
CFLAGS = -W -Wall
SRCS = main.cpp ArbreBinaireRecherche.cpp SortieLatex.cpp
OBJS = $(SRCS:.cpp = .o)
BIN = abr
EXT = *.o

all: $(OBJS)
	clear
	clear
	$(CC) -o $(BIN) $(OBJS)

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(EXT) $(BIN)

