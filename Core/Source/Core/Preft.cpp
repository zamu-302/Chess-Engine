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
void splitPreft(const GameState& state, int depth) {
    std::vector<Move> moves = generateLegalMoves(state);
    int total = 0;
    for (const auto& move : moves) {
        GameState copy = state;
        copy.Makemove(move);
        int nodes = preft(copy, depth - 1);
        total += nodes;
        // print move in algebraic notation + node count
        std::cout << (char)('a' + move.from % 8) << (move.from / 8 + 1)
                  << (char)('a' + move.to % 8)   << (move.to / 8 + 1)
                  << " : " << nodes << "\n";
    }
    std::cout << "Total: " << total << "\n";
}