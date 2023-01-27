/**************************************************************************************
    Author: Mordechai Ben Shimon
    Creation date :  01/01/23
    Last modified date:  --
    Description :  Ui
***************************************************************************************/

#ifndef __UI_H__
#define __UI_H__

#define SUDOKU_SIZE 9
typedef struct WinningPlayers WinningPlayers_t;






void PrintWelcome();

int PrintGetNumOfPlayers();

void PrintGetPlayersNames(char* name);

void PrintGetNumberFromUser(short board[][SUDOKU_SIZE], short* arr, unsigned short size, char* name, int x, int y);

void PrintBoard(short board[][SUDOKU_SIZE], char* name, int isClean);

void PrintEnterValueToBoard(int x, int y);

void PrintPossibleValue(short* arr, unsigned short size);

void GetNumberToBoard(short board[][SUDOKU_SIZE], int x, int y); 

void PrinrtInvalidNumber();

void PrintPlayerLoses(short board[][SUDOKU_SIZE], char* name);

void PrintSudokuWinnersAndBoards(WinningPlayers_t* winners);






#endif /*__UI_H__*/