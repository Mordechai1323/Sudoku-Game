/**************************************************************************************
    Author: Mordechai Ben Shimon
    Creation date :  01/01/23
    Last modified date:  --
    Description : solver .
***************************************************************************************/

#ifndef __SOLVER_H__
#define __SOLVER_H__

#define SUDOKU_SIZE 9

typedef struct Array Array_t;

typedef struct PossibleValue PossibleValue_t;


/**
 * @brief The function receives a Sudoku board represented by a matrix of cells. The function will generate a 2D array of pointers 
 *  to the Array type in the size of a board Sudoku where each cell (Array) contains all the possible digits for the cell.
 *
 * @param sudokuBoard:  a 2D array of short integers representing the sudoku board.
 *
 * @returna 2D array of pointers to the Array type in the size of a board Sudoku where each cell (Array) contains all the possible digits for the cell.
 */
Array_t*** PossibleDigits(short sudokuBoard[][SUDOKU_SIZE]);

/**
 *@brief Determines the possible values that can be placed in a given slot of a sudoku board.
 *
 * @param sudokuBoard:  a 2D array of short integers representing the sudoku board
 * @param x:            the x-coordinate of the slot
 * @param y:            the y-coordinate of the slot
 * @return              an Array_t struct containing the possible values for the slot or NULL if an error occurs
 */
Array_t* CheckPossibleValuesForSlot(short sudokuBoard[][SUDOKU_SIZE], int x, int y);

void DestroyPossibleDigits(Array_t*** arrayPossibleDigits);

/**
 * @brief This function looks for slots that can be filled by only one digit legally and if found update the cell 
 *  in the board with the only possible value and update the options for other cells in the board.
 *
 * @param board: Two-dimensional array storing the sudoku board.
 * @param possibilities: 2D array of pointers to the Array type storing the possibilities for each cell in the board.
 * @param x: Pointer to an integer storing the x-coordinate of the cell with the smallest number of possibilities.
 * @param y: Pointer to an integer storing the y-coordinate of the cell with the smallest number of possibilities.
 *
 * @return An Errors value indicates the success or failure of the operation. 
    ERR_FINISH_SUCCESS if the Sudoku board is solved, 
    ERR_FINISH_FAILURE if the solution is illegal,or 
    ERR_NOT_FINISH if the board is not solved yet. 
    If the board is not solved yet, store the coordinates of the cell with the smallest number of possibilities in 'x' and 'y'.
 */
Errors OneStage(short board[][SUDOKU_SIZE], Array_t*** possibilities, int* x, int* y);

void UpdatingPossibleDigits(short board[][SUDOKU_SIZE], Array_t*** possibilities, int x, int y);

/**
 *@brief This function checks if a given value at a given position on a Sudoku board is legal
 *
 * @param board:  a 2D array of short integers representing the sudoku board
 * @param  x:     the x-coordinate of the position
 * @param  y:     the y-coordinate of the position

 * @return returns: ERR_OK if the value is legal, ERR_ILLEGAL if it is not
 */
Errors CheckingLegalityFboard(short board[][SUDOKU_SIZE], int x, int y);

/**
 *@brief This function checks if a Sudoku board is full or not.
 *
 * @param sudokuBoard:  a 2D array of short integers representing the sudoku board

 * @return 1 if the board is full, 0 if it is not
 */
int IsBoardFull(short board[][SUDOKU_SIZE]);

/**
 * @brief This function gets a number from the user and enters it onto a Sudoku board and checks whether the values are valid.
 *
 * @param sudokuBoard:  a 2D array of short integers representing the sudoku board
   @param possibilities: 2D array of pointers to the Array type storing the possibilities for each cell in the board.
 * @param x: Pointer to an integer storing the x-coordinate of the cell with the smallest number of possibilities.
 * @param y: Pointer to an integer storing the y-coordinate of the cell with the smallest number of possibilities.
 * 
 * @return ERR_FINISH_SUCCESS if the Sudoku board is solved, 
 *         ERR_FINISH_FAILURE if the solution is illegal,or 
 *         ERR_OK if the entered values are valid. 
 */
Errors EnterNumberFromUser(short board[][SUDOKU_SIZE], Array_t*** possibilities, char* name, int x, int y);



#endif /*__SOLVER_H__ */