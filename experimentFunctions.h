#ifndef EXPERIMENT_FUNCTIONS_H
#define EXPERIMENT_FUNCTIONS_H
#include "AVLTree.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <random>
#include <cstdlib>  
#include <ctime>   
#include <chrono>
#include <cmath>

// Utility function for log base 2
double log2(double d);

// Test functions for experiment 1
bool testBST(AVLTree<int>* avl);
bool testBalanced(AVLTree<int>* avl);
bool testContains(AVLTree<int>* avl, int numData);

// Test functions for experiment 2
bool testSize(AVLTree<int>* avl, int targetNumIntegers);
bool testHeight(AVLTree<int>* avl);

// Random insertion and removal functions for experiment 2
void insertRandomIntegers(AVLTree<int>* avl, int numIntegers);
void deleteRandomIntegers(AVLTree<int>* avl, int numDelete);

// Experiment functions
void experiment1(int numIntegers);
void stage1(AVLTree<int>* avl, int numIntegers);
void stage2(AVLTree<int>* avl, int numRandomInsertRemove);

#endif // EXPERIMENT_FUNCTIONS_H
