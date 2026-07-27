#include<iostream>
#include <limits>
#include <vector>
#include "search.h"


int maxi(const GameState& state,int depth){
    if (depth==1){
        return Score();
    }
    int max=std::numeric_limits<int>::min();
    std::vector<Move> moves= generateLegalMoves(state);
    for(const auto& move:moves){
        int score=mini(state,depth-1);
        if(score>max){
            max=score;
        }

    }
    return max;
}
int mini(const GameState& state, int depth){
    if(depth==1){
        return -Score();
    }
    int min=std::numeric_limits<int>::max();
    std::vector<Move> moves=generateLegalMoves(state);
    for(const auto&move:moves){
        int score=maxi(state,depth-1);
        if(score<min){
            min=score;
        }
    }
    return min;
}
