#include "union_find.h"

UnionFind::UnionFind()
{
}

UnionFind::~UnionFind()
{
}

void UnionFind::add(std::string elem)
{
    this->elements[elem] = elem;
    this->lookup_leaves[elem] = 0;
}

std::string UnionFind::root(std::string node, bool use_path_compression)
{
    std::string n = node;

    while (node != this->elements[node])
    {
        node = this->elements[node];
    }

    // now node is the root

    std::string tmp;
    if (use_path_compression) {
        while (node != this->elements[n]) {
            tmp = this->elements[n];
            this->elements[n] = node;
            n = tmp;
        }
    }

    return node;
}

bool UnionFind::find(std::string node_x, std::string node_y)
{
    return this->root(node_x, false) == this->root(node_y, false);
}

void UnionFind::unite(std::string node_x, std::string node_y, bool use_path_compression)
{
    std::string root_x = this->root(node_x, use_path_compression);
    std::string root_y = this->root(node_y, use_path_compression);

    // weighted-quick-union
    // merge smaller tree into larger one && update the lookup_leaves map
    if (this->lookup_leaves[root_x] > this->lookup_leaves[root_y])
    {
        this->elements[root_y] = root_x;
        this->lookup_leaves[root_x] += this->lookup_leaves[root_y];
    }
    else
    {
        this->elements[root_x] = root_y;
        this->lookup_leaves[root_y] += this->lookup_leaves[root_x];
    }
}
