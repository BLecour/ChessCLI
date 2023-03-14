#include "../include/header.h"

int isMoveValid (struct pieceMove move, struct piece board[64], int colour) {

  int currentPosition, destinationPosition;
  moveToCoordinates(move, &currentPosition, &destinationPosition);

// if player is trying to move other player's pieces
  if ((board[currentPosition].type > 0 && colour == 2) || (board[currentPosition].type < 0 && colour == 1)) {

    printf("currentPosition (%d) or destinationPosition (%d) is trying to move other player's pieces\n", currentPosition, destinationPosition);

    return 0;

  }

// if move is out of bounds
  if (currentPosition < 0 || destinationPosition < 0) {

    printf("currentPosition (%d) or destinationPosition (%d) is out of bounds\n", currentPosition, destinationPosition);

    return 0;

  }

// can't move to its current spot
  if (strcmp(move.current, move.destination) == 0) {

    printf("currentPosition (%d) or destinationPosition (%d) is trying to move to its current location\n", currentPosition, destinationPosition);

    return 0;

  }

  int currentType = board[currentPosition].type;

  printf("current type at %d is %d\n", currentPosition, board[currentPosition].type);

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

int isPawnMoveValid (struct pieceMove move, struct piece board[64], int colour) {

// convert chars to integers to use on the 2D board array
  int currentPosition, destinationPosition;
  moveToCoordinates(move, &currentPosition, &destinationPosition);

  int distance = currentPosition-destinationPosition;

  printf("currentPosition = %d  destinationPosition = %d\n", currentPosition, destinationPosition);

  printf("the type at this position is %d\n", board[currentPosition].type);

// check if pawn can take another piece
  if ((distance == 7 && board[destinationPosition].type < 0 && colour == 1) || (distance == 9 && board[destinationPosition].type < 0 && colour == 1) || (distance == -7 && board[destinationPosition].type > 0 && colour == 2) || (distance == -9 && board[destinationPosition].type > 0 && colour == 2)) {

    return 1;

  }

  if (board[destinationPosition].type != 0) {
// if there is already a piece at the destination, move is not valid

    return 0;

  }

// pawns can't move more than 2 spaces at once
  if (distance != 8 && distance != 16) {

    return 0;

  } else if (abs(distance) == 16 && board[currentPosition].moves != 0) {
// pawns can't move 2 spaces if they have already moved
      
    return 0;

  }

// pawn cannot capture straight on/ or land capture his colour's pieces
  if (abs(distance) == 8 && board[destinationPosition].type != 0) {

    return 0;

// if moving 2 squares, pawn also cannot jump over pieces (for white)
  } else if (abs(distance) == 16 && (board[currentPosition-8].type != 0 || board[currentPosition-16].type != 0) && colour == 1) {

    return 0;

// if moving 2 squares, pawn also cannot jump over pieces (for black)
  } else if (abs(distance) == 16 && (board[currentPosition+8].type != 0 || board[currentPosition+16].type != 0) && colour == 2) {

    return 0;

  }

  return 1;

}

int isRookMoveValid (struct pieceMove move, struct piece board[64], int colour) {

  int currentPosition, destinationPosition;
  moveToCoordinates(move, &currentPosition, &destinationPosition);

// must be either moving horizontally or vertically, not both or neither (XOR)
/*
  if ((horizontalDistance != 0) == (verticalDistance != 0)) {

    return 0;

  }
*/

  return 1;

}

int isKnightMoveValid (struct pieceMove move, struct piece board[64], int colour) {

  int currentPosition, destinationPosition;
  moveToCoordinates(move, &currentPosition, &destinationPosition);

/*
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
*/
  return 1;

}

int isBishopMoveValid (struct pieceMove move, struct piece board[64], int colour) {

  int currentPosition, destinationPosition;
  moveToCoordinates(move, &currentPosition, &destinationPosition);

  return 1;
}

int isQueenMoveValid (struct pieceMove move, struct piece board[64], int colour) {

  int currentPosition, destinationPosition;
  moveToCoordinates(move, &currentPosition, &destinationPosition);

  return 1;

}

int isKingMoveValid (struct pieceMove move, struct piece board[64], int colour) {

  int currentPosition, destinationPosition;
  moveToCoordinates(move, &currentPosition, &destinationPosition);

  return 1;

}

void doMove (struct pieceMove move, struct piece movedPiece, struct piece board[64], int colour) {

  int currentPosition, destinationPosition;
  moveToCoordinates(move, &currentPosition, &destinationPosition);
  
// create a null piece to signify empty space
  typedef struct piece piece;
  piece blank = {};
  blank.type = 0;

  movedPiece.moves++;

  board[currentPosition] = blank;
  board[destinationPosition] = movedPiece;

}

void moveToCoordinates (struct pieceMove move, int * currentPosition, int * destinationPosition) {

    switch (move.current[1]) {

    case '1':
      * currentPosition = 56;
      break;

    case '2':
      * currentPosition = 48;
      break;

    case '3':
      * currentPosition = 40;
      break;

    case '4':
      * currentPosition = 32;
      break;

    case '5':
      * currentPosition = 24;
      break;

    case '6':
      * currentPosition = 16;
      break;

    case '7':
      * currentPosition = 8;
      break;

    case '8':
      * currentPosition = 0;
      break;

    default:
      * currentPosition = -1;

  }

      switch (move.current[0]) {

    case 'a':
      * currentPosition += 0;
      break;

    case 'b':
      * currentPosition += 1;
      break;

    case 'c':
      * currentPosition += 2;
      break;

    case 'd':
      * currentPosition += 3;
      break;

    case 'e':
      * currentPosition += 4;
      break;

    case 'f':
      * currentPosition += 5;
      break;

    case 'g':
      * currentPosition += 6;
      break;

    case 'h':
      * currentPosition += 7;
      break;

    default:
      * currentPosition = -1;

  }


    switch (move.destination[1]) {

    case '1':
      * destinationPosition = 56;
      break;

    case '2':
      * destinationPosition = 48;
      break;

    case '3':
      * destinationPosition = 40;
      break;

    case '4':
      * destinationPosition = 32;
      break;

    case '5':
      * destinationPosition = 24;
      break;

    case '6':
      * destinationPosition = 16;
      break;

    case '7':
      * destinationPosition = 8;
      break;

    case '8':
      * destinationPosition = 0;
      break;

    default:
      * destinationPosition = -1;

  }

      switch (move.destination[0]) {

    case 'a':
      * destinationPosition += 0;
      break;

    case 'b':
      * destinationPosition += 1;
      break;

    case 'c':
      * destinationPosition += 2;
      break;

    case 'd':
      * destinationPosition += 3;
      break;

    case 'e':
      * destinationPosition += 4;
      break;

    case 'f':
      * destinationPosition += 5;
      break;

    case 'g':
      * destinationPosition += 6;
      break;

    case 'h':
      * destinationPosition += 7;
      break;

    default:
      * destinationPosition = -1;

  }
}