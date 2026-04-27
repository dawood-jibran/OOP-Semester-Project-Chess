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
class Bishop;
class Queen;
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