CC = g++
CFLAGS = -W -Wall
HEADER = includes
SRCS1 = srcs/testCasier6.cc
SRCS2 = srcs/testTriBulles.cpp
EXE1 = testCasier6
EXE2 = testTriBulles
EXT = *.o

all: $(EXE1) $(EXE2) 

$(EXE1): $(SRCS1)
	clear
	clear
	$(CC) $(SRCS1) -o $(EXE1) -I $(HEADER) $(CFLAGS) 

$(EXE2): $(SRCS2)
	clear
	$(CC) $(SRCS2) -o $(EXE2) -I $(HEADER) $(CFLAGS) 

clean:
	rm -f $(EXT) $(BIN)