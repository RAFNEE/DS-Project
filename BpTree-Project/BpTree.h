#ifndef _BpTree_H_
#define _BpTree_H_

#include "BpTreeDataNode.h"
#include "BpTreeIndexNode.h"
#include "LoanBookData.h"
#include <fstream>
#include <iostream>
#include <queue>

class BpTree {
private:
	BpTreeNode* root;
	BpTreeNode* data;		// leaf nodes
	int order;		// m children
	ofstream* fout;
public:
	BpTree(ofstream *fout, int order = 3) {
		root = NULL;
		this->order = order;
		this->fout = fout;
	}
	~BpTree() {
		delete root;
		delete data;
   	}
	/* essential */
	bool		Insert(LoanBookData* newData);
	bool		excessDataNode(BpTreeNode* pDataNode);
	bool		excessIndexNode(BpTreeNode* pIndexNode);
	void		splitDataNode(BpTreeNode* pDataNode);
	void		splitIndexNode(BpTreeNode* pIndexNode);
	BpTreeNode* getRoot() { return root; }
	BpTreeNode* searchDataNode(string name);

	bool searchBook(string name);
	bool searchRange(string start, string end, ofstream& fout);
};

#endif