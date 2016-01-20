using namespace std;


// for difficulty setting
enum Difficulty{ easy, normal, hard};

struct Coordinate
{
	int xCord;
	int yCord;
};

enum Orientation{ vertical, horizontal };

// struct to contain ships
struct Ships
{
	string name;
	Coordinate position;
	Orientation orientation;
	int size;
	bool *hitbox;
	bool alive; 	// if all condition = hit
};


struct ShipNode;

typedef ShipNode* ShipPtr;

struct ShipNode
{
    Ships component;
    ShipPtr next;
};

enum PlayerType{ human, cpu};

struct Player
{
    string name;
    int playerNumber;
    ShipPtr ships;
    char** board;
    PlayerType playerType;
};

enum Aim{ yUp, yDown, xLeft, xRight};
struct Target
{
    Coordinate initialHit;
    bool located;
    bool destroyed;
    bool *direction;

    Aim aiming;
    int up;
    int down;
    int left;
    int right;
};

// makes sure ships fit on board
int setAmountShips(int , int );

//initializes the board by setting all spaces to ocean = '~'
char** initBoard(char **, int);

// creates the ships – Battleship to Patrol Boat
void createShips(ShipPtr&,  int);

// turns coordinates of ship position to '#' on the board
// sets the ships on the board in random positions
void setShips(char **, ShipPtr, int);

// returns what character is in a particular space
char checkSpace(char **,Coordinate);

// generates a random coordinate
Coordinate randCoordinate(int);

// Calls randCoordinate to get a starting point
// places a ship on the board, returns true if successful, false if need to try again
bool placeShip(Ships &, char **&, int, Coordinate, int);


// if ocean or ship part draw '~', else, if Miss draw '.', else draw 'H'
// displays the board to the screen
void drawBoard(char **, int , bool);


void updateBoard(char,Coordinate, char **);

//
char launchAttack(Coordinate, char **);

// Checks if ship is still in play
bool Alive(Ships);

// Checks if any ships are still in play
bool gameOver(ShipPtr);

//prompts user for a coordinate
// calls checkSpace(Coordinate)...
// if check space is not ocean or Ship part get another coord
// returns the coordinate
Coordinate getUserCoord(int);

// called if a ship is hit
// returns ship that was hit
ShipPtr updateShips(Coordinate, ShipPtr);

// initializes each individual ship with the correct size and name
// and sets all spaces hitbox spaces to true
// new ships is returned
Ships initBattleShip();
Ships initCarrier();
Ships initDestroyer();
Ships initPatrolBoat();
Ships initSubmarine();

//Functions to manage linked list of ships
void InitList(ShipPtr& , ShipPtr& );
void AddToFront(ShipPtr& , ShipPtr& );
void AddToBack(ShipPtr& , ShipPtr& );
void PrintList(ShipPtr);
void removeShip(ShipPtr& , ShipPtr& );

// Functions to manage game modes
void GameLoop1();
void GameLoop2(Difficulty);

// Functions to manage versus mode
Player initCPU(int, int);
Player initUser(int, int);
void setUserShips(char**, ShipPtr, int);
bool userTurn(char** , int , ShipPtr );
bool cpuTurnV1(char**, int, ShipPtr, int);
bool cpuTurnV2(char**, int, ShipPtr);

