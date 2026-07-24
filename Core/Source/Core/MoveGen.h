#include <iostream>
#include <vector>
#include "Board.h"
#include "types.h"

std::vector<Move> generateMoves(const GameState& state);
std::vector<Move> generateLegalMoves(const GameState& state);

//helpers
void generatePawnmoves(const GameState& state, int row, int col,std::vector<Move>& moves);
void generateQueenmoves(const GameState& state, int row, int col,std::vector<Move>& moves);
void generateRookmoves(const GameState& state, int row, int col,std::vector<Move>& moves);
void generateKnightmoves(const GameState& state, int row, int col,std::vector<Move>& moves);
void generateBishopmoves(const GameState& state, int row, int col,std::vector<Move>& moves);
void generateKingmoves(const GameState& state, int row, int col,std::vector<Move>& moves);