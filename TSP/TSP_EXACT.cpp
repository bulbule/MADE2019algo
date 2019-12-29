#include "TSP_EXACT.h"

double TSP_EXACT::get_loop_len() {
    double len = 0;
    for (unsigned ind = 0; ind < size; ++ind) {
        if (ind == size - 1) {
            len += graph_->get_weight(loop[ind], loop[0]);
            return len;
        }
        len += graph_->get_weight(loop[ind], loop[ind + 1]);
    }
}

double TSP_EXACT::get_exact_len(const Graph& graph) {
    graph_ = &graph;
    size = graph_->get_size();
    for (unsigned node = 0; node < size; ++node) {
        loop.push_back(node);
    }
    min_loop = get_loop_len();
    std::sort(loop.begin(), loop.end());
    while (std::next_permutation(loop.begin(), loop.end())) {
        double clen = get_loop_len();
        if (clen < min_loop) {
            min_loop = clen;
        }
    }
    return min_loop;
}