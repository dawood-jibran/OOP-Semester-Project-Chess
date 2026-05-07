#include "ChessGame.h"

int absoluteValue(int value) 
{
    return (value < 0) ? -value : value;
}

ChessPiece::ChessPiece(TeamColor teamColor, char symbol) : team(teamColor), pieceSymbol(symbol) {}
ChessPiece::~ChessPiece() {}
TeamColor ChessPiece::getTeam() const { return team; }
char ChessPiece::getPieceSymbol() const { return pieceSymbol; }

Bishop::Bishop(TeamColor color) : ChessPiece(color, (color == WHITE) ? 'B' : 'b') {}
bool Bishop::isValidMove(int startRow, int startCol, int endRow, int endCol, ChessPiece* grid[8][8]) const 
{
    if (absoluteValue(endRow - startRow) != absoluteValue(endCol - startCol)) return false;
    int rowDir = (endRow > startRow) ? 1 : -1;
    int colDir = (endCol > startCol) ? 1 : -1;
    int currR = startRow + rowDir;
    int currC = startCol + colDir;
    while (currR != endRow) 
    {
        if (grid[currR][currC] != nullptr) return false; 
        currR += rowDir;
        currC += colDir;
    }
    return (grid[endRow][endCol] == nullptr || grid[endRow][endCol]->getTeam() != team);
}


King::King(TeamColor color) : ChessPiece(color, (color == WHITE) ? 'K' : 'k') {}
bool King::isValidMove(int startRow, int startCol, int endRow, int endCol, ChessPiece* grid[8][8]) const 
{
    return (absoluteValue(endRow - startRow) <= 1 && absoluteValue(endCol - startCol) <= 1) && (grid[endRow][endCol] == nullptr || grid[endRow][endCol]->getTeam() != team);
}