#include<iostream>
#include <limits>
#include <vector>
#include "search.h"
int negamax(const GameState& state ,int depth,int alpha,int beta){
    std::vector<Move> moves=generateLegalMoves(state); 
    Color color=state.WhiteToMove? Color::White: Color::Black;
if(moves.empty()){
    if(state.inCheck(color)){
        return -100000000 - depth;
    }
    return 0;
}
    if(depth==0){
        int eval=evaluation(state);
        return color==Color::White? eval:-eval;
    }


    int bestScore=std::numeric_limits<int>::min()+1;
    for(const auto& move: moves){
        GameState next=state;
        next.Makemove(move);
        
        int score=-negamax(next,depth-1,-beta,-alpha);
        if(move.type==MoveType::Promotion) score+=300;
        if(move.type==MoveType::KingSideCastle||move.type==MoveType::QueenSideCastle) score+=500;
        if(score>bestScore) {bestScore=score;}
        if(bestScore>alpha){alpha=bestScore;}
        if(alpha>=beta) {break;}

    
    }
return bestScore;




}


Move selectBestMove(const GameState& state, int depth){
std::vector<Move> moves=generateLegalMoves(state);
if(moves.empty()){
    return Move{-1,-1};
}
Move bestMove=moves.front();
Color color=state.WhiteToMove? Color::White:Color::Black;
int alpha=std::numeric_limits<int>::min()+1;
int bestScore=std::numeric_limits<int>::min()+1;
int beta=std::numeric_limits<int>::max();
int score;
for(const auto& move:moves){
    GameState next=state;
    next.Makemove(move);
    score=-negamax(next,depth-1,-beta,-alpha);
   
    if (score>bestScore){
        bestScore=score;
        bestMove=move;
    }
    if(bestScore>alpha){
        alpha=bestScore;
    }
}
return bestMove;
}