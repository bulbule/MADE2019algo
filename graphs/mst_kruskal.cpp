#include <iostream>
#include <vector>
#include <algorithm>

// Implementing Kruskal with a standard Disjoint Set Union data structure

class Graph {
    public:
     explicit Graph(int size, int num_edges): size(size), \
                                              num_edges(num_edges), \
                                              parent(size), \
                                              tree_size(size) {}
     int Kruskal();
     void add_edge(int, int, int);
    private:
     int size = 0;
     int num_edges = 0;
     std::vector<int> parent, tree_size;
     std::vector<std::pair<int, std::pair<int, int>>> weights;
     void make_set(int);
     int find_set(int);  // return a representative of a set(tree) 
                         // to which a node belongs
     void unite_sets(int, int);  // merge two sets   
};

void Graph::add_edge(int node1, int node2, int weight) {
    weights.push_back(std::make_pair(weight, 
                                     std::make_pair(node1 - 1,
                                                    node2 - 1)));
}

void Graph::make_set(int node) {
    parent[node] = node;  // representative or parent of the node
    tree_size[node] = 1;
}

int Graph::find_set(int node) {
    if (node == parent[node])
        return node;
    // all the nodes that are on the path to the root (representative)
    // get their parent updated
    return parent[node] = find_set(parent[node]); 
}

void Graph::unite_sets(int node1, int node2) {
    node1 = find_set(node1);
    node2 = find_set(node2);
    if (node1 != node2) {
        // we attach the tree of smaller size
        // to the tree of a larger size
        if (tree_size[node1] < tree_size[node2])
            std::swap(node1, node2);
        parent[node2] = node1;
        tree_size[node1] += tree_size[node2];
    }
}

int Graph::Kruskal() {
    int cost = 0;
    for (int node = 0; node < size; ++node)
        make_set(node);
    std::sort(weights.begin(), weights.end());
    for (auto edge : weights) {
        if (find_set(edge.second.first) != find_set(edge.second.second)) {
            cost += edge.first;
            unite_sets(edge.second.first, 
                       edge.second.second);
        }
    }
    return cost;
}

int main() {
    size_t size = 0;
    size_t edges = 0;
    std::cin >> size >> edges;
    Graph graph(size, edges);
    for (int i = 0; i < edges; ++i) {
        int node1, node2, weight;
        std::cin >> node1 >> node2 >> weight;
        graph.add_edge(node1, node2, weight);
    }
    std::cout << graph.Kruskal() << std::endl;
}
