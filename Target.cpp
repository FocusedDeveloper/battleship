#include "Target.h"
#include <iostream>
#include <cstdlib>

using namespace::std;

// constructors... omg, i have no dynamic data!  No copy constructor for me!
Target::Target(int boardSize)
{
    maxSize = boardSize;
    targetAquired = false;
    missesInSuccession = 0;
}

// pass me a hit and a board size
Target::Target(Coordinate origin, int boardSize)
{
    initialHit = origin;
    upResult = unChecked;
    downResult = unChecked;
    leftResult = unChecked;
    rightResult = unChecked;

    shotsInDirection = 1;   // TBD: I need to fix these numbers to read accurately.  But everything works as is.
    targetAquired = true;
    maxSize = boardSize;
    missesInSuccession = 0;

    currentAim = static_cast<Aim>(rand()%4);        // choose a random direction to begin aiming
    //ctor
}

// sets max size
void Target::setMaxSize(int boardSize)
{
    maxSize = boardSize;
}

// choose a new direction to aim
Target::Aim Target::chooseDirection()
{
    //cout<<"changing directions"<<endl;
    Aim newDirection;
    int random = rand()%2;  // random number for tie breaking

    switch (currentAim)         // based on where we are currently aiming...
    {
        case left:                          // if we are aiming one way...
            if(rightResult == unChecked)        // go the opposite if we haven't already
                newDirection = right;
            else if(random == 0)                // otherwise, use the random number
            {
                if(upResult == unChecked)       // and go one of the remaining two directions...
                    newDirection = up;                  // if we haven't already
                else
                    newDirection = down;
            }else
            {
                if(downResult == unChecked)
                    newDirection = down;
                else
                    newDirection = up;
            }
            break;
        case right:                         // repeat for other directions
            if(leftResult == unChecked)
                newDirection = left;
            else if(random == 0)
            {
                if(upResult == unChecked)
                    newDirection = up;
                else
                    newDirection = down;
            }else
            {
                if(downResult == unChecked)
                    newDirection = down;
                else
                    newDirection = up;
            }
            break;
        case up:
            if(downResult == unChecked)
                newDirection = down;
            else if(random == 0)
            {
                if(leftResult == unChecked)
                    newDirection = left;
                else
                    newDirection = right;
            }else
            {
                if(rightResult == unChecked)
                    newDirection = right;
                else
                    newDirection = left;
            }
            break;
        case down:
            if(upResult == unChecked)
                newDirection = up;
            else if(random == 0)
            {
                if(leftResult == unChecked)
                    newDirection = left;
                else
                    newDirection = right;
            }else
            {
                if(rightResult == unChecked)
                    newDirection = right;
                else
                    newDirection = left;
            }
            break;
        default:
            break;
    }
    return newDirection;
}

// Return the next coordinate to be attacked
Coordinate Target::retrieveFireCoord(int recursiveCount) throw (int)
{
    Coordinate myCoord;

    // IF we haven't gotten a valid point after 5 tries...
    if(recursiveCount > 5)  // base case
    {
        targetAquired = false;      // give up
        throw recursiveCount;           // throw exception
    }

    switch (currentAim)     // based on current aim...
    {
        case left:
            myCoord.xCoord = initialHit.xCoord-shotsInDirection;        // choose a coordinate based on
            myCoord.yCoord = initialHit.yCoord;                             // shots fired in current direction
            break;
        case right:
            myCoord.xCoord = initialHit.xCoord+shotsInDirection;
            myCoord.yCoord = initialHit.yCoord;
            break;
        case up:
            myCoord.xCoord = initialHit.xCoord;
            myCoord.yCoord = initialHit.yCoord-shotsInDirection;
            break;
        case down:
            myCoord.xCoord = initialHit.xCoord;
            myCoord.yCoord = initialHit.yCoord+shotsInDirection;
            break;
        default:
            break;
    }
    if( !testBoundaries(myCoord) )      // if the coordinate is out of bounds...
    {
        reportStatus(false);                    // update the system
        myCoord = retrieveFireCoord(recursiveCount+1);  // get another coordinate
        shotsInDirection--;     // balance out shots fired with recursive call
    }
    shotsInDirection++;

    /* TBD: these comments will be used for error reporting */
   // cout<<"Fire on position: ";
   // cout<<"("<<myCoord.xCoord<<", "<<myCoord.yCoord<<")"<<endl;
   // cout<<"Shots in direction: "<<shotsInDirection<<endl;
   // cout<<"Current direction: ";
//    switch (currentAim)
//    {
//        case left:
//            cout<<"left."<<endl;
//            break;
//        case right:
//            cout<<"right."<<endl;
//            break;
//        case up:
//            cout<<"up."<<endl;
//            break;
//        case down:
//            cout<<"down."<<endl;
//            break;
//        default:
//            break;
//    }

return myCoord;

}

// report the status of the last shot fired
void Target::reportStatus(bool targetHit) throw (int)
{
    if(targetHit)       // on hit, reset misses
        missesInSuccession = 0;
    else
        missesInSuccession++;   // on miss, increment misses

    if(missesInSuccession > 5)  // after five misses...
    {
        targetAquired = false;      // give up target
        throw missesInSuccession;
    }

    //TBD: Still need to check these numbers again....
    if(shotsInDirection == 2)       // on the first shot in this direction
    {
        switch (currentAim)             // track the result
        {
        case left:                  // in current direction
            if(!targetHit)  // if we missed
            {
                leftResult = miss;                  // track it
                currentAim = chooseDirection();     // choose a new direction
                shotsInDirection = 1;               // reset shots in direction
            }
            else{
                leftResult = hit;                   // else report hit
                //shotsInDirection = 1;
            }
            break;
        case right:                         // repeat for other directions
            if(!targetHit)
            {
                rightResult = miss;
                currentAim = chooseDirection();
                shotsInDirection = 1;
            }
            else{
                rightResult = hit;
                //shotsInDirection = 1;
            }
            break;
        case up:
            if(!targetHit)
            {
                upResult = miss;
                currentAim = chooseDirection();
                shotsInDirection = 1;
            }
            else{
                upResult = hit;
                //shotsInDirection = 1;
            }
            break;
        case down:
            if(!targetHit)
            {
                downResult = miss;
                currentAim = chooseDirection();
                shotsInDirection = 1;
            }
            else{
                downResult = hit;
                //shotsInDirection = 1;
            }
            break;
        default:
            break;
        }
    }else if(!targetHit)
    {
        currentAim = chooseDirection();
        shotsInDirection = 1;
    }
//    if(targetHit)
//        shotsInDirection++;
}

// On ship destroyed, pass system the destroyed ship
void Target::shipDestroyed(Ship target)
{
    Coordinate myCoord;
    targetAquired = false;      // release the current target
    if(target.getOrientation() == Ship::vertical)   // if the ship was vertical
    {
        if(leftResult == hit)                               // and we got a hit on the left.. or right of the ship
        {
            myCoord.xCoord = initialHit.xCoord-1;                   // we have a new target set in this direction
            myCoord.yCoord = initialHit.yCoord;
            targetAquired = true;
        }
        else if(rightResult == hit)                         // or right.
        {
            myCoord.xCoord = initialHit.xCoord+1;
            myCoord.yCoord = initialHit.yCoord;
            targetAquired = true;
        }
    }else                           // repeat for up and down
    {
        if(upResult == hit)
        {
            myCoord.xCoord = initialHit.xCoord;
            myCoord.yCoord = initialHit.yCoord-1;
            targetAquired = true;
        }
        else if(downResult == hit)
        {
            myCoord.xCoord = initialHit.xCoord;
            myCoord.yCoord = initialHit.yCoord+1;
            targetAquired = true;
        }
    }
    if(targetAquired)               // if we have a new target
        setNewTarget(myCoord);          // initialize it.
}

void Target::setNewTarget(Coordinate myCoord)
{
    /* comments to be used for error logging */
    //cout<<"Target Aquired"<<endl;
    //cout<<"Origin: ("<<myCoord.xCoord<<", "<<myCoord.yCoord<<")"<<endl;
    initialHit = myCoord;
    upResult = unChecked;
    downResult = unChecked;
    leftResult = unChecked;
    rightResult = unChecked;

    missesInSuccession = 0;
    shotsInDirection = 1;
    targetAquired = true;

    currentAim = static_cast<Aim>(rand()%4);        // choose a random direction to begin aiming...
}

bool Target::getTargetAquired() const
{
    return targetAquired;
}

// test the boundaries of the coordinate
bool Target::testBoundaries(Coordinate myCoord) const
{
    if(myCoord.xCoord < 0 || myCoord.yCoord < 0)
        return false;
    if(myCoord.xCoord >= maxSize || myCoord.yCoord >= maxSize)
        return false;

    return true;
}
