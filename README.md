
Program prompt follows. Check header files for documentation on class purpose and structure and cpp files for function-specific documentaiton.


# homework3
C++ / Advanced Programming Homework 3

Prompt: 

Project 3 - CSC 402/502
STL && Streams
The point of this project will be to gain a familiarity and understanding of working with some common elements of the STL and using streams. You will be writing a full application, which mimics a hospital emergency room triage (very simplified) that has two major functions: cataloging/reporting of patient info and simulation of “treating” patients.

Acceptance Criteria
As a nurse, I want to add a patient to the system.

As a doctor, I want to “treat” a patient in triaged order.

As a doctor, I want to print out a patient’s info as a report.

As a doctor, I want to print out a report of “treated” patients.

As a doctor, I want to know the next patient to be “treated”.

As a hospital, I want to print out a report of all the patients in triage.

As a hospital, I want a single command to treat all patients.

As a hospital, I want a print out of all patients by doctor.

As a user, I want to be able to print out a guide on each command the system offers. (-help).

As an admin, I want to bulk add patients into the system (from a file).

As an admin, I want all operations of the system to be logged to a file that I can specify.

As a professor, my students should use standard STL containers, algorithms, and iterators to solve the problem.

As a professor, students should use the proper STL container for a triaging system.

As a professor, my students should use streams to facilitate the retrieval and storage of the patient data.

As a professor, my students should use proper syntax, formatting, commenting, break code into classes and separate files, and otherwise logically separate code.

As a professor, and as a user, I want a simple command-line style interface to easily interact with the system without confusion.

“Treating” a patient is marking them as treated and removing them from the triaged container and inserting them into a treated container, as well as some random thread sleep interval from 1 to 3 seconds.
Triaging patients is by priority order, and then first come, first serve. Priority is an integer, with lower number being a higher priority. E.g. 1 is higher than 10.
Do not worry about invalid data cases. 
All commands are accessible to all users, so you do not need to worry about roles, permissions, etc.
