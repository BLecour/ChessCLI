#include "../include/header.h"

void fenDecode (struct piece board[64], struct piece previousBoard[64], char FEN[100], int * turn) {

// initializing piece structs
  typedef struct piece piece;
  piece wP = {}, wR = {}, wN = {}, wB = {}, wQ = {}, wK = {}, bP = {}, bR = {}, bN = {}, bB = {}, bQ = {}, bK = {};
// set piece types (+ = white, - = black, 1 = pawn, 2 = rook, 3 = knight, 4 = bishop, 5 = queen, 6 = king)
  wP.type = 1, wR.type = 2, wN.type = 3, wB.type = 4, wQ.type = 5, wK.type = 6;
  bP.type = -1, bR.type = -2, bN.type = -3, bB.type = -4, bQ.type = -5, bK.type = -6;

  piece blank = {};
  blank.type = 0;

  typedef struct pieceMove pieceMove;
  pieceMove move;

  char currentChar;
  int row = 0, column = 0, charCount = 1, currentPosition, destinationPosition;

// decode the first part of FEN (piece placement)
  for (int i = 0; i < strlen(FEN); i++) {

    currentChar = FEN[i];

    if (currentChar == ' ') {

      break;

// go to the next row
    } else if (currentChar == '/') {

      charCount++;

      column = 0;
      row++;

    } else {

      charCount++;

      if (isdigit(currentChar)) {

        column += (currentChar - '0');

      } else {

        switch (currentChar) {

          case 'p':
            board[row * 8 + column] = bP;

            if (row != 1) {

              board[row * 8 + column].moves = 1;

            }

            break;

          case 'r':
            board[row * 8 + column] = bR;
            break;

          case 'n':
            board[row * 8 + column] = bN;
            break;

          case 'b':
            board[row * 8 + column] = bB;
            break;

          case 'q':
            board[row * 8 + column] = bQ;
            break;

          case 'k':
            board[row * 8 + column] = bK;
            break;

          case 'P':
            board[row * 8 + column] = wP;

            if (row != 6) {

              board[row * 8 + column].moves = 1;

            }

            break;

          case 'R':
            board[row * 8 + column] = wR;
            break;

          case 'N':
            board[row * 8 + column] = wN;
            break;

          case 'B':
            board[row * 8 + column] = wB;
            break;

          case 'Q':
            board[row * 8 + column] = wQ;
            break;

          case 'K':
            board[row * 8 + column] = wK;
            break;

        }

        column++;

      }

    }

  }

// decode second part of FEN
  if (FEN[charCount] == 'w') {

    *turn = 1;

  } else if (FEN[charCount] == 'b') {

    *turn = 2;

  } else {

    printf("Error while parsing FEN. EXITING\n");
    exit(0);

  }

  charCount += 2;

// decode third part of FEN
  if (FEN[charCount] == '-') {

    board[60].moves = 1;
    board[4].moves = 1;
    charCount += 2;

  } else if (isupper(FEN[charCount]) && FEN[charCount+2] == ' ') {

    board[4].moves = 1;
    charCount += 3;

  } else if (islower(FEN[charCount]) && FEN[charCount+2] == ' ') {

    board[60].moves = 1;
    charCount += 3;

  } else {

    charCount += 5;

  }

// decode fourth part of FEN
  if (FEN[charCount] == '-') {

    charCount += 2;

  } else {

    move.current[0] = FEN[charCount];
    move.current[1] = FEN[charCount+1];

    for (int i = 0; i < 64; i++) {

      previousBoard[i] = board[i];
    
    }

    moveToSquare(move, &currentPosition, &destinationPosition);

// white piece
    if (move.current[1] == '3') {

      previousBoard[currentPosition-8] = blank;
      previousBoard[currentPosition+8] = wP;
      board[currentPosition-8].moves = 1;

// black piece
    } else {

      previousBoard[currentPosition+8] = blank;
      previousBoard[currentPosition-8] = bP;
      board[currentPosition+8].moves = 1;

    }

    charCount += 3;

  }

}

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

void printPossibleMoves (struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int colour, int exception) {

  int currentPosition, destinationPosition;
  moveToSquare(move, &currentPosition, &destinationPosition);

  int possibleMoves[64];
  int possibleCaptures[64];
  char coordinate [5];

  resetArray(possibleMoves, 64);
  resetArray(possibleCaptures, 64);

  int currentType = board[currentPosition].type;

  if (currentType == 1 || currentType == -1) {

    returnPawnCaptures(move, board, previousBoard, possibleCaptures, colour, exception);

    printf("Possible pawn captures are: ");

    for (int i = 0; i < 64; i++) {

      squareToMove(possibleCaptures[i], coordinate);

      printf("%s ", coordinate);

    }

    printf("\n");

    returnPawnMoves(move, board, previousBoard, possibleMoves, colour, exception);

  } else if (currentType == 2 || currentType == -2) {

    returnRookMoves(move, board, previousBoard, possibleMoves, colour, exception);

  } else if (currentType == 3 || currentType == -3) {

    returnKnightMoves(move, board, previousBoard, possibleMoves, colour, exception);

  } else if (currentType == 4 || currentType == -4) {

    returnBishopMoves(move, board, previousBoard, possibleMoves, colour, exception);

  } else if (currentType == 5 || currentType == -5) {

    returnQueenMoves(move, board, previousBoard, possibleMoves, colour, exception);

  } else if (currentType == 6 || currentType == -6) {

    returnKingMoves(move, board, previousBoard, possibleMoves, colour, exception);

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