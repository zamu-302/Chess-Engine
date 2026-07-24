#include <iostream>
#include "MoveGen.h"
#include <vector>


std::vector<Move> generatePseudoLegalMoves(const GameState& state){
std::vector<Move> moves;
for(int row=0;row<8;row++){
    for (int col=0;col<8;col++){
        Piece currPiece=state.getPiece(row,col);
        if(currPiece.type==PieceType::None||((currPiece.color!=state.getTurn()))){
            continue;
        }
        //generate moves
        PieceType p=currPiece.type;
        switch (p)
        {
        case PieceType::Pawn:
            generatePawnmoves(state,row,col,moves);
            break;
        case PieceType::Knight:
            generateKnightmoves(state,row,col,moves);
            break;
        case PieceType::King:
            generateKingmoves(state,row,col,moves);
            break;
        case PieceType::Queen:
            generateQueenmoves(state,row,col,moves);
            break;
        case PieceType::Rook:
            generateRookmoves(state,row,col,moves);
            break;
        case PieceType::Bishop:
            generateBishopmoves(state,row,col,moves);
            break;
        
        default:
            break;
        }
        

    }
   
}


 return moves;


}