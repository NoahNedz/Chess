#ifndef CHESS_GUARD
#define CHESS_GUARD

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

#define KING_INDEX 7
#define ROOK_LEFT_INDEX 0
#define ROOK_RIGHT_INDEX 1

#define JUST_CHECK_TRUE 1
#define JUST_CHECK_FALSE 0

extern char errStr[256];
extern int turnNum;
int getTurnColor(int turnNum);
#endif

#include "display.h"
#include "move.h"
#include "pieces.h"