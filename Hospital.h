/*
 * Ethan Gallagher
 * 11/20/2016
 * Instructor: Michael Clarke
 * Course: CSC 402
 * Assignment: Homework 3
 */

//Check Hospital.cpp for function-specific documentation.

//This class provides all the required functionality as regards creating, reporting or manipulating
//Patient records, as well as all output to the console and to the log file.

#ifndef HOMEWORK3_HOSPITAL_H
#define HOMEWORK3_HOSPITAL_H

#include <queue>
#include <set>
#include <string>
#include <map>
#include <istream>
#include "Patient.h"
#include "Logger.h"

//type use for triage priority queue
typedef priority_queue< Patient *, deque<Patient *>, PCompare> triageType;
//type used to store patients in "untreated" and "treated" sets
typedef multiset<Patient *> datType;
//type used to store patients by doctor
typedef map<string, vector<Patient *>> docType;

using namespace std;

class Hospital {
private:
    triageType * triage;
    datType * treated;
    datType * untreated;
    docType * doctors;
    Logger * lg;

public:
    Hospital();
    ~Hospital();

    void addPatient();
    void inputParser( istream& in_stream, string specifier );
    void treatPatient();
    void patientReport();
    void insertPatient( string f, string m, string l, string s, set<string> * ail, string d, int t, int p);
    void treatedReport();
    void updateDoctors( Patient * p);
    void nextPatient();
    void triageReport();
    void bulkTreat();
    void patientByDoctorReport();
    void bulkAdd();
    void static printHelp( string specifier );

};


#endif //HOMEWORK3_HOSPITAL_H
