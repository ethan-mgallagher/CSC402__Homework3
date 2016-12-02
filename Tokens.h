/*
 * Ethan Gallagher
 * 11/20/2016
 * Instructor: Michael Clarke
 * Course: CSC 402
 * Assignment: Homework 3
 */

//This header file contains preprocessor constants used for control flow
//in Logger.cpp and Hospital.cpp

//Each constant defines a string that indicates which scope a function was called from
// i.e. what other function or class ( int he case of main) it was called from

#ifndef HOMEWORK3_TOKENS_H
#define HOMEWORK3_TOKENS_H
#define A_PATIENT "addPatient"
#define B_ADD "bulkAdd"
#define MAIN "main"
#define P_REPORT "patientReport"
#define T_PATIENT "treatPatient"
#define B_TREAT "bulkTreat"
#define U_DOC "updateDoctors"
#define D_REPORT "doctorReport"
#define T_REPORT "triageReport"
#define U_REPORT "untreatedReport"
#endif //HOMEWORK3_TOKENS_H
