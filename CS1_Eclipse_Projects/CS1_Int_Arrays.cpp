//============================================================================
// Name        : CS1_Int_Arrays.cpp
// Author      : Nicholas Deal
// Version     :
// Copyright   : Make sure you bring the money if you want to use this
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <climits>
using namespace std;

void clearCIN(void) {
	cin.clear();
	cin.ignore(INT_MAX, '\n');
}

int main() {

	const int DONUTARRAYSIZE = 30;
	int DonutCount[DONUTARRAYSIZE];
	int lastDonutIndex = -1;
	int intInput = 0;
	int arraySum = 0;

	for (int i=0; i<DONUTARRAYSIZE; i++) {
		cout << "Please enter the donuts for " << i << ": ";
		cin >> intInput;
		clearCIN();
		if (intInput == -999) {
			break;
		}//if
		else {
			DonutCount[i] = intInput;
			lastDonutIndex++;
		}//else
	}//for

	for (int i=0; i<=lastDonutIndex; i++) {
		cout << i << ": " << DonutCount[i] << endl;
		arraySum += DonutCount[i];
	}//for

	cout << "The average for this array is: " << arraySum/(lastDonutIndex+1) << endl;

	cout << "Program ending, have a nice day!" << endl; // prints !!!Hello World!!!
	return 0;
}
