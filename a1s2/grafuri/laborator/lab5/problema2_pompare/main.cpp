#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
#include <limits.h>
using namespace std;

int V, E;

void initialize_preflow(int** capacity, int** flow, int* height, int* excess, int source) {
    height[source] = V;
    for (int v = 0; v < V; ++v) {
        flow[source][v] = capacity[source][v];
        flow[v][source] = -capacity[source][v];
        excess[v] = capacity[source][v];
        excess[source] -= capacity[source][v];
    }
}

void push(int** capacity, int** flow, int* excess, int* height, int u, int v) {
    int send = min(excess[u], capacity[u][v] - flow[u][v]);
    flow[u][v] += send;
    flow[v][u] -= send;
    excess[u] -= send;
    excess[v] += send;
}

void relabel(int** capacity, int** flow, int* height, int u) {
    int minHeight = INT_MAX;
    for (int v = 0; v < V; ++v) {
        if (capacity[u][v] - flow[u][v] > 0) {
            minHeight = min(minHeight, height[v]);
        }
    }
    if (minHeight < INT_MAX) {
        height[u] = minHeight + 1;
    }
}

void discharge(int** capacity, int** flow, int* excess, int* height, int* seen, int u) {
    while (excess[u] > 0) {
        if (seen[u] < V) {
            int v = seen[u];
            if (capacity[u][v] - flow[u][v] > 0 && height[u] > height[v]) {
                push(capacity, flow, excess, height, u, v);
            } else {
                ++seen[u];
            }
        } else {
            relabel(capacity, flow, height, u);
            seen[u] = 0;
        }
    }
}

int push_relabel(int** capacity, int source, int sink) {
    int** flow = new int*[V];
    for (int i = 0; i < V; ++i) {
        flow[i] = new int[V]();
    }
    int* height = new int[V]();
    int* excess = new int[V]();
    int* seen = new int[V]();
    initialize_preflow(capacity, flow, height, excess, source);
    queue<int> active;
    for (int i = 0; i < V; ++i) {
        if (i != source && i != sink && excess[i] > 0) {
            active.push(i);
        }
    }
    while (!active.empty()) {
        int u = active.front();
        active.pop();
        discharge(capacity, flow, excess, height, seen, u);
        if (excess[u] > 0) {
            active.push(u);
        }
    }
    int max_flow = 0;
    for (int i = 0; i < V; ++i) {
        max_flow += flow[source][i];
    }
    for (int i = 0; i < V; ++i) {
        delete[] flow[i];
    }
    delete[] flow;
    delete[] height;
    delete[] excess;
    delete[] seen;

    return max_flow;
}

int main(int argc, char** argv) {
    int a, b, c;
    if (argc < 3) {
        cerr << "Usage: ./p1 in out\n";
        exit(1);
    }
    ifstream fin(argv[1]);
    fin >> V >> E;
    int** capacity = new int*[V];
    for (int i = 0; i < V; ++i) {
        capacity[i] = new int[V]();
    }
    for (int i = 0; i < E; ++i) {
        fin >> a >> b >> c;
        capacity[a][b] = c;
    }
    int max_flow = push_relabel(capacity, 0, 4);
    ofstream fout(argv[2]);
    fout << max_flow << endl;
    cout << max_flow << endl;
    for (int i = 0; i < V; ++i) {
        delete[] capacity[i];
    }
    delete[] capacity;

    return 0;
}
