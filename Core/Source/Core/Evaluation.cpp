#include <iostream>
#include "Evaluation.h"


int evaluation(const GameState& state) {
int mg[2]={0,0}; //white/black
int eg[2]={0,0};
int phase=0;


uint64_t occupied=(state.blackPiece()|state.whitePiece());
int score=0;


while(occupied){
    int from = __builtin_ctzll(occupied);
    Piece piece=state.getPiece(from);
    int c=(piece.color==Color::White)? 0: 1;
    int pt= (int) piece.type;
    int idx=(c==0)? from:mirror64(from);
    switch (pt)
        {
        case 0:
            mg[c]+=pawnMg[idx];
            eg[c]+=pawnEg[idx];
            break;
        case 1:
            mg[c]+=knightMg[idx];
            eg[c]+=knightEg[idx];
            break;
        case 2:
            mg[c]+=bishopMg[idx];
            eg[c]+=bishopEg[idx];
            break;
        case 3:
            mg[c]+=rookMg[idx];
            eg[c]+=rookEg[idx];
            break;
        case 4:
            mg[c]+=queenMg[idx];
            eg[c]+=queenEg[idx];
            break;
        case 5:
            mg[c]+=kingMg[idx];
            eg[c]+=kingEg[idx];
            break;
        
        default:
            break;
        }
    
    mg[c]+=mgValue[pt];
    eg[c]+=egValue[pt];
    phase+= phaseWeight[pt];
    
    occupied &= occupied - 1;
}
//bishop Pair
    if (__builtin_popcountll(state.board.whiteBishop) >= 2) mg[0] += 30;
    if (__builtin_popcountll(state.board.blackBishop) >= 2) mg[1] += 30;
    //Rook on openFile
    uint64_t rooks = state.board.whiteRook;
    while (rooks) {
        int sq = __builtin_ctzll(rooks);
        int file = sq % 8;
        uint64_t fileMask = 0x0101010101010101ULL << file;
        if (!(fileMask & state.board.whitePawn)) { // no own pawn
            if (!(fileMask & state.board.blackPawn)) mg[0] += 20; // fully open
            else mg[0] += 10; // semi-open
        }
    rooks &= rooks - 1;
}
    rooks = state.board.blackRook;
    while (rooks) {
        int sq = __builtin_ctzll(rooks);
        int file = sq % 8;
        uint64_t fileMask = 0x0101010101010101ULL << file;
        if (!(fileMask & state.board.blackPawn)) { 
            if (!(fileMask & state.board.whitePawn)) mg[1] += 20; // fully open
            else mg[1] += 10; // semi-open
        }
    rooks &= rooks - 1;
}

    int mgScore=mg[0]-mg[1];
    int egScore=eg[0]-eg[1];

    phase= std::min(phase,totalPhase);
    score=(mgScore*phase +egScore*(totalPhase-phase))/totalPhase;






    return score;
}

