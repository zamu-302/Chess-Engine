#pragma once
#include <cstdint>
#include <iostream>
class Piece{
    public:
    uint64_t whitePawn;  
    uint64_t whiteQueen;  
    uint64_t whiteKing;  
    uint64_t whiteRook;  
    uint64_t whiteBishop;  
    uint64_t whiteKnight;  
    uint64_t blackPawn;  
    uint64_t blackQueen;  
    uint64_t blackKing;  
    uint64_t blackRook;  
    uint64_t blackKnight;  
    uint64_t blackBishop;  
     
};

enum class PieceType{
None,
Rook,
Bishop,
Queen,
King,
Pawn,
Knight
};
enum class Color{
    None,
    White,
    Black
};

enum class MoveType{
    Normal,
    KingSideCastle,
    QueenSideCastle,
    Capture,
    Enpassant,
    Promotion,
   PromotionCapture
};

struct Move{
    int fromRow;
    int fromCol;
    int toRow;
    int toCol;
    MoveType type=MoveType::Normal;
    Piece PromotionPiece;
};
