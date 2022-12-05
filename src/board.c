#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../includes/board.h"
#include "../includes/pieces.h"
#include "../includes/move.h"

char* dividerDash = "------------------------------------------------";
char* dividerUnder = "________________________________________________";
char* dividerPipeStart = "  |     |     |     |     |     |     |     |     |";
char* dividerPipeEnd = "_____|_____|_____|_____|_____|_____|_____|_____|";
char* LeterEnd = "   A      B     C     D     E     F     G     H   ";

int printBoard(){
   system("clear -x");
   if(turnNum % 2 == 0) printf("White's turn\n");
   else printf("Black's turn\n");
   
   printf("\n   %s",dividerUnder);
   for(int i=0; i < 64; i++){
      if(i ==0) printf("\n%s", dividerPipeStart);
      if(i%8 == 0){
         if(i != 0) printf("\n  |%s",dividerDash);
         printf("\n%d |",8-(i/8));
      }
      printf("%3s%3s",findPiece(i),"|");
   }
   printf("\n  |%s",dividerPipeEnd);
   printf("\n %s", LeterEnd);
   printf("\n");
   return 0;
}


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
		int inputStopInt = 0;
		
		printf("Select Piece: ");
		inputStart = (char *)malloc(bufsize * sizeof(char));
		if(getline(&inputStart,&bufsize,stdin) <= 0){
			printf("Invalid user input\n");
			free(inputStart);
			continue;
		}	
		inputStartInt = convertUserInput(inputStart);
		if(inputStartInt < 0) { free(inputStart); continue;}
		/////////////////////////////////
		printf("\nInput Placement:");
		inputStop = (char *)malloc(bufsize * sizeof(char));
		if(getline(&inputStop,&bufsize,stdin) <= 0){
			printf("Invalid user input\n");
			free(inputStop);
			continue;
		}	
		inputStopInt = convertUserInput(inputStop);
		/////////////////////////////////
		if(inputStopInt < 0){ free(inputStop); continue;}

		if(validateMove(inputStartInt,inputStopInt) != 0){
			printf("Invalid move");
			continue;
		}
		free(inputStart);free(inputStop);
		turnNum++;
		sleep(2);
	}

return 0;
}
