#include <iostream>
#include "Lookuptabel.h"
bool checkBound(int row, int col) {
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

        if(checkBound(r+1,c))attack<<1ULL<<(sq+8);
        if(checkBound(r+1,c+1))attack<<1ULL<<(sq+9);
        if(checkBound(r,c+1))attack<<1ULL<<(sq+1);
        if(checkBound(r-1,c))attack<<1ULL<<(sq-8);
        if(checkBound(r+1,c-1))attack<<1ULL<<(sq+7);
        if(checkBound(r,c-1))attack<<1ULL<<(sq-1);
        if(checkBound(r-1,c-1))attack<<1ULL<<(sq-9);
        if(checkBound(r-1,c+1))attack<<1ULL<<(sq-7);

        kingAttacks[sq]=attack;
         

    }
}