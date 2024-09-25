// This code was taken from https://www.techiedelight.com/queue-implementation-cpp/
// The code has been modified from the original to provide opportunities to learn
/* Things that could be improved in the code:
1. There should be more comments to clarify what's happening in the code.
2. The different classes should be in separate header files for better organization.
3. The testing could be more efficient and cover more scenarios.
4. Some variables could have clearer names so it's easier to understand their purpose.
5. The code could be structured or layered better for readability and maintenance.
*/
#include "testQueue.h"
#include <iostream>

// Main functions
int main()
{
    testQueue* tQueue = new testQueue();

    std::cout << "Testing isEmpty\n";
    tQueue->testIsEmpty();
    getchar();
    system("cls");

    std::cout << "Testing isFull\n";
    tQueue->testIsFull();
    getchar();
    system("cls");

    std::cout << "Testing size\n";
    tQueue->testsize();
    getchar();
    system("cls");

    std::cout << "Testing dequeue\n";
    tQueue->testdequeue();
    getchar();
    system("cls");

    std::cout << "Testing enqueue\n";
    tQueue->testenqueue();
    getchar();
    system("cls");

    std::cout << "Testing peek\n";
    tQueue->testpeek();
    getchar();
    system("cls");

    return 0;
}