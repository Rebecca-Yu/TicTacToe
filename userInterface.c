/*

AUTHOR: Rebecca Yu
DATE MODIFIED: 18-10-2019
PURPOSE: interacts with terminal (main), 
		 specifically handling any user input
		 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"
#include "setting.h"
#include "game.h"
#include "logs.h"
#include "validation.h"
#include "userInterface.h"

int main(int argc, char* argv[])
{
	/*reports error if not 1 argument + 1 for exectable name*/
	if (argc != 2)
	{
		printf("\nERROR! Not enough arguments :< \
			\nusage: \" ./game [settings.txt] \"\n \
			\n\t  [settings.txt]: filename of the settings file \n");
	}
	else
	{
		int *width, *height, *tiles, a, b, c;
		/*initialise pointers*/
		a = 0, b = 0, c = 0;
		width = &a, height = &b, tiles = &c;
		
		readFile(argv[1], width, height, tiles);/*read in settings*/
		/*check that all settings have been assigned a value*/
		if ((*width != 0) && (*height != 0) && (*tiles != 0))
		{
			#ifdef EDITOR
            char response = 0;
            #endif
            int option = 0;			
			LinkedList* logs = createLinkedList();
			do
			{
				/*prompt user for menu selection*/
				char* prompt;
				prompt = "\nSelect an option: \
						\n 1: Start a new game \
						\n 2: View the settings of the game \
						\n 3: View the current logs \
						\n 4: Save the logs to a file \
						\n 5: Exit the application \n ";
				option = integerInput(prompt, 1, 5);
				
				switch(option)
				{
					/*start new game*/
					case 1:
						newGame(width, height, tiles, logs);
					break;
					
					/*view game settings*/
					case 2:
						viewSettings(width, height, tiles);
						/*if EDITOR is defined during compilation, 
						user will be able to access additional feature of editing settings*/
						#ifdef EDITOR
						prompt = "\nWould you like to EDIT the current settings? [y/n] \n";
						response = yesOrNo(prompt);
						if((response == 'y') || (response == 'Y'))
						{
							editSettings(width, height, tiles);
						}
						#endif
					break;
					
					/*view current logs*/
					case 3:
						viewLogs(logs, width, height, tiles);
					break;
					
					/*save logs to a file*/
					case 4:
						/*if SECRET is defined during compilation, 
						user will be unable to access feature of saving logs to a file*/
						#ifdef SECRET
						printf("\nSorry~ You have NO access to this function... :p\n\n");	
						#else
						writeFile(logs, width, height, tiles);
						#endif
					break;
				}
			}while(option != 5);
			
			/*free linkedlist*/
			freeLogs(logs);
			
			printf("\nOkay~~ Goodbye :) ");
		} /*NOTE: error message is OUTPUTTED from readFile*/
	}
	printf("\n\n");
	return 0;
}


/* METHOD: integerInput   
* IMPORT: prompt (char*), min (integer), max (integer)
* EXPORTS: num (integer)
* PURPOSE: returns integer input by user within the given range*/
int integerInput(char* prompt, int min, int max)
{
	char* outPrompt, input[MAX_STRLEN];
	int num = 0;
	outPrompt = " ";
	/*prompt user integer until valid input is given*/
	do
	{
		printf("%s%s", outPrompt, prompt);
		scanf("%20s", input);
		/*check if string consists of only integer characters*/
		if(checkInteger(input) == 1)
		{
			/*covert string variable into integer datatype*/
			num = atoi(input);
			outPrompt = "ERROR! Invalid Option Selected! >:( \n ";
		}
		else
		{
			outPrompt = "ERROR! Input Must be an Integer! >:( \n ";
			num = min - 1;
		}
	}while((num < min) || (num > max));
	return num;
}

/* METHOD: inputNoMax   
* IMPORT: prompt (char*), min (integer)
* EXPORTS: num (integer)
* PURPOSE: returns integer input by user with a value larger than the given minimum value*/
int inputNoMax(char* prompt, int min)
{
	char* outPrompt, input[MAX_STRLEN];
	int num = 0;
	outPrompt = " ";
	/*prompt user integer until valid input is given*/
	do
	{
		printf("%s%s", outPrompt, prompt);
		scanf("%20s", input);
		/*check if string consists of only integer characters*/
		if(checkInteger(input) == 1)
		{
			/*covert string variable into integer datatype*/
			num = atoi(input);
			outPrompt = "ERROR! Invalid number entered! >:( \
					\nNOTE: Number must be greater than 2\n ";
		}
		else
		{
			outPrompt = "ERROR! Input Must be an Integer! >:( \n ";
			num = min - 1;
		}
	}while((num < min));
	return num;
}

/* METHOD: yesOrNo   
* IMPORT: prompt (char*)
* EXPORTS: response (char)
* PURPOSE: returns a character representing yes OR no*/
char yesOrNo(char* prompt)
{
	char *outPrompt, input[MAX_STRLEN], response;
	response = 0;
	outPrompt = " ";
	/*prompt user for yes or no response until valid response is given*/
	do
	{
		printf("%s%s", outPrompt, prompt);
		scanf("%20s", input);
		/*check input is a character -- length of input is one*/
		if((int)strlen(input) == 1)
		{
			response = input[0];
			outPrompt = "ERROR! Invalid Option Selected! >:( \n ";
		}
		else
		{
			outPrompt = "ERROR! Input Must be a Character! >:( \n ";
			response = 0;
		}
	}while((response != 'y') && (response != 'Y') &&
			(response != 'n') && (response != 'N'));
	return response;
}

/* METHOD: getLocation   
* IMPORT: player (int), array (int**), game (LinkedList*), width (int*), height (int*)
* EXPORTS: response (character)
* PURPOSE: prompts user for coordinates for the tile they wan to place on board*/
void getLocation(int player, int** array, LogEntry* entry, int* width, int* height)
{
	int xCoor, yCoor;
	char location[MAX_STRLEN];
	int cont = 0;
	char* outPrompt = " ";
	char* prompt = "\nEnter location as \"x,y\" : x ACROSS, y DOWN from top left corner \n";
	char postPrompt[100] = {'\0'};
	
    if(player == 1)
    {
	    printf(GREEN); /*set text colour to GREEN for player X*/
	}
    else
    {
        printf(BLUE); /*set text colour to BLUE for player O*/
    }
    printf("\nPLAYER \" %c \":", entry->player);
	printf(RESET); /*reset text color to default colour*/
	
	/*prompt user for coordinates of position they choose until VALID coordinates are given*/
	do
	{
		printf("%s%s%s", outPrompt, prompt, postPrompt);
		scanf("%20s", location);
		/*check if input is in the appropriate format and datatype for coordinates*/
		if(checkLocation(location) == 1)
		{
			/*parse entered coordinates into x and y coordinates*/
			sscanf(location, "%d,%d", &xCoor, &yCoor);
			/*validate given coordinates*/
			if((xCoor >= 0) && (xCoor < (*height)) && (yCoor >= 0) && (yCoor < (*width)))
			{
				cont = 0;
				/*check if current block is empty/ unused*/
				if(array[yCoor][xCoor] != -1)
				{
					cont = 1;
					outPrompt = "ERROR! unavailable location entered! :0 \n";
				}
			}
			else
			{
				cont = 1;
				outPrompt = "ERROR! Invalid location entered! >:( \n";
				sprintf(postPrompt, "   [x] : between 0 and %d \
									\n   [y] : between 0 and %d\n", (*height - 1), (*width - 1));
			}
		}
		else
		{
			cont = 1;
			outPrompt = "ERROR! Invalid location entered! >:( \n";
			sprintf(postPrompt, "   [x] : between 0 and %d \
								\n   [y] : between 0 and %d\n", (*height - 1), (*width - 1));
		}
		
	}while(cont == 1);
	entry->locationX = xCoor;
	entry->locationY = yCoor;
	/*assign player to the coordinates given*/
	array[yCoor][xCoor] = player;
}
