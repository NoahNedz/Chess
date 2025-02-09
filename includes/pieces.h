#ifndef PIECES_GUARD
#define PIECES_GUARD

typedef struct piece{
   int color;
   int moveCount;
   int location;
   int alive;
   int value;
   char name[3];
}piece;

extern piece white[16];
extern piece black[16];
extern int boardLocationWorth[64];

void initBlack();
void initWhite();
char* drawPiece(int position);
#endif