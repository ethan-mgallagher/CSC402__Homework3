/*
 * Ethan Gallagher
 * 11/20/2016
 * Instructor: Michael Clarke
 * Course: CSC 402
 * Assignment: Homework 3
 */

#include "Patient.h"
#include <iostream>

Patient::Patient(string f, string m, string l, string s, set<string> a, string d, int t, int pr) : firstName(f)
, middleName(m), lastName(l), suffix(s), ailments(a), doctor(d), treated(t), priority(pr) {};

//accessors are only needed for doctor, firstName, middleName, lastName and priority
string Patient::getFName() const{
    return firstName;
}

string Patient::getMName() const{
    return middleName;
}

string Patient::getLName() const{
    return lastName;
}

string Patient::getDoctor() const {
    return doctor;
}

int Patient::getPriority() const {
    return priority;
}

//mutators only needed for treated, nothing else should change
void Patient::setTreated(int t) {
    treated = t;
}

//print report out for the patient
//note format of report is the same as that used for input
//in the addPatients() and bulkAdd() functions of Hospital
void Patient::printReport() {
    cout << endl;
    cout << "firstName:" << firstName << endl;
    cout << "middleName:" << middleName << endl;
    cout << "lastName:" << lastName << endl;
    cout << "suffix:" << suffix << endl;
    set<string>::iterator it;//iterate over all ailments
    for ( it=ailments.begin(); it != ailments.end() ; it++ ){
        cout << "ailment:" << *it << endl;
    }
    cout << "doctor:" << doctor << endl;
    cout << "treated:" << to_string(treated) << endl;
    cout << "priority:" << to_string( priority ) << "\n\n";
}