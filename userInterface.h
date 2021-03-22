/*

AUTHOR: Rebecca Yu
DATE MODIFIED: 11-10-2019

*/

#ifndef USERINTERFACE_H
#define USERINTERFACE_H
	
	int integerInput(char* prompt, int min, int max);
	int inputNoMax(char* prompt, int min);
	char yesOrNo(char* prompt);
	void getLocation(int player, int** array, LogEntry* entry, int* width, int* height);
	
#endif