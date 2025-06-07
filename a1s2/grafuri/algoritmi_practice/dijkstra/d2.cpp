#include <fstream>
#include <iostream>
#include <vector>

#include "../nod.h"
#include "../muchie.h"

#define INF 100000

class Graf {
public:
    
    int n, m;

    int** matrice_adiacenta;
    //...

    Nod* noduri;
    Muchie* muchii;

    std::vector<Nod> S;


    Graf() {
        int a, b, p;
        std::ifstream fin("graf.txt");

        fin >> n >> m;

        matrice_adiacenta = new int*[n];
        for(int i = 0; i < n; ++i)
            matrice_adiacenta[i] = new int[n];

        noduri = new Nod[n];
        muchii = new Muchie[m];

        int i = 0;
        while(fin >> a >> b >> p) {
            matrice_adiacenta[a][b] = p; // seteaza muchia de la a la b cu ponderea p
            muchii[i].a = a;
            muchii[i].b = b;
            muchii[i].pond = p;
            i++;
        }

        for(int i = 0; i < n; ++i)
            noduri[i].indice = i;

         

        fin.close();
    }

    ~Graf() {
        for(int i = 0; i < n; ++i)
            delete [] matrice_adiacenta[i];
        delete [] matrice_adiacenta;
        delete [] noduri;
        delete [] muchii;
    }
    //////////

    void initializare_noduri(int start) {
        for(int i = 0; i < n; ++i)
            noduri[i].d = INF, noduri[i].pi = nullptr;
        noduri[start].d = 0;
    }

    void print_matrice_adiacenta() {
        for(int i = 0; i < n; ++i, std::cout << '\n')
            for(int j = 0; j < n; ++j)
                std::cout << matrice_adiacenta[i][j] << ' ';
    }

    void sorteaza_noduri(int st, int dr) {
        for(int i = st; i < dr; ++i)
            for(int j = st + 1; j <= dr; ++j)
                if(noduri[i].d > noduri[j].d)
                    std::swap(noduri[i], noduri[j]);
    }

    Nod& cauta_nod(int indice) {
        for(int i = 0; i < n; ++i)
            if(noduri[i].indice == indice)
                return noduri[i];
    }

    void dijkstra() {
        initializare_noduri(0); // pornim de la nodul 0
        int st = 0, dr = n - 1;
        while(st <= dr) {
            sorteaza_noduri(st, dr);
            Nod& u = noduri[st];
            S.push_back(u);
            for(int i = 0; i < n; ++i) {
                Nod& v = noduri[i];
                if(u.indice != v.indice && u.d != INF && u.d + matrice_adiacenta[u.indice][v.indice] < v.d) {
                    v.d = u.d + matrice_adiacenta[u.indice][v.indice];
                }
            }
            st++; // avansam la urmatorul nod
        }
    }
};


int main() {
    Graf g;
    g.print_matrice_adiacenta();
    return 0;
}



void Graf::dijkstra(int startNode) {
    std::vector<Node> nodes(n + 1, Node(-1));
    nodes[startNode].distance = 0;

    std::priority_queue<Node*, std::vector<Node*>, 
                        std::function<bool(const Node*, const Node*)>> pq(
        [](const Node* a, const Node* b) { return a->distance > b->distance; }
    );
    pq.push(&nodes[startNode]);

    while (!pq.empty()) {
        Node* current = pq.top();
        pq.pop();

        for (const Edge& edge : adjacencyList[current->id]) {
            Node& nextNode = nodes[edge.to];
            int newDistance = current->distance + edge.weight;
            if (newDistance < nextNode.distance) {
                nextNode.distance = newDistance;
                nextNode.parent = current;
                pq.push(&nextNode);
            }
        }
    }
}

void Graf::printShortestPaths(int startNode) {
    for (int i = 1; i <= n; ++i) {
        std::cout << "Distanta minima de la nodul " << startNode << " la nodul " << i << " este: ";
        if (i != startNode && adjacencyList[i].size() > 0 && nodes[i].distance != INF) {
            std::cout << nodes[i].distance << std::endl;
            
            // Afisam ruta corespunzatoare
            std::cout << "Ruta: ";
            Node* current = &nodes[i];
            while (current != nullptr) {
                std::cout << current->id << " ";
                current = current->parent;
            }
            std::cout << std::endl;
        } else {
            std::cout << "nu este accesibila." << std::endl;
        }
    }
}