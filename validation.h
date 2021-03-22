/*

AUTHOR: Rebecca Yu
DATE MODIFIED: 18-10-2019

*/

#ifndef VALIDATION_H
#define VALIDATION_H

	/*Maximum length of input program will read in, 
	including null terminator -- general number (not too big, not too small)*/
	#define MAX_STRLEN 21

	int checkInteger(char* str);
	int checkLocation(char* str);
	
#endif