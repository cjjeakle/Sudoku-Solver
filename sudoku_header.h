//Sudoku Solver header file
//written by: Chris Jeakle (cjjeakle)

//an underscore was used between sudoku and header instead of a hyphen to 
//prevent compiler warnings about whitespace and hanging tokens (the word header 
//is treated as one when it comes after a hyphen)
#ifndef sudoku_header
#define sudoku_header

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

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
  
there are 9 sub-boards to consider (the 9 3x3 squares that can't have repeats)
These are arranged as:
				    0 1 2
				    - - -
				  0|1 2 3
				  1|4 5 6
				  2|7 8 9
a square's sub-board coordinates can be determined by interger dividing row 
and col coordinates by 3.
  
  
inside each of the 81 "squares" are 9 variables representing the 9 possible 
answers to that square:
 
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



//Requires: a fully populated board, with any int value in the 9*9*10 array locs
//Modifies: N/A
//Effects: prints the sudoku board with all garanteed squares showing their 
//	solution and all others showing a "?" 
void printBoard (vector<vector<vector<int> > >  &board);

//Requires: basis be a garanteed correct answer for row and col, board is valid
//Modifies: board
//Effects: takes a row and col, finds its equilivent sub-board, and removes
//	"basis" as a possibility for all squares in this sub-board except 
//	that with the row and col given
void eliminateSubBoard (vector<vector<vector<int> > >  &board, int basis, 
	int row, int col);

//Requires: basis be a garanteed correct answer for row and col, board is valid
//Modifies: board
//Effects: takes a row and removes "basis" as a possibility for all squares 
//	except the square in "col"
void eliminateRow (vector<vector<vector<int> > >  &board, int basis, int row, 
	int col);

//Requires: basis be a garanteed correct answer for row and col, board is valid
//Modifies: board
//Effects: takes a col and removes "basis" as a possibility for all squares 
//	except the square in "row"
void eliminateCol (vector<vector<vector<int> > >  &board, int basis, int row, 
	int col);

//Requires: a board that has just been populated by the user
//Modifies: board
//Effects: takes a newly populated board and eliminates the givens as
//	possibilities for conflicting squares.
void clearMatches (vector<vector<vector<int> > >  &board);

//Requires: a valid board
//Modifies: board, change
//Effects: finds all squares with one possible number as a solution, assigns 
//	that single possibility as a solution to the square.
//	possibilities in the sub-board, row and col that match the solved num 
//	are removed. 
//	If a change is made, change = true.
void solveSingletons (vector<vector<vector<int> > >  &board, bool &change);

//Requires: a valid board
//Modifies: board, change
//Effects: finds numbers in a row or col that have multiple possibilities
//	but are the only possible solution for a specific number, then makes 
//	that the answer ex: 4, 7,and 9 are possible in a square, but it is the 
// 	only 9 possible in its col, this means the square is a 9.
//	This function is also used to call onlyInARow and onlyInACol.
//	If a change is made, change = true.
void findLoneSolutions (vector<vector<vector<int> > >  &board, bool &change);

//Requires: a valid board
//Modifies: board, change
//Effects: finds squares in a row that are the only possible solution for a 
//	number but have multiple allowable solutions. If a change is made, 
//	change = true.
void rowLoneSolutions (vector<vector<vector<int> > >  &board, int row, int col,
	bool &change);

//Requires: a valid board
//Modifies: board, change
//Effects: finds squares in a col that are the only possible solution for a 
//	number but have multiple allowable solutions. If a change is made,
//	change = true.
void colLoneSolutions (vector<vector<vector<int> > >  &board, int row, int col,
	bool &change);

//Requires: a valid board
//Modifies: board, change
//Effects: finds numbers in a sub-board that are the only possible in one square 
//	of the sub-board, denotes that as the solution to its given square.
//	If a change is made, change = true.
void subBoardLoneSolution (vector<vector<vector<int> > >  &board, 
	bool &change);

//Requires: a valid board
//Modifies: board, change
//Effects: finds any possibility that only exists in one col of a given
//	sub-board, eliminates possibilities using this information.
//	If a change is made, change = true.
void onlyInACol (vector<vector<vector<int> > >  &board, int row, int col, 
	bool &change);

//Requires: a valid board
//Modifies: board, change
//Effects: finds any possibility that only exists in one row of a given
//	sub-board, eliminates possibilities using this information.
//	If a change is made, change = true.
void onlyInARow (vector<vector<vector<int> > >  &board, int row, int col, 
	bool &change);

inline bool valid (vector<vector<vector<int> > >  &board);

inline bool solution (vector<vector<vector<int> > >  &board);

void backtrackingSol (vector<vector<vector<int> > >  &board);

#endif //sudoku-header 

