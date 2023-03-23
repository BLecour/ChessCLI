#include "../include/header.h"

void printBoard (struct piece board[64]) {

  char boardLetter = 'a';
  int boardNum = 8;

  printf("\n\n");

  for (int i = 0; i < 8; i++) {

// print numbers on the left side of board
    printf("%d   ", boardNum);
    boardNum--;

    for (int j = 0; j < 8; j++) {

      printPiece(board[(i*8)+j].type);

    }

    printf("\n");

  }

  printf("\n    ");

// print letters at the bottom of the board
  for (int i = 0; i < 8; i++) {

    printf("%c ", boardLetter);
    boardLetter++;

  }

  printf("\n\n");

}

void printBlackBoard (struct piece board[64]) {

  char boardLetter = 'h';
  int boardNum = 1;

  printf("\n\n");

  for (int i = 7; i >= 0; i--) {

// print numbers on the left side of board
    printf("%d   ", boardNum);
    boardNum++;

    for (int j = 7; j >= 0; j--) {

      printPiece(board[(i*8)+j].type);

    }

    printf("\n");

  }

  printf("\n    ");

// print letters at the bottom of the board
  for (int i = 0; i < 8; i++) {

    printf("%c ", boardLetter);
    boardLetter--;

  }

  printf("\n\n");

}

void printPiece (int num) {

  if (num > 0 && num < 7) {

    printf("\033[0;34m"); // blue

    switch (num) {

      case 6:
        printf("K ");
        break;
    
      case 5:
        printf("Q ");
        break;

      case 4:
        printf("B ");
        break;

      case 3:
        printf("N ");
        break;

      case 2:
        printf("R ");
        break;

      case 1:
        printf("P ");
        break;

    }

  } else if (num < 0 && num > -7) {

    printf("\033[0;31m"); // red

    switch (num) {

      case -6:
        printf("K ");
        break;
    
      case -5:
        printf("Q ");
        break;

      case -4:
        printf("B ");
        break;

      case -3:
        printf("N ");
        break;

      case -2:
        printf("R ");
        break;

      case -1:
        printf("P ");
        break;

    }

  } else if (num == 0) {

    printf("\033[0;37m"); // white

    printf(". ");

  } else {

    printf("Error occured: Piece type (%d) not recognized\n\n", num);
    exit(0);

  }

// default back to white at the end
  printf("\033[0;37m");
  
}

void printPossibleMoves (struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int colour) {

  int currentPosition, destinationPosition;
  moveToSquare(move, &currentPosition, &destinationPosition);

  int possibleMoves[64];
  int possibleCaptures[64];
  char coordinate [5];

  resetArray(possibleMoves, 64);
  resetArray(possibleCaptures, 64);

  int currentType = board[currentPosition].type;

  if (currentType == 1 || currentType == -1) {

    returnPawnCaptures(move, board, previousBoard, possibleCaptures, colour);

    printf("Possible pawn captures are: ");

    for (int i = 0; i < 64; i++) {

      squareToMove(possibleCaptures[i], coordinate);

      printf("%s ", coordinate);

    }

    printf("\n");

    returnPawnMoves(move, board, previousBoard, possibleMoves, colour);

  } else if (currentType == 2 || currentType == -2) {

    returnRookMoves(move, board, previousBoard, possibleMoves, colour);

  } else if (currentType == 3 || currentType == -3) {

    returnKnightMoves(move, board, previousBoard, possibleMoves, colour);

  } else if (currentType == 4 || currentType == -4) {

    returnBishopMoves(move, board, previousBoard, possibleMoves, colour);

  } else if (currentType == 5 || currentType == -5) {

    returnQueenMoves(move, board, previousBoard, possibleMoves, colour);

  } else if (currentType == 6 || currentType == -6) {

    returnKingMoves(move, board, previousBoard, possibleMoves, colour);

  } 

  printf("Possible piece moves are: ");

  for (int i = 0; i < 64; i++) {

    squareToMove(possibleMoves[i], coordinate);

    printf("%s ", coordinate);

  }

  printf("\n");

}

void resetArray(int * array, int len) {

  for (int i = 0; i < len; i++) {

    array[i] = -1;

  }

}