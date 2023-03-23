#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct piece {

  int type;
  int moves;

};

struct pieceMove {

  char current [5];
  char destination [5];

};

// print.c
void printBoard (struct piece board[64]);

void printBlackBoard (struct piece board[64]);

void printPiece (int num);

void printPossibleMoves (struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int colour);

void resetArray(int * array, int len);

// game.c
void returnWhiteOccupiedSquares (struct piece board[64], int whiteOccupiedSquares[16]);

void returnBlackOccupiedSquares (struct piece board[64], int blackOccupiedSquares[16]);

void returnWhitePossibleCaptures (struct piece board[64], struct piece previousBoard[64], int whitePossibleCaptures[64], int colour);

void returnBlackPossibleCaptures (struct piece board[64], struct piece previousBoard[64], int blackPossibleCaptures[64], int colour);

void enemyDoRandomMove (struct piece board[64], struct piece previousBoard[64], int enemyOccupiedSquares[16], int colour);

// move.c
int isMoveValid (struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int colour);

int isAnyMoveValid (struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int colour);

int isPawnMoveValid (struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int colour);

int isRookMoveValid (struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int colour);

int isKnightMoveValid (struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int colour);

int isBishopMoveValid (struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int colour);

int isQueenMoveValid (struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int colour);

int isKingMoveValid (struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int colour);

int isKingInCheck (struct piece board[64], struct piece previousBoard[64], int colour);

int canKingCastle (struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int colour);

void doMove (struct pieceMove move, struct piece piece, struct piece board[64], struct piece previousBoard[64], int colour);

void returnPawnMoves(struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int pawnMoves[64], int colour);

void returnPawnCaptures(struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int pawnCaptures[64], int colour);

void returnRookMoves(struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int rookMoves[64], int colour);

void returnKnightMoves(struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int knightMoves[64], int colour); 

void returnBishopMoves(struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int bishopMoves[64], int colour);

void returnQueenMoves(struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int queenMoves[64], int colour); 

void returnKingMoves(struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int kingMoves[64], int colour); 

void moveToSquare(struct pieceMove move, int * currentPosition, int * destinationPosition);

void squareToMove(int squareNum, char coordinate [5]);