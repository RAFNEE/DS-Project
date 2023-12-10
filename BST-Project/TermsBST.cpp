#include "TermsBST.h"

// constructor
TermsBST::TermsBST()
{
	root = nullptr;
}

// destructor
TermsBST::~TermsBST()
{
	// delete all nodes
	if (root != nullptr)
	{
		delete root;
	}
}

// get root
TermsBSTNode* TermsBST::getRoot()
{
	return root;		// return root
}

// insert
void TermsBST::insert(string name, int age, string date, string expiration_date)
{
	// recursive insert function to insert node
	root = insert(root, name, age, date, expiration_date);
}

// recursive insert function to insert node
TermsBSTNode* TermsBST::insert(TermsBSTNode* node, string name, int age, string date, string expiration_date)
{
    // if tree is empty, return a new node
    if (node == nullptr)
    {
        return new TermsBSTNode(name, age, date, expiration_date);
    }

    // compare and sort by expiration date
    if (expiration_date < node->getExpirationDate())
    {
        node->setLeft(insert(node->getLeft(), name, age, date, expiration_date));
    }
    else if (expiration_date > node->getExpirationDate())
    {
        node->setRight(insert(node->getRight(), name, age, date, expiration_date));
    }

    // return node
    return node;
}

// print
void TermsBST::print(ostream& os)
{
	// recursive print in order function to print nodes in order
	printInOrder(root, os);
}

// recursive print in order function to print nodes in order
void TermsBST::printInOrder(TermsBSTNode* node, ostream& os)
{
    // if node is not null
    if (node != nullptr)
    {
        printInOrder(node->getLeft(), os);      // print left node
        os << node->getName() << "/" << node->getAge() << "/" << node->getDate() << "/" << node->getExpirationDate() << endl;       // print node
        printInOrder(node->getRight(), os);     // print right node
    }
}
// find min node
TermsBSTNode* TermsBST::findMinNode(TermsBSTNode* node)
{
    // loop to find min node
    while (node->getLeft() != nullptr)
    {
        node = node->getLeft();
    }
    return node;
}

// remove
void TermsBST::remove(string name, string expiration_date)
{
	// recursive remove function to delete node
	root = remove(root, name, expiration_date);
}

// recursive remove function to delete node
TermsBSTNode* TermsBST::remove(TermsBSTNode* node, string name, string expiration_date)
{
    // if the tree is empty, return a new node
    if (node == nullptr)
    {
        return nullptr;
    }

    // determine which side to delete node
    if (expiration_date < node->getExpirationDate())
    {
        node->setLeft(remove(node->getLeft(), name, expiration_date));        // get left node
    }
    else if (expiration_date > node->getExpirationDate())
    {
        node->setRight(remove(node->getRight(), name, expiration_date));      // get right node
    }
    else
    {
        // node with only one child
        if (node->getLeft() == nullptr)
        {
            // get right node
            TermsBSTNode* temp = node->getRight();
            delete node;
            return temp;
        }
        else if (node->getRight() == nullptr)
        {
            // get left node
            TermsBSTNode* temp = node->getLeft();
            delete node;
            return temp;
        }

        // node with two children
        TermsBSTNode* temp = findMinNode(node->getRight());     // find min node

        // load the data of the inorder
        node->setName(temp->getName());
        node->setAge(temp->getAge());
        node->setDate(temp->getDate());
        node->setExpirationDate(temp->getExpirationDate());

        // delete the data of the inorder
        node->setRight(remove(node->getRight(), temp->getName(), temp->getExpirationDate()));
    }

    return node;
}