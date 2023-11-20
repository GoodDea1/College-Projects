//============================================================================
// Name        : CS1_Password_Verifier_Project.cpp
// Author      : Nicholas Deal
// Version     :
// Copyright   : Make sure you bring the money if you want to use this
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

bool verifyPassword(char password[], int MAX_LENGTH) {
	bool passwordCheck = true;
	int counter = 0;
	int counter2 = 0;
	int counter3 = 0;
	int counter4 = 0;
	int counter5 = 0;
	bool hasUpperCase = true;
	bool hasLowerCase = true;
	bool hasDigits = true;
	bool hasSpecialCharacters = true;

	cout << "Verifying password, please wait." << endl;

	//Checks to see if the password is longer than 6 characters
	while (password[counter] != '\0') {
		counter++;
		if (counter == MAX_LENGTH) {
			break;
		}//if
	}//while
	if (counter < 6) {
		cout << "***Error: Password must be at least six characters long.***" << endl;
	}//if
	else{}

	//Checks to see if the password has an uppercase character
	while (password[counter2] != '\0') {
		if (isupper(password[counter2])) {
			hasUpperCase = true;
			break;
		}//if
		else {
			counter2++;
		}//else
	}//while
	if (hasUpperCase == false) {
		cout << "***Error: Password must have at least one uppercase character.***" << endl;
	}//if
	else{}

	//Checks to see if the password has an lower character
	while (password[counter3] != '\0') {
		if (islower(password[counter3])) {
			hasLowerCase = true;
			break;
		}//if
		else {
			counter3++;
		}//else
	}//while
	if (hasLowerCase == false) {
		cout << "***Error: Password must have at least one lowercase character.***" << endl;
	}//if
	else{}

	//Checks to see if the password has a number in it
	while (password[counter4] != '\0') {
		if (isdigit(password[counter4])) {
			hasDigits = true;
			break;
		}//if
		else {
			counter4++;
		}//else
	}//while
	if (hasDigits == false) {
		cout << "***Error: Password must have at least one number.***" << endl;
	}//if
	else{}

	//Checks to see if the password has a special character
	while (password[counter5] != '\0') {
		if (password[counter5] == '$') {
			hasSpecialCharacters = true;
			break;
		}//else if
		else if (password[counter5] == '%') {
			hasSpecialCharacters = true;
			break;
		}//else if
		else if (password[counter5] == '!') {
			hasSpecialCharacters = true;
			break;
		}//else if
		else if (password[counter5] == '&') {
			hasSpecialCharacters = true;
			break;
		}//else if
		else if (password[counter5] == '@') {
			hasSpecialCharacters = true;
			break;
		}//else if
		else {
			counter5++;
		}//else
	}//while
	if (hasSpecialCharacters == false) {
		cout << "***Error: Password must have at least one of the listed characters ($, %, !, &, @).***" << endl;
	}//if
	else {}

	if (counter >= 6 && hasUpperCase == true && hasLowerCase == true && hasDigits == true && hasSpecialCharacters == true) {
		passwordCheck = true;
	}//if
	else {
		passwordCheck = false;
	}//else
	return passwordCheck;
}//verifyPassword

int main() {

	bool passwordStatus = true;
	const int MAX_LENGTH = 50;
	char password[MAX_LENGTH];

	cout << "Please enter a password: ";
	cin.getline(password, MAX_LENGTH);

	passwordStatus = verifyPassword(password, MAX_LENGTH);

	cout << passwordStatus << endl;

	while (true) {
		if (passwordStatus == false) {
			cout << "Please re-enter a password: ";
			cin.getline(password, MAX_LENGTH);
			passwordStatus = verifyPassword(password, MAX_LENGTH);
		}//if
		else {
			cout << "Password is verified!" << endl;
			break;
		}//else
	}//while

	cout << "Program ending, have a nice day!" << endl; // prints !!!Hello World!!!
	return 0;
}
