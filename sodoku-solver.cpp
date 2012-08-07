//Sodoku Solver
//written by: Chris Jeakle (cjjeakle)

#include <iostream>

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
and can be determined by interger dividing row and col coordinates by 9.
  
  
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
	
	TEN is unique, it stores the solution for a square or a 0 if none is 
	found yet
*/



//Requires: a fully populated board, with any int value in the 9*9*10 array locations
//Modifies: N/A
//Effects: prints the sodoku board with all garanteed squares showing their 
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
//Modified: board
//Effects: takes a newly populated board and eliminates the givens as possibilities
//	for conflicting squares
void firstRun (int board[9][9][10]);

//Requires: a valid board
//Modifies: board
//Effects: finds all squares with one possible number as a solution, assigns that
//	single possibility as a solution to the square.
//	possibilities in the sub-board, row and col that match the solved num are removed
void solveSingletons (int board[9][9][10]);

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
			//at this point every number is a possibility
			for (int n = 0; n < 9; n++)
			{
				board [i][j][n] = 2;
			}
			
			//we assign a 1 to any location values that are garanteed true
			cin >> x;
			if (x != 0)
			{
				board [i][j][x] = 1;
				board [i][j][9] = x;
				
				for (int n = 0; n < 9; n++)
				{	if (x != n)
					{
						board [i][j][n] = 0;
					}
				}
			}
			
		}
	}
	firstRun (board);
	
	bool complete = false;
	int checker = 0;
	while (!complete && checker < 100000)
	{
		//iterate through solving step 5 times and check if complete, repeat 
		for (int i = 0; i < 5; i++)
		{
			solveSingletons (board);
			checker++;
		}
		complete = checkComplete(board);	
	}
	
	cout << checker <<endl;
	//print what sould be a solved board
	printBoard (board);
	return 0;
}


void printBoard (int board[9][9][10])
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			//if there is a solution for this square, print that
			if (board[i][j][9] != 0)
			{	
				cout << " " << board[i][j][9] <<" ";
			}
			//otherwise, print a question mark
			else
			{
				cout << " ? ";
			}
			//separate squares with a "|"
			if (j < 8)
			{
				cout << " | ";
			}
		}
		cout << endl;
		for (int j = 0; j < 9; j++)
		{
			cout << "---";
			if (j < 8)
			{ 
				cout << " | ";
			}
		}
		cout << endl;
	}
}
	

void eliminateSubBoard (int board[9][9][10], int basis, int row, int col)
{
	int subBoardRow = row/9;
	int subBoardCol = col/9;
	
	//navigate the rows
	for (int i = 0; i < 9; i++)
	{
		//navigate the cols
		for (int j = 0; j < 9; j++)
		{
			if ((i/9 == subBoardRow) && (j/9 == subBoardCol)\
			&& (i != row) && (j != col)) 
			{
				board[i][j][basis] = 0;
			}
		}
	}
}


void eliminateRow (int board[9][9][10], int basis, int row, int col)
{
	//navigate across the row
	for (int j = 0; j < 9; j++)
	{
		if (j != col)
		{
			board[row][j][basis] = 0;
		}
	}
}


void eliminateCol (int board[9][9][10], int basis, int row, int col)
{
	//navigate down the col
	for (int i = 0; i < 9; i++)
	{
		if (i != row) 
		{
			board[i][col][basis] = 0;
		}
	}
}

void firstRun (int board[9][9][10])
{
	//rows
	for (int i = 0; i< 9; i++)
	{	
		//cols
		for (int j = 0; j < 9; j++)
		{
			//if no solution for this square, iterate through possibilities
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
						possibleAns = n;
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


bool checkComplete (int board[9][9][10])
{
	//rows
	for (int i = 0; i< 9; i++)
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














	
