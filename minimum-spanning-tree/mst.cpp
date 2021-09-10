#include "mst.h"

Graph::Graph() {}

Graph::~Graph() {}

void
Graph::add_edge(std::string u, std::string v, int w) {
    this->edges.push_back({w, {u, v}});
    this->uf.add(u);
    this->uf.add(v);
}

int
Graph::apply_kruskal_mst() {
    int mst_wt = 0;

    std::sort(this->edges.begin(), this->edges.end());

    std::vector<std::pair<int, std::pair<std::string, std::string>>>::iterator iter;
    for (iter = this->edges.begin(); iter != this->edges.end(); iter++) {
        std::string u = iter->second.first;
        std::string v = iter->second.second;

        std::string u_root = this->uf.root(u, false);
        std::string v_root = this->uf.root(v, false);

        // Check if the selected edge is creating a cycle or not
        // (Cycle is created if u and v both belong to the same set)
        if (u_root != v_root) {
            this->mst_edges.push_back({u, v});

            mst_wt += iter->first;
            this->uf.unite(u_root, v_root, true);
        }
    }

    return mst_wt;
}

void
Graph::print_kruskal_mst() {
    std::cout << "Edges of MST are \n\n";

    std::vector<std::pair<std::string, std::string>>::iterator iter;
    for (iter = this->mst_edges.begin(); iter != this->mst_edges.end(); iter++) {
        std::string u = iter->first;
        std::string v = iter->second;
        std::cout << "\t" << u << " - " << v << std::endl;
    }
}
