#ifndef QUEUE_H 
#define QUEUE_H
#define SIZE 10 

class queue
{
    int* arr;        // array to store elements
    int capacity;    // maximum capacity of the queue
    int front;       // front points to front element in the queue
    int rear;        // rear points to last element in the queue
    int count;       // current size of the queue

public:
    queue(int size = SIZE);  // constructor
    ~queue();                // destructor

    int dequeue();
    int enqueue(int x);
    int peek();
    int size();
    bool isEmpty();
    bool isFull();
};
#endif 