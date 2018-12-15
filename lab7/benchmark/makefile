FLAGS= -std=c++11 -pedantic -Werror -Wno-sign-compare -Wno-long-long -lm -O2
CC=g++

LINK=-lm

all: matrix main clear

main: main.cpp
	$(CC) $(FLAGS) -o benchmark main.cpp TMatrix.o

matrix: TMatrix.cpp
	$(CC) $(FLAGS) -c TMatrix.cpp

clear:
	rm *.o
