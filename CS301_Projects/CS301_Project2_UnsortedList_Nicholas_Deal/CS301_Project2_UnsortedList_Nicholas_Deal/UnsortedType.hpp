#pragma once

#include <iostream>
#include <fstream>

using namespace std;

const int MAX_ITEMS = 15;

class UnsortedType
{
public:
	UnsortedType();
	void MakeEmpty();
	bool IsFull() const;
	int	GetLength() const;
	int GetItem(long item);
	void PutItem(long item);
	void DeleteItem(long item);
	void ResetList();
	long GetNextItem();
	void PrintList(ofstream& OutFile);
private:
	int length;
	int currentPos;
	long info;
};
