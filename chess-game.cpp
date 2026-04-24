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

int main()
{
    return 0;
}