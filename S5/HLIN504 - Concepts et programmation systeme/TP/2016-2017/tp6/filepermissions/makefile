CC = gcc
CFLAGS = -Wall -ansi -std=c99
SOURCES = filepermissions.c
OBJ = $(SOURCES:.c=.o)
EXECUTABLE = filepermissions

all : $(EXECUTABLE)

$(EXECUTABLE) : $(OBJ)
		$(CC) $(OBJ) -o $(EXECUTABLE)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm $(OBJ)
	rm $(EXECUTABLE)
