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


Queen::Queen(TeamColor color) : ChessPiece(color, (color == WHITE) ? 'Q' : 'q') {}

bool Queen::isValidMove(int startRow, int startCol, int endRow, int endCol, ChessPiece* grid[8][8]) const 
{
    int rDiff = absoluteValue(endRow - startRow);
    int cDiff = absoluteValue(endCol - startCol);

    if (startRow != endRow && startCol != endCol && rDiff != cDiff) 
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


King::King(TeamColor color) : ChessPiece(color, (color == WHITE) ? 'K' : 'k') {}

bool King::isValidMove(int startRow, int startCol, int endRow, int endCol, ChessPiece* grid[8][8]) const 
{
    return (absoluteValue(endRow - startRow) <= 1 && absoluteValue(endCol - startCol) <= 1) && (grid[endRow][endCol] == nullptr || grid[endRow][endCol]->getTeam() != team);
}


ChessBoard::ChessBoard() 
{
    for (int i = 0; i < 8; i++) 
    {
        for (int j = 0; j < 8; j++) 
        {
            grid[i][j] = nullptr;
        }
    }
    initializePieces();
}

ChessBoard::~ChessBoard() 
{ 
    for (int i = 0; i < 8; i++) 
    {
        for (int j = 0; j < 8; j++) 
        {
            delete grid[i][j];
        }
    }
}

void ChessBoard::initializePieces() 
{
    grid[0][0] = new Rook(BLACK); 
    grid[0][7] = new Rook(BLACK);
    grid[0][1] = new Knight(BLACK); 
    grid[0][6] = new Knight(BLACK);
    grid[0][2] = new Bishop(BLACK); 
    grid[0][5] = new Bishop(BLACK);
    grid[0][3] = new Queen(BLACK); 
    grid[0][4] = new King(BLACK);
    for (int i = 0; i < 8; i++) 
    {
        grid[1][i] = new Pawn(BLACK);
    }
    
    grid[7][0] = new Rook(WHITE); 
    grid[7][7] = new Rook(WHITE);
    grid[7][1] = new Knight(WHITE); 
    grid[7][6] = new Knight(WHITE);
    grid[7][2] = new Bishop(WHITE); 
    grid[7][5] = new Bishop(WHITE);
    grid[7][3] = new Queen(WHITE); 
    grid[7][4] = new King(WHITE);
    for (int i = 0; i < 8; i++) 
    {
        grid[6][i] = new Pawn(WHITE);
    }
}

bool ChessBoard::isSquareUnderAttack(int row, int col, TeamColor attackerColor) 
{
    for (int i = 0; i < 8; i++) 
    {
        for (int j = 0; j < 8; j++) 
        {
            if (grid[i][j] != nullptr && grid[i][j]->getTeam() == attackerColor) 
            {
                if (grid[i][j]->isValidMove(i, j, row, col, grid)) 
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool ChessBoard::isKingInCheck(TeamColor kingColor) 
{
    int kR = -1, kC = -1;
    for (int i = 0; i < 8; i++) 
    {
        for (int j = 0; j < 8; j++) 
        {
            if (grid[i][j] != nullptr && grid[i][j]->getTeam() == kingColor && (grid[i][j]->getPieceSymbol() == 'K' || grid[i][j]->getPieceSymbol() == 'k')) 
            {
                kR = i; kC = j; 
                break;
            }
        }
    }
    return isSquareUnderAttack(kR, kC, (kingColor == WHITE ? BLACK : WHITE));
}

bool ChessBoard::canEscapeCheck(TeamColor playerColor) 
{
    for (int sR = 0; sR < 8; sR++) 
    {
        for (int sC = 0; sC < 8; sC++) 
        {
            if (grid[sR][sC] != nullptr && grid[sR][sC]->getTeam() == playerColor) 
            {
                for (int eR = 0; eR < 8; eR++) 
                {
                    for (int eC = 0; eC < 8; eC++) 
                    {
                        if (grid[sR][sC]->isValidMove(sR, sC, eR, eC, grid)) 
                        {
                            ChessPiece* tempDest = grid[eR][eC];
                            grid[eR][eC] = grid[sR][sC];
                            grid[sR][sC] = nullptr;
                            bool stillInCheck = isKingInCheck(playerColor);
                            grid[sR][sC] = grid[eR][eC];
                            grid[eR][eC] = tempDest;
                            if (!stillInCheck) return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool ChessBoard::movePiece(int sRow, int sCol, int eRow, int eCol, TeamColor playerTurn) 
{
    if (sRow < 0 || sRow > 7 || sCol < 0 || sCol > 7 || eRow < 0 || eRow > 7 || eCol < 0 || eCol > 7) 
    {
        return false;
    }
    ChessPiece* piece = grid[sRow][sCol];

    if (piece == nullptr || piece->getTeam() != playerTurn) 
    {
        return false;
    }

    if (!piece->isValidMove(sRow, sCol, eRow, eCol, grid)) 
    {
        return false;
    }

    ChessPiece* tempDest = grid[eRow][eCol];
    grid[eRow][eCol] = grid[sRow][sCol];
    grid[sRow][sCol] = nullptr;

    if (isKingInCheck(playerTurn)) 
    {
        grid[sRow][sCol] = grid[eRow][eCol];
        grid[eRow][eCol] = tempDest;
        return false;
    }
    delete tempDest;
    return true;
}

void ChessBoard::display() 
{
    cout << "\n    0 1 2 3 4 5 6 7\n   -----------------\n";
    for (int i = 0; i < 8; i++) 
    {
        cout << i << " | ";
        for (int j = 0; j < 8; j++) 
        { 
            if (grid[i][j] == nullptr) 
            {
                cout << ". "; 
            }
            else 
            {
                cout << grid[i][j]->getPieceSymbol() << " ";
            }
        }
        cout << "|\n";
    }
    cout << "   -----------------\n";
}

ChessEngine::ChessEngine() : activeTurn(WHITE) {}
void ChessEngine::play() 
{
    while (true) 
    {
        board.display();
        if (board.isKingInCheck(activeTurn)) 
        {
            if (!board.canEscapeCheck(activeTurn)) 
            {
                cout << "\nCHECKMATE! " << (activeTurn == WHITE ? "BLACK" : "WHITE") << " WINS!\n";
                break;
            }
            cout << "!!! YOUR KING IS IN CHECK !!!\n";
        }
        cout << (activeTurn == WHITE ? "WHITE" : "BLACK") << "'S TURN\n";
        int sR, sC, eR, eC;
        cout << "Source (Row Col): "; cin >> sR >> sC;
        cout << "Target (Row Col): "; cin >> eR >> eC;
        if (board.movePiece(sR, sC, eR, eC, activeTurn)) 
        {
            activeTurn = (activeTurn == WHITE) ? BLACK : WHITE;
        }
        else cout << "[ERROR] Invalid Move (King may be in check).\n";
    }
}   