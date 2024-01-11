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
wlp4s0:
	sudo ./main $@
bili:
	sudo ./main wlp4s0 47.103.24.173
debug:
	sudo cgdb main
%:
	sudo ./main $@
clean:
	rm *.o



