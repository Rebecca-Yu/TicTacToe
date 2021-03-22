/*

AUTHOR: Rebecca Yu
DATE MODIFIED: 18-10-2019
PURPOSE: contains helper functions for user input functions
	   : validates user input 

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "validation.h"

/* METHOD: checkInteger   
* IMPORT: str (char*)
* EXPORTS: isValid (int)
* PURPOSE: returns 0 or 1 depending on if the string imported is an integer*/
int checkInteger(char str[])
{
	int isValid, i, length;
	length = (int)strlen(str);
	/*assume string input is an integer*/
	isValid = 1;
	/*check every character in the string is integer*/
	for(i = 0; i < length; i++)
	{
		/*if character is not an integer, 
		then input is not an integer -- using ASCII CODE*/
		if((str[i] < 48) || (str[i] > 57))
		{
			isValid = 0;
		}
		if(isValid != 1)
		{
			i = length;
		}
	}	
	return isValid;
}

/* METHOD: checkLocation   
* IMPORT: str (char*)
* EXPORTS: isValid (int)
* PURPOSE: returns 0 or 1 depending on if the string imported is in the 
			correct specified format for coordinates*/
int checkLocation(char str[])
{
	int isValid, count;
	char* tokens, copy[MAX_STRLEN];
	/*make copy of parameter because tokeniser destroys original string*/
	strncpy(copy, str, MAX_STRLEN);
	/*first "sub-string" before "," delimiter*/
	tokens = strtok(copy, ",");
	count = 0;
	/*assume sub-string is an integer*/
	isValid = 1;
	while ((tokens != NULL) && (isValid == 1))
	{
		count++;
		isValid = checkInteger(tokens);
		/*check for next sub-string*/
		tokens = strtok(NULL, ",");
	}
	/*if input has less than OR more than 2 parts (like "x" OR "x,y,z"),
	then it is NOT in a valid coordinate format*/
	if(count != 2)
	{
		isValid = 0;
	}
	return isValid;
}