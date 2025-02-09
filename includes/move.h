#ifndef MOVE_GUARD
#define MOVE_GUARD

int validateMove(int startPosition, int endPosition, int checkBool, int turnColor);
int convertUserInput(char* inputString);
int translateToRow(int position);
int translateToColumn(int position);
int checkWinCondition();
int checkMateCheck(int turnColor);
void findBestMove(int turnColor);
#endif