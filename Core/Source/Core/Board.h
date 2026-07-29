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

void Makemove(const Move& move);
void unMakeMove(const Move& move);
bool getTurn()const;
void UndoMove();
int getEnPassantTargetcol() const;
int getEnPassantTargetrow()const;
bool inCheck()const;
std::pair<bool, bool> getCastlingRights() const;
GameState() {
    LoadFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

Piece board;
private:
bool WhiteToMove=true;
bool castlingKingSideWhite=true;
bool castlingQueenSideWhite=true;
bool castlingKingSideBlack=true;
bool castlingQueenSideBlack=true;
int enPassantTargetRow=-1;
int enPassantTargetcol=-1;
int fullMoveClock=1;
int halfMoveClock=0;
void setPiece(int square,PieceType piece,Color color);

};
