#ifndef dots_h
#define dots_h

#include <vector>
#include <cstdlib>
#include <cmath>
#include "graph.h"

struct dot {
    dot(double x_, double y_): x(x_), y(y_) {}
    int x = 0;
    int y = 0;
};

void generate_graph(unsigned seed, Graph& graph);
   /* Generate a sample of normally distributed points forming a full
      graph using the Box-Mueller transformation*/

#endif