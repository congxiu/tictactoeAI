CC=c++
CFLAGS=-Wall -g -std=c++11
#CFLAGS=-Wall -g -std=c++1z

TicTacToe.o : TicTacToe.cpp TicTacToe.h
	${CC} ${CFLAGS} -c TicTacToe.cpp

main.o : main.cpp TicTacToe.h
	${CC} ${CFLAGS} -c main.cpp

game : main.o TicTacToe.o
	${CC} ${CFLAGS} main.o TicTacToe.o -o game
