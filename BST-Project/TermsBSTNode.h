#pragma once
#include <iostream>
#include <string>
#include <ostream>

using namespace std;

class TermsBSTNode
{
private:
	string name;		// user name
	int age;		// age
	string date;		// personal information date
	string expiration_date;		// expiration date

	TermsBSTNode*	left;
	TermsBSTNode*	right;


public:
	// constructor
	TermsBSTNode()
	{
		// initialize data
		name = "";
		age = 0;
		date = "";
		expiration_date = "";
		left = nullptr;
		right = nullptr;
	}

	// constructor
	TermsBSTNode(string n, int a, string d, string exd)
	{
		name = n;
		age = a;
		date = d;
		expiration_date = exd;
		left = nullptr;
		right = nullptr;
	}

	// destructor
	~TermsBSTNode()
	{
		// delete all nodes
		if(left != nullptr)
			delete left;
		if(right != nullptr)
			delete right;
	}

	// get name
	string getName()
	{
		return name;		// return name
	}

	// set name
	void setName(string name)
	{
		this->name = name;		// set name
	}

	// get age
	int getAge()
	{
		return age;		// return age
	}

	// set age
	void setAge(int age)
	{
		this->age = age;		// set age
	}

	// get date
	string getDate()
	{
		return date;		// return date
	}

	// set date
	void setDate(string date)
	{
		this->date = date;		// set date
	}

	// get expiration date
	string getExpirationDate()
	{
		return expiration_date;		// return expiration date
	}

	// set expiration date
	void setExpirationDate(string expiration_date)
	{
		this->expiration_date = expiration_date;		// set expiration date
	}

	// get left node
	TermsBSTNode*	getLeft()
	{
		return left;		// return left node
	}

	// get right node
	TermsBSTNode*	getRight()
	{
		return right;		// return right node
	}

	// set left node
	void setLeft (TermsBSTNode* left)
	{
		this->left = left;		// set left node
	}

	// set right node
	void setRight(TermsBSTNode* right)	
	{
		this->right = right;		// set right node
	}
};