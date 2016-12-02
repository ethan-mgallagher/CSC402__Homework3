/*
 * Ethan Gallagher
 * 11/20/2016
 * Instructor: Michael Clarke
 * Course: CSC 402
 * Assignment: Homework 3
 */

#include <iostream>
#include "Hospital.h"

//this function simply executes an event loop, calling the appropriate function
//of the Hospital class depending on user input
int main() {

    //make new Hospital
    //this will prompt user for location of logfiel
    Hospital * hosp = new Hospital();
    Hospital::printHelp("main"); //print out main prompt first time so user knows what to do
    string input;

    //define a map relating valid user input to integers so a switch statement can be used
    //because why not switch statements are the shit
    map<string , int> inputMap = { {"-a" , 1 }, {"-t", 2}, {"-r", 3}, {"-tr", 4}, {"-ur", 5},
                                   {"-rn", 6}, {"-bt", 7}, {"-dr", 8}, {"-ba", 9},
                                   {"-h", 10}, {"-e", 11},  };

    bool running = true;//used to determine when to break out of event loop

    while (running){
        if ( !(cin>>input) ){//check for error state
            cin.clear();
            cout << "\nError occurred, please re-enter input\n";
        }
        else {
            //call appropraite function based on user input
            switch ( inputMap[input] ){
                case 1 : hosp->addPatient();
                    break;
                case 2: hosp->treatPatient();
                    break;
                case 3: hosp->patientReport();
                    break;
                case 4: hosp->treatedReport();
                    break;
                case 5: hosp->triageReport();
                    break;
                case 6: hosp->nextPatient();
                    break;
                case 7: hosp->bulkTreat();
                    break;
                case 8: hosp->patientByDoctorReport();
                    break;
                case 9: hosp->bulkAdd();
                    break;
                case 10: Hospital::printHelp("main");
                    break;
                case 11: cout<< "\n\nGoodbye"; running = false; break;
                default://invalid input
                    cout << "Input not recognized, please try again\n\n";
            }
        }
    }

    delete hosp;//delete hospital and return
    //hospital destructor deals with patient objects allocated on heap
    return(0);
}