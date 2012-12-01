#sudoku-solver makefile, by: Chris Jeakle (cjjeakle)

all: solver

solver: sudoku-solver.o sudoku-functions.o
	g++ sudoku-solver.o sudoku-functions.o -o solver
	
sudoku-solver.o:
	g++ sudoku-solver.cpp -c -O3 -Wall
	
sudoku-functions.o:
	g++ sudoku-functions.cpp -c -O3 -Wall
	
sudoku-solver.o sudoku-functions.o: sudoku_header.h

clean:
	rm -rf *o solver
