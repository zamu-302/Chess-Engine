#include <iostream>
#include "MoveGen.h"
#include <vector>
bool checkBound(int row,int col){
    if (row>-1||row<8||col>-1||col<8){
        return false;
    }
    return true;
}

void generatePawnMoves(GameState & state,int row,int col,std::vector<Move> &moves){
// Blacks turn 
if((state.getTurn()==Color::Black)){

    if((checkBound(row+1,col))&&(state.getPiece(row+1,col).type==PieceType::None)){
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

    //capturing if it's in row+1,col+-1 
    if((checkBound(row+1,col-1))&&(state.getPiece(row+1,col-1).color==Color::White)){// if row or col out of bound then it return Color::None
        moves.push_back({row,col,row+1,col-1,MoveType::Capture});
    }
    if (checkBound(row+1,col+1)&&(state.getPiece(row+1,col+1).color==Color::White)){
        moves.push_back({row,col,row+1,col+1,MoveType::Capture});
    }
    //enpassant
    if (row+1==state.getEnPassantTargetrow()){
        if((checkBound(row,col+1))&&(state.getPiece(row,col+1).color==Color::White)&&(col+1==state.getEnPassantTargetcol())){
            moves.push_back({row,col,row+1,col+1,MoveType::Enpassant});
        }
        else if((checkBound(row,col-1))&&(state.getPiece(row,col-1).color==Color::White)&&(col-1==state.getEnPassantTargetcol())){
            moves.push_back({row,col,row+1,col-1,MoveType::Enpassant});
        }
    }
    }
     
}

//Whites turn
else if((state.getTurn()==Color::White)){
    if ((checkBound(row-1,col))&&(state.getPiece(row-1,col).type==PieceType::None)){
        if(row-1==0){
            for(auto p:{PieceType::Bishop,PieceType::Queen,PieceType::Knight,PieceType::Rook}){
            moves.push_back({row,col,row-1,col,MoveType::Promotion,p});
        }}
        else{
        moves.push_back({row,col,row-1,col});
        }
    if((row==6)&&(state.getPiece(row-2,col).type==PieceType::None)){
    moves.push_back({row,col,row-2,col});// 2 moves up before it makes any move...
    }
}
     //capturing if it's in row-1,col+-1 
    if((checkBound(row-1,col-1))&&(state.getPiece(row-1,col-1).color==Color::Black)){
        moves.push_back({row,col,row-1,col-1,MoveType::Capture});
    }
    if ((checkBound(row-1,col+1))&&(state.getPiece(row-1,col+1).color==Color::Black)){
        moves.push_back({row,col,row-1,col+1,MoveType::Capture});
    }
    //enpassant
    if (row-1==state.getEnPassantTargetrow()){
        if((checkBound(row-1,col+1))&&(state.getPiece(row,col+1).color==Color::Black)&&(col+1==state.getEnPassantTargetcol())){
            moves.push_back({row,col,row-1,col+1,MoveType::Enpassant});
        }
        else if((checkBound(row-1,col-1))&&(state.getPiece(row,col-1).color==Color::Black)&&(col-1==state.getEnPassantTargetcol())){
            moves.push_back({row,col,row-1,col-1,MoveType::Enpassant});
        }
    }
    
}




}

void generateKnightMoves(GameState& state, int row,int col,std::vector<Move> &moves){
int offsets[8][2] = {
        {2, 1}, {2, -1},
        {-2, 1}, {-2, -1},
        {1, 2}, {1, -2},
        {-1, 2}, {-1, -2}
    };
    for(int i=0;i<8;i++){
        int offsetRow = offsets[i][0];
        int offsetCol = offsets[i][1];
        if(!checkBound(row+offsetRow,col+offsetCol)){
            continue;
        }
        Piece currPiece=state.getPiece(row+offsetRow,col+offsetCol);
        if(currPiece.color==Color::None){
            moves.push_back({row,col,row+offsetRow,col+offsetCol});
        }
        else if(currPiece.color==state.getTurn()){
            continue;
        }
        else{
             moves.push_back({row,col,row+offsetRow,col+offsetCol,MoveType::Capture});
        }

        
    }


}

void generateKingMoves(GameState& state, int row,int col, std::vector<Move>& moves){
    int offsets[8][2] = {
        {1, 0}, {1, -1},
        {1, 1}, {0, -1},
        {0, 1}, {-1, -1},
        {-1, 0}, {-1, 1}
    };
    for(int i=0;i<8;i++){
        int offsetRow = offsets[i][0];
        int offsetCol = offsets[i][1];
        if(!checkBound(row+offsetRow,col+offsetCol)){
            continue;
        }
        Piece currPiece=state.getPiece(row+offsetRow,col+offsetCol);
        if(currPiece.color==Color::None){
            moves.push_back({row,col,row+offsetRow,col+offsetCol});
        }
        else if(currPiece.color==state.getTurn()){
            continue;
        }
        else{
             moves.push_back({row,col,row+offsetRow,col+offsetCol,MoveType::Capture});
        } 
}
    //castling
    

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

