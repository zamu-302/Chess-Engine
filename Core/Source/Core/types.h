#pragma once
#include <cstdint>
#include <iostream>


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
    PieceType PromotionPiece=PieceType::None;
};
class Postion{
    public:
    uint64_t whitePawn=0;  
    uint64_t whiteQueen=0;  
    uint64_t whiteKing=0;  
    uint64_t whiteRook=0;  
    uint64_t whiteBishop=0;  
    uint64_t whiteKnight=0;  
    uint64_t blackPawn=0;  
    uint64_t blackQueen=0;  
    uint64_t blackKing=0;  
    uint64_t blackRook=0;  
    uint64_t blackKnight=0;  
    uint64_t blackBishop=0;  
     
};
struct Piece{
    PieceType type=PieceType::None;
    Color color=Color::None;
};
