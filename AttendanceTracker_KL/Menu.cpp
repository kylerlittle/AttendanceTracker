#include "Menu.h"

void Menu::run_app()
{
	int choice = 0;
	do {
		do {
			system("cls");
			this->printMenu();
			cin >> choice;
		} while (choice < 1 || choice > 7);  // make sure user choice is valid
		this->perform_user_choice(choice);
		system("pause");
	} while (choice != 7); // choice 7 means exit, so close program
	system("cls");
	cout << "Thanks for using Kyler Little's attendance tracker!" << endl;
}

void Menu::perform_user_choice(int option)
{
	switch (option)
	{
	case 1:			// Import Course List
		this->loadRecords();
		break;
	case 2:
		this->loadMasterList();
		break;
	case 3:
		this->storeMasterList();
		break;
	case 4:
		this->markAbsences();
		break;
	case 5:
		this->editAbsences();
		break;
	case 6:
		this->generateReport();
		break;
	case 7:
		this->storeMasterList();
		cout << "(i.e. Master list was saved before exiting.)" << endl;
		break;
	}
}

void Menu::printMenu()
{
	cout << "\t\tMENU" << endl;
	cout << "\t1.  Import course list." << endl;
	cout << "\t2.  Load master list." << endl;
	cout << "\t3.  Store master list." << endl;
	cout << "\t4.  Mark absences." << endl;
	cout << "\t5.  Edit absences." << endl;
	cout << "\t6.  Generate report." << endl;
	cout << "\t7.  Exit." << endl;
	cout << "Please enter a choice <1-7>: ";
}

void Menu::printSubMenu()
{
	cout << "\t\tREPORT MENU" << endl;
	cout << "\t1.  Generate report for all students." << endl;
	cout << "\t2.  Generate report for students with absences that match or exceed" << endl;
	cout << "\t    the number entered by the user (you)" << endl;
}

void Menu::printSearchMenu()
{
	cout << "\t\tSEARCH MENU" << endl;
	cout << "\t1.  Search for student by name." << endl;
	cout << "\t2.  Search for student by ID number." << endl;
	cout << "\t    Please enter <1> or <2>: ";
}

void Menu::loadRecords()
{
	if (mCourseList.is_open()) {   // if file is already open, it might not be open for "reading"
		mCourseList.close();
	}
	mCourseList.open("classList.csv");
	mStudentData.loadRecords(mCourseList);	
	cout << "Records loaded successfully!" << endl;
	mCourseList.close();
}

void Menu::loadMasterList()
{
	if (mMasterFile.is_open()) {
		mMasterFile.close();
	}
	mMasterFile.open("master.txt");
	mStudentData.loadFullRecords(mMasterFile);
	cout << "Master List records loaded successfully!" << endl;
	mMasterFile.close();
}

void Menu::storeMasterList()
{
	if (mMasterFile.is_open()) {
		mMasterFile.close();
	}
	mMasterFile.open("master.txt", std::ofstream::out | std::ofstream::trunc);	// trunc means "clear contents" of file
	mStudentData.storeRecords(mMasterFile);					// necessary so I overwrite it each time
	cout << "Master List records stored successfully!" << endl;
	mMasterFile.close();
}

void Menu::markAbsences()
{
	mStudentData.markAbsences();
}

void Menu::editAbsences()
{
	// Prompt user to search by name or ID num
	int choice = 0;
	do
	{
		system("cls");
		this->printSearchMenu();
		cin >> choice;
	} while (choice < 1 || choice > 2);
	system("cls");
	mStudentData.printList();
	this->performSearch(choice);
}

void Menu::performSearch(int choice)
{
	string name = "";
	int ID = 0;
	
	switch (choice)
	{
	case 1:
		cout << "Enter name: ";
		cin >> name;
		mStudentData.searchListbyName(name);
		break;
	case 2:
		cout << "Enter ID number: ";
		cin >> ID;
		mStudentData.searchListbyID(ID);
		break;
	}
}

void Menu::generateReport()
{
	int choice = 0;
	do
	{
		system("cls");
		this->printSubMenu();
		cin >> choice;
	} while (choice < 1 || choice > 2);	
	this->performReportChoice(choice);
}

void Menu::performReportChoice(int choice)
{
	int absences = 0;
	switch (choice)
	{
	case 1:
		this->generateReportALL();
		break;
	case 2:
		cout << "Create report for students with absences that match or exceed: ";
		cin >> absences;
		this->generateReportAbsences(absences);
		break;
	}
}

void Menu::generateReportALL()
{
	if (mMasterReport.is_open()) {		// close so that we change ensure mode is writing
		mMasterReport.close();
	}
	mMasterReport.open("masterReport.txt", std::ofstream::out | std::ofstream::trunc);	// clears contents of file first
	mStudentData.generateReportALL(mMasterReport);
	cout << "Report generated successfully!" << endl;
	mMasterReport.close();
}

void Menu::generateReportAbsences(int absences)
{
	if (mAbsenceReport.is_open()) {		// close so that we change ensure mode is writing
		mAbsenceReport.close();
	}
	mAbsenceReport.open("absenceReport.txt", std::ofstream::out | std::ofstream::trunc);		// clears contents of file first
	mStudentData.generateReportAbsences(absences, mAbsenceReport);
	cout << "Report generated successfully!" << endl;
	mAbsenceReport.close();
}