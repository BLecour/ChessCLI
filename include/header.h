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

void printPossibleMoves (struct pieceMove move, struct piece board[64], int colour);

int isMoveValid (struct pieceMove move, struct piece board[64], int colour);

int isAnyMoveValid (struct pieceMove move, struct piece board[64], int colour);

int isPawnMoveValid (struct pieceMove move, struct piece board[64], int colour);

int isRookMoveValid (struct pieceMove move, struct piece board[64], int colour);

int isKnightMoveValid (struct pieceMove move, struct piece board[64], int colour);

int isBishopMoveValid (struct pieceMove move, struct piece board[64], int colour);

int isQueenMoveValid (struct pieceMove move, struct piece board[64], int colour);

int isKingMoveValid (struct pieceMove move, struct piece board[64], int colour);

void doMove (struct pieceMove move, struct piece piece, struct piece board[64], int colour);

void returnPawnMoves(struct pieceMove move, struct piece board[64], int pawnMoves[64], int colour);

void returnRookMoves(struct pieceMove move, struct piece board[64], int rookMoves[64], int colour);

void returnKnightMoves(struct pieceMove move, struct piece board[64], int knightMoves[64], int colour); 

void returnBishopMoves(struct pieceMove move, struct piece board[64], int bishopMoves[64], int colour);

void returnQueenMoves(struct pieceMove move, struct piece board[64], int queenMoves[64], int colour); 

void returnKingMoves(struct pieceMove move, struct piece board[64], int kingMoves[64], int colour); 

void moveToSquare(struct pieceMove move, int * currentPosition, int * destinationPosition);

void squareToMove(int squareNum, char coordinate [5]);