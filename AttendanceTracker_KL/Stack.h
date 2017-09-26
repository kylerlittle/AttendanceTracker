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

#define NOT_FOUND -1			// since this is an invalid index

using std::cout;
using std::cin;
using std::endl;
using std::string;

template <class T>
class Stack
{
public:
	Stack(int newSize = 0);

	// Overloaded Assignment
	Stack<T> & operator = (Stack<T> &rhs);
	~Stack();

	int getSize() const;

	bool push(T &newItem);
	bool pop(T &poppedItem);
	bool peek(T &item) const;

	bool isEmpty() const;
	bool isFull() const;

	// this will be used to write the stack to the file; although this technically
	// breaks the container rules of a stack, it would waste a lot of memory and time
	// to use pushs and pops for all of these operations
	T returnItemAtN(int N) const;

	// simply prints the stack
	// (this will eventually be used so that the user can see all of the absences
	// and type in the absence to remove it)
	void displayStack();

	// eventually the user will enter an absence that needs to be removed
	// this function returns the index which that item is located at; if it
	// is not found, -1 is returned
	int searchStack(T searchItem);    // return the index of Found Item

	// Remove item at index; perform linear shift. Decrease mSize.
	// this function does the above SO LONG AS the index entered is not -1,
	// indicating that the item was not, in fact, found
	bool removeItem(int index);

private:
	int mSize; // represents the current number of items in the stack
	int mMaxSize; // must not exceed the max size of our allocated array
	T *mTop; // will point to contigous memory on the heap (an array)
};

template <class T>
Stack<T>::Stack(int newSize)
{
	mSize = newSize; // this can also be used as the index to the top of the stack
	mMaxSize = 30;
	mTop = new T[30]; // allocating an array of 30 items of type T on the heap
}

template <class T>
Stack<T> & Stack<T>::operator = (Stack<T> &rhs)
{
	mTop = new T[30];   // create a new array
	// now, copy entries from one to the others
	for (int i = 0; i < rhs.getSize(); ++i) {
		mTop[i] = rhs.returnItemAtN(i);
	}
	mSize = rhs.getSize();
	mMaxSize = 30;

	return *this;
}

template <class T>
Stack<T>::~Stack()
{
	delete[] mTop; // this is how we free up an array on the heap in C++
}

template <class T>
int Stack<T>::getSize() const
{
	return this->mSize;
}

// Places the newItem at the top of the stack
template <class T>
bool Stack<T>::push(T &newItem)
{
	bool result = false;

	if (!(this->isFull())) {   // if there is room to insert
		mTop[mSize] = newItem;
		++mSize;
		result = true;
	}

	return result;
}

// In this implementation you will apply defensive design. You must check to 
// see if the stack is empty or not before you pop. Places the popped item in 
// the parameter referred to as "poppedItem". Returns true if the item was popped; false
// otherwise.
template <class T>
bool Stack<T>::pop(T &poppedItem)
{
	bool result = false;

	if (!isEmpty()) {
		poppedItem = mTop[mSize - 1];
		cout << "popped item: " << poppedItem << endl;
		--mSize;
		result = true;
	}

	return result;
}

// In this implementation you will apply defensive design. You must check to 
// see if the stack is empty or not before you peek. Places the item at the top of the
// stack in the parameter referred to as "item". Returns true if there
// is an item at the top; false otherwise.
template <class T>
bool Stack<T>::peek(T &item) const
{
	bool result = false;

	if (!isEmpty()) {
		item = mTop[mSize - 1];
		result = true;
	}

	return result;
}

// Returns true if the stack is empty; false otherwise
template <class T>
bool Stack<T>::isEmpty() const
{
	bool result = false;
	if (this->mSize == 0) {
		result = true;
	}
	return result;
}

template <class T>
bool Stack<T>::isFull() const
{
	bool result = false;
	if (this->mSize == this->mMaxSize) {
		result = true;
	}
	return result;
}

template <class T>
T Stack<T>::returnItemAtN(int N) const
{
	return mTop[N];
}

template <class T>
void Stack<T>::displayStack()
{
	for (int i = 0; i < this->getSize(); ++i) {
		cout << mTop[i] << endl;
	}
}

template <class T>
int Stack<T>::searchStack(T searchItem)
{
	int i = 0;
	bool found = false;

	while (i < this->getSize() && !found) {
		if (mTop[i++] == searchItem) {
			found = true;
		}
	}
	if (!found) {
		i = NOT_FOUND;    // i.e. item was not found
	}
	return i;
}

template <class T>
bool Stack<T>::removeItem(int index)
{
	bool result = false;
	if (index == NOT_FOUND) {		// item was not found
		cout << "Item was not found!" << endl;
	}
	else {
		cout << "Item was removed successfully!" << endl;
		result = true;
		for (int i = index; i < this->getSize() - 1; ++i) {   // mSize - 1 since we're deleting 1 item
			mTop[i] = mTop[i + 1];
		}
		--mSize;
	}
	return result;
}