/*
 * Ethan Gallagher
 * 11/20/2016
 * Instructor: Michael Clarke
 * Course: CSC 402
 * Assignment: Homework 3
 */

//This class defines a singletong logger used for logging events in the Hospital system
//Check Logger.cpp for function-specific documentation

#ifndef LOGGER_H
#define LOGGER_H
#include <string>
#include "Patient.h"
#include <iostream>
#include <fstream>

using namespace std;

class Logger {

public:

    void getLogFile( string filename );
    void log( string specifier );
    void log( Patient * p, string specifier );
    static Logger * getLogger();

private:
    Logger();
    Logger(const Logger&);//don't implement
    string logfile;
};


#endif //LOGGER_H