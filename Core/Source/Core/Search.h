#pragma once
#include "Board.h"
#include "Evaluation.h"
#include "Movegen.h"
#include "types.h"

int negamax(const GameState& state, int depth,int alpha,int beta);
Move selectBestMove(const GameState& state, int depth);