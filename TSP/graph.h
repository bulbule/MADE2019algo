#ifndef graph_h
#define graph_h
#include <vector>
#include <iostream>

class Graph {
    public:
     explicit Graph(size_t nodes_number);
     void add_edge(unsigned node1, unsigned node2, double weight);
     size_t get_size() const;
     double get_weight(unsigned node1, unsigned node2) const;
     std::vector<std::pair<unsigned, double> > get_neighbors(unsigned node) const;
     void print();
    private:
     size_t size = 0;
     std::vector<std::vector<double> > mat; 
};

#endif