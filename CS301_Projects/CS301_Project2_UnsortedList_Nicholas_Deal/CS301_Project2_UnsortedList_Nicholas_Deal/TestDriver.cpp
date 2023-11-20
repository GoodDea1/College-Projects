#include "UnsortedType.hpp"

int main() {

	UnsortedType list;
	ofstream outputFile;

	outputFile.open("Output.txt", ios::out);

	//Test Case #1
	try {
		list.PutItem(2);
		list.PutItem(13);
		list.PutItem(3);
		list.PutItem(5);
		list.PutItem(8);
		list.PutItem(1);
		list.PutItem(11);
		list.PutItem(12);	//Already surpasses long int limits
		list.PutItem(6);
		list.PutItem(9);
		list.PutItem(4);
		list.PutItem(10);
		list.PutItem(14);
		list.PutItem(5);
		list.PutItem(3);
		list.PutItem(7);
		list.PutItem(15);
		list.PutItem(10);
	}//try
	catch (string stringException) {
		cout << stringException << endl;
	}//catch

	//Test Case #2
	cout << "The length of the current list is " << list.GetLength() << endl;

	//Test Case #3
	list.MakeEmpty();

	//Test Case #4
	list.PutItem(2);
	list.PutItem(13);
	list.PutItem(3);
	list.PutItem(5);

	list.ResetList();
	for (int i = 0; i < list.GetLength(); i++) {
		cout << list.GetNextItem() << endl;
	}//for
	cout << endl;

	//Test Case #5
	cout << "The position for number 3 is position " << list.GetItem(3) << "." << endl;

	//Test Case #6
	try {
		list.GetItem(4);
	}//try
	catch (string stringException) {
		cout << stringException << endl;
	}//catch
	
	//Test Case #7
	list.DeleteItem(3);
	list.ResetList();
	for (int i = 0; i < list.GetLength(); i++) {
		cout << list.GetNextItem() << endl;
	}//for
	cout << endl;

	//Test Case #8
	try {
		list.DeleteItem(7);
	}//try
	catch (string stringException) {
		cout << stringException << endl;
	}//catch

	//Test Case #9
	list.PrintList(outputFile);

	outputFile.close();

	return 0;
}//main