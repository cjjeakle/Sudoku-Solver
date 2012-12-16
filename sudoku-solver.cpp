//Sudoku Solver
//written by: Chris Jeakle (cjjeakle)

#include "sudoku_header.h"

int main()
{
	//intitlize the board, at this point everything is a possibility
	vector<int> temp (10, 2);
	temp[9] = 0;
	vector<vector<int> > temp2 (9, temp);
	vector<vector<vector<int> > > board (9, temp2);

	//populate givens from user input
	for (int i = 0; i < 9; i++)
	{
		cout << "input the data for row " << i+1 
		<<" , separate with spaces and use 0 to denote blanks" <<endl;
		int x = 0;

		for (int j = 0; j < 9; j++)
		{
			//we assign a 1 to any location values that are for sure
			cin >> x;
			if (x > 0 && x < 10)
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
	
	//The solving loop
	//If no change is made during the previous iteration of the loop, then
	//the puzzle is either solved or cannot be further solved
	bool change = true;
	int checker = 0;
	while (change && checker < 10)
	{
		change = false;
		solveSingletons (board, change);
		findLoneSolutions(board, change);
		subBoardLoneSolution (board, change);
		checker++;
	}
	
	//use backtracking for harder puzzles
	backtrackingSol (board);
	
	//print what will hopefully be a solved board
	printBoard (board);
	return 0;
}

