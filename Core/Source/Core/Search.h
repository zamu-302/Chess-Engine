#pragma once
#include "Board.h"
#include "Evaluation.h"
#include "Movegen.h"
#include "types.h"

int maxi(const GameState& state,int depth);
int mini(const GameState& state,int depth);
int alphaBetaPruning(const GameState& state,int depth);
Move selectBestMove(const GameState& state, int depth);