#include "MemberQueue.h"

// constructor
MemberQueue::MemberQueue()
{
    front = nullptr;
    rear = nullptr;
}

// destructor
MemberQueue::~MemberQueue()
{
    // if queue is not empty, delete all nodes
    while (!empty())
    {
        MemberQueueNode* temp = front;
        front = front->getNext();
        delete temp;
    }
}

// empty function
bool MemberQueue::empty()
{
    return front == nullptr;        // if front is nullptr, queue is empty
}

// full function
bool MemberQueue::full()
{
    return size >= Queue_Size;      // if size is greater than or equal to Queue_Size, queue is full
}

// push data in queue
void MemberQueue::push(string name, int age, string date, char terms)
{
    // if queue is full, print error
    if (full())
    {
        cout << "Queue is full" << endl;
    }

    MemberQueueNode* newNode = new MemberQueueNode(name, age, date, terms);     // create new node

    // if queue is empty, set front and rear to newNode
    if (empty())
    {
        front = newNode;
        rear = newNode;
    }
    // set rear's next node to newNode and set rear to newNode
    else
    {
        rear->setNext(newNode);
        rear = newNode;
    }

    size++;     // increment size of queue
}

// pop data in queue
MemberQueueNode* MemberQueue::pop()
{
    if (empty())
    {
        cout << "Queue is empty" << endl;
        return nullptr; // return nullptr to find exception
    }

    MemberQueueNode* temp = front;
    front = front->getNext();
    return temp;
}


// frontNode function
MemberQueueNode MemberQueue::frontNode()
{
    // if queue is empty, print error
    if (empty())
    {
        cout << "Queue is empty" << endl;
    }

    return MemberQueueNode(front->getName(), front->getAge(), front->getDate(), front->getTerms());     // return front node
}
