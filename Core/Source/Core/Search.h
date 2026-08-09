#pragma once
#include <iostream>
#include <algorithm>
#include <chrono>
#include "Board.h"
#include "Evaluation.h"
#include "Movegen.h"
#include "Lookuptabel.h"
#include "types.h"


void initZobrist();
using Clock=std::chrono::steady_clock;
struct Timeup{};
struct SearchLimits{
    Clock::time_point startTime;
    long long timeLimitsMs;
};
struct TTEntry{
    uint64_t hash;
    int depth;
    int score;
    Move bestMove;
    enum Flag{EXACT,LOWER,UPPER} flag;
};
inline int historyTable[2][64][64]={};
inline Move killerMoves[128][2];
const int TT_SIZE=1<<22;
inline TTEntry transpositionTable[TT_SIZE];
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
inline int moveScore(const GameState& state, const Move& move,int depth,const Move& ttMove){
    //TT move
    if(move.from==ttMove.from&& move.to==ttMove.to&& move.type==ttMove.type){
        return 200000;
    }
    
    //capture
    bool isCapture=(move.type==MoveType::Capture||move.type==MoveType::PromotionCapture||move.type==MoveType::Enpassant);
    if(isCapture){
        PieceType victim=(move.type==MoveType::Enpassant)?PieceType::Pawn: state.getPiece(move.to).type;
        PieceType attacker=state.getPiece(move.from).type;

        return 100000 + PieceValue(victim) *10 -PieceValue(attacker);
    }
    //promo
    if(move.type==MoveType::Promotion){
        return 90000;
    }
    //killer move
    auto moveEquals=[&](const Move &a,const Move &b){
        return a.from==b.from && a.to==b.to && a.type==b.type;
    };
    if(moveEquals(move,killerMoves[depth][0])||moveEquals(move,killerMoves[depth][1])){
        return 8000;
    }
    return historyTable[(int)state.WhiteToMove][move.from][move.to];
}
inline void orderMoves(const GameState& state, std::vector<Move>& moves,int depth,const Move& ttMove){
    std::sort(moves.begin(),moves.end(),[&](const Move& a,const Move& b){
        return moveScore(state,a,depth,ttMove)>moveScore(state,b,depth,ttMove);
    });
}




int negamax(const GameState& state, int depth,int alpha,int beta,std::vector<uint64_t>& history);


Move selectBestMove(const GameState& state, int maxDepth,long long timeLimitMs,std::vector<uint64_t> gameHistory);