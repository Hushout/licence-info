CC = gcc
CFLAGS = -Wall -std=c99
SOURCES = sieve_exec.c fsieve.c
OBJ = $(SOURCES:.c=.o)
EXECUTABLE = sieve_exec fsieve

all : sieve_exec fsieve

sieve_exec : sieve_exec.o
	$(CC) $(CFLAGS) -o $@ $<

fsieve : fsieve.o
	$(CC) $(CFLAGS) -o $@ $<

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm $(OBJ)
	rm $(EXECUTABLE)
