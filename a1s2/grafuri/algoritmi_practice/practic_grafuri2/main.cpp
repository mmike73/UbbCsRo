#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <queue>
#include <map>

using namespace std;

int n;
char sir_enc[1000];
string sir_dec;
map<char, int> fr;
map<char, string> coduri;

struct graf {
    graf* stanga = nullptr;
    graf* dreapta = nullptr;
    int frecventa = 0;
    char caracter = '\0';
};

struct cmp {
    bool operator()(graf* x, graf* y) {
        if (x->frecventa == y->frecventa)
            return x->caracter > y->caracter;
        return x->frecventa > y->frecventa;
    }
};

priority_queue<graf*, vector<graf*>, cmp> Q;

graf* Huffman_encode() {
    int n = (int)fr.size();
    auto it = fr.begin();
    while (it != fr.end()) {
        graf *nod = new graf;
        nod->frecventa = it->second;
        nod->caracter = it->first;
        Q.push(nod);
        ++it;
    }
    for (int i = 0; i < n - 1; i++) {
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

graf* Hulfman_decode() {
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

void cod_caracter(graf* h, char caracter, string cod="") {
    if (h->stanga == nullptr && h->dreapta == nullptr && fr[caracter] == h->frecventa && caracter == h->caracter) {
        coduri[caracter] = cod;
        return;
    }
    if (h->stanga != nullptr)
        cod_caracter(h->stanga, caracter, cod + "0");
    if (h->dreapta != nullptr)
        cod_caracter(h->dreapta, caracter, cod + "1");
}

int main() {
    int choice;

    cout << "Codare 1 / Decodare -1 >>> ";
    cin >> choice;
    if(choice == -1) {
        ifstream f("../codat.txt");
        ofstream f2("../clar.txt");
        f >> n;
        char c;
        int frecventa;
        for (int i = 0; i < n; ++i) {
            f >> c >> frecventa;
            fr[c] = frecventa;
        }
        f >> sir_dec;
        graf *h = Hulfman_decode();
        for (int i = 0; i < sir_dec.size(); i++) {
            graf *p = h;
            while (p->caracter == '\0') {
                if (sir_dec[i] == '0')
                    p = p->stanga;
                else
                    p = p->dreapta;
                i++;
            }
            i--;
            f2 << p->caracter;
            cout << p->caracter;
        }
        cout << '\n';
        f.close();
        f2.close();
    } else if(choice == 1) {
        ifstream f("../clar.txt");
        ofstream f2("../codat.txt");
        f.getline(sir_enc, 10005);
        for (int i = 0; i < strlen(sir_enc); i++)
            fr[sir_enc[i]]++;

        graf* h = Huffman_encode();

        auto it = fr.begin();
        f2 << fr.size() << '\n';
        while (it != fr.end()) {
            cod_caracter(h, it->first);
            f2 << it->first << " " << it->second << endl;
            ++it;
        }

        for (int i = 0; i < strlen(sir_enc); i++) {
            f2 << coduri[sir_enc[i]];
            cout << coduri[sir_enc[i]];
        }
        cout << '\n';

        f.close();
        f2.close();
    }
    return 0;
}
