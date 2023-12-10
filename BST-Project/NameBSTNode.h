#pragma once
#include <iostream>
#include <string>
#include <ostream>

using namespace std;

class NameBSTNode
{
private:
    string name;       // user name
    int age;        // age
    string date;       // personal information date
    string expiration_date;     // expiration date
    char terms;     // terms of subscription

    // left and right node
    NameBSTNode* left;
    NameBSTNode* right;

public:
    // constructor
    NameBSTNode(string n, int a, string d, string exd, char t)
    {
        name = n;
        age = a;
        date = d;
        expiration_date = exd;
        terms = t;
        left = nullptr;
        right = nullptr;
    }

    ~NameBSTNode()
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
        return name;        // return name
    }

    // set name
    void setName(string n)
    {
		name = n;       // set name
	}

    // get age
    int getAge()
    {
        return age;     // return age
    }

    // set age
    void setAge(int a)
    {
		age = a;        // set age
	}

    // get date
    string getDate()
    {
        return date;        // return date
    }

    // set date
    void setDate(string d)
    {
        date = d;       // set date
    }

    // get expiration date
    string getExpireDate()
    {
        return expiration_date;     // return expiration date
    }

    // set expiration date
    void setExpireDate(string exd)
    {
		expiration_date = exd;      // set expiration date
	}

    // get terms
    char getTerms()
    {
        return terms;       // return terms
    }

    // set terms
    void setTerms(char t)
    {
		terms = t;      // set terms
	}

    // get left node
    NameBSTNode* getLeft()
    {
        return left;        // return left node
    }

    // get right node
    NameBSTNode* getRight()
    { 
        return right;       // return right node
    }

    // set left node
    void setLeft(NameBSTNode* node)
    {
        left = node;        // set left node
    }

    // set right node
    void setRight(NameBSTNode* node)
    {
        right = node;       // set right node
    }
};
