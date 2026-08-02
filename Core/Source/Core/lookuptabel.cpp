#include <iostream>
#include "Lookuptabel.h"
constexpr bool checkBound(int row, int col) {
    return row >= 0 && row < 8 && col >= 0 && col < 8;
}
void KnightLookupTabel(){
    for(int sq=0;sq<64;++sq){
        uint64_t attacks=0ULL;
        int r=sq/8;
        int c=sq%8;
            
        if (checkBound(r+2,c+1)) attacks |= 1ULL << (sq + 17);
        if (checkBound(r+2,c-1)) attacks |= 1ULL << (sq + 15);
        if (checkBound(r-2,c+1)) attacks |= 1ULL << (sq - 15);
        if (checkBound(r-2,c-1)) attacks |= 1ULL << (sq - 17);
        if (checkBound(r+1,c+2)) attacks |= 1ULL << (sq + 10);
        if (checkBound(r+1,c-2)) attacks |= 1ULL << (sq + 6);
        if (checkBound(r-1,c+2)) attacks |= 1ULL << (sq - 6);
        if (checkBound(r-1,c-2)) attacks |= 1ULL << (sq - 10);

        knightAttacks[sq] = attacks;

    }





}
void KingLookupTabel(){

    for(int sq=0;sq<64;sq++){
        uint64_t attack=0ULL;
        int r=sq/8;
        int c=sq%8;

        if(checkBound(r+1,c))attack|=1ULL<<(sq+8);
        if(checkBound(r+1,c+1))attack|=1ULL<<(sq+9);
        if(checkBound(r,c+1))attack|=1ULL<<(sq+1);
        if(checkBound(r-1,c))attack|=1ULL<<(sq-8);
        if(checkBound(r+1,c-1))attack|=1ULL<<(sq+7);
        if(checkBound(r,c-1))attack|=1ULL<<(sq-1);
        if(checkBound(r-1,c-1))attack|=1ULL<<(sq-9);
        if(checkBound(r-1,c+1))attack|=1ULL<<(sq-7);

        kingAttacks[sq]=attack;
         

    }
}

constexpr uint64_t rookOccupancy(int sq){
    int row=sq/8;
    int col=sq%8;
    uint64_t mask=0ULL;
    for(int rank=row+1;rank<7;rank++){
        mask|=(1ULL<<(rank*8+col));
    }
    for(int rank=row-1;rank>0;rank--){
        mask|=(1ULL<<(rank*8+col));
    }
    for(int file=col+1;file<7;file++){
        mask|=(1ULL<<(row*8+file));
    }
    for(int file=col-1;file>0;file--){
        mask|=(1ULL<<(row*8+file));
    }

    return mask;



}
constexpr bool isInnerBound(int row,int col){
return (row>0&&row<7)&&(col>0&&col<7);
}

constexpr uint64_t bishopOccupancy(int sq){
    constexpr int offset[4][2]{{1,1},{1,-1},{-1,1},{-1,-1}};
    int row=sq/8;
    int col=sq%8;
    uint64_t mask=0ULL;
    for(int i=0;i<4;i++){
    int curRow=offset[i][0]+row;
    int curCol=offset[i][1]+col;
    while(isInnerBound(curRow,curCol)){
        mask|=(1ULL<<(curRow*8+curCol));
        curRow+=offset[i][0];
        curCol+=offset[i][1];
        }
    }
    return mask;


    
}

uint64_t generate_bishop_attack(int sq,uint64_t block){
    constexpr int offset[4][2]{{1,1},{1,-1},{-1,1},{-1,-1}};
    int row=sq/8;
    int col=sq%8;
    uint64_t attacks=0ULL;
    for(int i=0;i<4;i++){
    int curRow=offset[i][0]+row;
    int curCol=offset[i][1]+col;
    while(checkBound(curRow,curCol)){
        attacks|=(1ULL<<(curRow*8+curCol));
        if (block&(1ULL<<(curRow*8+curCol))) break;
        curRow+=offset[i][0];
        curCol+=offset[i][1];
        }
    }
    return attacks;
}
uint64_t generate_rook_attack(int sq,uint64_t block){
    int row=sq/8;
    int col=sq%8;
    uint64_t attacks=0ULL;
    for(int rank=row+1;rank<=7;rank++){
        attacks|=(1ULL<<(rank*8+col));
        if(block&(1ULL<<(rank*8+col))) break;
    }
    for(int rank=row-1;rank>=0;rank--){
        attacks|=(1ULL<<(rank*8+col));
        if(block&(1ULL<<(rank*8+col))) break;
    }
    for(int file=col+1;file<=7;file++){
        attacks|=(1ULL<<(row*8+file));
        if(block&(1ULL<<(row*8+file))) break;
    }
    for(int file=col-1;file>=0;file--){
        attacks|=(1ULL<<(row*8+file));
        if(block&(1ULL<<(row*8+file))) break;
    }

    return attacks;
}