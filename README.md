Sudoku-Solver
=============

A c++ project that solves sudoku puzzles

* The program can now solve any Sudoku puzzle with relatively high efficency<br>
  (there probably exist worst-case puzzles that will take awhile)

How it works:
* Input a sudoku row by row (using 0's for any blank spaces) into the program 
* -> Be careful what you type! Although typing "20" instead of '2' '0' will not break the program,<br> 
  it will reject that input and render the puzzle unsolvable (or it will result in too few inputs)
* -> Unlimited newlines and whitespace are permissable but at least one space must separate each square
* -> <h4>It is recommended to use redirected input from pre-prepared puzzle text files (like the test files)</h4>
* The program computes legal solutions for the puzzle's squares and prints either a finished or partially completed board
* If a square's solution cannot be found, its coordinates (in a 1-9 format) and the possibilities left for it are printed below the board<br>
  -> This is a hold-over from previous versions and will be removed in an update (all puzzles should be solvable now)

Changes to make:

* investigate further refinements to algorithm to improve speed (especially on BFS for backtracking)
