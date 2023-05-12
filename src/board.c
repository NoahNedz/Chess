#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../includes/board.h"
#include "../includes/pieces.h"
#include "../includes/move.h"

char* dividerDash = "+----+----+----+----+----+----+----+----+";
char* LeterEnd = "   A     B    C    D    E    F    G    H  ";

int printBoard(){
   system("clear -x");
   printf("%s\n", errStr);
   if(turnNum % 2 == 0){
      printf("White's turn\n");
   }
   else{
      printf("Black's turn\n");
   }
   printf("Turn #%d\n",turnNum);
   printf("\n  %s", dividerDash);
   for(int i=0; i < 64; i++){
      if(i%8 == 0){
         if(i != 0) printf("\n  %s", dividerDash);
         printf("\n%d |", 8-(i/8));
      }
      printf("%3s%2s", drawPieces(i), "|");
   }
   printf("\n  %s", dividerDash);
   printf("\n %s", LeterEnd);
   printf("\n");
   return 0;
}
