/*
Inserting the randomly generated integers into a BST generally gives a height in the order of:

Your answer:O(log n) on average, where n is the number of nodes in the tree.


*/

#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <chrono>
#include <cmath>
#include <random>
#include "BST.h"

double log2(double d)
{
    return log(d) / log(2); // log() use e as base
}

void insertRandomIntegers(BST<int>* root, int numIntegers)
{
    // The range of random integers
    const int minValue = -1000000000;
    const int maxValue = 1000000000;
    int randomInteger;

    // Generate a uniform distribution to generate random integers
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<std::mt19937::result_type> dist(minValue, maxValue);

    // Generate random integers (without duplicates) from the specified range
    for (int i = 0; i < numIntegers; ++i) {
        randomInteger = dist(rng);
        while (root->contains(randomInteger) == true)
        {
            randomInteger = dist(rng);
        }
        root->insert(randomInteger);
    }
}

int main()
{
    // Seed the random number generator with the current time
    srand(static_cast<unsigned>(time(0)));

    // (i) test member functions with simple 6 inputs
    BST<int>* bst = new BST<int>();
    bst->insert(11);
    bst->insert(1);
    bst->insert(6);
    bst->insert(-1);
    bst->insert(-10);
    bst->insert(100);

    // a demo for findMin and findMax if "insert" is successfully implemented
    // cout << "(0) findMin = " << bst->findMin() << endl;
    // cout << "    findMax = " << bst->findMax() << endl;

    cout << "(1.1) Print BST (in-order traversal): " << endl << " ";
    bst->printInOrder();
    cout << endl;

    cout << "(1.2) Print BST in level order: " << endl;
    bst->printLevels();

    cout << "(1.3) Is 100 in BST? true (1) or false (0): " << bst->contains(100) << endl;

    cout << "(1.4) Is 9 in BST? true (1) or false (0): " << bst->contains(9) << endl;

    cout << "(1.5) BST size: " << bst->treeSize() << endl;

    cout << "(1.6) Height of BST: " << bst->treeHeight() << endl;

    cout << "(1.7) Print max path: " << endl << " ";
    bst->printMaxPath();
    cout << endl;

    bst->remove(11);
    cout << "(1.8) Removing 11, print BST (in-order traversal): " << endl << " ";
    bst->printInOrder();
    cout << endl;

    cout << "(1.9) Print BST in level order: " << endl;
    bst->printLevels();

    cout << "(1.10) BST size: " << bst->treeSize() << endl;

    // Delete this bst
    delete bst;

    return 0;
}