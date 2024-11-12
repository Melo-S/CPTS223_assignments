#ifndef SEPARATE_CHAINING_H
#define SEPARATE_CHAINING_H

#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <functional>
#include <iostream>
#include "Employee.h"
#include "utils.h"

using namespace std;

template <typename HashedObj>
class ChainingHash
{
  public:
    explicit ChainingHash( int size = 101 ) : currentSize{ 0 }
      { theLists.resize( 101 ); }

      bool contains(const HashedObj& x) const {
          auto& whichList = theLists[myhash(x)];
          return std::find(whichList.begin(), whichList.end(), x) != whichList.end();
      }


      void makeEmpty() {
          for (auto& thisList : theLists)
              thisList.clear();  // Clear each linked list
          currentSize = 0;       // Resets size
      }


      bool insert(const HashedObj& x) {
          auto& whichList = theLists[myhash(x)];
          if (std::find(whichList.begin(), whichList.end(), x) != whichList.end())
              return false;  // if its present then do nothing

          whichList.push_back(x);  // Add a new element to the list
          currentSize++;

          if (loadFactor() >= 1.0)  // Rehash if the load factor exceeds >= 1
              rehash();
          return true;
      }

    
      bool insert(HashedObj&& x) {
          auto& whichList = theLists[myhash(x)];
          if (std::find(whichList.begin(), whichList.end(), x) != whichList.end())
              return false;  // if its present then do nothing

          whichList.push_back(std::move(x));  // Moves the element
          currentSize++;

          if (loadFactor() >= 1.0)
              rehash();
          return true;
      }



      bool remove(const HashedObj& x) {
          auto& whichList = theLists[myhash(x)];
          auto itr = std::find(whichList.begin(), whichList.end(), x);

          if (itr == whichList.end())
              return false;  // if nothing is present then dont remove

          whichList.erase(itr);  // Removes the element
          currentSize--;
          return true;
      }


    double readLoadFactor() 
    {
        return loadFactor();
    }

    double readCurrentSize() 
    {
        return currentSize;
    }

    double readArraySize() 
    {
        return theLists.size();
    }

  private:
    vector<list<HashedObj>> theLists;   
    int currentSize;

    void rehash() {
        vector<list<HashedObj>> oldLists = theLists;

        // Create a new large empty table
        theLists.resize(nextPrime(2 * theLists.size()));
        for (auto& thisList : theLists)
            thisList.clear();

        currentSize = 0;
        for (auto& thisList : oldLists)
            for (auto& x : thisList)
                insert(std::move(x));  // Reinsert elements into the new table
    }


    size_t myhash( const HashedObj & x ) const
    {
        static hash<HashedObj> hf;
        return hf( x ) % theLists.size( );
    }

    double loadFactor() {
        return static_cast<double>(currentSize) / theLists.size();
    }
};

#endif
