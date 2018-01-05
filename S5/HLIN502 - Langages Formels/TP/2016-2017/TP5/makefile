CC=gcc
CFLAGS=-g -ansi -Wall -std=c99



testTP5 : testTP5.o tp5_implantation.o
	$(CC) $(CFLAGS) -o $@ $+

testTP5.o : testTP5.c  tp5_implantation.h tp5_interface.h 
	$(CC) $(CFLAGS) -c $<

tp5_implantation.o : tp5_implantation.c tp5_interface.h  tp5_implantation.h
	$(CC) $(CFLAGS) -c $<

propre: 
	/bin/rm -f *.o

toutpropre: propre
	/bin/rm -f testTP5
