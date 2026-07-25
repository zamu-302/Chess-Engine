#pragma once
#include <iostream>
#include <vector>
#include "Board.h"
#include "types.h"

std::vector<Move> generatePseudoLegalMoves(const GameState& state);
std::vector<Move> generateLegalMoves(const GameState& state);


//helpers
void generatePawnMoves(const GameState& state, int row, int col,std::vector<Move>& moves);
void generateQueenMoves(const GameState& state, int row, int col,std::vector<Move>& moves);
void generateRookMoves(const GameState& state, int row, int col,std::vector<Move>& moves);
void generateKnightMoves(const GameState& state, int row, int col,std::vector<Move>& moves);
void generateBishopMoves(const GameState& state, int row, int col,std::vector<Move>& moves);
void generateKingMoves(const GameState& state, int row, int col,std::vector<Move>& moves);