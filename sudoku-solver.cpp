//Sudoku Solver
//written by: Chris Jeakle (cjjeakle)
//compile this document with the sudoku-functions.cpp doucment
//ex: g++ sudoku-solver.cpp sudoku-functions.cpp

#include <iostream>
#include "sudoku_header.h"

using namespace std;

int main()
{
	int board[9][9][10];
	
	
	//initilize the board
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			board [i][j][9] = 0;
			//at this point every number is a possibility
			for (int n = 0; n < 9; n++)
			{
				board [i][j][n] = 2;
			}
		}
	}
	
	//populate givens from user input
	for (int i = 0; i < 9; i++)
	{
		cout << "input the data for row " << i+1 <<" , separate with spaces and use 0 to denote blanks" <<endl;
		int x = 0;
		
		for (int j = 0; j < 9; j++)
		{
			//we assign a 1 to any location values that are garanteed true
			cin >> x;
			if (x != 0)
			{
				board [i][j][(x - 1)] = 1;
				board [i][j][9] = x;
				
				for (int n = 0; n < 9; n++)
				{	
					if ((x - 1) != n)
					{
						board [i][j][n] = 0;
					}
				}
			}
		}
	}
	clearMatches (board);
	
	//the solving loop
	bool complete = false;
	int checker = 0;
	while (!complete && checker < 10000)
	{
		solveSingletons (board);
		findLoneSolutions(board);
		subBoardLoneSolution (board);
		complete = checkComplete(board);
		checker++;
	}
	
	
	cout << checker <<endl;
	//print what will hopefully be a solved board or a partially solved board
	//and coordinates for all unsolved possibilities
	printBoard (board);
	return 0;
}

