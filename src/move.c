#include "../include/header.h"

int isMoveValid (struct pieceMove move, struct piece board[8][8], int colour) {

  int currentPositionX, currentPositionY, destinationPositionX, destinationPositionY;
  moveToCoordinates(move, &currentPositionX, &currentPositionY, &destinationPositionX, &destinationPositionY);

// if player is trying to move other player's pieces
  if ((board[currentPositionX][currentPositionY].type > 0 && colour == 2) || (board[currentPositionX][currentPositionY].type < 0 && colour == 1)) {

    return 0;

  }

  if (currentPositionX > 8 || currentPositionX < 0 || currentPositionY > 8 || currentPositionY < 0 || destinationPositionX > 8 || destinationPositionX < 0 || destinationPositionY > 8 || destinationPositionY < 0) {

    return 0;

  }

  int currentType = board[currentPositionX][currentPositionY].type;

// check if move is for a pawn
  if (currentType == 1 || currentType == -1) {

    return isPawnMoveValid(move, board, colour);

  } else if (currentType == 2 || currentType == -2) {

    return isRookMoveValid(move, board, colour);

  } else if (currentType == 3 || currentType == -3) {

    return isKnightMoveValid(move, board, colour);

  } else if (currentType == 4 || currentType == -4) {

    return isBishopMoveValid(move, board, colour);

  } else if (currentType == 5 || currentType == -5) {

    return isQueenMoveValid(move, board, colour);

  } else if (currentType == 6 || currentType == -6) {

    return isKingMoveValid(move, board, colour);

  }

  return 0;

}

int isPawnMoveValid (struct pieceMove move, struct piece board[8][8], int colour) {

// convert chars to integers to use on the 2D board array
  int currentPositionX, currentPositionY, destinationPositionX, destinationPositionY;
  moveToCoordinates(move, &currentPositionX, &currentPositionY, &destinationPositionX, &destinationPositionY);
  
  int verticalDistance = abs(currentPositionX - destinationPositionX);
  int horizontalDistance = abs(currentPositionY - destinationPositionY);

  printf("row = %d column = %d\n", currentPositionX, currentPositionY);

  printf("the type at this position is %d\n", board[currentPositionX][currentPositionY].type);

  if ((board[currentPositionX][currentPositionY].type != 1 && colour == 1) || (board[currentPositionX][currentPositionY].type != -1 && colour == 2)) {
// piece at current position is NOT a pawn, move is not valid
    return 0;

  }

   if (verticalDistance == 1 && horizontalDistance == 1 && board[destinationPositionX][destinationPositionY].type != 0) {

    return 1;

  }

  if (board[destinationPositionX][destinationPositionY].type != 0) {
// if there is already a piece at the destination, move is not valid

    return 0;

  }

  printf("Destination is at row = %d column = %d\n", destinationPositionX, destinationPositionY);

// pawns can't move more than 2 spaces at once
  if (verticalDistance > 2) {

    return 0;

  } else if (verticalDistance == 2 && board[currentPositionX][currentPositionY].moves != 0) {
// pawns can't move 2 spaces if they have already moved
      
    return 0;

  }

// pawn cannot capture straight on/ or land capture his colour's pieces
  if (verticalDistance == 1 && horizontalDistance == 0 && board[destinationPositionX][destinationPositionY].type != 0) {

    return 0;

// if moving 2 squares, pawn also cannot jump over pieces (for white)
  } else if (verticalDistance == 2 && horizontalDistance == 0 && (board[currentPositionX-1][currentPositionY].type != 0 || board[destinationPositionX][destinationPositionY].type != 0) && colour == 1) {

    return 0;

// if moving 2 squares, pawn also cannot jump over pieces (for black)
  } else if (verticalDistance == 2 && horizontalDistance == 0 && (board[currentPositionX+1][currentPositionY].type != 0 || board[destinationPositionX][destinationPositionY].type != 0) && colour == 2) {

    return 0;

  }

  printf("Pawn is at (%d,%d) and wants to check (%d,%d)\n", currentPositionX, currentPositionY, currentPositionX-1, currentPositionY);

  return 1;

}

int isRookMoveValid (struct pieceMove move, struct piece board[8][8], int colour) {

  int currentPositionX, currentPositionY, destinationPositionX, destinationPositionY;
  moveToCoordinates(move, &currentPositionX, &currentPositionY, &destinationPositionX, &destinationPositionY);

  if ((board[currentPositionX][currentPositionY].type != 2 && colour == 1) || (board[currentPositionX][currentPositionY].type != -2 && colour == 2)) {
// piece at current position is NOT a rook, move is not valid
    return 0;

  }

  
  return 1;

}

int isKnightMoveValid (struct pieceMove move, struct piece board[8][8], int colour) {

  int currentPositionX, currentPositionY, destinationPositionX, destinationPositionY;
  moveToCoordinates(move, &currentPositionX, &currentPositionY, &destinationPositionX, &destinationPositionY);
  
  int verticalDistance = abs(currentPositionX - destinationPositionX);
  int horizontalDistance = abs(currentPositionY - destinationPositionY);

// piece at current position is NOT a knight, move is not valid
  if ((board[currentPositionX][currentPositionY].type != 3 && colour == 1) || (board[currentPositionX][currentPositionY].type != -3 && colour == 2)) {

    return 0;

  }

// if move is not an L shape, move is not valid
  if (!((horizontalDistance == 2 && verticalDistance == 1) || (horizontalDistance == 1 && verticalDistance == 2))) {

    return 0;

  }

  if ((board[destinationPositionX][destinationPositionY].type > 0 && colour == 1) ||  (board[destinationPositionX][destinationPositionY].type < 0 && colour == 2)) {

    return 0;

  }

  return 1;

}

int isBishopMoveValid (struct pieceMove move, struct piece board[8][8], int colour) {

  int currentPositionX, currentPositionY, destinationPositionX, destinationPositionY;
  moveToCoordinates(move, &currentPositionX, &currentPositionY, &destinationPositionX, &destinationPositionY);

  if ((board[currentPositionX][currentPositionY].type != 4 && colour == 1) || (board[currentPositionX][currentPositionY].type != -4 && colour == 2)) {
// piece at current position is NOT a knight, move is not valid
    return 0;

  }
  
  return 1;
}

int isQueenMoveValid (struct pieceMove move, struct piece board[8][8], int colour) {

  int currentPositionX, currentPositionY, destinationPositionX, destinationPositionY;
  moveToCoordinates(move, &currentPositionX, &currentPositionY, &destinationPositionX, &destinationPositionY);

  if ((board[currentPositionX][currentPositionY].type != 5 && colour == 1) || (board[currentPositionX][currentPositionY].type != -5 && colour == 2)) {
// piece at current position is NOT a queen, move is not valid
    return 0;

  }
  
  return 1;

}

int isKingMoveValid (struct pieceMove move, struct piece board[8][8], int colour) {

  int currentPositionX, currentPositionY, destinationPositionX, destinationPositionY;
  moveToCoordinates(move, &currentPositionX, &currentPositionY, &destinationPositionX, &destinationPositionY);

  if ((board[currentPositionX][currentPositionY].type != 6 && colour == 1) || (board[currentPositionX][currentPositionY].type != -6 && colour == 2)) {
// piece at current position is NOT a knight, move is not valid
    return 0;

  }
  
  return 1;

}

void doMove (struct pieceMove move, struct piece movedPiece, struct piece board[8][8], int colour) {

  int currentPositionX, currentPositionY, destinationPositionX, destinationPositionY;
  moveToCoordinates(move, &currentPositionX, &currentPositionY, &destinationPositionX, &destinationPositionY);
  
// create a null piece to signify empty space
  typedef struct piece piece;
  piece blank = {};
  blank.type = 0;

  movedPiece.moves++;

  board[currentPositionX][currentPositionY] = blank;
  board[destinationPositionX][destinationPositionY] = movedPiece;

}

void moveToCoordinates (struct pieceMove move, int * currentPositionX, int * currentPositionY, int * destinationPositionX, int * destinationPositionY) {

    switch (move.current[0]) {

    case 'a':
      * currentPositionY = 0;
      break;

    case 'b':
      * currentPositionY = 1;
      break;

    case 'c':
      * currentPositionY = 2;
      break;

    case 'd':
      * currentPositionY = 3;
      break;

    case 'e':
      * currentPositionY = 4;
      break;

    case 'f':
      * currentPositionY = 5;
      break;

    case 'g':
      * currentPositionY = 6;
      break;

    case 'h':
      * currentPositionY = 7;
      break;

    default:
      * currentPositionY = -1;


  }

  switch (move.current[1]) {

    case '1':
      * currentPositionX = 7;
      break;

    case '2':
      * currentPositionX = 6;
      break;

    case '3':
      * currentPositionX = 5;
      break;

    case '4':
      * currentPositionX = 4;
      break;

    case '5':
      * currentPositionX = 3;
      break;

    case '6':
      * currentPositionX = 2;
      break;

    case '7':
      * currentPositionX = 1;
      break;

    case '8':
      * currentPositionX = 0;
      break;

    default:
      * currentPositionX = -1;

  }

  switch (move.destination[0]) {

    case 'a':
      * destinationPositionY = 0;
      break;

    case 'b':
      * destinationPositionY = 1;
      break;

    case 'c':
      * destinationPositionY = 2;
      break;

    case 'd':
      * destinationPositionY = 3;
      break;

    case 'e':
      * destinationPositionY = 4;
      break;

    case 'f':
      * destinationPositionY = 5;
      break;

    case 'g':
      * destinationPositionY = 6;
      break;

    case 'h':
      * destinationPositionY = 7;
      break;

    default:
      * destinationPositionY = -1;

  }

  switch (move.destination[1]) {

    case '1':
      * destinationPositionX = 7;
      break;

    case '2':
      * destinationPositionX = 6;
      break;

    case '3':
      * destinationPositionX = 5;
      break;

    case '4':
      * destinationPositionX = 4;
      break;

    case '5':
      * destinationPositionX = 3;
      break;

    case '6':
      * destinationPositionX = 2;
      break;

    case '7':
      * destinationPositionX = 1;
      break;

    case '8':
      * destinationPositionX = 0;
      break;

    default:
      * destinationPositionX = -1;

  }


}