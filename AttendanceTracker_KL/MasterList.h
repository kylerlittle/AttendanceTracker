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

#include "Node.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::fstream;
using std::to_string;

class MasterList
{
public:
	// Constructor
	MasterList();

	// Destructor
	~MasterList();

	// Load Records from File
	// Will read in data fields from "courseList.csv" & store into the list.
	// Each object in the list is allocated to be on the heap, and inserted at the
	// front of the list.
	void loadRecords(fstream & CourseList);

	// Load "full records" (with absence numbers and dates) from master.txt
	// Will use overloaded stream extraction operator for fstream lhs and Node rhs
	void loadFullRecords(fstream & masterFile);

	// Store current records to "master.txt"
	// Will used overloaded stream insertion operator for fstream lhs & Node rhs
	// Output will be in the form of a standard csv file.
	void storeRecords(fstream & masterFile);

	// Report Generation
	void generateReportALL(fstream & masterFile);
	// only store records if absences is above threshold entered by user
	void generateReportAbsences(int absences, fstream & absenceReport);

	// isEmpty
	bool isEmpty();

	// Insert at Front
	bool insertFront(fileData const &newData);
	bool insertFront(Node &newData);

	// Print List
	void printList() const;

	// Search
	void searchListbyName(string name);
	void searchListbyID(int IDnum);

	// Mark absences
	void markAbsences();
	bool studentIsAbsent();

private:
	Node *mpList;		// head pointer

	// Private Functions
	// Reverses the List; this is private so that the user does not have access to the head
	// pointer. This function is called by the public function "storeRecords" so that
	// records are inserted back into the file in the correct order from which they
	// were originally extracted.
	void reverseList(Node *& pList);		
};

// Nonmember Functions
string todaysDate();