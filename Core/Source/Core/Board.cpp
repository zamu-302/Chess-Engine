#include <iostream>
#include <vector>
#include "Board.h"
#include "MoveGen.h"
#include <cctype>
#include <cstdlib>
#include <string>
#include <algorithm>

Piece GameState::getPiece(int row,int col)const{
    return board[row][col];
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



void GameState::Makemove(const Move &move){
    bool flag=false;
    //normal type
    if(move.type==MoveType::Normal){
        board[move.toRow][move.toCol]=getPiece(move.fromRow,move.fromCol);
        halfMoveClock++;
        if((board[move.toRow][move.toCol].type==PieceType::Pawn)){
            halfMoveClock=0;
            if(abs(move.toRow-move.fromRow)==2){
                enPassantTargetRow=(move.fromRow+move.toRow)/2;
                enPassantTargetcol=move.fromCol;
                flag=true;
            }
        }
    }
        
    
    //capture
    else if(move.type==MoveType::Capture){
       board[move.toRow][move.toCol]=getPiece(move.fromRow,move.fromCol);
       halfMoveClock=0;

    }
    //enpassant
    else if(move.type==MoveType::Enpassant){
        board[move.toRow][move.toCol]=getPiece(move.fromRow,move.fromCol);
        board[move.fromRow][enPassantTargetcol]={PieceType::None,Color::None};
        halfMoveClock=0;
    }

    //castling

    else if(move.type==MoveType::KingSideCastle||move.type==MoveType::QueenSideCastle){
        if(move.type==MoveType::KingSideCastle){
        board[move.toRow][move.toCol]=getPiece(move.fromRow,move.fromCol);
        board[move.toRow][move.toCol-1]=getPiece(move.toRow,7);
        board[move.toRow][7]={PieceType::None,Color::None};
        
        }
        
    
        else if(move.type==MoveType::QueenSideCastle){
        board[move.toRow][move.toCol]=getPiece(move.fromRow,move.fromCol);
        board[move.toRow][move.toCol+1]=getPiece(move.toRow,0);
        board[move.toRow][0]={PieceType::None,Color::None};
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
        board[move.toRow][move.toCol]={move.PromotionPiece,getTurn()};
        halfMoveClock++;
    }
    board[move.fromRow][move.fromCol]={PieceType::None,Color::None};
    if(!flag){
        enPassantTargetcol=-1;
        enPassantTargetRow=-1;
    }
    if(!WhiteToMove){
        fullMoveClock++;
        
    }
    // king moved — lose both rights for that color
if (move.fromRow == 7 && move.fromCol == 4) {
    castlingKingSideWhite = castlingQueenSideWhite = false;
}
if (move.fromRow == 0 && move.fromCol == 4) {
    castlingKingSideBlack = castlingQueenSideBlack = false;
}

// rook moved from starting square — lose that side's right
if (move.fromRow == 7 && move.fromCol == 7) castlingKingSideWhite = false;
if (move.fromRow == 7 && move.fromCol == 0) castlingQueenSideWhite = false;
if (move.fromRow == 0 && move.fromCol == 7) castlingKingSideBlack = false;
if (move.fromRow == 0 && move.fromCol == 0) castlingQueenSideBlack = false;

// rook captured on its starting square — lose that right too
if (move.toRow == 7 && move.toCol == 7) castlingKingSideWhite = false;
if (move.toRow == 7 && move.toCol == 0) castlingQueenSideWhite = false;
if (move.toRow == 0 && move.toCol == 7) castlingKingSideBlack = false;
if (move.toRow == 0 && move.toCol == 0) castlingQueenSideBlack = false;
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
        break;
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



bool GameState::inCheck()const {
    std::vector<Move> moves=generatePseudoLegalMoves(*this);
    for(auto move:moves){
        if(move.type==MoveType::Capture||move.type==MoveType::PromotionCapture){
            if((board[move.toRow][move.toCol].type==PieceType::King)&&(board[move.toRow][move.toCol].color!=getTurn())){
                return true;
            }
            
        }
    }
    return false;
}

void GameState::LoadFEN(const std::string &fen){
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

