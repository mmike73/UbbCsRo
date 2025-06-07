#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
#include <stack>

using namespace std;

ifstream f("in.txt");
ofstream g("out.txt");

int n;

bool DFS(vector<vector<int>>graf, vector<int>& parinte){
	stack<int> st;
	vector<bool> vizitat(n);

	for (int i = 0; i < n; i++)
		vizitat[i] = 0;

	st.push(0);
	parinte[0] = -1;
	vizitat[0] = 1;

	while (!st.empty()) {
		int nod = st.top();
		st.pop();
		for (int i = 0; i < graf[nod].size(); i++) {
			if (graf[nod][i] != 0 && !vizitat[i]) {
				parinte[i] = nod;
				if (i == n - 1)
					return true;
				vizitat[i] = 1;
				st.push(i);
			}
		}
	}
	return false;
}

int FordFulkerson(vector<vector<int>> graf, int s, int d) {

	vector<int> parinte;//parintii fiecarui nod
	parinte.resize(graf.size());
	int flux_maxim = 0;
    //parinte este drumul de la s la t, determinat de dfs
	while (DFS(graf, parinte)) {
		int flux_curent = INT_MAX;
        //determina fluxul minim al unui drum de la s la t
		for (int u = d; u != s; u = parinte[u]) {
			int v = parinte[u];
			flux_curent = min(flux_curent, graf[v][u]);
		}
        //actualizeaza graful rezidual
		for (int u = d; u != s; u = parinte[u]) {
			int v = parinte[u];
			graf[v][u] = graf[v][u] - flux_curent;
			graf[u][v] = graf[u][v] + flux_curent;
		}

		//fluxul maxim va fi suma fluxurilor de pe fiecare drum
		flux_maxim = flux_maxim + flux_curent;
	}
	return flux_maxim;
}

int main() {
	int m, x, y, z;
	vector<vector<int>> graf;
	f >> n >> m;
	for (int i = 0; i < n; i++)
	{
		vector<int> linie(n);
		graf.push_back(linie);
	}
	for (int i = 0; i < m; i++)
	{
		f >> x >> y >> z;
		graf[x][y] = z;
	}
	g << FordFulkerson(graf, 0, n - 1);
}