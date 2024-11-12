#include <iostream>
#include <ctime>
#include <chrono>
#include "LinearProbing.h"

using namespace std;

vector<Employee> addRandomEntries(int numEntries, ProbingHash<Employee> & aHashTable);
void searchEachEntryOnce(vector<Employee> aVector, ProbingHash<Employee> & aHashTable);
void initializeHash(ProbingHash<Employee> & aHashTable);
void testInsertToHash(ProbingHash<Employee> & aHashTable);
void testRemoveFromHash(ProbingHash<Employee> & aHashTable);
void testRehash(ProbingHash<Employee> & aHashTable);

