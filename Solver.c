/**************************************************************************************
    Author: Mordechai Ben Shimon
    Creation date :  21/01/23
    Description :  This file deals with the functionality to fill in and verify the validity of the numbers in the sudoku board.
    The "PossibleDigits" function creates a 2D array of pointers that holds the possible values for each slot on the board.
    The "CheckPossibleValuesForSlot" function, which receives a board and an X, Y position on the board, and
    returns an array of possible values for that particular slot.
    The "on stage" function looks for a position on the board that has only one valid value and updates the position with that value.
    In case no such position is found, the function returns the coordinates of the position with the smallest possible values on the board in the output parameters, X and Y.
    The "UpdatingPossibleDigits" function updates the valid digits for the row, column, and 3x3 square containing the most recently entered number.
    The "CheckingLegalityFboard" function verifies whether the value entered in the board is legal according to the sudoku rules.
    The "IsBoardFull" function checks if the board is completely full and returns 1 if true or 0 if false.
    Finally, the "EnterNumberFromUser" function gives the user the ability to enter a number for a specific cell on the board.
***************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "Errors.h"
#include "Solver.h"
#include "Board.h"
#include "Ui.h"


struct Array
{
    short* arr;
    unsigned short size;
};

struct PossibleValue {
    int value;
    bool isPossible;
};


Array_t*** PossibleDigits(short sudokuBoard[][SUDOKU_SIZE])
{
    Array_t*** arrayPossibleValue = NULL;
    int* arr = NULL, numPossibleValues = 0;

    arrayPossibleValue = (Array_t***)malloc(SUDOKU_SIZE * sizeof(Array_t**));
    if (!arrayPossibleValue)
    {
        return NULL;
    }

    for (size_t x = 0; x < SUDOKU_SIZE; x++)
    {
        arrayPossibleValue[x] = (Array_t**)malloc(SUDOKU_SIZE * sizeof(Array_t*));
        if (!arrayPossibleValue[x])
        {
            free(arrayPossibleValue);
            return NULL;
        }

        for (size_t y = 0; y < SUDOKU_SIZE; y++)
        {
            arrayPossibleValue[x][y] = CheckPossibleValuesForSlot(sudokuBoard, x, y);
            if (!arrayPossibleValue[x][y])
            {
                return NULL;
            }
        }
    }

    return arrayPossibleValue;
}

Array_t* CheckPossibleValuesForSlot(short sudokuBoard[][SUDOKU_SIZE], int x, int y)
{
    PossibleValue_t possibleValues[9] = { {1,1 }, { 2,1 }, { 3,1 }, { 4,1 }, { 5,1 }, { 6,1 }, { 7, 1 }, { 8,1 }, { 9,1 } };
    Array_t* arrayPossibleValue = NULL;
    int newX = 0, newY = 0;

    arrayPossibleValue = (Array_t*)malloc(sizeof(Array_t));
    if (!arrayPossibleValue)
    {
        return NULL;
    }

    arrayPossibleValue->size = 0;
    if (sudokuBoard[x][y] != -1)
    {
        arrayPossibleValue->arr = NULL;
    }
    else
    {
        newX = (x / 3) * 3;
        newY = (y / 3) * 3;

        for (size_t i = 0; i < SUDOKU_SIZE; i++)
        {
            if (sudokuBoard[x][i] != -1 )
            {
                possibleValues[(sudokuBoard[x][i] - 1)].isPossible = 0;
            }
            if (sudokuBoard[i][y] != -1 && i != x)
            {
                possibleValues[(sudokuBoard[i][y] - 1)].isPossible = 0;
            }
            if (i == 3 || i == 6)
            {
                ++newX, newY = (y / 3) * 3;
            }
            if (sudokuBoard[newX][newY] != -1  && (newX != x && newY != y))
            {
                possibleValues[(sudokuBoard[newX][newY] - 1)].isPossible = 0;
            }
            ++newY;
        }

        for (size_t i = 0; i < 9; i++)
        {
            if (possibleValues[i].isPossible)
            {
                ++arrayPossibleValue->size;
            }
        }
        arrayPossibleValue->arr = (short*)malloc(arrayPossibleValue->size * sizeof(short));
        if (!arrayPossibleValue->arr)
        {
            return NULL;
        }
        for (size_t i = 0,j = 0; i < 9; i++)
        {
            if (possibleValues[i].isPossible)
            {
                arrayPossibleValue->arr[j] = possibleValues[i].value;
                ++j;
            }
        }
    }

    return arrayPossibleValue;
}

void DestroyPossibleDigits(Array_t*** arrayPossibleDigits)
{
    for (size_t x = 0; x < SUDOKU_SIZE; x++)
    {
        for (size_t y = 0; y < SUDOKU_SIZE; y++)
        {
            free(arrayPossibleDigits[x][y]->arr);
            free(arrayPossibleDigits[x][y]);
        }
        free(arrayPossibleDigits[x]);
    }
    free(arrayPossibleDigits);
}

Errors OneStage(short board[][SUDOKU_SIZE], Array_t*** possibilities, int* x, int* y)
{
    int min = 9;
    for (size_t i = 0; i < SUDOKU_SIZE; i++)
    {
        for (size_t j = 0; j < SUDOKU_SIZE; j++)
        {
            // If a cell with a single possibility is found, update the cell in the board with the single possible value
            if (possibilities[i][j]->size == 1)
            {
                // Update the cell in the board with the single possible value
                board[i][j] = possibilities[i][j]->arr[0];
                free(possibilities[i][j]->arr);
                possibilities[i][j]->arr = NULL;
                possibilities[i][j]->size = 0;

                // Update the possibilities for other cells in the board
                UpdatingPossibleDigits(board, possibilities, i, j);

                // Check the legality of the updated board
                if (CheckingLegalityFboard(board,i,j) == ERR_ILLEGAL)
                {
                    // If the updated board is illegal, return ERR_FINISH_FAILURE
                    return ERR_FINISH_FAILURE;
                }
                // If the updated board is full, return ERR_FINISH_SUCCESS
                if (IsBoardFull(board))
                {
                    return ERR_FINISH_SUCCESS;
                }
            }

            // If no cell with a single possibility is found, search for the cell with the smallest number of possibilities
            else
            {
                if (board[i][j] == -1 && possibilities[i][j]->size < min)
                {
                    // Store the coordinates of the cell with the smallest number of possibilities
                    min = possibilities[i][j]->size;
                    *x = i, * y = j;
                }
            }
        }
    }
    

    return ERR_NOT_FINISH;
}

void UpdatingPossibleDigits(short board[][SUDOKU_SIZE], Array_t*** possibilities, int x, int y)
{
    int newX, newY;
    newX = (x / 3) * 3;
    newY = (y / 3) * 3;

    // Search the board array for cells that have not been filled in yet
    for (size_t i = 0; i < SUDOKU_SIZE; i++)
    {
        if (board[x][i] == -1)
        {
            free(possibilities[x][i]);
            possibilities[x][i] = CheckPossibleValuesForSlot(board, x, i);
        }
        if (board[i][y] == -1 && i != x)
        {
            free(possibilities[i][y]);
            possibilities[i][y] = CheckPossibleValuesForSlot(board, i, y);
        }
        if (i == 3 || i == 6)
        {
            ++newX, newY = (y / 3) * 3;
        }
        if (board[newX][newY] == -1 && (newX != x && newY != y))
        {
            free(possibilities[newX][newY]);
            possibilities[newX][newY] = CheckPossibleValuesForSlot(board, newX, newY);
        }
        ++newY;
    }
}

Errors CheckingLegalityFboard(short board[][SUDOKU_SIZE], int x, int y)
{
   int newX = 0, newY = 0;
   newX = (x / 3) * 3;
   newY = (y / 3) * 3;

   for (size_t i = 0; i < SUDOKU_SIZE; i++)
   {
        if (i != y && board[x][i] == board[x][y])
        {
          return ERR_ILLEGAL; 
        }
        if (i != x && board[i][y] == board[x][y])
        {
            return ERR_ILLEGAL;
        }
        if (i == 3 || i == 6)
        {
            ++newX, newY = (y / 3) * 3;
        }
        if (board[newX][newY] == board[x][y] && (newX != x && newY != y))
        {
            return ERR_ILLEGAL;
        }
       ++newY;
   }



   return ERR_OK;
}

int IsBoardFull(short board[][SUDOKU_SIZE])
{
    for (size_t i = 0; i < SUDOKU_SIZE; i++)
    {
        for (size_t j = 0; j < SUDOKU_SIZE; j++)
        {
            if (board[i][j] == -1)
            {
                return 0;
            }
        }
    }

    return 1;
}

Errors EnterNumberFromUser(short board[][SUDOKU_SIZE], Array_t*** possibilities, char* name, int x, int y)
{
    if (possibilities[x][y]->size == 0)
    {
        return ERR_FINISH_FAILURE;
    }

    PrintGetNumberFromUser(board, possibilities[x][y]->arr, possibilities[x][y]->size,name, x, y);

    free(possibilities[x][y]->arr);
    possibilities[x][y]->arr = NULL;
    possibilities[x][y]->size = 0;

    UpdatingPossibleDigits(board, possibilities, x, y);

    if (CheckingLegalityFboard(board, x, y) == ERR_ILLEGAL)
    {
        return ERR_FINISH_FAILURE;
    }
    if (IsBoardFull(board))
    {
        return ERR_FINISH_SUCCESS;
    }

    return ERR_OK;
}