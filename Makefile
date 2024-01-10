CC = gcc

SRC = main.c
OBJ =main.o




CFLAGS=-g -Wall

LD_LIB = 

INCLUDE_LIB =

all: main
	sudo ./main


main:${OBJ}
	${CC} ${CFLAGS} $^ -o $@

%.o:%.c
	${CC} ${CFLAGS} -c $^ -o $@

debug:
	sudo cgdb main

clean:
	rm *.o



