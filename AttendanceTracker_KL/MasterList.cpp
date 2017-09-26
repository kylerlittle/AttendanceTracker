#include "MasterList.h"

MasterList::MasterList()
{
	mpList = nullptr;
}

MasterList::~MasterList()
{
	// Algorithm:
	// 1. Set pCur to point at start of list
	// 2. While pCur is not null, walk through the list & delete the node
	//	  immediately before pCur
	// 3. if we're at the head of the list, I must set mpHead to null to avoid a dangling ptr
	Node *pCur = mpList, *pPrev = nullptr;
	if (!(this->isEmpty())) {		// takes care of an empty list
		while (pCur->getpNext() != nullptr) {
			pPrev = pCur;
			pCur = pCur->getpNext();
			if (pPrev == mpList) {  // if at the first item in the list, set head pointer to null
				mpList = nullptr;
			}
			delete pPrev;
		}
	}
}

void MasterList::loadRecords(fstream & CourseList)
{
	char garbageLine[50] = "";
	CourseList.getline(garbageLine, 50);		// get the first line out of the way

	fileData data;
	while (!(CourseList.eof())) {
		CourseList >> data;
		this->insertFront(data);
	}
}

void MasterList::loadFullRecords(fstream & masterFile)
{
	char garbageLine[100] = "";
	masterFile.getline(garbageLine, 100);		// get rid of the column headers I put in

	while (!(masterFile.eof())) {
		fileData empty;			// redeclare each time through the loop (so they're empty)
		Node data(empty);
		masterFile >> data;
		this->insertFront(data);
	}
}

void MasterList::storeRecords(fstream & masterFile)
{
	this->reverseList(mpList);		// Reverse the list first! Necessary since the
									// records are inserted in reverse order 
	Node *pCur = mpList;
	if (this->isEmpty()) {
		cout << "Empty list! Try loading some records." << endl;
	}
	else {		// output the column headers first!
		masterFile << ",ID,Name,Email,Units,Program,Level,Absences,NumberOfAbsences" << endl;
		while (pCur != nullptr) {    // takes care of an empty list
			masterFile << *pCur;		// uses overloaded stream insertion operator
			if (pCur->getpNext() != nullptr) {
				masterFile << endl;  // on the last time through, we don't want to add a newline
			}
			pCur = pCur->getpNext();
		}
	}
}

void MasterList::generateReportALL(fstream & masterFile)
{
	Node *pCur = mpList;

	while (pCur != nullptr) {
		masterFile << "Name: " << pCur->getName() << endl;
		masterFile << "Number of Absences: " << pCur->getNumAbsences() << endl;
		masterFile << "Most Recent Absence: " << pCur->getMostRecentAbsence();
		if (pCur->getpNext() != nullptr) {
			masterFile << endl << endl;
		}
		pCur = pCur->getpNext();
	}
}

void MasterList::generateReportAbsences(int absences, fstream & absenceReport)
{
	Node *pCur = mpList;

	while (pCur != nullptr) {
		if (pCur->getNumAbsences() >= absences) {		// then we want a report for them
			absenceReport << "Name: " << pCur->getName() << endl;
			absenceReport << "Number of Absences: " << pCur->getNumAbsences() << endl;
			absenceReport << "Most Recent Absence: " << pCur->getMostRecentAbsence() << endl << endl;
		}
		pCur = pCur->getpNext();
	}
}

bool MasterList::isEmpty()
{
	bool result = false;
	if (mpList == nullptr) {
		result = true;
	}
	return result;
}

bool MasterList::insertFront(fileData const &newData)
{
	bool success = false;

	// if list is empty
	// set mpHead to point at new Node
	if (this->isEmpty()) {
		mpList = new Node(newData);
		success = true;
	}
	// else, store mpHead into a temp pointer
	// set mpHead to point at new Node
	// pHead->setNextPtr(tempPtr);
	else {
		Node *pNewSecond = mpList;
		mpList = new Node(newData);
		mpList->setNextPtr(pNewSecond);
		success = true;
	}
	return success;
}

bool MasterList::insertFront(Node &newData)
{
	bool success = false;

	// if list is empty
	// set mpHead to point at new Node
	if (this->isEmpty()) {
		mpList = new Node(newData);		// uses Node copy constructor (EVEN though this passes by reference)
		success = true;
	}
	// else, store mpHead into a temp pointer
	// set mpHead to point at new Node
	// pHead->setNextPtr(tempPtr);
	else {
		Node *pNewSecond = mpList;
		mpList = new Node(newData);
		mpList->setNextPtr(pNewSecond);
		success = true;
	}
	return success;
}

void MasterList::printList() const
{
	Node *pCur = mpList;

	while (pCur != nullptr) {   // takes care of the case of an empty list
		pCur->printRecord();
		cout << endl;	// give a space in between each record
		pCur = pCur->getpNext();
	}
}

void MasterList::searchListbyName(string name)
{
	bool found = false;
	Node *pCur = mpList;

	while (!found && pCur != nullptr) {   // while not found and while not at end of list
		if (pCur->getName() == name) {
			found = true;
		}
		else {		// if we do find it, we don't want to update pCur 
			pCur = pCur->getpNext();	// and if it is found, the loop breaks anyways
		}
	}
	if (found) {
		pCur->removeAbsence();
	}
	else {
		cout << "No student was found with that name." << endl;
	}
}

void MasterList::searchListbyID(int IDnum)
{
	bool found = false;
	Node *pCur = mpList;

	while (!found && pCur != nullptr) {   // while not found and while not at end of list
		if (pCur->getIDNum() == IDnum) {
			found = true;
		}
		else {
			pCur = pCur->getpNext();
		}
	}
	if (found) {
		pCur->removeAbsence();
	}
	else {
		cout << "No student was found with that ID number." << endl;
	}
}

void MasterList::markAbsences()
{
	Node *pCurStudent = mpList;

	while (pCurStudent != nullptr) {
		cout << pCurStudent->getName() << endl;
		if (this->studentIsAbsent()) {		// see what I did there. eh? eh?
			pCurStudent->incrementAbsences();   // increment numAbsences by 1
			pCurStudent->pushToStack(todaysDate());		// mark the student as absent for today
		}
		pCurStudent = pCurStudent->getpNext();
	}
}

bool MasterList::studentIsAbsent()
{
	bool result = false;
	int answer = 0;
	cout << "Is this student here today? <1> for yes <2> for no: ";
	cin >> answer;
	if (answer == 2) {		// student is absent
		result = true;
	}
	return result;
}

void MasterList::reverseList(Node *& pList)
{
	Node *pCur = pList, *pPrev = nullptr, *pNext = nullptr;
	while (pCur != nullptr) {
		pNext = pCur->getpNext();
		pCur->getpNext() = pPrev;
		pPrev = pCur;
		pCur = pNext;
	}
	pList = pPrev;   // at the very end, we must set the head pointer to point at the "new head"
}

string todaysDate()
{
	time_t t = time(0);		// get time now
	struct tm * now = localtime(&t);
	string todaysDate = "";		// declare string that I'll be returning a copy of
	int day = now->tm_mday, month = now->tm_mon + 1, year = now->tm_year + 1900;
	todaysDate.append(to_string(day));	// converts day to a string & appends to todaysDate
	todaysDate.append(1, '-');
	todaysDate.append(to_string(month));
	todaysDate.append(1, '-');
	todaysDate.append(to_string(year));

	return todaysDate;	// notice how I return a COPY... if I passed back by reference,
	// then todaysDate would go out of scope & I'd be returning an invalid string
}