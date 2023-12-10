#pragma once
#include <iostream>
#include <string>

using namespace std;

class MemberQueueNode
{
private:
    string name;        // user name
    int age;        // age
    string date;        // personal information date
    char terms;     // terms of subscription
    MemberQueueNode* next;      // next node

public:
    // constructor
    MemberQueueNode(string n, int a, string d, char t)
    {
        // initialize data
        name = n;
        age = a;
        date = d;
        terms = t;
        next = nullptr;
    }

    // destructor
    ~MemberQueueNode() 
    {
        // delete all nodes
        while (next != nullptr)
        {
			MemberQueueNode* temp = next;
			next = next->getNext();
			delete temp;
		}
    }

    // get next node
    MemberQueueNode* getNext()
    {
        return next;
    }

    // set next node
    void setNext(MemberQueueNode* nextNode)
    {
        next = nextNode;
    }

    // get name data
    string getName()
    {
        return name;
    }

    // get age data
    int getAge()
    {
        return age;
    }

    // get date data
    string getDate()
    {
        return date;
    }

    // get terms data
    char getTerms()
    {
        return terms;
    }
};
