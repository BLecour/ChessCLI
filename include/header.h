#include <stdio.h>
#include <stdlib.h>

struct piece {

  int type;
  int moves;

};

struct pieceMove {

  char current [2];
  char destination [2];

};

void printBoard (struct piece board[8][8]);

void printBlackBoard (struct piece board[8][8]);

void printPiece (int num);

int isMoveValid (struct pieceMove, struct piece board[8][8], int colour);

int isPawnMoveValid (struct pieceMove, struct piece board[8][8], int colour);

int isRookMoveValid (struct pieceMove, struct piece board[8][8], int colour);

int isKnightMoveValid (struct pieceMove, struct piece board[8][8], int colour);

int isBishopMoveValid (struct pieceMove, struct piece board[8][8], int colour);

int isQueenMoveValid (struct pieceMove, struct piece board[8][8], int colour);

int isKingMoveValid (struct pieceMove, struct piece board[8][8], int colour);

void doMove (struct pieceMove, struct piece board[8][8], int colour);

int moveToPositionX (char coordinate [2]);

int moveToPositionY (char coordinate [2]);