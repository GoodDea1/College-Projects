#include "StackType.hpp"

int main() {
	ifstream inputFile;
	ofstream outputFile;

	inputFile.open("input.txt", ios::in);
	outputFile.open("output.txt", ios::out);
	string infixString;
	string postfixString;
	StackType stack;
	bool end;
	bool precedence;

	end = false;

	while (!end) {
		inputFile >> infixString;
		for (int i = 0; i < infixString.size(); i++) {
			if (infixString[i] == '(') {
				stack.Push(infixString[i]);
			}//if
			else if (infixString[i] == ')') {
				while (stack.Top() != '(') {
					postfixString += stack.Top();
					stack.Pop();
				}//while
				stack.Pop();
			}//else if
			else if (infixString[i] == '*') {
				precedence = true;
				while (precedence) {
					if (stack.IsEmpty()) {
						precedence = false;
						stack.Push(infixString[i]);
					}//if
					else if ((stack.Top() == '/') || (stack.Top() == '*')) {
						postfixString += stack.Top();
						stack.Pop();
					}//else if
					else {
						precedence = false;
						stack.Push(infixString[i]);
					}//else
				}//while
			}//else if
			else if (infixString[i] == '/') {
				precedence = true;
				while (precedence) {
					if (stack.IsEmpty()) {
						precedence = false;
						stack.Push(infixString[i]);
					}//if
					else if ((stack.Top() == '/') || (stack.Top() == '*')) {
						postfixString += stack.Top();
						stack.Pop();
					}//else if
					else {
						precedence = false;
						stack.Push(infixString[i]);
					}//else
				}//while
			}//else if
			else if (infixString[i] == '+') {
				precedence = true;
				while (precedence) {
					if (stack.IsEmpty()) {
						precedence = false;
						stack.Push(infixString[i]);
					}//if
					else if ((stack.Top() == '/') || (stack.Top() == '*') ||
						(stack.Top() == '+') || (stack.Top() == '-')) {
						postfixString += stack.Top();
						stack.Pop();
					}//else if
					else {
						precedence = false;
						stack.Push(infixString[i]);
					}//else
				}//while
			}//else if
			else if (infixString[i] == '-') {
				precedence = true;
				while (precedence) {
					if (stack.IsEmpty()) {
						precedence = false;
						stack.Push(infixString[i]);
					}//if
					else if ((stack.Top() == '/') || (stack.Top() == '*') ||
						(stack.Top() == '+') || (stack.Top() == '-')) {
						postfixString += stack.Top();
						stack.Pop();
					}//else if
					else {
						precedence = false;
						stack.Push(infixString[i]);
					}//else
				}//while
			}//else if
			else if (infixString[i] == ';') {
				while (stack.IsEmpty() != true) {
					postfixString += stack.Top();
					stack.Pop();
				}//while
				outputFile << "Infix:   " << infixString   << endl << endl;
				outputFile << "Postfix: " << postfixString << endl << endl;
				postfixString = "";
			}//else if
			else if (infixString[i] == '.') {
				while (stack.IsEmpty() != true) {
					postfixString += stack.Top();
					stack.Pop();
				}//while
				outputFile << "Infix:   " << infixString <<   endl << endl;
				outputFile << "Postfix: " << postfixString << endl << endl;
				postfixString = "";
				end = true;
			}//else if
			else {
				//This is here if the char is an operand, then immediately append to the postfix string.
				postfixString += infixString[i];
			}//else
		}//for
	}//while

	inputFile.close();
	outputFile.close();

	return 0;
}