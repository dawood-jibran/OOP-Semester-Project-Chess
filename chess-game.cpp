#include <iostream>

using namespace std;

enum Color 
{ 
    WHITE, 
    BLACK 
};

class Piece
{
    protected:
        Color color;
        char symbol;

    public:
        Piece(Color c, char s) : color(c), symbol(s) {}
        virtual ~Piece() {}

        Color getColor() const 
        { 
            return color; 
        }
        char getSymbol() const 
        { 
            return symbol; 
        }

        virtual bool isValidMove(int sR, int sC, int eR, int eC, Piece* board[8][8]) const = 0;
};

class Pawn: public Piece
{
    public:
        Pawn(Color c) : Piece(c, (c == WHITE) ? 'P' : 'p') {}

        bool isValidMove(int sR, int sC, int eR, int eC, Piece* board[8][8]) const override
        {
            int direction = (color == WHITE) ? -1 : 1;
            
            if (sC == eC && (eR-sR == direction))
            {
                if (board[eR][eC] == nullptr)
                {
                    return true;
                }
            }

            bool isOneColumnAway = (eC - sC == 1) || (eC - sC == -1);

            if (isOneColumnAway && (eR - sR == direction))
            {
                if (board[eR][eC] != nullptr && board[eR][eC]->getColor() != this->color)
                {
                    return true;
                }
            }
            return false;
        }
};

class Pawn: public Piece
{
    public:
        Pawn(Color c) : Piece(c, (c == WHITE) ? 'P' : 'p') {}

        bool isValidMove(int sR, int sC, int eR, int eC, Piece* board[8][8]) const override
        {
            int direction = (color == WHITE) ? -1 : 1;
            
            if (sC == eC && (eR-sR == direction))
            {
                if (board[eR][eC] == nullptr)
                {
                    return true;
                }
            }

            bool isOneColumnAway = (eC - sC == 1) || (eC - sC == -1);

            if (isOneColumnAway && (eR - sR == direction))
            {
                if (board[eR][eC] != nullptr && board[eR][eC]->getColor() != this->color)
                {
                    return true;
                }
            }
            return false;
        }
};

class Knight;
class Bishop: public Piece
{
    public:
        Bishop(Color c) : Piece(c, (c == WHITE) ? 'B' : 'b') {}

        bool isValidMove(int sR, int sC, int eR, int eC, Piece* board[8][8]) const override
        {
            int rowDiff = eR - sR;

            if (rowDiff < 0) 
            {
                rowDiff = -rowDiff;
            }

            int colDiff = eC - sC;

            if (colDiff < 0) 
            {
                colDiff = -colDiff;
            }

            if (rowDiff != colDiff || rowDiff == 0)
            {
                return false;
            }

            int rowStep = (eR > sR) ? 1 : -1;
            int colStep = (eC > sC) ? 1 : -1;

            int currentRow = sR + rowStep;
            int currentCol = sC + colStep;

            while (currentRow != eR && currentCol != eC)
            {
                if (board[currentRow][currentCol] != nullptr)
                {
                    return false;
                }

                currentRow += rowStep;
                currentCol += colStep;
            }

            if (board[eR][eC] != nullptr && board[eR][eC]->getColor() == this->color)
            {
                return false;
            }

            return true;            
        }
};

class Queen : public Piece
{
    public:
        Queen(Color c) : Piece(c, (c == WHITE) ? 'Q' : 'q') {}

        bool isValidMove(int sR, int sC, int eR, int eC, Piece* board[8][8]) const override 
        {
            int rowDiff = eR - sR;

            if (rowDiff < 0) 
            {
                rowDiff = -rowDiff;
            }
        
            int colDiff = eC - sC;

            if (colDiff < 0) 
            {
                colDiff = -colDiff;
            }

        bool isStraight = (sR == eR || sC == eC);
        bool isDiagonal = (rowDiff == colDiff);

        if (!isStraight && !isDiagonal) 
        {
            return false;
        }

        if (sR == eR && sC == eC) 
        {
            return false;
        }

        int rowStep = 0;

        if (eR > sR) 
        {
            rowStep = 1;
        }
        else if (eR < sR) 
        {
            rowStep = -1;
        }

        int colStep = 0;

        if (eC > sC) 
        {
            colStep = 1;
        }
        else if (eC < sC) 
        {
            colStep = -1;
        }

        int currR = sR + rowStep;
        int currC = sC + colStep;

        while (currR != eR || currC != eC) 
        {
            if (board[currR][currC] != nullptr) 
            {
                return false;
            }

            currR += rowStep;
            currC += colStep;
        }

        if (board[eR][eC] != nullptr && board[eR][eC]->getColor() == this->color) 
        {
            return false;
        }

        return true;
    }
};

class King : public Piece 
{
    public:
        King(Color c) : Piece(c, (c == WHITE) ? 'K' : 'k') {}

        bool isValidMove(int sR, int sC, int eR, int eC, Piece* board[8][8]) const override 
        {
            int rowDiff = eR - sR;

            if (rowDiff < 0) 
            {
                rowDiff = -rowDiff;
            }

            int colDiff = eC - sC;
            
            if (colDiff < 0) 
            {
                colDiff = -colDiff;
            }

            if (rowDiff <= 1 && colDiff <= 1) 
            {
                if (rowDiff == 0 && colDiff == 0) 
                {
                    return false;
                }

                if (board[eR][eC] != nullptr && board[eR][eC]->getColor() == this->color) 
                {
                return false;
                }
                return true;
            }
            
            return false;
    }
};

int main()
{
    return 0;
}