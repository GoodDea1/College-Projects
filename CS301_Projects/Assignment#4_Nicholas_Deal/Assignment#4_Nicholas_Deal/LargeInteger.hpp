#pragma once
#include <iostream>
#include <fstream>

using namespace std;

template<typename Type>
struct DoubleNode {
//The structure used to build a doubly linked list.
	Type info;			//Node holds a type of integer
	DoubleNode* prev;	//Points to the previous node
	DoubleNode* next;	//Points to the next node
};

template<class Type>
class LargeInteger
{
public:
	LargeInteger();
	~LargeInteger();
	void Factorial(Type num, ofstream& outFile);
	void MakeEmpty();
	bool IsFull() const;
	bool IsEmpty() const;
private:
	DoubleNode<Type>* front;	//Points to the first node of the doubly linked list.
	DoubleNode<Type>* rear;		//Points to the last node of the doubly linked list.
};

template<class Type>
LargeInteger<Type>::LargeInteger() {
//Constructor
	this->front = NULL;
	this->rear = NULL;
}//Constructor

template<class Type>
LargeInteger<Type>::~LargeInteger() {
//Destructor
	this->MakeEmpty();
}//Destructor

template<class Type>
void LargeInteger<Type>::Factorial(Type num, ofstream &outFile) {
//Function:       Calculates the factorial of the user-given number.
//Preconditions:  Doubly linked list is initialized.
//				  A number and file are inputted by client.
//Postconditions: Outputs the resulting factorial onto the console and output file.
	DoubleNode<Type>* location;
	this->MakeEmpty();
	if (this->IsEmpty()) {
		front = new DoubleNode<Type>;
		front->info = 1;
		front->next = NULL;
		front->prev = NULL;
		rear = front;
	}//if
	for (int i = 1; i <= num; i++) {
		location = front;
		//Process the nodes in the do while loop
		while (location != NULL) {
			location->info = location->info * i;
			location = location->next;
		}//while
		location = front;
		while (location != NULL) {
			if (location->info > 999) {
				if (location == this->rear) {
					if (!this->IsFull()) {
						location->next = new DoubleNode<Type>;
						location->next->prev = location;
						location->next->next = NULL;
						this->rear = location->next;
						location->next->info = 0;
						location->next->info += (location->info / 1000);
						location->info = location->info % 1000;
						location = location->next;
					}//if
					else {
						cout << "***Error: Not enough space.***" << endl;
					}//else
				}//if
				else {
					location->next->info += (location->info / 1000);
					location->info = location->info % 1000;
					location = location->next;
				}//else

			}//if
			else {
				location = location->next;
			}//else
		}//while
	}//for
	location = rear;
	cout << num << "! = " << location->info;
	outFile << num << "! = " << location->info;
	location = location->prev;
	while (location != NULL) {
		if (location->info < 10) {
			cout << ",00" << location->info;
			outFile << ",00" << location->info;
			location = location->prev;
		}//if
		else if ((location->info >= 10) && (location->info < 100)) {
			cout << ",0" << location->info;
			outFile << ",0" << location->info;
			location = location->prev;
		}//else if
		else {
			cout << "," << location->info;
			outFile << "," << location->info;
			location = location->prev;
		}//else	
	}//while
	cout << endl << endl;
	outFile << endl << endl;
}//factorial

template<class Type>
void LargeInteger<Type>::MakeEmpty() {
//Function:       Clears the doubly linked list
//Preconditions:  Doubly linked list is initialized.
//Postconditions: Pointers of the doubly linked list points to NULL.
	DoubleNode<Type>* tempPtr;
	while (this->front != NULL) {
		tempPtr = this->front;
		this->front = this->front->next;
		delete tempPtr;
	}//while
}//MakeEmpty

template<class Type>
bool LargeInteger<Type>::IsFull() const {
//Function:       Determines if the doubly linked list is full.
//Preconditions:  Doubly linked list is initialized.
//Postconditions: Returns true if there is no space in the free store, otherwise return false.
	DoubleNode<Type>* temp;
	temp = new DoubleNode<Type>;
	if (temp == NULL) {
		return true;
	}//if
	else {
		delete temp;
		return false;
	}//else
}//IsFull

template<class Type>
bool LargeInteger<Type>::IsEmpty() const {
//Function:       Determines if the doubly linked list is empty.
//Preconditions:  Doubly linked list is initialized.
//Postconditions: Returns true if front points to NULL, otherwise return false.
	return (front == NULL);
}//IsEmpty