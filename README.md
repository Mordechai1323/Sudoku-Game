# Sudoku Game
This project was written as part of a final project for the course Advanced Programming in the C language(full assignment details [here](https://github.com/Mordechai1323/Sudoku-Game/blob/a77cd7d94576945d2bfc47044bee0d944d3e1774/Sudoku%20project.pdf)).

# Description
Sudoku is a logic-based, combinatorial number-placement puzzle. The objective of the game is to fill a 9x9 grid with digits so that each column, each row, and each of the nine 3x3 subgrids that compose the grid contain all of the digits from 1 to 9. The puzzle setter provides a partially completed grid, which for a well-posed puzzle has a single solution.

# Overview
The software asks the user how many players there will be and then creates a linked list of active players. For each player, the program defines a game board randomly which contains between 8 and 21 full slots. After creating the list, the program defines an array of pointers that point to the cells in the list, in order to sort it using the MergeSort algorithm. The primary sort criterion is the amount of filled slots on the player's board (from minimum to maximum). If there are two or more players with the same number of filled slots, the secondary sort criterion is their name in ascending lexicographic order. At the end of the sorting, the array of pointers will contain the players according to the sorting order specified above.

We will build a tree of players from the sorted array and then we will go through the tree in InOrder. For each player, we will do the following actions:

- We will check if there are places on the board that have only one option that can be filled legally. If so, we will update the board and then return whether the board is full or if the board has reached an illegal state or we have not yet finished filling the board.

- If the answer is an invalid board, the player exits the game by deleting him from the list of active players and placing a NULL pointer on him on the tree.

- If we have a board that is full, we will transfer the player to the list of winners and put a NULL value to the pointer.

- If he has not yet finished, we will allow him to choose one of the options in the slot with the minimum number of options. After receiving the option from the user, the player's board and matrix must be updated accordingly.

At the end, the list of winners and their boards will be printed.

# Built with
C language
