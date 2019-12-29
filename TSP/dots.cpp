#include "dots.h"

void generate_graph(unsigned seed, Graph& graph) {
    unsigned size = graph.get_size();
    std::vector<dot> dots;
    double x, y, s;
    std::srand(seed);
    unsigned counter = 0;
    int base = 100000;
    for (unsigned i = 0; i < size; ++i) {
        x = (base - 2 * (std::rand() % base)) / double(base);
        y = (base - 2 * (std::rand() % base)) / double(base);
        s = x * x + y * y;
        if (s <= 1 && s != 0) {
            x = x * std::sqrt(-2 * std::log(s) / s);
            y = y * std::sqrt(-2 * std::log(s) / s);
        }
        dots.push_back(dot(x, y));
        for (unsigned j = 0; j < i; ++j) {
            graph.add_edge(i, j, std::sqrt(std::pow(x - dots[j].x, 2.) +  \
                                           std::pow(y - dots[j].y, 2.)));
        }
    }
}