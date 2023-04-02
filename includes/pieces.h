#define WHITE 1
#define BLACK 0
#define KING_INDEX 6
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
char* drawPieces(int position);
