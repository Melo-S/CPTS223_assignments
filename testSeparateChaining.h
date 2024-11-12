#include <iostream>
#include <ctime>
#include <chrono>
#include "SeparateChaining.h"

using namespace std;

vector<Employee> addRandomEntries(int numEntries, ChainingHash<Employee> & aHashTable);
void searchEachEntryOnce(vector<Employee> aVector, ChainingHash<Employee> & aHashTable);
void initializeHash(ChainingHash<Employee> & aHashTable);
void testInsertToHash(ChainingHash<Employee> & aHashTable);
void testRemoveFromHash(ChainingHash<Employee> & aHashTable);
void testRehash(ChainingHash<Employee> & aHashTable);

