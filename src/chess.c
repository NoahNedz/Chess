#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../includes/chess.h"

int turnNum = 0;

int getTurnColor(int turnNum){
	if(turnNum % 2 != 0){
		return BLACK;
	}
	return WHITE;	
}

int main(){
	int inputStartInt = 0;
	int inputStopInt = 0;
	size_t bufsize = 3;
	char* inputStart = NULL;
	char* inputStop = NULL;
	int turnColor = WHITE;
	move bestMoveForCOM;
	bestMoveForCOM.startPosition = 0;
	bestMoveForCOM.endPosition = 0;

	initWhite();
	initBlack();
	while(1){
		printScreen();
		turnColor = getTurnColor(turnNum);
		if(checkMateCheck(turnColor)){
			if(turnColor == WHITE){
				printf("Black has won by checkmate\n");
			}
			else{
				printf("White has won by checkmate\n");
			}
			return 0;
		}
		
		//COMPUTER'S TURN
		if(turnColor == BLACK){
			findBestMove(BLACK, &bestMoveForCOM, 1, 0);
			validateMove(bestMoveForCOM.startPosition, bestMoveForCOM.endPosition, JUST_CHECK_FALSE, turnColor);
			snprintf(errStr, 255, "");
			turnNum++;
			continue;
		}

		printf("\nSelect Piece: ");
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

		if(validateMove(inputStartInt, inputStopInt, JUST_CHECK_FALSE, turnColor) != 0){
			free(inputStart); free(inputStop);
			continue;
		}
		free(inputStart); free(inputStop);
		if(checkWinCondition()){
			printScreen();
			return 0;
		}
		turnNum++;
    	snprintf(errStr, 255, " ");
	}
return 0;
}