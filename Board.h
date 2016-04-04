#ifndef BOARD_H
#define BOARD_H
#include "Ship.h"


class Board
{
    public:
        // Static constants of board characters
        static const char HIT = 'H';
        static const char MISS = '.';
        static const char ERR_CHAR = 'E';
        static const char SHIP = '#';
        static const char OCEAN = '~';

        // Constructors
            // Set's board to NULL, size to 0
        Board();
            // Creates board of int size
        Board(int);
            // Copy constructor
        Board(const Board&);
            // Assignment operator
        Board& operator=(const Board&);
            // Destructor
        ~Board();

        // prints the board to the screen
        void print(bool viewShips = false) const;

        // returns what character is at a particular coordinate on the board
        // PRE: Coordinate is within bounds of the board
        char checkSpace(Coordinate);

        // Returns if a ship will fit on the board at given Coordinate and with given Orientation
        // PRE: Ship has been initialized
        // POST: Returns true if the ship fits
        bool shipFit(Ship& myShip, Coordinate, Ship::Orientation);

        // Places given ship on the board
        // PRE: Ship fits on the board
        void placeShip(Ship&);

        // Changes character at Coordinate given parameter
            // PRE: Coordinate is within board range
        void updateBoard(char,Coordinate);

        // Returns board size
        int getSize() const;

        // Returns the result of a attack at Coordinate
            // PRE: Coordinate is within board range
        char incomingAttack(Coordinate);

    private:
        char** board;
        int size;

        // Maximum and minimum values for ship size.
        static const int MAXSIZE = 30;
        static const int MINSIZE = 5;

        // Sets the size of the board
        // POST: Size set between Min and Max
        void setSize(int);

        // Initializes the board
        // PRE: Size must be set
        void initBoard();

};

#endif // BOARD_H
