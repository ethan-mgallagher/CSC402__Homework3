/*
 * Ethan Gallagher
 * 11/20/2016
 * Instructor: Michael Clarke
 * Course: CSC 402
 * Assignment: Homework 3
 */

//Check Patients.cpp for function-specific documentation

//This class stores patient data in a Patient object and provides functionality for altering or retrieving said data
//This header file also includes the definition for the functor used to sort patients by priority in the
//triage priority_queue found in Hospital.h and Hosptial.cpp

#ifndef HOMEWORK3_PATIENT_H
#define HOMEWORK3_PATIENT_H

#include <string>
#include <set>

using namespace std;

class Patient {
private:
    string firstName;
    string middleName;
    string lastName;
    string suffix;
    string doctor;
    int treated;
    int priority;
    set<string>ailments;//we can have more than one ailment, all other data members are unique

public:
    Patient( string f , string m, string l, string s, set<string> a, string d, int t, int pr );

    string getFName() const;
    string getMName() const;
    string getLName() const;
    string getDoctor() const;
    int getPriority() const;

    void setTreated( int t );
    void printReport();


};

//functor for comparing patients in priority queue
class PCompare {
public:
    bool operator()( Patient * lhs, Patient * rhs ){
        return ( lhs->getPriority() > rhs->getPriority() );//lower number = higher priority
    }
};

#endif //HOMEWORK3_PATIENT_H
