/*******************************************************************************
* Programmer: Kyler Little													  *
* Class: CptS 122; Lab Section 6                                              *
* Programming Assignment: AttendanceTracker (PA #7)							  *
* Date: 4/4/2017                                                              *
*                                                                             *
* Description: This program is an application which manages attendance for	  *
*			   a course. If a course list csv file is supplied with			  *
*			   appropriate data fields, then all operations can be performed. *
*			   Operations include marking absences, generating reports, and   *
*			   storing any modifications to the list to a separate file.      *
*																			  *
* Relevant Formulas: Refer to each function definition.                       *
*                                                                             *
*																			  *
******************************************************************************/

#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include "Stack.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::fstream;
using std::ostream;

// Data Fields from File
// this struct makes it much "cleaner"
struct fileData
{
	int RecordNum;				// (max 3 digits)
	int IDnum;					// (max 9 digits)
	string Name;				// (last, first)
	string Email;
	int Units;					// (number of credits for class or AU for audit)
	string Program;				// (major)
	string Level;				// (freshman, sophomore, junior, senior, graduate)
};

class Node
{
public:
	// Constructor
	Node(const fileData &newData);

	// Copy Constructor
	Node(Node &copy);

	// Getters
	Node *& getpNext();
	int getRecordNum() const;
	int getIDNum() const;
	string getName() const;
	string getEmail() const;
	int getUnits() const;
	string getProgram() const;
	string getLevel() const;
	int getNumAbsences() const;
	string getMostRecentAbsence() const;
	string getAbsenceAtN(int N) const;

	// Setters
	void setNextPtr(Node * const pNewNext);
	void setRecordNum(const int newRecordNum);
	void setIDNum(const int newIDNum);
	void setName(const string newName);
	void setEmail(const string newEmail);
	void setUnits(const int newUnits);
	void setProgram(const string newProgram);
	void setLevel(const string newLevel);
	void pushToStack(string newAbsence);		// non const since passing by reference in 'push' function
	void setAbsences(const int newAbsenceNum);
	void incrementAbsences();
	void removeAbsence();  // be sure to update mNumAbsences as well

	// Print Node
	void printRecord() const;

private:
	Node *mpNext;					// Self Referential Pointer
	fileData mStudentInfo;			// Data Fields from File
	int mNumAbsences;				// User-Inputted Field
	Stack<string> mAbsenceDates;	// User-Inputted Field
};

// Non-Member Functions

// Stream Extraction Overloaded Operator
// This will be used to read in data from classList.csv and store into a fileData struct
fstream & operator >> (fstream &lhs, fileData &rhs);

// Stream Extraction Overloaded Operator
// This will be used to read in data from master.txt and store into a Node
fstream & operator >> (fstream &lhs, Node &rhs);

// Stream Insertion Overloaded Operator 
// This will be used to write nodes to master.txt 
fstream & operator << (fstream &lhs, Node &rhs);

// Print Node to Screen using Stream Insertion Overloaded Operator
ostream & operator << (ostream &lhs, const Node &rhs);