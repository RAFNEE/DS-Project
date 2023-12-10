#pragma once
#include "MemberQueueNode.h"

using namespace std;

class MemberQueue
{
private:
    int size = 0;       // current size of queue
    const int Queue_Size = 100;     // maximum size of queue
    MemberQueueNode* front;     // the front of queue
    MemberQueueNode* rear;      // the rear of queue

public:
    MemberQueue();      // constructor
    ~MemberQueue();     // destructor

    bool empty();       // empty function
    bool full();        // full function
    void push(string name, int age, string date, char terms);       // push data in queue
    MemberQueueNode* pop();      // pop data from queue
    MemberQueueNode frontNode();        // get front node
};
