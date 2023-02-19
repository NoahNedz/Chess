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
	if(userInput == NULL || strlen(userInput) != 3){
    snprintf(errStr, 255, "Invalid user input length");
		return -1;
	}
	int letterOffset = 0;
	if     ((userInput[0] == 'A') || (userInput[0] == 'a')) letterOffset = 0;
	else if((userInput[0] == 'B') || (userInput[0] == 'b')) letterOffset = 1;
	else if((userInput[0] == 'C') || (userInput[0] == 'c')) letterOffset = 2;
	else if((userInput[0] == 'D') || (userInput[0] == 'd')) letterOffset = 3;
	else if((userInput[0] == 'E') || (userInput[0] == 'e')) letterOffset = 4;
	else if((userInput[0] == 'F') || (userInput[0] == 'f')) letterOffset = 5;
	else if((userInput[0] == 'G') || (userInput[0] == 'g')) letterOffset = 6;
	else if((userInput[0] == 'H') || (userInput[0] == 'h')) letterOffset = 7;
	else {
   snprintf(errStr, 255, "Invalid user input : %s", userInput);
		return -1;
	}
	int numOffset = 0;
	if     ((userInput[1] == '1') || (userInput[1] == '1')) numOffset = 56;
	else if((userInput[1] == '2') || (userInput[1] == '2')) numOffset = 48;
	else if((userInput[1] == '3') || (userInput[1] == '3')) numOffset = 40;
	else if((userInput[1] == '4') || (userInput[1] == '4')) numOffset = 32;
	else if((userInput[1] == '5') || (userInput[1] == '5')) numOffset = 24;
	else if((userInput[1] == '6') || (userInput[1] == '6')) numOffset = 16;
	else if((userInput[1] == '7') || (userInput[1] == '7')) numOffset = 8;
	else if((userInput[1] == '8') || (userInput[1] == '8')) numOffset = 0;
	else {
		snprintf(errStr, 255, "Invalid user input : %s", userInput);
		return -1;
	}
  //printf("%d+%d = %d\n", letterOffset,numOffset,letterOffset+numOffset);
	return letterOffset+numOffset;
}

int translateToRow(int position){
  if(position >= 0  && position <= 7) return 8;
  if(position >= 8  && position <= 15) return 7;
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

int findMoveDirection(int startPos, int endPos){
  int startRow = translateToRow(startPos);
  int endRow = translateToRow(endPos);
  int startCol = translateToColumn(startPos);
  int endCol = translateToColumn(endPos);
  int direction = -1;
  if     (endRow > startRow && endCol == startCol ) direction = UP;
  else if(endRow > startRow && endCol > startCol) direction = UPRIGHT;
  else if(endRow == startRow && endCol > startCol) direction = RIGHT;
  else if(endRow < startRow && endCol > startCol) direction = DOWNRIGHT;
  else if(endRow < startRow && endCol == startCol) direction = DOWN;
  else if(endRow < startRow && endCol < startCol) direction = DOWNLEFT;
  else if(endRow == startRow && endCol < startCol) direction = LEFT;
  else if(endRow > startRow && endCol < startCol) direction = UPLEFT;
  else {
    return -1;
  }
  //check that moving in proper diagonal
  if(direction == UPRIGHT || direction == UPLEFT || 
     direction == DOWNRIGHT || direction == DOWNLEFT)
     {
        if(abs(endRow - startRow) != abs(endCol - startCol)){
          return -1;
        }
     }
  return direction;
}

int checkIfLandingOnOwnPiece(int position){
  char* findPiece = drawPieces(position);
  if(findPiece == NULL){
    snprintf(errStr, 255, "Unable to locate piece");
    return 1;
  }
  if(turnColor == WHITE && findPiece[0] == 'W') return 1;
  if(turnColor == BLACK && findPiece[0] == 'B') return 1;
  return 0;
}

int movePawn(){
  if(checkIfLandingOnOwnPiece(endPos) != 0){
    return -1;
  }
  //moving backwards as pawn check
  if(turnColor == WHITE){
	  if(endPos >= startPos) return -1;
  }
  else{
    if(endPos <= startPos) return -1;
  }
	if(firstMove == 1){
		if( (turnColor == WHITE && ((endPos == startPos-8) || (endPos == startPos-16))) ||
        (turnColor == BLACK && ((endPos == startPos+8) || (endPos == startPos+16)))){
			return 0;
		}
	}
	if(takingOpponent == 1){
		if( (turnColor == WHITE && ((endPos == startPos-9) || (endPos == startPos-7)))|| 
        (turnColor == BLACK &&  ((endPos == startPos+9) || (endPos == startPos+7)))){
			return 0;
		}
		else return -1;
	}
	else if( (turnColor == WHITE && (endPos == startPos-8)) ||
           (turnColor == BLACK && (endPos == startPos+8))){
		return 0;
	}
	return -1;
}
int moveRook(){
  //check if start and end position are in the same row or col
  int sameRow = translateToRow(startPos) == translateToRow(endPos);
  int sameCol = translateToColumn(startPos) == translateToColumn(endPos);
  if(!sameRow && !sameCol){
    snprintf(errStr, 255, "Invalid movement");
    return -1;
  }
  if(checkIfLandingOnOwnPiece(endPos) != 0){
    snprintf(errStr, 255, "Cannot place on one's own piece");
    return -1;
  }
  int direction = findMoveDirection(startPos, endPos);
  int moveInc = 0;
  if      (direction == UP) moveInc = -8;
  else if (direction == DOWN) moveInc = 8;
  else if (direction == LEFT) moveInc = -1;
  else if (direction == RIGHT) moveInc = 1;
  else{
    snprintf(errStr, 255, "Invalid movement");
    return -1;
  }
  //check if any obstacles in the way
  int spotCheck = startPos + moveInc;
  while(spotCheck != endPos){
    for(int j = 0; j < 16; j++){
      if(spotCheck == white[j].location || spotCheck == black[j].location ){
        snprintf(errStr, 255, "Piece in the way of movement");
        return -1;
      }
    }
    spotCheck += moveInc;
    if(spotCheck > 63 || spotCheck < 0) break;
  }
	return 0;
}

int moveKnight(){
  //check if landing on your own piece
  if(checkIfLandingOnOwnPiece(endPos) == 1){
    snprintf(errStr, 255, "Cannot place on one's own piece");
    return -1;
  }
  int startRow = translateToRow(startPos);
  int endRow = translateToRow(endPos);
  int startCol = translateToColumn(startPos);
  int endCol = translateToColumn(endPos);
  if(abs(startRow - endRow) == 1 && abs(startCol - endCol) != 2) return -1;
  if(abs(startRow - endRow) == 2 && abs(startCol - endCol) != 1) return -1;
  return 0;
}

int moveBishop(){
  //check if landing on your own piece
  if(checkIfLandingOnOwnPiece(endPos) == 1){
    snprintf(errStr, 255, "Cannot place on one's own piece");
    return -1;
  }
  int direction = findMoveDirection(startPos, endPos);
  int moveInc = 0;
  if      (direction == UPRIGHT) moveInc = -7;
  else if (direction == UPLEFT) moveInc = -9;
  else if (direction == DOWNRIGHT) moveInc = 9;
  else if (direction == DOWNLEFT) moveInc = 7;
  else{
    snprintf(errStr, 255, "Bishop must move diagonally");
    return -1;
  }
  int spotCheck = startPos + moveInc ;
  //check if any obstacles in the way
  while(spotCheck != endPos){
    for(int j = 0; j < 16; j++){
      if(spotCheck == white[j].location || spotCheck == black[j].location ){
        snprintf(errStr, 255, "Piece in the way of movement");
        return -1;
      }
    }
    spotCheck += moveInc;
    if(spotCheck > 63 || spotCheck < 0) break;
  } 
  return 0;
}

int moveQueen(){
  //check if landing on your own piece
  if(checkIfLandingOnOwnPiece(endPos) == 1){
    snprintf(errStr, 255, "Cannot place on one's own piece");
    return -1;
  }
  int direction = findMoveDirection(startPos, endPos);
  if(direction == -1){
    snprintf(errStr, 255, "Invalid move");
    return -1;
  }
  int moveInc = 0;
  if      (direction == UP) moveInc = -8;
  else if (direction == UPRIGHT) moveInc = -7;
  else if (direction == RIGHT) moveInc = 1;
  else if (direction == DOWNRIGHT) moveInc = 9;
  else if (direction == DOWN) moveInc = 8;
  else if (direction == DOWNLEFT) moveInc = 7;
  else if (direction == LEFT) moveInc = -1;
  else if (direction == UPLEFT) moveInc = -9;
  else{
    snprintf(errStr, 255, "Invalid move");
    return -1;
  }
  //check if pieces in the way
  int spotCheck = startPos + moveInc; 
  while(spotCheck != endPos){
    for(int j = 0; j < 16; j++){
      if(spotCheck == white[j].location || spotCheck == black[j].location ){
        snprintf(errStr, 255, "Piece in the way of movement");
        return -1;
      }
    }
    spotCheck += moveInc;
    if(spotCheck > 63 || spotCheck < 0) break;
  }
  return 0;
}
int moveKing(){
  //check if landing on your own piece
  if(checkIfLandingOnOwnPiece(endPos) == 1){
    snprintf(errStr, 255, "Cannot place on one's own piece");
    return -1;
  }
  int direction = findMoveDirection(startPos, endPos);
  if(direction == -1){
    snprintf(errStr, 255, "Invalid direction of movement");
    return -1;
  }
  //king can only move one tile, need to add logic for castling
  int posDiff = abs(endPos - startPos);
  if(posDiff == 1 || posDiff == 7 || posDiff == 8 || posDiff == 9)
  {
    return 0;
  }
  snprintf(errStr, 255, "Invalid move");
  return -1;
}

int validateMove(int startPosition, int endPosition){
	int rc = -1;
  startPos = startPosition;
	endPos = endPosition;
	pieceNum = 0;
	startValid = 0;
	takingOpponent = 0;
	takingOpponentPos = 0;
	firstMove = 0;

  //determine turn color
  if(turnNum % 2 == 0) turnColor = WHITE;
  else turnColor = BLACK;

  //check if start and finish are the same
  if(startPos == endPos) return -1;

  //see if start position is pointing to players piece
	for(int i = 0; i < 16; i++){
    if(turnColor == BLACK) piecePointer = &black[i];
    else piecePointer = &white[i];
  	if(piecePointer->location == startPos && piecePointer->alive){
  			pieceNum = i;
  			startValid = 1;
        break;
		}
	}
  if(startValid != 1){
    snprintf(errStr, 255, "Start position does not point to one's own piece");
    return -1;
  }

	//determine if taking opponent
	for(int i = 0; i < 16; i++){
    if(turnColor == BLACK) piecePointerOppChecker = &white[i];
    else piecePointerOppChecker = &black[i];
		if(piecePointerOppChecker->location == endPos){
      piecePointerOpp = piecePointerOppChecker;
			takingOpponent = 1;
			takingOpponentPos = i;
      break;
		}
	}

	//check rules for that piece
  if(piecePointer->moveCount == 0) firstMove = 1;
 
	if     (piecePointer->name[1] == 'p'){
		rc = movePawn();
	}
	else if(piecePointer->name[1] == 'r'){
		rc = moveRook();
	}
 	else if(piecePointer->name[1] =='k'){
		rc = moveKnight();
	}
	else if(piecePointer->name[1] == 'b'){
		rc = moveBishop();
	}
  else if(piecePointer->name[1] == 'Q'){
    rc = moveQueen();
  }
  else if(piecePointer->name[1] == 'K'){
    rc = moveKing();
  }
  else{
    snprintf(errStr, 255, "Unable to determine piece type");
    rc = -1;
  }
  if(rc == 0){
    piecePointer->location = endPos;
    piecePointer->moveCount++;
    if(takingOpponent == 1){
      piecePointerOpp->alive = 0;
      piecePointerOpp->location = -1;
    }
	}
  return rc;
}

int checkWinCondition(){
  int whiteAlive = 0;
  int blackAlive = 0;
  int whiteKingAlive = 0;
  int blackKingAlive = 0;
  for(int i = 0; i < 16; i++){
    whiteAlive |= white[i].alive;
    blackAlive |= black[i].alive;
    if(white[i].name[1] == 'K' && white[i].alive == 0){
      snprintf(errStr, 255, "Black wins!");
      return 1;
    }
    if(black[i].name[1] == 'K' && black[i].alive == 0){
      snprintf(errStr, 255, "White wins!");
      return 1;
    }
  }
  if(whiteAlive == 0){
    snprintf(errStr, 255, "Black wins!");
    return 1;
  }
  if(blackAlive == 0){
    snprintf(errStr, 255, "White wins!");
    return 1;
  }
  return 0;
}