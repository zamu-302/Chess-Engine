#include <iostream>
#include "MoveGen.h"
#include <vector>
bool checkBound(int row, int col) {
    return row >= 0 && row < 8 && col >= 0 && col < 8;
}
inline uint64_t getRookAttacks(int sq, uint64_t occupied) {
    uint64_t blockers = occupied & rookMask[sq];
    int index = (int)((blockers * rookMagicnum[sq]) >> (64 - ROOK_BITS[sq]));
    return rookAttacks[sq][index];
}

inline uint64_t getBishopAttacks(int sq, uint64_t occupied) {
    uint64_t blockers = occupied & bishopMask[sq];
    int index = (int)((blockers * bishopMagicnum[sq]) >> (64 - BISHOP_BITS[sq]));
    return bishopAttacks[sq][index];
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
if(enpassRight){ int to=__builtin_ctzll(enpassRight); moves.emplace_back(to+7,to,MoveType::Enpassant); enpassRight&=enpassRight-1;}
if(enpassLeft){ int to=__builtin_ctzll(enpassLeft); moves.emplace_back(to+9,to,MoveType::Enpassant); enpassLeft&=enpassLeft-1;}
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
if(enpassRight){ int to=__builtin_ctzll(enpassRight); moves.emplace_back(to-9,to,MoveType::Enpassant); enpassRight&=enpassRight-1;}
if(enpassLeft){ int to=__builtin_ctzll(enpassLeft); moves.emplace_back(to-7,to,MoveType::Enpassant); enpassLeft&=enpassLeft-1; }
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
    uint64_t ownPieces=(color==Color::White)? state.whitePiece():state.blackPiece();
    uint64_t occupied=(state.blackPiece()|state.whitePiece());
    uint64_t Rook=(color==Color::White)? state.board.whiteRook:state.board.blackRook;
    uint64_t enemyPieces=(color==Color::White)? state.blackPiece():state.whitePiece();
   
    while(Rook){
        int from=__builtin_ctzll(Rook);
        uint64_t attacks=generate_rook_attack(from,occupied)&~ownPieces;
        while(attacks){
            int to=__builtin_ctzll(attacks);
            MoveType type=(enemyPieces& (1ULL<<to))?MoveType::Capture :MoveType::Normal;
            moves.emplace_back(from,to,type);
            attacks&=attacks-1;
        }
        Rook&=Rook-1;
        


    }
}
void generateBishopMoves(GameState& state,std::vector<Move> &moves,Color color){
   uint64_t ownPieces=(color==Color::White)? state.whitePiece():state.blackPiece();
    uint64_t occupied=(state.blackPiece()|state.whitePiece());
    uint64_t Bishop=(color==Color::White)? state.board.whiteBishop:state.board.blackBishop;
    uint64_t enemyPieces=(color==Color::White)? state.blackPiece():state.whitePiece();
   
    while(Bishop){
        int from=__builtin_ctzll(Bishop);
        uint64_t attacks=generate_bishop_attack(from,occupied)&~ownPieces;
        while(attacks){
            int to=__builtin_ctzll(attacks);
            MoveType type=(enemyPieces& (1ULL<<to))?MoveType::Capture :MoveType::Normal;
            moves.emplace_back(from,to,type);
            attacks&=attacks-1;
        }
        Bishop&=Bishop-1;
        


    }
    
}
void generateQueenMoves(GameState& state,std::vector<Move> &moves,Color color){
   uint64_t ownPieces=(color==Color::White)? state.whitePiece():state.blackPiece();
    uint64_t occupied=(state.blackPiece()|state.whitePiece());
    uint64_t Queens=(color==Color::White)? state.board.whiteQueen:state.board.blackQueen;
    uint64_t enemyPieces=(color==Color::White)? state.blackPiece():state.whitePiece();
   
    while(Queens){
        int from=__builtin_ctzll(Queens);
        uint64_t attacks=(generate_bishop_attack(from,occupied)|generate_rook_attack(from,occupied))&~ownPieces;
        while(attacks){
            int to=__builtin_ctzll(attacks);
            MoveType type=(enemyPieces& (1ULL<<to))?MoveType::Capture :MoveType::Normal;
            moves.emplace_back(from,to,type);
            attacks&=attacks-1;
        }
        Queens&=Queens-1;
        


    }
}

std::vector<Move> generatePseudoLegalMoves(const GameState& state){
std::vector<Move> move;
Color color=(state.WhiteToMove)? Color::White: Color::Black;

    
    generateBishopMoves(state,move,color);
    generateRookMoves(state,move,color);
    generatePawnMoves(state,move,color);
    generateQueenMoves(state,move,color);
    generateKingMoves(state,move,color);
    generateKnightMoves(state,move,color);

    


   



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