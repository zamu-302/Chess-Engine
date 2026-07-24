#include <iostream>
#include "types.h"

class GameState{
public:

void LoadFEN(const std::string & fen);
std::string toFEN()const;
void Makemove(Move move);
void UndoMove();
bool inCheck();
GameState() {
    LoadFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}
private:
PieceType board[8][8]={};
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