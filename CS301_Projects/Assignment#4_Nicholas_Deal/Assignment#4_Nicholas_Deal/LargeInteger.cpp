//#include "LargeInteger.hpp"

//template<class Type> 
//LargeInteger<Type>::LargeInteger() {
//	this->front = NULL;
//	this->rear = NULL;
//}//Constructor
//
//template<class Type> 
//LargeInteger<Type>::~LargeInteger() {
//	this->MakeEmpty();
//}//Destructor
//
//template<class Type>
//void LargeInteger<Type>::Factorial(Type num) {
//	DoubleNode* location;
//	DoubleNode* partialProduct;
//	DoubleNode* productLocation;
//	this->MakeEmpty();
//	if (this->IsEmpty()) {
//		front = new DoubleNode;
//		front->info = 1;
//	}//if
//	for (int i = 1; i <= num; i++) {
//		if (i < 10) {
//			location = front;
//			while (location != NULL) {
//				if (location->info > 999) {
//					if (location->next == NULL) {
//						location->next = new DoubleNode;
//						this->rear = location->next;
//						location->next->info = 0;
//						location->next->info += (location->info / 1000);
//					}//if
//					else {
//						location->next->info += (location->info / 1000);
//					}//else
//				}//if
//				else {
//					location->info = location->info * i;
//					if (location->info > 999) {
//						if (location->next == NULL) {
//							location->next = new DoubleNode;
//							this->rear = location->next;
//							location->next->info = 0;
//							location->next->info += (location->info / 1000);
//							location = NULL;
//						}//if
//						else {
//							location->next->info += (location->info / 1000);
//							location = location->next;
//						}//else
//					}//if
//					else {
//						location = location->next;
//					}//else
//				}//else
//			}//while
//		}//if
//		else if ((i >= 10) && (i < 100)) {
//
//		}//else if
//		else if (i > 100) {
//
//		}//else if
//	}//for
//}//factorial
//
//template<class Type>
//void LargeInteger<Type>::MakeEmpty() {
//	DoubleNode* tempPtr;
//	while (this->front != NULL) {
//		tempPtr = this->front;
//		this->front = this->front->next;
//		delete tempPtr;
//	}//while
//}//MakeEmpty
//
//template<class Type>
//bool LargeInteger<Type>::IsFull() const{
//	DoubleNode* temp;
//	temp = new DoubleNode;
//	if (temp == NULL) {
//		return true;
//	}//if
//	else {
//		delete temp;
//		return false;
//	}//else
//}//IsFull
//
//template<class Type>
//bool LargeInteger<Type>::IsEmpty() const{
//	return (front == NULL);
//}//IsEmpty