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
#include <fstream>
#include <string>
#include "MasterList.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::fstream;

class Menu
{
public:
	// run app
	void run_app();
	
	// run selected_choice
	void perform_user_choice(int option);


	void printMenu();						// print menu
	void printSubMenu();				// print sub-menu
	void printSearchMenu();				// print search menu

	// Load Student Records from CourseList.csv
	void loadRecords();

	// Load Master List from master.txt
	void loadMasterList();

	// Store Master List into master.txt
	void storeMasterList();

	// Mark Absences
	// Runs through each student and asks if the user was here or not
	void markAbsences();

	// Edit Absences
	void editAbsences();
	void performSearch(int choice);		// based on name or ID

	// Generate Report
	void generateReport();
	void performReportChoice(int choice);		// based on report type
	void generateReportALL();						// writes report to masterReport.txt
	void generateReportAbsences(int absences);		// writes report to absenceReport.txt

private:
	MasterList mStudentData;		
	fstream mCourseList;					// import records from courseList.csv
	fstream mMasterFile;					// used for reading and writing with master.txt
	fstream mMasterReport;					// writing to masterReport.txt
	fstream mAbsenceReport;					// writing to absenceReport.txt
};