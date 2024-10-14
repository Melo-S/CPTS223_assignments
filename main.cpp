#include "AVLTree.h"
#include "experimentFunctions.h"
#include <iostream>

using namespace std;

int main() {
    // Experiment 1: Test BST order and AVL height condition
    cout << "================================ Experiment 1 ================================" << endl;
    int numIntegers = 20;  // Keep this for Experiment 1
    experiment1(numIntegers);
    cout << endl;

    // Experiment 2: Test whether the average depth of AVL trees is invariant to random insert/remove pair operations
    cout << "============================ Experiment 2, Stage 1 ============================" << endl;

    // Stage 1: Insert 3000 random integers into AVL BST
    numIntegers = 3000;  // Update for stage 1
    AVLTree<int>* avl = new AVLTree<int>();
    stage1(avl, numIntegers);
    cout << endl;

    // Stage 2: Perform 250,000 random insert/delete operations
    int numRandomInsertRemove = 250000;  // Confirm the correct number of operations
    cout << "========== Experiment 2, Stage 2 (after " << numRandomInsertRemove << " random insert/delete) ==========" << endl;
    stage2(avl, numRandomInsertRemove);

    // Delete this AVL tree
    delete avl;

    return 0;
}
