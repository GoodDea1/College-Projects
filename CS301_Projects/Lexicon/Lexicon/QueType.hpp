#pragma once
#include <iostream>

using namespace std;

template<class T>
class QueType {
public:
	QueType();
	QueType(int max);
	~QueType();
	void MakeEmpty();
	bool IsEmpty() const;
	bool IsFull() const;
	void Enqueue(T newItem);
	void Dequeue(T& item);
private:
	int front;
	int rear;
	T* items;
	int maxQue;
};

template<class T>
QueType<T>::QueType() {
	//Post-Conditions:	maxQue, front, and rear have been initialized.
	//					The array to hold the queue elements has been dynamically
	//					allocated.
	this->maxQue = 501;
	this->front = this->maxQue - 1;
	this->rear = this->maxQue - 1;
	this->items = new T[this->maxQue];
}//Default constructor

template<class T>
QueType<T>::QueType(int max) {
	//Post-Conditions:	maxQue, front, and rear have been initialized.
	//					The array to hold the queue elements has been dynamically
	//					allocated.
	this->maxQue = max + 1;
	this->front = this->maxQue - 1;
	this->rear = this->maxQue - 1;
	this->items = new T[this->maxQue];
}//Paramaterized constructor

template<class T>
QueType<T>::~QueType() {
	delete[] items;
}//Destructor

template<class T>
void QueType<T>::MakeEmpty() {
	//Function: Initializes the queue to an empty state.
	//Preconditions: None.
	//Postconditions: Queue is empty.
	this->front = this->maxQue - 1;
	this->rear = this->maxQue - 1;
}//MakeEmpty

template<class T>
bool QueType<T>::IsEmpty() const {
	//Function: Returns true if the queue is empty; false otherwise.
	//Preconditions: Queue has been initialized.
	//Postconditions: Function value = (queue is empty).
	return (rear == front);
}//IsEmpty

template<class T>
bool QueType<T>::IsFull() const {
	//Function: Returns true if the queue is full; false otherwise.
	//Preconditions: Queue has been initialized.
	//Postconditions: Function value = (queue is full).
	return (((this->rear + 1) % this->maxQue) == front);
}//IsFull

template<class T>
void QueType<T>::Enqueue(T newItem) {
	//Function: Adds newItem to the rear of the queue.
	//Preconditions: Queue has been initialized.
	//Postconditions: If (queue if full), an error message is sent to console, else newItem
	//				  is at rear of queue.
	if (this->IsFull()) {
		cout << "***Error: Queue is full.***" << endl;
	}//if
	else {
		this->rear = (this->rear + 1) % this->maxQue;
		this->items[this->rear] = newItem;
	}//else
}//Enqueue

template<class T>
void QueType<T>::Dequeue(T& item) {
	//Function: Removes front item from the queue and returns in in item.
	//Preconditions: Queue has been initialized.
	//Postconditions: If (queue is empty), an error message is sent to console, and
	//				  item is undefined, else front element has been removed from queue
	//				  and item is a copy of removed element.
	if (this->IsEmpty()) {
		cout << "***Error: Queue is empty.***" << endl;
	}//if
	else {
		this->front = (this->front + 1) % this->maxQue;
		item = this->items[this->front];
	}//else
}//Dequeue