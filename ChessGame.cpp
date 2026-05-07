#include "ChessGame.h"

int absoluteValue(int value) 
{
    return (value < 0) ? -value : value;
}

ChessPiece::ChessPiece(TeamColor teamColor, char symbol) : team(teamColor), pieceSymbol(symbol) {}

ChessPiece::~ChessPiece() {}

TeamColor ChessPiece::getTeam() const 
{ 
    return team; 
}

char ChessPiece::getPieceSymbol() const 
{ 
    return pieceSymbol; 
}

Pawn::Pawn(TeamColor color) : ChessPiece(color, (color == WHITE) ? 'P' : 'p') {}

bool Pawn::isValidMove(int startRow, int startCol, int endRow, int endCol, ChessPiece* grid[8][8]) const 
{
    int direction = (team == WHITE) ? -1 : 1; 
    int initialRow = (team == WHITE) ? 6 : 1;

    if (startCol == endCol && (endRow - startRow == direction)) 
    {
        if (grid[endRow][endCol] == nullptr) 
        {
            return true;
        }
    }

    if (startCol == endCol && startRow == initialRow && (endRow - startRow == 2 * direction)) 
    {
        if (grid[startRow + direction][startCol] == nullptr && grid[endRow][endCol] == nullptr) 
        {
            return true;
        }
    }

    if (absoluteValue(endCol - startCol) == 1 && (endRow - startRow == direction)) 
    {
        if (grid[endRow][endCol] != nullptr && grid[endRow][endCol]->getTeam() != this->team) 
        {
            return true;
        }
    }

    return false;
}

Rook::Rook(TeamColor color) : ChessPiece(color, (color == WHITE) ? 'R' : 'r') {}

bool Rook::isValidMove(int startRow, int startCol, int endRow, int endCol, ChessPiece* grid[8][8]) const 
{
    if (startRow != endRow && startCol != endCol) 
    {
        return false;
    }

    int rowDir = (endRow == startRow) ? 0 : (endRow > startRow ? 1 : -1);
    int colDir = (endCol == startCol) ? 0 : (endCol > startCol ? 1 : -1);
    
    int currR = startRow + rowDir;
    int currC = startCol + colDir;
    while (currR != endRow || currC != endCol) 
    {
        if (grid[currR][currC] != nullptr) 
        {
            return false;
        }
        
        currR += rowDir;
        currC += colDir;
    }

    return (grid[endRow][endCol] == nullptr || grid[endRow][endCol]->getTeam() != team);
}

Knight::Knight(TeamColor color) : ChessPiece(color, (color == WHITE) ? 'N' : 'n') {}

bool Knight::isValidMove(int startRow, int startCol, int endRow, int endCol, ChessPiece* grid[8][8]) const 
{
    int rDiff = absoluteValue(endRow - startRow);
    int cDiff = absoluteValue(endCol - startCol);
    
    return ((rDiff == 2 && cDiff == 1) || (rDiff == 1 && cDiff == 2)) && (grid[endRow][endCol] == nullptr || grid[endRow][endCol]->getTeam() != team);
}

Bishop::Bishop(TeamColor color) : ChessPiece(color, (color == WHITE) ? 'B' : 'b') {}

bool Bishop::isValidMove(int startRow, int startCol, int endRow, int endCol, ChessPiece* grid[8][8]) const 
{
    if (absoluteValue(endRow - startRow) != absoluteValue(endCol - startCol)) 
    {
        return false;
    }
    
    int rowDir = (endRow > startRow) ? 1 : -1;
    int colDir = (endCol > startCol) ? 1 : -1;
    
    int currR = startRow + rowDir;
    int currC = startCol + colDir;
    
    while (currR != endRow) 
    {
        if (grid[currR][currC] != nullptr) 
        {
            return false;
        }

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