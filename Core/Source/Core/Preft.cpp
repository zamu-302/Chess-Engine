#include <iostream>
#include "Preft.h"

int preft(const GameState& state, int depth){
    if(depth==0){
        return 1;
    }

    std::vector<Move>moves=generateLegalMoves(state);
    int node=0;
    for(const auto&move:moves){
        GameState copy=state;
        copy.Makemove(move);
        node+=preft(copy,depth-1);
    }
    return node;
}