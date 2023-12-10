#include "TermsList.h"

// constructor
TermsList::TermsList()
{
    head = nullptr;
}

// destructor
TermsList::~TermsList()
{
	// delete all nodes
	while (head != nullptr)
	{
		TermsListNode* temp = head;
		head = head->getNext();
		delete temp;
	}
}

// insert a new node with terms
void TermsList::insert(char terms)
{
	if (head == nullptr)
	{
		head = new TermsListNode(terms);		// declare new node to head
	}

	TermsListNode* current = head;
	TermsListNode* prev = nullptr;

	while (current != nullptr)
	{
		// compare the size of terms / A, B, C, D
		if (current->getTerms() == terms)
		{
			current->incrementMembercount(); // increase member count if term exists
			return;
		}
		else if (current->getTerms() > terms)
		{
			// insert new node before the current node
			TermsListNode* newNode = new TermsListNode(terms);
			newNode->setNext(current);

			if (prev == nullptr)
			{
				head = newNode;
			}
			else
			{
				prev->setNext(newNode);
			}
			return;
		}

		prev = current;
		current = current->getNext();

		// term insert
		prev->setNext(new TermsListNode(terms));
	}
}

// search for a node with terms and return its pointer
TermsListNode* TermsList::search(char terms)
{
	TermsListNode* current = head;
	while (current != nullptr)
	{
		if (current->getTerms() == terms)
		{
			return current;
		}

		current = current->getNext();
	}

	return nullptr;
}

// delete the node with terms from the list
void TermsList::remove(char terms)
{
	if (head == nullptr)
	{
		return;
	}

	if (head->getTerms() == terms)
	{
		// update the head to the next node
		TermsListNode* temp = head;
		head = head->getNext();
		delete temp;
		return;
	}

	TermsListNode* current = head;

	while (current->getNext() != nullptr && current->getNext()->getTerms() != terms)
	{
		current = current->getNext();
	}

	if (current->getNext() != nullptr)
	{
		// if the next node matches, delete
		TermsListNode* temp = current->getNext();
		current->setNext(temp->getNext());
		delete temp;
	}
}
