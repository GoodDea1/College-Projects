#include "TreeType.hpp"

struct words {
	string word;
	int frequency;
};

int main() {

	ifstream	inFile;
	ofstream	outFile;
	int			avgWordLength,
				numberOfSentences,
				arrayLength,
				greaterThanThreeLetters;
	bool		exit,
				finished,
				getOut,
				increased;
	char		userInput,
				fileChar;
	string		inputFileName,
				currentWord;
	words		freqArray[500];
	TreeType<string>	lexicon;

	exit = false;
	outFile.open("output.txt", ios::out);

	do {
		inputFileName.clear();
		cout << "Enter the filename you wish to use: ";
		cin >> inputFileName;
		inFile.open(inputFileName, ios::in);
		if (inFile.fail()) {
			cout << endl << endl << "***Error: File doesn't exist.***" << endl;
		}//if
		else {
			//Output filename.
			cout    << endl << endl << inputFileName << endl << endl;
			outFile << inputFileName << endl << endl;
			//Output listing of the file.
			cout	<< "Listing: ";
			outFile << "Listing: ";
			getline(inFile, currentWord);
			while (inFile) {
				cout	<< currentWord << endl;
				outFile << currentWord << endl;
				getline(inFile, currentWord);
			}//while
			inFile.close();
			//Load words into the binary search tree called lexicon.
			inFile.open(inputFileName, ios::in);
			if (inFile) {
				avgWordLength = 0;
				while (inFile) {
					currentWord.clear();
					getOut = false;
					while (getOut != true) {
						inFile.get(fileChar);
						if ((fileChar == '.') ||
							(fileChar == '!') ||
							(fileChar == ',') ||
							(fileChar == ' ') ||
							(fileChar == ';') ||
							(fileChar == '"') ||
							(fileChar == '?') ||
							(fileChar == ':')) {
							getOut = true;
						}//if
						else {
							currentWord.append(1, fileChar);
						}//else
					}//while
					if (!currentWord.empty()) {
						avgWordLength += currentWord.size();
						currentWord[0] = tolower(currentWord[0]);
						lexicon.PutItem(currentWord);
					}//if
				}//while
			}//if
			inFile.close();
			//Load words into frequency array
			currentWord.clear();
			lexicon.ResetTree(IN_ORDER);
			finished = false;
			arrayLength = 0;
			while (finished != true) {
				increased = false;
				currentWord = lexicon.GetNextItem(IN_ORDER, finished);
				for (int i = 0; i <= arrayLength; i++) {
					if (currentWord == freqArray[i].word) {
						freqArray[i].frequency++;
						increased = true;
					}//if
					else if ((i == arrayLength) && (increased == false)) {
						freqArray[i].word = currentWord;
						freqArray[i].frequency = 1;
					}//else if
				}//for
				if (increased == false) {
					arrayLength++;
				}//if
			}//while
			//Print the lexicon with word frequencies
			for (int i = 0; i < arrayLength; i++) {
				currentWord.clear();
				currentWord = freqArray[i].word;
				currentWord[0] = toupper(currentWord[0]);
				cout	<< currentWord << ": " << freqArray[i].frequency << endl;
				outFile << currentWord << ": " << freqArray[i].frequency << endl;
			}//for
			//Print statistical report
			//Total number of words
			cout	<< endl << "Total number of words: " << lexicon.GetLength() << endl;
			outFile << endl << "Total number of words: " << lexicon.GetLength() << endl;
			//Unique words
			cout	<< "Number of unique words: " << arrayLength << endl;
			outFile << "Number of unique words: " << arrayLength << endl;
			//Words with more than 3 letters
			greaterThanThreeLetters = 0;
			for (int i = 0; i < arrayLength; i++) {
				if (freqArray[i].word.size() > 3) {
					greaterThanThreeLetters++;
				}//if
			}//for
			cout	<< "Number of unique words of more than three letters: " << greaterThanThreeLetters << endl;
			outFile << "Number of unique words of more than three letters: " << greaterThanThreeLetters << endl;
			//Average word length
			cout	<< "Average word length: " << (avgWordLength / lexicon.GetLength()) << endl;
			outFile << "Average word length: " << (avgWordLength / lexicon.GetLength()) << endl;
			//Average sentence length
			inFile.open(inputFileName, ios::in);
			numberOfSentences = 0;
			while (inFile) {
				inFile.get(fileChar);
				if ((fileChar == '.') ||
					(fileChar == '!') ||
					(fileChar == '?')) {
					numberOfSentences++;
				}//if
			}//while
			numberOfSentences--;
			cout	<< "Average sentence length: " << (lexicon.GetLength() / numberOfSentences) << endl;
			outFile << "Average sentence length: " << (lexicon.GetLength() / numberOfSentences) << endl;
		}//else

		//Continue or exit
		cout << endl << "Do you wish to continue? Type 'N' if you don't: ";
		cin >> userInput;
		if (userInput == 'n' || userInput == 'N') {
			exit = true;
		}//if
		inFile.close();

	} while (exit != true);

	cout << "Program ending, have a nice day!" << endl;
	outFile.close();

	return 0;
}