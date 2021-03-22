/*

AUTHOR: Rebecca Yu
DATE MODIFIED: 18-10-2019
PURPOSE: handles functions related to the settings
		 read in settings for game from file
		 viewing and editing the setting of the file 

*/

/*NOTE: format can be in any order with key:
	M – The width of the board (row)
	N – The height of the board (column)
	K – The number of matching tiles in a row to win*/

#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"
#include "setting.h"
#include "userInterface.h"
    
/* METHOD: readFile   
* IMPORT: filename(char*), width (int*), height (int*), tiles (int*)
* EXPORTS: none
* PURPOSE: read in file and parse text to determine setting values*/
void readFile(char* filename, int* width, int* height, int* tiles)
{
    FILE* file;
    file = fopen(filename, "r");
    if (file != NULL)
    {
        char key;
        int hasError, value, numLines;
        key = '0';
        value = -1; 
		hasError = 0, numLines = 0;

        while((!feof(file)) && (hasError == 0))
        {
            fscanf(file, "%c=%d\n", &key, &value);
			numLines++;
            /*check that setting value is at least 3 */
			if(value >= MIN)
            {
                switch(key)
                {	
                    case 'M': case 'm':
						/*checks that width is NOT already defined*/
                        if (*width == 0)
                        {
                            *width = value;
                        }
					break;

                    case 'N': case 'n':
						/*checks that height is NOT already defined*/
                        if (*height == 0)
                        {
                            *height = value;
                        }
					break;
					
                    case 'K': case 'k':
						/*checks that tiles is NOT already defined*/
                        if (*tiles == 0)
                        {
                            *tiles = value;
                        }
                    break;

                    default:
                        printf("ERROR in format of settings file :0");
                        hasError = 1;
                    break;
                }
            }
            else
            {
                printf("ERROR in parameter of settings: INVALID values! :0");
                hasError = 1;
            }
        }
		
		/*checks if ALL setting values are defined*/
        if ((hasError == 0) && ((*width == 0) || (*height == 0) || (*tiles == 0)))
        {
            printf("ERROR in parameter's format of settings file :0");
        }
        if (ferror(file))
        {
            printf("ERROR in reading \" %s \"  :< ", filename);
            perror("");
        }
		
		/*check that tile can be achieved with the board size*/
        if((*tiles > *width) && (*tiles > *height))
        {
            value = 0;
            *tiles = value;
            printf("ERROR! number of tiles specified cannot be achieved with current size of board");
        }
		/*check that file only contains 3 lines -- no additional lines*/
        if(numLines != 3)
        {
            value = 0;
            *tiles = value;
            printf("\n file contains additional lines");
        }
    }
    else
    {
        printf("ERROR in opening \" %s \"  :< ", filename);
        perror("");
    }
    fclose(file);
}

/* METHOD: editSettings   
* IMPORT: width (int*), height (int*), tiles (int*)
* EXPORTS: none
* PURPOSE: allow edit settings during run-time*/
void editSettings(int* width, int* height, int* tiles)
{
    char* setPrompt;
    int setting, tile;
	
	do
	{
		/*prompt user for which setting they what to edit*/
		setPrompt = "\nWhich setting do you wish to edit: \
					\n  1. the size of the board \
					\n  2. the number of matching tiles in a row required to win \
					\n  3. Go Back to Menu :> \n";
		setting = integerInput(setPrompt, 1, 3);
		/*prompt user for NEW board size*/
		if(setting == 1)
		{
			*width = inputNoMax("\nEnter NEW width (row) size of the board\n", MIN);
			*height = inputNoMax("\nEnter NEW height (column) size of the board\n", MIN);
		}
		/*prompt user for NEW tile number and validate*/
		else if(setting == 2)
		{
			tile = inputNoMax("\nEnter NEW number of consecutive tiles needed to win\n", MIN);
			/*check that tile can be achieved with the board size*/
			if((tile <= *width) || (tile <= *height))
			{
				*tiles = tile;
			}
			else
			{
				printf("\nERROR! number of tiles specified cannot be achieved with current size of board\n");
			}
		}
	}while(setting != 3);
}

/* METHOD: viewSettings   
* IMPORT: width (int*), height (int*), tiles (int*)
* EXPORTS: none
* PURPOSE: print the 'current' settings to the terminal*/
void viewSettings(int* width, int* height, int* tiles)
{
    printf("\nSETTINGS: \n");
    printf("   M: %d\n", *width);
    printf("   N: %d\n", *height);
    printf("   K: %d\n", *tiles);
}