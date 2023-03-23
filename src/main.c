#include "../include/header.h"

int main () {

  srand(time(NULL));

// initializing piece structs
  typedef struct piece piece;
  piece wP = {}, wR = {}, wN = {}, wB = {}, wQ = {}, wK = {}, bP = {}, bR = {}, bN = {}, bB = {}, bQ = {}, bK = {};
// set piece types (+ = white, - = black, 1 = pawn, 2 = rook, 3 = knight, 4 = bishop, 5 = queen, 6 = king)
  wP.type = 1, wR.type = 2, wN.type = 3, wB.type = 4, wQ.type = 5, wK.type = 6;
  bP.type = -1, bR.type = -2, bN.type = -3, bB.type = -4, bQ.type = -5, bK.type = -6;
// create a null piece to signify empty space
  piece blank = {};
  blank.type = 0;

  int mySquares[16];
  int enemySquares[16];

  int colour, opponentColour, currentPosition, destinationPosition;

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

  piece previousBoard [64] = {0};

  typedef struct pieceMove pieceMove;
  pieceMove move;

  printf("Do you want to play as white (1) or black (2)? ");
  scanf("%d", &colour);

  if (colour == 1) {

    opponentColour = 2;

  } else {

    opponentColour = 1;

  }

  while (1) {

    if (colour == 1) {

      printf("CURRENT BOARD:\n");
      printBoard(board);
      printf("PREVIOUS BOARD:\n");
      printBoard(previousBoard);

    } else {

      printBlackBoard(board);

    }

    move.destination[0] = '0';

    while (move.destination[0] == '0') {

// if user enters more than 2 characters then it creates a memory error where it changes board[0].type
      printf("Enter the coordinates of the piece you want to move: ");
      scanf(" %s", move.current);
    
      printPossibleMoves(move, board, previousBoard, colour);

      printf("Enter where you want to move the piece (or enter 0 to restart): ");
      scanf(" %s", move.destination);

      if (move.destination[0] != '0') {

        while ((strlen(move.current) != 2) || (strlen(move.destination) != 2) || (isMoveValid(move, board, previousBoard, colour) != 1)) {

          printf("Not a valid move. Enter the coordinates of the piece you want to move: ");
          scanf(" %s", move.current);
          printf("Enter where you want to move the piece (or enter 0 to restart): ");
          scanf(" %s", move.destination);

        }

      }

    }

    moveToSquare(move, &currentPosition, &destinationPosition);

    piece currentPiece = board[currentPosition];

    doMove(move, currentPiece, board, previousBoard, colour);

// enemy turn

    if (colour == 1) {

      returnWhiteOccupiedSquares(board, mySquares);
      returnBlackOccupiedSquares(board, enemySquares);

    } else {

      returnWhiteOccupiedSquares(board, enemySquares);
      returnBlackOccupiedSquares(board, mySquares);

    }

    enemyDoRandomMove(board, previousBoard, enemySquares, opponentColour);

  }

  return 0;

}