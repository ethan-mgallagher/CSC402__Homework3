/*
 * Ethan Gallagher
 * 11/20/2016
 * Instructor: Michael Clarke
 * Course: CSC 402
 * Assignment: Homework 3
 */

#include "Logger.h"
#include "Tokens.h"

Logger::Logger(){}

//simply sets the logfile to the path provided by user input
//called from Hospital constructor, user input retrieved there
void Logger::getLogFile(string filename) {
    logfile = filename;
}

//'specifier' is a string indicating which function log was called from
//i.e. what action to log to file
void Logger::log(string specifier) {
    ofstream out( logfile, ios::app );//open logfile for append
    //prepare for writing timestamp
    time_t rtime;
    struct tm * timeinfo;

    time (&rtime);
    timeinfo = localtime (&rtime);

    //log action and a timestamp to file depending on specifier
    if ( specifier == B_TREAT ){
        out << "Bulk treat performed  " << asctime(timeinfo) << "\n";
    }
    else if ( specifier == D_REPORT ){
        out << "Doctors report generated  " << asctime(timeinfo) << "\n";
    }
    else if (specifier == T_REPORT ){
        out << "Triage report generated  " << asctime(timeinfo) << "\n";
    }
    else if (specifier == U_REPORT ){
        out << "Untreated patients report generated  " << asctime(timeinfo) << "\n";
    }
    else{//if function called with bad specifier
        out << "Unrecognized specifier entered" << asctime(timeinfo) << "\n";
        cerr << "Error: Unrecognized specifier to log function\n\n";
    }
    out.close();//close logfile
}

//overloaded version of log, this is called by any patient-specific function
//like insertPatient() -- the Patient's name is included in logfile
void Logger::log(Patient *p, string specifier) {
    ofstream out( logfile, ios::app );//open logfile for append
    //get ready for timestamp
    time_t rtime;
    struct tm * timeinfo;

    time (&rtime);
    timeinfo = localtime (&rtime);
    //log action (depending on timestamp) , patient info and a timestamp
    if ( specifier == A_PATIENT ){
        out << "Patient " << p->getFName() << " " << p->getMName() << " " << p->getLName() << " added  "
                                            << asctime(timeinfo) << "\n";
    }
    else if ( specifier == T_PATIENT ) {
        out << "Patient " << p->getFName() << " " << p->getMName() << " " << p->getLName() << " treated  "
                << asctime(timeinfo) << "\n";
    }
        else if ( specifier == P_REPORT ){
        out << "Report for patient " << p->getFName() << " " << p->getMName() << " " << p->getLName() << " generated  "
            << asctime(timeinfo) << "\n";
    }
    else{//if function called with bad specifier
        out << "Unrecognized specifier entered" << asctime(timeinfo) << "\n";
        cerr << "Error: Unrecognized specifier to log function\n\n";
    }
    out.close();//close logfile
}

//function for getting a reference to the logger singleton
Logger * Logger::getLogger() {
    static Logger instance;
    return &instance;
}
