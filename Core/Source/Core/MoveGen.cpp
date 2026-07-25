#include <iostream>
#include "MoveGen.h"
#include <vector>


void generatePawnMoves(GameState & state,int row,int col,std::vector<Move> &moves){
// Blacks turn 
if((state.getTurn()==Color::Black)){

    if((row+1<8 )&&(state.getPiece(row+1,col).type==PieceType::None)){
        if(row+1==7){
            for(auto p:{PieceType::Knight,PieceType::Bishop,PieceType::Queen,PieceType::Rook}){
                moves.push_back({row,col,row+1,col,MoveType::Promotion,p});
            }
            }
        else{
            moves.push_back({row,col,row+1,col});
        }
    //intial 2 space move
    if ((row==1)&&(state.getPiece(row+2,col).type==PieceType::None)){
        moves.push_back({row,col,row+2,col});
    }
}
    //capturing if it's in row+1,col+-1 
    if(state.getPiece(row+1,col-1).color==Color::White){// if row or col out of bound then it return Color::None
        moves.push_back({row,col,row+1,col-1,MoveType::Capture});
    }
    if (state.getPiece(row+1,col+1).color==Color::White){
        moves.push_back({row,col,row+1,col+1,MoveType::Capture});
    }
    //enpassant
    if (row+1==state.getEnPassantTargetrow()){
        if((state.getPiece(row,col+1).color==Color::White)&&(col+1==state.getEnPassantTargetcol())){
            moves.push_back({row,col,row+1,col+1,MoveType::Enpassant});
        }
        else if((state.getPiece(row,col-1).color==Color::White)&&(col-1==state.getEnPassantTargetcol())){
            moves.push_back({row,col,row+1,col-1,MoveType::Enpassant});
        }
    }
     
}

//Whites turn
else if((state.getTurn()==Color::White)){
    if ((row-1>-1)&&(state.getPiece(row-1,col).type==PieceType::None)){
        if(row-1==0){
            moves.push_back({row,col,row-1,col,MoveType::Promotion});
        }
        else{
        moves.push_back({row,col,row-1,col});// will contain promotion and +1 move up
        }
    if((row==6)&&(state.getPiece(row-2,col).type==PieceType::None)){
    moves.push_back({row,col,row-2,col});// 2 moves up before it makes any move...
    }
}
     //capturing if it's in row-1,col+-1 
    if(state.getPiece(row-1,col-1).color==Color::Black){
        moves.push_back({row,col,row-1,col-1,MoveType::Capture});
    }
    if (state.getPiece(row-1,col+1).color==Color::Black){
        moves.push_back({row,col,row-1,col+1,MoveType::Capture});
    }
    //enpassant
    if (row-1==state.getEnPassantTargetrow()){
        if((state.getPiece(row,col+1).color==Color::Black)&&(col+1==state.getEnPassantTargetcol())){
            moves.push_back({row,col,row-1,col+1,MoveType::Enpassant});
        }
        else if((state.getPiece(row,col-1).color==Color::Black)&&(col-1==state.getEnPassantTargetcol())){
            moves.push_back({row,col,row-1,col-1,MoveType::Enpassant});
        }
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

