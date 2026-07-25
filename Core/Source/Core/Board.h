#pragma once 
#include <iostream>
#include "types.h"

class GameState{
public:

void LoadFEN(const std::string & fen);
std::string toFEN()const;

Piece getPiece(int row,int col) const;
Color getTurn()const;
void Makemove(Move move);
void UndoMove();
int getEnPassantTargetcol();
int getEnPassantTargetrow();
bool inCheck();

GameState() {
    LoadFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}
private:
Piece board[8][8];
bool WhiteToMove=true;
bool castlingKingSideWhite=false;
bool castlingQueenSideWhite=false;
bool castlingKingSideBlack=false;
bool castlingQueenSideBlack=false;
int enPassantTargetRow=-1;
int enPassantTargetcol=-1;
int fullMoveClock=1;
int halfMoveClock=0;
};