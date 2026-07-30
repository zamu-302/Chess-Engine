#pragma once
#include <cstdint>
#include <iostream>
class Postion{
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
struct Piece{
    PieceType type;
    Color color;
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
    int from;
    int to;
    MoveType type=MoveType::Normal;
    PieceType PromotionPiece;
};
