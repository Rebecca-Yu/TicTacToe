/*

AUTHOR: Rebecca Yu
DATE MODIFIED: 12-10-2019

*/

#ifndef SETTING_H
#define SETTING_H
	
	/*minimum size for tiles, height and width settings*/
	#define MIN 3
	/*Justification for '3' minimum: 
	  1 : for board size - can't even have each player place a tile each (1x1) 
		: for number of matching tiles - would not allow second player to win
	  2 : for board size - would not allow for either player to win, 
		   unless '1' was a valid minimum number of tiles (1x2 OR 2x2) 
		   -- NOTE: this also applies to 1x3, 2x3, 1x4, 2x4, ....
		: for number of matching tiles - would not allow second player a great chance of winning */
	
	void readFile(char* filename, int* width, int* height, int* tiles);
	void editSettings(int* width, int* height, int* tiles);
	void viewSettings(int* width, int* height, int* tiles);

#endif