#pragma once
#include "TermsBSTNode.h"

class TermsBST
{
private:
	TermsBSTNode* root;

	// recursive insert function to insert node
	TermsBSTNode* insert(TermsBSTNode* node, string name, int age, string date, string expiration_date);
	// find min node
	TermsBSTNode* findMinNode(TermsBSTNode* node);
	// recursive remove function to delete node
	TermsBSTNode* remove(TermsBSTNode* node, string name, string expiration_date);
	// recursive print in order function to print nodes in order
	void printInOrder(TermsBSTNode* node, ostream& os);

public:
	TermsBST();		// constructor
	~TermsBST();		// destructor

	TermsBSTNode* getRoot();		// get root
	
	// insert
	void insert(string name, int age, string date, string expiration_date);
	// print
	void print(ostream& os);
	// remove
	void remove(string name, string expiration_date);
};