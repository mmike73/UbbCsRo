#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int INF = 10000;

struct Muchie {
    int sursa, destinatie;
    int pondere;
};

void BellmanFord(vector<Muchie>& muchii, int n, int sursa, vector<int>& dist) {
    dist.assign(n, INF);
    dist[sursa] = 0;
    for (int i = 0; i < n - 1; ++i) {
        for (const Muchie& muchie : muchii) {
            if (dist[muchie.sursa] != INF && dist[muchie.sursa] + muchie.pondere < dist[muchie.destinatie]) {
                dist[muchie.destinatie] = dist[muchie.sursa] + muchie.pondere;
            }
        }
    }

    for (const Muchie& muchie : muchii) {
        if (dist[muchie.sursa] != INF && dist[muchie.sursa] + muchie.pondere < dist[muchie.destinatie]) {
            dist.assign(n, INF);
            return;
        }
    }
}

int main(int argc, char* argv[]) {
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int n, m, start;
    fin >> n >> m >> start;

    vector<Muchie> muchii(m);
    for (int i = 0; i < m; ++i) {
        fin >> muchii[i].sursa >> muchii[i].destinatie >> muchii[i].pondere;
    }

    vector<int> distances;
    BellmanFord(muchii, n, start, distances);

    for (int distance : distances) {
        if (distance == INF)
            fout << "INF ";
        else
            fout << distance << " ";
    }

    return 0;
}
