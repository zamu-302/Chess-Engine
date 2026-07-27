#pragma once 
#include <iostream>
#include <string>
#include <utility>
#include "types.h"

class GameState{
public:

void LoadFEN(const std::string & fen);
std::string toFEN()const;

Piece getPiece(int row,int col) const;
Color getTurn()const;
void Makemove(const Move& move);
void UndoMove();
int getEnPassantTargetcol() const;
int getEnPassantTargetrow()const ;
bool inCheck();
std::pair<bool, bool> getCastlingRights(Color c) const;
GameState() {
    LoadFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}
private:
Piece board[8][8];
bool WhiteToMove=true;
bool castlingKingSideWhite=true;
bool castlingQueenSideWhite=true;
bool castlingKingSideBlack=true;
bool castlingQueenSideBlack=true;
int enPassantTargetRow=-1;
int enPassantTargetcol=-1;
int fullMoveClock=1;
int halfMoveClock=0;
};
