#include "SelectionTree.h"

bool SelectionTree::Insert(LoanBookData* newData) {
    if (newData == nullptr) return false;       // if the data is null, return false

    // if root is null, create a new data node and set it as the root
    if (root == nullptr) {
        root = new SelectionTreeNode();
        root->setBookData(newData);
        return true;
    }
    else {
        SelectionTreeNode* pCur = root;     // start from the root

        // repeat until child of pCur is null
        while (pCur->getLeftChild() != nullptr || pCur->getRightChild() != nullptr) {
            // if code is smaller than the code of pCur, move to the left child
            if (pCur->getBookData()->getCode() > newData->getCode()) {
                if (pCur->getLeftChild() == nullptr) {
                    SelectionTreeNode* newNode = new SelectionTreeNode();
                    newNode->setBookData(newData);      // set the data
                    pCur->setLeftChild(newNode);        // set the new node as the left child
                    return true;
                }
                else {
                    pCur = pCur->getLeftChild();        // move to the left child
                }
            }
            else {
                if (pCur->getRightChild() == nullptr) {
                    SelectionTreeNode* newNode = new SelectionTreeNode();
                    newNode->setBookData(newData);      // set the data
                    pCur->setRightChild(newNode);       // set the new node as the right child
                    return true;
                }
                else {
                    pCur = pCur->getRightChild();       // move to the right child
                }
            }
        }
    }
}

bool SelectionTree::Delete() {
    // delete logic
}

bool SelectionTree::printBookData(int bookCode) {
    // print bookdata for PRINT_ST
}