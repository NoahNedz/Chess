#define WHITE 1
#define BLACK 0

#define UP 0
#define UPRIGHT 1
#define RIGHT 2
#define DOWNRIGHT 3
#define DOWN 4
#define DOWNLEFT 5
#define LEFT 6
#define UPLEFT 7

int validateMove(int startPosition, int endPosition);
int convertUserInput(char* inputString);
int translateToRow(int position);
int translateToColumn(int position);
int checkWinCondition();


