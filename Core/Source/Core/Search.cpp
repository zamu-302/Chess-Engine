#include<iostream>
#include <limits>
#include <vector>
#include "search.h"


int maxi(const GameState& state,int depth){
    std::vector<Move> moves=generateLegalMoves(state);
   
    if (moves.empty()) {
        if (state.inCheck()) {
            return -100000 + depth;  
        } else {
            return 0;  
        }
    }
    if(depth==0){
        return evaluate(state);
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
    
    if (moves.empty()) {
        if (state.inCheck()) {
            return 100000 - depth;  
        } else {
            return 0;  
        }
    }
    if(depth==0){
        return evaluate(state);
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
