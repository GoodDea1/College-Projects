#pragma once
#include <fstream>
#include <string>
#include "QueType.hpp"

using namespace std;

enum OrderType {PRE_ORDER, IN_ORDER, POST_ORDER};

template<class T>
struct TreeNode {
	TreeNode* left;
	TreeNode* right;
	T info;
};

template<class T>
class TreeType
{
public:
	TreeType();
	~TreeType();
	TreeType(const TreeType<T>& originalTree);
	void operator=(const TreeType<T>& originalTree);
	void MakeEmpty();
	bool IsEmpty() const;
	bool IsFull() const;
	int GetLength() const;
	T GetItem(T item, bool& found);
	void PutItem(T item);
	void DeleteItem(T item);
	void ResetTree(OrderType order);
	T GetNextItem(OrderType order, bool& finished);
	void Print(ofstream& outFile);
private:
	TreeNode<T>* root;
	QueType<T>	preQue,
				inQue,
				postQue;
};

template<class T>
TreeType<T>::TreeType() {
	//Function: Initializes root to NULL.
	root = NULL;
}//Constructor

template<class T>
bool TreeType<T>::IsFull() const {
	//Function: Checks to see if TreeType is full.
	//Preconditions: TreeType is initialized.
	//Postconditions: Returns true if tree is full; false otherwise.
	TreeNode<T>* location;
	try {
		location = new TreeNode<T>;
		delete location;
		return false;
	}//try
	catch (bad_alloc exception) {
		return true;
	}//catch
}//IsFull

template<class T>
bool TreeType<T>::IsEmpty() const {
	//Function: Checks to see if TreeType is empty.
	//Preconditions: TreeType is initialized.
	//Postconditions: Returns true if tree is empty; false otherwise.
	return (root == NULL);
}//IsEmpty

template<class T>
int CountNodes(TreeNode<T>* tree);			//CountNodes prototype

template<class T>
int TreeType<T>::GetLength() const {
	//Function: Calls on the recursive function CountNodes.
	//Preconditions: TreeType is initialized.
	//Postconditions: Returns the number of tree nodes from CountNodes function.
	return CountNodes(root);
}//GetLength

template<class T>
int CountNodes(TreeNode<T>* tree) {
	//Function: Counts the number of TreeNode nodes in tree.
	//Preconditions: TreeType is initialized.
	//Postconditions: Returns the number of TreeNode nodes.
	if (tree == NULL) {
		return 0;
	}//if
	else {
		return CountNodes(tree->left) + CountNodes(tree->right) + 1;
	}//else
}//CountNodes

template<class T>
void Retrieve(TreeNode<T>* tree, T& item, bool& found);		//Retrieve prototype

template<class T>
T TreeType<T>::GetItem(T item, bool& found) {
	//Function: Calls on the recursive function Retrieve.
	//Preconditions: TreeType is initialized. Found is false.
	//Postconditions: If item is found, item is returned.
	Retrieve(this->root, item, found);
	return item;
}//GetItem

template<class T>
void Retrieve(TreeNode<T>* tree, T& item, bool& found) {
	//Function: Recursively searches for specified item in tree.
	//Preconditions: TreeType is initialized. Found is false.
	//Postconditions: If item is found, item is returned and found = true; otherwise found = false.
	if (tree == NULL) {
		found = false;
	}//if
	else if (item < tree->info) {
		Retrieve(tree->left, item, found);
	}//else if
	else if (item < tree->right) {
		Retrieve(tree->right, item, found);
	}//else if
	else {
		item = tree->info;
		found = true;
	}//else
}//Retrieve

template<class T>
void Insert(TreeNode<T>*& tree, T item);		//Insert prototype

template<class T>
void TreeType<T>::PutItem(T item) {
	//Function: Calls the recursive function Insert to instert item into tree.
	//Preconditions: TreeType is initialized.
	//Postconditions: item is in tree.
	Insert(this->root, item);
}//PutItem

template<class T>
void Insert(TreeNode<T>*& tree, T item) {
	//Function: Inserts item into tree.
	//Preconditions: TreeType is initialized.
	//Post-Conditions: item is in tree; search property is maintained
	if (tree == NULL) {
		tree = new TreeNode<T>;
		tree->right = NULL;
		tree->left = NULL;
		tree->info = item;
	}//if
	else if (item[0] < tree->info[0]) {
		Insert(tree->left, item);
	}//else if
	else if (item[0] == tree->info[0]) {
		if (item < tree->info) {
			Insert(tree->left, item);
		}//if
		else {
			Insert(tree->right, item);
		}//else
	}//else if
	else {
		Insert(tree->right, item);
	}//else
}//Insert

template<class T>
void DeleteNode(TreeNode<T>*& tree);		//DeleteNode prototype

template<class T>
void Delete(TreeNode<T>*& tree, T item);	//Delete prototype

template<class T>
void TreeType<T>::DeleteItem(T item) {
	//Function: Calls the recursive function Delete to delete item from tree.
	//Preconditions: TreeType is initialized.
	//Postconditions: item is deleted from tree.
	Delete(this->root, item);
}//DeleteItem

template<class T>
void Delete(TreeNode<T>*& tree, T item) {
	//Function: Recursively deletes item from tree.
	//Preconditions: TreeType is initialized.
	//Postconditions: item is deleted from tree.
	if (item < tree->info) {
		Delete(tree->left, item);	//Look in left subtree
	}//if
	else if (item > tree->info) {
		Delete(tree->right, item);	//Look in right subtree
	}//else if
	else {
		DeleteNode(tree);			//Node found; call DeleteNode
	}//else
}//Delete

template<class T>
void GetPredecessor(TreeNode<T>* tree, T& data);	//GetPredecessor prototype

template<class T>
void DeleteNode(TreeNode<T>*& tree) {
	//Function: Delete the node pointed to by tree.
	//Preconditions: TreeType is initialized.
	//Postconditions: The user's data in the node pointed to by tree is no
	//					longer in the tree. If tree is a leaf node or has only one
	//					non-NULL child opinter, the node pointed to by tree is
	//					deleted; otherwise, the user's data is replaced by its
	//					logical predecessor and the predecessor's node is deleted
	T data;
	TreeNode<T> tempPtr;

	tempPtr = tree;
	if (tree->left == NULL) {
		tree = tree->right;
		delete tempPtr;
	}//if
	else if (tree->right == NULL) {
		tree = tree->left;
		delete tempPtr;
	}//else if
	else {
		GetPredecessor(tree->left, data);
		tree->info = data;
		Delete(tree->left, data);	//Delete predecessor node
	}//else
}//DeleteNode

template<class T>
void GetPredecessor(TreeNode<T>* tree, T& data) {
	//Function: Sets data to the info member of the rightmost node in tree.
	while (tree->right != NULL) {
		tree = tree->right;
	}//while
	data = tree->info;
}//GetPredecessor

template<class T>
void PrintTree(TreeNode<T>* tree, ofstream& outFile) {
	//Function: Prints info member of items in tree in sorted order on outFile.
	if (tree != NULL) {
		PrintTree(tree->left, outFile);		//Print left subtree
		outFile << tree->info;
		PrintTree(tree->right, outFile);	//Print right subtree
	}//if
}//PrintTree

template<class T>
void TreeType<T>::Print(ofstream& outFile) {
	//Function: Calls recursive function PrintTree to print items in the tree.
	//Preconditions: TreeType is initialized. outFile is open.
	//Postconditions: outFile contains all TreeNode infos.
	PrintTree(this->root, outFile);
}//Print

template<class T>
void Destroy(TreeNode<T>*& tree);	//Destroy prototype

template<class T>
TreeType<T>::~TreeType() {
	//Function: Calls recursive function Destroy to destroy the tree.
	Destroy(this->root);
}//Destructor

template<class T>
void TreeType<T>::MakeEmpty() {
	//Function: Clears the tree.
	//Preconditions: TreeType is initialized.
	//Postconditions: tree is cleared and root is set to NULL.
	Destroy(this->root);
}//MakeEmpty

template<class T>
void Destroy(TreeNode<T>*& tree) {
	//Post-Conditions: Tree is empty; nodes have been deallocated.
	if (tree != NULL) {
		Destroy(tree->left);
		Destroy(tree->right);
		delete tree;
	}//if
}//Destroy

template<class T>
void CopyTree(TreeNode<T>*& copy, const TreeNode<T>* originalTree);		//CopyTree prototype

template<class T>
TreeType<T>::TreeType(const TreeType<T>& originalTree) {
	//Function: Calls the recurisve function CopyTree to copy originalTree into root
	CopyTree(this->root, originalTree.root);
}//Copy Constructor

template<class T>
void TreeType<T>::operator=(const TreeType<T>& originalTree) {
	//Function: Calls the recursive function CopyTree to copy originalTree
	if (&originalTree == this) {
		return;						//Ignore assigning self to self
	}//if
	Destroy(this->root);			//Deallocate existing tree nodes
	CopyTree(this->root, originalTree.root);
}//operator=

template<class T>
void CopyTree(TreeNode<T>*& copy, const TreeNode<T>* originalTree) {
	//Post-Conditions: Copy is the root of a tree that is a duplicate of originalTree.
	if (originalTree == NULL) {
		copy = NULL;
	}//if
	else {
		copy = new TreeNode<T>;
		copy->info = originalTree->info;
		CopyTree(copy->left, originalTree->left);
		CopyTree(copy->right, originalTree->right);
	}//else
}//CopyTree

//Function prototypes for auxiliary functions.
template<class T>
void PreOrder(TreeNode<T>*, QueType<T>&);
//Enqueues tree items in preorder.

template<class T>
void InOrder(TreeNode<T>*, QueType<T>&);
//Enqueues tree items in inorder.

template<class T>
void PostOrder(TreeNode<T>*, QueType<T>&);
//Enqueues tree items in postorder.

template<class T>
void TreeType<T>::ResetTree(OrderType order) {
	//Fucntion: Calls a function to create a queue of the tree elements
	//			in the desired order.
	switch (order) {
	case PRE_ORDER:
		PreOrder(this->root, this->preQue);
		break;
	case IN_ORDER:
		InOrder(this->root, this->inQue);
		break;
	case POST_ORDER:
		PostOrder(this->root, this->postQue);
		break;
	}//switch
}//ResetTree

template<class T>
void PreOrder(TreeNode<T>* tree, QueType<T>& preQue) {
	//Function: Enqueues TreeNode info onto preQueue in preorder
	//Preconditions: TreeType and QueType are initialized
	//Postconditions: preQue contains the tree items in preorder
	if (tree != NULL) {
		preQue.Enqueue(tree->info);
		PreOrder(tree->left, preQue);
		PreOrder(tree->right, preQue);
	}//if
}//PreOrder

template<class T>
void InOrder(TreeNode<T>* tree, QueType<T>& inQue) {
	//Function: Enqueues TreeNode info onto inQueue in inorder
	//Preconditions: TreeType and QueType are initialized
	//Postconditions: inQue contains the tree items in inorder
	if (tree != NULL) {
		InOrder(tree->left, inQue);
		inQue.Enqueue(tree->info);
		InOrder(tree->right, inQue);
	}//if
}//PreOrder

template<class T>
void PostOrder(TreeNode<T>* tree, QueType<T>& postQue) {
	//Function: Enqueues TreeNode info onto postQueue in postorder
	//Preconditions: TreeType and QueType are initialized
	//Postconditions: postQue contains the tree items in postorder
	if (tree != NULL) {
		PostOrder(tree->left, postQue);
		PostOrder(tree->right, postQue);
		postQue.Enqueue(tree->info);
	}//if
}//PreOrder

template<class T>
T TreeType<T>::GetNextItem(OrderType order, bool& finished) {
	//Function: Returns the next item in the desired order.
	//Preconditions: TreeType and QutType are initialized.
	//Postconditions: For the desired order, item is the next item in the queue.
	//				  If item is the last one in the queue, finished is true;
	//				  otherwise, finished is false.
	T item;
	finished = false;
	switch (order) {
	case PRE_ORDER:
		preQue.Dequeue(item);
		if (preQue.IsEmpty()) {
			finished = true;
		}//if
		break;
	case IN_ORDER:
		inQue.Dequeue(item);
		if (inQue.IsEmpty()) {
			finished = true;
		}//if
		break;
	case POST_ORDER:
		postQue.Dequeue(item);
		if (postQue.IsEmpty()) {
			finished = true;
		}//if
		break;
	}//switch
	return item;
}//GetNextItem