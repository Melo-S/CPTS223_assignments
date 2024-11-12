#include "testLinearProbing.h"
#include "utils.h"

using namespace std;

vector<Employee> addRandomEntries(int numEntries, ProbingHash<Employee> & aHashTable)
{
    vector<string> names = generateRandomNames(numEntries);
    vector<int> salaries = generateRandomIntegers(numEntries);
    vector<Employee> employeeVector;
    for (int i = 0; i < numEntries; i++)
    {
        Employee emp(names[i], double( salaries[i]) );
        aHashTable.insert( emp );
        employeeVector.push_back( emp );
    }
    return employeeVector;
}

void searchEachEntryOnce(vector<Employee> aVector, ProbingHash<Employee> & aHashTable)
{
    for (Employee element : aVector)
    {
        if (aHashTable.contains(element) == 0)
        {
            // cout << "ERROR!" << endl;
        }    
    }
}

void initializeHash(ProbingHash<Employee> & aHashTable)
{
    aHashTable.insert(emp1);
    aHashTable.insert(emp2);
    aHashTable.insert(emp3);
    aHashTable.insert(emp4);
    cout << "(1.0) INITILIZATION done: Hash Table with Linear Probing..." << endl;
}

void testInsertToHash(ProbingHash<Employee> & aHashTable)
{
    cout << "(1.1) TEST INSERT TO HASH TABLE" << endl;
    cout << "Alice is in the hash table: " << aHashTable.contains(emp1) << endl;
    cout << "Bob is in the hash table: " << aHashTable.contains(emp2) << endl;
    cout << "Charlie is in the hash table: " << aHashTable.contains(emp3) << endl;
    cout << "David is in the hash table: " << aHashTable.contains(emp4) << endl;

    cout << "Load factor = " << aHashTable.readLoadFactor();
    cout << "; Current size = " << aHashTable.readCurrentSize();
    cout << "; Array size = " << aHashTable.readArraySize() << endl;
}

void testRemoveFromHash(ProbingHash<Employee> & aHashTable)
{
    cout << "(1.2) TEST REMOVE FROM HASH TABLE" << endl;
    aHashTable.remove(emp4);
    if (aHashTable.contains(emp4) != 1)
    { 
        cout << "Succesful! David is NOT in the hash table: " << aHashTable.contains(emp4) << endl;
        cout << "Load factor = " << aHashTable.readLoadFactor();
        cout << "; Current size = " << aHashTable.readCurrentSize();
        cout << "; Array size = " << aHashTable.readArraySize() << endl;
    }
    else
        cout << "REMOVE TEST FAILED!" << endl;
}

void testRehash(ProbingHash<Employee> & aHashTable)
{
    cout << "(1.3) TEST REHASH" << endl;
    int numEntries = 10000;
    auto start = chrono::high_resolution_clock::now();
    vector<Employee> employeeVector = addRandomEntries(numEntries, aHashTable);
    auto end = chrono::high_resolution_clock::now();
    auto elapsedTime = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    cout << "Add " << numEntries << " entries. Elapsed time: " << elapsedTime << "ms" << endl;
    cout << "Load factor = " << aHashTable.readLoadFactor();
    cout << "; Current size = " << aHashTable.readCurrentSize();
    cout << "; Array size = " << aHashTable.readArraySize() << endl;

    start = chrono::high_resolution_clock::now();
    searchEachEntryOnce(employeeVector, aHashTable);
    end = chrono::high_resolution_clock::now();
    elapsedTime = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Search each entry once. Elapsed time: " << elapsedTime << "ms" << endl;
}