#include "UnsortedType.hpp"

UnsortedType::UnsortedType() {
	this->info = 0;
	this->length = 0;
}//UnsortedType

//Function:       Initializes list to empty state
//Preconditions:  None
//Postconditions: List is empty.
void UnsortedType::MakeEmpty() {
	this->info = 0;
	this->length = 0;
	return;
}//MakeEmpty

//Function:		  Determines whether list is full.
//Preconditions:  List has been initialized.
//Postconditions: Function value = (list is full)
bool UnsortedType::IsFull() const {
	return (this->length == MAX_ITEMS);		//return true if the list is full
}//IsFull

//Function:		  Determines the number of elements in list
//Preconditions:  List has been initialized
//Postconditions: Function value = number of elements in list
int UnsortedType::GetLength() const {
	return this->length;
}//GetLength

//Function:       Returns the position of the searched element (if it exists in the list).
//Preconditions:  List has been initialized.
//				  Number is initialized.
//Postconditions: If there is an element someItem whose key matches item's key, then found = true
//				  and copy of someItem is returned; otherwise found = false and item is returned.
//				  List is unchanged.
int UnsortedType::GetItem(long number) {
	bool found;
	found = false;
	int location = 0;
	long temp = this->info;
	long temp2 = temp;
	long remainder = 0;
	while ((location < this->length) && (found == false)) {
		remainder = temp % 16;
		if (remainder == 0) {
			temp /= 16;
		}//if
		else if (remainder > 0) {
			if (remainder == number) {
				found = true;
				return location;
			}//if
			else {
				temp = temp2 - (remainder * pow(16, location));
				temp2 = temp;
				location++;
				remainder = 0;
			}//else
		}//else if
		else {}
	}//while
	if (found == false) {
		string stringException = "***Error: Couldn't find the integer you were looking for.***";
		throw stringException;
		return -1;
	}//if
	else {}
}//GetItem

//Function:       Puts item to list.
//Preconditions:  List has been initialized.
//				  List is not full.
//				  Item is not in list.
//Postconditions: Item is in list.
void UnsortedType::PutItem(long number) {
	if (this->IsFull()) {
		string stringException = "***Error: List is full. Can't put any more integers.***";
		throw stringException;
		return;
	}//if
	else {
		this->info += (number * pow(16, this->GetLength()));
		this->length++;
		return;
	}//else
}//PutItem

//Function:       Deletes the element whose key matches item's key.
//Preconditions:  List has been initialized.
//				  Key member of item is initialized.
//				  One and only one element in list has a key matching items key.
//Postconditions: No element in list has a key matching item's key.
void UnsortedType::DeleteItem(long number) {
	bool found;
	found = false;
	int location = 0;
	long temp = this->info;
	long temp2 = temp;
	long remainder = 0;
	while ((location < this->length) && (found == false)) {
		remainder = temp % 16;
		if (remainder == 0) {
			temp /= 16;
		}//if
		else if (remainder > 0) {
			//If the element is found, remove it from info
			if (remainder == number) {
				found = true;
				this->info -= (number * pow(16, location));
				temp = temp2 - (remainder * pow(16, location));
				temp2 = temp;
				location++;
				remainder = 0;
				//Move the following elements forward 1.
				while (location < this->length) {
					remainder = temp % 16;
					if (remainder == 0) {
						temp /= 16;
					}//if
					else if (remainder > 0) {
						this->info += (remainder * pow(16, location - 1));
						this->info -= (remainder * pow(16, location));
						temp = temp2 - (remainder * pow(16, location));
						temp2 = temp;
						location++;
						remainder = 0;
					}//else if
				}//while
				this->length--;
				return;
			}//if
			else {
				temp = temp2 - (remainder * pow(16, location));
				temp2 = temp;
				location++;
				remainder = 0;
			}//else
		}//else if
		else {}
	}//while
	if (found == false) {
		string stringException = "***Error: Couldn't find the integer you were deleting.***";
		throw stringException;
	}//if
	else {}
	return;
}//DeleteItem

//Function:       Initialized current position for an iteration through the list.
//Preconditions:  List has been initialized.
//Postconditions: Current position is prior to list.
void UnsortedType::ResetList() {
	this->currentPos = -1;
	return;
}//ResetList

//Function:       Gets the next element in list.
//Preconditions:  List has been initialized.
//				  Current position is defined.
//				  Element at current position is not last in list.
//Postconditions: Current position is updated to next position.
//				  Returns a copy of element at current position.
long UnsortedType::GetNextItem() {
	this->currentPos++;
	int location = 0;
	long remainder = 0;
	long temp = this->info;
	long temp2 = temp;
	while (location <= this->currentPos) {
		//If at current position, find and return the remainer
		if (location == this->currentPos) {
			remainder = temp % 16;
			if (remainder == 0) {
				temp /= 16;
			}//if
			else if (remainder > 0) {
				return remainder;
			}//else if
		}//if
		//If not at current position, remove current element and move on to the next element.
		else {
			remainder = temp % 16;
			if (remainder == 0) {
				temp /= 16;
			}//if
			else if (remainder > 0) {
				temp = temp2 - (remainder * pow(16, location));
				temp2 = temp;
				remainder = 0;
				location++;
			}//else if
		}//else
	}//while
}//GetNextItem

//Function:       Prints the list onto an output file.
//Preconditions:  List has been initialized.
//				  Output file is initialized
//Postconditions: Output file contains elements of list with the same order.
//				  List remains unchanged.
void UnsortedType::PrintList(ofstream &OutFile) {
	this->ResetList();
	for (int i = 0; i < this->length; i++) {
		OutFile << this->GetNextItem() << endl;
	}//for
	this->ResetList();
}//PrintList