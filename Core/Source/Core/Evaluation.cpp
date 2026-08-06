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


    int mgScore=mg[0]-mg[1];
    int egScore=eg[0]-eg[1];

    phase= std::min(phase,totalPhase);
    score=(mgScore*phase +egScore*(totalPhase-phase))/totalPhase;






    return score;
}

