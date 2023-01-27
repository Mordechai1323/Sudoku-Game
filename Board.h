/**************************************************************************************
    Author: Mordechai Ben Shimon
    Creation date :  01/01/23
    Last modified date:  --
    Description :  Create board .
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