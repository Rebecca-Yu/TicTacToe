/*

AUTHOR: Rebecca Yu
DATE MODIFIED: 16-10-2019

*/

#ifndef LOGS_H
#define LOGS_H

	void writeFile(LinkedList* logs, int* width, int* height, int* tiles);
	void viewLogs(LinkedList* logs, int* width, int* height, int* tiles);
	void printGame(LinkedList* logs, void* data);
	void printTurn(LinkedList* logs, void* data);
	void freeLogs(LinkedList* logs);
	void freeGame(LinkedList* logs, void* data);
	void freeTurn(LinkedList* logs, void* data);
	
#endif
