#include "graph.h"

Graph::Graph(size_t number_nodes): size(number_nodes),  \
                                   mat(std::vector<std::vector<double> >(
                                       size, std::vector<double>(size, 0.0))) {}

void Graph::add_edge(unsigned node1, unsigned node2, double weight) {
    mat[node1][node2] = weight;
    mat[node2][node1] = weight;
}

size_t Graph::get_size() const {
    return size;
}

double Graph::get_weight(unsigned node1, unsigned node2) const {
    return mat[node1][node2];
}

std::vector<std::pair<unsigned, double> > Graph::get_neighbors(unsigned node) const{
    std::vector<std::pair<unsigned, double> > neighbors;
    for (unsigned node2 = 0; node2 < size; ++node2) {
        if (node2 != node) {
            neighbors.push_back(std::make_pair(node2, mat[node][node2]));
        }
    }
    return neighbors;
}

void Graph::print() {
    for (unsigned node1 = 0; node1 < size; ++node1) {
        for (unsigned node2 = node1; node2 < size; ++node2) {
            if (mat[node1][node2] != 0) {
                std::cout << "weight" << mat[node1][node2] << ", nodes: " \
                << node1 << " " << node2 << std::endl;
            }
        }
    }
}


