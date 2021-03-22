/*

AUTHOR: Rebecca Yu
DATE MODIFIED: 18-10-2019
PURPOSE: handles functions related to logs 
		 view current logs 
		 write current logs saved into a 'log' file
		 get filename of the log file to be written
		 free the current linked list of logs

***************************************************************************
REFERENCES:
https://www.tutorialspoint.com/c_standard_library/c_function_localtime.htm

***************************************************************************

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "linked_list.h"
#include "logs.h"
#include "setting.h"

/* METHOD: writeFile   
* IMPORT: logs(LinkedList*), width (int*), height (int*), tiles (int*)
* EXPORTS: none
* PURPOSE: write current logs to file*/
void writeFile(LinkedList* logs, int* width, int* height, int* tiles)
{
	FILE* file;    
	char filename[40];
	int hour, min, day, month;
	time_t now;
	struct tm* local;
	
	/*determine filename*/
	time(&now);
	local = localtime(&now);
	hour = local->tm_hour;
	min = local->tm_min;
	day = local->tm_mday;
	month = local->tm_mon + 1;
	sprintf(filename, "MNK_%d-%d-%d_%02d-%02d_%02d-%02d.log", *width, *height, *tiles, hour, min, day, month);
	
	/*writing to file*/
	file = fopen(filename, "w");
	printf("\nwriting to \" %s \"...\n", filename);
	/*check if file opens*/
	if (file != NULL)
	{
		int i, j;
		void* game;
		ListNode *turnNode, *gameNode;
		LogEntry* entry;
		/*write current settings to file:*/
		fprintf(file, "SETTINGS:\n");
		fprintf(file, "   M: %d\n", *width);
		fprintf(file, "   N: %d\n", *height);
		fprintf(file, "   K: %d\n", *tiles);
		/*write logs of EVERY game stored to file:*/
		gameNode = logs->head;
		for(i = 0; i < logs->count; i++)
		{
			game = gameNode->data;
			fprintf(file, "\nGAME %d:\n", i+1);
			turnNode = ((LinkedList*)game)->head;
			/*write logs of EVERY turn in game to file:*/
			for(j = 0; j < ((LinkedList*)game)->count; j++)
			{
				entry = (LogEntry*)turnNode->data;
				fprintf(file, "   Turn: %d\n", entry->turn);
				fprintf(file, "   Player: %c\n", entry->player);
				fprintf(file, "   Location: %d,%d\n\n", entry->locationX, entry->locationY);
				turnNode = turnNode->next;
			}
			fprintf(file, "   . . . \n");
			gameNode = (((ListNode*)gameNode)->next);
		}
		
		if (ferror(file))
		{
			printf("ERROR writing to \" %s \"  :< ", filename);
			perror("");
		}
	}
	else
	{
		printf("ERROR writing to \" %s \"  :< ", filename);
		perror("");
	}
	fclose(file);
}

/* METHOD: viewLogs   
* IMPORT: logs(LinkedList*), width (int*), height (int*), tiles (int*)
* EXPORTS: none
* PURPOSE: 'kickstart' printing logs to terminal via function pointer 
			and print list function of generic linkedlist*/
void viewLogs(LinkedList* logs, int* width, int* height, int* tiles)
{
	viewSettings(width, height, tiles);
	printLinkedList(logs, &printGame);
}

/* METHOD: printGame   
* IMPORT: data(void*)
* EXPORTS: none
* PURPOSE: print each game header to terminal*/
void printGame(LinkedList* logs, void* data)
{
	LinkedList *game;
	static int i = 0;
	game = (LinkedList*)data;
	i++;
	
	printf("\nGAME %d:\n", i);
	printLinkedList(game, &printTurn);
	printf("   . . . \n");
	
	/*RESET static i to 0 IF all games have been displayed*/
	if (i == logs->count)
	{
		i = 0;
	}
}

/* METHOD: printTurn   
* IMPORT: data(void*)
* EXPORTS: none
* PURPOSE: print each turn's information to terminal*/
void printTurn(LinkedList* logs, void* data)
{
	LogEntry *entry;
	entry = (LogEntry*)data;
	
	printf("   Turn: %d\n", entry->turn);
	printf("   Player: %c\n", entry->player);
	printf("   Location: %d,%d\n\n", entry->locationX, entry->locationY);
}

/* METHOD: freeLogs   
* IMPORT: logs (LinkedList*)
* EXPORTS: none
* PURPOSE: free logs via free list function of generic linkedlist*/
void freeLogs(LinkedList* logs)
{
	freeLinkedList(logs, &freeGame);
}

/* METHOD: freeGame   
* IMPORT: data(void*)
* EXPORTS: none
* PURPOSE: free each linkedlist of game*/
void freeGame(LinkedList* logs, void* data)
{
	LinkedList *game;
	game = (LinkedList*)data;
	freeLinkedList(game, &freeTurn);
}

/* METHOD: freeTurn   
* IMPORT: data(void*)
* EXPORTS: none
* PURPOSE: free each turn (data)*/
void freeTurn(LinkedList* logs, void* data)
{
	LogEntry *entry;
	entry = (LogEntry*)data;
	free(entry);
}
