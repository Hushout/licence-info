EXEC=analdesc2
CC=gcc
FLAGS=-c -ansi

all : $(EXEC)

$(EXEC) : analdesc2.o lex.yy.o
					$(CC) analdesc2.o lex.yy.o -o $(EXEC)

analdesc2.o : analdesc2.c
							$(CC) $(FLAGS) analdesc2.c

lex.yy.o : lex.yy.c
						$(CC) $(FLAGS) lex.yy.c

lex.yy.c :
					flex flex.l

cleanup :
				rm *o ~*

clean :
				rm *o ~* lex.yy.c $(EXEC)
