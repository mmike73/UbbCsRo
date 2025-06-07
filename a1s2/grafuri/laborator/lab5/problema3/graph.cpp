//
// Created by Mihai Moldovan on 23.05.2024.
//
// A class that represents an undirected graph
#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <string.h>
using namespace std;


class Graph {
    int V;
    list<int>* adj;
public:
    Graph(int V)
    {
        this->V = V;
        adj = new list<int>[V];
    }
    ~Graph() { delete[] adj; }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void rmvEdge(int u, int v);
    void printEulerTour();
    void printEulerUtil(int s);
    int DFSCount(int v, bool visited[]);
    bool isValidNextEdge(int u, int v);
};

