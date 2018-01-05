CC = g++
CFLAGS = -W -Wall
SRCS = fichierTP2.cpp progListeSC.cpp
OBJS = $(SRCS:.cpp = .o)
BIN = fichierTP2
EXT = *.o

all: $(OBJS)
	$(CC) -o $(BIN) $(OBJS)

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(EXT) $(BIN)

