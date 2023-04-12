#include "../include/header.h"

int main (int argc, char * argv[]) {

  srand(time(NULL));

  typedef struct piece piece;

  int mySquares[16];
  int enemySquares[16];

  int colour, currentPosition, destinationPosition, turn, exception = 0;

// create a null piece to signify empty space
  piece blank = {};
  blank.type = 0;

  piece board [64] = {blank};
  piece previousBoard [64] = {0};

  char FEN [100];

  if (argc == 7) {

    snprintf(FEN, 100, "%s %s %s %s %s %s", argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);

  } else {

    strcpy(FEN, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

  }

  fenDecode(board, previousBoard, FEN, &turn);

// copy board to previousBoard
  for (int i = 0; i < 64; i++) {

    previousBoard[i] = board[i];

  }

/*
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
  */

  typedef struct pieceMove pieceMove;
  pieceMove move;

  int depth = 1;
  int numOfMoves = depthTest(board, previousBoard, 1, exception, depth);

  printf("depth at %d = %d\n", depth, numOfMoves);

  printf("Do you want to play as white (1) or black (2)? ");
  scanf("%d", &colour);

  while (1) {

    if (colour == 1) {

      //printf("PREVIOUS BOARD:\n");
      //printBoard(previousBoard);

      //printf("\nCURRENT BOARD:\n");
      printBoard(board);

    } else {

      printBlackBoard(board);

    }
/*
    if (isItCheckmate(board, previousBoard, colour)) {

      printf("CHECKMATE!!!!!!!!!!!!!!!\n");
      exit(0);

    }
*/
    move.destination[0] = '0';

    while (move.destination[0] == '0') {

      if (turn == 1) {

// if user enters more than 2 characters then it creates a memory error where it changes board[0].type
        printf("Enter the coordinates of the white piece you want to move: ");
        scanf(" %s", move.current);
      
        printPossibleMoves(move, board, previousBoard, turn, exception);

        printf("Enter where you want to move the white piece (or enter 0 to restart): ");
        scanf(" %s", move.destination);

        if (move.destination[0] != '0') {

          while ((strlen(move.current) != 2) || (strlen(move.destination) != 2) || (isMoveValid(move, board, previousBoard, turn, 0) != 1)) {

            printf("Not a valid move. Enter the coordinates of the white piece you want to move: ");
            scanf(" %s", move.current);

            printPossibleMoves(move, board, previousBoard, turn, exception);

            printf("Enter where you want to move the white piece (or enter 0 to restart): ");
            scanf(" %s", move.destination);

          }

        }

      } else {

// if user enters more than 2 characters then it creates a memory error where it changes board[0].type
        printf("Enter the coordinates of the black piece you want to move: ");
        scanf(" %s", move.current);
      
        printPossibleMoves(move, board, previousBoard, turn, exception);

        printf("Enter where you want to move the black piece (or enter 0 to restart): ");
        scanf(" %s", move.destination);

        if (move.destination[0] != '0') {

          while ((strlen(move.current) != 2) || (strlen(move.destination) != 2) || (isMoveValid(move, board, previousBoard, turn, 0) != 1)) {

            printf("Not a valid move. Enter the coordinates of the black piece you want to move: ");
            scanf(" %s", move.current);

            printPossibleMoves(move, board, previousBoard, turn, exception);

            printf("Enter where you want to move the black piece (or enter 0 to restart): ");
            scanf(" %s", move.destination);

          }

        }

      }

    }

    moveToSquare(move, &currentPosition, &destinationPosition);

    piece currentPiece = board[currentPosition];

    doMove(move, currentPiece, board, previousBoard, turn, exception);

// enemy turn

    if (turn == 1) {

      returnWhiteOccupiedSquares(board, mySquares);
      returnBlackOccupiedSquares(board, enemySquares);

    } else {

      returnWhiteOccupiedSquares(board, enemySquares);
      returnBlackOccupiedSquares(board, mySquares);

    }

    if (turn == 1) {

      turn = 2;

    } else {

      turn = 1;

    }

    // enemyDoRandomMove(board, previousBoard, enemySquares, opponentColour);

  }

  return 0;

}