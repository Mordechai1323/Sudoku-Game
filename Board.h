/**************************************************************************************
    Author: Mordechai Ben Shimon
    Creation date :  21/01/23
    Description : This file contains functions that generate the initial board of a Sudoku game randomly.
    The main function CreateSudokuBoard initializes all the cells on the board to -1, and creates a random board by using a linked list with all possible squares on the board.
    The function generates a random number, N, between 8 and 21 and performs this operation N times.
    It also generates a random number, K, between 1 and the size of the list (initially 81, but decreases as cells are removed).
    The function reaches cell K in the list and takes the slot position (X, Y) from it.
    Delete the cell from the list and places a random number in the cell that respects the possible value for this cell in the Sudoku game.
    The function uses random number generation to select a valid value for the particular slot by creating an array of valid values for that slot,
    then it picks an index from it and the value at that index is placed in the board.
***************************************************************************************/

#ifndef __BOARD_H__
#define __BOARD_H__

#define SUDOKU_SIZE 9

typedef struct SlotLocation SlotLocation_t;

typedef struct SlotLocationlistManeger SlotLocationlistManeger_t;


/**
 * @brief generates a random Sudoku board and stores it in a 2D array. It returns an error code indicating success or failure.
 *
 * @param board: The Sudoku board that will be filled with values
 *
 * @return An error code indicating the success or failure of the operation
 */
Errors CreateSudokuBoard(short board[][SUDOKU_SIZE]);

Errors CreateSoltLocationLinkedList(SlotLocationlistManeger_t* maneger, short board[][SUDOKU_SIZE]);

SlotLocation_t* CreateNewItem(int x, int y);

/**
 * @brief Adds an item to the end of a slot location linked list

 * @param maneger: The slot location list manager
 * @param item: The item to add to the linked list
 *
 * @return An error code indicating the success or failure of the operation
 */
Errors AddToEndSlotLocationList(SlotLocationlistManeger_t* maneger, SlotLocation_t* item);

/**
 * @brief is a function that randomly places a set of values on a sudoku board by selecting available slots and filling them with possible values.
 * 
 * @param maneger:  a pointer to a SlotLocationlistManeger_t struct containing a linked list of available slots
 * @param board: a 2D array of short integers representing the sudoku board
 * 
 * @return an Errors enum value indicating success or failure
 */
Errors CreateRandomBoard(SlotLocationlistManeger_t* maneger, short board[][SUDOKU_SIZE]);

void DestroySlotLocationList(SlotLocation_t* head);







#endif /*__BOARD_H__*/