#include "MatrixType.hpp"

enum Input {
	GetNewMatrix,
	AddMatrices,
	SubMatrices,
	MultiplyMatrices,
	PrintMatrix,
	Quit
};

istream& operator>>(istream& is, Input& input) {
	string option;
	is >> option;
	
	if (option == "GetNewMatrix") {
		input = GetNewMatrix;
	}//if
	else if (option == "AddMatrices") {
		input = AddMatrices;
	}//else if
	else if (option == "SubMatrices") {
		input = SubMatrices;
	}//else if
	else if (option == "MultiplyMatrices") {
		input = MultiplyMatrices;
	}//else if
	else if (option == "PrintMatrix") {
		input = PrintMatrix;
	}//else if
	else if (option == "Quit") {
		input = Quit;
	}//else if
	else {}

	return is;

}

int main() {

	Input userInput;
	char charInput;
	int rowInput;
	int colInput;
	int valInput;
	ofstream DataOut;
	MatrixType matrixA;
	MatrixType matrixB;
	MatrixType resultMatrix;

	//Open the output file
	DataOut.open("DataOut.txt", ios::out);

	do {
		//The menu
		cout << "Please type one of the following into the console:" << endl << endl;
		cout << "GetNewMatrix" << endl;
		cout << "AddMatrices" << endl;
		cout << "SubMatrices" << endl;
		cout << "MultiplyMatrices" << endl;
		cout << "PrintMatrix" << endl;
		cout << "Quit" << endl << endl;
		cin >> userInput;
		cout << endl;

		switch (userInput) {
		case GetNewMatrix:
			//Choose a matrix
			cout << "Type 'A' or 'B' to create either matrix A or matrix B: ";
			cin >> charInput;
			cout << endl;
			if (charInput == 'a' || (charInput == 'A')) {
				//Get number of rows and columns for matrix A
				matrixA.MakeEmpty();
				cout << "Please enter the number of rows for matrix A: ";
				cin >> rowInput;
				cout << endl;
				cout << "Please enter the number of columns for matrix A: ";
				cin >> colInput;
				cout << endl;
				try {
					matrixA.SetSize(rowInput, colInput);
					//Get values for each index of matrix A
					for (int i = 0; i < rowInput; i++) {
						for (int j = 0; j < colInput; j++) {
							cout << "Please enter an integer for row " << (i + 1) << " column " << (j + 1) << " of matrix A: ";
							cin >> valInput;
							matrixA.StoreItem(valInput, i, j);
							cout << endl;
						}//for
					}//for
					cout << "Matrix A generated." << endl << endl;
				}//try
				catch (string stringException) {
					cout << stringException << endl << endl;
				}//catch
			}//if
			else if ((charInput == 'b') || (charInput == 'B')) {
				//Get number of rows and columns for matrix B
				matrixB.MakeEmpty();
				cout << "Please enter the number of rows for matrix B: ";
				cin >> rowInput;
				cout << endl;
				cout << "Please enter the number of columns for matrix B: ";
				cin >> colInput;
				cout << endl;
				try {
					matrixB.SetSize(rowInput, colInput);
					//Get values for each index of matrix B
					for (int i = 0; i < rowInput; i++) {
						for (int j = 0; j < colInput; j++) {
							cout << "Please enter an integer for row " << (i + 1) << " column " << (j + 1) << " of matrix B: ";
							cin >> valInput;
							matrixB.StoreItem(valInput, i, j);
							cout << endl;
						}//for
					}//for
					cout << "Matrix B generated." << endl << endl;
				}//try
				catch (string stringException) {
					cout << stringException << endl << endl;
				}//catch
			}//else if
			else {
				cout << "***Error: Invalid option.***" << endl << endl;
			}//else
			break;

		case AddMatrices:
			resultMatrix.MakeEmpty();
			try {
				if (matrixA.AddSubCompatible(matrixB)) {
					matrixA.Add(matrixB, resultMatrix);
					cout << "Matrices added, result stored." << endl << endl;
				}//if
				else {}
			}//try
			catch (string exceptionString) {
				cout << exceptionString << endl << endl;
			}//catch
			break;

		case SubMatrices:
			resultMatrix.MakeEmpty();
			try {
				if (matrixA.AddSubCompatible(matrixB)) {
					matrixA.Sub(matrixB, resultMatrix);
					cout << "Matrices subtracted, result stored." << endl << endl;
				}//if
				else {}
			}//try
			catch (string exceptionString) {
				cout << exceptionString << endl << endl;
			}//catch
			break;

		case MultiplyMatrices:
			resultMatrix.MakeEmpty();
			try {
				if (matrixA.MultCompatible(matrixB)) {
					matrixA.Mult(matrixB, resultMatrix);
					cout << "Matrices multiplied, result stored." << endl << endl;
				}//if
				else {}
			}//try
			catch (string exceptionString) {
				cout << exceptionString << endl << endl;
			}//catch
			break;

		case PrintMatrix:
			cout << "Type 'A' or 'B' to print either matrix A or matrix B. Otherwise press any other key to print the result matrix: ";
			cin >> charInput;
			cout << endl;
			if (charInput == 'a' || (charInput == 'A')) {
				matrixA.Print(DataOut);
				cout << "Matrix A printed." << endl << endl;
			}//if
			else if ((charInput == 'b') || (charInput == 'B')) {
				matrixB.Print(DataOut);
				cout << "Matrix B printed." << endl << endl;
			}//else if
			else {
				resultMatrix.Print(DataOut);
				cout << "Result printed." << endl << endl;
			}//else
			break;

		case Quit:
			matrixA.MakeEmpty();
			matrixB.MakeEmpty();
			resultMatrix.MakeEmpty();
			cout << "Ending program..." << endl;
			break;

		default:
			cout << "***Error: You must type one of the displayed options into the console. Please try again.***" << endl << endl;
		}//switch
	}while (userInput != Quit);
	DataOut.close();
	return 0;
}//main