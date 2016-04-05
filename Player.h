#ifndef PLAYER_H
#define PLAYER_H

#include "battle.h"
#include "Ship.h"
#include "Board.h"
#include "Target.h"
#include "LostTarget.h"

using namespace::battle;

class Player
{
    public:
        // Constructor, double's as default constructor
            // If no parameters are passed, these defaults will be used
        Player(int boardSize = 0, int myNumShips = 0, PlayerType type = human);
        // destructor
        ~Player();
        Player(const Player& other);                // copy constructor
        Player& operator=(const Player& other);     // assignment operator

        // prints complete list of ship info for debugging
        void printList() const;

        // displays the board, displays ships locations if show Ships is true
        // PRE: Board has been initialized
        void displayBoard(bool showShips = false) const;

        // Returns a random coordinate
            // PRE: param contains board size for the coordinate requested
        Coordinate getRandCoordinate(int) const;

        // launches an attack on a player
        // PRE: opposing player's board has been initialized
        void launchAttack(Player&);

        // Getter functions - return appropriate data
        Coordinate getUserCoord(int) const;
        ShipPtr getTargetedShip(Coordinate) const;
        bool getGameOver() const;
        PlayerType getType() const;
        int getNumShips() const;
        string getName() const;

    private:

        string name;
        int playerNumber;   // not currently in use...
        ShipPtr ships;      // linked list of ships
        Board board;
        PlayerType playerType;
        int numShips;
        bool gameLoss;          // true if the game is over
        Target targetingSystem;

        // Create ships, put them in linked list
        // PRE: total ships has been set
        void createShips();

        // Setters - all private, used internally
        void setName();
        int setNumShips(int);
        void setShips();
        void setLoss();

        // passed a player to attack, this function gets a valid attack Coordinate and...
            // returns the Coordinate and char by reference
        // PRE: Pass the function the player being attack, the coordinate to be used, and a char for the result
        void getAttackResults(Player&, Coordinate&, char&);


        //Functions to manage linked list of ships
            // TBD: move to separate class, create list template
        void InitList(ShipPtr& , ShipPtr& );
        void AddToFront(ShipPtr& , ShipPtr& );
        void AddToBack(ShipPtr& , ShipPtr& );

        void removeShip(ShipPtr&  );
};

#endif // PLAYER_H
