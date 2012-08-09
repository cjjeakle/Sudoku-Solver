//Sudoku Solver
//written by: Chris Jeakle (cjjeakle)

#include <iostream>


//credit goes to shuttle87 on this suggestion for color coding output
//http://stackoverflow.com/questions/9158150/colored-output-in-c
//THESE COLOR CODES ARE FOR MAC OS AND UBUNTU TERMINAL ONLY
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

using namespace std;

/*
how to imagine the data:
a 9x9 array of "squares", or a 3x3 array or sub-boards

the board is an array arranged as such:
 0,0 | 0,1 | 0,2...
 --- | --- | ---
 1,0 | 1,1 | 1,2...
 --- | --- | ---
 2,2 | 2,1 | 2,2...
  .     .     .
  .     .     .
  .     .     .
  
there are 9 sub-boards to consider, too (the nine 3x3 squares that can't contain repeats)
These are arranged as:
				    0 1 2
				    - - -
				  0|1 2 3
				  1|4 5 6
				  2|7 8 9
a square's sub-board coordinates can be determined by interger dividing row and col coordinates by 3.
  
  
inside each of the 81 "squares" are 9 variables representing the 9 possible answers to that square:
 
			  one  |  two   | three
			  ---  |  ---   |  ---
			  four |  five  |  six
			  ---  |  ---   |  ---
			 seven | eight  |  nine
			 	  ---
			 	  TEN
 
	each is assigned a 0, 1, or 2
	0 = eliminated possibility
	1 = part of the origional board or garanteed true
	2 = possibility (more than one answer possible for this location)
	
	TEN (array reference 9) is unique, it stores the solution for a square 
	or a 0 if none is found yet
*/



//Requires: a fully populated board, with any int value in the 9*9*10 array locations
//Modifies: N/A
//Effects: prints the sudoku board with all garanteed squares showing their 
//	solution and all others showing a "?" 
void printBoard (int board[9][9][10]);

//Requires: basis be a garanteed correct answer for row and col, board is populated
//Modifies: board
//Effects: takes a row and col, finds its equilivent sub-board, and removes
//	"basis" as a possibility for all squares in this sub-board except 
//	that with the row and col given
void eliminateSubBoard (int board[9][9][10], int basis, int row, int col);

//Requires: basis be a garanteed correct answer for row and col, board is populated
//Modifies: board
//Effects: takes a row and removes "basis" as a possibility for all squares except
//	the square in "col"
void eliminateRow (int board[9][9][10], int basis, int row, int col);

//Requires: basis be a garanteed correct answer for row and col, board is populated
//Modifies: board
//Effects: takes a col and removes "basis" as a possibility for all squares except
//	the square in "row"
void eliminateCol (int board[9][9][10], int basis, int row, int col);

//Requires: a board that has just been populated by the user
//Modifies: board
//Effects: takes a newly populated board and eliminates the givens as possibilities
//	for conflicting squares
void clearMatches (int board[9][9][10]);

//Requires: a valid board
//Modifies: board
//Effects: finds all squares with one possible number as a solution, assigns that
//	single possibility as a solution to the square.
//	possibilities in the sub-board, row and col that match the solved num are removed
void solveSingletons (int board[9][9][10]);

//Requires: a valid board
//Modifies: board
//Effects: finds numbers in a row or col that have multiple possibilities
//	but are the only possible solution for a specific number, then makes that the answer
//	ex: 4, 7,and 9 are possible in a square, but it is the only 9 possible in its col,
// 	this means the square is a 9.
//	This function is also used to call onlyInARow and onlyInACol.
void findLoneSolutions (int board[9][9][10]);

//Requires: a valid board
//Modifies: board
//Effects: finds squares in a row that are the only possible solution for a number
//	but have multiple allowable solutions
void rowLoneSolutions (int board [9][9][10], int row, int col);

//Requires: a valid board
//Modifies: board
//Effects: finds squares in a col that are the only possible solution for a number
//	but have multiple allowable solutions
void colLoneSolutions (int board [9][9][10], int row, int col);

//Requires: a valid board
//Modifies: board
//Effects: finds numbers in a sub-board that are the only possible in one square of
//	the sub-board, denotes that as the solution to its given square
void subBoardLoneSolution (int board [9][9][10]);

//Requires: a valid board
//Modifies: board
//Effects: finds any possibility that only exists in one col of a given sub-board,
//	eliminates possibilities using this information
void onlyInACol (int board[9][9][10], int row, int col);

//Requires: a valid board
//Modifies: board
//Effects: finds any possibility that only exists in one row of a given sub-board,
//	eliminates possibilities using this information
void onlyInARow (int board[9][9][10], int row, int col);

//Requires: a valid board
//Modifies: N/A
//Effects: returns false if any squares still need solutions, returns true otherwise
bool checkComplete (int board[9][9][10]);

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
	
	//populate givens
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


void printBoard (int board[9][9][10])
{
	//print the board
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			//if there is a solution for this square, print that
			if (board[i][j][9] != 0)
			{	
				cout << GREEN << " " << board[i][j][9] <<RESET <<" ";
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
					cout << " location:" << n+1 <<" value: " <<board[i][j][n] <<endl;
				}
				cout << endl <<endl <<endl;
			}
		}
	}
}
	

void eliminateSubBoard (int board[9][9][10], int basis, int row, int col)
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


void eliminateRow (int board[9][9][10], int basis, int row, int col)
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


void eliminateCol (int board[9][9][10], int basis, int row, int col)
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


void clearMatches (int board[9][9][10])
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
				eliminateSubBoard (board, board [i][j][9], i, j);
				eliminateRow (board, board [i][j][9], i, j);
				eliminateCol (board, board [i][j][9], i, j);
			}
		}
	}
}


void solveSingletons (int board[9][9][10])
{
	//rows
	for (int i = 0; i< 9; i++)
	{	
		//cols
		for (int j = 0; j < 9; j++)
		{
			//if no solution for this square, iterate through possibilities
			if (board[i][j][9] == 0)
			{
				int numPossible = 0;
				int possibleAns = 0;
				for (int n = 0; n < 9; n++)
				{
					if (board[i][j][n] == 2)
					{
						numPossible++;
						//n+1 translates the array location
						//into the number it represents
						possibleAns = (n + 1);
					}
				}
				//if there is only one possibility, that is the solution
				if (numPossible == 1)
				{
					board [i][j][possibleAns] = 1;
					board [i][j][9] = possibleAns;
					eliminateSubBoard (board, possibleAns, i, j);
					eliminateRow (board, possibleAns, i, j);
					eliminateCol (board, possibleAns, i, j);
				}
			}
		}
	}
}


void findLoneSolutions (int board[9][9][10])
{
	//rows
	for (int i = 0; i< 9; i++)
	{	
		//cols
		for (int j = 0; j < 9; j++)
		{
			rowLoneSolutions (board, i, j);
			colLoneSolutions (board, i, j);
			onlyInARow (board, i, j);
			onlyInACol (board, i, j);
		}
	}
}


void rowLoneSolutions (int board [9][9][10], int row, int col)
{
	//iterate possible numbers
	for (int n = 0; n < 9; n++)
	{
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
			}
		}
	}
}

void colLoneSolutions (int board [9][9][10], int row, int col)
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
			}
		}
	}	
}


void subBoardLoneSolution (int board [9][9][10])
{
	for (int subBoardRow = 0; subBoardRow < 3; subBoardRow++)
	{
		for (int subBoardCol = 0; subBoardCol < 3; subBoardCol++)
		{
			//iterate number being checked
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
						//we are in the correct sub-board for 
						//comparison and n is possible 
						//for the square in question
						if (i/3 == subBoardRow && j/3 ==\
						subBoardCol && board[i][j][n] == 2)
						{
							possibilities++;
							row = i;
							col = j;
						}
					}
				}
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
					eliminateSubBoard (board, n+1, row, col);
					eliminateRow (board, n+1, row, col);
					eliminateCol (board, n+1, row, col);
				}
			}
		}
	}
}
					

void onlyInACol (int board[9][9][10], int row, int col)
{
	int subBoardRow = row/3;
	int subBoardCol = col/3;
	int outsideCol = 0;
	
	for (int n = 0; n <9; n++)
	{
		//if a number is possible for a square
		if (board[row][col][n] == 2)
		{
			//rows
			for (int i = 0; i < 9; i++)
			{
				//cols
				for (int j = 0; j < 9; j++)
				{
					//if another row in that sub-board contains
					//the number
					if ((i/3 == subBoardRow) && (j != col) &&\
					(j/3 == subBoardCol) && (board[i][j][n] == 2))
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
			//eliminate that number as a possibility outside this sub-
			//board but inside this col
			for (int i = 0; i < 9; i++)
			{
				if (i/3 != subBoardRow)
				{
					board[i][col][n] = 0;
				}
			}
		}
	} 
					
}

void onlyInARow (int board[9][9][10], int row, int col)
{
	int subBoardRow = row/3;
	int subBoardCol = col/3;
	int outsideRow = 0;
	
	for (int n = 0; n <9; n++)
	{
		//if a number is possible for a square
		if (board[row][col][n] == 2)
		{
			//rows
			for (int i = 0; i < 9; i++)
			{
				//cols
				for (int j = 0; j < 9; j++)
				{
					//if another col in that sub-board contains
					//the number, iterate the counter
					if ((j/3 == subBoardCol) && (i != row) &&\
					(i/3 == subBoardRow) && (board[i][j][n] == 2))
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
			//eliminate that number as a possibility outside this sub-
			//board but inside this row
			for (int j = 0; j < 9; j++)
			{
				if (j/3 != subBoardCol)
				{
					board[row][j][n] = 0;
				}
			}
		}
	} 			
}


bool checkComplete (int board[9][9][10])
{
	//rows
	for (int i = 0; i < 9; i++)
	{	
		//cols
		for (int j = 0; j < 9; j++)
		{
			//if a square lacks a solution, the board is incomplete
			if (board[i][j][9] == 0)
			{
				return false;
			}
		}
	}
	return true;
}














	
