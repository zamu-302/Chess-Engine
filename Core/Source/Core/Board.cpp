#include <iostream>
#include <vector>
#include <unordered_set>
#include "types.h"
#include <string>
#include <algorithm>

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


PieceType charToPiece(char c){
    switch (c)
    {
    case 'R':
    case 'r':
        return PieceType::Rook;
    case 'n':
    case 'N':
        return PieceType::Knight;
    case 'K':
    case 'k':
        return PieceType::King;
    case 'Q':
    case 'q':
        return PieceType::Queen;
    case 'B':
    case 'b':
        return PieceType::Bishop;
    case 'P':
    case 'p':
        return PieceType::Pawn;
    default:
        return PieceType::None;
    }
}

class GameState{
public:

void LoadFEN(const std::string & fen);
std::string toFEN()const;
void Makemove(Move move);
void UndoMove();
GameState() {
    LoadFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}
private:
PieceType board[8][8]={};
bool WhiteToMove;
bool castlingKingSideWhite,castlingQueenSideWhite;
bool castlingKingSideBlack,castlingQueenSideBlack;
int enPassantTargetRow;
int enPassantTargetcol;
int fullMoveClock=1;
int halfMoveClock=0;
};

void GameState::LoadFEN(const std::string &fen){
    std::fill(&board[0][0], &board[0][0] + 64, PieceType::None);//resets the postions everytime LoadFEN is called
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
                board[row][col]=charToPiece(pos[j]);
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
                enPassantTargetRow=enpassant[0]-'a';
                enPassantTargetcol=enpassant[1]-'1';
            }
            
        
        halfMoveClock = std::stoi(parts[4]);
        fullMoveClock = std::stoi(parts[5]);


    }

