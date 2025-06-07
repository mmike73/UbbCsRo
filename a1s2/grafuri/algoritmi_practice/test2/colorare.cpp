#include <iostream>

class Edge {
public:
    int a, b;
    Edge* next;
};

class Node {
public:
    int color;
    Edge* neighbors;
};

bool fits(int& n_node, Node* V, int col) {
    Edge* e;
    for(e = V[col].neighbors; e; e=e->next)
        if(V[e->b].color == col) return 0;
    return 1;
}

bool coloreaza(int& n_nodes, Node* V, int& n_col, int crt_node) {
    if(crt_node == n_nodes) {
        //print
        std::cout << "oh yeah\n";
    }
    int color;
    for(color = 0; color < n_col; ++color) {
        if(fits(n_nodes,V,color)) {
            V[crt_node].color = color;
            if(coloreaza(n_nodes, V, n_col,crt_node + 1)) return 1;
        }
    }
    V[crt_node].color = 0;
    return 0;
}

int main() {
    int n_col, n_nodes, a, b;
    Node* V;
    std::cin >> n_nodes >> n_col;
    V = new Node[n_nodes];

    while(std::cin >> a >> b) {
        Edge* e = new Edge;
        e->a = a;
        e->b = b;
        e->next = V[b].neighbors;
        V[a].neighbors = e;
    }
    if(!coloreaza(n_nodes,V,n_col, 0)) {
        std::cout << "Coloring impossible!\n";
    }
    return 0;
}