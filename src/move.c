#include "../include/header.h"

int isMoveValid (struct pieceMove move, struct piece board[8][8], int colour) {

  char firstLetterOfMove = move.current[0];

// check if move is for a pawn
  if (firstLetterOfMove == 'a' || firstLetterOfMove == 'b' || firstLetterOfMove == 'c' || firstLetterOfMove == 'd' || firstLetterOfMove == 'e' || firstLetterOfMove == 'f' || firstLetterOfMove == 'g' || firstLetterOfMove == 'h') {

    return isPawnMoveValid(move, board, colour);

  } else if (firstLetterOfMove == 'R') {

    return isRookMoveValid(move, board, colour);

  } else if (firstLetterOfMove == 'N') {

    return isKnightMoveValid(move, board, colour);

  } else if (firstLetterOfMove == 'B') {

    return isBishopMoveValid(move, board, colour);

  } else if (firstLetterOfMove == 'Q') {

    return isQueenMoveValid(move, board, colour);

  } else if (firstLetterOfMove == 'K') {

    return isKingMoveValid(move, board, colour);

  }

  return 0;

}

int isPawnMoveValid (struct pieceMove move, struct piece board[8][8], int colour) {

// convert chars to integers to use on the 2D board array
  int currentPositionX = moveToPositionX(move.current), currentPositionY = moveToPositionY(move.current);
  int destinationPositionX = moveToPositionX(move.destination), destinationPositionY = moveToPositionY(move.destination);

  printf("row = %d column = %d\n", currentPositionX, currentPositionY);

  printf("the type at this position is %d\n", board[currentPositionX][currentPositionY].type);

  if (colour == 1) {
// white pieces

    if (board[currentPositionX][currentPositionY].type != 1) {
// piece at current position is NOT a pawn, move is not valid
      return 0;

    }

    if (board[destinationPositionX][destinationPositionY].type != 0) {
// if there is already a piece at the destination, move is not valid

      return 0;

    }

    printf("Destination is at row = %d column = %d\n", destinationPositionX, destinationPositionY);

    int distance = currentPositionX - destinationPositionX;

// pawns can't move more than 2 spaces at once
    if (distance > 2) {

      return 0;

    } else if (distance == 2 && board[currentPositionX][currentPositionY].moves != 0) {

      

    }



    


  } else {
// black pieces

    if (board[currentPositionX][currentPositionY].type != -1) {

      return 0;

    }

  }

  return 1;

}

int isRookMoveValid (struct pieceMove move, struct piece board[8][8], int colour) {

  return 0;

}

int isKnightMoveValid (struct pieceMove move, struct piece board[8][8], int colour) {

  return 0;

}

int isBishopMoveValid (struct pieceMove move, struct piece board[8][8], int colour) {

  return 0;

}

int isQueenMoveValid (struct pieceMove move, struct piece board[8][8], int colour) {

  return 0;

}

int isKingMoveValid (struct pieceMove move, struct piece board[8][8], int colour) {

  return 0;

}

void doMove (struct pieceMove move, struct piece board[8][8], int colour) {

}

int moveToPositionX (char coordinate [2]) {

  switch (coordinate[1]) {

    case '1':
      return 7;
      break;

    case '2':
      return 6;
      break;

    case '3':
      return 5;
      break;

    case '4':
      return 4;
      break;

    case '5':
      return 3;
      break;

    case '6':
      return 2;
      break;

    case '7':
      return 1;
      break;

    case '8':
      return 0;
      break;

  }

  return -1;

}

int moveToPositionY (char coordinate [2]) {

  switch (coordinate[0]) {

    case 'a':
      return 0;
      break;

    case 'b':
      return 1;
      break;

    case 'c':
      return 2;
      break;

    case 'd':
      return 3;
      break;

    case 'e':
      return 4;
      break;

    case 'f':
      return 5;
      break;

    case 'g':
      return 6;
      break;

    case 'h':
      return 7;
      break;

  }

  return -1;

}