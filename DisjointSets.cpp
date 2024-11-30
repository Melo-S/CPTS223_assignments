#include "DisjointSets.h"

/**
 * Construct the disjoint sets object.
 * numElements is the initial number of disjoint sets.
 */
DisjointSets::DisjointSets(int numElements) : s(numElements, -1)
{
}

/**
 * Union two disjoint sets using union by rank.
 * root1 and root2 are the roots of the sets to be merged.
 */
void DisjointSets::unionSets(int root1, int root2)
{
    if (root1 == root2)
        return; // There already in the same set

    if (s[root1] < s[root2]) // Root1 has a higher rank making it more negative
    {
        s[root2] = root1; 
    }
    else
    {
        if (s[root1] == s[root2]) 
            s[root1]--;          
        s[root2] = root1;         // Makes root1 the new root
    }
}

/**
 * Perform a find (does not change anything).
 * Return the set containing x.
 */
int DisjointSets::find(int x) const
{
    if (s[x] < 0)
        return x; // x becomes the root of the set
    else
        return find(s[x]); // finds the root
}

/**
 * Perform a find with path compression (the mutator version).
 * Return the set containing x.
 */
int DisjointSets::find(int x)
{
    if (s[x] < 0)
        return x; 
    else
        return s[x] = find(s[x]); // Path compression --> makes x point directly to the root
}
