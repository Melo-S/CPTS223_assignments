#include "queue.h"
#include <iostream>
#include <limits>

// Constructor to initialize queue
queue::queue(int size)
{
    arr = new int[size];
    capacity = size;
    front = 0;
    rear = -1;
    count = 0;
}

// Destructor to free memory allocated to the queue
queue::~queue()
{
    delete[] arr;
}

// Utility function to remove front element from the queue
int queue::dequeue()
{
    if (isEmpty())

    {
        std::cout << "UnderFlow\nProgram Terminated\n";
        return std::numeric_limits<int>::min();  // Return error code
    }

    int removedElement = arr[front];  // Store the front element before updating the index
    front = (front + 1) % capacity;
    count--;
    return removedElement;
}

// Utility function to add an item to the queue
int queue::enqueue(int item)
{
    if (isFull())
    {
        std::cout << "OverFlow\nProgram Terminated\n";
        return std::numeric_limits<int>::max();  // Return error code
    }

    rear = (rear + 1) % capacity;
    arr[rear] = item;
    count++;
    return arr[rear];  // Return the inserted element
}

// Utility function to return front element in the queue
int queue::peek()
{
    if (isEmpty())
    {
        std::cout << "UnderFlow\nProgram Terminated\n";
        return std::numeric_limits<int>::min();  // Return error code
    }
    return arr[front];
}

// Utility function to return the current size of the queue
int queue::size()
{
    return count;
}

// Utility function to check if the queue is empty
bool queue::isEmpty()
{
    return (count == 0);
}

// Utility function to check if the queue is full
bool queue::isFull()
{
    return (count == capacity);
}