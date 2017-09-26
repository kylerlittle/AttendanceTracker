#include "Node.h"

Node::Node(const fileData &newData)
{
	mpNext = nullptr;		// nextptr should always be set to nullptr in constructor

	mStudentInfo.RecordNum = newData.RecordNum;
	mStudentInfo.IDnum = newData.IDnum;
	mStudentInfo.Name = newData.Name;
	mStudentInfo.Email = newData.Email;
	mStudentInfo.Units = newData.Units;
	mStudentInfo.Program = newData.Program;
	mStudentInfo.Level = newData.Level;

	mNumAbsences = 0;
	// by default, numItems in Stack will be set to 0, so I don't need to do that again here
}

Node::Node(Node &copy)
{
	mpNext = copy.getpNext();
	mStudentInfo.RecordNum = copy.getRecordNum();
	mStudentInfo.IDnum = copy.getIDNum();
	mStudentInfo.Name = copy.getName();
	mStudentInfo.Email = copy.getEmail();
	mStudentInfo.Units = copy.getUnits();
	mStudentInfo.Program = copy.getProgram();
	mStudentInfo.Level = copy.getLevel();
	mNumAbsences = copy.getNumAbsences();
	mAbsenceDates = copy.mAbsenceDates;  // uses copy contructor!
}

Node *& Node::getpNext()
{
	return mpNext;
}

int Node::getRecordNum() const
{
	return mStudentInfo.RecordNum;
}

int Node::getIDNum() const
{
	return mStudentInfo.IDnum;
}

string Node::getName() const
{
	return mStudentInfo.Name;
}

string Node::getEmail() const
{
	return mStudentInfo.Email;
}

int Node::getUnits() const
{
	return mStudentInfo.Units;
}

string Node::getProgram() const
{
	return mStudentInfo.Program;
}

string Node::getLevel() const
{
	return mStudentInfo.Level;
}

int Node::getNumAbsences() const
{
	return mNumAbsences;
}

string Node::getMostRecentAbsence() const
{
	string absence = "";
	if (mAbsenceDates.peek(absence)) {
		return absence;
	}
	else {
		return "No absences";
	}
}

string Node::getAbsenceAtN(int N) const {
	return mAbsenceDates.returnItemAtN(N);
}

void Node::setNextPtr(Node * const pNewNext)
{
	mpNext = pNewNext;
}

void Node::setRecordNum(const int newRecordNum)
{
	mStudentInfo.RecordNum = newRecordNum;
}

void Node::setIDNum(const int newIDNum)
{
	mStudentInfo.IDnum = newIDNum;
}

void Node::setName(const string newName)
{
	mStudentInfo.Name = newName;
}

void Node::setEmail(const string newEmail)
{
	mStudentInfo.Email = newEmail;
}

void Node::setUnits(const int newUnits)
{
	mStudentInfo.Units = newUnits;
}

void Node::setProgram(const string newProgram)
{
	mStudentInfo.Program = newProgram;
}

void Node::setLevel(const string newLevel)
{
	mStudentInfo.Level = newLevel;
}

void Node::setAbsences(const int newAbsenceNum)
{
	mNumAbsences = newAbsenceNum;
}

void Node::incrementAbsences()
{
	++mNumAbsences;
}

void Node::pushToStack(string newAbsence)
{
	mAbsenceDates.push(newAbsence);
}

void Node::removeAbsence()
{
	cout << "Absence Dates:" << endl;
	mAbsenceDates.displayStack();   // display all absence dates
	cout << "Student was incorrectly marked absent on day: ";
	string removeThisAbsence = "";
	cin >> removeThisAbsence;
	int indexFoundAt = mAbsenceDates.searchStack(removeThisAbsence);
	if (mAbsenceDates.removeItem(indexFoundAt)) {		// returns true if found
		--mNumAbsences;   // subtract number of absences
	}		// otherwise, we shouldn't decrement number of absences
}

void Node::printRecord() const
{
	cout << (*this) << endl;   // usees overloaded stream insertion operator
}



// Non Member Functions
fstream & operator >> (fstream &lhs, fileData &rhs)
{
	char tempString[50] = "", firstDoubleQuote = '\0', comma = '\0';

	lhs.getline(tempString, 5, ',');

	// my eof() function doesn't work on this computer, so I have to add this extra 'if'
	// statement so that it doesn't read in an extra blank record
	if (tempString[0] != '\0') {
		int RecordNum = atoi(tempString);
		rhs.RecordNum = RecordNum;
		lhs.getline(tempString, 9, ',');
		int ID = atoi(tempString);
		rhs.IDnum = ID;
		lhs.get(firstDoubleQuote);			// read in first double quote to ignore it
		lhs.getline(tempString, 50, '\"');	// now we should be able to grab the full name
		lhs.get(comma);						// now grab that closing comma
		rhs.Name = tempString;
		lhs.getline(tempString, 50, ',');
		rhs.Email = tempString;
		lhs.getline(tempString, 3, ',');
		if (tempString == "AU") {  // person is auditing course
			rhs.Units = 0;
		}
		else {
			int numCredits = atoi(tempString);
			rhs.Units = numCredits;
		}
		lhs.getline(tempString, 20, ',');
		rhs.Program = tempString;
		lhs.getline(tempString, 20, '\n');
		rhs.Level = tempString;
	}
	return lhs;
}

fstream & operator >> (fstream &lhs, Node &rhs)
{
	char tempString[100] = "", firstDoubleQuote = '\0', comma = '\0';
	string dates = "";

	lhs.getline(tempString, 5, ',');

	// my eof() function doesn't work on this computer, so I have to add this extra 'if'
	// statement so that it doesn't read in an extra blank record
	if (tempString[0] != '\0') {
		int RecordNum = atoi(tempString);
		rhs.setRecordNum(RecordNum);
		lhs.getline(tempString, 9, ',');
		int ID = atoi(tempString);
		rhs.setIDNum(ID);
		lhs.get(firstDoubleQuote);			// read in first double quote to ignore it
		lhs.getline(tempString, 50, '\"');	// now we should be able to grab the full name
		lhs.get(comma);						// now grab that closing comma
		rhs.setName(tempString);
		lhs.getline(tempString, 50, ',');
		rhs.setEmail(tempString);
		lhs.getline(tempString, 3, ',');
		if (tempString == "AU") {  // person is auditing course
			rhs.setUnits(0);
		}
		else {
			int numCredits = atoi(tempString);
			rhs.setUnits(numCredits);
		}
		lhs.getline(tempString, 20, ',');
		rhs.setProgram(tempString);
		lhs.getline(tempString, 20, ',');
		rhs.setLevel(tempString);
		lhs.get(firstDoubleQuote); // if this is, instead, a comma, then the field is empty
		if (firstDoubleQuote == '\"') {
			lhs.getline(tempString, 100, '\"');
			// I have the string of dates; just need to parse & pushToStack
			for (int i = 0; tempString[i] != '\0'; ++i) {		// takes care of case of 0 absences
				if (tempString[i] == ',') {
					rhs.pushToStack(dates);		// once we've reached delimiter, add date to stack!
					dates = "";
				//if (tempString[i + 1] != '\0') {	// then we have more absences to read in
					//	dates = "";			// reset the string to nothing
					//}
				}
				else {
					dates.append(1, tempString[i]);		// appends 1 consecutive copy of the current char
				}
			}
			rhs.pushToStack(dates);		// this always pushs the last date read in to the stack
			lhs.get(comma);
		}
		lhs.getline(tempString, 3, '\n');
		int numAbsences = atoi(tempString);
		rhs.setAbsences(numAbsences);
	}
	return lhs;
}

fstream & operator << (fstream &lhs, Node &rhs)
{
	lhs << rhs.getRecordNum() << ',' << rhs.getIDNum() << ',' << '\"' << rhs.getName();
	lhs << '\"' << ',' << rhs.getEmail() << ',';
	if (rhs.getUnits() == 0) {
		lhs << "AU";			// auditing course
	}
	else {
		lhs << rhs.getUnits();
	}
	lhs << ',' << rhs.getProgram() << ',' << rhs.getLevel() << ',';
	if (rhs.getNumAbsences() == 0) {
		lhs << ',';
	}
	else {
		lhs << '\"';	// put opening double quote (indicates this is one cell)
		for (int i = 0; i < rhs.getNumAbsences(); ++i) {
			lhs << rhs.getAbsenceAtN(i);
			if (i + 1 != rhs.getNumAbsences()) {		// if not last absence, add comma to space the absences
				lhs << ',';
			}
			// by putting items in file in chronological order, I can push them onto the stack
			// in the correct order when I reload the file
		}
		lhs << '\"' << ',';	// put closing double quote (finishes the cell)
	}
	lhs << rhs.getNumAbsences();

	return lhs;
}

ostream & operator << (ostream &lhs, const Node &rhs)
{
	lhs << "Name: \t" << rhs.getName() << endl;
	lhs << "ID #: \t" << rhs.getIDNum() << endl;
	lhs << "Email: \t" << rhs.getEmail() << endl;
	lhs << "Level: \t" << rhs.getLevel() << endl;
	lhs << "Total Absences: " << rhs.getNumAbsences() << endl;
	lhs << "Most Recent Absence: " << rhs.getMostRecentAbsence() << endl;

	return lhs;
}