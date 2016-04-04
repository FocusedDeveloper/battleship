#ifndef LOSTTARGET_H
#define LOSTTARGET_H

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace::std;

// exception class...
// TBD: output time stamp with each log
//      read in file, save all data, write it all back with updated log
class LostTarget
{
    public:

        LostTarget()        // empty constructor, prints basic error message
        {
            message = "Targeting system has lost the target.  A valid attack Coordinate has not been found.";
            baseName = "targetLog";
            buildTimeString();
            buildOuputFile();
            logReport();
        }
        // TBD: Target data placed in a string, along with attack log, and attacked board
        LostTarget(Target myTarget, string attackLog = "", string enemyBoard = "")
        {
            message = "Targeting system has lost the target.  A valid attack Coordinate has not been found.";
            baseName = "targetLog";
            buildTimeString();
            buildOuputFile();
            logReport();
        }
        string what()
        {
            return message;
        }

    private:
        string message;
        string baseName;
        string dateTime;
        string fileName;

        // uses current time to get a time stamp for the error
        void buildTimeString()
        {
            time_t currTime = time(0); // get current time
            time(&currTime);
            dateTime = ctime(&currTime);
        }

        // builds output file name
        void buildOuputFile()
        {
            fileName = baseName;
            fileName.append(".txt");
        }

        // logs the error to txt file
        void logReport()
        {
            ofstream outFile;
            outFile.open(fileName.c_str() );
            outFile<<dateTime<<endl;
            outFile<<message<<endl<<endl;

            outFile.close();
        }
};

#endif // LOSTTARGET_H
