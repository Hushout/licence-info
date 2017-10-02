CC = g++
CFLAGS = -W -Wall
SRCS = JDV.cpp JDV-main.cpp population.cpp option.cpp tabOptions.cpp cellule.cpp
OBJS = $(SRCS:.cpp = .o)
BIN = JDV
EXT = *.o

all: $(OBJS)
	clear; clear;
	$(CC) -o $(BIN) $(OBJS)

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(EXT) $(BIN)

