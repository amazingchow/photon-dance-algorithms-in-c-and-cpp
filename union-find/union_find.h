#ifndef __UNION_FIND__H__
#define __UNION_FIND__H__

typedef struct DisjointSets
{
    int* sets;
    int* size_lookup;
    int N;
} DisjointSets;

int root(DisjointSets* disjoint_sets, int i, int path_compression);
int find(DisjointSets* disjoint_sets, int p, int q, int path_compression);
void unite(DisjointSets* disjoint_sets, int p, int q);

#endif /* __UNION_FIND__H__ */
