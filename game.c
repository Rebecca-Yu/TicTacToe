/*

AUTHOR: Rebecca Yu
DATE MODIFIED: 17-10-2019
PURPOSE: functions related to playing the game

*/

#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"
#include "game.h"
#include "userInterface.h"

/* METHOD: newGame   
* IMPORT: width (int*), height (int*), tiles (int*), logs(LinkedList*)
* EXPORTS: none
* PURPOSE: play a new game*/
void newGame(int* width, int* height, int* tiles, LinkedList* logs)
{
	LinkedList* game;
	int **array, *winner, turnNo, noWinner;
	
	noWinner = -1;
	winner = &noWinner;
	
	game = createLinkedList();
	/*create board*/
	array = createArray(width, height);
	
	/*start game*/
	turnNo = 1;
	printBoard(array, width, height);
	do
	{
		LogEntry* entry = (LogEntry*)malloc(sizeof(LogEntry));
		entry->turn = turnNo;
		/*if turnNo is odd, then it is player O's turn*/
		if(turnNo % 2 != 0) 
		{
			entry->player = 'O';
			/*prompt player 'O' for the position where htey want to place the tile */
			getLocation(0, array, entry, width, height);
			/*check if player 'O' has won based on the current turn*/
			findWinner(array, winner, entry->locationX, entry->locationY, 0, width, height, tiles); 
		}
		/*otherwise, turnNo is even, meaning it is player X's turn*/
		else
		{
			entry->player = 'X';
			/*prompt player 'X' for the position where htey want to place the tile */
			getLocation(1, array, entry, width, height);
			/*check if player 'X' has won based on the current turn*/
			findWinner(array, winner, entry->locationX, entry->locationY, 1, width, height, tiles);
		}
		
		insertLast(game, entry);
		printBoard(array, width, height);
		turnNo++;
	
	}while((turnNo != (((*width)*(*height))+ 1)) && (*winner == -1));
	insertLast(logs, game);
	
	/*display results of game*/
    printf(RED);
	if(*winner == 0)
	{
		printf("\n  Player One (\"O\") WINS ! \n");
	}
	else if(*winner == 1)
	{
		printf("\n  Player Two (\"X\") WINS ! \n");
	}
	else /*board is full and no winner has been decided*/
	{
		printf("\n  IT IS A DRAW ! \n");
	}
    printf(RESET);
	freeArray(array, width, height);
}


/* METHOD: findWinner   
* IMPORT: array(int**), winner(int*), x(int), y(int), player(int), height (int*), width (int*), tiles (int*)
* EXPORTS: none
* PURPOSE: check if player has won based of the coordinates their input in that turn*/
void findWinner(int** array, int* winner, int x, int y, int player, int* width, int* height, int* tiles)
{
	/*check number of consequtive places player occupies in a column */
	checkCol(array, winner, x, player, width, tiles);
	/*check number of consequtive places player occupies in a row */
	checkRow(array, winner, y, player, height, tiles);
	/*check diagonal only if board is square AND number of tile required to win is the same as the height*/
	checkDiagonal(array, winner, player, width, height, tiles);
}

/* METHOD: checkCol   
* IMPORT: array(int**), winner(int*), x(int), player(int), width (int*), tiles (int*)
* EXPORTS: none
* PURPOSE: check the column based on the x coordinate entered by player*/
void checkCol(int** array, int* winner, int x, int player, int* width, int* tiles)
{
	int i, j, count;
	/*for every <tiles> number of blocks in the column, 
	check if all possible <tiles> number of consecutive blocks are holding player*/
	for(j = 0; j <= (*width - *tiles) ; j++)
	{
		count = 0;
		for(i = j; i < (j + *tiles); i++)
		{
			if (array[i][x] == player)
			{
				count++;	
			}
		}
		/*check if winner is found*/
		if(count == *tiles)
		{
			*winner = player;
		}
	}
}

/* METHOD: checkRow   
* IMPORT: array(int**), winner(int*), y(int), player(int), height (int*), tiles (int*)
* EXPORTS: none
* PURPOSE: check the row based on the y coordinate entered by player*/
void checkRow(int** array, int* winner, int y, int player, int* height, int* tiles)
{
	int i, j, count;
	/*for every <tiles> number of blocks in the row, 
	check if all possible <tiles> number of consecutive blocks are holding player*/
	for(j = 0; j <= (*height - *tiles) ; j++)
	{
		count = 0;
		for(i = j; i < (j + *tiles); i++)
		{
			if (array[y][i] == player)
			{
				count++;	
			}
		}
		/*check if winner is found*/
		if(count == *tiles)
		{
			*winner = player;
		}
	}
}

/* METHOD: checkDiagonal   
* IMPORT: array(int**), winner(int*), player(int), height (int*), width (int*), tiles (int*)
* EXPORTS: none
* PURPOSE: check every possible diagonal on the board for winner */
void checkDiagonal(int** array, int* winner, int player, int* width, int* height, int* tiles)
{
	int row, col, i, count;
	
	/*for every <tiles> by <tiles> size sub-blocks of the board,
	check the diagonals of that sub-block to see if the diagonals 
	hold <tiles> number of consecetive blocks of player*/
	for(row = 0; row <= (*width - *tiles); row++)
	{
		for(col = 0; col <= (*height - *tiles); col++)
		{
			/*check diagonal from top left to bottom right of sub-block*/
			count = 0;
			for(i = 0; i < *tiles; i++)
			{	
				if (array[i + row][i + col] == player)
				{
					count++;	
				}
			}
			/*check if winner is found*/
			if(count == *tiles)
			{
				*winner = player;
			}
			
			/*check diagonal from top right to bottom left of sub-block*/
			count = 0;
			for(i = 0; i < *tiles; i++)
			{
				if (array[i + row][(*tiles - 1 - i) + col] == player)
				{
					count++;	
				}
			}
			/*check if winner is found*/
			if(count == *tiles)
			{
				*winner = player;
			}
		}
	}
}

/* METHOD: printBoard   
* IMPORT: array (int**), width (int*), height (int*)
* EXPORTS: none
* PURPOSE: print board to terminal(graphical view of each players positions)*/
void printBoard(int** array, int* width, int* height)
{
	int i, j;
	/*column numbers*/
	printf("      00 ");
	for(i = 1; i < (*height); i++)
	{
		printf(" %02d ", i);
	}
	/*top border*/
	printf("\n    +");
	for(i = 0; i < (*height); i++)
	{
		printf("====");
	}
	printf("=+\n");
	/*row number + actual array*/
	for(j = 0; j < (*width - 1); j++)
	{
		printf(" %02d ||", j);
		for(i = 0; i < (*height); i++)
		{
			/*player that holds current position on board*/
			if(array[j][i] == 1)
			{
                printf(GREEN);
				printf(" X ");
			}
			else if(array[j][i] == 0)
			{
                printf(BLUE);
				printf(" O ");
                
			}
			/*if not X or O, the positon is currently not occupied by neither players*/
			else 
			{
				printf("   ");
			}
			printf(RESET);
            printf("|");
		}
		/*dividing line between rows*/
		printf("|\n    ||");
		for(i = 0; i < (*height - 1); i++)
		{
			printf("----");
		}
		printf("---||\n");
	}
	/*last row in the array*/
	printf(" %02d ||", *width - 1);
	for(i = 0; i < (*height); i++)
	{
		if(array[*width - 1][i] == 1)
		{
            printf(GREEN);
			printf(" X ");
		}
		else if(array[*width - 1][i] == 0)
		{
            printf(BLUE);
			printf(" O ");
		}
		else
		{
			printf("   ");
		}
		printf(RESET);
        printf("|");
	}
	printf("|\n");
	/*bottom border*/
	printf("    +");
	for(i = 0; i < (*height); i++)
	{
		printf("====");
	}
	printf("=+\n");
}

/* METHOD: createArray   
* IMPORT: height (int*), width (int*)
* EXPORTS: none
* PURPOSE: declare and malloc 2 dimensional integer array*/
int** createArray(int* width, int* height)
{
	int i;
	int** array = (int**)malloc((*width) * sizeof(int*));
	for(i = 0; i < (*width); i++)
	{
		array[i] = (int*)malloc((*height) * sizeof(int));
	}
	
	/*initialise array to '-1'*/
	initialiseArray(array, width, height);
	return array;
}

/* METHOD: initialiseArray   
* IMPORT: height (int*), width (int*)
* EXPORTS: none
* PURPOSE: initialise integer 2 dimensional array elements to "-1"
			- represents 'EMPTY', unused board tile*/
void initialiseArray(int** array, int* width, int* height)
{
	int i, j;
	for(i = 0; i < (*width); i++)
	{
		for(j = 0; j < (*height); j++)
		{
			array[i][j] = -1;
		}
	}
}

/* METHOD: freeArray   
* IMPORT: array(int**), height (int*), width (int*)
* EXPORTS: none
* PURPOSE: free the malloc'd 2D array*/
void freeArray(int** array, int* width, int* height)
{
	int i;
	for(i = 0; i < (*width); i++)
	{
		free(array[i]);
		array[i] = NULL;
	}
	free(array);
	array = NULL;
}
