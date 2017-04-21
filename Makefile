SHELL = /bin/sh
FLAGS =-g  -Wall
CC = g++

all: 2P2C 2P3C dynpipe 

dynpipe:    DynPipe.cpp
	$(CC) $(FLAGS) -o $@ DynPipe.cpp

2P2C:    TwoPipesTwoChildren.cpp
	$(CC) $(FLAGS) -o $@ TwoPipesTwoChildren.cpp

2P3C:	TwoPipesThreeChildren.cpp
	$(CC) $(FLAGS) -o $@ TwoPipesThreeChildren.cpp
clean:
	rm 2P2C 2P3C dynpipe
