#define WHITE 1
#define BLACK 0
#define KING_INDEX 7
#define ROOK_LEFT_INDEX 0
#define ROOK_RIGHT_INDEX 1
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
