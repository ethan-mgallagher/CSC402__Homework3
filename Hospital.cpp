/*
 * Ethan Gallagher
 * 11/20/2016
 * Instructor: Michael Clarke
 * Course: CSC 402
 * Assignment: Homework 3
 */

#include "Hospital.h"
#include "Tokens.h"
#include <sstream>
#include <chrono>
#include <thread>
#include <random>

using namespace std;

Hospital::Hospital(){
    triage = new triageType;//priority queue, store patients in order of urgency
    treated = new datType;//multiset of all treated patient records
    untreated = new datType;//multiset of all untreated patient records
    doctors = new docType;//stores patient records by doctor
    lg = Logger::getLogger();

    //set up logfile for this process
    string lfile;
    cout<<"Enter path of logfile: \n";
    getline( cin, lfile );
    lg->getLogFile( lfile );
    srand( time(NULL) );//initialize randomizer
}

//destructor for hospital
//deallocates all memory this object allocated on the heap
//as well as all Patient objects allocated on the heap
Hospital::~Hospital(){

    datType::iterator itr;

    //clear memory and delete private data members
    for ( itr = treated->begin() ; itr != treated->end() ; itr++ ){
        delete *itr;
    }

    for ( itr = untreated->begin(); itr != untreated->end() ; itr++ ){
        delete *itr;
    }

    delete triage;
    delete treated;
    delete untreated;
    delete doctors;

}

//insert patient into doctors database
//find correct doctor key or make a new one if needed
void Hospital::updateDoctors( Patient * p ){
    map<string, vector<Patient *>>::iterator m_it;
    int found = 0;

    for ( m_it=doctors->begin() ; m_it != doctors->end() ; m_it++ ){
        if ( p->getDoctor() == m_it->first ){
            m_it->second.push_back( p );
            found = 1;
        }
    }

    if ( !found ){
        vector<Patient *> temp = vector<Patient *>();
        temp.push_back(p);
        doctors->insert( pair< string, vector<Patient *>>( p->getDoctor(), temp ) );
    }

}

//treats patient at top of priority queue and sleeps for 1 - 3 s
void Hospital::treatPatient(){
    int sleep = 0;
    if ( triage->empty() ){
        cout << "No patients to treat\n\n";
        Hospital::printHelp(MAIN);
        return;
    }

    triage->top()->setTreated(1); //set patient to treated
    treated->insert( triage->top() ); //insert patient into treated multiset
    untreated->erase( triage->top() ); //erase patient from untreated multiset

    sleep = rand() % 2000 + 1000;
    this_thread::sleep_for(chrono::milliseconds(sleep));

    cout << "Following patient has been treated: \n";
    lg->log( triage->top(), T_PATIENT );//log procedure to logfile
    triage->top()->printReport();
    triage->pop(); //pop patient from triage priority queue

    Hospital::printHelp(MAIN);// print main help to let user know what input is expected
}

//helper function for inputParser.
//creates a new patient record and inserts it as a pointer into the relevant data structures
//all the logging for addPatient() and bulkAdd() occurs here
void Hospital::insertPatient( string f, string m, string l, string s, set<string> * ail, string d, int t, int p){
    Patient * p_temp;
    //create new patient record and insert into appropriate data structures
    p_temp = new Patient( f, m, l, s, *ail, d, t, p);
    if (t){
        treated->insert(p_temp );
        updateDoctors( p_temp );
    }
    else {
        triage->emplace( p_temp );
        untreated->insert( p_temp );
        updateDoctors( p_temp );
    }
    lg->log( p_temp, A_PATIENT );//log patient creation to logfile

    cout<< "Patient \"" << f << " " << m << " " << l << "\" added.\n\n";//notify user of success
}

//parses input into data for adding patient record to hospital
//adding patients from files or the command line uses the same format
//so we will parse the input with a single function.
//The input stream that will be used is passed in as 'in_stream'
//A string specifier indicating whether this function is being called
//by bulkAdd() or addPatient() is passed in as 'specifier'
//this should be one of the preprocessor defined constants from Tokens.h
void Hospital::inputParser(istream& in_stream, string specifier) {
    //check for valid specifier
    if ( specifier != A_PATIENT && specifier != B_ADD ){
        cerr << "Error: unrecognized specifier in inputParser call ";
        return;
    }

    string line;
    string f = "", m = "", l = "", s = "", d = "";
    set<string> * ail = new set<string>;
    int t=0, p = 0;

    cin.ignore();//ignore /n character from help prompt
    //while not at EOF
    while( getline(in_stream, line)){
        //parse add_patient specific input
        if ( specifier == A_PATIENT ){//if addPatient() called this function
            if ( line == "-h" ){
                Hospital::printHelp(A_PATIENT);
                continue; //unavoidable, system must get new line here
            }
            if (line == "-e" ){//exit to main prompt
                cout<<"Returning to main prompt\n\n";
                return;
            }
            if (line == "-s" ){//print out current patient data
                set<string>::const_iterator itr;
                cout
                        << "\nfirstName:" << f << "\n"
                        << "middleName:" << m << "\n"
                        << "lastName:" << l << "\n"
                        << "suffix:" << s << "\n";
                for ( itr=ail->cbegin() ; itr != ail->cend() ; itr++  ){
                    cout << "ailment:" << *itr << "\n";
                }
                cout
                        << "doctor:" << d << "\n"
                        << "treated:" << t << "\n"
                        << "priority:" << p << "\n\n";
                continue;// unavoidable, system must get new line at this point
            }
            if ( line == "add" ){//add current data to system
                this->insertPatient( f, m, l, s, ail, d, t, p );
                ail->clear();//clear ailments
                f = "", m = "", l = "", s = "", d = "";//clear other fields
                t = 0, p = 0;
                Hospital::printHelp(A_PATIENT);
                continue; //unavoidable, system must get new line at this point
            }
        }

        //generic input parsing
        if ( line.substr(0, 10) == "firstName:" ){
            f = line.substr(10);
            cout << "Good input for first name\n";
        }
        else if( line.substr(0, 11) == "middleName:" ){
            m = line.substr(11);
            cout << "Good input for middle name\n";
        }
        else if( line.substr(0, 9) == "lastName:" ){
            l = line.substr(9);
            cout << "Good input for last name\n";
        }
        else if ( line.substr(0,7) == "suffix:" ){
            s = line.substr(7);
            cout << "Good input for suffix\n";
        }
        else if ( line.substr(0,8) == "ailment:" ){
            ail->insert( line.substr(8));
            cout << "Good input for ailment\n";
        }
        else if ( line.substr(0,7) == "doctor:" ){
            d = line.substr(7);
            cout << "Good input for doctor\n";
        }
        else if ( line.substr(0,8) == "treated:" ){
            t = stoi(line.substr(8));
            cout << "Good input for treated\n";
        }
        else if ( line.substr(0,9) == "priority:"){
            cout << "Good input for priority \n";
            p = stoi( line.substr(9) );
            if ( specifier == B_ADD ) {//if in bulk-add mode, priority is the signal to add the patient
                this->insertPatient( f, m, l, s, ail, d, t, p );
                ail->clear(); // clear ailments
                f = "", m = "", l ="", s="", d = ""; //clear other fields
                t=0, p= 0;
            }
        }
        else  if ( specifier == A_PATIENT ){//user feedback if addPatient() called this function
            cout << "Unrecognized input, please try again \n";
        }

    }

    delete ail;

}

//This function is used to add a patient record from the command line
//using user input.
void Hospital::addPatient() {

    Hospital::printHelp( A_PATIENT );//print help prompt for this function

    this->inputParser( cin , A_PATIENT );//parse input we get from command line

    Hospital::printHelp(MAIN);//print main help before returning to event loop so user knows what to do
}

//Function for bulk-adding patients to system from file
void Hospital::bulkAdd() {

    Hospital::printHelp(B_ADD);//print out help prompt for this function

    //get file path or user input
    bool valid = 0;
    string file;

    while ( !valid ) {
        cin >> file;
        if (file == "-e") {
            cout << "Returning to main prompt";
            Hospital::printHelp(MAIN);
            return;
        }
        else if (file == "-h") {
            Hospital::printHelp(B_ADD);
        }
        else if (!cin) {
            cout << "Error encountered, please try again ";
            cin.clear();
        }
        else {
            valid = true;
        }
    }

    //open input file and call inputParser()
    ifstream i_file;
    i_file.open( file, ios::in );

    cout << "Bulk add file opened succesfully\n\n";

    this->inputParser( i_file , B_ADD );

    //close file and print out main prompt so user knows what to do
    i_file.close();
    Hospital::printHelp(MAIN);

}

//Treat every patient in triage
void Hospital::bulkTreat() {
    int sleep = 0;
    while ( !triage->empty() ){//while patients left to treat
        treated->insert( triage->top() );//insert into treated multiset
        triage->top()->setTreated(1);//set the patient record to treated
        triage->pop();//pop from triage
        sleep = rand() % 2000 + 1000;//sleep 1-3s
        this_thread::sleep_for(chrono::milliseconds(sleep));
    }

    untreated->clear();//clear untreated multiset
    cout<<"Bulk treatment completed\n\n";
    lg->log( B_TREAT );//log bulk treatment to file
    Hospital::printHelp(MAIN);//pint out main prompt so user knows what to do
}

//print out the report for a patient specified by user from command line
void Hospital::patientReport( ) {
    bool found;//indicates whether record found
    Patient * temp;
    multiset<Patient *>::iterator it;//for iterating over treated and untreated multisets
    string f, m, l; //first middle and last names
    string input;

    Hospital::printHelp( P_REPORT );//print out help prompt
    cin.ignore();//ignore last /n

    while( 1 ) {//until user exits this subsystem with -e

        found = false;//we haven't found the record yet
        //get input and try to parse into first middle and last name
        getline( cin, input );
        istringstream iss( input );

        if ( iss >> f >> m >> l ) {
            //check treated and untreated patient sets
            for (it = treated->begin(); it != treated->end(); it++) {
                temp = *it;
                if (temp->getFName() == f && temp->getMName() == m && temp->getLName() == l) {
                    temp->printReport();
                    Hospital::printHelp(P_REPORT);
                    lg->log( temp, P_REPORT );//log printing of report
                    found = true;
                }
            }

            for (it = untreated->begin(); it != untreated->end(); it++) {
                temp = *it;
                if (temp->getFName() == f && temp->getMName() == m && temp->getLName() == l) {
                    temp->printReport();
                    Hospital::printHelp(P_REPORT);
                    lg->log( temp, P_REPORT );//log printing of report
                    found = true;
                }
            }

            if ( !found ){//if not in either of those multisets, not in system
                cout << "Patient not found \n\n";
            }
        }
        else if ( input == "-e" ){//exit on user specification
            Hospital::printHelp(MAIN);//print out main help prompt so user knows what to do
            return;
        }
        else if ( input == "-h" ){//print out help for this subsystem
            Hospital::printHelp( P_REPORT );
        }
        else {//else invalid input was entered
            cout << "Input not recognized, please try again";
        }

    }


}

//print out report for patient next in line to be treated
void Hospital::nextPatient() {
    cout << "Next patient to be treated is: " << endl;
    if ( triage->empty() ){//check if triage is empty
        cout << "No patients left in triage \n\n";
        Hospital::printHelp(MAIN);//print out main help prompt so user knows what to do
        return;
    }
    lg->log( triage->top(), P_REPORT );//log printing of patient report
    triage->top()->printReport();//print report of patient at top of triage
    Hospital::printHelp(MAIN);//print out main help prompt so user knows what to do
}

//print out a report of all patients, organized by doctor
void Hospital::patientByDoctorReport( ) {

    //prepare to iterate over doctor map
    docType::iterator m_it;
    vector<Patient *> temp;

    //each member of doctors is a doctor in the system, mapped to a vector of patient record pointers
    for ( m_it = doctors->begin(); m_it != doctors->end() ; m_it++ ){
        cout << "\nPatient reports for doctor: " << m_it->first << endl;//patient results for this doctor
        temp = m_it->second;//get vector of patient pointers
        for ( int i = 0; i < temp.size(); i++ ){
            temp[i]->printReport();//print out a report for each patient associated with this doctor
        }
    }

    lg->log( D_REPORT );//log printing of reports by doctor to logfile
    Hospital::printHelp(MAIN);//print out main help prompt so user knows what to do
}

//print out a report of all treated patients
void Hospital::treatedReport() {
    //prepare to iterate over treated multiset
    datType::const_iterator itr;
    Patient * temp;

    cout << "Reports for all treated patients: \n\n";
    for ( itr = treated->cbegin() ; itr != treated->cend() ; itr++ ){
        temp = *itr;
        temp->printReport();//print out report for each patient
    }

    //log event to logfile and print out main help prompt so user knows what to do
    lg->log( U_REPORT );
    Hospital::printHelp(MAIN);
}

//print out a report of all untreated patients
void Hospital::triageReport() {
    //prepare to iterate over untreated patients multiset
    datType::const_iterator itr;
    Patient * temp;

    cout << "Reports for all patients in triage: \n\n";
    for ( itr = untreated->cbegin() ; itr != untreated->cend() ; itr++ ){
        temp = *itr;
        temp->printReport();//print out each patient's report
    }

    //log event and print out main prompt so user knows what to do
    lg->log( T_REPORT );
    Hospital::printHelp(MAIN);
}

//static function containing all help prompts for hospital system
//functions with significant help prompts have their prompts stored here
//function is called with a string 'specifier', this should be
//one of the constants defined in Tokens.h
void Hospital::printHelp( string specifier ){
    if ( specifier == MAIN ) {//main help prompt
        cout << "Hospital command prompt help system \n"
             << "Commands requiring user input have their own help systems \n"
             << "Format: \" command \" -- action \n"
             << " \"-a\"  -- add patient \n"
             << " \"-t\"  -- treat patient with highest priority \n"
             << " \"-r\"  -- generate a patient report \n"
             << " \"-tr\"  -- generate a report of all treated patients \n"
             << " \"-ur\"  -- generate a report for all patients in triage \n"
             << " \"-rn\"  -- generate a report for the next patient to be treated \n"
             << " \"-bt\"  -- bulk treat all patients in triage \n"
             << " \"-dr\"  -- generate reports for all patients by doctor \n"
             << " \"-ba\"  -- bulk add patients to system with an input file \n"
             << " \"-h\"  -- print help  \n"
             << " \"-e\"  -- exit from system \n\n";
    }
    else if ( specifier == A_PATIENT ){//addPatient() help prompt
        cout << "Enter patient information in following format: \n"
             << "firstName:data\n middleName:data\n lastName:data\n suffix:data\n ailment:data\n "
                     "doctor:(data)\n treated:(0 for false, 1 for true)\n priority:(numerical value)\n\n "
             << "After entering a data item, press enter to add it to the patient record. Enter \"add\" to add patient"
             << " to system with current data\n"
             << " to return to main prompt enter -e \n"
             << " to reprint this prompt, enter -h\n"
             << " to overwrite previously entered data, simply enter new data\n "
             << "to see the currently entered data, enter -s\n"
             << "Valid input will generate a response from the system\n\n";
    }
    else if ( specifier == B_ADD ){//bulk add help prompt
        cout << "Bulk add help system \n"
             << "Enter the file path, -e to exit or -h to reprint this prompt\n"
             << "Full file path may need to be entered\n\n";
    }
    else if ( specifier == P_REPORT ){//patient report help prompt
        cout << "Patient report help system \n"
             << "enter patient name in first middle last format, separated by spaces \n"
             << "enter -e to exit or -h to reprint this prompt \n\n";
    }
    else{
        cerr << "Error, unrecognized call to printHelp() \n\n";
    }
}

