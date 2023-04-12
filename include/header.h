#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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
void fenDecode (struct piece board[64], struct piece previousBoard[64], char FEN[100], int * turn);

void printBoard (struct piece board[64]);

void printBlackBoard (struct piece board[64]);

void printPiece (int num);

void printPossibleMoves (struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int colour, int exception);

void resetArray(int * array, int len);

// game.c
void returnWhiteOccupiedSquares (struct piece board[64], int whiteOccupiedSquares[16]);

void returnBlackOccupiedSquares (struct piece board[64], int blackOccupiedSquares[16]);

void returnWhitePossibleCaptures (struct piece board[64], struct piece previousBoard[64], int whitePossibleCaptures[64], int colour, int exception);

void returnBlackPossibleCaptures (struct piece board[64], struct piece previousBoard[64], int blackPossibleCaptures[64], int colour, int exception);

int isItCheckmate (struct piece board[64], struct piece previousBoard[64], int colour, int exception);

void doRandomMove (struct piece board[64], struct piece previousBoard[64], int occupiedSquares[16], int colour, int exception);

// move.c
int isMoveValid (struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int colour, int exception);

int isAnyMoveValid (struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int colour, int exception);

int isPawnMoveValid (struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int colour, int exception);

int isRookMoveValid (struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int colour, int exception);

int isKnightMoveValid (struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int colour, int exception);

int isBishopMoveValid (struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int colour, int exception);

int isQueenMoveValid (struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int colour, int exception);

int isKingMoveValid (struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int colour, int exception);

int isKingInCheck (struct piece board[64], struct piece previousBoard[64], int colour, int exception);

int canKingCastle (struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int colour, int exception);

int canPawnEnPassant (struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int colour);

int isPieceProtected (struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int colour);

void doMove (struct pieceMove move, struct piece piece, struct piece board[64], struct piece previousBoard[64], int colour, int exception);

void undoMove (struct pieceMove move, struct piece piece, struct piece board[64], struct piece previousBoard[64], int colour);

void returnPawnMoves(struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int pawnMoves[64], int colour, int exception);

void returnPawnCaptures(struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int pawnCaptures[64], int colour, int exception);

void returnRookMoves(struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int rookMoves[64], int colour, int exception);

void returnKnightMoves(struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int knightMoves[64], int colour, int exception); 

void returnBishopMoves(struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int bishopMoves[64], int colour, int exception);

void returnQueenMoves(struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int queenMoves[64], int colour, int exception); 

void returnKingMoves(struct pieceMove move, struct piece board[64], struct piece previousBoard[64], int kingMoves[64], int colour, int exception); 

void moveToSquare(struct pieceMove move, int * currentPosition, int * destinationPosition);

void squareToMove(int squareNum, char coordinate [5]);