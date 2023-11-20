#include "LargeInteger.hpp"

int main() {

	LargeInteger<int> test;
	ofstream outFile;
	bool stop;
	int intInput;
	char charInput;
	stop = false;

	outFile.open("output.txt", ios::out);

	do {
		cout << "Please enter a number between 1 and 500 to find the factorial: ";
		cin >> intInput;
		if ((intInput < 1) || (intInput > 500)) {
			cout << endl;
			cout << "Warning: You must enter a number between 1 and 500." << endl << endl;
		}//if
		else {
		cout << endl << endl;
		test.Factorial(intInput, outFile);
		}//else
		cout << "Enter 'Y' if you would like to continue, enter 'N' if you don't: ";
		cin >> charInput;
		cout << endl;
		if ((charInput == 'n') || (charInput == 'N')) {
			stop = true;
		}//if
	} while (!stop);

	cout << "Program ending, have a nice day!" << endl;
	outFile.close();

	return 0;
}