 #include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <queue>
#include <map>

using namespace std;

char sir[10005];
map<char, int> fr;
map<char, string> coduri;
struct graf{
    graf* stanga = nullptr;
    graf* dreapta = nullptr;
    int frecventa = 0;
    char caracter = NULL;
};

struct compara{
    bool operator()(graf* x, graf* y){
        if (x->frecventa == y->frecventa)
            return x->caracter > y->caracter;
        return x->frecventa > y->frecventa;
    }
};

priority_queue<graf*, vector<graf*>, compara> Q;

graf* Huffman(){
    int n = (int)fr.size();
    auto it = fr.begin();
    while (it != fr.end()) {
        graf *nod = new graf;
        nod->frecventa = it->second;
        nod->caracter = it->first;
        Q.push(nod);
        ++it;
    }
    for (int i = 0; i < n - 1; i ++){
        graf* z = new graf;
        graf* x = z->stanga = Q.top();
        Q.pop();
        graf* y = z->dreapta = Q.top();
        Q.pop();
        z->frecventa = x->frecventa + y->frecventa;
        Q.push(z);
    }

    graf* min = Q.top();
    Q.pop();
    return min;
}

void cod_caracter(graf* h, char caracter, string cod=""){
    if (h->stanga == nullptr && h->dreapta == nullptr && fr[caracter] == h->frecventa && caracter == h->caracter) {
        coduri[caracter] = cod;
        return;
    }
    if (h->stanga != nullptr)
        cod_caracter(h->stanga, caracter, cod + "0");
    if (h->dreapta != nullptr)
        cod_caracter(h->dreapta, caracter, cod + "1");
}

int main(int argc, char * argv[]) {
    if (argc!=3){
        std::cerr << "Usage: ./p1 in out";
        exit(1);
    }
    
    ifstream f(argv[1]);
    ofstream f2(argv[2]);

    f.getline(sir, 10005);
    for (int i = 0; i < strlen(sir); i ++)
        fr[sir[i]]++;

    graf* h = Huffman();

    auto it = fr.begin();
    while (it != fr.end()) {
        cod_caracter(h, it->first);
        f2 << it->first << ": " << it->second << endl;
        ++it;
    }

    for (int i = 0; i < strlen(sir); i ++)
        f2 << coduri[sir[i]];
    
    f.close();
    f2.close();
}
