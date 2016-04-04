#include "Board.h"
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <limits>
#include <iostream>

using namespace::std;

// Default constructor
Board::Board()
{
    size = 0;
    board = NULL;
}

// Copy Constructor
Board::Board(const Board& origBoard)
{
    size = origBoard.size;

    board = new char* [size];       // Allocates dynamic space

    for( int i = 0; i<size; i++)
        board[i] = new char[size];

    for(int i =0; i<size; i++)      // Deep copy dynamic data
    {
        for(int j = 0; j<size; j++)
        {
            board[i][j] = origBoard.board[i][j];
        }
    }
}

// Assignment Operator for deep copy
Board& Board::operator=(const Board& origBoard)
{
    if(this != &origBoard)
    {
        for( int i = 0; i<size; i++)        // Deallocate current dynamic data
            delete [] board[i];
        delete []board;

        size = origBoard.size;

        board = new char* [size];

        for( int i = 0; i<size; i++)        // Allocate new space for dynamic data
            board[i] = new char[size];

        for(int i =0; i<size; i++)
        {
            for(int j = 0; j<size; j++)
            {
                board[i][j] = origBoard.board[i][j];    // copy...
            }
        }
    }
    return *this;
}

// Create board of given size
Board::Board(int mySize)
{
    if(mySize < 1)
    {
        size = 0;
        board = NULL;
    }
    else{                       // first set size
        setSize(mySize);
        initBoard();            // then initialize the board
    }
}

// destructor free's dynamic memory
Board::~Board()
{
    for( int i = 0; i<size; i++)
        delete [] board[i];

    delete []board;
}

// insure size falls between set limits
void Board::setSize(int mySize)
{
    if(mySize < MINSIZE )
        mySize = MINSIZE;
    else if(mySize > MAXSIZE )
        mySize = MAXSIZE;
    size = mySize;
}

int Board::getSize() const
{
    return size;
}

// init board to all ocean tiles
void Board::initBoard()
{
    board = new char* [size];

    for( int i = 0; i<size; i++)
        board[i] = new char[size];

    for(int i =0; i<size; i++)
    {
        for(int j = 0; j<size; j++)
        {
            board[i][j] = OCEAN;
        }
    }
}

// print's board
// POST: If viewShips is true, ships will be shown on board
void Board::print(bool viewShips) const
{
    char tile = 'A';                    // Used to display characters across the top of board
    cout<<endl<<"    ";
    for(int i =0; i<size; i++)     // Display A through boardsize characters across top of board
    {
        cout<<setw(4)<<tile;
        tile++;
    }
    cout<<endl<<endl;
    for(int i =0; i<size; i++)         // Nested for loop to display board
    {
        cout<<setw(4)<<i+1;                 // Display numbers down the left side of the board
        for(int j = 0; j<size; j++)
        {
            tile = board[i][j];             // Depending on what character in a specific place on the board
            switch (tile)
            {
                case OCEAN:
                    cout<<setw(4)<<OCEAN;
                    break;
                case SHIP:
                    if(viewShips)
                        cout<<setw(4)<<SHIP;
                    else
                        cout<<setw(4)<<OCEAN;
                    break;
                case HIT:
                    cout<<setw(4)<<HIT;
                    break;
                case MISS:
                    cout<<setw(4)<<MISS;
                    break;
                default:
                    cout<<setw(4)<<ERR_CHAR;
            }
        }
        cout<<endl<<endl;
    }
}

// returns character at space
char Board::checkSpace(Coordinate myCoord)
{
    return board[myCoord.yCoord][myCoord.xCoord];
}

// return true if the ship fits on the board with given parameters and there are no conflicts
bool Board::shipFit(Ship& myShip, Coordinate myCoord, Ship::Orientation myOrn)
{
    bool fit = false;

    if(myOrn == Ship::vertical)                                      // If the ship is vertical...
    {
        if(myCoord.yCoord+myShip.getSize() <= size)                          // And if the Y coordinates for the ship don't go out of bounds of the board
        {
            fit = true;                                                     // Then the ship fits
            for(int i = myCoord.yCoord; i<myCoord.yCoord+myShip.getSize();i++)     // For every position the ship would occupy
            {
                if(board[i][myCoord.xCoord]!=OCEAN)                            // If something is already in that space...
                {
                    fit = false;                                            // The ship does not fit in this location
                    break;                                                  // break out of the loop - there is no need to check the remaining spaces if ship does not fit
                }
            }
        }
    }
    else if(myOrn == Ship::horizontal)                               // If the ship is horizontal...
    {
        if(myCoord.xCoord+myShip.getSize() <= size)                          // And if the X coordinates for the ship don't go out of bounds of the board
        {
            fit = true;                                                     // Then the ship fits
            for(int i = myCoord.xCoord; i<myCoord.xCoord+myShip.getSize(); i++)    // For every position the ship would occupy
            {
                if(board[myCoord.yCoord][i]!=OCEAN)                            // If something is already in that space...
                {
                    fit = false;                                            // The ship does not fit in this location
                    break;                                                  // break out of the loop - there is no need to check the remaining spaces if ship does not fit
                }
            }
        }
    }
    return fit;
}

// places a ship on the board
// PRE: The ship fits on the board, Ship position is set
// POST: Board updated with ship
void Board::placeShip(Ship& myShip)
{
    Coordinate myCoord;

    myCoord = myShip.getPosition();
    if(myShip.getOrientation() == Ship::vertical)                                    // if vertical...
    {
        for(int i = myCoord.yCoord; i<myCoord.yCoord+myShip.getSize(); i++)    // go through each space Y axis starting at the position - through the size
        {
            board[i][myCoord.xCoord] = SHIP;                              // and place the ship on the board
        }
    }
    else if(myShip.getOrientation() == Ship::horizontal)                             // if horizontal...
    {
        for(int i = myCoord.xCoord; i<myCoord.xCoord+myShip.getSize() ; i++)   // go through each space X axis starting at the position - through the size
        {
            board[myCoord.yCoord][i] = SHIP;                              // and place the ship on the board
        }
    }
}

void Board::updateBoard(char oceanTile,Coordinate myCoord)
{
    board[myCoord.yCoord][myCoord.xCoord] = oceanTile;
}

char Board::incomingAttack(Coordinate myCoord)
{
    char attackResult;
    char tile = checkSpace(myCoord);        // get character at position on board
    switch (tile)                                           // check what's in the tile and return a value accordingly
    {
        case OCEAN:
            attackResult = MISS;             // ~ Ocean is miss, return M
            break;
        case SHIP:
            attackResult = HIT;             // # is a hit, return H
            break;
        default:
            attackResult = ERR_CHAR;
    }
    return attackResult;
}
