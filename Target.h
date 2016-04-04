#ifndef TARGET_H
#define TARGET_H

#include "Coordinate.h"
#include "Ship.h"


class Target
{
    public:
        enum ShotResult{unChecked, hit, miss};      // results of shot
        enum Aim{up, down, left, right};            // what direction the system is aiming

        // Constructors
            // doubles as default if no parameter is passed in, boardSize 5 is used
        Target(int boardSize = 5);
            // Pass it a coordinate that has hit a ship, and the size of the board attacking on
        Target(Coordinate, int);

        // Returns Coordinate for next attack, may throw an exception
            // PRE: DO NOT pass this function an integer.  Param is used for error checking only
        Coordinate retrieveFireCoord(int recursiveCount = 0) throw (int);

        // report how the last shot turned out.
            // PRE: true for a hit, false == miss
            // POST: if false, aim will be adjusted
        void reportStatus(bool) throw (int);

        // report a destroyed ship
            // POST: target is released -
            // TBD: if another ship was found, obtain new target
        void shipDestroyed(Ship);

        // Set a new target
            // PRE: Coordinate parameter has hit a ship
        void setNewTarget(Coordinate);

        // return true if the system currently has a target
        bool getTargetAquired() const;

        // set how large the board is to be attacked
        void setMaxSize(int );

    private:
        // coordinate of the initial contact
        Coordinate initialHit;
        // what direction is the system aiming...
        Aim currentAim;

        // keep track of the results of aiming in each direction
        ShotResult upResult;
        ShotResult downResult;
        ShotResult leftResult;
        ShotResult rightResult;
        // how many shots have been fired in current direction
        int shotsInDirection;
        bool targetAquired; // do we have a target
        int maxSize;
        int missesInSuccession;

        // Chooses a new direction for the system
        Aim chooseDirection();

        // true if the coordinate chosen by the system falls on the board
        bool testBoundaries(Coordinate) const;


};

#endif // TARGET_H
