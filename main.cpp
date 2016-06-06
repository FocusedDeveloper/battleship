//*****************************************************
//  Charles Darnell Johnson 5100474
//  04/03/2016
//  Battleship Game
//  This game allows the user to play  2 different
//  versions of the classic Battleship game.
//  Version 1 - Single player see how many attacks it takes to
//  destroy all cpu ships.
//  Version 2 - Play against a CPU opponent
//  In both version the user may select the total number of ships (stored in a linked list)
//  as well as the size of the playing board for the game. (dynamic 2d array of characters)
//  TBD: Additional game modes
//*****************************************************


#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>


#include "Ship.h"
//#include "Coordinate.h"
//#include "Board.h"
#include "LinkedList.h"
#include "Player.h"
//#include "LostTarget.h"



using namespace std;

void gameLoop1();
void gameLoop2();
void testLinkedList();


int main()
{
    srand(time(NULL));  // seed the time for random numbers

    int option;

    do
    {
        cout << "*** BATTLESHIP ***"<< endl;
        cout << "Select an option:" << endl
             << "  1) Single Player Standard Mode" << endl
             << "  2) Player vs CPU " << endl
//             << "  3) Player vs Player " << endl
//             << "  4) Player vs CPU (hard)" << endl
            << " 4) Test Linked List" << endl
             << "  3) Exit" << endl;
        cin >> option;

        if (!cin){
            cin.clear();
        }

        cin.ignore(500, '\n');
        cout << endl;

        switch (option)
        {
        case 1:
            gameLoop1();
            break;
        case 2:
            gameLoop2();            // cpu attacks once per turn
            break;
        case 4:
            testLinkedList();
            break;
//        case 4:
//            cpuDiff = hard;
//            GameLoop2(hard);            // cpu attacks thre times per turn!
//            break;
        case 3:
            cout << "Thanks for playing." << endl;
            break;
        default:
            cout << "Invalid option entered" << endl;
            cin.clear();
            cin.ignore(500, '\n');
        }

    } while (option != 3);


    return 0;
}

void testLinkedList()
{
    LinkedList<Ship> myList;
    int option;
    int myNum;
    char myChar;
    string shipName = "DefaultShip";
    Ship myShip;

    do
    {
        cout<<"Enter an option" << endl
            <<" 1) add to list " <<endl
            <<" 2) remove from list " <<endl
            <<" 3) print list "<< endl
            <<" 4) delete list " <<endl
            <<" 5) exit "<<endl;
        cin>>option;
        if(!cin)
        {
            cin.clear();
        }

        cin.ignore(500, '\n');
        cout<<endl;

        switch (option)
        {
            case 1: cout<<"Add) Input a ship size: ";
                    cin>>myNum;
                    myShip = Ship(shipName,myNum);
                    myList.addToFront(myShip);
                    break;

            case 2: cout<<"Del) Input a ship size: ";
                    cin>>myNum;
                    myShip = Ship(shipName,myNum);
                    myList.removeComponent(myShip);
                    break;

            case 3: myList.printList();
                    cout<<endl;
                    break;

            case 4: cout<<"This will delete the list" <<endl
                    << "Are you sure? Yes (Y) or No (N): ";
                    cin>> myChar;
                    myChar = toupper(myChar);
                    if(myChar == 'Y')
                        myList.deleteList();
                    break;

            case 5: cout<<"Exiting"<<endl;
                    break;

            default: cout<<"Invalid option"<<endl;
                    cin.clear();
                    cin.ignore(500, '\n');
                    break;
        }
    }while( option != 5 );


}

void gameLoop1()
{
    char myChar;

    int numberShips;
    int boardSize;
    int turnCount = 0;
    int attackCounter = 0;

        cout<<"What size board would you like: ";
        cin>>boardSize;
        cout<<endl;
        cout<<"How many ships: ";
        cin>>numberShips;
        cout<<endl;

        Player myPlayer1(0, 0, human);    // Create my two players
        Player myPlayer2(boardSize, numberShips, cpu);          // cpu player
        //myPlayer1.printList();
        myPlayer1.displayBoard(true);
        //myPlayer2.displayBoard(true);

        do{                         // this until game over
            turnCount++;
            if(turnCount%2 == 1)
            {
                attackCounter++;
                myPlayer1.launchAttack(myPlayer2);
            }

        }while(myPlayer2.getGameOver() == false );

        cout<<"You win!"<<endl;
        cout<<"It took you "<<attackCounter<<" turns to sink all of my ships"<<endl;
        cout<<"(Input any character to continue)"<<endl;
        cin>>myChar;


}

void gameLoop2()
{
    char myChar;

    int numberShips;
    int boardSize;
    int turnCount = 0;
    int attackCounter = 0;


        cout<<"What size board would you like: ";
        cin>>boardSize;
        cout<<endl;
        cout<<"How many ships: ";
        cin>>numberShips;
        cout<<endl;

        Player myPlayer1(boardSize, numberShips, human);    // Create my two players
        Player myPlayer2(boardSize, numberShips, cpu);          // cpu player
        //myPlayer1.printList();
        myPlayer1.displayBoard(true);
        //myPlayer2.displayBoard(true);

        do{                         // this until game over
            turnCount++;
            if(turnCount%2 == 1)
            {
                attackCounter++;
                myPlayer1.launchAttack(myPlayer2);      // player 1 attacks
            }

            else{
                myPlayer2.launchAttack(myPlayer1);      // cpu attacks
            }

        }while(myPlayer2.getGameOver() == false && myPlayer1.getGameOver() == false);

        if(turnCount%2==1){                                                                       // If game ended on user's turn...
            cout<<"You win!"<<endl;
            cout<<"It took you "<<attackCounter<<" turns to sink all of my ships"<<endl;
        }
        else{                                                                                       // If game ended on computer's turn...
            cout<<"You lose.  Deal with it."<<endl;
        }
        cout<<"(Input any character to continue)"<<endl;
        cin>>myChar;
}


