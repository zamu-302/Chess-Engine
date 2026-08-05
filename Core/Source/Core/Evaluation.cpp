#include <iostream>
#include "Evaluation.h"


int evaluation(const GameState& state) {
int pawnValue=100;
int knightValue=320;
int QueenValue=900;
int RookValue=500;
int KingValue=20000;
int BishopValue=320;


uint64_t occupied=(state.blackPiece()|state.whitePiece());
int score=0;
//castling point

while(occupied){
    int from = __builtin_ctzll(occupied);
    Piece piece=state.getPiece(from);
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
    occupied &= occupied - 1;
}






    return score;
}

