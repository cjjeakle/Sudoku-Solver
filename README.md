Sudoku-Web-Solver
=================

A Wt based c++ project to create a simple website for solving a Sudoku  (based on my previous Sudoku solver)

* The site currently solves any Sudoku up to "Hard" on websudoku.net

How it works:
* Input your puzzle into the text boxes<br>
--> Only one character per box and only 1-9
* The program outputs the board's solution below the solve button<br>
--> if there are any '?' in the solution, those are squares that could not be solved (>1 solution)

Needed improvments:
* An improved solving strategy that leverages the "x-wing" to solve the most advanced puzzles
