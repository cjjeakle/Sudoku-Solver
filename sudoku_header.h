//Sudoku Solver header file
//written by: Chris Jeakle (cjjeakle)

//an underscore was used between sudoku and header instead of a hyphen to prevent
//compiler warnings about whitespace and hanging tokens (the word header is treated
//as one when it comes after a hyphen)
#ifndef sudoku_header
#define sudoku_header


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

#endif //sudoku-header 

