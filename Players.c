/**************************************************************************************
    Author: Mordechai Ben Shimon
    Creation date :  21/01/23
    Description : This file contains functions related to managing a list of players in a game.
    The functions allows you to create a new player, create a list of active players, create an array of players from the linked list of active players and
    sort the array of active players using the merge sort algorithm,
    Create a binary tree from the orderly array, and scan the binary tree using the inOrder algorithm.
    This file also includes functionality for determining whether a player has completed the game successfully, and if so, moving them to a list of winning players
    and removing them from the active players list and their cell in the binary tree is set to NULL.
    If a player has not completed the game, they can fill in the slot on their board that has the least number of options.
    If a player's board is a failure, they are removed from the active player list and their cell in the binary tree is set to NULL.
    The file also includes a function for destroying the list of active players, the array of active players, the binary tree, and the list of winning players.
***************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


#include "Errors.h"
#include "Players.h"
#include "Board.h"
#include "Ui.h"
#include "Solver.h"

struct Player
{
    char name[100];
    short board[9][9];
   Array_t*** possibilities;
};

struct ActivePlayers
{
    Player_t* player;
    ActivePlayers_t* next;
};

struct ActivePlayerslistManeger
{
    ActivePlayers_t* head;
    ActivePlayers_t* tail;
};

struct TreeNodePlayers
{
    Player_t* player;
    TreeNodePlayers_t* left;
    TreeNodePlayers_t* right;
};

struct TreePlayers
{
    TreeNodePlayers_t* root;
};

struct WinningPlayers
{
    Player_t* winner;
    WinningPlayers_t* next;
};

void StartGame()
{
    size_t size = 0;
    ActivePlayerslistManeger_t maneger = { NULL };
    Errors eErr;
    Player_t** array;
    TreePlayers_t* tree;
    WinningPlayers_t* winners = NULL;

    size = PrintGetNumOfPlayers();
    eErr = CreateListOfActivePlayers(&maneger, size);
    array = CreateArrayActivePlayers(maneger.head, size);
    eErr = MergeSort(array, size);
    tree = BuildTreeFromArray(array, size);
    CheckListActivePlayers(&maneger, tree, &winners);
    if (winners)
    {
        PrintSudokuWinnersAndBoards(winners);
    }

 

    DestroyTree(tree->root);
    free(tree);
    DestroyWinnersList(winners);
    free(array);
}

Errors CreateListOfActivePlayers(ActivePlayerslistManeger_t* maneger, size_t size)
{
    ActivePlayers_t* item = NULL;
    
    assert(maneger);

    for (size_t i = 0; i < size; i++)
    {
        item = CreateNewPlayer();
        if (!item)
        {
            DestroyActivePlayersList(maneger->head);
            return ERR_ALLOCATION_FAILED;
        }
        if (AddToEndOfPlayersList(maneger, item) != ERR_OK)
        {
            DestroyActivePlayersList(maneger->head);
            return ERR_NOT_INITIALIZED;
        }
    }

    return ERR_OK;
}

void DestroyActivePlayersList(ActivePlayers_t* head)
{
    if (!head) 
    {
        return;
    }

    ActivePlayers_t* curr = NULL;
    while (head->next)
    {
        curr = head;
        head = head->next;
        DestroyPossibleDigits(curr->player->possibilities);
        free(curr->player);
        free(curr);
    }

    DestroyPossibleDigits(head->player->possibilities);
    free(head->player);
    free(head);
}

ActivePlayers_t* CreateNewPlayer()
{
    ActivePlayers_t* item = NULL;
    

    item = (ActivePlayers_t*)malloc(sizeof(ActivePlayers_t));
    if (!item)
    {
        return NULL;
    }

    item->player = (Player_t*)malloc(sizeof(Player_t));
    if (!item->player)
    {
        free(item);
        return NULL;
    }

    PrintGetPlayersNames(item->player->name);
    
    if (CreateSudokuBoard(item->player->board) != ERR_OK)
    {
        free(item);
        return NULL;
    }
    item->player->possibilities = PossibleDigits(item->player->board);
    if (!item->player->possibilities)
    {
        free(item);
        return NULL;
    }
    item->next = NULL;

    return item;
}

Errors AddToEndOfPlayersList(ActivePlayerslistManeger_t* maneger, ActivePlayers_t* item)
{
    if (!item || !maneger)
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

Player_t** CreateArrayActivePlayers(ActivePlayers_t* head, size_t size)
{
    Player_t** array;
    ActivePlayers_t*  curr;

    assert(head);

    array = (Player_t**)malloc(size * sizeof(Player_t*));
    if (!array)
    {
        return NULL;
    }

    curr = head;
    for (size_t i = 0; i < size; i++)
    {
        array[i] = curr->player;
        curr = curr->next;
    }

    return array;
}

Errors MergeSort(Player_t** array, size_t size)
{
    ActivePlayers_t** newArray;
    if (size < 2)
    {
        return;
    }

    MergeSort(array, size / 2);
    MergeSort(array + size / 2, size - (size / 2));

    newArray = (Player_t**)malloc(size * sizeof(Player_t*));
    if (!newArray)
    {
        return ERR_ALLOCATION_FAILED;
    }

    Merge(array, size/2, array + size / 2, size - (size / 2), newArray);

    for (size_t i = 0; i < size; i++)
    {
        array[i] = newArray[i];
    }

    free(newArray);
}

void Merge(Player_t** array1, int sizeArray1, Player_t** array2, int sizeArray2, Player_t** newArray)
{
    int numOfPlayerOne = 0, numOfPlayerTwo = 0;
    int indexArray1 = 0, indexArray2 = 0, i = 0, result = 0;

    while (indexArray1 < sizeArray1 && indexArray2 < sizeArray2)
    {
        NumOfFullSlots(array1[indexArray1], array2[indexArray2], &numOfPlayerOne, &numOfPlayerTwo);

        if (numOfPlayerOne == numOfPlayerTwo)
        {
            numOfPlayerTwo = 0;
            numOfPlayerOne = strcmp(array1[indexArray1]->name, array2[indexArray2]->name);
        }
        if (numOfPlayerOne > numOfPlayerTwo)
        {
            newArray[i] = array2[indexArray2];
            ++indexArray2;
        }
        else
        {
            newArray[i] = array1[indexArray1];
            ++indexArray1;
        }
        ++i;
    }

    while (indexArray1 < sizeArray1)
    {
        newArray[i] = array1[indexArray1];
        ++indexArray1, ++i;
    }

    while (indexArray2 < sizeArray2)
    {
        newArray[i] = array2[indexArray2];
        ++indexArray2, ++i;
    }
}

void NumOfFullSlots(Player_t* playerOne, Player_t* playerTwo, int* numOfPlayerOne, int* numOfPlayerTwo)
{
    // Initialize the counters to 0
    *numOfPlayerOne = *numOfPlayerTwo = 0;

    // Iterate over the boards of the two players and count the number of full slots
    for (size_t i = 0; i < SUDOKU_SIZE; i++)
    {
        for (size_t j = 0; j < SUDOKU_SIZE; j++)
        {
            if (playerOne->board[i][j] != -1)
            {
                ++(*numOfPlayerOne);
            }
            if (playerTwo->board[i][j] != -1)
            {
                ++(*numOfPlayerTwo);
            }
        }
    }
}

TreePlayers_t* BuildTreeFromArray(ActivePlayers_t** array, size_t size)
{
    TreePlayers_t* tree;
    tree = (TreePlayers_t*)malloc(sizeof(TreePlayers_t));
    if(tree == NULL) 
    {
        return NULL;
    }

    tree->root = CreateTreeFromArray(array, size);
    if (!tree->root)
    {
        return NULL;
    }

    return tree;
}

TreeNodePlayers_t* CreateTreeFromArray(Player_t** array, size_t size)
{
    TreeNodePlayers_t* root = NULL, * left = NULL, * right = NULL;

    if (size == 0 || array[size / 2] == -1)
    {
        return NULL;
    }
    else
    {
        root = CreateNewTNode(*(array + size / 2), NULL, NULL);
        if (!root)
        {
            return NULL;
        }
        root->left = CreateTreeFromArray(array, size / 2);
        root->right = CreateTreeFromArray(array + size / 2 + 1, size - size / 2 - 1);
    }
    return root;
}

TreeNodePlayers_t* CreateNewTNode(Player_t* player, TreeNodePlayers_t* left, TreeNodePlayers_t* right)
{
    TreeNodePlayers_t* temp = NULL;
    temp = (TreeNodePlayers_t*)malloc(sizeof(TreeNodePlayers_t));
    if (!temp)
    {
        return NULL;
    }

    temp->player = player;
    temp->left = left;
    temp->right = right;

    return temp;
}

void DestroyTree(TreeNodePlayers_t* root)
{
    if (!root)
    {
        return;
    }

    DestroyTree(root->left);
    DestroyTree(root->right);

    free(root);
}

void CheckListActivePlayers(ActivePlayerslistManeger_t* maneger, TreePlayers_t* tree, WinningPlayers_t** winners)
{
    while (maneger->head)
    {
        ScannerTree(tree->root, maneger, winners);
    }
}

void ScannerTree(TreeNodePlayers_t* root, ActivePlayerslistManeger_t* maneger, WinningPlayers_t** winners)
{
    
    if (!root)
    {
        return;
    }
    
    ScannerTree(root->left, maneger, winners);

    checkPlayerStatus(root, maneger, winners);

    ScannerTree(root->right, maneger, winners);
}

void checkPlayerStatus(TreeNodePlayers_t* root, ActivePlayerslistManeger_t* maneger, WinningPlayers_t** winners)
{
    Errors eErr, eErr2;
    int x = 0, y = 0;

    if (!root)
    {
        return;
    }


    eErr = OneStage(root->player->board, root->player->possibilities, &x, &y);

    while (eErr == ERR_NOT_FINISH)
    {
        eErr2 = EnterNumberFromUser(root->player->board, root->player->possibilities, root->player->name, x, y);
        if (eErr2 != ERR_OK)
        {
            eErr = eErr2;
            break;
        }
        eErr = OneStage(root->player->board, root->player->possibilities, &x, &y);
    }

    if (eErr == ERR_FINISH_FAILURE)
    {
        RemovePlayer(maneger, root);
    }
    else if (eErr == ERR_FINISH_SUCCESS)
    {
        MovePlayerToWinningList(maneger, root, root->player, winners);
    }
}

Errors AddWinnersPlayer(WinningPlayers_t** head, Player_t* player)
{
    WinningPlayers_t* curr;

    if (!*head)
    {
        *head = (WinningPlayers_t*)malloc(sizeof(WinningPlayers_t));
        if (!*head)
        {
            return ERR_ALLOCATION_FAILED;
        }
        (*head)->winner = player;
        (*head)->next = NULL;
        return ERR_OK;
    }

    curr = *head;
    while (curr->next)
    {
        curr = curr->next;
    }

    curr->next = (WinningPlayers_t*)malloc(sizeof(WinningPlayers_t));
    if (!curr->next)
    {
        return ERR_ALLOCATION_FAILED;
    }
    curr->next->winner = player;
    curr->next->next = NULL;

    return ERR_OK;
}

void DestroyWinnersList(WinningPlayers_t* head)
{
    WinningPlayers_t* curr = NULL;

    if (!head)
    {
        return;
    }
    curr = head;

    while (head->next)
    {
        curr = head;
        head = head->next;
        DestroyPossibleDigits(curr->winner->possibilities);
        free(curr->winner);
        free(curr);
        curr = NULL;
    }

    DestroyPossibleDigits(head->winner->possibilities);
    free(head->winner);
    free(head);
    curr = NULL;
}

void RemovePlayer(ActivePlayerslistManeger_t* maneger, TreeNodePlayers_t* node)
{
    ActivePlayers_t* curr = maneger->head, * prev = NULL;

    if (!maneger->head)
    {
        return;
    }
    PrintPlayerLoses(node->player->board, node->player->name);

    if (maneger->head->player->name == node->player->name)
    {
        curr = maneger->head;
        maneger->head = maneger->head->next;
        DestroyPlayerFromActivePlayersList(curr);
    }
    else
    {
        while (curr && curr->player->name != node->player->name)
        {
            prev = curr;
            curr = curr->next;
        }
        if (curr)
        {
            prev->next = curr->next;
            DestroyPlayerFromActivePlayersList(curr);
        }
    }

    node->player = NULL;
}

void MovePlayerToWinningList(ActivePlayerslistManeger_t* maneger, TreeNodePlayers_t* node, Player_t* player, WinningPlayers_t** winnersList)
{
    ActivePlayers_t* curr = maneger->head, *prev = NULL;

    
    assert(maneger->head || player);
    if (maneger->head->player->name == player->name)
    {
        curr = maneger->head;
        maneger->head = maneger->head->next;
        AddWinnersPlayer(winnersList, player);
        free(curr);
    }
    else
    {
        while (curr && curr->player->name != player->name)
        {
            prev = curr;
            curr = curr->next;
        }
        if (curr)
        {
            prev->next = curr->next;
            AddWinnersPlayer(winnersList, player);
            free(curr);
        }
    }

    node->player = NULL;
}

void DestroyPlayerFromActivePlayersList(ActivePlayers_t* player)
{
    if (!player)
    {
        return;
    }

    DestroyPossibleDigits(player->player->possibilities);

    free(player->player);
    free(player);
    player = NULL;
}



