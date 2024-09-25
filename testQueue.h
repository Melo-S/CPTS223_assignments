#ifndef TESTQUEUE_H  
#define TESTQUEUE_H
#include "queue.h"   
#include <iostream>
#include <cstdlib>

using namespace std;

class testQueue
{
public:
    void testIsEmpty();
    void testIsFull();
    void testsize();
    void testdequeue();
    void testenqueue();
    void testpeek();
};
#endif 