#include <iostream>
#include "MoveGen.h"
#include <vector>


void generatePawnMoves(GameState & state,int row,int col,std::vector<Move> &moves){

if((state.getTurn()==Color::Black)){
moves.push_back({row,col,row+1,col});
    //intial 2 space move
    if (row==1){
        moves.push_back({row,col,row+2,col});
    }
    //capturing if it's in row+1,col+-1 and if the enpassant row and col is the same as the capture moves
    if(state.getPiece(row+1,col-1).color==Color::White){
        moves.push_back({row,col,row+1,col-1});
    }
    if (state.getPiece(row+1,col+1).color==Color::White){
        moves.push_back({row,col,row+1,col+1});
    }
    //enpassant
    if (row+1==state.getEnPassantTargetrow()){
        if((state.getPiece(row,col+1).color==Color::White)&&(col+1==state.getEnPassantTargetcol())){
            moves.push_back({row,col,row+1,col+1});
        }
        else if((state.getPiece(row,col-1).color==Color::White)&&(col-1==state.getEnPassantTargetcol())){
            moves.push_back({row,col,row+1,col-1});
        }
    }
    
    
   
}
else if((state.getTurn()==Color::White)){
moves.push_back({row,col,row-1,col});
    if(row==6){
    moves.push_back({row,col,row-2,col});
    }
}




}
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

void generatePawn