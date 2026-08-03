#pragma once
#include <iostream>
#include <vector>
#include "Board.h"
#include "types.h"
#include "Lookuptabel.h"

std::vector<Move> generatePseudoLegalMoves(const GameState& state);
std::vector<Move> generateLegalMoves(const GameState& state);



//helpers
void generatePawnMoves(const GameState& state,std::vector<Move>& moves,Color color);
void generateQueenMoves(const GameState& state,std::vector<Move>& moves,Color color);
void generateRookMoves(const GameState& state,std::vector<Move>& moves,Color color);
void generateKnightMoves(const GameState& state,std::vector<Move>& moves,Color color);
void generateBishopMoves(const GameState& state,std::vector<Move>& moves, Color color);
void generateKingMoves(const GameState& state,std::vector<Move>& moves, Color color);
inline uint64_t getRookAttacks(int sq, uint64_t occupied);
inline uint64_t getBishopAttacks(int sq, uint64_t occupied);