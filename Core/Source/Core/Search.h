#pragma once
#include <iostream>
#include <algorithm>
#include <chrono>
#include "Board.h"
#include "Evaluation.h"
#include "Movegen.h"
#include "types.h"

using Clock=std::chrono::steady_clock;
struct Timeup{};
struct SearchLimits{
    Clock::time_point startTime;
    long long timeLimitsMs;
};
inline SearchLimits g_limits;
inline long long g_nodeCount;
inline int PieceValue(PieceType t){
    switch(t){
        case PieceType::Pawn: return 100;
        case PieceType::Knight: return 330;
        case PieceType::Bishop: return 320;
        case PieceType::Rook: return 500;
        case PieceType::Queen: return 900;
        default: return 0;
        
    }
}
inline void CheckTime(){
    if((++g_nodeCount&2047)==0){
        auto elapsed= std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now()-g_limits.startTime).count();
        if(elapsed>=g_limits.timeLimitsMs) throw Timeup{};
    }
}
inline int moveScore(const GameState& state, const Move& move){
    bool isCapture=(move.type==MoveType::Capture||move.type==MoveType::PromotionCapture||move.type==MoveType::Enpassant);
    if(isCapture){
        PieceType victim=(move.type==MoveType::Enpassant)?PieceType::Pawn: state.getPiece(move.to).type;
        PieceType attacker=state.getPiece(move.from).type;

        return 100000 + PieceValue(victim) *10 -PieceValue(attacker);
    }
    if(move.type==MoveType::Promotion){
        return 90000;
    }
    return 0;
}
inline void orderMoves(const GameState& state, std::vector<Move>& moves){
    std::sort(moves.begin(),moves.end(),[&state](const Move& a,const Move& b){
        return moveScore(state,a)>moveScore(state,b);
    });
}



int negamax(const GameState& state, int depth,int alpha,int beta);


Move selectBestMove(const GameState& state, int maxDepth,long long timeLimitMs);