#ifndef tsp_exact_h
#define tsp_exact_h
#include <algorithm>
#include "graph.h"

class TSP_EXACT {
    public:
     double get_exact_len(const Graph& graph);
    private:
     Graph const* graph_;
     unsigned size;
     std::vector<unsigned> loop;
     double min_loop;
     double get_loop_len();
};

#endif