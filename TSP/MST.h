#ifndef mst_h
#define mst_h

#include "graph.h"
#include <algorithm>

void make_set(unsigned node, std::vector<unsigned> &parent, \
                    std::vector<unsigned> &tree_size);
unsigned find_set(unsigned node, std::vector<unsigned> &parent);
void unite_sets(unsigned node1, unsigned node2,  \
                std::vector<unsigned> &parent,  \
                std::vector<unsigned> &tree_size);  // merge two sets  
// construct minimum spanning tree using Kruskal's algo
void MST(const Graph& graph, Graph& mst_tree);

#endif