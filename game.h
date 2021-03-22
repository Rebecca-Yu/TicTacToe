/*

AUTHOR: Rebecca Yu
DATE MODIFIED: 17-10-2019

*/

#ifndef GAME_H
#define GAME_H

    /*COLOURS*/
    #define RED "\033[1;31m"
    #define GREEN "\033[1;32m"
    #define YELLOW "\033[01;33m"
    #define BLUE "\033[1;36m"
    #define RESET "\033[0m"

	void newGame(int* width, int* height, int* tiles, LinkedList* logs);
	void findWinner(int** array, int* winner, int x, int y, int player, int* width, int* height, int* tiles);
	void checkCol(int** array, int* winner, int x, int player, int* width, int* tiles);
	void checkRow(int** array, int* winner, int y, int player, int* height, int* tiles);
	void checkDiagonal(int** array, int* winner, int player, int* width, int* height, int* tiles);
	void printBoard(int** array, int* width, int* height);
	int** createArray(int* width, int* height);
	void initialiseArray(int** array, int* width, int* height);
	void freeArray(int** array, int* width, int* height);
	
#endif
