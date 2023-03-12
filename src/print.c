#include "../include/header.h"

void printBoard (struct piece board[8][8]) {

  char boardLetter = 'a';
  int boardNum = 8;

  printf("\n\n");

  for (int i = 0; i < 8; i++) {

// print numbers on the left side of board
    printf("%d   ", boardNum);
    boardNum--;

    for (int j = 0; j < 8; j++) {

      printPiece(board[i][j].type);

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

void printBlackBoard (struct piece board[8][8]) {

  char boardLetter = 'h';
  int boardNum = 1;

  printf("\n\n");

  for (int i = 7; i >= 0; i--) {

// print numbers on the left side of board
    printf("%d   ", boardNum);
    boardNum++;

    for (int j = 7; j >= 0; j--) {

      printPiece(board[i][j].type);

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

  if (num > 0) {

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

  } else if (num < 0) {

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

  } else {

    printf("\033[0;37m"); // white

    printf(". ");

  }

// default back to white at the end
  printf("\033[0;37m");
  
}