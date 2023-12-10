#include "BpTree.h"

bool BpTree::Insert(LoanBookData* newData) {
    if (newData == nullptr) return false;       // if the data is null, return false

    // if the root is null, create a new data node and set it as the root
    if (root == nullptr) {
        BpTreeDataNode* pCur = new BpTreeDataNode();
        pCur->insertDataMap(newData->getName(), newData);
        data = pCur;
        root = data;
    }
    else {
        BpTreeNode* pCur = data;        // start from the data node
        // find the same key
        auto iter = pCur->getDataMap()->find(newData->getName());
        if (iter != pCur->getDataMap()->end()) {
            iter->second->updateCount();        // if the same key exists, update the count
        } else {
            pCur->insertDataMap(newData->getName(), newData);       // insert the data
            if (excessDataNode(pCur)) {
                splitDataNode(pCur);        // if the data node is full, split
            }
        }
        data = pCur;        // update the data node
    }
    return true;
}

bool BpTree::excessDataNode(BpTreeNode* pDataNode) {
	if (pDataNode->getDataMap()->size() > order - 1) return true;		// order is equal to the number of elements 
	else return false;
}

bool BpTree::excessIndexNode(BpTreeNode* pIndexNode) {
	if (pIndexNode->getIndexMap()->size() > order - 1) return true;		// order is equal to the number of elements 
	else return false;
}

void BpTree::splitDataNode(BpTreeNode* pDataNode) {
    BpTreeDataNode* dataNode = dynamic_cast<BpTreeDataNode*> (pDataNode);

    BpTreeDataNode* newNode = new BpTreeDataNode();     // creating a new data node
    auto iter = dataNode->getDataMap()->begin();        // finding the middle key
    advance(iter, (dataNode->getDataMap()->size() - 1) / 2);        // moving the iterator to the middle

    // transferring half of elements to the new node
    while (iter != dataNode->getDataMap()->end()) {
        newNode->insertDataMap(iter->first, iter->second);      // inserting the element to the new node
        iter++;     // moving the iterator to the next element
    }
    
    // removing transferred elements from the original node
    iter = newNode->getDataMap()->begin();
    while (iter != newNode->getDataMap()->end()) {
        dataNode->deleteMap(iter->first);       // deleting the element from the original node
        iter++;     // moving the iterator to the next element
    }

    // updating next and previous pointers
    newNode->setNext(dataNode->getNext());
    newNode->setPrev(dataNode);
    if (dataNode->getNext() != nullptr) {
        dataNode->getNext()->setPrev(newNode);
    }
    dataNode->setNext(newNode);

    // setting parent node
    // if the parent node is null, create a new index node and set it as the root
    if (dataNode->getParent() == nullptr) {
        BpTreeIndexNode* newRoot = new BpTreeIndexNode();       // creating a new index node
        newRoot->insertIndexMap(newNode->getDataMap()->begin()->first, newNode);        // inserting the middle key to the new node
        newRoot->setMostLeftChild(dataNode);        // setting the most left child
        dataNode->setParent(newRoot);       // setting the parent node
        newNode->setParent(newRoot);        // setting the parent node
        root = newRoot;     // updating the root
    }
    else {
        BpTreeIndexNode* pIndexNode = dynamic_cast<BpTreeIndexNode*> (dataNode->getParent());
        pIndexNode->insertIndexMap(newNode->getDataMap()->begin()->first, newNode);     // inserting the middle key to the parent node
        newNode->setParent(pIndexNode);     // setting the parent node
        if (excessIndexNode(pIndexNode)) {
            splitIndexNode(pIndexNode);     // if the index node is full, split
        }
    }
}

void BpTree::splitIndexNode(BpTreeNode* pIndexNode) {
    BpTreeIndexNode* indexNode = dynamic_cast<BpTreeIndexNode*> (pIndexNode);

    BpTreeIndexNode* newNode = new BpTreeIndexNode();       // creating a new index node
    
    // finding the middle key
    auto iter = indexNode->getIndexMap()->begin();      // finding the middle key
    advance(iter, (indexNode->getIndexMap()->size() - 1) / 2);      // moving the iterator to the middle
    string mid = iter->first;       // saving the middle key

    // transferring half of elements to the new node
    while (iter != indexNode->getIndexMap()->end()) {
        newNode->insertIndexMap(iter->first, iter->second);     // inserting the element to the new node
        iter++;     // moving the iterator to the next element
    }

    // removing transferred elements from the original node
    iter = newNode->getIndexMap()->begin();
    while (iter != newNode->getIndexMap()->end()) {
        indexNode->deleteMap(iter->first);      // deleting the element from the original node
        iter++;     // moving the iterator to the next element
    }

    // updating parent node
    // if the parent node is null, create a new index node and set it as the root
    if (indexNode->getParent() == nullptr) {
        BpTreeIndexNode* newRoot = new BpTreeIndexNode();       // creating a new index node
        newRoot->insertIndexMap(mid, newNode);      // inserting the middle key to the new node
        newRoot->setMostLeftChild(indexNode);       // setting the most left child
        indexNode->setParent(newRoot);      // setting the parent node
        newNode->setParent(newRoot);        // setting the parent node
        root = newRoot;     // updating the root
    }
    else {
        // inserting the middle key to the parent node
        BpTreeIndexNode* parentIndexNode = dynamic_cast<BpTreeIndexNode*> (indexNode->getParent());
        parentIndexNode->insertIndexMap(mid, newNode);      // inserting the middle key to the parent node
        newNode->setParent(parentIndexNode);        // setting the parent node
        if (excessIndexNode(parentIndexNode)) {
            splitIndexNode(parentIndexNode);        // if the index node is full, split
        }
    }
}

BpTreeNode* BpTree::searchDataNode(string name) {
    BpTreeNode* pCur = root;        // start from the root

    if (pCur == nullptr) return nullptr;        // if the root is null, return null

    // finding the most left child
    while (pCur->getMostLeftChild() != nullptr) {
        pCur = pCur->getMostLeftChild();        // moving to the most left child
    }

    // finding the data node
    while (pCur != nullptr) {
        BpTreeDataNode* pDataNode = (BpTreeDataNode*) pCur;
		if (pDataNode == nullptr) return nullptr;       // if the data node is null, return null
        auto iter = pDataNode->getDataMap()->find(name);        // finding the key
        if (iter != pDataNode->getDataMap()->end()) {
            return pDataNode;       // if the key is found, return the data node
        }
        pCur = pDataNode->getNext();        // moving to the next data node
    }

    return nullptr;
}

bool BpTree::searchBook(string name) {
    if (root == nullptr) return false;

    BpTreeNode* pCur = searchDataNode(name);        // finding the data node
    BpTreeDataNode* pDataNode = dynamic_cast<BpTreeDataNode*> (pCur);
    if (pDataNode == nullptr) {
        return false;
    }

    // searching the book
    for (auto iter = pDataNode->getDataMap()->begin(); iter != pDataNode->getDataMap()->end(); ++iter) {
        string bookName = iter->first;      // getting the key

        if (bookName == name) {
            return true;
        }
    }
    return false;
}

bool BpTree::searchRange(string start, string end, ofstream& fout) {
    if (root == nullptr) return false;      // if the root is null, return false

    // find the first data node
    BpTreeNode* current = root;     // start from the root
    while (current->getMostLeftChild() != nullptr) {
        current = current->getMostLeftChild();      // moving to the most left child
    }
    
    // find the first data node
    BpTreeDataNode* pDataNode = dynamic_cast<BpTreeDataNode*> (current);
    if (pDataNode == nullptr) return false;

    while (pDataNode != nullptr) {
        for (auto iter = pDataNode->getDataMap()->begin(); iter != pDataNode->getDataMap()->end(); ++iter) {
            string bookName = iter->first;      // getting the key

            // if the key is in the range, write the data to the file
            if (bookName >= start && bookName <= end) {
                LoanBookData* bookData = iter->second;      // getting the value
                // getting the data
                string name = bookData->getName();
                int code = bookData->getCode();
                string author = bookData->getAuthor();
                int year = bookData->getYear();
                int count = bookData->getLoanCount();
                string codestr;
                // if the code is 0, set the code as 000
                if (code == 0) {
                    codestr = "000";
                }
                else {
                    codestr = to_string(code);
                }
                fout << name << "/" << codestr << "/" << author << "/" << year << "/" << count << endl;     // writing the data to the file
            }
        }

        // move to the next data node
        pDataNode = dynamic_cast<BpTreeDataNode*> (pDataNode->getNext());
        if (pDataNode && pDataNode->getDataMap()->begin()->first > end) {
            return false;
        }
    }

    return true;
}