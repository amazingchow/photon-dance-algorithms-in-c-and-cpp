#include <iostream>
#include "mst.h"

int
main(int argc, char const *argv[]) {
    Graph *g = new (Graph);

    g->add_edge(std::string("v_0000"), std::string("v_0001"), 4);
    g->add_edge(std::string("v_0000"), std::string("v_0007"), 8);
    g->add_edge(std::string("v_0001"), std::string("v_0002"), 8);
    g->add_edge(std::string("v_0001"), std::string("v_0007"), 11);
    g->add_edge(std::string("v_0002"), std::string("v_0003"), 7);
    g->add_edge(std::string("v_0002"), std::string("v_0008"), 2);
    g->add_edge(std::string("v_0002"), std::string("v_0005"), 4);
    g->add_edge(std::string("v_0003"), std::string("v_0004"), 9);
    g->add_edge(std::string("v_0003"), std::string("v_0005"), 14);
    g->add_edge(std::string("v_0004"), std::string("v_0005"), 10);
    g->add_edge(std::string("v_0005"), std::string("v_0006"), 2);
    g->add_edge(std::string("v_0006"), std::string("v_0007"), 1);
    g->add_edge(std::string("v_0006"), std::string("v_0008"), 6);
    g->add_edge(std::string("v_0007"), std::string("v_0008"), 7);

    int mst_wt = g->apply_kruskal_mst();
    g->print_kruskal_mst();
    std::cout << "\nWeight of MST is " << mst_wt << std::endl;

    delete g;
}
