Sudoku-Solver
=============

A c++ project intended to solve sudoku puzzles

* The program can now solve "hard" puzzles from websodoku.com, the program encounters difficulty with "Evil" difficulty

How it works:
* Input a sudoku row by row (using 0's for any blank spaces) into the program 
* -> Be careful what you type! Although typing "20" instead of '2' '0' will not break the program, it will reject that input and render the puzzle unsolvable (or it will result in too few inputs)
* -> Unlimited newlines and whitespace are permissable but at least one space must separate each square
* -> Entire puzzles can be pasted at once if one wishes
* The program computes legal solutions for the puzzle's squares and prints either a finished or partially completed board
* If a square's solution cannot be found, its coordinates (in a 1-9 format) and the possibilities left for it are printed below the board

Changes to make:

* investigate more complex sudoku strategy for solving puzzles of the highest difficulty

