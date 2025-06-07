// A C++ program print Eulerian Trail in a given Eulerian or
// Semi-Eulerian Graph
#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <string.h>
#include "graph.cpp"
using namespace std;
vector<char> rez;

void Graph::printEulerTour()
{
    int u = 0;
    for (int i = 0; i < V; i++)
        if (adj[i].size() & 1) {
            u = i;
            break;
        }
    printEulerUtil(u);
}

void Graph::printEulerUtil(int u)
{
    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i) {
        int v = *i;
        if (v != -1 && isValidNextEdge(u, v)) {
            cout << v << " ";

            rmvEdge(u, v);
            printEulerUtil(v);
        }
    }
}

bool Graph::isValidNextEdge(int u, int v) {
    int count = 0;
    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i)
        if (*i != -1)
            count++;
    if (count == 1)
        return true;
    bool visited[V];
    memset(visited, false, V);
    int count1 = DFSCount(u, visited);
    rmvEdge(u, v);
    memset(visited, false, V);
    int count2 = DFSCount(u, visited);
    addEdge(u, v);
    return (count1 > count2) ? false : true;
}

void Graph::rmvEdge(int u, int v) {
    list<int>::iterator iv
            = find(adj[u].begin(), adj[u].end(), v);
    *iv = -1;
    list<int>::iterator iu
            = find(adj[v].begin(), adj[v].end(), u);
    *iu = -1;
}

int Graph::DFSCount(int v, bool visited[]) {
    visited[v] = true;
    int count = 1;
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (*i != -1 && !visited[*i])
            count += DFSCount(*i, visited);
    return count;
}

int main(int argc, char** argv) {
    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);
    int V,E;
    fin >> V >> E;
    Graph g(V);

    int a = 0,b = 0;
    for( int i = 0; i < E; ++i) {
        fin >> a >> b;
        g.addEdge(a,b);
    }
    g.printEulerTour();


    return 0;
}
