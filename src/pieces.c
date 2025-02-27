#include <stdio.h>
#include <stdlib.h>
#include "../includes/chess.h"
#include <string.h>
piece white[16] = {0};
piece black[16] = {0};
int boardLocationWorth[64] = {
       28,32,34,34,34,34,32,28,
       32,39,43,43,43,43,39,32,
       34,43,49,49,49,49,43,34,
       34,43,49,51,51,49,43,34,
       34,43,49,51,51,49,43,34,
       34,43,49,49,49,49,43,34,
       32,39,43,43,43,43,39,32,
       28,32,34,34,34,34,32,28
};
void initWhite(){
       white[0].color = WHITE;
       white[0].moveCount = 0;
       white[0].location = 56;
       white[0].alive = 1;
       white[0].value = 5;
       strncpy (white[ROOK_LEFT_INDEX].name, "Wr", sizeof(white[0].name));

       white[1].color = WHITE;
       white[1].moveCount = 0;
       white[1].location = 63;
       white[1].alive = 1;
       white[1].value = 5;
       strncpy (white[ROOK_RIGHT_INDEX].name, "Wr", sizeof(white[1].name));

       white[2].color = WHITE;
       white[2].moveCount = 0;
       white[2].location = 57;
       white[2].alive = 1;
       white[2].value = 3;
       strncpy (white[2].name, "Wk", sizeof(white[2].name));

       white[3].color = WHITE;
       white[3].moveCount = 0;
       white[3].location = 62;
       white[3].alive = 1;
       white[3].value = 3;
       strncpy (white[3].name, "Wk", sizeof(white[3].name));

       white[4].color = WHITE;
       white [4].moveCount = 0;
       white[4].location = 58;
       white[4].alive = 1;
       white[4].value = 3;
       strncpy (white[4].name, "Wb", sizeof(white[4].name));

       white[5].color = WHITE;
       white[5].moveCount = 0;
       white[5].location = 61;
       white[5].alive = 1;
       white[5].value = 3;
       strncpy (white[5].name, "Wb", sizeof(white[5].name));

       white[6].color = WHITE;
       white[6].moveCount = 0;
       white[6].location = 59;
       white[6].alive = 1;
       white[6].value = 9;
       strncpy (white[6].name, "WQ", sizeof(white[6].name));

       white[7].color = WHITE;
       white[7].moveCount = 0;
       white[7].location = 60;
       white[7].alive = 1;
       white[7].value = 999;
       strncpy (white[KING_INDEX].name, "WK", sizeof(white[7].name));



       ////////////////////pawns

       white[8].color = WHITE;
       white[8].moveCount = 0;
       white[8].location = 48;
       white[8].alive = 1;
       white[8].value = 1;
       strncpy (white[8].name, "Wp", sizeof(white[8].name));


       white[9].color = WHITE;
       white[9].moveCount = 0;
       white[9].location = 49;
       white[9].alive = 1;
       white[9].value = 1;
       strncpy (white[9].name, "Wp", sizeof(white[9].name));


       white[10].color = WHITE;
       white[10].moveCount = 0;
       white[10].location = 50;
       white[10].alive = 1;
       white[10].value = 1;
       strncpy (white[10].name, "Wp", sizeof(white[10].name));       


       white[11].color = WHITE;
       white[11].moveCount = 0;
       white[11].location = 51;
       white[11].alive = 1;
       white[11].value = 1;
       strncpy (white[11].name, "Wp", sizeof(white[11].name));


       white[12].color = WHITE;
       white[12].moveCount = 0;
       white[12].location = 52;
       white[12].alive = 1;
       white[12].value = 1;
       strncpy (white[12].name, "Wp", sizeof(white[12].name));

              
       white[13].color = WHITE;
       white[13].moveCount = 0;
       white[13].location = 53;
       white[13].alive = 1;
       white[13].value = 1;
       strncpy (white[13].name, "Wp", sizeof(white[13].name));

       white[14].color = WHITE;
       white[14].moveCount = 0;
       white[14].location = 54;
       white[14].alive = 1;
       white[14].value = 1;
       strncpy (white[14].name, "Wp", sizeof(white[14].name));  


       white[15].color = 1,
       white[15].moveCount = 0,
       white[15].location = 55,
       white[15].alive = 1,
       white[15].value = 1;
       strncpy (white[15].name, "Wp", sizeof(white[15].name));
       
       return;
}
void initBlack(){
	black[0].color = BLACK;
	black[0].moveCount = 0;
	black[0].location = 0;
	black[0].alive = 1;
       black[0].value = 5;
       strncpy (black[ROOK_LEFT_INDEX].name, "Br", sizeof(black[0].name));

	black[1].color = BLACK;
	black[1].moveCount = 0;
	black[1].location = 7;
	black[1].alive = 1;
       black[1].value = 5;
       strncpy (black[ROOK_RIGHT_INDEX].name, "Br", sizeof(black[1].name));

	black[2].color = BLACK;
	black[2].moveCount = 0;
	black[2].location = 1;
	black[2].alive = 1;
       black[2].value = 3;
       strncpy (black[2].name, "Bk", sizeof(black[2].name));

	black[3].color = BLACK;
	black[3].moveCount = 0;
	black[3].location = 6;
	black[3].alive = 1;
       black[3].value = 3;
       strncpy (black[3].name, "Bk", sizeof(black[3].name));

	black[4].color = BLACK;
	black[4].moveCount = 0;
	black[4].location = 2;
	black[4].alive = 1;
       black[4].value = 3;
       strncpy (black[4].name, "Bb", sizeof(black[4].name));

	black[5].color = BLACK;
	black[5].moveCount = 0;
	black[5].location = 5;
	black[5].alive = 1;
       black[5].value = 3;
       strncpy (black[5].name, "Bb", sizeof(black[5].name));

       black[6].color = BLACK;
	black[6].moveCount = 0;
	black[6].location = 3;
	black[6].alive = 1;
       black[6].value = 9;
       strncpy (black[6].name, "BQ", sizeof(black[6].name));

	black[7].color = BLACK;
	black[7].moveCount = 0;
	black[7].location = 4;
	black[7].alive = 1;
       black[7].value = 999;
       strncpy (black[KING_INDEX].name, "BK", sizeof(black[7].name));



	////////////////////pawns

	black[8].color = BLACK;
	black[8].moveCount = 0;
	black[8].location = 8;
	black[8].alive = 1;
       black[8].value = 1;
       strncpy (black[8].name, "Bp", sizeof(black[8].name));


	black[9].color = BLACK;
	black[9].moveCount = 0;
	black[9].location = 9;
	black[9].alive = 1;
       black[9].value = 1;
       strncpy (black[9].name, "Bp", sizeof(black[9].name));


	black[10].color = BLACK;
	black[10].moveCount = 0;
	black[10].location = 10;
	black[10].alive = 1;
       black[10].value = 1;
       strncpy (black[10].name, "Bp", sizeof(black[10].name));      


	black[11].color = BLACK;
	black[11].moveCount = 0;
	black[11].location = 11;
	black[11].alive = 1;
       black[11].value = 1;
       strncpy (black[11].name, "Bp", sizeof(black[11].name));


	black[12].color = BLACK;
	black[12].moveCount = 0;
	black[12].location = 12;
	black[12].alive = 1;
       black[12].value = 1;
       strncpy (black[12].name, "Bp", sizeof(black[12].name));

	  
	black[13].color = BLACK;
	black[13].moveCount = 0;
	black[13].location = 13;
	black[13].alive = 1;
       black[13].value = 1;
       strncpy (black[13].name, "Bp", sizeof(black[13].name));


	black[14].color = BLACK;
	black[14].moveCount = 0;
	black[14].location = 14;
	black[14].alive = 1;
       black[14].value = 1;
       strncpy (black[14].name, "Bp", sizeof(black[14].name)); 


	black[15].color = BLACK;
	black[15].moveCount = 0;
	black[15].location = 15;
	black[15].alive = 1;
       black[15].value = 1;
       strncpy (black[15].name, "Bp", sizeof(black[15].name));

       return;
}

char* drawPiece(int position){
   for(int i=0; i < 16; i++){
      if(white[i].location == position && white[i].alive){
         return white[i].name;
      }
      if(black[i].location == position && black[i].alive){
         return black[i].name;
      }
   }
   return "  ";
}





