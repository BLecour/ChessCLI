#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct piece {

  int type;
  int moves;

};

struct pieceMove {

  char current [5];
  char destination [5];

};

void printBoard (struct piece board[64]);

void printBlackBoard (struct piece board[64]);

void printPiece (int num);

int isMoveValid (struct pieceMove, struct piece board[64], int colour);

int isPawnMoveValid (struct pieceMove, struct piece board[64], int colour);

int isRookMoveValid (struct pieceMove, struct piece board[64], int colour);

int isKnightMoveValid (struct pieceMove, struct piece board[64], int colour);

int isBishopMoveValid (struct pieceMove, struct piece board[64], int colour);

int isQueenMoveValid (struct pieceMove, struct piece board[64], int colour);

int isKingMoveValid (struct pieceMove, struct piece board[64], int colour);

void doMove (struct pieceMove, struct piece piece, struct piece board[64], int colour);

void moveToCoordinates(struct pieceMove, int * currentPosition, int * destinationPosition);