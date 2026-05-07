#include "ChessGame.h"

int absoluteValue(int value) 
{
    return (value < 0) ? -value : value;
}

ChessPiece::ChessPiece(TeamColor teamColor, char symbol) : team(teamColor), pieceSymbol(symbol) {}
ChessPiece::~ChessPiece() {}
TeamColor ChessPiece::getTeam() const { return team; }
char ChessPiece::getPieceSymbol() const { return pieceSymbol; }