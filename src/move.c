#include "../include/header.h"

int isMoveValid (struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int colour, int exception) {

  int currentPosition, destinationPosition;
  moveToSquare(move, &currentPosition, &destinationPosition);

// perform general checks to see if move is valid
  if (isAnyMoveValid(move, board, previousBoard, colour, exception) == 0) {
    
    return 0;

  }

  int currentType = board[currentPosition].type;

// check if move is for a pawn
  if (currentType == 1 || currentType == -1) {

    return isPawnMoveValid(move, board, previousBoard, colour, exception);

  } else if (currentType == 2 || currentType == -2) {

    return isRookMoveValid(move, board, previousBoard, colour, exception);

  } else if (currentType == 3 || currentType == -3) {

    return isKnightMoveValid(move, board, previousBoard, colour, exception);

  } else if (currentType == 4 || currentType == -4) {

    return isBishopMoveValid(move, board, previousBoard, colour, exception);

  } else if (currentType == 5 || currentType == -5) {

    return isQueenMoveValid(move, board, previousBoard, colour, exception);

  } else if (currentType == 6 || currentType == -6) {

    return isKingMoveValid(move, board, previousBoard, colour, exception);

  }

  return 0;

}

int isAnyMoveValid (struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int colour, int exception) {

  int currentPosition, destinationPosition;
  moveToSquare(move, &currentPosition, &destinationPosition);

// if player is trying to move other player's pieces
  if ((board[currentPosition].type > 0 && colour == 2) || (board[currentPosition].type < 0 && colour == 1)) {

    return 0;

  }

// if move is out of bounds
  if (currentPosition < 0 || destinationPosition < 0) {

    return 0;

  }

// can't move to its current spot
  if (strcmp(move.current, move.destination) == 0) {

    return 0;

  }

// can't capture own colour's pieces
  if (((board[destinationPosition].type > 0 && board[currentPosition].type > 0) || (board[destinationPosition].type < 0 && board[currentPosition].type < 0)) && !exception) {

    return 0;

  }



  return 1;

}

int isPawnMoveValid (struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int colour, int exception) {

// convert chars to integers to use on the 2D board array
  int currentPosition, destinationPosition, rowDifference, columnDifference;
  moveToSquare(move, &currentPosition, &destinationPosition);

  int distance = destinationPosition-currentPosition;

  rowDifference = abs(((currentPosition) / 8) - (destinationPosition / 8));
  columnDifference = abs(((currentPosition) % 8) - (destinationPosition % 8));

// perform general checks to see if move is valid
  if (isAnyMoveValid(move, board, previousBoard, colour, exception) == 0) {
    
    return 0;

  }

// pawns can't move backwards
  if ((distance < 0 && colour == 2) || (distance > 0 && colour == 1)) {

    return 0;

  }

// check is white pawn can do en passant
  if (canPawnEnPassant(move, board, previousBoard, colour)) {

    return 1;

  }

// check if pawn can take another piece
  if ((distance == -7 && board[destinationPosition].type < 0 && colour == 1) || (distance == -9 && board[destinationPosition].type < 0 && colour == 1) || (distance == 7 && board[destinationPosition].type > 0 && colour == 2) || (distance == 9 && board[destinationPosition].type > 0 && colour == 2)) {

// make sure that pawn isn't moving across the board
    if (rowDifference == 1 && columnDifference == 1) {

      return 1;

    }

    return 0;

  }

// if there is already a piece at the destination, move is not valid
  if (board[destinationPosition].type != 0) {

    return 0;

  }

// pawns can't move more than 2 spaces at once
  if (abs(distance) != 8 && abs(distance) != 16) {

    return 0;

// pawns can't move 2 spaces if they have already moved
  } else if (abs(distance) == 16 && board[currentPosition].moves != 0) {
      
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

int isRookMoveValid (struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int colour, int exception) {

  int currentPosition, destinationPosition;
  moveToSquare(move, &currentPosition, &destinationPosition);

  int distance = destinationPosition-currentPosition;

// perform general checks to see if move is valid
  if (isAnyMoveValid(move, board, previousBoard, colour, exception) == 0) {
    
    return 0;

  }

// check if rook is moving vertically (first conditional) or horizontally (second)
  if (abs(distance) % 8 != 0 && (move.current[1] != move.destination[1])) {

    return 0;

  }

  if (abs(distance) % 8 == 0 && (move.current[1] == move.destination[1])) {

    return 0;

  }

// check if any pieces are in the way of horizontal move
  if (move.current[1] == move.destination[1]) {

    if (distance > 0) {

// iterate through all squares inbetween pieces (to the right)
      for (int i = currentPosition+1; i < destinationPosition; i++) {

        if (board[i].type != 0) {

          return 0;

        }

      }

      return 1;

    } else {

// iterate through all squares inbetween pieces (to the left)
      for (int i = currentPosition-1; i > destinationPosition; i--) {

        if (board[i].type != 0) {

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

          return 0;

        }

      }

      return 1;
      
    } else {

      for (int i = currentPosition-8; i > destinationPosition; i -= 8) {

        if (board[i].type != 0) {

          return 0;

        }

      }

      return 1;
      
    }

  }

  return 0;

}

int isKnightMoveValid (struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int colour, int exception) {

  int currentPosition, destinationPosition;
  moveToSquare(move, &currentPosition, &destinationPosition);

  int distance = destinationPosition-currentPosition;

  int rowDifference = abs((destinationPosition / 8) - (currentPosition / 8));
  int columnDifference = abs((destinationPosition % 8) - (currentPosition % 8));

// perform general checks to see if move is valid
  if (isAnyMoveValid(move, board, previousBoard, colour, exception) == 0) {
    
    return 0;

  }

// check that knight move is an L shape
  if (abs(distance) != 6 && abs(distance) != 10 && abs(distance) != 15 && abs(distance) != 17) {

    return 0;

  }

  if ((rowDifference == 1 && columnDifference == 2) || (rowDifference == 2 && columnDifference == 1)) {

    return 1;

  }
  
  return 0;

}

int isBishopMoveValid (struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int colour, int exception) {

  int currentPosition, destinationPosition;
  moveToSquare(move, &currentPosition, &destinationPosition);

  int distance = destinationPosition-currentPosition;

// perform general checks to see if move is valid
  if (isAnyMoveValid(move, board, previousBoard, colour, exception) == 0) {
    
    return 0;

  }

// check if bishop move is diagonal
  if (abs(distance) % 7 != 0 && abs(distance) % 9 != 0) {

    return 0;

  }

// check if bishop move crosses the side of the board
  if (abs((destinationPosition/8)-(currentPosition/8)) != abs((destinationPosition%8)-(currentPosition%8))) {

    return 0;

  }

// bishop is moving towards bottom right
  if (distance % 9 == 0 && distance > 0) {

    for (int i = currentPosition+9; i < destinationPosition; i+=9) {

      if (board[i].type != 0) {

        return 0;

      }

    }

    return 1;

// bishop is moving towards bottom left
  } else if (distance % 7 == 0 && distance > 0) {

    for (int i = currentPosition+7; i < destinationPosition; i+=7) {

      if (board[i].type != 0) {

        return 0;

      }

    }

    return 1;

// bishop is moving towards top left
  } else if (distance % 9 == 0 && distance < 0) {

    for (int i = currentPosition-9; i > destinationPosition; i-=9) {

      if (board[i].type != 0) {

        return 0;

      }

    }

    return 1;

// bishop is moving towards top right
  } else if (distance % 7 == 0 && distance < 0) {

    for (int i = currentPosition-7; i > destinationPosition; i-=7) {

      if (board[i].type != 0) {

        return 0;

      }

    }

    return 1;

  }

  return 0;
}

int isQueenMoveValid (struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int colour, int exception) {

  int currentPosition, destinationPosition;
  moveToSquare(move, &currentPosition, &destinationPosition);

// check if queen move works for rooks and bishops
  int rookLegal = isRookMoveValid(move, board, previousBoard, colour, exception);
  int bishopLegal = isBishopMoveValid(move, board, previousBoard, colour, exception);

// if it fails both the rook and bishop test, it is not a legal queen move
  if (rookLegal == 0 && bishopLegal == 0) {

    return 0;

  }

// if it passes either the rook or bishop test, it is a legal queen move
  return 1;

}

int isKingMoveValid (struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int colour, int exception) {

  int currentPosition, destinationPosition;
  moveToSquare(move, &currentPosition, &destinationPosition);

  int distance = destinationPosition-currentPosition;

  int rowDifference = abs((destinationPosition / 8) - (currentPosition / 8));
  int columnDifference = abs((destinationPosition % 8) - (currentPosition % 8));

// perform general checks to see if move is valid
  if (isAnyMoveValid(move, board, previousBoard, colour, exception) == 0) {
    
    return 0;

  }

// check for castling for white
  if ((colour == 1 && currentPosition == 60 && (destinationPosition == 62 || destinationPosition == 58)) || (colour == 2 && currentPosition == 4 && (destinationPosition == 6 || destinationPosition == 2))) {

    return canKingCastle(move, board, previousBoard, colour, exception);

  }

  if (abs(distance) != 1 && abs(distance) != 7 && abs(distance) != 8 && abs(distance) != 9) {

    return 0;

  }

  if (abs(distance) == 1 && move.current[1] != move.destination[1]) {

    return 0;

  }

// make sure king is not crossing over board borders
  if (abs(rowDifference) > 1|| abs(columnDifference) > 1) {

    return 0;

  }

// check if piece it wants to attack is protected
  if (isPieceProtected(move, board, previousBoard, colour)) {

    return 0;

  }

// now check if move would put the king in check
  int captureSquares [64];

  if (colour == 1) {

    returnBlackPossibleCaptures(board, previousBoard, captureSquares, 1, exception);

  } else {

    returnWhitePossibleCaptures(board, previousBoard, captureSquares, 2, exception);

  }

  for (int i = 0; i < 64; i++) {

    if (captureSquares[i] == destinationPosition) {

      return 0;

    }

  }

  return 1;

}

int isKingInCheck (struct piece board[64], struct piece previousBoard[64], int colour, int exception) {

  int king;
  int captures[64];

  resetArray(captures, 64);

  if (colour == 1) {

    for (int i = 0; i < 64; i++) {

      if (board[i].type == 6) {

        king = i;
        break;

      }

    }

    returnBlackPossibleCaptures(board, previousBoard, captures, colour, exception);

  } else {

    for (int i = 0; i < 64; i++) {

      if (board[i].type == -6) {

        king = i;
        break;

      }

    }

    returnWhitePossibleCaptures(board, previousBoard, captures, colour, exception);

    }

  for (int i = 0; i < 64; i++) {

    if (captures[i] == king) {

      return 1;

    }

  }

  return 0;

}

int canKingCastle (struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int colour, int exception) {

  int currentPosition = -1, destinationPosition = -1;
  moveToSquare(move, &currentPosition, &destinationPosition);
  
  int captures[64];

  resetArray(captures, 64);

// check that the king isn't in check
  if (isKingInCheck(board, previousBoard, colour, exception)) {

    return 0;

  }

// check that king hasn't moved
  if (board[currentPosition].moves != 0) {

    return 0;

  }

// white kingside castle
  if (colour == 1 && currentPosition == 60 && destinationPosition == 62) {

// check that there are no pieces in the way
    if (board[61].type != 0 || board[62].type != 0) {

      return 0;

    }

// check that the rook hasn't moved
    if (board[63].moves != 0 && board[63].type == 2) {

      return 0;

    }

    returnBlackPossibleCaptures(board, previousBoard, captures, colour, exception);

// check that the squares in between aren't under attack
    if (captures[61] != -1 || captures[62] != -1) {

      return 0;

    }

// white queenside castle
  } else if (colour == 1 && currentPosition == 60 && destinationPosition == 58) {

// check that there are no pieces in the way
    if (board[57].type != 0 || board[58].type != 0 || board[59].type != 0) {

      return 0;

    }

// check that the rook hasn't moved
    if (board[56].moves != 0 && board[56].type == 2) {

      return 0;

    }

    returnBlackPossibleCaptures(board, previousBoard, captures, colour, exception);

// check that the squares in between aren't under attack
    if (captures[57] != -1 || captures[58] != -1 || captures[59] != -1) {

      return 0;

    }


// black kingside castle
  } else if (colour == 2 && currentPosition == 4 && destinationPosition == 6) {

// check that there are no pieces in the way
    if (board[5].type != 0 || board[6].type != 0) {

      return 0;

    }

// check that the rook hasn't moved
    if (board[7].moves != 0 && board[7].type == 2) {

      return 0;

    }

    returnBlackPossibleCaptures(board, previousBoard, captures, colour, exception);

// check that the squares in between aren't under attack
    if (captures[5] != -1 || captures[6] != -1) {

      return 0;

    }


// black queenside castle
  } else if (colour == 2 && currentPosition == 4 && destinationPosition == 2) {
  
// check that there are no pieces in the way
    if (board[1].type != 0 || board[2].type != 0 || board[3].type != 0) {

      return 0;

    }

// check that the rook hasn't moved
    if (board[0].moves != 0 && board[0].type == 2) {

      return 0;

    }

    returnBlackPossibleCaptures(board, previousBoard, captures, colour, exception);

// check that the squares in between aren't under attack
    if (captures[1] != -1 || captures[2] != -1 || captures[3] != -1) {

      return 0;

    }

  }

  return 1;

}

int canPawnEnPassant (struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int colour) {

  int currentPosition, destinationPosition, rowDifference, columnDifference;
  moveToSquare(move, &currentPosition, &destinationPosition);
  
  rowDifference = abs(((currentPosition) / 8) - (destinationPosition / 8));
  columnDifference = abs(((currentPosition) % 8) - (destinationPosition % 8));

// check is white pawn can do en passant
  if (colour == 1 && (currentPosition / 8 == 3) && previousBoard[destinationPosition+8].type == 0 && board[destinationPosition+8].type == -1 && board[destinationPosition+8].moves == 1) {

// make sure that pawn isn't moving across the board
    if (rowDifference == 1 && columnDifference == 1) {

      return 1;

    }

  }

// check is black pawn can do en passant
  if (colour == 2 && (currentPosition / 8 == 4) && previousBoard[destinationPosition-8].type == 0 && board[destinationPosition-8].type == 1 && board[destinationPosition-8].moves == 1) {

// make sure that pawn isn't moving across the board
    if (rowDifference == 1 && columnDifference == 1) {

      return 1;

    }

  }

  return 0;

}

int isPieceProtected (struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int colour) {

  int currentPosition, destinationPosition;
  moveToSquare(move, &currentPosition, &destinationPosition);

  struct pieceMove tempMove;
  squareToMove(destinationPosition, tempMove.destination);
  int pieces[16];

  resetArray(pieces, 16);

  if (colour == 1) {

    returnBlackOccupiedSquares(board, pieces);

    for (int i = 0; i < 16; i++) {

      if (pieces[i] == -1) {

        break;

      }

      squareToMove(pieces[i], tempMove.current);

      if (isMoveValid(tempMove, board, previousBoard, 2, 1) == 1) {

        return 1;

      }

    }

  } else {

    returnWhiteOccupiedSquares(board, pieces);

    for (int i = 0; i < 16; i++) {

      if (pieces[i] == -1) {

        break;

      }

      squareToMove(pieces[i], tempMove.current);

      if (isMoveValid(tempMove, board, previousBoard, 1, 1) == 1) {

        return 1;

      }

    }

  }

  return 0;

}

void doMove (struct pieceMove move, struct piece movedPiece, struct piece board[64], struct piece previousBoard[64], int colour, int exception) {

  int currentPosition, destinationPosition;
  moveToSquare(move, &currentPosition, &destinationPosition);

// en passant
  if (abs(board[currentPosition].type) == 1 && canPawnEnPassant(move, board, previousBoard, colour)) {

    if (colour == 1) {

      board[destinationPosition+8].type = 0;

    } else {

      board[destinationPosition-8].type = 0;

    }

  }

// copy current board to previousBoard. it has to be past the en passant for it to work. do i know why? nope
  for (int i = 0; i < 64; i++) {

    previousBoard[i] = board[i];
    
  }

// castling
  if (abs(board[currentPosition].type) == 6 && canKingCastle(move, board, previousBoard, colour, exception)) {

    typedef struct pieceMove pieceMove;
    pieceMove move;

    if (destinationPosition == 62) {

      strcpy(move.current, "h1");
      strcpy(move.destination, "f1");

      doMove(move, board[63], board, previousBoard, 0, exception);

    } else if (destinationPosition == 58) {

      strcpy(move.current, "a1");
      strcpy(move.destination, "d1");

      doMove(move, board[56], board, previousBoard, 0, exception);

    } else if (destinationPosition == 6) {

      strcpy(move.current, "h8");
      strcpy(move.destination, "f8");

      doMove(move, board[7], board, previousBoard, 0, exception);

    } else if (destinationPosition == 2) {

      strcpy(move.current, "a8");
      strcpy(move.destination, "d8");

      doMove(move, board[0], board, previousBoard, 0, exception);

    }

  }
  
  movedPiece.moves++;

  board[currentPosition].type = 0;
  board[destinationPosition] = movedPiece;

}

void undoMove (struct pieceMove move, struct piece movedPiece, struct piece board[64], struct piece previousBoard[64], int colour) {

  int currentPosition, destinationPosition;
  moveToSquare(move, &currentPosition, &destinationPosition);

  struct piece previousPiece = previousBoard[destinationPosition];

// copy previousBoard to board
  for (int i = 0; i < 64; i++) {

    board[i] = previousBoard[i];

  }

  movedPiece.moves--;
  previousPiece.moves--;

  board[currentPosition] = movedPiece;
  board[destinationPosition].type = 0;



}

void returnPawnMoves(struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int pawnMoves[64], int colour, int exception) {

  int numOfMoves = 0;

  int currentPosition, destinationPosition;
  moveToSquare(move, &currentPosition, &destinationPosition);

  typedef struct pieceMove pieceMove;
  pieceMove tempMove;
  char coordinate [5];

  strcpy(tempMove.current, move.current);

  for (int i = 0; i < 64; i++) {

    squareToMove(i, coordinate);

    strcpy(tempMove.destination, coordinate);

    if (isPawnMoveValid(tempMove, board, previousBoard, colour, exception) == 1) {

        pawnMoves[numOfMoves] = i;
        numOfMoves++;

    }

  }

}

void returnPawnCaptures(struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int pawnMoves[64], int colour, int exception) {

  int numOfMoves = 0;

  int currentPosition, destinationPosition, rowDifference, columnDifference;
  moveToSquare(move, &currentPosition, &destinationPosition);

  typedef struct pieceMove pieceMove;
  pieceMove tempMove;
  char coordinate [5];

  strcpy(tempMove.current, move.current);

  for (int i = 0; i < 64; i++) {

    rowDifference = abs(((currentPosition) / 8) - (i / 8));
    columnDifference = abs(((currentPosition) % 8) - (i % 8));

// make sure that pawn isn't moving across the board
    if (!(rowDifference == 1 && columnDifference == 1)) {

      continue;

    }

    squareToMove(i, coordinate);

    strcpy(tempMove.destination, coordinate);

    if (isPawnMoveValid(tempMove, board, previousBoard, colour, exception) == 1) {

        pawnMoves[numOfMoves] = i;
        numOfMoves++;

    }

  }

}

void returnRookMoves(struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int rookMoves[64], int colour, int exception) {

  int numOfMoves = 0;

  int currentPosition, destinationPosition;
  moveToSquare(move, &currentPosition, &destinationPosition);

  typedef struct pieceMove pieceMove;
  pieceMove tempMove;
  char coordinate [5];

  strcpy(tempMove.current, move.current);

  for (int i = 0; i < 64; i++) {

    squareToMove(i, coordinate);

    strcpy(tempMove.destination, coordinate);

    if (isRookMoveValid(tempMove, board, previousBoard, colour, exception) == 1) {

      rookMoves[numOfMoves] = i;
      numOfMoves++;

    }

  }

}

void returnKnightMoves(struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int knightMoves[64], int colour, int exception) {

  int numOfMoves = 0;

  int currentPosition, destinationPosition;
  moveToSquare(move, &currentPosition, &destinationPosition);

  typedef struct pieceMove pieceMove;
  pieceMove tempMove;
  char coordinate [5];

  strcpy(tempMove.current, move.current);

  for (int i = 0; i < 64; i++) {

    squareToMove(i, coordinate);

    strcpy(tempMove.destination, coordinate);

    if (isKnightMoveValid(tempMove, board, previousBoard, colour, exception) == 1) {

        knightMoves[numOfMoves] = i;
        numOfMoves++;

    }

  }

}

void returnBishopMoves(struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int bishopMoves[64], int colour, int exception) {

  int numOfMoves = 0;

  int currentPosition, destinationPosition;
  moveToSquare(move, &currentPosition, &destinationPosition);

  typedef struct pieceMove pieceMove;
  pieceMove tempMove;
  char coordinate [5];

  strcpy(tempMove.current, move.current);

  for (int i = 0; i < 64; i++) {

    squareToMove(i, coordinate);

    strcpy(tempMove.destination, coordinate);

    if (isBishopMoveValid(tempMove, board, previousBoard, colour, exception) == 1) {

        bishopMoves[numOfMoves] = i;
        numOfMoves++;

    }

  } 

}

void returnQueenMoves(struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int queenMoves[64], int colour, int exception) {

  int numOfMoves = 0;

  int currentPosition, destinationPosition;
  moveToSquare(move, &currentPosition, &destinationPosition);

  typedef struct pieceMove pieceMove;
  pieceMove tempMove;
  char coordinate [5];

  strcpy(tempMove.current, move.current);

  for (int i = 0; i < 64; i++) {

    squareToMove(i, coordinate);

    strcpy(tempMove.destination, coordinate);

    if (isQueenMoveValid(tempMove, board, previousBoard, colour, exception) == 1) {

        queenMoves[numOfMoves] = i;
        numOfMoves++;

    }

  } 

}

void returnKingMoves(struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int kingMoves[64], int colour, int exception) {

  int numOfMoves = 0;

  int currentPosition, destinationPosition;
  moveToSquare(move, &currentPosition, &destinationPosition);

  typedef struct pieceMove pieceMove;
  pieceMove tempMove;
  char coordinate [5];

  strcpy(tempMove.current, move.current);

  for (int i = 0; i < 64; i++) {

    squareToMove(i, coordinate);

    strcpy(tempMove.destination, coordinate);

    if (isKingMoveValid(tempMove, board, previousBoard, colour, exception) == 1) {

      kingMoves[numOfMoves] = i;
      numOfMoves++;

    }

  }

}

void moveToSquare (struct pieceMove move, int * currentPosition, int * destinationPosition) {

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

void squareToMove(int squareNum, char coordinate [5]) {

  if (squareNum > 63 || squareNum < 0) {

    coordinate[0] = '\0';
    
  } else {

    coordinate[0] = 'a' + (squareNum % 8);
    coordinate[1] = '8' - (squareNum / 8);
    coordinate[2] = '\0';

  }

}