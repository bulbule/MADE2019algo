#include <iostream>
#include <vector>
#include <queue>

/* 11_1. Цикл минимальной длины
Дан невзвешенный неориентированный граф. Найдите цикл минимальной длины.
Ввод: v: кол-во вершин (макс. 50000), n: кол-во ребер (макс. 200000), 
n пар реберных вершин.
Вывод: одно целое число равное длине минимального цикла. 
Если цикла нет, то вывести -1.
*/

class Graph {
    public:
     explicit Graph(int num_nodes): size(num_nodes), \
                                    adj_list(num_nodes) {}
     void add_edge(int, int);
     int get_min_loop();
    private:
     size_t size;
     std::vector<std::vector<int>> adj_list;
     struct Node {
         bool visited = false;
         int parent = -1;
         int depth = 0;
     };
     int BFS(int); 
};

void Graph::add_edge(int v1, int v2) {
    adj_list[v1].push_back(v2);
    adj_list[v2].push_back(v1);
}

int Graph::BFS(int inode) {
    std::vector<Node> nodes(size);
    std::queue<int> inodes_queue;
    nodes[inode].visited = true;
    inodes_queue.push(inode);
    while (!inodes_queue.empty()) {
        int current_inode = inodes_queue.front();
        inodes_queue.pop();
        for (int ineighbor: adj_list[current_inode]) {
            if (!nodes[ineighbor].visited) {
                inodes_queue.push(ineighbor);
                nodes[ineighbor].visited = true;
                nodes[ineighbor].parent = current_inode;
                nodes[ineighbor].depth = nodes[current_inode].depth + 1;
            } else if (nodes[current_inode].parent != ineighbor) {
                return nodes[ineighbor].depth + \
                       nodes[current_inode].depth + 1;
            }    
        }
    }
    return size + 1;
}

int Graph::get_min_loop() {
    int min_loop = size + 1;
    for (int inode = 0; inode < size; ++inode) {
        int new_loop = BFS(inode);
        if (new_loop < min_loop) min_loop = new_loop;
    }
    return min_loop;
}

int main() {
    size_t v = 0;
    size_t n = 0;
    std::cin >> v >> n;
    Graph graph(v);

    for (int i = 0; i < n; ++i) {
        int v1, v2;
        std::cin >> v1 >> v2;
        graph.add_edge(v1, v2);
    }
    int min_loop = graph.get_min_loop();
    std::cout << (min_loop == v + 1 ? -1 : min_loop) << std::endl;
}
