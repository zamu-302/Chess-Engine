#include <iostream>
#include "MoveGen.h"
#include <vector>
bool checkBound(int row, int col) {
    return row >= 0 && row < 8 && col >= 0 && col < 8;
}


void generatePawnMoves(GameState& state,std::vector<Move> &moves,Color color){

uint64_t pawns=(color==Color::White)? state.board.whitePawn:state.board.blackPawn;
const uint64_t NOT_A_FILE = 0xFEFEFEFEFEFEFEFEULL;  
const uint64_t NOT_H_FILE = 0x7F7F7F7F7F7F7F7FULL; 
const uint64_t RANK_2 = 0x000000000000FF00ULL;  
const uint64_t RANK_7 = 0x00FF000000000000ULL;
const uint64_t Rank_8 = 0xFF00000000000000ULL;
const uint64_t Rank_1 = 0x00000000000000FFULL;
uint64_t enemyPieces=(color==Color::White)? state.blackPiece():state.whitePiece();
uint64_t emptySquare=~(state.blackPiece()|state.whitePiece());


if(color==Color::White)
{
uint64_t push=((pawns)>>8) & emptySquare;
uint64_t promoPush   = push & Rank_1;
uint64_t normalPush  = push & ~Rank_1;

uint64_t doublePush=((pawns&RANK_7)>>16) & emptySquare&(emptySquare>>8);

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
while(normalCapL){
    int to=__builtin_ctzll(normalCapL);
    moves.emplace_back(to+9,to,MoveType::Capture);

    normalCapL&=normalCapL-1;
}
while(normalCapR){
    int to=__builtin_ctzll(normalCapR);
    moves.emplace_back(to+7,to,MoveType::Capture);

    normalCapR&=normalCapR-1;
}

// enpassant 
int enpassantRow=state.getEnPassantTargetrow();
int enpassantCol=state.getEnPassantTargetcol();
int square=enpassantRow*8+enpassantCol;
uint64_t mask=1Ull<<square;
uint64_t enpassRight=((pawns&NOT_H_FILE)>>7)&mask;
uint64_t enpassLeft=((pawns&NOT_A_FILE)>>9)&mask;
if(enpassantRow!=-1){
while(enpassRight){ int to=__builtin_ctzll(enpassRight); moves.emplace_back(to+7,to,MoveType::Enpassant); enpassRight&=enpassRight-1;}
while(enpassLeft){ int to=__builtin_ctzll(enpassLeft); moves.emplace_back(to+9,to,MoveType::Enpassant); enpassLeft&=enpassLeft-1;}
}
}
//black
else{
uint64_t push=((pawns)<<8) & emptySquare;
uint64_t promoPush   = push & Rank_8;
uint64_t normalPush  = push & ~Rank_8;

uint64_t doublePush=((pawns&RANK_2)<<16) & emptySquare&(emptySquare<<8);

uint64_t leftCap  = ((pawns & NOT_A_FILE) << 7) & enemyPieces;
uint64_t promoCapL   = leftCap & Rank_8;
uint64_t normalCapL  = leftCap  & ~Rank_8;

uint64_t rightCap = ((pawns & NOT_H_FILE) << 9) & enemyPieces;
uint64_t promoCapR   = rightCap & Rank_8;
uint64_t normalCapR  = rightCap & ~Rank_8;

while(normalPush){
    int to=__builtin_ctzll(normalPush);
    moves.emplace_back(to-8,to);
    normalPush&=normalPush-1;
}
while(promoPush){
    int to=__builtin_ctzll(promoPush);
    for(PieceType p:{PieceType::Bishop,PieceType::Knight,PieceType::Queen,PieceType::Rook}){
        moves.emplace_back(to-8,to,MoveType::Promotion,p);
    }
    promoPush&=promoPush-1;
}

while(promoCapL){
int to=__builtin_ctzll(promoCapL);
 for(PieceType p:{PieceType::Bishop,PieceType::Knight,PieceType::Queen,PieceType::Rook}){
        moves.emplace_back(to-7,to,MoveType::PromotionCapture,p);
    }

promoCapL&=promoCapL-1;
}
while(promoCapR){
int to=__builtin_ctzll(promoCapR);
 for(PieceType p:{PieceType::Bishop,PieceType::Knight,PieceType::Queen,PieceType::Rook}){
        moves.emplace_back(to-9,to,MoveType::PromotionCapture,p);
    }

promoCapR&=promoCapR-1;
}
while(doublePush){

    int to=__builtin_ctzll(doublePush);
    moves.emplace_back(to-16,to);
    doublePush&=doublePush-1;

}
while(normalCapL){
    int to=__builtin_ctzll(normalCapL);
    moves.emplace_back(to-7,to,MoveType::Capture);

    normalCapL&=normalCapL-1;
}
while(normalCapR){
    int to=__builtin_ctzll(normalCapR);
    moves.emplace_back(to-9,to,MoveType::Capture);

    normalCapR&=normalCapR-1;
}


// enpassant 
int enpassantRow=state.getEnPassantTargetrow();
int enpassantCol=state.getEnPassantTargetcol();
int square=enpassantRow*8+enpassantCol;
uint64_t mask=1Ull<<square;
uint64_t enpassRight=((pawns&NOT_A_FILE)<<9)&mask;
uint64_t enpassLeft=((pawns&NOT_H_FILE)<<7)&mask;
if(enpassantRow!=-1){
while(enpassRight){ int to=__builtin_ctzll(enpassRight); moves.emplace_back(to-9,to,MoveType::Enpassant); enpassRight&=enpassRight-1;}
while(enpassLeft){ int to=__builtin_ctzll(enpassLeft); moves.emplace_back(to-7,to,MoveType::Enpassant); enpassLeft&=enpassLeft-1; }
}
}
}

void generateKnightMoves(GameState& state,std::vector<Move> &moves,Color color){
const uint64_t ownPieces=(color==Color::White)?state.whitePiece(): state.blackPiece();
uint64_t knight=(color==Color::White)?state.board.whiteKnight: state.board.blackKnight;
const uint64_t enemyPieces=(color==Color::White)?state.blackPiece(): state.whitePiece();
while(knight){
    int from=__builtin_ctzll(knight);
    uint64_t target=knightAttacks[from]& ~ownPieces;
    while(target){
        int to=__builtin_ctzll(target);
        if(enemyPieces&(1ULL<<to)){
            moves.emplace_back(from,to,MoveType::Capture);
        }
        else{
            moves.emplace_back(from,to);
        }
        target&=target-1;
    }
    knight&=knight-1;

}

    


}
void generateKingMoves(GameState& state,std::vector<Move> &moves,Color color){
const uint64_t ownPieces=(color==Color::White)?state.whitePiece(): state.blackPiece();
uint64_t king=(color==Color::White)?state.board.whiteKing: state.board.blackKing;
const uint64_t enemyPieces=(color==Color::White)?state.blackPiece(): state.whitePiece();
int casfrom=__builtin_ctzll(king);
while(king){
    int from=__builtin_ctzll(king);
    uint64_t target=kingAttacks[from]& ~ownPieces;
    while(target){
        int to=__builtin_ctzll(target);
        if(enemyPieces&(1ULL<<to)){
            moves.emplace_back(from,to,MoveType::Capture);
        }
        else{
            moves.emplace_back(from,to);
        }
        target&=target-1;
    }
    king&=king-1;

}
   
    //castling
        std::pair<bool,bool> rights=state.getCastlingRights();
        bool kingside=rights.first;
        bool queenside=rights.second;
        if(kingside){
           
           uint64_t mask= (1ULL << (casfrom + 1)) | (1ULL << (casfrom + 2));
           if(!(mask&(ownPieces|enemyPieces))){
            moves.emplace_back(casfrom,casfrom+2,MoveType::KingSideCastle);
           }
        }
        if(queenside){
           
           uint64_t mask= (1ULL << (casfrom - 1)) | (1ULL << (casfrom - 2)) |(1ULL<<(casfrom-3));
           if(!(mask&(ownPieces|enemyPieces))){
            moves.emplace_back(casfrom,casfrom-2,MoveType::QueenSideCastle);
           }
            
        }

    }
    
    


void generateRookMoves(GameState& state,std::vector<Move> &moves,Color color){
    uint64_t enemyPieces=(color==Color::White)? state.blackPiece():state.whitePiece();
    uint64_t emptySquare=~(state.blackPiece()|state.whitePiece());
    uint64_t Rook=(color==Color::White)? state.board.whiteRook:state.board.blackRook;
    int offset[2]={8,1};

    //basically we take the lsb in the rook and shift it in all 4 direction
    while(Rook){
        int from=__builtin_ctzll(Rook);
        int row=from/8;
        int col=from%8;
        int to=from;
        //up
        while(checkBound(row+1,col)){
            to+=offset[0];
            uint64_t mask=1ULL<<to;
            if(mask&emptySquare){
                moves.emplace_back(from,to);
                row++;

            }
            else if(mask&enemyPieces){
                moves.emplace_back(from,to,MoveType::Capture);
                break;
            }
            else{
                break;
            }
        }
        row=from/8;
        to=from;
        //down
        while(checkBound(row-1,col)){
            to-=offset[0];
            uint64_t mask=1ULL<<to;
            if(mask&emptySquare){
                moves.emplace_back(from,to);
                row--;

            }
            else if(mask&enemyPieces){
                moves.emplace_back(from,to,MoveType::Capture);
                break;
            }
            else{
                break;
            }
        }
        row=from/8;
        to=from;
        //right
        while(checkBound(row,col+1)){
            to+=offset[1];
            uint64_t mask=1ULL<<to;
            if(mask&emptySquare){
                moves.emplace_back(from,to);
                col++;

            }
            else if(mask&enemyPieces){
                moves.emplace_back(from,to,MoveType::Capture);
                break;
            }
            else{
                break;
            }
        }
        col=from%8;
        to=from;
        //left
        while(checkBound(row,col-1)){
            to-=offset[1];
            uint64_t mask=1ULL<<to;
            if(mask&emptySquare){
                moves.emplace_back(from,to);
                col--;

            }
            else if(mask&enemyPieces){
                moves.emplace_back(from,to,MoveType::Capture);
                break;
            }
            else{
                break;
            }
        }

        

        Rook&=Rook-1;

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
    
    generateBishopMoves(state,move,Color::White);
    generateRookMoves(state,move,Color::White);
    generatePawnMoves(state,move,Color::White);
    generateQueenMoves(state,move,Color::White);
    generateKingMoves(state,move,Color::White);
    generateKnightMoves(state,move,Color::White);

    
}
else{
    generateBishopMoves(state,move,Color::Black);
    generateRookMoves(state,move,Color::Black);
    generatePawnMoves(state,move,Color::Black);
    generateQueenMoves(state,move,Color::Black);
    generateKingMoves(state,move,Color::Black);
    generateKnightMoves(state,move,Color::Black);



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