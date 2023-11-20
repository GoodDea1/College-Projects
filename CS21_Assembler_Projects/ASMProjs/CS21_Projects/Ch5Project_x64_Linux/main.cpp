#include <iostream>
#include "myFuncs.h"

using namespace std;

int main() {
	
	long long int array1[] = {1, 2, 3, 4};
	long long int array2[] = {5, 6, 7, 8};
	
	cout << "Here are the values of the first array: ";
	for (int i = 0; i<4; i++) {
		cout << array1[i] << " ";
	}//for
	cout << endl;
	
	cout << "Here are the values of the second array: ";
	for (int i = 0; i<4; i++) {
		cout << array2[i] << " ";
	}//for
	cout << endl << endl;
	
	cout << "Testing swapArrays function..." << endl;
	swapArrays(array1, array2, 4);
	cout << "First array: ";
	for (int i = 0; i<4; i++) {
		cout << array1[i] << " ";
	}//for
	cout << endl;
	
	cout << "Second array: ";
	for (int i = 0; i<4; i++) {
		cout << array2[i] << " ";
	}//for
	cout << endl << endl;
	
	cout << "Testing addArray function..." << endl;
	cout << "First array: " << addArray(array1, 4) << endl;	
	cout << "Second array: " << addArray(array2, 4) << endl << endl;

	
	cout << "Testing addTwo function..." << endl;
	cout << "Adding 10 and 20, result shows: " << addTwo(10, 20) << endl << endl;
	
	cout << "Program ending, have a nice day!" << endl;
	return 0;
}//main
