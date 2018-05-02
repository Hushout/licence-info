CC = gcc
FLAGS = -W -Wall

SRCS0 = main.c

BIN0 = addrinfo

INCLUDE = 

EXT = *.o *~

default: $(BIN0)

%.o: %.c
	$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

$(BIN0): $(SRCS0:%.c=%.o)
	$(CC) -o $@ $+

clean:
	rm -f $(EXT)

mrproper: clean
	rm -f $(BIN0)