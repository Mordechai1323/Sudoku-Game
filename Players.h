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

#ifndef __PLAYERS_H__
#define __PLAYERS_H__

typedef struct Player Player_t;

typedef struct ActivePlayers ActivePlayers_t;

typedef struct ActivePlayerslistManeger ActivePlayerslistManeger_t;

typedef struct WinningPlayers WinningPlayers_t;

typedef struct TreeNodePlayers TreeNodePlayers_t;

typedef struct TreePlayers TreePlayers_t;




void StartGame();

/**
 * @brief Creates a linked list of active players.
 *
 * @param size: The number of players to be added to the list.
 * @return A pointer to the head of the linked list of active players.
 */
Errors CreateListOfActivePlayers(ActivePlayerslistManeger_t* maneger, size_t size);

/**
 * @brief destroyActivePlayersList frees all nodes in a linked list of ActivePlayers_t.
 *
 * @param pointer to the head of the linked list.
 */
void DestroyActivePlayersList(ActivePlayers_t* head);

/**
 * @brief Creates a new player with a name and a sudoku board.
 *
 * @return A pointer to the new player, or NULL if an error occurred.
 */
ActivePlayers_t* CreateNewPlayer();

/**
 * @brief addToEndOfPlayersList adds an item to the end of a linked list of ActivePlayers_t.
 *
 * @param head: a double pointer to the head of the linked list.
 * @param item: a pointer to the item to be added to the end of the list.
 *
 * @return OK if the item is successfully added to the end of the list, or an error code if an error occurred.
 */
Errors AddToEndOfPlayersList(ActivePlayerslistManeger_t* maneger, ActivePlayers_t* item);


/**
 * @brief Creates an array of `Player_t` pointers from a linked list of active players.
 *
 * @param head: Pointer to the head of the linked list of active players.
 * @param size: The size of the array to be created.
 * @return A pointer to the array or `NULL` on error.
 */
Player_t** CreateArrayActivePlayers(ActivePlayers_t* head, size_t size);

/**
 * @brief Sorts an array of `Player_t` pointers using the merge sort algorithm.
 *
 * @param array: Pointer to the array to be sorted.
 * @param size: The size of the array.
 */
Errors MergeSort(Player_t** array, size_t size);

/**
 * @brief Merges two sorted arrays of `Player_t` pointers into a single sorted array.
 *
 * @param array1: Pointer to the first array to be merged.
 * @param sizeArray1: The size of the first array.
 * @param array2: Pointer to the second array to be merged.
 * @param sizeArray2: The size of the second array.
 * @param newArray: Pointer to the array to store the merged results.
 */
void Merge(Player_t** array1, int sizeArray1, Player_t** array2, int sizeArray2, Player_t** newArray);

/**
 * @brief Calculates the number of full slots in the boards of two players.
 *
 * @param playerOne: Pointer to the first player.
 * @param playerTwo: Pointer to the second player.
 * @param numOfPlayerOne: Pointer to a variable to store the number of full slots in the board of the first player.
 * @param numOfPlayerTwo: Pointer to a variable to store the number of full slots in the board of the second player.
 */
void NumOfFullSlots(Player_t* playerOne, Player_t* playerTwo, int* numOfPlayerOne, int* numOfPlayerTwo);




/**
 * @brief BuildTreeFromArray - Creates a binary tree from an array of ActivePlayers_t.
 * @param array: Array of ActivePlayers_t to create the tree from.
 * @param size: Size of the array.
 *
 * Returns a pointer to the root node of the created tree.
 */
TreePlayers_t* BuildTreeFromArray(ActivePlayers_t** array, size_t size);

TreeNodePlayers_t* CreateTreeFromArray(Player_t** array, size_t size);

/**
 * @brief Creates a new tree node for player data.
 *
 * @param player: Pointer to player data.
 * @param left: Pointer to left child node.
 * @param right: Pointer to right child node.
 *
 * @return Pointer to the new tree node. Returns NULL if node creation fails.
 */
TreeNodePlayers_t* CreateNewTNode(Player_t* player, TreeNodePlayers_t* left, TreeNodePlayers_t* right);

/**
 * @brief Recursively destroys a binary search tree and frees the memory allocated for each node.
 *
 * @param root: Pointer to the root node of the binary search tree.
 */
void DestroyTree(TreeNodePlayers_t* root);


void CheckListActivePlayers(ActivePlayerslistManeger_t* maneger, TreePlayers_t* tree, WinningPlayers_t** winners);

/**
 * @brief Recursively scans a binary search tree of player data and performs a series of operations based on the status of each player's game.
 *
 * @param root: pointer to the root node of the binary search tree.
 * @param maneger: pointer to the active players list manager.
 * @param winners: pointer to the head node of a linked list of winning players.
 */
void ScannerTree(TreeNodePlayers_t* root, ActivePlayerslistManeger_t* maneger, WinningPlayers_t** winners);

void checkPlayerStatus(TreeNodePlayers_t* root, ActivePlayerslistManeger_t* maneger, WinningPlayers_t** winners);

/**
 * @brief Adds a player to a linked list of winning players.
 *
 * @param head:  pointer to the head node of the linked list.
 * @param player: Pointer to the player data to be added to the linked list.
 *
 * @return An Errors enum value indicating the success or failure of the operation. Returns ERR_OK if the operation is successful.
 */
Errors AddWinnersPlayer(WinningPlayers_t** head, Player_t* player);

/**
 * @brief Frees the memory allocated for a linked list of winning players and the player data associated with each node in the list.
 *
 * @param head: Pointer to the head node of the linked list of winning players.
 */
void DestroyWinnersList(WinningPlayers_t* head);

/*
*@brief Prints a message to the player indicating that they lost 
and removes the player from the active players list.
*
*@param maneger: pointer to the active players list manager.
*@param node: pointer to the tree node containing the player to remove.
*/
void RemovePlayer(ActivePlayerslistManeger_t* maneger, TreeNodePlayers_t* node);

/**
 *@brief Removes a player from the linked list of active players and adds them to the linked list of winning players. 
   The player's data is also removed from the binary search tree. 
 *
 * @param maneger: pointer to the active players list manager.
 * @param node: Pointer to the node in the binary search tree that represents the player to be removed
 * @param player: Pointer to the player data
 * @param winnersList: Pointer to the head of the linked list of winning players
 */
void MovePlayerToWinningList(ActivePlayerslistManeger_t* maneger, TreeNodePlayers_t* node, Player_t* player, WinningPlayers_t** winnersList);

/*
 *@brief Frees the memory for an active player and sets the pointer to NULL.
 *
 *@param player: pointer to the active player to be destroyed.
 */
void DestroyPlayerFromActivePlayersList(ActivePlayers_t* player);



#endif /*__PLAYERS_H__*/