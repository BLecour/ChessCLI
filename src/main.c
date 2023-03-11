#include "../include/header.h"

int main () {

// initializing piece structs
  typedef struct piece piece;
  piece wP0 = {}, wP1 = {}, wP2 = {}, wP3 = {}, wP4 = {}, wP5 = {}, wP6 = {}, wP7 = {}, wR0 = {}, wR1 = {}, wN0 = {}, wN1 = {}, wB0 = {}, wB1 = {}, wQ = {}, wK = {}, bP0 = {}, bP1 = {}, bP2 = {}, bP3 = {}, bP4 = {}, bP5 = {}, bP6 = {}, bP7 = {}, bR0 = {}, bR1 = {}, bN0 = {}, bN1 = {}, bB0 = {}, bB1 = {}, bQ = {}, bK = {};
// set piece types (+ = white, - = black, 1 = pawn, 2 = rook, 3 = knight, 4 = bishop, 5 = queen, 6 = king)
  wP0.type = 1, wP1.type = 1, wP2.type = 1, wP3.type = 1, wP4.type = 1, wP5.type = 1, wP6.type = 1, wP7.type = 1, wR0.type = 2, wR1.type = 2, wN0.type = 3, wN1.type = 3, wB0.type = 4, wB1.type = 4, wQ.type = 5, wK.type = 6;
  bP0.type = -1, bP1.type = -1, bP2.type = -1, bP3.type = -1, bP4.type = -1, bP5.type = -1, bP6.type = -1, bP7.type = -1, bR0.type = -2, bR1.type = -2, bN0.type = -3, bN1.type = -3, bB0.type = -4, bB1.type = -4, bQ.type = -5, bK.type = -6;
// create a null piece to signify empty space
  piece blank = {};
  blank.type = 0;

  int colour;

  piece board[8][8] = {
//    a    b    c   d   e    f    g    h
    {bR0, bN0, bB0, bQ, bK, bB1, bN1, bR1},                           // 8
    {bP0, bP1, bP2, bP3, bP4, bP5, bP6, bP7},                         // 7
    {blank, blank, blank, blank, blank, blank, blank, blank},         // 6
    {blank, blank, blank, blank, blank, blank, blank, blank},         // 5
    {blank, blank, blank, blank, blank, blank, blank, blank},         // 4
    {blank, blank, blank, blank, blank, blank, blank, blank},         // 3
    {wP0, wP1, wP2, wP3, wP4, wP5, wP6, wP7},                         // 2
    {wR0, wN0, wB0, wQ, wK, wB1, wN1, wR1}                            // 1
 //   a    b    c   d   e    f    g    h 
  }; 

  typedef struct pieceMove pieceMove;
  pieceMove move;

  printf("Do you want to play as white (1) or black (2)? ");
  scanf("%d", &colour);

  if (colour == 1) {
    printBoard(board);
  } else {
    printBlackBoard(board);
  }

  while (1) {

    printf("Enter the coordinates of the piece you want to move: ");
    scanf(" %s", move.current);

    printf("Enter where you want to move the piece: ");
    scanf(" %s", move.destination);

    while (isMoveValid(move, board, colour) != 1) {

      printf("Not a valid move. Enter the coordinates of the piece you want to move: ");
      scanf(" %s", move.current);
      printf("Enter where you want to move the piece: ");
      scanf(" %s", move.destination);

    }

    doMove(move, board, colour);

  }

  return 0;

}