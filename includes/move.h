#ifndef MOVE_GUARD
#define MOVE_GUARD

#define RESET_BOARD_TRUE 1
#define RESET_BOARD_FALSE 0

typedef struct move {
    int startPosition;
    int endPosition;
}move;

int validateMove(int startPosition, int endPosition, int checkBool, int turnColor);
int convertUserInput(char* inputString);
int translateToRow(int position);
int translateToColumn(int position);
int checkWinCondition();
int checkMateCheck(int turnColor);
void findBestMove(int turnColor, move* movePointer, int depth, int depthI);
#endif