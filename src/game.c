#include "../include/header.h"

void returnWhiteOccupiedSquares (struct piece board[64], int whiteOccupiedSquares[16]) {

  int count = 0;

  resetArray(whiteOccupiedSquares, 16);

  for (int i = 0; i < 64; i++) {

    if (board[i].type > 0) {

      whiteOccupiedSquares[count] = i;
      count++; 

    }

  }

}

void returnBlackOccupiedSquares (struct piece board[64], int blackOccupiedSquares[16]) {

  int count = 0;

  resetArray(blackOccupiedSquares, 16);

  for (int i = 0; i < 64; i++) {

    if (board[i].type < 0) {

      blackOccupiedSquares[count] = i;
      count++;  

    }

  }

}

void returnWhitePossibleCaptures (struct piece board[64], struct piece previousBoard[64], int whitePossibleCaptures[64], int colour, int exception) {

  typedef struct pieceMove pieceMove;
  pieceMove move;

  int piecePossibleCaptures[32];
  int whiteOccupiedSquares[16];
  int pieceCount = 0, moveCount = 0, currentType, currentOffset, rowDifference, columnDifference;

  int kingOffsets[8] = {-9, -8, -7, -1, 1, 7, 8, 9};

  returnWhiteOccupiedSquares(board, whiteOccupiedSquares);

// reset array to -1
  resetArray(whitePossibleCaptures, 64);

// get the number of white pieces
  for (int i = 0; i < 16; i++) {

    if (whiteOccupiedSquares[i] != -1) {

      pieceCount++;  

    } else {

      break;

    }

  }

// loop through all of white's pieces
  for (int i = 0; i < pieceCount; i++) {

    resetArray(piecePossibleCaptures, 32);

    currentType = board[whiteOccupiedSquares[i]].type;

    squareToMove(whiteOccupiedSquares[i], move.current);

    switch (currentType) {

      case 1:
        returnPawnMoves(move, board, previousBoard, piecePossibleCaptures, 1, exception);
        break;

      case 2:
        returnRookMoves(move, board, previousBoard, piecePossibleCaptures, 1, exception);
        break;

      case 3:
        returnKnightMoves(move, board, previousBoard, piecePossibleCaptures, 1, exception);
        break;

      case 4:
        returnBishopMoves(move, board, previousBoard, piecePossibleCaptures, 1, exception);
        break;

      case 5:
        returnQueenMoves(move, board, previousBoard, piecePossibleCaptures, 1, exception);
        break;

      case 6:
        for (int j = 0; j < 8; j++) {
          currentOffset = whiteOccupiedSquares[i] + kingOffsets[j];

          rowDifference = abs((currentOffset / 8) - (whiteOccupiedSquares[i] / 8));
          columnDifference = abs((currentOffset % 8) - (whiteOccupiedSquares[i] % 8));

          currentOffset = whiteOccupiedSquares[i] + kingOffsets[j];

// check that move doesn't cross over the side of the board
          if (!(abs(rowDifference) > 1 || abs(columnDifference) > 1)) {

            piecePossibleCaptures[moveCount] = currentOffset;
            moveCount++;

          }

        }

        break;

    }

    for (int i = 0; i < 32; i++) {

      if (piecePossibleCaptures[i] != -1) {

        whitePossibleCaptures[piecePossibleCaptures[i]] = piecePossibleCaptures[i];

      } else {

        break;

      }

    }

  }

}

void returnBlackPossibleCaptures (struct piece board[64], struct piece previousBoard[64], int blackPossibleCaptures[64], int colour, int exception) {

  typedef struct pieceMove pieceMove;
  pieceMove move;

  int piecePossibleCaptures[32];
  int blackOccupiedSquares[16];
  int pieceCount = 0, moveCount = 0, currentType, currentOffset, rowDifference, columnDifference;

  int kingOffsets[8] = {-9, -8, -7, -1, 1, 7, 8, 9};

  returnBlackOccupiedSquares(board, blackOccupiedSquares);

// reset array to -1
  resetArray(blackPossibleCaptures, 64);

// get the number of black pieces
  for (int i = 0; i < 16; i++) {

    if (blackOccupiedSquares[i] != -1) {

      pieceCount++;  

    } else {

      break;

    }

  }

// loop through all of black's pieces
  for (int i = 0; i < pieceCount; i++) {

    resetArray(piecePossibleCaptures, 32);

    currentType = board[blackOccupiedSquares[i]].type;

    squareToMove(blackOccupiedSquares[i], move.current);

    switch (currentType) {

      case -1:
        returnPawnMoves(move, board, previousBoard, piecePossibleCaptures, 2, exception);
        break;

      case -2:
        returnRookMoves(move, board, previousBoard, piecePossibleCaptures, 2, exception);
        break;

      case -3:
        returnKnightMoves(move, board, previousBoard, piecePossibleCaptures, 2, exception);
        break;

      case -4:
        returnBishopMoves(move, board, previousBoard, piecePossibleCaptures, 2, exception);
        break;

      case -5:
        returnQueenMoves(move, board, previousBoard, piecePossibleCaptures, 2, exception);
        break;

      case -6:

        for (int j = 0; j < 8; j++) {
          
          currentOffset = blackOccupiedSquares[i] + kingOffsets[j];

          rowDifference = abs((currentOffset / 8) - (blackOccupiedSquares[i] / 8));
          columnDifference = abs((currentOffset % 8) - (blackOccupiedSquares[i] % 8));

          currentOffset = blackOccupiedSquares[i] + kingOffsets[j];

// check that move doesn't cross over the side of the board
          if (!(abs(rowDifference) > 1 || abs(columnDifference) > 1)) {

            piecePossibleCaptures[moveCount] = currentOffset;
            moveCount++;

          }

        }

        break;

    }

    for (int i = 0; i < 32; i++) {

      if (piecePossibleCaptures[i] != -1) {

        blackPossibleCaptures[piecePossibleCaptures[i]] = piecePossibleCaptures[i];

      } else {

        break;

      }

    }

  }

}

void returnAllPossibleMoves (struct piece board[64], struct piece previousBoard[64], struct pieceMove moves[128], int colour, int exception) {

  typedef struct pieceMove pieceMove;
  pieceMove tempMove;

  int whiteSquares[16];
  int blackSquares[16];
  int possibleCaptures[64];
  int currentSquare = 0, currentCapture = 0, moveCount = 0;

  resetArray(whiteSquares, 16);
  resetArray(blackSquares, 16);

  returnWhiteOccupiedSquares(board, whiteSquares);
  returnBlackOccupiedSquares(board, blackSquares);

  for (int i = 0; i < 16; i++) {

    resetArray(possibleCaptures, 64);

    currentSquare = whiteSquares[i];

    if (currentSquare == -1) {

      break;

    }

    squareToMove(currentSquare, tempMove.current);

    switch (board[currentSquare].type) {

      case 1:
        returnPawnMoves(tempMove, board, previousBoard, possibleCaptures, 1, exception);
        break;

      case 2:
        returnRookMoves(tempMove, board, previousBoard, possibleCaptures, 1, exception);
        break;

      case 3:
        returnKnightMoves(tempMove, board, previousBoard, possibleCaptures, 1, exception);
        break;

      case 4:
        returnBishopMoves(tempMove, board, previousBoard, possibleCaptures, 1, exception);
        break;

      case 5:
        returnQueenMoves(tempMove, board, previousBoard, possibleCaptures, 1, exception);
        break;

      case 6:
        returnKingMoves(tempMove, board, previousBoard, possibleCaptures, 1, exception);
        break;

    }

    for (int j = 0; j < 64; j++) {

      currentCapture = possibleCaptures[j];

      if (currentCapture == -1) {

        break;

      }

      squareToMove(currentCapture, tempMove.destination);
      moves[moveCount] = tempMove;
      moveCount++;

    }

  }

  for (int i = 0; i < 16; i++) {

    resetArray(possibleCaptures, 64);

    currentSquare = blackSquares[i];

    if (currentSquare == -1) {

      break;

    }

    squareToMove(currentSquare, tempMove.current);

    switch (board[currentSquare].type) {

      case 1:
        returnPawnMoves(tempMove, board, previousBoard, possibleCaptures, 2, exception);
        break;

      case 2:
        returnRookMoves(tempMove, board, previousBoard, possibleCaptures, 2, exception);
        break;

      case 3:
        returnKnightMoves(tempMove, board, previousBoard, possibleCaptures, 2, exception);
        break;

      case 4:
        returnBishopMoves(tempMove, board, previousBoard, possibleCaptures, 2, exception);
        break;

      case 5:
        returnQueenMoves(tempMove, board, previousBoard, possibleCaptures, 2, exception);
        break;

      case 6:
        returnKingMoves(tempMove, board, previousBoard, possibleCaptures, 2, exception);
        break;

    }

    for (int j = 0; j < 64; j++) {

      currentCapture = possibleCaptures[j];

      if (currentCapture == -1) {

        break;

      }

      squareToMove(currentCapture, tempMove.destination);
      moves[moveCount] = tempMove;
      moveCount++;

    }

  }

}

int isItCheckmate (struct piece board[64], struct piece previousBoard[64], int colour, int exception) {

  typedef struct pieceMove pieceMove;
  pieceMove move;

  int kingPosition, kingMovesCount = 0, matchesCount = 0;
  int kingMoves[64];
  int possibleCaptures[64];

  resetArray(kingMoves, 64);
  resetArray(possibleCaptures, 64);

// king cannot be in checkmate if king is not in check
/*
  if (isKingInCheck(board, previousBoard, colour) == 0) {

    return 0;

  }
*/
  for (int i = 0; i < 64; i++) {

    if ((board[i].type == 6 && colour == 1) || (board[i].type == -6 && colour == 2)) {

      kingPosition = i;
      break;

    }

  }

  squareToMove(kingPosition, move.current);

  returnKingMoves(move, board, previousBoard, kingMoves, colour, exception);

  if (colour == 1) {

    returnBlackPossibleCaptures(board, previousBoard, possibleCaptures, colour, exception);

  } else {

    returnWhitePossibleCaptures(board, previousBoard, possibleCaptures, colour, exception);

  }

// get number of valid king moves
  for (int i = 0; i < 64; i++) {

    if (kingMoves[i] != -1) {

      kingMovesCount++;

    } else {

      break;

    }

  }

// check to see if all the king valid moves match black possible captures
  for (int i = 0; i < 64; i++) {

    if (kingMoves[i] == -1) {

      break;

    }

    for (int j = 0; j < 64; j++) {

      if (kingMoves[i] == possibleCaptures[j]) {

        matchesCount++;
        break;

      }

    }

  }

  if (kingMovesCount == matchesCount) {

    return 1;

  }

  return 0;

}

void doRandomMove (struct piece board[64], struct piece previousBoard[64], int enemyOccupiedSquares[16], int colour, int exception) {

  typedef struct pieceMove pieceMove;
  pieceMove move;

  int chosenPiece, chosenMove, pieceCount = 0, moveCount = 0;
  int pieceMoves[64];

  resetArray(pieceMoves, 64);

// see how many pieces the other team has
  for (int i = 0; i < 16; i++) {

    if (enemyOccupiedSquares[i] != -1) {

      pieceCount++;  

    } else {

      break;

    }

  }

  while (moveCount == 0) {

    chosenPiece = rand() % pieceCount;

    squareToMove(chosenPiece, move.current);

// get moves for the randomly chosen piece
    switch (abs(board[chosenPiece].type)) {

      case 1:
        returnPawnMoves(move, board, previousBoard, pieceMoves, colour, exception);
        break;

      case 2:
        returnRookMoves(move, board, previousBoard, pieceMoves, colour, exception);
        break;

      case 3:
        returnKnightMoves(move, board, previousBoard, pieceMoves, colour, exception);
        break;

      case 4:
        returnBishopMoves(move, board, previousBoard, pieceMoves, colour, exception);
        break;

      case 5:
        returnQueenMoves(move, board, previousBoard, pieceMoves, colour, exception);
        break;

      case 6:
        returnKingMoves(move, board, previousBoard, pieceMoves, colour, exception);
        break;

    }

// see how many moves the chosen piece has
    for (int i = 0; i < 64; i++) {

      if (pieceMoves[i] != -1) {

        moveCount++;  

      } else {

        break;

      }

    }

  }

  chosenMove = rand() % moveCount;

  squareToMove(pieceMoves[chosenMove], move.destination);

  doMove(move, board[chosenPiece], board, previousBoard, colour, exception);

}

int depthTest (struct piece board[64], struct piece previousBoard[64], int colour, int exception, int depth) {

  if (depth == 0) {

    return 1;

  }

  int numPositions = 0, currentPosition, destinationPosition;

  typedef struct pieceMove pieceMove;
  pieceMove moves [128] = {0};

  returnAllPossibleMoves(board, previousBoard, moves, colour, exception);

  for (int i = 0; i < 128; i++) {

    if (moves[i].current[0] == '\0') {

      break;

    }

    moveToSquare(moves[i], &currentPosition, &destinationPosition);

    doMove(moves[i], board[currentPosition], board, previousBoard, colour, exception);
    numPositions += depthTest(board, previousBoard, colour, exception, depth-1);
    undoMove(moves[i], board[destinationPosition], board, previousBoard, colour);
    //printf("moves[%d].current = %s  and moves[%d].destination = %s\n", i, moves[i].current, i, moves[i].destination);

  }

  return numPositions;

}