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

#include <stdio.h>
#include <time.h>
#include <stdlib.h>


#include "Errors.h"
#include "Board.h"
#include "Solver.h"

struct SlotLocation 
{
    int x;
    int y;
    SlotLocation_t* next;
    SlotLocation_t* prev;
};

struct SlotLocationlistManeger
{
    SlotLocation_t* head;
    SlotLocation_t* tail;
};

struct Array
{
    short* arr;
    unsigned short size;
};


Errors CreateSudokuBoard(short board[][SUDOKU_SIZE])
{
    SlotLocationlistManeger_t maneger = { NULL };

    if (CreateSoltLocationLinkedList(&maneger, board) != ERR_OK)
    {
        return ERR_GENERAL;
    }
    if (CreateRandomBoard(&maneger, board) != ERR_OK)
    {
        return ERR_ALLOCATION_FAILED;
    }

    DestroySlotLocationList(maneger.head);

    return ERR_OK;
}

Errors CreateSoltLocationLinkedList(SlotLocationlistManeger_t* maneger, short board[][SUDOKU_SIZE])
{
    SlotLocation_t* item = NULL;

    for (size_t x = 0; x < SUDOKU_SIZE; x++)
    {
        for (size_t y = 0; y < SUDOKU_SIZE; y++)
        {
            board[x][y] = -1;
            item = CreateNewItem(x, y);
            if (!item)
            {
                DestroySlotLocationList(maneger->head);
                return ERR_ALLOCATION_FAILED;
            }
            if (AddToEndSlotLocationList(maneger, item) != ERR_OK)
            {
                DestroySlotLocationList(maneger->head);
                return ERR_NOT_INITIALIZED;
            }
        }
    }

    return ERR_OK;
}

SlotLocation_t* CreateNewItem(int x, int y)
{
    SlotLocation_t* item = NULL;

    item = (SlotLocation_t*)malloc(sizeof(SlotLocation_t));
    if (!item)
    {
        return NULL;
    }
    item->x = x;
    item->y = y;
    item->next = NULL;
    item->prev = NULL;

    return item;
}

Errors AddToEndSlotLocationList(SlotLocationlistManeger_t* maneger, SlotLocation_t* item)
{
    if (! maneger || !item)
    {
        return ERR_NOT_INITIALIZED;
    }
    if (!maneger->head)
    {
        maneger->head = item;
        maneger->tail = item;
    }
    else
    {
        maneger->tail->next = item;
        maneger->tail = item;
    }

    return ERR_OK;
}

Errors CreateRandomBoard(SlotLocationlistManeger_t* maneger, short board[][SUDOKU_SIZE])
{
    int n = 0, k = 0, index = 0, sizeList = 81;
    SlotLocation_t* curr = NULL, *prev = NULL;
    Array_t* possibleValue = NULL;

    srand(time(NULL));

    n = (rand() % 13) + 8;
    for (size_t i = 0; i < n; i++)
    {
        curr = maneger->head;
        prev = NULL;
        k = rand() % (sizeList - 1) + 1;
        for (size_t j = 1; j < k; j++)
        {
            prev = curr;
            curr = curr->next;
        }
        possibleValue =  CheckPossibleValuesForSlot(board, curr->x, curr->y);
        if (!possibleValue)
        {
            return ERR_ALLOCATION_FAILED;
        }

        index = rand() % possibleValue->size;
        board[curr->x][curr->y] = possibleValue->arr[index];
        if (!prev)
        {
            maneger->head = curr->next;
            maneger->head->prev = NULL;
        }
        else
        {
            prev->next = curr->next;
            if (curr->next)
            {
                curr->next->prev = prev;
            }
        }

        --sizeList;
        free(curr);
        free(possibleValue);
    }

    return ERR_OK;
}

void DestroySlotLocationList(SlotLocation_t* head)
{
    SlotLocation_t* curr = NULL;

    if (!head)
    {
        return;
    }
    while (head->next)
    {
        curr = head;
        head = head->next;
        free(curr);
    }
    free(head);
}