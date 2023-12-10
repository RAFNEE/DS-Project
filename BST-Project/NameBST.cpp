#include "NameBST.h"

// constructor
NameBST::NameBST()
{
	root = nullptr;
}

// destructor
NameBST::~NameBST()
{
	// delete all nodes
	if (root != nullptr)
	{
		delete root;
	}
}

// get root
NameBSTNode* NameBST::getRoot()
{
	return root;
}

// insert
void NameBST::insert(string name, int age, string date, string expiration_date, char terms)
{
	// recursive insertion function to insert node
	root = insert(root, name, age, date, expiration_date, terms);
}

// recursive insertion function to insert node
NameBSTNode* NameBST::insert(NameBSTNode* node, string name, int age, string date, string expiration_date, char terms)
{
	// if tree is empty, return a new node
	if (node == nullptr)
	{
		return new NameBSTNode(name, age, date, expiration_date, terms);
	}
	// sort by name
	if (name < node->getName())
	{
		node->setLeft(insert(node->getLeft(), name, age, date, expiration_date, terms));
	}
	else
	{
		node->setRight(insert(node->getRight(), name, age, date, expiration_date, terms));
	}
	// return node
	return node;
}

// search
NameBSTNode* NameBST::search(string name)
{
	// recursive search function to search for node
	return search(root, name);
}

// recursive search function to search for node
NameBSTNode* NameBST::search(NameBSTNode* node, string name)
{
	// if tree is empty or node is found, return node
	if (node == nullptr || node->getName() == name)
	{
		return node;
	}

	// determine which side to search
	if (name < node->getName())
	{
		return search(node->getLeft(), name);
	}
	else
	{
		return search(node->getRight(), name);
	}

	return nullptr;		// if not found, return nullptr
}

// print
void NameBST::print(ostream& os)
{
	// recursive print in order function to print nodes in order
	printInOrder(root, os);
}

// recursive print in order function to print nodes in order
void NameBST::printInOrder(NameBSTNode* node, ostream& os)
{
	// if tree is empty, return
	if (node == nullptr)
	{
		return;
	}

	// print left
	printInOrder(node->getLeft(), os);
	// print node
	os << node->getName() << "/" << node->getAge() << "/" << node->getDate() << "/" << node->getExpireDate() << endl;
	// print right
	printInOrder(node->getRight(), os);
}

// find min node
NameBSTNode* NameBST::findMinNode(NameBSTNode* node)
{
	NameBSTNode* current = node;		// set current to node

	// loop to find left node
	while (current->getLeft() != nullptr)
	{
		current = current->getLeft();		// set current to left node
	}

	return current;		// return left node
}

// remove
void NameBST::remove(string name)
{
	// recursive remove function to remove node
	root = remove(root, name);
}

// recursive remove function to remove node
NameBSTNode* NameBST::remove(NameBSTNode* node, string name)
{
	// if tree is empty, return
	if (node == nullptr)
	{
		return node;
	}

	// determine which side to remove node
	if (name < node->getName())
	{
		node->setLeft(remove(node->getLeft(), name));
	}
	else if (name > node->getName())
	{
		node->setRight(remove(node->getRight(), name));
	}
	else
	{
		// remove node with one child
		if (node->getLeft() == nullptr)
		{
			// set temp to right node
			NameBSTNode* temp = node->getRight();
			delete node;
			return temp;
		}
		else if (node->getRight() == nullptr)
		{
			// set temp to left node
			NameBSTNode* temp = node->getLeft();
			delete node;
			return temp;
		}

		// remove node with two children
		NameBSTNode* minNode = findMinNode(node->getRight());
		node->setName(minNode->getName());
		node->setRight(remove(node->getRight(), minNode->getName()));
	}

	return node;
}