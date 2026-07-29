#include <iostream>
#include "Evaluation.h"


int evaluation(const GameState& state){
int pawnValue=100;
int knightValue=320;
int QueenValue=900;
int RookValue=500;
int KingValue=20000;
int BishopValue=320;




int score=0;
for(int row=0;row<8;row++){
    for(int col=0;col<8;col++){
        Piece piece=state.getPiece(row,col);

        switch (piece.type)
        {
        case PieceType::Pawn:
            score+=(piece.color==Color::White)?pawnValue:-pawnValue;
            break;
        case PieceType::Knight:
            score+=(piece.color==Color::White)?knightValue:-knightValue;
            break;
        case PieceType::Bishop:
            score+=(piece.color==Color::White)?BishopValue:-BishopValue;
            break;
        case PieceType::Rook:
            score+=(piece.color==Color::White)?RookValue:-RookValue;
            break;
        case PieceType::Queen:
            score+=(piece.color==Color::White)?QueenValue:-QueenValue;
            break;
        
        default:
            break;
        }

    }
}






    return score;
}

