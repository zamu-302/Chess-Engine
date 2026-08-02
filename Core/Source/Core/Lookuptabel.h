#pragma once

#include <cstdint>

extern uint64_t knightAttacks[64];
extern uint64_t kingAttacks[64];
extern uint64_t rookMask[64];
extern uint64_t bishopMask[64];
extern uint64_t rookAttacks[64][4096];
extern uint64_t bishopAttacks[64][512];
const int BISHOP_BITS[64] = {
    6, 5, 5, 5, 5, 5, 5, 6,
    5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5,
    6, 5, 5, 5, 5, 5, 5, 6
};
const int ROOK_BITS[64] = {
    12, 11, 11, 11, 11, 11, 11, 12,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    12, 11, 11, 11, 11, 11, 11, 12
};
const uint64_t rookMagicnum[64]{};
const uint64_t bishopMagicnum[64]{};
void KnightLookupTabel();
void KingLookupTabel();
constexpr uint64_t rookOccupancy(int sq);
constexpr uint64_t bishopOccupancy(int sq);
uint64_t generate_bishop_attack(int sq,uint64_t occupancy);
uint64_t generate_rook_attack(int sq,uint64_t occupancy);
