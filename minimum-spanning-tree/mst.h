#ifndef __MINIMUM_SPANNING_TREE__H__
#define __MINIMUM_SPANNING_TREE__H__

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "union_find.h"

class Graph final {
  public:
    /* 构造函数 */
    explicit Graph();
    /* 析构函数 */
    ~Graph();

  private:
    /* 拷贝构造 */
    Graph(const Graph &) = delete;
    Graph(Graph &&) = delete;
    /* 赋值拷贝 */
    Graph &operator=(const Graph &) = delete;
    Graph &operator=(Graph &&) = delete;

  public:
    void add_edge(std::string u, std::string v, int w);
    int apply_kruskal_mst();
    void print_kruskal_mst();

  private:
    std::vector<std::pair<int, std::pair<std::string, std::string>>> edges;
    std::vector<std::pair<std::string, std::string>> mst_edges;
    UnionFind uf;
};

#endif /* __MINIMUM_SPANNING_TREE__H__ */
