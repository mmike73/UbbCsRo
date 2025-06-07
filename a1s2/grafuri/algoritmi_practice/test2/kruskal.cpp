#include <iostream>
#include <fstream>
#include <queue>
#include <map>
#include <set>

using namespace std;

int n, m;
int a[5005][5005];

ifstream f;
ofstream f2;

struct muchii{
    int x, y, c;
};

struct compara{
    bool operator()(const muchii& m1, const muchii& m2) const {
        return m1.c <= m2.c;
    }
};

set<muchii, compara> M;

void DFS(int nod, int v[]){
    v[nod] = 1;
    for (int i = 0; i < n; i ++)
        if (!v[i] && a[nod][i])
            DFS(i, v);
}

void kruskal(){
    int cnt = 0, sumac = 0;
    auto it = M.begin();
    while (it != M.end()){
        cnt ++;
        sumac += it->c;
        int verificare = 0;
        int v1[n + 1], v2[n + 1];
        for (int i = 0; i < n; i ++)
            v1[i] = 0;
        int x = M.begin()->x;
        DFS(x, v1);

        for (int i = 0; i < n; i ++)
            v2[i] = 0;
        x = it->x;
        int y = it->y;
        a[x][y] = a[y][x] = 1;
        x = it->x;
        DFS(x, v2);
        for (int i = 0; i < n; i ++)
            if (v1[i] != v2[i])
                verificare = 1;
        if (!verificare) {
            a[x][y] = a[y][x] = 0;
            cnt--;
            sumac -= it->c;
        }
        it++;
    }
    f2 << sumac << "\n" << cnt << "\n";
    for (int i = 0; i < n; i ++) {
        for (int j = i + 1; j < n; j++)
            if (a[i][j])
                f2 << i << " " << j << "\n";
    }
}

int main(int argc, char * argv[]) {
    if (argc!=3){
        std::cerr << "Usage: ./p1 in out";
        exit(1);
    }
    f.open(argv[1]);
    f2.open(argv[2]);
    f >> n >> m;
    int x, y, c;
    while (f >> x >> y >> c) {
        muchii muchie{x, y, c};
        M.insert(muchie);
    }
    kruskal();
    f.close();
    f2.close();
    return 0;
}