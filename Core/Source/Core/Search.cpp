#include<iostream>
#include <limits>
#include <vector>
#include <random>
#include "search.h"

void initZobrist() {
    std::mt19937_64 rng(12345678ULL); 
    for (int c = 0; c < 2; c++){
        for (int pt = 0; pt < 6; pt++){
            for (int sq = 0; sq < 64; sq++){
                zobristTabel[c][pt][sq] = rng();
        }   }
    }   
    zobristSideKey = rng();
}
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
    orderMoves(state,capture,0);
    for (const auto& move : capture) {
        GameState next = state;
        next.Makemove(move);
        int score = -quiescence(next, -beta, -alpha);
        if (score >= beta) return beta;
        if (score > alpha) alpha = score;
    }
    return alpha;
}
int negamax(const GameState& state ,int depth,int alpha,int beta,std::vector<uint64_t>& history){
    CheckTime();
    if(state.getHalfMoveClock()>=100) return 0;
    uint64_t hash=state.getHash();

    int occurrences=0;
    for(uint64_t h:history) if(h==hash) occurrences++;
    if(occurrences>=2) return 0;


    int alphaOrig=alpha;
    TTEntry& entry= transpositionTable[hash%TT_SIZE];
    if(entry.hash==hash && entry.depth>=depth){
        if(entry.flag==TTEntry::EXACT) return entry.score;
        if(entry.flag==TTEntry::LOWER){
          alpha=std::max(alpha,entry.score);
          if(alpha>=beta) return entry.score; 
            
        }
        if(entry.flag==TTEntry::UPPER)  {
            beta=std::min(beta,entry.score);
            if(alpha>=beta) return entry.score; 
        }
        if(alpha>=beta) return entry.score;
    }

    std::vector<Move> moves=generateLegalMoves(state); 
    orderMoves(state,moves,depth);
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
    Move bestMoveHere=moves.front();
    for(const auto& move: moves){
        GameState next=state;
        next.Makemove(move);

        history.emplace_back(hash);
        int score=-negamax(next,depth-1,-beta,-alpha,history);
        history.pop_back();

        if(score>bestScore) {bestScore=score; bestMoveHere=move;}
        if(bestScore>alpha){alpha=bestScore;}
        if(alpha>=beta) {
            if(move.type==MoveType::Normal&&depth<128){
            killerMoves[depth][1]=killerMoves[depth][0];
            killerMoves[depth][0]=move;
            }
            break;
        }
       

    
    }
TTEntry::Flag flag;
if (bestScore <= alphaOrig) flag = TTEntry::UPPER;
else if (bestScore >= beta) flag = TTEntry::LOWER;
else flag = TTEntry::EXACT;

transpositionTable[hash % TT_SIZE] = {hash, depth, bestScore, bestMoveHere, flag};

return bestScore;




}


Move selectBestMove(const GameState& state, int maxDepth, long long timeLimitMs,std::vector<uint64_t> gameHistory){
std::vector<Move> RootMoves=generateLegalMoves(state);
if(RootMoves.empty()){
    return Move{-1,-1};
}
g_nodeCount=0;
g_limits.startTime=Clock::now();
g_limits.timeLimitsMs=timeLimitMs;

Move bestMove=RootMoves.front();//as a fallback
uint64_t rootHash=state.getHash();

for(int depth=1;depth<=maxDepth;depth++){
    try{
        std::vector moves=RootMoves;
        orderMoves(state,moves,depth);
        int alpha= std::numeric_limits<int>::min() + 1;
        int beta= std::numeric_limits<int>::max();
        Move bestMoveinDepth= moves.front();
        int bestScoreinDepth= std::numeric_limits<int>::min() + 1;

        for(const auto& move:moves){
            GameState next=state;
            next.Makemove(move);

            std::vector<uint64_t> history=gameHistory;
            history.emplace_back(rootHash);
            int score=-negamax(next,depth-1,-beta,-alpha,history);

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