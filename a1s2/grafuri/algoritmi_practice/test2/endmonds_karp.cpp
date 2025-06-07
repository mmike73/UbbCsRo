// C++ program for implementation of Ford Fulkerson algorithm
#include <iostream>
#include <fstream>
#include <limits.h>
#include <string.h>
#include <queue>
using namespace std;

int V,E;

bool bfs(int** rGraph, int s, int t, int parent[])
{
    bool visited[V];
    memset(visited, 0, sizeof(visited));

    queue <int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v=0; v<V; v++)
        {
            if (visited[v]==false && rGraph[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return (visited[t] == true);
}

int edmond_karp(int** graph, int s, int t)
{
    int u, v;

    //initializarea grafului rezidual
    int** rGraph;
    rGraph = new int*[V];//graf rezidual
    for( int i = 0; i < V; ++i) {
        rGraph[i] = new int[V];
    }
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
            rGraph[u][v] = graph[u][v];

    int parent[V];

    int max_flow = 0;
    //parinte este drumul de la s la t determinat de bfs
    while (bfs(rGraph, s, t, parent))
    {
        int path_flow = INT_MAX;
        for (v=t; v!=s; v=parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
        //ne intoarcem din t in s si actualizam graful rezidual
        for (v=t; v != s; v=parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
        max_flow += path_flow;
    }

    for( int i = 0; i < V; ++i) {
        delete [] rGraph[i];
    delete rGraph;
    return max_flow;
    }
}

int main(int argc, char** argv) {
    int a,b,c;
    int** graph;
    if(argc < 3) {
        std::cerr << "Usage: ./p1 in out\n";
        exit(1);
    }
    ifstream fin(argv[1]);


    fin >> V >> E;

    graph = new int*[V];
    for( int i = 0; i < V; ++i) {
        graph[i] = new int[V];
    }

    for(int i = 0; i < E; ++i) {
        fin >> a >> b >> c;
        graph[a][b] = c;
    }


    int max_flow = 0;
    for(int i = 0; i < V; ++i)
        for(int j = 0; j < V; ++j) {
            if( i != j) {
                int e = edmond_karp(graph, i, j);
                if( e > max_flow) {
                    max_flow = e;
                }
            }
        }

    ofstream fout(argv[2]);
    cout << max_flow;

    for( int i = 0; i < V; ++i) {
        delete [] graph[i];
    }
    delete graph;

    return 0;
}
