//*****************************************************
//  Charles Darnell Johnson 5100474
//  12/13/2015
//  Battleship Game
//  This game allows the user to play (currently) 2 different
//  versions of the classic Battleship game.
//  Version 1 - Single player see how many attacks it takes to
//  destroy all cpu ships.
//  Version 2 - Play against a CPU opponent
//  In both version the user may select the total number of ships (stored in a linked list)
//  as well as the size of the playing board for the game. (dynamic 2d array of characters)
//*****************************************************

#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <limits>
#include "battleship.h"



int main()
{

    srand(time(NULL));

    int option;
    Difficulty cpuDiff;

    /** Main menu loop layout and switch statement shamelessly borrowed from Professor Scott Davis  **/

    do
    {
        cout << "*** BATTLESHIP ***"<< endl;
        cout << "Select an option:" << endl
             << "  1) Single Player Standard Mode" << endl
             << "  2) Player vs CPU (easy)" << endl
             << "  3) Player vs CPU (normal)" << endl
             << "  4) Player vs CPU (hard)" << endl
             //<< "  5) Add a class" << endl
            // << "  6) Remove a class" << endl
             << "  5) Exit" << endl;
        cin >> option;

        if (!cin){
            cin.clear();
        }

        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << endl;

        switch (option)
        {
        case 1:
            GameLoop1();
            break;
        case 2:
            cpuDiff = easy;
            GameLoop2(easy);            // cpu attacks once per turn
            break;
        case 3:
            cpuDiff = normal;
            GameLoop2(normal);          // cpu attacks twice per turn
            break;
        case 4:
            cpuDiff = hard;
            GameLoop2(hard);            // cpu attacks thre times per turn!
            break;
        case 5:
            cout << "Thanks for playing." << endl;
            break;
        default:
            cout << "Invalid option entered" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

    } while (option != 5);



return 0;
}

// single player game loop
void GameLoop1()
{
    int attackCounter = 0;                      // Keep track of total number of attacks
    int boardSize;                              // Size of the playing board that will hold the ships
    int numShips;                               // Total number of ships to be created for each fleet
    char** board;                               // 2D array for the playing board
    char oceanTile;                             // Character used to know what's in a particular space on the board
    //const char SHIPPART = '#';
    bool gameover = false;                      // Keeps track of the state of the game

    ShipPtr headPtr=NULL;                       // Contains the first node of the linked list of ships
//    ShipPtr tailPtr=NULL;                       // contains the last node of the linked list of ships
//    ShipPtr newShipPtr=NULL;
    ShipPtr target=NULL;                        // Ship that is the target of an attack

    Coordinate myCoord;                         // Keep track of attack coordinate

    cout<<"Board Size: ";
    cin>>boardSize;

    if(boardSize<5)                             // If the board size is less than 5
        boardSize = 5;                          // Set the board size to 5
    else if(boardSize>15)
        boardSize = 15;

    cout<<"How many ships: ";
    cin>>numShips;

//    if(numShips<1)                              // If the number of ships are less than 1...
//        numShips = 1;                           // Set the number of ships to 1
//    else if(numShips>15)                        // If the number of ships are greater than 15...
//        numShips = 15;                          // Set the total number of ships to 15

    if(numShips < 1)                        // If less than 1 ship, set amount to 1
    {
        numShips = 1;
    }
    else if(numShips > boardSize)           // If amount of ships is more than the board size, set amount of ships equal to board size
    {
        numShips = boardSize;
    }

    //numShips = setAmountShips(boardSize, numShips);     // Make sure all ships will fit on board

    board = initBoard(board, boardSize);        // Initialize the board
    //drawBoard(board, boardSize);

    createShips(headPtr, numShips);    // Create the linked list of ships
 //   PrintList(headPtr);

    setShips(board,headPtr, boardSize);         // Sets the ships on the board

    drawBoard(board, boardSize, true);                // Draw the board to the screen
    //PrintList( headPtr);
    do{
        attackCounter++;
        gameover = userTurn(board,boardSize,headPtr);           // Users turn
    }while(!gameover);                                                                          // Loop until game over (all ships destroyed)

    delete board;

    cout<<"You win!"<<endl;
    cout<<"It took you "<<attackCounter<<" turns to sink all of my ships"<<endl;

}

void GameLoop2(Difficulty cpuDiff)
{
    int attackCounter = 0;                      // Keep track of total number of attacks
    int turnCounter = 0;
    int boardSize;                              // Size of the playing board that will hold the ships
    int numShips;                               // Total number of ships to be created for each fleet
    char** board;                               // 2D array for the playing board
    char oceanTile;                             // Character used to know what's in a particular space on the board
    //const char SHIPPART = '#';
    bool gameover = false;                      // Keeps track of the state of the game

    ShipPtr headPtr=NULL;                       // Contains the first node of the linked list of ships
//    ShipPtr tailPtr=NULL;                       // contains the last node of the linked list of ships
//    ShipPtr newShipPtr=NULL;
    ShipPtr target=NULL;                        // Ship that is the target of an attack

    Coordinate myCoord;                         // Keep track of attack coordinate
    char buffer;                                // input to pause screen

    cout<<"Board Size: ";
    cin>>boardSize;

    if(boardSize<5)                             // If the board size is less than 5
        boardSize = 5;                          // Set the board size to 5

    cout<<"How many ships: ";
    cin>>numShips;

    //numShips = setAmountShips(boardSize, numShips);     // Make sure all ships will fit on board
    if(numShips < 1)                        // If less than 1 ship, set amount to 1
    {
        numShips = 1;
    }
    else if(numShips > boardSize)           // If amount of ships is more than the board size, set amount of ships equal to board size
    {
        numShips = boardSize;
    }

    Player players[2];                              // Array of players
    players[0] = initUser(boardSize, numShips);
    players[1] = initCPU(boardSize, numShips);
    //PrintList( headPtr);
    do{
        turnCounter++;
        if(turnCounter%2==1)                                 // If it's the players turn...
        {
            attackCounter++;
            gameover = userTurn(players[1].board, boardSize, players[1].ships); // user's turn
        }
        else
        {
            gameover = cpuTurnV1(players[0].board, boardSize, players[0].ships, int(cpuDiff)+1);  // computer's turn
            cout<<"Enter any character to continue: ";
            cin>>buffer;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout<<endl;
        }


    }while(!gameover);                                                                          // Loop until game over (all ships destroyed)

    if(turnCounter%2==1){                                                                       // If game ended on user's turn...
        cout<<"You win!"<<endl;
        cout<<"It took you "<<attackCounter<<" turns to sink all of my ships"<<endl;
    }
    else{                                                                                       // If game ended on computer's turn...
        cout<<"You lose.  Deal with it."<<endl;
    }

    delete players[0].board;
    delete players[1].board;

}



// Manages the computer's turn against, CPU attacks and returns true if this attack destroyed the final ship
// V2 will use a targeting system to continuously search for and attack the same ship once one has been found
// PRE: board and ships are initialized, ships are placed on the board, headPtr points to the ships list to be attacked
// POST: board updated with attack information (hit or miss), on hit attacked shipped is updated.  Return true on game over
bool cpuTurnV2(char** board, int boardSize, ShipPtr headPtr)
/*Not Yet Functional*/
{
    bool gameover = false;
    Coordinate myCoord;                                 // Keeps track of attack coordinate
    char oceanTile;                                     // Keeps track of what character is in a particular space on the board
    ShipPtr target=NULL;                                // Keeps track of attacked ship

    static Coordinate initialHit;
    static bool lastShotHit = false;
    static bool targetAqciured = false;
    static bool targetDestroyed = false;
    do
    {
        if(lastShotHit || targetAqciured)
        {
               // myCoord = targetingSystem(boardSize, initialHit, lastShotHit);
        }
        else{
                myCoord = randCoordinate(boardSize);                                                // Get a random attack coordinate from the cpu
        }

        oceanTile = launchAttack(myCoord,board);                                            // checks what character is at that coordinate on the board
        //if(oceanTile=='E')
            //cout<<"We've already attacked there.  Choose another location."<<endl<<endl;
    }while(oceanTile=='E');                                                                 // If the coordinate == 'E', Repeat
    updateBoard(oceanTile,myCoord, board);                                                  // Update the board with the new attack

    drawBoard(board,boardSize, true);                                                             // Draw the updated board to display device
    cout<<"     ***** Your Board & Ships ******"<<endl;
    if ( oceanTile == 'H' )                                                                 // If the oceanTile is a hit...
    {
        cout<<"You can't hide from me!"<<endl<<endl;
        target = updateShips(myCoord, headPtr);                                             // Find which ship was hit, update it's hit box, and store the ship into target
        if(target->component.alive == false)                                                // If the target was destroyed...
        {
            targetAqciured = false;                                                         // a new target needs to be found
            cout<<"I sunk your "<<target->component.name<<"! Haha"<<endl<<endl;
            removeShip(target, headPtr);                                           // Remove the target from the linked list
            gameover = gameOver(headPtr);                                                   // Check if all ships have been destroyed
        }
    }
    else                                                                                    // Attack Coordinate did not hit a ship
    {
        lastShotHit = false;
        cout<<"You can live, for now."<<endl;
    }
    return gameover;
}

// Manages the computer's turn against, CPU attacks and returns true if this attack destroyed the final ship
// V1 attacks random spaces on the map
// PRE: board and ships are initialized, ships are placed on the board, headPtr points to the ships list to be attacked
// POSt: board updated with attack information (hit or miss), on hit attacked shipped is updated.  Return true on game over
bool cpuTurnV1(char** board, int boardSize, ShipPtr headPtr, int attacksPerTurn)
{
    bool gameover = false;
    Coordinate myCoord;                                 // Keeps track of attack coordinate
    char oceanTile;                                     // Keeps track of what character is in a particular space on the board
    ShipPtr target=NULL;                                // Keeps track of attacked ship
    char myChar;
    int attackCounter = 0;
    do
    {
        attackCounter++;
        do
        {
            myCoord = randCoordinate(boardSize);                                                // Get an attack coordinate from the cpu
            oceanTile = launchAttack(myCoord,board);                                            // checks what character is at that coordinate on the board
            //if(oceanTile=='E')
            //cout<<"We've already attacked there.  Choose another location."<<endl<<endl;
        }while(oceanTile=='E');                                                                 // If the coordinate == 'E', Repeat
        updateBoard(oceanTile,myCoord, board);                                                  // Update the board with the new attack
        drawBoard(board,boardSize, true);                                                             // Draw the updated board to display device
        cout<<"     ***** Your Board & Ships ******"<<endl;
        if ( oceanTile == 'H' )                                                                 // If the oceanTile is a hit...
        {
            cout<<"You can't hide from me!"<<endl<<endl;
            target = updateShips(myCoord, headPtr);                                             // Find which ship was hit, update it's hit box, and store the ship into target
            if(target->component.alive == false)                                                // If the target was destroyed...
            {
                cout<<"I sunk your "<<target->component.name<<"! Haha"<<endl<<endl;
                removeShip(target, headPtr);                                           // Remove the target from the linked list
                gameover = gameOver(headPtr);                                                   // Check if all ships have been destroyed
            }
        }
        else                                                                                    // Attack Coordinate did not hit a ship
        {
            cout<<"You can live, for now."<<endl;
        }
    }while(attackCounter<attacksPerTurn);
    return gameover;
}


// Manages the user's turn, prompts user for an attack and returns true if this attack destroyed the final ship
// PRE: board and ships are initialized, ships are placed on the board, headPtr points to the ships list to be attacked
// POSt: board updated with attack information (hit or miss), on hit attacked shipped is updated.  Return true on game over
bool userTurn(char** board, int boardSize, ShipPtr headPtr)
{
    bool gameover = false;
    Coordinate myCoord;
    char oceanTile;
    ShipPtr target=NULL;
    do
    {
        drawBoard(board,boardSize, false);
        cout<<"     ***** CPU Board & Ships ******"<<endl<<endl;
        cout<<"Ready to launch another attack!"<<endl;
        myCoord = getUserCoord(boardSize);                                                  // Get an attack coordinate from the user
        oceanTile = launchAttack(myCoord,board);                                            // checks what character is at that coordinate on the board
        if(oceanTile=='E')
            cout<<"We've already attacked there.  Choose another location."<<endl<<endl;
    }while(oceanTile=='E');                                                                 // If the coordinate == 'E', Repeat
    updateBoard(oceanTile,myCoord, board);                                                  // Update the board with the new attack
    drawBoard(board,boardSize, false);                                                             // Draw the updated board to display device
    cout<<"     ***** CPU Board & Ships ******"<<endl;
    if ( oceanTile == 'H' )                                                                 // If the oceanTile is a hit...
    {
        cout<<"It's a direct hit!!!"<<endl<<endl;
        target = updateShips(myCoord, headPtr);                                             // Find which ship was hit, update it's hit box, and store the ship into target
        if(target->component.alive == false)                                                // If the target was destroyed...
        {
            cout<<"You sunk my "<<target->component.name<<"! Grr..."<<endl<<endl;
            removeShip(target, headPtr);                                           // Remove the target from the linked list
            gameover = gameOver(headPtr);                                                   // Check if all ships have been destroyed
        }
    }
    else                                                                                    // Attack Coordinate did not hit a ship
    {
        cout<<"It's a miss, Captain..."<<endl;
    }
    return gameover;
}

// Insures the amount of ships fits on the board size selected
// PRE: amtShips and boardSize have been set
// POST: return amount of ships
int setAmountShips(int boardSize, int amtShips)
{
    if(amtShips < 1)                        // If less than 1 ship, set amount to 1
    {
        amtShips = 1;
    }
    else if(amtShips > boardSize)           // If amount of ships is more than the board size, set amount of ships equal to board size
    {
        amtShips = boardSize;
    }
    return amtShips;
}

// Initialize a computer player
// PRE: boardSize and numShips have been set.  There is enough space on the board for all ships
// POST: computer player has been initialized with all ships placed on the computer players board
Player initCPU(int boardSize, int numShips)
{
    Player myPlayer;                                        // new player...
    myPlayer.name = "CPUv1";                                // Version of AI cpu is using
    myPlayer.playerType = cpu;                              // type of player (human or cpu)
    myPlayer.ships = NULL;                                  // Init ships to NULL
    myPlayer.board = initBoard(myPlayer.board, boardSize);  // Create the board for the player
    createShips(myPlayer.ships, numShips);                  // create the ships for the player
    setShips(myPlayer.board, myPlayer.ships, boardSize);    // set the ships on the players board
    return myPlayer;                                        // return player
}

// Initialize a human player
// PRE: boardSize and numShips have been set.  There is enough space on the board for all ships
// POST: a human player has been initialized with all ships placed on the players board
Player initUser(int boardSize, int numShips)
{
    Player myPlayer;
    cout<<"Enter your name:";                               // prompts for user name
    cin>>myPlayer.name;
    myPlayer.playerType = human;                            // set player to human
    myPlayer.ships = NULL;                                  // init ships to NULL
    myPlayer.board = initBoard(myPlayer.board, boardSize);  // create the board for the player
    createShips(myPlayer.ships, numShips);                  // create the ships for the player
    setUserShips(myPlayer.board, myPlayer.ships, boardSize);    // sets user's ships on their board
    return myPlayer;                                            // return player
}

// Set's user's ships on the their board.  Gives option to have ships position manually inputted or randomly generated
// PRE: board has been initialized, board size correct, headPtr points to a linked list of user ships.  Ships will fit on board of this size
// POST: all ships have been placed on the board
void setUserShips(char **board, ShipPtr headPtr, int boardSize)
{
    ShipPtr currPtr = headPtr;                                              // used to loop iterate through the list
    char choice;
    bool shipPlaced;
    int orn;                                                                // keeps track of orientation for ship being placed
    Coordinate myCoord;                                                     // keeps track of coordinate for placing ship on the board
    cout<<"Would you like to place your own ships on the board?"<<endl;
    cout<<"Enter Y for yes or N for no: ";
    cin>>choice;
    if(toupper(choice)== 'N')                                               // If the user explicitly says they don't want to place their own ships
        setShips(board, headPtr, boardSize);                                // randomly place ships on the board
    else                                                                    // else, default to user selected positions for ships
    {
        while(currPtr!=NULL)                                                // For all ships in the list...
        {
            shipPlaced = false;                                             // This ship has not been placed
            while(!shipPlaced)                                              // Until this ship has been placed...
            {
                drawBoard(board,boardSize, true);                                                                 // Show the user the current board
                cout<<"Please select a starting position for your "<<currPtr->component.name<<"."<<endl;
                cout<<"This ship has a size of "<<currPtr->component.size<<endl;
                myCoord = getUserCoord(boardSize);                                                          // Prompt user for a starting position for ship
                cout<<"Will this ship be placed Horizontal or Vertical?"<<endl;
                cout<<"Enter H or V: ";
                cin>>choice;                                                                                // Prompt user for a orientation
                if(toupper(choice)=='H')
                    orn = 1;                                                                                // 1 = horizontal
                else
                    orn = 0;                                                                                // 0 = vertical
                shipPlaced = placeShip(currPtr->component,board, boardSize, myCoord, orn);                  // attempt to place ship on board in given position
                drawBoard(board,boardSize, true);                                                                 // draw the board to screen
                if(!shipPlaced)                                                                             // If placement fails, inform user
                {
                    cout<<endl<<"Your "<<currPtr->component.name<<" will not fit in this location."<<endl;
                    cout<<"Please try again."<<endl;
                }

            }
            currPtr = currPtr->next;                                                                        // advance to next ship
        }
    }
}

// Prompts user for a coordinate
// PRE: boardSize is accurate to the board the coordinate will be used for
// POST: returned coordinate fits on the board
Coordinate getUserCoord(int boardSize)
{
    bool goodCoord;                                 // If the coord will work or not with the specified board
    char x;                                         // using x as a character for ease of readability and use for the user
    int y;                                          // y coordinate
    Coordinate myCoord;                             // stores the coordinate

    do{
        goodCoord = true;                                                       // coordinate starts off good
        cout<<"Enter a coordinate. "<<endl;
        cout<<"Letter: ";
        cin>>x;
        cout<<"Number: ";                                                       // Prompt user for a coordinate
        cin>>y;
        if(x>='a'&&x<='z')                                                      // If the user inputs a lowercase character, make it capital
            x = toupper(x);
        if(y < 1 || y > boardSize)                                              // If the coordinate falls out of range
        {                                                                       // Inform the user of which axis is out of range...
            goodCoord = false;
            cout<<"Y Coordinate out of range.  Please try again."<<endl<<endl;
        }
        if(x < 'A' || x >= 'A'+boardSize)
        {
            goodCoord = false;
            cout<<"X Coordinate out of range.  Please try again."<<endl<<endl;
        }
    }while(!goodCoord);                                                         // Continue to get coordinate from user until we have a good one
    myCoord.xCord = x-'A';                                                      // convert user input to corresponding board position
    myCoord.yCord = y-1;
    cout<<endl<<"("<<myCoord.xCord<<":"<<myCoord.yCord<<")"<<endl<<endl;
    //cin>>x;
    return myCoord;
}

// Returns what character is in particular position on the given board
// PRE: board has been initialized, myCord is within the range of the board
// POST: character at position myCord returned.
char checkSpace(char **board,Coordinate myCord)
{
    return board[myCord.yCord][myCord.xCord];
}

// Updates given board with character value oceanTile
// PRE: board has been initialized, oceanTile has been set
// POST: Board updated
void updateBoard(char oceanTile,Coordinate myCord,char **board)
{
    board[myCord.yCord][myCord.xCord] = oceanTile;
}

// Takes coordinate and checks whether the attack was a hit or a  miss
// PRE: board has been initialized, myCoord is in range of board
// POST: M returned on miss, H returned on hit, E returned otherwise (space already attacked - not valid)
char launchAttack(Coordinate myCoord, char **board)
{
    char attackResult;
    char tile = board[myCoord.yCord][myCoord.xCord];        // get character at position on board
    switch (tile)                                           // check what's in the tile and return a value accordingly
            {
                case '~':
                    attackResult = 'M';             // ~ Ocean is miss, return M
                    break;
                case '#':
                    attackResult = 'H';             // # is a hit, return H
                    break;
                default:
                    attackResult = 'E';
            }
        return attackResult;
}

// Find ship that was hit, update it's hitbox
// PRE: myCoord contains position of a ship that has been hit, headPtr points to linked list of ships
// POST: targeted ship has been updated, hitbox set to false at myCoord position
ShipPtr updateShips(Coordinate myCoord, ShipPtr headPtr)
{
    ShipPtr currPtr = headPtr;
    while(currPtr!=NULL)                                                                            // Go through all the ships
    {
        if(currPtr->component.position.xCord == myCoord.xCord )                                     // If the x coordinate of the ships position
        {                                                                                           // matches the xCoordinate of myCoord...
            if(currPtr->component.orientation == vertical)                                          // And the ship is positioned vertically...
            {
                if(myCoord.yCord>=currPtr->component.position.yCord &&                              // And if the Y coordinate falls between
                   myCoord.yCord<=currPtr->component.position.yCord+currPtr->component.size )       // the Y coordinates for the ship...
                   {
                       currPtr->component.hitbox[myCoord.yCord - currPtr->component.position.yCord] = false;    // Then currPtr is at the ship that was hit
                       currPtr->component.alive = Alive(currPtr->component);                                    // So mark this position on the hitbox to false
                       return currPtr;                                                                          // check to see if the ship was destroyed
                   }                                                                                            // return the targeted ship
            }
        }
        if(currPtr->component.position.yCord == myCoord.yCord)                                      // If the y coordinate of the ships position
        {                                                                                           // matches the yCoordinate of myCoord...
            if(currPtr->component.orientation == horizontal)                                        // And the ship is positioned horizontally...
            {
                if(myCoord.xCord>=currPtr->component.position.xCord &&                              // And if the X coordinate falls between
                    myCoord.xCord<=currPtr->component.position.xCord+currPtr->component.size )      // the X coordinate for the ship....
                    {
                        currPtr->component.hitbox[myCoord.xCord - currPtr->component.position.xCord] = false;   // Then currPtr is at the ship that was hit
                        currPtr->component.alive = Alive(currPtr->component);                                   // So mark this position on the hitbox to false
                        return currPtr;                                                                         // check to see if the ship was destroyed
                    }                                                                                           // return the targeted ship
            }
        }
        currPtr = currPtr->next;                                                                    // advance to the next ship
    }
    return NULL;                                                // because we check that a ship was actually hit prior to calling this function
    cout<<endl<<"ERROR ERROR"<<endl;                            // we should never reach this state.
}

// Checks if ship is still in play
// PRE: Ship has been initialized and the hitbox array is accurate
// POST: returns true if ship is 'alive' and false if 'dead'
bool Alive(Ships myShip)
{
    bool alive = false;                                 // Start off with ship being dead
    for(int i = 0; i<myShip.size; i++)                  // For each space the ship takes up
    {
        if(myShip.hitbox[i]== true)                     // If any of the hitboxes for the ship are alive the ship is alive
            alive = true;
    }
    return alive;                                       // return ship status
}

// Checks to see if the game is over
// PRE: headPtr points to the ships of the player that was just attacked
// POST: returns true if all the ships have been destroyed, else return false
bool gameOver(ShipPtr headPtr)
{
    bool gameover = true;
//    ShipPtr currPtr = headPtr;
//    do
//    {
//        if(currPtr->component.alive==true)
//        {
//            gameover = false;
//            break;
//        }
//        currPtr= currPtr->next;
//    }while(currPtr!=NULL);
    if(headPtr == NULL)     // If the headPtr = NULL then there are no ships in play
        gameover= true;     // Game over
    else
        gameover = false;       // Else, the game continues
    return gameover;
}

// Initializes a players board
// PRE: boardSize contains the size to be used for both rows and columns of the 2x2 board
// POST: 2D array of characters, initialized to '~' turned
char** initBoard(char **board, int boardSize)
{
    board = new char* [boardSize];

    for( int i = 0; i<boardSize; i++)
        board[i] = new char[boardSize];

    for(int i =0; i<boardSize; i++)
    {
        for(int j = 0; j<boardSize; j++)
        {
            board[i][j] = '~';
        }
    }
    return board;
}

// Draws the board to the screen
// PRE: Board has been initialized, boardsize is correct
// POST: board displayed to screen
void drawBoard(char **board, int boardSize, bool viewShips)
{
    char tile = 'A';                    // Used to display characters across the top of board
    cout<<endl<<"    ";
    for(int i =0; i<boardSize; i++)     // Display A through boardsize characters across top of board
    {
        cout<<setw(4)<<tile;
        tile++;
    }
    cout<<endl<<endl;
    for(int i =0; i<boardSize; i++)         // Nested for loop to display board
    {
        cout<<setw(4)<<i+1;                 // Display numbers down the left side of the board
        for(int j = 0; j<boardSize; j++)
        {
            tile = board[i][j];             // Depending on what character in a specific place on the board
            switch (tile)
            {
                case '~':
                    cout<<setw(4)<<"~";
                    break;
                case '#':
                    if(viewShips)
                        cout<<setw(4)<<"#";
                    else
                        cout<<setw(4)<<"~";
                    break;
                case 'H':
                    cout<<setw(4)<<"H";
                    break;
                case 'M':
                    cout<<setw(4)<<".";
                    break;
                default:
                    cout<<setw(4)<<"E";
            }
        }
        cout<<endl<<endl;
    }
}



// Sets all the ships on the board in random locations
// PRE: board has been initialized, board size is accurate,
//      headPtr points to a linked list containing ships to be placed on board
//      the number of ships will fit on the board
// POST: ships have been placed on the board
void setShips(char **board, ShipPtr headPtr, int boardSize)
{
    bool shipPlaced = false;
    ShipPtr currPtr = headPtr;
    int orn;                                                // controls orientation of the ship
    Coordinate myCoord;
    while(currPtr!=NULL)                                    // Go through all of the ships in the list...
    {
        shipPlaced = false;                                 // Set ship placed to false
        while(!shipPlaced)
        {
            myCoord = randCoordinate(boardSize);            // generate a random coordinate to attempt to place the ship
            //cout<<currPtr->component.name<<endl;
            //cout<<"("<<myCoord.xCord<<","<<myCoord.yCord<<")"<<endl;
            orn = rand()%2;                                                                 // orn 0 = vertical, 1 = horizontal
            shipPlaced = placeShip(currPtr->component,board, boardSize, myCoord, orn);      // attempt to place the ship on the board in given location
            if(shipPlaced)                                                                  // if the ship was placed draw the new board to the screen
            {
                //drawBoard(board, boardSize);
            }
        }                                                                                   // if ship not placed try again until we get it right
        currPtr= currPtr->next;                                                             // move to the next ship
    }
}

// Creates the ships for a player
// PRE: headPtr initialized to NULL, numShips has been set
// POST: headPtr points to a list of ships with the correct number of ships
void createShips(ShipPtr& headPtr,  int numShips)
{
    int counter = 0;
    ShipPtr newShipPtr = NULL;
    while(counter<numShips)                                         // while there is another ship to be created
    {
        newShipPtr = new ShipNode;                                  // allocate space for a new ship
        //cout<<"In Create Ships."<<endl<<endl;
       // cout<<"Counter%5 = :"<<counter%5<<endl;
        switch(counter%5)                                           // Cycle through the 5 types of ships, starting with the Carrier, and initialize the new ship
        {
            case 0:
               // cout<<"About to init carrier"<<endl;
                newShipPtr->component = initCarrier();
                break;
            case 1:
                newShipPtr->component = initBattleShip();
                break;
            case 2:
                newShipPtr->component = initDestroyer();
                break;
            case 3:
                newShipPtr->component = initSubmarine();
                break;
            case 4:
                newShipPtr->component = initPatrolBoat();
                break;
            default:
                cout<<"Error in createShips"<<endl<<endl;
        }
        if(headPtr!=NULL)                                           // if this is not the first element of the list...
        {
            AddToBack(headPtr, newShipPtr);                         // Add this element to the back of the list
        }else
        {
            InitList(headPtr, newShipPtr);                          // If this is the first element, use this element to initialize the list
        }
        counter++;                                                  // increment number of ships created
    }
}

// Initializes a Carrier
// PRE:
// POST: returns a Carrier
Ships initCarrier()
{
    Ships myShip;
    myShip.name = "Carrier";
    myShip.size = 5;
    myShip.alive = true;
    myShip.hitbox = new bool[myShip.size];                          // Create a hitbox the size of the ship
    for(int i = 0; i<myShip.size; i++)                              // Turn all spaces in hitbox to true
        myShip.hitbox[i] = true;
    return myShip;
}

// Initializes a Battleship
// PRE:
// POST: returns a Battleship
Ships initBattleShip()
{
    Ships myShip;
    myShip.name = "Battleship";
    myShip.size = 4;
    myShip.alive = true;
    myShip.hitbox = new bool[myShip.size];                              // Create a hitbox the size of the ship
    for(int i = 0; i<myShip.size; i++)                                   // Turn all spaces in hitbox to true
        myShip.hitbox[i] = true;

    return myShip;
}

// Initializes a Destroyer
// PRE:
// POST: returns a Destroyer
Ships initDestroyer()
{
    Ships myShip;
    myShip.name = "Destroyer";
    myShip.size = 3;
    myShip.alive = true;
    myShip.hitbox = new bool[myShip.size];                              // Creates a hitbox the size of the ship
    for(int i = 0; i<myShip.size; i++)
        myShip.hitbox[i] = true;                                        // Turn all spaces in hitbox to true
    return myShip;
}

// Initializes a Submarine
// PRE:
// POST: returns a Submarine
Ships initSubmarine()
{
    Ships myShip;
    myShip.name = "Submarine";
    myShip.size = 3;
    myShip.alive = true;
    myShip.hitbox = new bool[myShip.size];                              // Creates a hitbox the size of the ship
    for(int i = 0; i<myShip.size; i++)
        myShip.hitbox[i] = true;                                        // Turn all spaces in hitbox to true
    return myShip;
}

// Initializes a Patrol Boat
// PRE:
// POST: returns a Patrol Boat
Ships initPatrolBoat()
{
    Ships myShip;
    myShip.name = "Patrol Boat";
    myShip.size = 2;
    myShip.alive = true;
    myShip.hitbox = new bool[myShip.size];                                  // Creates a hitbox the size of the ship
    for(int i = 0; i<myShip.size; i++)
        myShip.hitbox[i] = true;                                             // Turn all spaces in hitbox to true
    return myShip;
}

// Generates a random coordinate
// PRE: boardsize is accurate
// POST: random coordinate that fits on the board is returned
Coordinate randCoordinate(int boardSize)
{
    Coordinate myCoord;
    myCoord.xCord = rand()%boardSize;               // generate a random number between 0 and boardSize....
    myCoord.yCord = rand()%boardSize;
    return myCoord;
}

// Attempts to place a ship at given location on the board
// PRE: board and ship have been initialized, boardsize is correct, orn == 0 for vertical or 1 for horizontal
//      coordinate is within the boards range
// POST: if ship fits on the board at location, it was placed there
//          else, return false
bool placeShip(Ships & myShip, char **&board, int boardSize, Coordinate myCoord, int orn)
{
    bool fit = false;
    if(orn == 0){                                   // orn = 0, make orientation vertical
        myShip.orientation = vertical;
    }
    else                                            // else, orientation is horizontal
    {
        myShip.orientation = horizontal;
    }
    if(myShip.orientation == vertical)                                      // If the ship is vertical...
    {
        if(myCoord.yCord+myShip.size <= boardSize)                          // And if the Y coordinates for the ship don't go out of bounds of the board
        {
            fit = true;                                                     // Then the ship fits
            for(int i = myCoord.yCord; i<myCoord.yCord+myShip.size;i++)     // For every position the ship would occupy
            {
                if(board[i][myCoord.xCord]!='~')                            // If something is already in that space...
                {
                    fit = false;                                            // The ship does not fit in this location
                    break;                                                  // break out of the loop - there is no need to check the remaining spaces if ship does not fit
                }
            }
        }
    }
    else if(myShip.orientation == horizontal)                               // If the ship is horizontal...
    {
        if(myCoord.xCord+myShip.size <= boardSize)                          // And if the X coordinates for the ship don't go out of bounds of the board
        {
            fit = true;                                                     // Then the ship fits
            for(int i = myCoord.xCord; i<myCoord.xCord+myShip.size; i++)    // For every position the ship would occupy
            {
                if(board[myCoord.yCord][i]!='~')                            // If something is already in that space...
                {
                    fit = false;                                            // The ship does not fit in this location
                    break;                                                  // break out of the loop - there is no need to check the remaining spaces if ship does not fit
                }
            }
        }
    }
    if(fit)                                                                 // If the ship fits
    {
        myShip.position = myCoord;                                          // set the position of the ship equal to the coordinate
        if(myShip.orientation==vertical)                                    // if vertical...
        {
            for(int i = myCoord.yCord; i<myCoord.yCord+myShip.size; i++)    // go through each space Y axis starting at the position - through the size
            {
                board[i][myCoord.xCord] = '#';                              // and place the ship on the board
            }
        }
        else if(myShip.orientation==horizontal)                             // if horizontal...
        {
            for(int i = myCoord.xCord; i<myCoord.xCord+myShip.size ; i++)   // go through each space X axis starting at the position - through the size
            {
                board[myCoord.yCord][i] = '#';                              // and place the ship on the board
            }
        }

    }else                                                                   // else, the ship did not fit
    {
        //cout<<"Does not fit"<<endl;                                       // nothing to do
    }
    return fit;
}

// Initializes a linked list of ships
// PRE: headptr == NULL, newNodeptr has been initialized
// POST: linked list of one node has been created
void InitList(ShipPtr& headPtr, ShipPtr& newNodePtr)
{
   //cout<<"Initializing list "<<endl<<endl;
    AddToFront(headPtr, newNodePtr);                                        // Add element to the front of the list
    headPtr->next=NULL;                                                     // the next pointer in the list is NULL
}

// Adds a node to the front of the linked list
// PRE: listPtr points to the first node of a linked list, newNodePtr has been initialized
// POST: newNodePtr is now at the front of the list
void AddToFront(ShipPtr& listPtr, ShipPtr& newNodePtr)
{
        newNodePtr->next = listPtr;                             // newNodePtr pointer's next element points to the head of the list
        listPtr= newNodePtr;                                    // make newNodeptr the new head of the list
}

// Adds a node to the back of the linked list
// PRE: headPtr points to the first node of a linked list, newNodeptr has been initialized
// POST: newNodePtr has been added to he back of the linked list
void AddToBack(ShipPtr& headPtr, ShipPtr& newNodePtr)
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
void removeShip(ShipPtr& target, ShipPtr& HeadPtr)
{
    ShipPtr currPtr = HeadPtr;
    ShipPtr prevPtr = NULL;
    bool dropped = false;


    if(target == HeadPtr)                   // if the course we are dropping is the head
    {
        HeadPtr = HeadPtr->next;            // set head pointer to the next pointer
        delete target;                              // delete the course to be dropped
    }
    else
    {
        while(currPtr!=NULL)                                // exit loop if we reach the end
        {
            if(target == currPtr)                   // Once the current pointer is pointing to the ship to be deleted...
            {
                //if(target == TailPtr)       // Check to see if course to be dropped is the tail pointer
                //    TailPtr = prevPtr;              // If so move the Tail pointer back one
                prevPtr->next = target->next;       // previous pointer skips over the target ship, to the next proceeding in the list
                delete target;                      // delete the dead ship
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
void PrintList(ShipPtr listPtr)
{
    ShipPtr currPtr = listPtr;                              // start currPtr at the head...
    int i = 1;
    cout<<endl;
    cout<<endl<<"Printing list"<<endl<<endl;
    while(currPtr!=NULL)                                    // until we reach the end of the list...
    {
        cout<<"#"<<setw(2)<<i<<": ";
        cout<<currPtr->component.name<<endl;                // print Name...

        cout<<"("<<currPtr->component.position.xCord<<","   // Starting Coordinate...
            <<currPtr->component.position.yCord<<")"
            <<currPtr->component.size<<endl;
        for(int i = 0; i < currPtr->component.size; i++)    // hitbox info...
            cout<<currPtr->component.hitbox[i]<<" ";
        cout<<endl;


        if(currPtr->component.orientation==horizontal)      // and orientation of the ship
        {
            cout<<"horizontal"<<endl;
        }

        else
        {
            cout<<"vertical"<<endl;
        }
        cout<<endl;
        currPtr=currPtr->next;                                // advance to the next ship
        i++;

    }
    cout<<endl;
}

