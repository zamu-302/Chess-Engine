#pragma once
#include <iostream>

enum class PieceType{
None,
Pawn,
Knight,
Bishop,
Rook,
Queen,
King
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
enum class Color{
    None,
    Black,
    White
};
struct Piece{
    PieceType type;
    Color color;
};
struct Move{
    int fromRow;
    int fromCol;
    int toRow;
    int toCol;
    MoveType type=MoveType::Normal;
    PieceType PromotionPiece=PieceType::None;
};
