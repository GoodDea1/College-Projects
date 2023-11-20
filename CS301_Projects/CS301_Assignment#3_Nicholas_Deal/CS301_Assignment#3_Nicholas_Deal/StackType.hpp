#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct NodeType {
	char info;
	NodeType* next;
};

class StackType
{
public:
	StackType();
	~StackType();
	bool IsEmpty() const;
	bool IsFull() const;
	void Push(char newChar);
	void Pop();
	char Top();
private:
	NodeType* topPtr;
};

