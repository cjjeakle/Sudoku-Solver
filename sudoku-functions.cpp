//Sudoku Solver function declarations
//written by: Chris Jeakle (cjjeakle)

#include "sudoku_header.h"

using namespace std;


void printBoard (vector<vector<vector<int> > >  &board)
{
	//print the board
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			//if there is a solution for this square, print that
			if (board[i][j][9] != 0)
			{	
				cout << GREEN << " " << board[i][j][9] 
					<<RESET <<" ";
			}
			//otherwise, print a question mark
			else
			{
				cout << " ? ";
			}
			//separate squares with a "|"
			if (j < 8)
			{
				if (j % 3 == 2)
				{
					cout << BLUE;
				}
				cout << " | ";
				if (j % 3 == 2)
				{
					cout << RESET;
				}
			}
		}
		cout << endl;
		
		//formatting
		for (int j = 0; j < 9; j++)
		{
			if (i < 8)
			{
				if (i % 3 == 2)
				{
					cout << BLUE;
				}
				cout << "---";
				if (i % 3 == 2)
				{
					cout << RESET;
				}
				if (j < 8)
				{ 
					if (j % 3 == 2)
					{
						cout << BLUE;
					}
					
					cout << " | ";
					
					if (j % 3 == 2)
					{
						cout << RESET;
					}
				}
			}
		}
		cout << endl;
	}
	//print any unsolved square coordinates and their possible solutions
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (board[i][j][9] == 0)
			{
				cout << i+1 << " " << j+1 <<endl;
				for (int n = 0; n < 10; n++)
				{
					cout << " location:" << n+1 <<" value: " 
					<<board[i][j][n] <<endl;
				}
				cout << endl <<endl <<endl;
			}
		}
	}
}
	

void eliminateSubBoard (vector<vector<vector<int> > >  &board, int basis,
	int row, int col)
{
	int subBoardRow = row/3;
	int subBoardCol = col/3;
	
	//navigate the rows
	for (int i = 0; i < 9; i++)
	{
		//navigate the cols
		for (int j = 0; j < 9; j++)
		{
			if ((board [i][j][9] == 0) && (i/3 == subBoardRow)\
			&& (j/3 == subBoardCol) && (i != row) && (j != col)) 
			{
				board[i][j][(basis - 1)] = 0;
			}
		}
	}
}


void eliminateRow (vector<vector<vector<int> > >  &board, int basis,
	int row, int col)
{
	//navigate across the row
	for (int j = 0; j < 9; j++)
	{
		if ((board [row][j][9] == 0) && (j != col))
		{
			board[row][j][(basis - 1)] = 0;
		}
	}
}


void eliminateCol (vector<vector<vector<int> > >  &board, int basis, int row, 
	int col)
{
	//navigate down the col
	for (int i = 0; i < 9; i++)
	{
		if ((board [i][col][9] == 0) && (i != row)) 
		{
			board[i][col][(basis - 1)] = 0;
		}
	}
}


void clearMatches (vector<vector<vector<int> > >  &board)
{
	//rows
	for (int i = 0; i < 9; i++)
	{	
		//cols
		for (int j = 0; j < 9; j++)
		{
			//delete any conflicts with the givens
			if (board[i][j][9] != 0)
			{
				eliminateSubBoard(board, board [i][j][9], i, j);
				eliminateRow (board, board [i][j][9], i, j);
				eliminateCol (board, board [i][j][9], i, j);
			}
		}
	}
}


void solveSingletons (vector<vector<vector<int> > >  &board, bool &change)
{
	//rows
	for (int i = 0; i< 9; i++)
	{	
		//cols
		for (int j = 0; j < 9; j++)
		{
			//if no solution for this square, check possibilities
			if (board[i][j][9] == 0)
			{
				int numPossible = 0;
				int possibleAns = 0;
				for (int n = 0; n < 9; n++)
				{
					if (board[i][j][n] == 2)
					{
						numPossible++;
						//n+1 translates the array loc
						//into the number it represents
						possibleAns = (n + 1);
					}
				}
				//if there is only one possibility, that is sol
				if (numPossible == 1)
				{
					board [i][j][possibleAns] = 1;
					board [i][j][9] = possibleAns;
					eliminateSubBoard(board,possibleAns,i,j);
					eliminateRow (board, possibleAns, i, j);
					eliminateCol (board, possibleAns, i, j);
					change = true;
				}
			}
		}
	}
}


void findLoneSolutions (vector<vector<vector<int> > >  &board, bool &change)
{
	//rows
	for (int i = 0; i< 9; i++)
	{	
		//cols
		for (int j = 0; j < 9; j++)
		{
			rowLoneSolutions (board, i, j, change);
			colLoneSolutions (board, i, j, change);
			onlyInARow (board, i, j, change);
			onlyInACol (board, i, j, change);
		}
	}
}


void rowLoneSolutions (vector<vector<vector<int> > >  &board, int row, int col,
	bool &change)
{
	//iterate possible numbers
	for (int n = 0; n < 9; n++)
	{
		//if the number is possible in the given row and col
		if (board[row][col][n] == 2)
		{
			int alternatives = 0;
			//navigate the cols
			for (int j = 0; j < 9; j++)
			{
				if ((board [row][j][9] == 0) && (j != col) &&\
				(board[row][j][n] == 2))
				{
					alternatives++;
				}
			}	
			//if a number is a possible in the given location and 
			//nowhere else in the row, then it is that square's sol
			if (alternatives == 0 && (board[row][col][n] == 2))
			{
				board[row][col][9] = n+1;
				board[row][col][n] = 1;
				for (int x = 0; x < 9; x++)
				{
					if (x != n)
					{
						board[row][col][x] = 0;
					}
				}
				eliminateSubBoard (board, n+1, row, col);
				eliminateRow (board, n+1, row, col);
				eliminateCol (board, n+1, row, col);
				change = true;
			}
		}
	}
}


void colLoneSolutions (vector<vector<vector<int> > >  &board, 
	int row, int col, bool &change)
{
	//iterate possible numbers
	for (int n = 0; n < 9; n++)
	{
		if (board[row][col][n] == 2)
		{
			int alternatives = 0;
			//navigate the rows
			for (int i = 0; i < 9; i++)
			{
				if ((board [i][col][9] == 0) && (i != row) &&\
				(board[i][col][n] == 2))
				{
					alternatives++;
				}
			}
			//if a number is a possible in the given location and 
			//nowhere else in the col, then it is that square's sol
			if ((alternatives == 0) && (board[row][col][n] == 2))
			{
				board[row][col][9] = n+1;
				board[row][col][n] = 1;
				for (int x = 0; x < 9; x++)
				{
					if (x != n)
					{
						board[row][col][x] = 0;
					}
				}
				eliminateSubBoard (board, n+1, row, col);
				eliminateRow (board, n+1, row, col);
				eliminateCol (board, n+1, row, col);
				change = true;
			}
		}
	}	
}


void subBoardLoneSolution (vector<vector<vector<int> > >  &board, bool &change)
{
	//we navigate the 9 sub-boards
	for (int subBoardRow = 0; subBoardRow < 3; subBoardRow++)
	{
		for (int subBoardCol = 0; subBoardCol < 3; subBoardCol++)
		{
			//iterate the number being checked
			for (int n = 0; n < 9; n++)
			{
				int possibilities = 0;
				int row = 0;
				int col = 0;
				//rows
				for (int i = 0; i < 9; i++)
				{
					//cols
					for (int j = 0; j < 9; j++)
					{
						//if we are in the correct 
						//sub-board for comparison and
						//n is possible for the square
						//in question
						if (i/3 == subBoardRow && j/3 \
						== subBoardCol && \
						board[i][j][n] == 2)
						{
							possibilities++;
							row = i;
							col = j;
						}
					}
				}
				//if a number is possible in only one location,
				//it is that location's solution
				if (possibilities == 1)
				{
					board [row][col][9] = n+1;
					board [row][col][n] = 1;
					for (int x = 0; x < 9; x++)
					{
						if (x != n)
						{
							board[row][col][x] = 0;
						}
					}
					eliminateSubBoard(board, n+1, row, col);
					eliminateRow (board, n+1, row, col);
					eliminateCol (board, n+1, row, col);
					change = true;
				}
			}
		}
	}
}
					

void onlyInACol (vector<vector<vector<int> > >  &board, int row, int col,
	bool &change)
{
	int subBoardRow = row/3;
	int subBoardCol = col/3;
	int outsideCol = 0;
	
	//iterate through numbers
	for (int n = 0; n <9; n++)
	{
		//if a number is possible for the given square
		if (board[row][col][n] == 2)
		{
			//rows
			for (int i = 0; i < 9; i++)
			{
				//cols
				for (int j = 0; j < 9; j++)
				{
					//if another row in that sub-board
					//contains the number
					if ((i/3 == subBoardRow) && (j != col) \
					&& (j/3 == subBoardCol) && \
					(board[i][j][n] == 2))
					{
						outsideCol++;
					}
				}
			}
		}
		//if the current number "n" is only in this col, remove it as a 
		//possibility for for this col in other sub-boards
		if (outsideCol == 0 && board[row][col][n] == 2)
		{
			//eliminate that number as a possibility outside this 
			//sub-board but inside this col
			for (int i = 0; i < 9; i++)
			{
				if (i/3 != subBoardRow)
				{
					board[i][col][n] = 0;
				}
			}
			change = true;
		}
	} 
					
}


void onlyInARow (vector<vector<vector<int> > >  &board, int row, int col,
	bool &change)
{
	int subBoardRow = row/3;
	int subBoardCol = col/3;
	int outsideRow = 0;
	
	//iterate through numbers
	for (int n = 0; n <9; n++)
	{
		//if a number is possible for the given square
		if (board[row][col][n] == 2)
		{
			//rows
			for (int i = 0; i < 9; i++)
			{
				//cols
				for (int j = 0; j < 9; j++)
				{
					//if another col in that sub-board
					//contains the number, iterate the
					//counter
					if ((j/3 == subBoardCol) && (i != row) \
					&& (i/3 == subBoardRow) && \
					(board[i][j][n] == 2))
					{
						outsideRow++;
					}
				}
			}
		}
		//if the current number "n" is only in this row, remove it as a 
		//possibility for for this row in other sub-boards
		if (outsideRow == 0 && board[row][col][n] == 2)
		{
			//eliminate that number as a possibility outside this 
			//sub-board but inside this row
			for (int j = 0; j < 9; j++)
			{
				if (j/3 != subBoardCol)
				{
					board[row][j][n] = 0;
				}
			}
			change = true;
		}
	} 			
}

inline bool valid (vector<vector<vector<int> > >  &board)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (board[i][i][9] == 0)
			{
				bool anyPossible = false;
				for (int n = 0; n < 9; n++)
				{
					if (board[i][j][n])
					{
						anyPossible = true;
					}
				}
				if (!anyPossible)
				{
					return false;
				}
			}
		}
	}
	return true;
}

inline bool solution (vector<vector<vector<int> > >  &board)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (board[i][i][9] == 0)
			{
				return false;
			}
		}
	}
	return true;
}

backtrackingCall (vector<vector<vector<int> > >  &board)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (baord[i][j][9] != 0)
			{
				//if this square is solved,
				//dont guess it
				continue;
			}
			for (int n = 0;n < 9 && incomplete;n++)
			{
				if (board[i][j][n])
				{
					backtrackingSol (board,
					incomplete, board, i, j, n);
				}
			}
		}
	}
}

void backtrackingSol (vector<vector<vector<int> > >  board, bool &incomplete
	vector<vector<vector<int> > >  &sol, int row, int col, int guess)
{
	//attempt the guess
	board [row][col][9] = guess + 1;
	board [row][col][guess] = 1;
	for (int x = 0; x < 9; x++)
	{
		if (x != n)
		{
			board[row][col][x] = 0;
		}
	}
	eliminateSubBoard(board, guess + 1, row, col);
	eliminateRow (board, guess + 1, row, col);
	eliminateCol (board, guess + 1, row, col);
	
	//check if the guess kept the board valid
	if (valid(board))
	{
		if (solution(board))
		{
			sol.swap(board);
			incomplete = false;
			return;
		}
		else
		{
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
			
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					if (baord[i][j][9] != 0)
					{
						//if this square is solved,
						//dont guess it
						continue;
					}
					for (int n = 0;n < 9 && incomplete;n++)
					{
						if (board[i][j][n])
						{
							backtrackingSol (board,
							incomplete, sol, i,j,n);
						}
					}
				}
			}
		}
	}
}








