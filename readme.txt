Rebecca Yu  : Tic-Tac-Toe Game
Readme

Date : 03-02-2021

Purpose: Play game of Tic-Tac-Toe with at least a 3x3 grid

Files: Makefile userInterface.c validation.c setting.c game.c logs.c linked_list.c
                userInterface.h validation.h setting.h game.h logs.h linked_list.handles
				
Test Files: settings.txt


Functionality: 
	Reads in a "Settings" File given by the command line argument
		-- handles file related errors/ validates values
		
	Play Game
		-- displays board with respective players positions
		-- gets user input for postion player chooses
		-- checks for winner after every turn
		
	Display 'current' settings of the game
		
	Display Logs
		
	Save the logs to a file
		-- writes logs to file named in format: "MNK_<M>-<N>-<K>_<HOUR>-<MIN>_<DAY>-<MONTH>.log"
		-- written format is as when logs are displayed
		
	Conditional Compilation
		-- if SECRET defined, disables functionality of writing to file
		-- if EDITOR defined, enables user to edit settings dring run time

-------------------------------------------------------------------------------------------------

How to Compile:
    "make"
 OR "make EDITOR=1"   <- compiles version where user can't write 'current' logs to file
 OR "make SECRET=1"   <- compiles version where users can edit 'current' settings during runtime


How to Run: 
"./TicTacToe [input.txt]"


Input File Content: 3 line file describing settings of game
	M='The width of the board'
	N='The height of the board'
	K='The number of matching tiles in a row to win'
 
NOTE: 3 is the minimum value for settings



How To Play: 
- At the start, empty board displayed 
- 1st player is prompted for coordinates
- 2nd player is prompted for coordinates
- This repeats until a winner or draw is found
- As the game progresses, board reflects each turn

NOTE: coordinates entered as (x,y) meaning x ACROSS, y DOWN from 0,0

