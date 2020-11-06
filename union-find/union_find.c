#include "union_find.h"

int root(DisjointSets* disjoint_sets, int i, int path_compression)
{
    while (i != disjoint_sets->sets[i])
    {
        if (path_compression)
        {
            // not standard implementation
            // make every other node in path point to its grandparent
            disjoint_sets->sets[i] = disjoint_sets->sets[disjoint_sets->sets[i]];
        }
        i = disjoint_sets->sets[i];
    }
    return i;
}

int find(DisjointSets* disjoint_sets, int p, int q, int path_compression)
{
    return root(disjoint_sets, p, path_compression) == root(disjoint_sets, q, path_compression);
}

void unite(DisjointSets* disjoint_sets, int p, int q)
{
    int i = root(disjoint_sets, p, 0);
    int j = root(disjoint_sets, q, 0);

    // weighted-quick-union
    // merge smaller tree into larger one && update the size_lookup array
    if (disjoint_sets->size_lookup[i] > disjoint_sets->size_lookup[j])
    {
        disjoint_sets->sets[j] = i;
        disjoint_sets->size_lookup[i] += disjoint_sets->size_lookup[j];
    }
    else
    {
        disjoint_sets->sets[i] = j;
        disjoint_sets->size_lookup[j] += disjoint_sets->size_lookup[i];
    }
}
