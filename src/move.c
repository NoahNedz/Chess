#include <stdio.h>
#include <stdlib.h>
#include "../includes/pieces.h"
#include "../includes/move.h"
#include "../includes/board.h"
#include <string.h>

int startPos = 0;
int endPos = 0;
int turnColor = 0;
int pieceNum = 0;
int startValid = 0;
int endValid = 1;
int takingOpponent = 0;
int takingOpponentPos = 0;
int firstMove = 0;

piece *piecePointer;
piece *piecePointerOpp;
piece *piecePointerChecker;
piece *piecePointerOppChecker;

int convertUserInput(char* userInput){
	if(strlen(userInput) != 3){
		printf("Invalid user input length");
		return -1;
	}
	int letterOffset = 0;
	if(strncmp(userInput,"A",1) == 0 || strncmp(userInput,"a",1) == 0) letterOffset = 0;
	else if(strncmp(userInput,"B",1) == 0 || strncmp(userInput,"b",1) == 0) letterOffset = 1;
	else if(strncmp(userInput,"C",1) == 0 || strncmp(userInput,"c",1) == 0) letterOffset = 2;
	else if(strncmp(userInput,"D",1) == 0 || strncmp(userInput,"d",1) == 0) letterOffset = 3;
	else if(strncmp(userInput,"E",1) == 0 || strncmp(userInput,"e",1) == 0) letterOffset = 4;
	else if(strncmp(userInput,"F",1) == 0 || strncmp(userInput,"f",1) == 0) letterOffset = 5;
	else if(strncmp(userInput,"G",1) == 0 || strncmp(userInput,"g",1) == 0) letterOffset = 6;
	else if(strncmp(userInput,"H",1) == 0 || strncmp(userInput,"h",1) == 0) letterOffset = 7;
	else {
		printf("Invalid user input : %s\n", userInput);
		return -1;
	}
	int numOffset = 0;
	if(strncmp(userInput+1,"1",1) == 0 || strncmp(userInput+1,"1",1) == 0) numOffset = 56;
	else if(strncmp(userInput+1,"2",1) == 0 || strncmp(userInput+1,"2",1) == 0) numOffset = 48;
	else if(strncmp(userInput+1,"3",1) == 0 || strncmp(userInput+1,"3",1) == 0) numOffset = 40;
	else if(strncmp(userInput+1,"4",1) == 0 || strncmp(userInput+1,"4",1) == 0) numOffset = 32;
	else if(strncmp(userInput+1,"5",1) == 0 || strncmp(userInput+1,"5",1) == 0) numOffset = 24;
	else if(strncmp(userInput+1,"6",1) == 0 || strncmp(userInput+1,"6",1) == 0) numOffset = 16;
	else if(strncmp(userInput+1,"7",1) == 0 || strncmp(userInput+1,"7",1) == 0) numOffset = 8;
	else if(strncmp(userInput+1,"8",1) == 0 || strncmp(userInput+1,"8",1) == 0) numOffset = 0;
	else {
		printf("Invalid user input : %s\n", userInput);
		return -1;
	}
  printf("%d+%d = %d\n", letterOffset,numOffset,letterOffset+numOffset);
	return letterOffset+numOffset;
}

int translateToRow(int position){
  if(position >= 0 && position <= 7) return 8;
  if(position >= 8 && position <= 15) return 7;
  if(position >= 16 && position <= 23) return 6;
  if(position >= 24 && position <= 31) return 5;
  if(position >= 32 && position <= 39) return 4;
  if(position >= 40 && position <= 47) return 3;
  if(position >= 48 && position <= 55) return 2;
  if(position >= 56 && position <= 63) return 1;
  return -1;
}

int translateToColumn(int position){
  return position%8;
}


int movePawn(){

  //moving backwards as pawn check
  if(turnColor){
	  if(endPos >= startPos) return -1;
  }
  else{
    if(endPos <= startPos) return -1;
  }
	if(firstMove == 1){
		if( (turnColor && ((endPos == startPos-8) || (endPos == startPos-16))) ||
        (!turnColor && ((endPos == startPos+8) || (endPos == startPos+16)))){
			piecePointer->location = endPos;
			piecePointer->moveCount++;
			printf("Moving pawn\n");
			return 0;
		}
	}
	if(takingOpponent == 1){
		if( (turnColor && ((endPos == startPos-9) || (endPos == startPos-7)))|| 
        (!turnColor &&  ((endPos == startPos+9) || (endPos == startPos+7)))){
			piecePointer->location = endPos;
			piecePointer->moveCount++;
			piecePointerOpp->alive = 0;
      printf("Moving pawn\n");
			return 0;
		}
		else return -1;
	}
	else if( (turnColor && (endPos == startPos-8)) ||
           (!turnColor && (endPos == startPos+8))){
		piecePointer->location = endPos;
		piecePointer->moveCount++;
		printf("Moving pawn\n");
		return 0;
	}
	return -1;
}
int moveRook(){
  //check if start and end position are in the same row or col
  int sameRow = translateToRow(startPos) == translateToRow(endPos);
  int sameCol = translateToColumn(startPos) ==  translateToColumn(endPos);
  if(!sameRow && !sameCol) return -1;
     
  int moveUp = 0;
  int moveDown = 0;
  int moveLeft = 0;
  int moveRight = 0;
  if(sameRow){
    if(startPos < endPos) moveRight = 1;
    else moveLeft = 1;
  }
  else if(endPos < startPos) moveUp = 1;
  else moveDown = 1;
  
  //check if landing on your own piece
  for(int i = 0; i < 16; i++){
    piecePointerChecker = &black[i];
    if(turnColor) piecePointerChecker = &white[i];
    if(endPos == piecePointerChecker->location) return -1;
  }
  //check if any obstacles in the way
  if(moveUp){
  printf("Moving rook up\n");
    for(int i = startPos; i != endPos; i -=8){
      for(int j = 0; j < 16; j++){
        if(i == white[j].location && piecePointer->location != i) return -1;
        if(i == black[j].location && piecePointer->location != i) return -1;
      }  
    }
  }
  if(moveDown){
    printf("Moving rook down\n");
    for(int i = startPos; i != endPos; i +=8){
      for(int j = 0; j < 16; j++){
        if(i == white[j].location && piecePointer->location != i) return -1;
        if(i == black[j].location && piecePointer->location != i) return -1;
      }  
    }
  }
  if(moveRight){
    printf("Moving rook right\n");
    for(int i = startPos; i%8 == 7; i++){
      for(int j = 0; j < 16; j++){
        if(i == white[j].location && piecePointer->location != i) return -1;
        if(i == black[j].location && piecePointer->location != i) return -1;
      }  
    }
  }
  if(moveLeft){
  printf("Moving rook left\n");
    for(int i = startPos; i%8 == 0; i--){
      for(int j = 0; j < 16; j++){
        if(i == white[j].location && piecePointer->location != i) return -1;
        if(i == black[j].location && piecePointer->location != i) return -1;
      }  
    }
  }
  piecePointer->location = endPos;
  piecePointer->moveCount++;
  if(takingOpponent == 1) piecePointerOpp->alive = 0;
	return 0;
}

int validateMove(int startPosition, int endPosition){
	startPos = startPosition;
	endPos = endPosition;
	turnColor = 0;
	pieceNum = 0;
	startValid = 0;
	takingOpponent = 0;
	takingOpponentPos = 0;
	firstMove = 0;
	
	if(turnNum % 2 == 0) turnColor = 1;
 
	for(int i = 0; i < 16; i++){
 
    piecePointer = &white[i];
    if(!turnColor) piecePointer = &black[i];
  	if(piecePointer->location == startPos && piecePointer->alive){
  			pieceNum = i;
  			startValid = 1;
        break;
		}
	}
	
	if(startValid != 1) return -1;
	for(int i = 0; i < 16; i++){
 
    piecePointerOppChecker = &black[i];
    if(!turnColor) piecePointerOppChecker = &white[i];
    
		if(piecePointerOppChecker->location == endPos){
      piecePointerOpp = piecePointerOppChecker;
			takingOpponent = 1;
			takingOpponentPos = i;
      break;
		}
	}

	//check rules for that piece
  
  if(piecePointer->moveCount == 0) firstMove = 1;
    
	if(strncmp(piecePointer->name,"p",1) == 0){
		return movePawn();
	}
	if(strncmp(piecePointer->name,"r",1) == 0){
		return moveRook();
	}
		
	
	
	
   return 0;
}

