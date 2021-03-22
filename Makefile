##
 # File: Makefile
 # File Created: 17-10-2019
 # Author: Rebecca Yu
##

# Makefile Variables
CC = gcc
CFLAGS = -Wall -pedantic -ansi -Werror -std=c89 -g
OBJ = userInterface.o validation.o setting.o logs.o game.o linked_list.o
EXEC = TicTacToe

# Add SECRET to CFLAGS and recompile the program
##NOTE: user can't save logs to file in this version
ifdef SECRET 
CFLAGS += -DSECRET
SECRET : clean $(EXEC)
endif

# Add EDITOR to CFLAGS and recompile the program
##NOTE: user can edit M,N,K at run time in this version
ifdef EDITOR 
CFLAGS += -DEDITOR
EDITOR : clean $(EXEC)
endif

#make Target Rules:
$(EXEC) : $(OBJ)
		$(CC) $(OBJ) -o $(EXEC)


userInterface.o : userInterface.c userInterface.h validation.h setting.h logs.h game.h linked_list.h
		$(CC) -c userInterface.c $(CFLAGS)
		
validation.o : validation.c validation.h
		$(CC) -c validation.c $(CFLAGS)

setting.o : setting.c setting.h userInterface.h linked_list.h 
		$(CC) -c setting.c $(CFLAGS)
		
logs.o : logs.c logs.h setting.h linked_list.h
		$(CC) -c logs.c $(CFLAGS)
		
game.o : game.c game.h userInterface.h linked_list.h
		$(CC) -c game.c $(CFLAGS)

linked_list.o : linked_list.c linked_list.h logs.h
		$(CC) -c linked_list.c $(CFLAGS)

clean:
		rm -f $(EXEC) $(OBJ)

run :
		./TicTacToe settings.txt
		
runVal :
		valgrind --track-origins=yes --leak-check=full --show-reachable=yes ./TicTacToe settings.txt
