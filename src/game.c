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

    if (board[i].type > 0) {

      blackOccupiedSquares[count] = i;
      count++; 

    }

  }

}

void returnWhitePossibleCaptures (struct piece board[64], int whitePossibleCaptures[64], int colour) {

  printf("*********************************** RETURN WHITE CAPTURES *******************************************\n");

  typedef struct pieceMove pieceMove;
  pieceMove move;

  int piecePossibleCaptures[32];
  int whiteOccupiedSquares[16];
  int pieceCount = 0, currentType;

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

  printf("There are %d white pieces\n", pieceCount);

// loop through all of white's pieces
  for (int i = 0; i < pieceCount; i++) {

    resetArray(piecePossibleCaptures, 32);

    currentType = board[whiteOccupiedSquares[i]].type;

    squareToMove(whiteOccupiedSquares[i], move.current);

    printf("looking at #%d white piece, it is of type %d and at coordinate %s and whiteOccupiedSquares[%d] = %d\n", i, currentType, move.current, i, whiteOccupiedSquares[i]);

    switch (currentType) {

      case 1:
      returnPawnMoves(move, board, piecePossibleCaptures, colour);
      break;

      case 2:
      returnRookMoves(move, board, piecePossibleCaptures, colour);
      break;

      case 3:
      returnKnightMoves(move, board, piecePossibleCaptures, colour);
      break;

      case 4:
      returnBishopMoves(move, board, piecePossibleCaptures, colour);
      break;

      case 5:
      returnQueenMoves(move, board, piecePossibleCaptures, colour);
      break;

      case 6:
      returnKingMoves(move, board, piecePossibleCaptures, colour);
      break;

    }

    for (int i = 0; i < 32; i++) {

      if (piecePossibleCaptures[i] != -1) {

        whitePossibleCaptures[piecePossibleCaptures[i]] = piecePossibleCaptures[i];

        printf("White capture at %d", piecePossibleCaptures[i]);

      } else {

        break;

      }

    }

  }

}

void returnBlackPossibleCaptures (struct piece board[64], int blackPossibleCaptures[64], int colour) {

  printf("*********************************** RETURN BLACK CAPTURES *******************************************\n");

  typedef struct pieceMove pieceMove;
  pieceMove move;

  int piecePossibleCaptures[32];
  int blackOccupiedSquares[16];
  int pieceCount = 0, currentType;

  returnWhiteOccupiedSquares(board, blackOccupiedSquares);

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

  printf("There are %d black pieces\n", pieceCount);

// loop through all of black's pieces
  for (int i = 0; i < pieceCount; i++) {

    resetArray(piecePossibleCaptures, 32);

    currentType = board[blackOccupiedSquares[i]].type;

    squareToMove(blackOccupiedSquares[i], move.current);

    printf("looking at #%d black piece, it is of type %d and at coordinate %s and blackOccupiedSquares[%d] = %d\n", i, currentType, move.current, i, blackOccupiedSquares[i]);

    switch (currentType) {

      case 1:
      returnPawnMoves(move, board, piecePossibleCaptures, colour);
      break;

      case 2:
      returnRookMoves(move, board, piecePossibleCaptures, colour);
      break;

      case 3:
      returnKnightMoves(move, board, piecePossibleCaptures, colour);
      break;

      case 4:
      returnBishopMoves(move, board, piecePossibleCaptures, colour);
      break;

      case 5:
      returnQueenMoves(move, board, piecePossibleCaptures, colour);
      break;

      case 6:
      returnKingMoves(move, board, piecePossibleCaptures, colour);
      break;

    }

    for (int i = 0; i < 32; i++) {

      if (piecePossibleCaptures[i] != -1) {

        blackPossibleCaptures[piecePossibleCaptures[i]] = piecePossibleCaptures[i];

        printf("Black capture at %d\n", piecePossibleCaptures[i]);

      } else {

        break;

      }

    }

  }

}

void enemyDoRandomMove (struct piece board[64], int enemyOccupiedSquares[16], int colour) {

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

    printf("randomly chosen piece = %d\n", chosenPiece);

    squareToMove(chosenPiece, move.current);

// get moves for the randomly chosen piece
    switch (abs(board[chosenPiece].type)) {

      case 1:
      returnPawnMoves(move, board, pieceMoves, colour);
      break;

      case 2:
      returnRookMoves(move, board, pieceMoves, colour);
      break;

      case 3:
      returnKnightMoves(move, board, pieceMoves, colour);
      break;

      case 4:
      returnBishopMoves(move, board, pieceMoves, colour);
      break;

      case 5:
      returnQueenMoves(move, board, pieceMoves, colour);
      break;

      case 6:
      returnKingMoves(move, board, pieceMoves, colour);
      break;

    }

// see how many moves the chosen piece has
    for (int i = 0; i < 64; i++) {

      if (pieceMoves[i] != -1) {

        printf("RANDOMLY CHOSEN PIECE CAN MOVE TO %d\n", pieceMoves[i]);

        moveCount++;  

      } else {

        break;

      }

    }

  }

  chosenMove = rand() % moveCount;

  printf("randomly chosen move = %d\n", pieceMoves[chosenMove]);

  squareToMove(pieceMoves[chosenMove], move.destination);

  doMove(move, board[chosenPiece], board, colour);

}