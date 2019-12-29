#include "MST.h"

void make_set(unsigned node, std::vector<unsigned> &parent, \
                    std::vector<unsigned> &tree_size) {
    parent[node] = node;  // representative or parent of the node
    tree_size[node] = 1;
}

unsigned find_set(unsigned node, std::vector<unsigned> &parent) {
    if (node == parent[node])
        return node;
    // all the nodes that are on the path to the root (representative)
    // get their parent updated
    return parent[node] = find_set(parent[node], parent); 
}

void unite_sets(unsigned node1, unsigned node2,  \
                std::vector<unsigned> &parent,  \
                std::vector<unsigned> &tree_size) {
    node1 = find_set(node1, parent);
    node2 = find_set(node2, parent);
    if (node1 != node2) {
        // we attach the tree of smaller size
        // to the tree of a larger size
        if (tree_size[node1] < tree_size[node2])
            std::swap(node1, node2);
        parent[node2] = node1;
        tree_size[node1] += tree_size[node2];
    }
}


void MST(const Graph& graph, Graph& mst) {
    size_t size = graph.get_size();
    // int cost = 0;
    std::vector<unsigned> parent(size), tree_size(size);
    for (unsigned node = 0; node < size; ++node)
        make_set(node, parent, tree_size);
    std::vector<std::pair<double,
                std::pair<unsigned, unsigned> > >  weights;
    for (unsigned node1 = 0; node1 < size; ++node1) {
        for (unsigned node2 = node1; node2 < size; ++node2) {
            if (graph.get_weight(node1, node2) != 0) {
                weights.push_back(std::make_pair(
                    graph.get_weight(node1, node2),
                    std::make_pair(node1, node2)
                    )
                );
            }
        }
    }
    std::sort(weights.begin(), weights.end());
    for (auto edge : weights) {
        if (find_set(edge.second.first, parent) !=  \
            find_set(edge.second.second, parent)) {
            // cost += edge.first;
            mst.add_edge(edge.second.first, \
                              edge.second.second,  \
                              edge.first);
            unite_sets(edge.second.first, 
                       edge.second.second,
                       parent,
                       tree_size);
        }
    }
}
