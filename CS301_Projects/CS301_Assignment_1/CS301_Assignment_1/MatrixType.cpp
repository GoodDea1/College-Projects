#include "MatrixType.hpp"

MatrixType::MatrixType () {

}//MatrixType

//Function:        Sets the values of the matrix and numRows and numCols to 0.
//Pre-conditions:  None
//Post-conditions: The values inside the matrix will all be set to 0.
//				   The variables numRows and numCols will be set to 0 also.
void MatrixType::MakeEmpty() {
	for (int i = 0; i < this->numRows; i++) {
		for (int j = 0; j < this->numCols; j++) {
			this->values[i][j] = 0;
		}//for
	}//for
	this->numRows = 0;
	this->numCols = 0;
	return;
}//MakeEmpty

//Function:		   Sets the size of the matrix.
//Pre-conditions:  2 integers are required.
//Post-conditions: The numRows and numCols variables for this MatrixType will be set to an integer.
//				   If either integer is less than 0 or greater than 10, then an exception is thrown.
void MatrixType::SetSize (int rowsSize, int colSize) {
	if ((rowsSize > 0) and (rowsSize <= 10)) {
		this->numRows = rowsSize;
	}//if
	else {
		string exceptionString = "***Error: Invalid number of rows***";
		throw exceptionString;
		return;
	}//else
	if ((colSize > 0) and (colSize <= 10)) {
		this->numCols = colSize;
	}//if
	else {
		string exceptionString = "***Error: Invalid number of columns***";
		throw exceptionString;
		return;
	}//else
	return;
}//SetSize

//Function:		   Stores a value in a matrix index.
//Pre-conditions:  3 integers are required. 
//				   The row and col integers must be greater than 0 and less than or equal to 10.
//Post-conditions: The item integer will be stored inside one of the indexes inside the values matrix based
//				   on the row and col integers.
void MatrixType::StoreItem (int item, int row, int col) {
	this->values[row][col] = item;
	return;
}//StoreItem

//Function:		   Adds 2 matrices together and stores the result in another matrix. 
//Pre-conditions:  2 additional MatrixType objects are required.
//				   The numRows and numCols variables of the first operand must equal to the numRows and numCols variables
//				   of otherOperand.
//Post-conditions: The result object will be set to the same size as the other 2 MatrixType objects.
//				   Each index of the result's values matrix will equal to the sum of the first and second operand in the
//				   same index position.
void MatrixType::Add (MatrixType otherOperand, MatrixType& result) {
	result.SetSize(this->numRows, this->numCols);
	for (int i = 0; i < this->numRows; i++) {
		for (int j = 0; j < this->numCols; j++) {
			result.values[i][j] = this->values[i][j] + otherOperand.values[i][j];
		}//for
	}//for
	return;
}//Add

//Function:		   Subtracts 2 matrices from each other and stores the result in another matrix. 
//Pre-conditions:  2 additional MatrixType objects are required.
//				   The numRows and numCols variables of the first operand must equal to the numRows and numCols variables
//				   of otherOperand.
//Post-conditions: The result object will be set to the same size as the other 2 MatrixType objects.
//				   Each index of result's values matrix will equal the difference of the first and second operand in the
//				   same index position.
void MatrixType::Sub (MatrixType otherOperand, MatrixType& result) {
	result.SetSize(this->numRows, this->numCols);
	for (int i = 0; i < this->numRows; i++) {
		for (int j = 0; j < this->numCols; j++) {
			result.values[i][j] = this->values[i][j] - otherOperand.values[i][j];
		}//for
	}//for
	return;
}//Sub

//Function:		   Multiplies 2 matrices and stores the result in another matrix.
//Pre-conditions:  2 additional MatrixType objects are required.
//				   The numCols variable of the first operand must equal to the numRows variable of otherOperand.
//Post-conditions: The numRows of the result object will be set to equal numRows of the first operand.
//				   The numCols of the result object will be set to equal numCols of otherOperand.
//				   The product of the first operand and otherOperand will be stored in result.
void MatrixType::Mult (MatrixType otherOperand, MatrixType& result) {
	result.SetSize(this->numRows, otherOperand.numCols);
	int temp = 0;
	for (int i = 0; i < this->numRows; i++) {
		for (int j = 0; j < otherOperand.numCols; j++) {
			//The number of columns in the other operand should equal to the number of rows of the first operand
			for (int k = 0; k < otherOperand.numRows; k++) {
				temp += this->values[i][k] * otherOperand.values[k][j];
			}//for
			result.values[i][j] = temp;
			temp = 0;
		}//for
	}//for
	return;
}//Mult

//Function:		   Prints the matrix onto a text file.
//Pre-conditions:  An opened ofstream file is required.
//Post-conditions: Each value from the values matrix will be outputted to outfile.
void MatrixType::Print (ofstream& outfile) {
	for (int i = 0; i < this->numRows; i++) {
		for (int j = 0; j < this->numCols; j++) {
			outfile << this->values[i][j] << " ";
		}//for
		outfile << endl;
	}//for
	outfile << endl;
	return;
}//Print

//Function:		   Checks to see if the 2 matrices can be added or subracted.
//Pre-conditions:  Another MatrixType object is required.
//Post-conditions: Returns true if both objects numRows and numCols variables are the same.
//				   If they're not, then an exception is thrown and returns false.
bool MatrixType::AddSubCompatible (MatrixType otherOperand) {
	if ((this->numRows == otherOperand.numRows) && (this->numCols == otherOperand.numCols)) {
		return true;
	}//if
	else {
		string exceptionString = "***Error: both matrices must have the same number of rows and columns.***";
		throw exceptionString;
		return false;
	}//else
}//AddSubCompatible

//Function:		   Checks to see if the 2 matrices can be multiplied.
//Pre-conditions:  Another MatrixType object is required.
//Post-conditions: Returns true if numCols of the first operand equals to numRows of otherOperand.
//				   If they don't equal, then an exception is thrown and returns false.
bool MatrixType::MultCompatible (MatrixType otherOperand) {
	if (this->numCols == otherOperand.numRows) {
		return true;
	}//if
	else {
		string exceptionString = "***Error: the number of columns of matrix A must be equal to the amount of rows of matrix B.***";
		throw exceptionString;
		return false;
	}//else
}//MultCompatible