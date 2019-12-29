#include "TSP_MST.h"
#include <stack>

void TSP_MST::preorder_traversal(const Graph& mst, unsigned node) {
    std::stack<unsigned> st;
    st.push(node);
    while (!st.empty()) {
        unsigned cnode = st.top();
        st.pop();
        if (!visited[cnode]) {
            loop.push_back(cnode);
            visited[cnode] = true;
            std::vector<std::pair<unsigned, double> > neighbors = \
                                         mst.get_neighbors(cnode);
            for (auto neighbor: neighbors) {
                st.push(neighbor.first);
             }
        }
    }
}

double TSP_MST::get_mst_len(const Graph& graph) {
    size_t size = graph.get_size();
    Graph mst(size);
    MST(graph, mst);
    visited.assign(size, false);
    preorder_traversal(mst, 0);
    double len = 0;
    for (unsigned ind = 0; ind < loop.size(); ++ind) {
        unsigned node1 = loop[ind];
        if (ind == loop.size() - 1) {
            len += graph.get_weight(node1, loop[0]);
            return len;
        }
        unsigned node2 = loop[ind + 1];
        len += graph.get_weight(node1, node2);
    }
}


