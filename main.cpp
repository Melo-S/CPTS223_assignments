#include "OpenMP.h"
#include "Heap.h"

void runOpenMP()
{
    hello_world();
    calSum();
    calMax();
}

void runHeap()
{
    int data_size = 10000;
    int *data = new int[data_size];
    for (int i = 0; i < data_size; ++i)
    {
        data[i] = rand() % data_size;
    }
    auto *hp = new Heap<int>();
    for (int i = 0; i < data_size; ++i)
    {
        hp->push(data[i]);
    }

    // Sort these values using stl
    std::vector<int> vect(data, data + data_size);
    std::sort(vect.begin(), vect.end());

    for (int i = 0; i < data_size; ++i)
    {
        // Compare the pop result with the value sorted by stl
        // If the two required functions are correct, the assertion should pass
        assert(vect[i] == hp->pop());
    }
    std::cout<< "(3) Test runHeap() assert pass!" << std::endl;
}

int main(int argc, char *argv[])
{
    runOpenMP();
    runHeap();
}