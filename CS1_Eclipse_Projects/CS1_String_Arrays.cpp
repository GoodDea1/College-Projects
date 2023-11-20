//============================================================================
// Name        : CS1_String_Arrays.cpp
// Author      : Nicholas Deal
// Version     :
// Copyright   : Make sure you bring the money if you want to use this
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int main() {

	const int ARRAYSIZE = 10;
	string Names[ARRAYSIZE];				//0 - 9
	string userInput;
	int lastIndex = -1;

	for (int i=0; i<ARRAYSIZE; i++) {
		cout << "Please enter a name: ";
		getline(cin, userInput);
		if (userInput == "-999") {			//The user wants to leave, so let's leave
			break;
		}//if
		else {
			Names[i] = userInput;
			lastIndex++;					//We added an item, so increment
		}//else
	}//for

	cout << "Here is the array: " << endl;
	for (int i=0; i<=lastIndex; i++) {
		cout << i << ": " << Names[i] << endl;
	}//for

	lastIndex = -1;

	cout << "Here is the array after setting lastIndex to -1" << endl;
	for (int i=0; i<=lastIndex; i++) {
		cout << i << ": " << Names[i] << endl;
	}//for

	cout << "Program ending, have a nice day!" << endl; // prints !!!Hello World!!!
	return 0;
}
