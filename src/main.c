#include "../include/header.h"

int main () {

// initializing piece structs
  typedef struct piece piece;
  piece wP = {}, wR = {}, wN = {}, wB = {}, wQ = {}, wK = {}, bP = {}, bR = {}, bN = {}, bB = {}, bQ = {}, bK = {};
// set piece types (+ = white, - = black, 1 = pawn, 2 = rook, 3 = knight, 4 = bishop, 5 = queen, 6 = king)
  wP.type = 1, wR.type = 2, wN.type = 3, wB.type = 4, wQ.type = 5, wK.type = 6;
  bP.type = -1, bR.type = -2, bN.type = -3, bB.type = -4, bQ.type = -5, bK.type = -6;
// create a null piece to signify empty space
  piece blank = {};
  blank.type = 0;

  int colour;

  piece board [64] = {
//   a   b   c   d   e   f   g   h
    bR, bN, bB, bQ, bK, bB, bN, bR,                         // 8
    bP, bP, bP, bP, bP, bP, bP, bP,                         // 7
    blank, blank, blank, blank, blank, blank, blank, blank, // 6
    blank, blank, blank, blank, blank, blank, blank, blank, // 5
    blank, blank, blank, blank, blank, blank, blank, blank, // 4
    blank, blank, blank, blank, blank, blank, blank, blank, // 3
    wP, wP, wP, wP, wP, wP, wP, wP,                         // 2
    wR, wN, wB, wQ, wK, wB, wN, wR                          // 1
 //  a   b   c   d   e   f   g   h 
  }; 

  typedef struct pieceMove pieceMove;
  pieceMove move;

  printf("Do you want to play as white (1) or black (2)? ");
  scanf("%d", &colour);

  while (1) {

    if (colour == 1) {

      printBoard(board);

    } else {

      printBlackBoard(board);

    }

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

    int currentPosition, destinationPosition;
    moveToCoordinates(move, &currentPosition, &destinationPosition);
  
    piece currentPiece = board[currentPosition];

    doMove(move, currentPiece, board, colour);

  }

  return 0;

}