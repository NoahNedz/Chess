typedef struct piece{
   int color;
   int moveCount;
   int location;
   int alive;
   char name[3];
}piece;

piece white[16];
piece black[16];
void initBlack();
void initWhite();
char* findPiece(int position);
