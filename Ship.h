#ifndef SHIP_H
#define SHIP_H
#include "Coordinate.h"
#include <string>
#include <iostream>

using std::string;
using std::ostream;


class Ship
{
    friend ostream& operator<<(ostream&, const Ship&);

    public:


        // Tracks Orientation of Ship
        enum Orientation{ vertical, horizontal };

        // Constructors
            // POST: Creates an empty ship with all numbers initialized to zero
        Ship();
            // POST: Ship initialized with name and size of parameters
                // position set to (0,0)
        Ship(string, int);
            // POST: Deep copy of original ship is made
        Ship(const Ship&);


        // Assignment Operator - Makes a deep copy of ship
        Ship& operator=(const Ship&);
        ~Ship();

        // Equal operator
        bool operator==(const Ship&);

        // set's the position and orientation of ship
        void setPosition(Coordinate, Orientation );

        // updates a ship's status when hit
            // PRE: Coordinate confirmed hit with this ship
            // POST: Ships hitbox and alive status are updated
        void onHit(Coordinate);

        // Prints ship's info to display device
        void print() const;

        // Get functions
            // return corresponding ship data
        int getSize() const;
        bool getAlive() const;
        string getName() const;
        Orientation getOrientation() const;
        Coordinate getPosition() const;


    private:
        string name;          // ship's name
        Coordinate position;        // position of ship's head ex: H####
        Orientation orientation;    // ships orientation - vertical or horizontal
        int size;                   // size of the ship
        bool *hitbox;               // tracks the status of each position on the ship
        bool alive; 	        // true if ship is still in play

        // Set's the alive status of ship based on hitbox
        void setAlive();

};

#endif // SHIP_H
