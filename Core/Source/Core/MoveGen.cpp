#include <iostream>
#include "MoveGen.h"
#include <vector>
bool checkBound(int row, int col) {
    return row >= 0 && row < 8 && col >= 0 && col < 8;
}

void generatePawnMoves(const GameState & state,int row,int col,std::vector<Move> &moves){
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
}

    //capturing if it's in row+1,col+-1 
    if((checkBound(row+1,col-1))&&(state.getPiece(row+1,col-1).color==Color::White)){
        if(row==6){
            for(auto p:{PieceType::Knight,PieceType::Bishop,PieceType::Queen,PieceType::Rook}){
                moves.push_back({row,col,row+1,col-1,MoveType::PromotionCapture,p});
        }
        }
        else{
        moves.push_back({row,col,row+1,col-1,MoveType::Capture});
    }
    }
    if (checkBound(row+1,col+1)&&(state.getPiece(row+1,col+1).color==Color::White)){
        if(row==6){
            for(auto p:{PieceType::Knight,PieceType::Bishop,PieceType::Queen,PieceType::Rook}){
                moves.push_back({row,col,row+1,col+1,MoveType::PromotionCapture,p});
        }
        }
        else{
        moves.push_back({row,col,row+1,col+1,MoveType::Capture});
    }
        
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
        if(row==1){
            for(auto p:{PieceType::Knight,PieceType::Bishop,PieceType::Queen,PieceType::Rook}){
                moves.push_back({row,col,row-1,col-1,MoveType::PromotionCapture,p});
        }
        }
        else{
        moves.push_back({row,col,row-1,col-1,MoveType::Capture});
    }
       
    }
    if ((checkBound(row-1,col+1))&&(state.getPiece(row-1,col+1).color==Color::Black)){
        if(row==1){
            for(auto p:{PieceType::Knight,PieceType::Bishop,PieceType::Queen,PieceType::Rook}){
                moves.push_back({row,col,row-1,col+1,MoveType::PromotionCapture,p});
        }
        }
        else{
        moves.push_back({row,col,row-1,col+1,MoveType::Capture});
    }
        
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
void generateKnightMoves(const GameState& state, int row,int col,std::vector<Move> &moves){
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
void generateKingMoves(const GameState& state, int row,int col, std::vector<Move>& moves){
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
    if(state.getPiece(row,col).color==Color::Black){
        std::pair<bool,bool> rights=state.getCastlingRights(Color::Black);
        bool kingside=rights.first;
        bool queenside=rights.second;
        if(kingside){
            moves.push_back({row,col,row,col+2,MoveType::KingSideCastle});

        }
        if(queenside){
            moves.push_back({row,col,row,col-2,MoveType::QueenSideCastle});
        }

    }
    else{
       std::pair<bool,bool> rights=state.getCastlingRights(Color::White);
        bool kingside=rights.first;
        bool queenside=rights.second; 
        if(kingside){
            moves.push_back({row,col,row,col+2,MoveType::KingSideCastle});
        }
        if(queenside){
            moves.push_back({row,col,row,col-2,MoveType::QueenSideCastle});
        }
    }

}
void generateRookMoves(const GameState& state, int row, int col,std::vector<Move>&moves){
    int offset[4][2]{{1,0},{-1,0},{0,1},{0,-1}};
    for(int i=0;i<4;++i){
        int curRow=offset[i][0]+row;
        int curCol=offset[i][1]+col;

        while(checkBound(curRow,curCol)){
            if(state.getPiece(curRow,curCol).type==PieceType::None){
                moves.push_back({row,col,curRow,curCol});
            }
            else if(state.getPiece(curRow,curCol).color!=state.getTurn()){
                moves.push_back({row,col,curRow,curCol,MoveType::Capture});
                break;
            }
            else{
                break;
            }
            curRow+=offset[i][0];
            curCol+=offset[i][1];
        }
    }
}
void generateBishopMoves(const GameState& state, int row,int col,std::vector<Move>& moves){
    int offset[4][2]{{1,1},{1,-1},{-1,1},{-1,-1}};
    for(int i=0;i<4;i++){
    int curRow=offset[i][0]+row;
    int curCol=offset[i][1]+col;
    while(checkBound(curRow,curCol)){
        if(state.getPiece(curRow,curCol).type==PieceType::None){
            moves.push_back({row,col,curRow,curCol});
        }
        else if(state.getPiece(curRow,curCol).color!=state.getTurn()){
            moves.push_back({row,col,curRow,curCol,MoveType::Capture});
            break;
        }
        else{
            break;
        }
        curRow+=offset[i][0];
        curCol+=offset[i][1];
        }
    }
    
}
void generateQueenMoves(const GameState& state, int row, int col,std::vector<Move>& moves){
    generateBishopMoves(state,row,col,moves);
    generateRookMoves(state,row,col,moves);
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
            generatePawnMoves(state,row,col,moves);
            break;
        case PieceType::Knight:
            generateKnightMoves(state,row,col,moves);
            break;
        case PieceType::King:
            generateKingMoves(state,row,col,moves);
            break;
        case PieceType::Queen:
            generateQueenMoves(state,row,col,moves);
            break;
        case PieceType::Rook:
            generateRookMoves(state,row,col,moves);
            break;
        case PieceType::Bishop:
            generateBishopMoves(state,row,col,moves);
            break;
        
        default:
            break;
        }
        

    }
   
}


 return moves;


}
std::vector<Move> generateLegalMoves(const GameState& state){
    std::vector<Move> moves=generatePseudoLegalMoves(state);
    std::vector<Move> LegalMoves;

    for(auto& move:moves){
        GameState copy=state;
        copy.Makemove(move);
        if(!copy.inCheck()){
            LegalMoves.push_back(move);
        }
    }




    return LegalMoves;
}