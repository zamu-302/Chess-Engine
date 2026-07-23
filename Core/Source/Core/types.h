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
};