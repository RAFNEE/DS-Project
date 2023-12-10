#pragma once
#include "TermsBST.h"

class TermsListNode {
private:
    char terms;           // type of terms
    int membercount;      // membercount
    TermsBST* bst;        // BST pointer
    TermsListNode* next;  // next node

public:
    // constructor
    TermsListNode(char t)
    {
        terms = t;
        membercount = 0;
        bst = nullptr;
        next = nullptr;
    }

    // destructor
    ~TermsListNode()
    {
        // delete all nodes
        if (bst != nullptr)
        {
            delete bst;
        }
    }

    // return type of terms
    char getTerms()
    {
        return terms;
    }

    // return member count
    int getMembercount()
    {
        return membercount;
    }

    // increment member count
    void incrementMembercount()
    {
        membercount++;
    }

    // decrement member count
    void decrementMembercount()
    {
        membercount--;
    }

    // return BST pointer
    TermsBST* getBST()
    {
        return bst;
    }

    // set BST pointer
    void setBST(TermsBST* b)
    {
        bst = b;
    }

    // return next node
    TermsListNode* getNext()
    {
        return next;
    }

    // set next node
    void setNext(TermsListNode* n)
    {
        next = n;
    }
};
