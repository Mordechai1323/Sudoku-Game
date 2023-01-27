/**************************************************************************************
    Author: Mordechai Ben Shimon
    Creation date :  01/01/23
    Last modified date:  --
    Description :  Ui
***************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "Errors.h"
#include "Ui.h"
#include "Players.h"
#include "Solver.h"


struct Player
{
    char name[100];
    short board[9][9];
    Array_t*** possibilities;
};

struct WinningPlayers
{
    Player_t* winner;
    WinningPlayers_t* next;
};


void PrintWelcome()
{
    printf("\n\033[1;36m                                          Welcome to the Sudoku game\033[0m\n");
}

int PrintGetNumOfPlayers()
{
    int numPlayers;
    int flag = 1;

    PrintWelcome();
    while (flag)
    {
        printf("\nEnter the number of players: ");
        scanf("%d", &numPlayers);
        flag = 0;
        if (numPlayers <= 0)
        {
            printf("\n--------------------------------------------\n");
            printf("|                                            |\n");
            printf("| Invalid number entered! Please try age.    |\n");
            printf("|                                            |\n");
            printf("---------------------------------------------\n");
            flag = 1;
        }
    }

    return numPlayers;
}

void PrintGetPlayersNames(char* name)
{
    printf("\nEnter the names of player: ");
    scanf("%s", name);
}

void PrintGetNumberFromUser(short board[][SUDOKU_SIZE], short* arr, unsigned short size, char* name,  int x, int y)
{
    PrintBoard(board, name, 1);
    PrintEnterValueToBoard(x, y);
    PrintPossibleValue(arr, size);
    GetNumberToBoard(board, x, y);
}

void PrintBoard(short board[][SUDOKU_SIZE], char* name, int isClean)
{
    isClean? system("cls"):"";

    printf("\n\033[1;34mSudoku board of: %s\033[0m\n\n", name);
    printf("  |");
    for (size_t i = 0; i < SUDOKU_SIZE; i++)
    {

        printf(" %c%s", 'A'+i, (i==2 || i == 5)?" |":"");
    }
    printf("\n");

    for (size_t x = 0; x < SUDOKU_SIZE; x++)
    {
        if (x % 3 == 0)
        {
            printf("--------------------------\n");
        }
        printf(" %d|", x+1);
        for (size_t y = 0; y < SUDOKU_SIZE; y++)
        {
            if (board[x][y] == -1)
            {
                printf("  ");
            }
            else
            {
                printf("\033[1;93m %hd\033[0m", board[x][y]);
            }
            if (y == 2 || y == 5)
            {
                printf(" |");
            }
        }
        printf("\n");

    }
    printf("--------------------------\n");

}

void PrintEnterValueToBoard(int x, int y)
{
    printf("Please enter value to %c%d, ", 'A'+y, x+1);
}

void PrintPossibleValue(short* arr, unsigned short size)
{
    printf("the value possible is: ");
    for (size_t i = 0; i < size; i++)
    {
        printf("%hd ", arr[i]);
    }
    printf("\n");
}

void GetNumberToBoard(short board[][SUDOKU_SIZE], int x, int y)
{
    short temp = 0;
    while (1)
    {
        scanf("%hd", &temp);
        if (temp > 0 && temp < 10)
        {
            board[x][y] = temp;
            break;
        }
        else
        {
            PrinrtInvalidNumber();
        }
    }
}

void PrinrtInvalidNumber()
{
    printf("\033[1;31mInvalid number!! The number should be between 1 and 9. Try again\033[0m\n");
}

void PrintPlayerLoses(short board[][SUDOKU_SIZE], char* name)
{
    system("cls");
    printf("\n\033[1;31m%s, you lost\033[0m\n", name);
    PrintBoard(board, name, 0);
    clock_t start = clock(); // record the start time
    while (clock() - start < 3 * CLOCKS_PER_SEC) {
        // busy loop
    }

}

void PrintSudokuWinnersAndBoards(WinningPlayers_t* winners)
{
    WinningPlayers_t* curr;
    int i = 1;

    system("cls");
    if (!winners)
    {
        return;
    }
    printf("\n\n ******************************\n");
    printf(" ********* WINNERS ***********\n");
    printf(" ******************************\n");

    curr = winners;
    while (curr)
    {
        printf("\n %d. %s\n", i, curr->winner->name);
        printf(" ---------------------------\n");
        PrintBoard(curr->winner->board, curr->winner->name, 0);
        curr = curr->next;
        i++;
    }
}