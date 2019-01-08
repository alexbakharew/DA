FLAGS= -std=c++11 -pedantic -Werror -Wno-sign-compare -Wno-long-long -lm -O2
CC=g++

LINK=-lm

all: equation main

main: main.cpp
	$(CC) $(FLAGS) -o lab8 main.cpp equation.o

equation: equation.cpp
	$(CC) $(FLAGS) -c equation.cpp

