#ifndef tsp_mst_h
#define tsp_mst_h

#include "graph.h"
#include "MST.h"

class TSP_MST {
    public:
     double get_mst_len(const Graph& graph);
    private:
     void preorder_traversal(const Graph& graph, unsigned node);
     std::vector<unsigned> loop;
     std::vector<bool> visited;
     unsigned size;  
};

#endif