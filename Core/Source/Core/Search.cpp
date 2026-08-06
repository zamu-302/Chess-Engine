#include<iostream>
#include <limits>
#include <vector>
#include "search.h"
int quiescence(const GameState& state, int alpha,int beta){
    CheckTime();
    Color color=state.WhiteToMove? Color::White:Color::Black;
    int standPat=evaluation(state);
    standPat=(color==Color::White)?standPat: -standPat;

    if(standPat>=beta) return beta;
    if(standPat>alpha) alpha=standPat;


    std::vector<Move> moves=generateLegalMoves(state);
    std::vector<Move> capture;
    for(auto& m:moves){
        if(m.type==MoveType::Capture||m.type==MoveType::PromotionCapture||m.type==MoveType::Enpassant||m.type==MoveType::Promotion){
            capture.emplace_back(m);
        }
    }
    orderMoves(state,capture);
    for (const auto& move : capture) {
        GameState next = state;
        next.Makemove(move);
        int score = -quiescence(next, -beta, -alpha);
        if (score >= beta) return beta;
        if (score > alpha) alpha = score;
    }
    return alpha;
}
int negamax(const GameState& state ,int depth,int alpha,int beta){
    std::vector<Move> moves=generateLegalMoves(state); 
    orderMoves(state,moves);
    Color color=state.WhiteToMove? Color::White: Color::Black;
if(moves.empty()){
    if(state.inCheck(color)){
        return -100000000 - depth;
    }
    return 0;
}
    if(depth==0){
        return quiescence(state,alpha,beta);
    }


    int bestScore=std::numeric_limits<int>::min()+1;
    for(const auto& move: moves){
        GameState next=state;
        next.Makemove(move);
        
        int score=-negamax(next,depth-1,-beta,-alpha);
        if(score>bestScore) {bestScore=score;}
        if(bestScore>alpha){alpha=bestScore;}
        if(alpha>=beta) {break;}

    
    }
return bestScore;




}


Move selectBestMove(const GameState& state, int maxDepth, long long timeLimitMs){
std::vector<Move> RootMoves=generateLegalMoves(state);
if(RootMoves.empty()){
    return Move{-1,-1};
}
g_nodeCount=0;
g_limits.startTime=Clock::now();
g_limits.timeLimitsMs=timeLimitMs;

Move bestMove=RootMoves.front();//as a fallback

for(int depth=1;depth<=maxDepth;depth++){
    try{
        std::vector moves=RootMoves;
        orderMoves(state,moves);
        int alpha= std::numeric_limits<int>::min() + 1;
        int beta= std::numeric_limits<int>::max();
        Move bestMoveinDepth= moves.front();
        int bestScoreinDepth= std::numeric_limits<int>::min() + 1;
        for(const auto& move:moves){
            GameState next=state;
            next.Makemove(move);
            int score=-negamax(next,depth-1,-beta,-alpha);
            if (score > bestScoreinDepth) {
                bestScoreinDepth = score;
                bestMoveinDepth = move;
            }
            if (bestScoreinDepth > alpha){
                alpha = bestScoreinDepth;
            }
            
        }
        bestMove=bestMoveinDepth;
    }
    catch(Timeup&){
        break;
    }
}
return bestMove;
}