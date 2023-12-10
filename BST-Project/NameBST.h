#pragma once
#include "NameBSTNode.h"

class NameBST
{
private:
	NameBSTNode* root;

	// recursive insertion function to insert node
	NameBSTNode* insert(NameBSTNode* node, string name, int age, string date, string expiration_date, char terms);
	// recursive search function to search for node
	NameBSTNode* search(NameBSTNode* node, string name);
	// find min node
	NameBSTNode* findMinNode(NameBSTNode* node);
	// recursive remove function to remove node
	NameBSTNode* remove(NameBSTNode* node, string name);

	// recursive print in order function to print nodes in order
	void printInOrder(NameBSTNode* node, ostream& os);

public:
	NameBST();		// constructor
	~NameBST();		// destructor

	NameBSTNode* getRoot();		// get root

	// insert
	void insert(string name, int age, string date, string expiration_date, char terms);
	// search
	NameBSTNode* search(string name);
	// print
	void print(ostream& os);
	// remove
	void remove(string name);
};