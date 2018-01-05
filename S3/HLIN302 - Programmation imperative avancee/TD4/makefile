CC = g++
CFLAGS = -W -Wall
SRCS = cellule.cpp population-vivante-v2.cpp option.cpp tabOptions.cpp JDV0-bis.cpp JDV0-main.cpp
OBJS = $(SRCS:.cpp = .o)
BIN = JDV0
EXT = *.o

all: $(OBJS)
	$(CC) -o $(BIN) $(OBJS)

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(EXT) $(BIN)

