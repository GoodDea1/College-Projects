#include <iostream>
#include "BinaryTree.hpp"
using namespace std;

int calculateHeight(TreeNode* rootNode) {
	int leftHeight = 0;
	int rightHeight = 0;
	if (rootNode->Left != nullptr) {
		leftHeight = 1 + calculateHeight(rootNode->Left);
	}//if
	else{}
	if (rootNode->Right != nullptr) {
		rightHeight = 1 + calculateHeight(rootNode->Right);
	}//if
	else{}
	if (leftHeight >= rightHeight) {
		return leftHeight;
	}//if
	else {
		return rightHeight;
	}//else
}//calculateHeight

int calculateBalance(TreeNode* rootNode) {
	int leftHeight = 0;
	int rightHeight = 0;
	if (rootNode->Left != nullptr) {
		leftHeight = 1 + calculateBalance(rootNode->Left);
	}//if
	else{}
	if (rootNode->Right != nullptr) {
		rightHeight = 1 + calculateBalance(rootNode->Right);
	}//if
	else{}
	rootNode->BalanceFactor = leftHeight - rightHeight;
	if (leftHeight >= rightHeight) {
		return leftHeight;
	}//if
	else {
		return rightHeight;
	}//else
}//calculateBalance

int getLargestBF(TreeNode* rootNode) {
	int leftLargest = 0;
	int rightLargest = 0;
	if (rootNode == nullptr) {
		return 0;
	}//if
	else {
		if (rootNode->Left != nullptr) {
			getLargestBF(rootNode->Left);
		}//if
		else{}

		if (abs(rootNode->BalanceFactor) > abs(leftLargest)) {
			leftLargest = rootNode->BalanceFactor;
		}//if
		else {}

		if (rootNode->Right != nullptr) {
			getLargestBF(rootNode->Right);
		}//if
		else{}

		if (abs(rootNode->BalanceFactor) > abs(rightLargest)) {
			rightLargest = rootNode->BalanceFactor;
		}//if
		else {}

		if (abs(leftLargest) >= abs(rightLargest)) {
			return leftLargest;
		}//if
		else {
			return rightLargest;
		}//else
	}//else
}//getLargestBF
