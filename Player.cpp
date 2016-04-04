#include "Player.h"
#include <iomanip>
#include <iostream>
#include <cstdlib>

using namespace::std;

Player::Player(int boardSize, int myNumShips, PlayerType type)
{
    playerType = type;
    board = Board(boardSize);
    ships = NULL;
    gameLoss = false;
    targetingSystem = Target();

    // If player is human, prompt their name.
    if(playerType == human)
        setName();
    else
        name = "CPUv1";
    cout<<"Name set"<<endl;

    numShips = setNumShips(myNumShips);
    if(numShips > 0)
    {
        createShips();
        setShips();
    }


    //ctor
}

// Destructors are fun
// deallocate dynamic memory
Player::~Player()
// iterate through linked list of ships and deallocate them all
// set ship to NULL
{
    //int x = 1;
    ShipPtr currPtr = ships;
    while(currPtr != NULL)
    {
        //cout<<"Count is: "<<x<<endl;
        removeShip(currPtr);
        currPtr = ships;
//        x++;
//
//        if(currPtr != NULL)
//            currPtr->component.print();
//        else
//            cout<<" All deleted"<<endl;
    }
    ships = NULL;
    //dtor
}

// No idea why I'd want to copy a player... but here it is
// Copy's a player, dynamic data and all
Player::Player(const Player& other)
{

    name = other.name;
    playerNumber = other.playerNumber;
    board = other.board;
    playerType = other.playerType;
    numShips = other.numShips;
    gameLoss = other.gameLoss;
    targetingSystem = other.targetingSystem;

    ships = NULL;

    ShipPtr temp = other.ships;     // create a temp pointer to point to the original list of ships
    ShipPtr newShipPtr = NULL;      // ship pointer for adding ships to new list
    while(temp!= NULL)
    {
        newShipPtr = new ShipNode;                                // allocate space for the new ship
        newShipPtr->component = temp->component;
        if(ships!=NULL)                                           // if this is not the first element of the list...
        {
            AddToBack(ships, newShipPtr);                         // Add this element to the back of the list
        }else
        {
            InitList(ships, newShipPtr);                          // If this is the first element, use this element to initialize the list
        }
        temp = temp->next;
    }
    //copy ctor
}

int Player::setNumShips(int myNumShips)
{
    int mySize = board.getSize();

    if(myNumShips < 0)                        // If less than 1 ship, set amount to 1
    {
        myNumShips = 0;
    }
    else if(myNumShips > mySize)           // If amount of ships is more than the board size, set amount of ships equal to board size
    {
        cout<<"Number of ships cannot exceed the board size."
            <<endl
            <<"Number of ships is being set to: "
            <<mySize<<endl;

        myNumShips = mySize;
    }
    return myNumShips;
}

Player& Player::operator=(const Player& other)
{
    if (this == &other) return *this; // handle self assignment
    //assignment operator

    name = other.name;
    playerNumber = other.playerNumber;
    board = other.board;
    playerType = other.playerType;
    numShips = other.numShips;
    gameLoss = other.gameLoss;
    targetingSystem = other.targetingSystem;

    ShipPtr currPtr = ships;
    while(currPtr != NULL)
    {
        removeShip(currPtr);
        currPtr = ships;
    }
    ships = NULL;

    ShipPtr temp = other.ships;     // create a temp pointer to point to the original list of ships
    ShipPtr newShipPtr = NULL;      // ship pointer for adding ships to new list
    while(temp!= NULL)
    {
        newShipPtr = new ShipNode;                                // allocate space for the new ship
        newShipPtr->component = temp->component;
        if(ships!=NULL)                                           // if this is not the first element of the list...
        {
            AddToBack(ships, newShipPtr);                         // Add this element to the back of the list
        }else
        {
            InitList(ships, newShipPtr);                          // If this is the first element, use this element to initialize the list
        }
        temp = temp->next;
    }
    return *this;
}

void Player::setName()
{
    string myName;
    string message = "How did you mess up your own name?!";
    try{

        cout<<"Player name: ";
        cin>>myName;
        if(!cin)
            throw message;
    }
    catch(string E)
    {
        cout<<E<<endl;
        cout<<"How about we just call you Mud."<<endl;
        myName = "Mud";
    }

    name = myName;
}

int Player::getNumShips() const
{
    return numShips;
}

// Creates the ships for a player
// PRE: ships initialized to NULL, numShips has been set
// POST: ships member value points to a list of ships with the correct number of ships
void Player::createShips()
{
    int counter = 0;
    ShipPtr newShipPtr = NULL;
    while(counter<numShips)                                         // while there is another ship to be created
    {
        newShipPtr = new ShipNode;                                  // allocate space for a new ship
        switch(counter%5)                                           // Cycle through the 5 types of ships, starting with the Carrier, and initialize the new ship
        {
            case 0:
                newShipPtr->component = Ship("Carrier", 5);
                break;
            case 1:
                newShipPtr->component = Ship("Battleship", 4);
                break;
            case 2:
                newShipPtr->component = Ship("Destroyer", 3);
                break;
            case 3:
                newShipPtr->component = Ship("Submarine", 3);
                break;
            case 4:
                newShipPtr->component = Ship("Patrol Boat", 2);
                break;
            default:
                cout<<"Error in createShips"<<endl<<endl;
        }
        if(ships!=NULL)                                           // if this is not the first element of the list...
        {
            AddToBack(ships, newShipPtr);                         // Add this element to the back of the list
        }else
        {
            InitList(ships, newShipPtr);                          // If this is the first element, use this element to initialize the list
        }
        counter++;                                                  // increment number of ships created
    }
}

// Initializes a linked list of ships
// PRE: headptr == NULL, newNodeptr has been initialized
// POST: linked list of one node has been created
void Player::InitList(ShipPtr& headPtr, ShipPtr& newNodePtr)
{
   //cout<<"Initializing list "<<endl<<endl;
    AddToFront(headPtr, newNodePtr);                                        // Add element to the front of the list
    headPtr->next=NULL;                                                     // the next pointer in the list is NULL
}

// Adds a node to the front of the linked list
// PRE: listPtr points to the first node of a linked list, newNodePtr has been initialized
// POST: newNodePtr is now at the front of the list
void Player::AddToFront(ShipPtr& listPtr, ShipPtr& newNodePtr)
{
        newNodePtr->next = listPtr;                             // newNodePtr pointer's next element points to the head of the list
        listPtr= newNodePtr;                                    // make newNodeptr the new head of the list
}

// Adds a node to the back of the linked list
// PRE: headPtr points to the first node of a linked list, newNodeptr has been initialized
// POST: newNodePtr has been added to he back of the linked list
void Player::AddToBack(ShipPtr& headPtr, ShipPtr& newNodePtr)
{
        newNodePtr->next = NULL;                                // set the next element of the newNodePtr to NULL
        ShipPtr currPtr = headPtr;
        while(currPtr->next!=NULL)                              // cycle through the list until we find the end
        {
            currPtr=currPtr->next;
        }
        currPtr->next = newNodePtr;                             // point the next element of the last item at the newNodePtr
}

// Removes Ship from fleet
// PRE: target is set to a ship that has been destroyed
// POST: Ship deleted from linked list.
void Player::removeShip(ShipPtr& target)
{
    ShipPtr currPtr = ships;
    ShipPtr prevPtr = NULL;

    if(target == ships)                   // if the course we are dropping is the head
    {
        ships = ships->next;            // set head pointer to the next pointer
        delete target;                              // delete the course to be dropped
        target = NULL;
        //cout<<"1st Ship Removed"<<endl<<endl;
    }
    else
    {
        while(currPtr!=NULL)                                // exit loop if we reach the end
        {
            if(target == currPtr)                   // Once the current pointer is pointing to the ship to be deleted...
            {
                prevPtr->next = target->next;       // previous pointer skips over the target ship, to the next proceeding in the list
                delete target;                      // delete the dead ship
                target = NULL;
                //cout<<"Ship Removed"<<endl<<endl;
                break;
            }
            prevPtr = currPtr;
            currPtr = currPtr->next;
        }
    }
}

// Prints the list of ships to the screen for debugging purposes
// PRE: listPtr points to the first node of a linked list of ships
// POST: the complete list of ships has been displayed to the screen
void Player::printList() const
{
    ShipPtr currPtr = ships;                              // start currPtr at the head...
    int i = 1;
    cout<<endl;
    cout<<endl<<"Printing "<<name<<"'s ships."<<endl<<endl;
    while(currPtr!=NULL)                                    // until we reach the end of the list...
    {
        cout<<"#"<<setw(2)<<i<<": ";
        currPtr->component.print();
        cout<<endl;
        currPtr=currPtr->next;                                // advance to the next ship
        i++;

    }
    cout<<endl;
}

void Player::displayBoard(bool showShips) const
{
    cout<<name<<"'s board"<<endl;
    board.print(showShips);
}

string Player::getName() const
{
    return name;
}

// returns a random coordinate, with the limits being set to parameter on X and Y
Coordinate Player::getRandCoordinate(int maxSize) const
{
    Coordinate myCoord;

    myCoord.xCoord = rand()%maxSize;               // generate a random number between 0 and maxSize....
    myCoord.yCoord = rand()%maxSize;
    return myCoord;
}

// Sets all the ships on the board in random locations
// PRE: board has been initialized, board size is accurate,
//      headPtr points to a linked list containing ships to be placed on board
//      the number of ships will fit on the board
// POST: ships have been placed on the board
void Player::setShips()
{
    bool shipPlaced = false;
    ShipPtr currPtr = ships;
    Ship::Orientation myOrn;
    int orn;                                                // controls orientation of the ship
    char choice;
    Coordinate myCoord;
    bool userSetShips = false;

    if(playerType == human)     // if it's a human player...
    {
        cout<<"Would you like to set your own ships (Y or N): ";
        cin>>choice;
        choice = toupper(choice);
        if(choice == 'Y')
            userSetShips = true;
    }

    while(currPtr!=NULL)                                    // Go through all of the ships in the list...
    {
        shipPlaced = false;                                 // Set ship placed to false
        while(!shipPlaced)
        {
            if(userSetShips)        // if user places own ships...
            {
                displayBoard(true);     // show the board with the ships
                try
                {
                    cout<<"Pick a starting location for your "<<currPtr->component.getName()<<endl;
                    myCoord = getUserCoord( board.getSize() );      // get a coordinate from the user
                    cout<<"Horizontal or Vertical? (H or V): "<<endl;
                    cin>>choice;
                    if(!cin)
                        throw choice;   // if the user screw up....
                }
                catch(int x)                // pick one for them.
                {
                    cout<<"Not sure what you meant... how about I surprise you."<<endl;
                    orn = rand()%2;
                    if(orn == 0)
                    {
                        cout<<"Vertical it is!"<<endl;
                    }else
                    {
                        cout<<"Horizontal it is!"<<endl;
                    }// orn 0 = vertical, 1 = horizontal

                }
                                                                                   // Prompt user for a orientation
                if(toupper(choice)=='H')
                    orn = 1;                                                                                // 1 = horizontal
                else
                    orn = 0;
            }
            else
            {
                myCoord = getRandCoordinate( board.getSize() );            // generate a random coordinate to attempt to place the ship
                orn = rand()%2;
            }


            if(orn == 0)
            {
                myOrn = Ship::vertical;
            }else
            {
                    myOrn = Ship::horizontal;
            }// orn 0 = vertical, 1 = horizontal
            shipPlaced = board.shipFit(currPtr->component,myCoord, myOrn);      // attempt to place the ship on the board in given location

            if(shipPlaced)                                                                  // if the ship was placed draw the new board to the screen
            {
                currPtr->component.setPosition(myCoord,myOrn);
                board.placeShip(currPtr->component);
                //drawBoard(board, boardSize);
            }
            else if(userSetShips)
            {
                cout<<endl<<"Your "<<currPtr->component.getName()<<" will not fit in this location."<<endl;
                cout<<"Please try again."<<endl;
            }
        }                                                                                   // if ship not placed try again until we get it right
        currPtr= currPtr->next;                                                             // move to the next ship
    }
}

// Prompts user for a coordinate
// PRE: boardSize is accurate to the board the coordinate will be used for
// POST: returned coordinate fits on the board
Coordinate Player::getUserCoord(int maxSize) const
{
    bool goodCoord;                                 // If the coord will work or not with the specified board
    char x;                                         // using x as a character for ease of readability and use for the user
    int y;                                          // y coordinate
    Coordinate myCoord;                             // stores the coordinate
    string message1 = "What the hell Capt?!  That's not a coordinate!";

    // loop for getting an attack coordinate
    do{
        try
        {
            goodCoord = true;                                                       // coordinate starts off good
            cout<<"Enter a coordinate. "<<endl;
            cout<<"Letter: ";
            cin>>x;
            cout<<"Number: ";                                                       // Prompt user for a coordinate
            cin>>y;

            // throw exception on invalid input
            if(!cin)
                throw message1;

            if(x>='a'&&x<='z')                                                      // If the user inputs a lowercase character, make it capital
            x = toupper(x);

            if(y < 1 || y > maxSize)                                              // If the coordinate falls out of range
            {                                                                       // Inform the user of which axis is out of range...
                goodCoord = false;
                cout<<"Y Coordinate out of range.  Please try again."<<endl<<endl;
            }
            if(x < 'A' || x >= 'A'+maxSize)
            {
                goodCoord = false;
                cout<<"X Coordinate out of range.  Please try again."<<endl<<endl;
            }
        }
        catch(string message)// catch exception
        {
            cout<<message<<endl;
            cin.clear();
            cin.ignore(500,'\n');   // fix error, notify user
            goodCoord = false;

        }


    }while(!goodCoord);                                                         // Continue to get coordinate from user until we have a good one
    myCoord.xCoord = x-'A';                                                      // convert user input to corresponding board position
    myCoord.yCoord = y-1;
    cout<<endl<<"("<<myCoord.xCoord<<":"<<myCoord.yCoord<<")"<<endl<<endl;
    //cin>>x;
    return myCoord;
}

// Returns the ship that was hit
ShipPtr Player::getTargetedShip(Coordinate myCoord) const
{
    ShipPtr currPtr = ships;
    while(currPtr!=NULL)                                                                            // Go through all the ships
    {
        if(currPtr->component.getPosition().xCoord == myCoord.xCoord )                                     // If the x coordinate of the ships position
        {                                                                                           // matches the xCoordinate of myCoord...
            if(currPtr->component.getOrientation() == Ship::vertical)                                          // And the ship is positioned vertically...
            {
                if(myCoord.yCoord>=currPtr->component.getPosition().yCoord &&                              // And if the Y coordinate falls between
                   myCoord.yCoord<=currPtr->component.getPosition().yCoord+currPtr->component.getSize() )       // the Y coordinates for the ship...
                   {
                       return currPtr;                                                                          // check to see if the ship was destroyed
                   }                                                                                            // return the targeted ship
            }
        }
        if(currPtr->component.getPosition().yCoord == myCoord.yCoord)                                      // If the y coordinate of the ships position
        {                                                                                           // matches the yCoordinate of myCoord...
            if(currPtr->component.getOrientation() == Ship::horizontal)                                        // And the ship is positioned horizontally...
            {
                if(myCoord.xCoord>=currPtr->component.getPosition().xCoord &&                              // And if the X coordinate falls between
                    myCoord.xCoord<=currPtr->component.getPosition().xCoord+currPtr->component.getSize() )      // the X coordinate for the ship....
                    {
                        return currPtr;                                                                         // check to see if the ship was destroyed
                    }                                                                                           // return the targeted ship
            }
        }
        currPtr = currPtr->next;                                                                    // advance to the next ship
    }
    cout<<endl<<"ERROR ERROR"<<endl;                            // we should never reach this state.
    return NULL;                                                // because we check that a ship was actually hit prior to calling this function

}

// Handles attacking another player. Retrieves attack Coordinate
    // and updates board and ship if one is hit
void Player::launchAttack(Player& enemy)
{
    Coordinate myCoord;
    char attackChar;
    string prompt;
    ShipPtr target = NULL;

    string buffer;

    // Loop controls getting a valid attack coordinate
    do{
        if(playerType == human) // Prompts human players for attack coordinate
        {
            enemy.displayBoard();
            cout<<"Ready to launch the next attack!"<<endl;
            myCoord = getUserCoord(enemy.board.getSize());
        }
        else        // computer generates an attack coordinate
        {
            if(targetingSystem.getTargetAquired())  // If the computer has 'found' a ship to attack
                try{
                    myCoord = targetingSystem.retrieveFireCoord();      // try to use the targeting system
                }
                catch(int attempts)                                     // if system fails, log error and go back to random
                {
                    LostTarget E = LostTarget(targetingSystem);
                    cout<<"Funny... I just lost track of your ship."<<endl;
                    E.what();
                    myCoord = getRandCoordinate(enemy.board.getSize());
                }
            else
                myCoord = getRandCoordinate(enemy.board.getSize());     // cpu generates random coordinate

        }

        attackChar = enemy.board.incomingAttack(myCoord);               // fetch result of attack

        if(playerType == cpu && targetingSystem.getTargetAquired() )    // if the cpu is using the targetSystem...
            if(attackChar == Board::ERR_CHAR )                              // and the attack is not valid
            {
                try{
                    targetingSystem.reportStatus(false);                    // notify the system, and try adjusting aim
                }
                catch(int attempts)                                         // on fail to find a valid point, log error and get random coordinate
                {
                    LostTarget E = LostTarget(targetingSystem);
                    cout<<"Funny... I just lost track of your ship."<<endl;
                    E.what();
                    myCoord = getRandCoordinate(enemy.board.getSize());
                }
            }


    }while(attackChar == Board::ERR_CHAR);                              // exit loop once we have a good character

    enemy.board.updateBoard(attackChar,myCoord);                        // update the board
    enemy.displayBoard();                                               // display the board...

    if(attackChar == Board::HIT)                                // if a ship was hit...
    {

        target = enemy.getTargetedShip(myCoord);            // locate the ship that was hit
        target->component.onHit(myCoord);                   // update the ship

        if(playerType == cpu)                                   // if player is cpu...
        {

            if(targetingSystem.getTargetAquired()== false)          // and the cpu wasn't already using the targeting system
            {
                targetingSystem.setMaxSize(enemy.board.getSize());      // set the size, and initialize the target system
                targetingSystem.setNewTarget(myCoord);
            }
            else
                targetingSystem.reportStatus(true);                 // if cpu is already using the system, notify system of hit

            // cpu smack talk, later to be retrieved from file
            cout<<"Gotcha!  Won't be long now..."<<endl;
            cout<<"(input a string to continue)"<<endl;
            cin>>prompt;
        }

        if( target->component.getAlive() == false )         // if the ship that was hit was destroyed
        {
            if(enemy.getType() == human){   // if the target is human, notify user
                cout<<"Your "<<target->component.getName()<<" was destroyed."<<endl;
                cout<<"(input a string to continue)"<<endl;
                cin>>prompt;
                targetingSystem.shipDestroyed(target->component);   // tell targeting system what ship was destroyed
            }
            else        // if enemy is human, smack talk...
            {
                cout<<"You sunk my "<<target->component.getName()<<"!"<<endl;
                cout<<"(input a string to continue)"<<endl;
                cin>>prompt;
            }
            enemy.removeShip(target);       // remove the destroyed ship from the list
            enemy.setLoss();                // check if the game is over
        }
    }
    else        // On miss...
    {
        cout<<"It's a miss... "<<endl;
        cin>>prompt;
        if(playerType == cpu && targetingSystem.getTargetAquired()) // update target system with the miss
            targetingSystem.reportStatus(false);

    }

}

void Player::setLoss()
{
    if(ships == NULL)
        gameLoss = true;
}

bool Player::getGameOver() const
{
    return gameLoss;
}

PlayerType Player::getType() const
{
    return playerType;
}
