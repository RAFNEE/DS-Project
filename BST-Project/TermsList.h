#pragma once
#include "TermsListNode.h"

class TermsList
{
private:
    TermsListNode* head;

public:
    TermsList();        // constructor

    ~TermsList();       // destructor

    // insert a new node with terms
    void insert(char terms);

    // search for a node with terms and return its pointer
    TermsListNode* search(char terms);

    // delete the node with terms from the list
    void remove(char terms);
};
