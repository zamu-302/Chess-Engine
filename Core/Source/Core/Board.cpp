#include <iostream>
#include <vector>
#include "Board.h"
#include "MoveGen.h"
#include "Lookuptabel.h"
#include <cctype>
#include <cstdlib>
#include <string>
#include <algorithm>

int GameState::getHalfMoveClock()const {
    return halfMoveClock;
}

uint64_t GameState::getHash()const {
uint64_t hash=0;
uint64_t occupied=(blackPiece()|whitePiece());
while(occupied){
int sq=__builtin_ctzll(occupied);
Piece p=getPiece(sq);
hash^=zobristTabel[(int)p.color][(int)p.type][sq];
occupied&=occupied-1;
}
if(!WhiteToMove){hash^=zobristSideKey;}
return hash;
}

Piece GameState::getPiece(int square)const{
    
    uint64_t mask=1ULL<<square;
    // white piece
    if(board.whiteBishop&mask) return {PieceType::Bishop,Color::White};
    else if(board.whiteKing&mask) return {PieceType::King,Color::White};
    else if(board.whiteQueen&mask) return {PieceType::Queen,Color::White};
    else if(board.whitePawn&mask) return {PieceType::Pawn,Color::White};
    else if(board.whiteKnight&mask) return {PieceType::Knight,Color::White};
    else if(board.whiteRook&mask) return {PieceType::Rook,Color::White};

    else if(board.blackKing&mask) return {PieceType::King,Color::Black};
    else if(board.blackQueen&mask) return {PieceType::Queen,Color::Black};
    else if(board.blackBishop&mask) return {PieceType::Bishop,Color::Black};
    else if(board.blackKnight&mask) return {PieceType::Knight,Color::Black};
    else if(board.blackPawn&mask) return {PieceType::Pawn,Color::Black};
    else if(board.blackRook&mask) return {PieceType::Rook,Color::Black};
    else return {PieceType::None,Color::None};

}

uint64_t GameState::blackPiece()const{
    return board.blackBishop|board.blackKing|board.blackKnight|board.blackPawn|board.blackQueen|board.blackRook;
}
uint64_t GameState::whitePiece()const{
    return board.whiteBishop|board.whiteKing|board.whiteKnight|board.whitePawn|board.whiteQueen|board.whiteRook;
}

bool GameState::isEnemyPiece(int pos, Color color){
    uint64_t mask=1Ull<<pos;
    if (color==Color::White){
        return mask&blackPiece();
    }
    return mask&whitePiece();
}
std::pair<bool, bool> GameState::getCastlingRights() const{
    if(!WhiteToMove){
        return {castlingKingSideBlack,castlingQueenSideBlack};
    }
    return {castlingKingSideWhite,castlingQueenSideWhite};
}

int GameState::getEnPassantTargetcol()const{
    return enPassantTargetcol;
}
int GameState::getEnPassantTargetrow()const {
    return enPassantTargetRow;
}

void GameState::clearState(int sq){
    uint64_t mask=~(1ULL<<sq);
    board.blackBishop&=mask;
    board.blackKnight&=mask;
    board.blackPawn&=mask;
    board.blackQueen&=mask;
    board.blackRook&=mask;
    board.whiteBishop&=mask;
    board.whiteKnight&=mask;
    board.whitePawn&=mask;
    board.whiteQueen&=mask;
    board.whiteRook&=mask;
    board.whiteKing&=mask;
    board.blackKing&=mask;
    
    

}

void GameState::Makemove(const Move &move){
    bool flag=false;
    Piece p=getPiece(move.from);
    Color color=p.color;
    PieceType type=p.type;
    //normal type
    if(move.type==MoveType::Normal){
        
       
        setPiece(move.to,type,color);
        halfMoveClock++;
        if(type==PieceType::Pawn){
            halfMoveClock=0;
            int toRow=move.to/8;
            int fromRow=move.from/8;
            int fromCol=move.from%8;
            if(abs(toRow-fromRow)==2){
                enPassantTargetRow=(toRow+fromRow)/2;
                enPassantTargetcol=fromCol;
                flag=true;
            }
        }
    }
        
    
    //capture
    else if(move.type==MoveType::Capture){
       clearState(move.to); 
       setPiece(move.to,type,color);
       halfMoveClock=0;

    }
    //enpassant
    else if(move.type==MoveType::Enpassant){
        setPiece(move.to,type,color);
        int row=move.from/8;
        clearState((row*8)+enPassantTargetcol);
   
        halfMoveClock=0;
    }

    //castling

    else if(move.type==MoveType::KingSideCastle||move.type==MoveType::QueenSideCastle){
        if(move.type==MoveType::KingSideCastle){
        setPiece(move.to,type,color);
        setPiece(move.to-1,PieceType::Rook,color);
        int row= move.to/8;
        clearState((row*8)+7);
       
        
        }
        
    
        else if(move.type==MoveType::QueenSideCastle){
        setPiece(move.to,type,color);
        setPiece(move.to+1,PieceType::Rook,color);
        int row= move.to/8;
        clearState(row*8);
        }
    halfMoveClock++;
    if(WhiteToMove){
        castlingKingSideWhite=false;
        castlingQueenSideWhite=false;
        }
    else{
        castlingKingSideBlack=false;
        castlingQueenSideBlack=false;
    }
}

    //promotion
    else{
        clearState(move.to); 
        uint64_t mask=1ULL<<move.to;
        switch (move.PromotionPiece)
        {
        case PieceType::Queen:
            WhiteToMove? (board.whiteQueen|=mask):(board.blackQueen|=mask);
            break;
        case PieceType::Rook:
            WhiteToMove? (board.whiteRook|=mask):(board.blackRook|=mask);
            break;
        case PieceType::Bishop:
            WhiteToMove? (board.whiteBishop|=mask):(board.blackBishop|=mask);
            break;
        case PieceType::Knight:
            WhiteToMove? (board.whiteKnight|=mask):(board.blackKnight|=mask);
            break;
        
        default:
            break;
        }
      
        halfMoveClock++;
    }
    clearState(move.from);
   
    if(!flag){
        enPassantTargetcol=-1;
        enPassantTargetRow=-1;
    }
    if(!WhiteToMove){
        fullMoveClock++;
        
    }
// king moved — lose both rights for that color
if (move.from==60) {
    castlingKingSideWhite = castlingQueenSideWhite = false;
}
if (move.from==4) {
    castlingKingSideBlack = castlingQueenSideBlack = false;
}

// rook moved from starting square — lose that side's right
if (move.from==63) castlingKingSideWhite = false;
if (move.from==56) castlingQueenSideWhite = false;
if (move.from==7) castlingKingSideBlack = false;
if (move.from==0) castlingQueenSideBlack = false;

// rook captured on its starting square — lose that right too
if (move.to==63) castlingKingSideWhite = false;
if (move.to==56) castlingQueenSideWhite = false;
if (move.to==7) castlingKingSideBlack = false;
if (move.to==0) castlingQueenSideBlack = false;
WhiteToMove^=1;

}


std::vector<std::string> split(const std::string&str,char delimter){
    std::vector<std::string>parts;
    std::string part;
    
    for(size_t i=0;i<str.length();i++){
        if(str[i]==delimter){
            parts.push_back(part);
            part.clear();
        }
        else{
            part.push_back(str[i]);
        }
    }
    parts.push_back(part);
    return parts;
}
Color getColor(char c){
    if(islower(c)){
        return Color::Black;
    }
    return Color::White;
}
PieceType getType(char c){
    switch (c)
    {
    case 'r':case 'R': return PieceType::Rook;
    case 'q':case 'Q': return PieceType::Queen;
    case 'P':case 'p': return PieceType::Pawn;
    case 'k':case 'K': return PieceType::King;
    case 'N':case 'n': return PieceType::Knight;
    case 'b':case 'B': return PieceType::Bishop;
    
    default:
        return PieceType::None;
    }
}
void GameState::setPiece(int square,PieceType type,Color color){
uint64_t bit=1ULL<<square;

if(color==Color::White){
    switch (type)
    {
    case PieceType::Pawn:
        board.whitePawn|=bit;
        break;
    case PieceType::Queen:
        board.whiteQueen|=bit;
        break;
    case PieceType::King:
        board.whiteKing|=bit;
        break;
    case PieceType::Rook:
        board.whiteRook|=bit;
        break;
    case PieceType::Bishop:
        board.whiteBishop|=bit;
        break;
    case PieceType::Knight:
        board.whiteKnight|=bit;
        break;
    default:
        break;
    }

}
else{
    switch (type)
    {
    case PieceType::Pawn:
        board.blackPawn|=bit;
        break;
    case PieceType::Queen:
        board.blackQueen|=bit;
        break;
    case PieceType::King:
        board.blackKing|=bit;
        break;
    case PieceType::Rook:
        board.blackRook|=bit;
        break;
    case PieceType::Bishop:
        board.blackBishop|=bit;
        break;
    case PieceType::Knight:
        board.blackKnight|=bit;
        break;
    default:
        break;
    }
}

}


bool GameState::squareAttacked(const GameState& state, int sq, Color color)const{
    
    uint64_t king=1Ull<<sq;
    uint64_t occupied=(whitePiece()|blackPiece());

    int kingSq=__builtin_ctzll(king);

    uint64_t enemyPiece=(color==Color::White)? blackPiece():whitePiece();
    uint64_t enemyRooks   = (color == Color::White) ? board.blackRook   : board.whiteRook;
    uint64_t enemyBishops = (color == Color::White) ? board.blackBishop : board.whiteBishop;
    uint64_t enemyQueens  = (color == Color::White) ? board.blackQueen  : board.whiteQueen;
    uint64_t enemyKnights = (color == Color::White) ? board.blackKnight : board.whiteKnight;
    uint64_t enemyPawns   = (color == Color::White) ? board.blackPawn   : board.whitePawn;
    uint64_t enemyKing    = (color == Color::White) ? board.blackKing   : board.whiteKing;

    // knight check — lookup table
    if (knightAttacks[kingSq] & enemyKnights) return true;

    // king check — lookup table
    if (kingAttacks[kingSq] & enemyKing) return true;

    // rook/queen check — magic lookup
    uint64_t rookRays = getRookAttacks(kingSq, occupied);
    if (rookRays & (enemyRooks | enemyQueens)) return true;

    // bishop/queen check — magic lookup
    uint64_t bishopRays = getBishopAttacks(kingSq, occupied);
    if (bishopRays & (enemyBishops | enemyQueens)) return true;

    // pawn check — depends on king color
    if (color == Color::Black) {
        const uint64_t NOT_A_FILE = 0xFEFEFEFEFEFEFEFEULL;
        const uint64_t NOT_H_FILE = 0x7F7F7F7F7F7F7F7FULL;
        uint64_t pawnAttacks = ((king & NOT_A_FILE) << 7) | ((king & NOT_H_FILE) << 9);
        if (pawnAttacks & enemyPawns) return true;
    } else {
        const uint64_t NOT_A_FILE = 0xFEFEFEFEFEFEFEFEULL;
        const uint64_t NOT_H_FILE = 0x7F7F7F7F7F7F7F7FULL;
        uint64_t pawnAttacks = ((king & NOT_A_FILE) >> 9) | ((king & NOT_H_FILE) >> 7);
        if (pawnAttacks & enemyPawns) return true;
    }


    return false;
}
bool GameState::inCheck(Color kingColor)const {
    uint64_t king=(kingColor==Color::White)? board.whiteKing:board.blackKing;
    uint64_t occupied=(whitePiece()|blackPiece());

    int kingSq=__builtin_ctzll(king);

    uint64_t enemyPiece=(kingColor==Color::White)? blackPiece():whitePiece();
    uint64_t enemyRooks   = (kingColor == Color::White) ? board.blackRook   : board.whiteRook;
    uint64_t enemyBishops = (kingColor == Color::White) ? board.blackBishop : board.whiteBishop;
    uint64_t enemyQueens  = (kingColor == Color::White) ? board.blackQueen  : board.whiteQueen;
    uint64_t enemyKnights = (kingColor == Color::White) ? board.blackKnight : board.whiteKnight;
    uint64_t enemyPawns   = (kingColor == Color::White) ? board.blackPawn   : board.whitePawn;
    uint64_t enemyKing    = (kingColor == Color::White) ? board.blackKing   : board.whiteKing;

    // knight check — lookup table
    if (knightAttacks[kingSq] & enemyKnights) return true;

    // king check — lookup table
    if (kingAttacks[kingSq] & enemyKing) return true;

    // rook/queen check — magic lookup
    uint64_t rookRays = getRookAttacks(kingSq, occupied);
    if (rookRays & (enemyRooks | enemyQueens)) return true;

    // bishop/queen check — magic lookup
    uint64_t bishopRays = getBishopAttacks(kingSq, occupied);
    if (bishopRays & (enemyBishops | enemyQueens)) return true;

    // pawn check — depends on king color
    if (kingColor == Color::Black) {
        const uint64_t NOT_A_FILE = 0xFEFEFEFEFEFEFEFEULL;
        const uint64_t NOT_H_FILE = 0x7F7F7F7F7F7F7F7FULL;
        uint64_t pawnAttacks = ((king & NOT_A_FILE) << 7) | ((king & NOT_H_FILE) << 9);
        if (pawnAttacks & enemyPawns) return true;
    } else {
        const uint64_t NOT_A_FILE = 0xFEFEFEFEFEFEFEFEULL;
        const uint64_t NOT_H_FILE = 0x7F7F7F7F7F7F7F7FULL;
        uint64_t pawnAttacks = ((king & NOT_A_FILE) >> 9) | ((king & NOT_H_FILE) >> 7);
        if (pawnAttacks & enemyPawns) return true;
    }


    return false;
}

void GameState::LoadFEN(const std::string &fen){
    board.whitePawn = board.whiteKnight = board.whiteBishop = 0;
    board.whiteRook = board.whiteQueen  = board.whiteKing   = 0;
    board.blackPawn = board.blackKnight = board.blackBishop = 0;
    board.blackRook = board.blackQueen  = board.blackKing   = 0;
    castlingKingSideWhite  = false;
    castlingQueenSideWhite = false;
    castlingKingSideBlack  = false;
    castlingQueenSideBlack = false;
    enPassantTargetRow = -1;
    enPassantTargetcol = -1;
    halfMoveClock = 0;
    fullMoveClock = 1;
    std::vector<std::string> parts=split(fen,' ');
    std::string pos=parts[0];
    int row=0;
    int col=0;
    for(size_t j=0;j<pos.length();j++){
        if(pos[j]=='/'){
            row+=1;
            col=0;
        }
        else if(isdigit(pos[j])){
            col+=(pos[j]-'0');
        }
        else{
            Color color=getColor(pos[j]);
            PieceType type=getType(pos[j]);
            int square=row*8+col;
            setPiece(square,type,color);
            col++;
        }
        }
    std::string turn=parts[1];
    if (turn=="w"){
        WhiteToMove=true;
    }
    else{
        WhiteToMove=false;
    }




    std::string castle=parts[2];
    for(size_t i=0;i<castle.length();i++){
        char c=castle[i];
        if(c=='-'){
            castlingKingSideWhite=false;
            castlingQueenSideWhite=false;
            castlingKingSideBlack=false;
            castlingQueenSideBlack=false;
        }
        else if(c=='K'){
            castlingKingSideWhite=true;
        }
        else if(c=='k'){
            castlingKingSideBlack=true;
        }
        else if(c=='Q'){
            castlingQueenSideWhite=true;
        }
        else if(c=='q'){
            castlingQueenSideBlack=true;
        }
        }
        std::string enpassant=parts[3];
       
        if(enpassant[0]=='-'){
            enPassantTargetcol=-1;
            enPassantTargetRow=-1;
        }
        else{
            enPassantTargetcol=enpassant[0]-'a';
            enPassantTargetRow=enpassant[1]-'1';
        }
            
        
        halfMoveClock = std::stoi(parts[4]);
        fullMoveClock = std::stoi(parts[5]);


    }

