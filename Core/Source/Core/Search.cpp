#include<iostream>
#include <limits>
#include <vector>
#include "search.h"


int maxi(const GameState& state,int depth){
    std::vector<Move> moves=generateLegalMoves(state);
    Color color=state.WhiteToMove? Color::White:Color::Black;
   
    if (moves.empty()) {
        
        if (state.inCheck(color)) {
            return -100000 + depth;  
        } else {
            return 0;  
        }
    }
    if(depth==0){
        return evaluation(state);
    }
    int max=std::numeric_limits<int>::min();
    for(const auto& move:moves){
        GameState newstate=state;
        newstate.Makemove(move);
        int score=mini(newstate,depth-1);
        if(score>max){
            max=score;
        }

    }
    return max;
}
int mini(const GameState& state, int depth){
    std::vector<Move> moves=generateLegalMoves(state);
    Color color=state.WhiteToMove? Color::White:Color::Black;
    if (moves.empty()) {
        if (state.inCheck(color)) {
            return 100000 - depth;  
        } else {
            return 0;  
        }
    }
    if(depth==0){
        return evaluation(state);
    }
    int min=std::numeric_limits<int>::max();
    
    for(const auto&move:moves){
        GameState newstate=state;
        newstate.Makemove(move);
        int score=maxi(newstate,depth-1);
        if(score<min){
            min=score;
        }
    }
    return min;
}
Move selectBestMove(const GameState& state, int depth){
std::vector<Move> moves=generateLegalMoves(state);
if(moves.empty()){
    return Move{-1,-1};
}
Move bestMove=moves.front();
Color color=state.WhiteToMove? Color::White:Color::Black;
int bestScore=(color==Color::White)?std::numeric_limits<int>::min(): std::numeric_limits<int>::max();
for(const auto& move:moves){
    GameState next=state;
    next.Makemove(move);
    int score=(color==Color::White)?mini(next,depth-1):maxi(next,depth-1);
    if ((color==Color::White&& score>bestScore)||(color==Color::Black&&score<bestScore)){
        bestScore=score;
        bestMove=move;
    }
}
return bestMove;
}