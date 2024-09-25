#include "testQueue.h"
#include "queue.h"
#include <iostream>
#include <limits>
/* Test ID: Empty queue check - EQC
Unit: queue::isEmpty ()
Description: test to determine if queue::isEmpty () returns 1 if a queue object
is empty.
Test steps:
1. Construct an empty queue object
2. Invoke queue::isEmpty ()
3. Conditionally evaluate the value returned by queue::isEmpty ()
Test data: size = 0
Precondition: queue object is empty
Postcondition: queue object is still empty
Expected result: queue is empty; 1 is returned
Actual result: queue is empty; 1 is returned
Status: passed
*/

// Test for an empty queue
void testQueue::testIsEmpty()
{
    queue* newqueue = new queue(2);
    bool result = newqueue->isEmpty();

    if (result)
    {
        std::cout << "Expected result: queue is empty; true is returned\n";
        std::cout << "Actual result: queue is empty; true is returned\n";
        std::cout << "Status: passed\n";
    }
    else
    {
        std::cout << "Expected result: queue is empty; true is returned\n";
        std::cout << "Actual result: queue is not empty; false is returned\n";
        std::cout << "Status: failed\n";
    }
}

// Test to see if the queue is full
void testQueue::testIsFull()
{
    queue* newqueue = new queue(2);

    newqueue->enqueue(100);
    newqueue->enqueue(200);
    bool result = newqueue->isFull();

    if (result)
    {
        std::cout << "Expected result: queue is full; true is returned\n";
        std::cout << "Actual result: queue is full; true is returned\n";
        std::cout << "Status: passed\n";
    }
    else
    {
        std::cout << "Expected result: queue is full; true is returned\n";
        std::cout << "Actual result: queue is not full; false is returned\n";
        std::cout << "Status: failed\n";
    }
}

// Test for the queue size
void testQueue::testsize()
{
    queue* newqueue = new queue(5);

    newqueue->enqueue(100);
    newqueue->enqueue(200);
    newqueue->enqueue(300);
    newqueue->enqueue(400);
    newqueue->enqueue(500);

    int siz = newqueue->size();
    if (siz == 5)
    {
        std::cout << "Expected result: queue size is 5; 5 is returned\n";
        std::cout << "Actual result: queue size is 5; 5 is returned\n";
        std::cout << "Status: passed\n";
    }
    else
    {
        std::cout << "Expected result: queue size is 5; 5 is returned\n";
        std::cout << "Actual result: queue size is not 5; " << siz << " is returned\n";
        std::cout << "Status: failed\n";
    }
}

// Test for the dequeue operations
void testQueue::testdequeue()
{
    queue* newqueue = new queue(5);

    newqueue->enqueue(1);
    newqueue->enqueue(2);
    newqueue->enqueue(3);
    newqueue->enqueue(4);
    newqueue->enqueue(5);

    int result = newqueue->dequeue();
    if (result == 1)
    {
        std::cout << "Expected result: dequeued number is 1; 1 is returned\n";
        std::cout << "Actual result: dequeued number is 1; 1 is returned\n";
        std::cout << "Status: passed\n";
    }
    else
    {
        std::cout << "Expected result: dequeued number is 1; 1 is returned\n";
        std::cout << "Actual result: dequeued number is not 1; " << result << " is returned\n";
        std::cout << "Status: failed\n";
    }

    // Testing for underflow
    queue* newqueue2 = new queue(5);
    int result1 = newqueue2->dequeue();

    if (result1 == std::numeric_limits<int>::min())
    {
        std::cout << "Expected result: underflow error; " << std::numeric_limits<int>::min() << " is returned\n";
        std::cout << "Actual result: underflow error; " << result1 << " is returned\n";
        std::cout << "Status: passed\n";
    }
    else
    {
        std::cout << "Expected result: underflow error; " << std::numeric_limits<int>::min() << " is returned\n";
        std::cout << "Actual result: something else; " << result1 << " is returned\n";
        std::cout << "Status: failed\n";
    }
}

// Test for enqueue operations
void testQueue::testenqueue()
{
    queue* newqueue = new queue(1);

    int result = newqueue->enqueue(1);
    if (result == 1)
    {
        std::cout << "Expected result: enqueued number is 1; 1 is returned\n";
        std::cout << "Actual result: enqueued number is 1; 1 is returned\n";
        std::cout << "Status: passed\n";
    }
    else
    {
        std::cout << "Expected result: enqueued number is 1; 1 is returned\n";
        std::cout << "Actual result: enqueued number is not 1; " << result << " is returned\n";
        std::cout << "Status: failed\n";
    }

    // Test for overflow
    queue* newqueue2 = new queue(0);

    int result1 = newqueue2->enqueue(1);

    if (result1 == std::numeric_limits<int>::max())
    {
        std::cout << "Expected result: overflow error; " << std::numeric_limits<int>::max() << " is returned\n";
        std::cout << "Actual result: overflow error; " << result1 << " is returned\n";
        std::cout << "Status: passed\n";
    }
    else
    {
        std::cout << "Expected result: overflow error; " << std::numeric_limits<int>::max() << " is returned\n";
        std::cout << "Actual result: something else; " << result1 << " is returned\n";
        std::cout << "Status: failed\n";
    }
}

// Test for peek operations
void testQueue::testpeek()
{
    queue* newqueue = new queue(5);

    newqueue->enqueue(10);
    newqueue->enqueue(20);
    newqueue->enqueue(30);
    newqueue->enqueue(40);
    newqueue->enqueue(50);

    int result = newqueue->peek();
    if (result == 10)
    {
        std::cout << "Expected result: peek number is 10\n";
        std::cout << "Actual result: peek number is 10\n";
        std::cout << "Status: passed\n";
    }
    else
    {
        std::cout << "Expected result: peek number is 10; 10 is returned\n";
        std::cout << "Actual result: peek number is not 10; " << result << " is returned\n";
        std::cout << "Status: failed\n";
    }

    // Test underflow case for peek
    queue* newqueue2 = new queue(1);
    int result1 = newqueue2->peek();

    if (result1 == std::numeric_limits<int>::min())
    {
        std::cout << "Expected result: underflow error; " << std::numeric_limits<int>::min() << " is returned\n";
        std::cout << "Actual result: underflow error; " << result1 << " is returned\n";
        std::cout << "Status: passed\n";
    }
    else
    {
        std::cout << "Expected result: underflow error; " << std::numeric_limits<int>::min() << " is returned\n";
        std::cout << "Actual result: something else; " << result1 << " is returned\n";
        std::cout << "Status: failed\n";
    }
}