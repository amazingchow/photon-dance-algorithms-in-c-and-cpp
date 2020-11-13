#ifndef __UNION_FIND__H__
#define __UNION_FIND__H__

#include <map>
#include <string>

class UnionFind final {

public:
    /* 构造函数 */
    explicit UnionFind();
    /* 析构函数 */
    ~UnionFind();

private:
    /* 拷贝构造 */
    UnionFind(const UnionFind &) = delete;
    UnionFind(UnionFind &&) = delete;
    /* 赋值拷贝 */
    UnionFind& operator=(const UnionFind &) = delete;
    UnionFind& operator=(UnionFind &&) = delete;

public:
    void add(std::string elem);
    std::string root(std::string node, bool use_path_compression);
    bool find(std::string node_x, std::string node_y);
    void unite(std::string node_x, std::string node_y, bool use_path_compression);

private:
    std::map<std::string, std::string> elements; // node -> root
    std::map<std::string, uint64_t> lookup_leaves; // node -> count of leaves
};

#endif /* __UNION_FIND__H__ */
