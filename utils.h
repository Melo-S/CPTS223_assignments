#ifndef UTILS_H
#define UTILS_H

#include <random>
#include <string>
#include "Employee.h"

using namespace std;

extern Employee emp1;
extern Employee emp2;
extern Employee emp3;
extern Employee emp4;

bool isPrime( int n );
int nextPrime( int n );
string generateARandomName(int length);
vector<string> generateRandomNames(int numNames);
int generateARandomInteger(int MAXNUM);
vector<int> generateRandomIntegers(int numNumbers);

#endif