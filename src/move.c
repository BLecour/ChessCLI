#include "../include/header.h"

int isMoveValid (struct pieceMove move, struct piece board[64], int colour) {

  int currentPosition, destinationPosition;
  moveToCoordinates(move, &currentPosition, &destinationPosition);


//test king invalid moves
  int badMoves[64] = {-64};

  movesUnderCheck(board, badMoves, colour);

  printf("invalid king moves at squares: ");

  for (int i = 0; i < 64; i++) {

    printf("%d ", badMoves[i]);

  }

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

// can't capture own colour's pieces
  if ((board[destinationPosition].type > 0 && colour == 1) || (board[destinationPosition].type < 0 && colour == 2)) {

    printf("currentPosition (%d) or destinationPosition (%d) trying to capture its own pieces\n", currentPosition, destinationPosition);

    return 0;

  }

  int currentType = board[currentPosition].type;

  // printf("current type at %d is %d\n", currentPosition, board[currentPosition].type);

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

  int distance = destinationPosition-currentPosition;

  printf("currentPosition = %d  destinationPosition = %d\n", currentPosition, destinationPosition);

  printf("the type at this position is %d\n", board[currentPosition].type);

// check if pawn can take another piece
  if ((distance == -7 && board[destinationPosition].type < 0 && colour == 1) || (distance == -9 && board[destinationPosition].type < 0 && colour == 1) || (distance == 7 && board[destinationPosition].type > 0 && colour == 2) || (distance == 9 && board[destinationPosition].type > 0 && colour == 2)) {

    return 1;

  }

  if (board[destinationPosition].type != 0) {
// if there is already a piece at the destination, move is not valid

    return 0;

  }

// pawns can't move more than 2 spaces at once
  if (abs(distance) != 8 && abs(distance) != 16) {

    return 0;

  } else if (abs(distance) == 16 && board[currentPosition].moves != 0) {
// pawns can't move 2 spaces if they have already moved
      
    return 0;

  }

// if moving 2 squares, pawn also cannot jump over pieces (for white)
  if (abs(distance) == 16 && (board[currentPosition-8].type != 0 || board[currentPosition-16].type != 0) && colour == 1) {

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

  int distance = destinationPosition-currentPosition;

// check if rook is moving vertically (first conditional) or horizontally (second)
  if (abs(distance) % 8 != 0 && (move.current[1] != move.destination[1])) {

    printf("not a valid rook move because of non-vertical/horizontal move\n");

    return 0;

  }

  if (abs(distance) % 8 == 0 && (move.current[1] == move.destination[1])) {

    printf("not a valid rook move because of it is not moving fully vertically/horizontally\n");

    return 0;

  }

// check if any pieces are in the way of horizontal move
  if (move.current[1] == move.destination[1]) {

    if (distance > 0) {

// iterate through all squares inbetween pieces
      for (int i = currentPosition+1; i < destinationPosition; i++) {

        if (board[i].type != 0) {

          printf("there is a piece in the way of a horizontal rook move at %d\n", i);

          return 0;

        }

      }

      return 1;

    } else {

// iterate through all squares inbetween pieces
      for (int i = destinationPosition-1; i > currentPosition; i--) {

        if (board[i].type != 0) {

          printf("there is a piece in the way of a horizontal rook move at %d\n", i);

          return 0;

        }

      }

      return 1;

    }

  }

// check if any pieces are in the way of vertical move
  if (abs(distance) % 8 == 0) {

    if (distance > 0) {

      for (int i = currentPosition+8; i < destinationPosition; i += 8) {

        if (board[i].type != 0) {

          printf("there is a piece in the way of a vertical rook move at %d\n", i);

          return 0;

        }

      }

      return 1;
      
    } else {

      for (int i = currentPosition-8; i > destinationPosition; i -= 8) {

        if (board[i].type != 0) {

          printf("there is a piece in the way of a vertical rook move at %d\n", i);

          return 0;

        }

      }

      return 1;
      
    }

  }

  printf("Rook move failed at the end of function\n");
  return 0;

}

int isKnightMoveValid (struct pieceMove move, struct piece board[64], int colour) {

  int currentPosition, destinationPosition;
  moveToCoordinates(move, &currentPosition, &destinationPosition);

  int distance = destinationPosition-currentPosition;

  int rowDifference = abs((destinationPosition / 8) - (currentPosition / 8));
  int columnDifference = abs((destinationPosition % 8) - (currentPosition % 8));

// check that knight move is an L shape
  if (abs(distance) != 6 && abs(distance) != 10 && abs(distance) != 15 && abs(distance) != 17) {

    printf("knight move failed because it is not an L shaped move (distance = %d)\n", distance);

    return 0;

  }

  if ((rowDifference == 1 && columnDifference == 2) || (rowDifference == 2 && columnDifference == 1)) {

    return 1;

  }

  printf("Invalid move: target square is not reachable by a knight's move. OR ANOTHER ERROR\n");
  return 0;

}

int isBishopMoveValid (struct pieceMove move, struct piece board[64], int colour) {

  int currentPosition, destinationPosition;
  moveToCoordinates(move, &currentPosition, &destinationPosition);

  int distance = destinationPosition-currentPosition;

// check if bishop move is diagonal
  if (abs(distance) % 7 != 0 && abs(distance) % 9 != 0) {

    printf("bishop move failed because it is not a diagonal move\n");

    return 0;

  }

  printf("bishop distance = %d\n", distance);

// bishop is moving towards bottom right
  if (distance % 9 == 0 && distance > 0) {

    for (int i = currentPosition+9; i < destinationPosition; i+=9) {

      if (board[i].type != 0) {

        printf("there is a piece in the way of a bottom right bishop move at %d\n", i);

        return 0;

      }

    }

    return 1;

// bishop is moving towards bottom left
  } else if (distance % 7 == 0 && distance > 0) {

    for (int i = currentPosition+7; i < destinationPosition; i+=7) {

      if (board[i].type != 0) {

        printf("there is a piece in the way of a bottom left bishop move at %d\n", i);

        return 0;

      }

    }

    return 1;

// bishop is moving towards top left
  } else if (distance % 9 == 0 && distance < 0) {

    for (int i = currentPosition-9; i > destinationPosition; i-=9) {

      printf("checking square [%d] and type at %d is %d\n", i, i, board[i].type);

      if (board[i].type != 0) {

        printf("there is a piece in the way of a top right bishop move at %d\n", i);

        return 0;

      }

    }

    return 1;

// bishop is moving towards top right
  } else if (distance % 7 == 0 && distance < 0) {

    for (int i = currentPosition-7; i > destinationPosition; i-=7) {

      printf("checking square [%d] and type at %d is %d\n", i, i, board[i].type);

      if (board[i].type != 0) {

        printf("there is a piece in the way of a top left bishop move at %d\n", i);

        return 0;

      }

    }

    return 1;

  }

  printf("bishop failed at end of function\n");

  return 0;
}

int isQueenMoveValid (struct pieceMove move, struct piece board[64], int colour) {

  int currentPosition, destinationPosition;
  moveToCoordinates(move, &currentPosition, &destinationPosition);

// check if queen move works for rooks and bishops
  int rookLegal = isRookMoveValid(move, board, colour);
  int bishopLegal = isBishopMoveValid(move, board, colour);

// if it fails both the rook and bishop test, it is not a legal queen move
  if (rookLegal == 0 && bishopLegal == 0) {

    printf("rookLegal = %d and bishopLegal = %d, failed both\n", rookLegal, bishopLegal);

    return 0;

  }

// if it passes either the rook or bishop test, it is a legal queen move
  printf("rookLegal = %d and bishopLegal = %d, passed!\n", rookLegal, bishopLegal);

  return 1;

}

int isKingMoveValid (struct pieceMove move, struct piece board[64], int colour) {

  int currentPosition, destinationPosition;
  moveToCoordinates(move, &currentPosition, &destinationPosition);

  int distance = destinationPosition-currentPosition;

  if (abs(distance) != 1 && abs(distance) != 7 && abs(distance) != 8 && abs(distance) != 9) {

    printf("FAILED: king move is not within 1 square of king\n");

    return 0;

  }

  if (abs(distance) == 1 && move.current[1] != move.destination[1]) {

    printf("FAILED: king move is horizontal but is trying to jump rows\n");

    return 0;

  }

  printf("king move PASSED at the end of function\n");

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

void movesUnderCheck(struct piece board[64], int invalidKingMoves[64], int colour) {

  typedef struct piece piece;
  int numOfMoves = 0;

// if white
  if (colour == 1) {

    for (int square = 0; square < 64; square++) {

      piece currentPiece = board[square];

// pawns
      if (currentPiece.type == 1) {

        int pawnMoveOffsets [4] = {-9, -7, -17, -15};
        int currentOffset;

        int rowDifference, columnDifference;

// if pawn can move 1 or 2 squares
        if (currentPiece.moves == 0) {

          for (int i = 0; i < 4; i++) {

            currentOffset = pawnMoveOffsets[i];

            rowDifference = abs(((square+currentOffset) / 8) - (square / 8));
            columnDifference = abs(((square+currentOffset) % 8) - (square % 8));

            if ((rowDifference == 1 && columnDifference == 1) || (rowDifference == 2 && columnDifference == 1)) {

              invalidKingMoves[numOfMoves] = square+currentOffset;
              numOfMoves++;

            }
        
          }

// if pawn can only move 1 square
        } else {

          for (int i = 0; i < 2; i++) {

            currentOffset = pawnMoveOffsets[i];

            rowDifference = abs(((square+currentOffset) / 8) - (square / 8));
            columnDifference = abs(((square+currentOffset) % 8) - (square % 8));

            if ((rowDifference == 1 && columnDifference == 1)) {

              invalidKingMoves[numOfMoves] = square+currentOffset;
              numOfMoves++;

            }
        
          }

        }

// rook
      } else if (currentPiece.type == 2) {

// iterate through all squares to the right of the rook
        for (int i = square+1; i < (square/8)*8 + 7; i++) {

          if (board[square].type != 0) {

            printf("there is a piece in the way of a horizontal (right) rook move at %d\n", i);

            break;

          } else {

            invalidKingMoves[numOfMoves] = i;
            numOfMoves++;

          }

        }

// iterate through all squares to the left of the rook
        for (int i = square-1; i > (square/8)*8; i--) {

          if (board[square].type != 0) {

            printf("there is a piece in the way of a horizontal (left) rook move at %d\n", i);

            break;

          } else {

            invalidKingMoves[numOfMoves] = i;
            numOfMoves++;

          }

        }

        for (int i = square+8; i > (square%8)+56; i+=8) {

          if (board[square].type != 0) {

            printf("there is a piece in the way of a vertical (down) rook move at %d\n", i);

            break;

          } else {

            invalidKingMoves[numOfMoves] = i;
            numOfMoves++;

          }

        }

        for (int i = square-8; i > square%8; i-=8) {

          if (board[square].type != 0) {

            printf("there is a piece in the way of a vertical (up) rook move at %d\n", i);

            break;

          } else {

            invalidKingMoves[numOfMoves] = i;
            numOfMoves++;

          }

        }
      
// knight
      } else if (currentPiece.type == 3) {

        int knightMoveOffsets [8] = {-17, -15, -10, -6, 6, 10, 15, 17};
        int currentOffset;

        int rowDifference, columnDifference;

        for (int i = 0; i < 8; i++) {

          currentOffset = knightMoveOffsets[i];

// knight move would be out of board bounds, go to next iteration
          if (square + currentOffset < 0 || square + currentOffset > 63) {

            continue;

          }

          rowDifference = abs(((square+currentOffset) / 8) - (square / 8));
          columnDifference = abs(((square+currentOffset) % 8) - (square % 8));

          if ((rowDifference == 1 && columnDifference == 2) || (rowDifference == 2 && columnDifference == 1)) {

            invalidKingMoves[numOfMoves] = square+currentOffset;
            numOfMoves++;

          }

        }

      }

    }


// if black
  } else {

    for (int i = 0; i < 64; i++) {

      piece currentPiece = board[i];

    }

  }

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