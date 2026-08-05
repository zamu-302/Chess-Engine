#pragma once 
#include <iostream>
#include <string>
#include <utility>
#include "types.h"


class GameState{
public:

void LoadFEN(const std::string & fen);
Piece getPiece(int square) const;
void Makemove(const Move& move);
void clearState(int sq);
int getEnPassantTargetcol() const;
int getEnPassantTargetrow()const;
uint64_t blackPiece()const;
uint64_t whitePiece()const;
bool isEnemyPiece(int pos, Color color);
bool inCheck(Color kingColor)const;
bool squareAttacked(const GameState& state, int square,Color color)const;
std::pair<bool, bool> getCastlingRights() const;
GameState() {
    LoadFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
   
}

Postion board;
bool WhiteToMove=true;
private:
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
