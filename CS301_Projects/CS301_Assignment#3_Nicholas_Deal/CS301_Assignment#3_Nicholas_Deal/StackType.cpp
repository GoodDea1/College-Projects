#include "StackType.hpp"

//Constructor
StackType::StackType() {
	this->topPtr = NULL;
}//StackType

//Destructor
StackType::~StackType() {
	NodeType* tempPtr;
	while (topPtr != NULL) {
		tempPtr = topPtr;
		topPtr = topPtr->next;
		delete tempPtr;
	}//while
}//~StackType

bool StackType::IsEmpty() const{
//Function:       Returns true if there are no elements on the stack; false otherwise.
//Preconditions:  Stack has been initialized.
//Postconditions: Return true if topPtr is NULL; return false if it isn't.
	return (topPtr == NULL);
}//IsEmpty

bool StackType::IsFull() const{
//Function:       Returns true if there is no room for another char on the free store; false otherwise.
//Preconditions:  Stack has been initialized.
//Postconditions: Return true if there is no space in free store; return false if there is space.
	NodeType* location;
	try {
		location = new NodeType;
		delete location;
		return false;
	}//try
	catch (std::bad_alloc exception) {
		return true;
	}//catch
}//IsFull

void StackType::Push(char newChar) {
//Function:       Adds a char to the top of the stack.
//Preconditions:  Stack has been initialized.
//Postconditions: If stack is full, and exception is thrown;
//				  else newChar is at the top of the stack.
	if (this->IsFull()) {
		string stringException;
		stringException = "***Error: Stack is full. Pop stack to make space.***";
		throw stringException;
	}//if
	else {
		NodeType* location;
		location = new NodeType;
		location->info = newChar;
		location->next = topPtr;
		topPtr = location;
	}//else
}//Push

void StackType::Pop() {
//Function:       Removes top char from the stack.
//Preconditions:  Stack has been initialized.
//Postconditions: If stack is empty, an exception is thrown;
//				  else top element has been removed.
	if (this->IsEmpty()) {
		string stringException;
		stringException = "***Error: Stack is empty.***";
		throw stringException;
	}//if
	else {
		NodeType* tempPtr;
		tempPtr = topPtr;
		topPtr = topPtr->next;
		delete tempPtr;
	}//else
}//Pop

char StackType::Top() {
//Function:       Returns a copy of the top char in the stack.
//Preconditions:  Stack has been initialized.
//Postconditions: If stack is empty, an exception is thrown;
//				  else a copy of the top element is returned.
	if (this->IsEmpty()) {
		string stringException;
		stringException = "***Error: Stack is empty.***";
		throw stringException;
	}//if
	else {
		return this->topPtr->info;
	}//else
}//Top