#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../includes/board.h"
#include "../includes/pieces.h"
#include "../includes/move.h"


int main(){
	turnNum = 0;
	

	initWhite();
	initBlack();
	printBoard();
	int inputStartInt = 0;
	int inputStopInt = 0;

	while(1){
		printBoard();
		size_t bufsize = 3;
		char* inputStart;
		char* inputStop;
		int inputStartInt = 0;
		if(checkMateCheck()){
			if(turnColor == WHITE){
				printf("Black has won by checkmate\n");
			}
			else{
				printf("White has won by checkmate\n");
			}
			return 0;
		}
		int inputStopInt = 0;
		printf("Select Piece: ");
		inputStart = (char *)malloc(bufsize * sizeof(char));
		if(getline(&inputStart,&bufsize,stdin) <= 0){
			snprintf(errStr, 255, "Invalid user input");
			free(inputStart);
			continue;
		}	
		inputStartInt = convertUserInput(inputStart);
		if(inputStartInt < 0) { free(inputStart); continue;}
		/////////////////////////////////
		printf("\nInput Placement:");
		inputStop = (char *)malloc(bufsize * sizeof(char));
		if(getline(&inputStop,&bufsize,stdin) <= 0){
			snprintf(errStr, 255, "Invalid user input");
			free(inputStart); free(inputStop);
			continue;
		}	
		inputStopInt = convertUserInput(inputStop);
		/////////////////////////////////
		if(inputStopInt < 0){ free(inputStop); continue;}

		if(validateMove(inputStartInt, inputStopInt, JUST_CHECK_FALSE) != 0){
			free(inputStart); free(inputStop);
			continue;
		}
		free(inputStart); free(inputStop);
		if(checkWinCondition()){
			printBoard();
			return 0;
		}
		turnNum++;
    	snprintf(errStr, 255, " ");
	}
return 0;
}