#include <iostream>
#include "union_find.h"

int
main(int argc, char const *argv[]) {
    UnionFind *uf = new (UnionFind);

    uf->add(std::string("doc_0001"));
    uf->add(std::string("doc_0002"));
    uf->add(std::string("doc_0003"));
    uf->add(std::string("doc_0004"));
    uf->add(std::string("doc_0005"));
    uf->add(std::string("doc_0006"));
    uf->add(std::string("doc_0007"));
    uf->add(std::string("doc_0008"));
    uf->add(std::string("doc_0009"));
    uf->add(std::string("doc_0010"));
    uf->add(std::string("doc_0011"));
    uf->add(std::string("doc_0012"));

    uf->unite(std::string("doc_0001"), std::string("doc_0008"), true);
    uf->unite(std::string("doc_0004"), std::string("doc_0008"), true);
    uf->unite(std::string("doc_0007"), std::string("doc_0008"), true);
    uf->unite(std::string("doc_0003"), std::string("doc_0011"), true);
    uf->unite(std::string("doc_0005"), std::string("doc_0011"), true);
    uf->unite(std::string("doc_0006"), std::string("doc_0011"), true);
    uf->unite(std::string("doc_0009"), std::string("doc_0002"), true);
    uf->unite(std::string("doc_0010"), std::string("doc_0002"), true);
    uf->unite(std::string("doc_0012"), std::string("doc_0002"), true);

    std::cout << "doc_0009 and doc_0004 are not inside the same union, actually is "
              << (uf->find(std::string("doc_0009"), std::string("doc_0004")) ? "false" : "true") << std::endl;

    std::cout << "doc_0005 and doc_0003 are inside the same union, actually is "
              << (uf->find(std::string("doc_0005"), std::string("doc_0003")) ? "true" : "false") << std::endl;

    delete uf;
}
