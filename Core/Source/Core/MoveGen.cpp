#include <iostream>
#include "MoveGen.h"
#include <vector>
bool checkBound(int row, int col) {
    return row >= 0 && row < 8 && col >= 0 && col < 8;
}

void generatePawnMoves(GameState& state,std::vector<Move> &moves,Color color){

int direction=(color==Color::White)? -8:8;
uint64_t pawns=(color==Color::White)? state.board.whitePawn:state.board.blackPawn;
const uint64_t NOT_A_FILE = 0xFEFEFEFEFEFEFEFEULL;  
const uint64_t NOT_H_FILE = 0x7F7F7F7F7F7F7F7FULL; 
const uint64_t RANK_2 = 0x000000000000FF00ULL;  
const uint64_t RANK_7 = 0x00FF000000000000ULL;
const uint64_t Rank_8 = 0xFF00000000000000ULL;
const uint64_t Rank_1 = 0x00000000000000FFULL;
uint64_t enemyPieces=(color==Color::White)? state.blackPiece():state.whitePiece();
uint64_t emptySquare=~(state.blackPiece()|state.whitePiece());

int from=__builtin_ctzll(pawns);
if(color==Color::White)
{
uint64_t push=((pawns)>>8) & emptySquare;

uint64_t promoPush   = push & Rank_1;
uint64_t normalPush  = push & ~Rank_1;




uint64_t doublePush=((pawns&RANK_7)>>16) & emptySquare;
uint64_t leftCap  = ((pawns & NOT_A_FILE) >> 9) & enemyPieces;

uint64_t promoCapL   = leftCap & Rank_1;
uint64_t normalCapL  = leftCap  & ~Rank_1;

uint64_t rightCap = ((pawns & NOT_H_FILE) >> 7) & enemyPieces;

uint64_t promoCapR   = rightCap & Rank_1;
uint64_t normalCapR  = rightCap & ~Rank_1;

while(normalPush){
    int to=__builtin_ctzll(normalPush);
    moves.emplace_back(to+8,to);
    normalPush&=normalPush-1;
}
while(promoPush){
    int to=__builtin_ctzll(promoPush);
    for(PieceType p:{PieceType::Bishop,PieceType::Knight,PieceType::Queen,PieceType::Rook}){
        moves.emplace_back(to+8,to,MoveType::Promotion,p);
    }
    promoPush&=promoPush-1;
}

while(promoCapL){
int to=__builtin_ctzll(promoCapL);
 for(PieceType p:{PieceType::Bishop,PieceType::Knight,PieceType::Queen,PieceType::Rook}){
        moves.emplace_back(to+9,to,MoveType::PromotionCapture,p);
    }

promoCapL&=promoCapL-1;
}
while(promoCapR){
int to=__builtin_ctzll(promoCapR);
 for(PieceType p:{PieceType::Bishop,PieceType::Knight,PieceType::Queen,PieceType::Rook}){
        moves.emplace_back(to+7,to,MoveType::PromotionCapture,p);
    }

promoCapR&=promoCapR-1;
}
while(doublePush){

    int to=__builtin_ctzll(doublePush);
    moves.emplace_back(to+16,to);
    doublePush&=doublePush-1;

}

}
}
void generateKnightMoves(std::vector<Move> &moves,Color color){
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
void generateKingMoves(std::vector<Move> &moves,Color color){
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
            if((state.getPiece(0,6).type==PieceType::None)&&(state.getPiece(0,5).type==PieceType::None)){
                moves.push_back({row,col,row,col+2,MoveType::KingSideCastle});

            }
            

        }
        if(queenside){
            if((state.getPiece(0,1).type==PieceType::None)&&(state.getPiece(0,2).type==PieceType::None)&&(state.getPiece(0,3).type==PieceType::None)){
                moves.push_back({row,col,row,col-2,MoveType::QueenSideCastle});
            }
            
        }

    }
    else{
       std::pair<bool,bool> rights=state.getCastlingRights(Color::White);
        bool kingside=rights.first;
        bool queenside=rights.second; 
        if(kingside){
              if((state.getPiece(7,6).type==PieceType::None)&&(state.getPiece(7,5).type==PieceType::None)){
               moves.push_back({row,col,row,col+2,MoveType::KingSideCastle});
            }
            
        }
        if(queenside){
             if((state.getPiece(7,1).type==PieceType::None)&&(state.getPiece(7,2).type==PieceType::None)&&(state.getPiece(7,3).type==PieceType::None)){
                moves.push_back({row,col,row,col-2,MoveType::QueenSideCastle});
            }
        }
    }

}
void generateRookMoves(std::vector<Move> &moves,Color color){
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
void generateBishopMoves(std::vector<Move> &moves,Color color){
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
void generateQueenMoves(std::vector<Move> &moves,Color color){
    generateBishopMoves(state,row,col,moves);
    generateRookMoves(state,row,col,moves);
}

std::vector<Move> generatePseudoLegalMoves(const GameState& state){
std::vector<Move> move;
if(state.WhiteToMove){
    
    generateBishopMoves(GameState& state,move,Color::White);
    generatePawnMoves(move,Color::White);
    generateKnightMoves(move,Color::White);
    generateKingMoves(move,Color::White);
    generateRookMoves(move,Color::White);
    generateQueenMoves(move,Color::White);
    
}
else{
    generateBishopMoves(move,Color::Black);
    generatePawnMoves(move,Color::Black);
    generateKnightMoves(move,Color::Black);
    generateKingMoves(move,Color::Black);
    generateRookMoves(move,Color::Black);
    generateQueenMoves(move,Color::Black);



}
   



 return move;


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