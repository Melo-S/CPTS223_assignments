
// experimentFunctions.cpp
#include "experimentFunctions.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <limits>

using namespace std;

// Insert random integers into the AVL tree
void insertRandomIntegers(AVLTree<int>* avl, int numIntegers) {
    const int minValue = -1000000000; // Adjusted to prevent overflow
    const int maxValue = 1000000000;  // Adjusted to prevent overflow

    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> uni(minValue, maxValue);

    for (int i = 0; i < numIntegers; ++i) {
        int randomValue = uni(rng);
        while (avl->contains(randomValue)) {
            randomValue = uni(rng);
        }
        avl->insert(randomValue);
    }
}

void deleteRandomIntegers(AVLTree<int>* avl, int numDelete)
{
    int treeSize = avl->treeSize();
    // The range of random integers for ranks in AVL
    const int minValue = 1;
    const int maxValue = treeSize;
    int randomInteger;

    // Generate a uniform distribution to generate random integers
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<std::mt19937::result_type> dist(minValue, maxValue); 

    // Randomly delete a node by its rank in AVL
    for (int i = 0; i < numDelete; i++) {
        randomInteger = dist(rng);
        avl->removeByRank(randomInteger);
    }
}

bool testBST(AVLTree<int>* avl) {
    return avl->isBST();
}

bool testBalanced(AVLTree<int>* avl) {
    return avl->isBalanced();
}

bool testContains(AVLTree<int>*avl, int numIntegers) {
    bool flag = 1;
    for (int i = 0; i < numIntegers; i++)
    {
        if (i % 2 == 1 && avl->contains(i) != 1) // odd: should contain
        {
            flag = 0;
            break;
        }
        if (i % 2 == 0 && avl->contains(i) == 1) // even: should not contain
        {
            flag = 0;
            break;
        }
    }
    return flag;
}

bool testSize(AVLTree<int> * avl, int targetNumIntegers) {
    return (avl->treeSize() == targetNumIntegers);
}

bool testHeight(AVLTree<int>* avl) {
    return (avl->readRootHeight() == avl->computeHeight());
}

void experiment1(int numIntegers) {

    AVLTree<int>* tree1 = new AVLTree<int>(); //insert odd numbers in ascending order
    AVLTree<int>* tree2 = new AVLTree<int>(); //insert odd numbers in descending order
    AVLTree<int>* tree3 = new AVLTree<int>(); // insert odd numbers in random order

    vector<int> testValues;
    vector<int> testValuesReversed;
    vector<int> testValuesShuffled;
    for (int i = 0; i < numIntegers; i++)
    {
        if (i % 2 != 0)
        {
            // cout << i << " ";
            testValues.push_back(i);
            testValuesReversed.push_back(i);
            testValuesShuffled.push_back(i);
        }
    }
    reverse(testValuesReversed.begin(), testValuesReversed.end());
    auto rng = default_random_engine{};
    shuffle(testValuesShuffled.begin(), testValuesShuffled.end(), rng);

    for (int i = 0; i < testValues.size(); i++)
    {
        tree1->insert(testValues[i]);
        tree2->insert(testValuesReversed[i]);
        tree3->insert(testValuesShuffled[i]);
    }

    bool testBSTOrder1 = testBST( tree1 );
    bool testBalanced1 = testBalanced( tree1 );
    bool testContains1 = testContains(tree1, numIntegers);
    cout << "(EXP1.1) Tree1 AVL validation: " << (testBSTOrder1 && testBalanced1 && testContains1) << endl;
    cout << "         BST order: " << testBSTOrder1 << "; AVL balanced: " << testBalanced1 << "; Contains generated odd int only: " << testContains1 << endl;

    bool testBSTOrder2 = testBST( tree2 );
    bool testBalanced2 = testBalanced( tree2 );
    bool testContains2 = testContains(tree2, numIntegers);
    cout << "(EXP1.2) Tree2 AVL validation: " << (testBSTOrder2 && testBalanced2) << endl;
    cout << "         BST order: " << testBSTOrder2 << "; AVL balanced: " << testBalanced2 << "; Contains generated odd int only: " << testContains2 << endl;

    bool testBSTOrder3 = testBST( tree3 );
    bool testBalanced3 = testBalanced( tree3 );
    bool testContains3 = testContains(tree3, numIntegers);
    cout << "(EXP1.3) Tree3 AVL validation: " << (testBSTOrder3 && testBalanced3) << endl;
    cout << "         BST order: " << testBSTOrder3 << "; AVL balanced: " << testBalanced3 << "; Contains generated odd int only: " << testContains3 << endl;

    if ( testBSTOrder1 && testBalanced1 && testContains1 && testBSTOrder2 && testBalanced2 && testContains2 && testBSTOrder3 && testBalanced3 && testContains3 )
    {
        cout << "(EXP1.4) Conclusion: my AVL tree implementation is correct" << endl;
    }
    else
    {
        cout << "(EXP1.4) Conclusion: my AVL tree implementation is incorrect" << endl;
    }

    delete tree1;
    delete tree2;
    delete tree3;
}

void stage1(AVLTree<int>* avl, int numIntegers) {
    // compute how many extra data we will insert into AVL compared with Figure 4.29 (500 nodes there) relatively
    double relativeSizeChangeFromTextbook = (numIntegers - 500.0) / 500.0;

    auto start = chrono::high_resolution_clock::now();
    insertRandomIntegers(avl, numIntegers);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    
    cout << "(EXP2.1) Inserted " << numIntegers << " random integers. " << "Execution time: " << duration.count() << " ms" << endl;
    
    cout << "(EXP2.2) AVL balanced? " << testBalanced( avl ) << endl;

    cout << "(EXP2.3) After inserting " << numIntegers << " random integers, AVL tree size: " << avl->treeSize() << endl;
    cout << "         Comparing with the BST in Figure 4.29 of Textbook: ";
    if (relativeSizeChangeFromTextbook > 0) 
        cout << (100*relativeSizeChangeFromTextbook) << "% more nodes" << endl;
    else 
        cout << (-100*relativeSizeChangeFromTextbook) << "% less nodes" << endl;
    
    cout << "(EXP2.4) Compute height (DFS): " << avl->computeHeight() << "; root->height: " << avl->readRootHeight() << endl;
    cout << "         testHeigth? " << testHeight(avl) << endl;
    
    double averageDepth = avl->averageDepth();
    cout << "(EXP2.5) The average depth: " << averageDepth << " (v.s. log2(n)=" << log2(numIntegers) << ")" << endl;
    double relativeChangeFromTextbookInitial = (averageDepth - 9.98) / 9.98;
    cout << "         Comparing with the BST in Figure 4.29 of Textbook (9.98): ";
    if (relativeChangeFromTextbookInitial > 0)
        cout << (relativeChangeFromTextbookInitial*100) << "% greater" << endl;
    else
        cout << (-relativeChangeFromTextbookInitial*100) << "% less" << endl;
}

void stage2(AVLTree<int>* avl, int numRandomInsertRemove) {
    // use treeSize() to compute how many extra data we will insert into AVL compared with Figure 4.29 (500 nodes there) relatively
    int numIntegers = avl->treeSize();
    double relativeSizeChangeFromTextbook = ( numIntegers - 500.0 ) / 500.0;
    
    // use averageDepth() to compute what is the initial average depth before stage 2
    double averageDepth = avl->averageDepth();

    auto start = chrono::high_resolution_clock::now();
    for (int i=0; i<numRandomInsertRemove; i++) {
        insertRandomIntegers(avl, 1);
        deleteRandomIntegers(avl, 1);
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    
    cout << "(EXP2.6) Random insert/remove " << numRandomInsertRemove << " random integers. " << "Execution time: " << duration.count() << " ms" << endl;
    cout << "(EXP2.7) AVL balanced? " << testBalanced( avl ) << endl;

    cout << "(EXP2.8) Now AVL tree size: " << avl->treeSize();
    cout << ", testSize()? " << testSize( avl, numIntegers ) << endl;
    cout << "         Comparing with the BST in Figure 4.30 of Textbook: ";
    if (relativeSizeChangeFromTextbook > 0) 
        cout << (100*relativeSizeChangeFromTextbook) << "% more nodes" << endl;
    else 
        cout << (-100*relativeSizeChangeFromTextbook) << "% less nodes" << endl;
    
    cout << "(EXP2.9) Compute height (DFS): " << avl->computeHeight() << "; root->height: " << avl->readRootHeight() << endl;
    cout << "         testHeigth? " << testHeight(avl) << endl;

    double newAverageDepth = avl->averageDepth();
    double relativeChangeFromInitial = ( newAverageDepth - averageDepth ) / newAverageDepth;
    double relativeChangeFromTextbook = ( newAverageDepth - 12.51 ) / 12.51;
    cout << "(EXP2.10) New average depth: " << newAverageDepth << " (v.s. log2(n)=" << log2(numIntegers) << ")" << endl;
    cout << "          Comparing with the initial AVL (" << averageDepth << "): ";
    if (relativeChangeFromInitial > 0)
        cout << (relativeChangeFromInitial*100) << "% more" << endl;
    else
        cout << (-relativeChangeFromInitial*100) << "% less" << endl;
    if ( abs( relativeChangeFromInitial ) <= 0.01 )
        cout << "           ==> average depth of my AVL tree does not change significantly (<=1%)" << endl;

    cout << "          Comparing with the BST in Figure 4.30 of Textbook (12.51): ";
    if (relativeChangeFromTextbook > 0)
        cout << (relativeChangeFromTextbook*100) << "% more" << endl;
    else
    {
        cout << (-relativeChangeFromTextbook*100) << "% less" << endl;
        if (-relativeChangeFromTextbook > 0.1)
            cout << "           ==> my AVL tree improves the average depth over BST significantly (>10%)" << endl;
    }
}