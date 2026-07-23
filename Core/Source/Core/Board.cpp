#include <iostream>
#include <vector>
#include <unordered_set>
#include "types.h"


class GameState{
public:

void LoadFEN(const std::string & fen);
std::string toFEN()const;
void Makemove(Move move);
void UndoMove();
GameState() {
    LoadFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}
private:
PieceType board[8][8];
std::string fen;
bool whiteToMove;
bool castlingKingSideWhite,castlingQueenSideWhite;
bool castlingKingSideBlack,castlingQueenSideBlack;
int enPassantTargetRow,enPassantTargetcol;
int fULLMoveClock;
int halfMoveClock;
};

