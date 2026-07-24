#include <iostream>
#include <vector>
#include "Board.h"
#include <string>
#include <algorithm>

Piece GameState::getPiece(int row,int col)const{
    return board[row][col];
}
Color GameState::getTurn()const{
    if(WhiteToMove){
        return Color::White;
    }
    return Color::Black;
}
Color checkColor(char c){
    if (c!='r'||c!='n'||c!='q'||c!='k'||c!='b'||c!='p'){
        return Color::White;
    }
    return Color::Black;
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



void GameState::LoadFEN(const std::string &fen){
    std::fill(&board[0][0], &board[0][0] + 64, Piece{PieceType::None,Color::None});//resets the postions everytime LoadFEN is called
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
                Color color=checkColor(pos[j]);
                PieceType piece= charToPiece(pos[j]);
                board[row][col]=Piece{piece,color};
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

