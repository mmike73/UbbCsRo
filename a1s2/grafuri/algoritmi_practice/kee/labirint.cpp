#include <bits/stdc++.h>
using namespace std;

typedef struct Punct {
    int x, y;
} Punct;

int di[] = {0,-1,0,1}, dj[] = {1,0,-1,0};

ifstream fin("labirint_1.txt");
ofstream fout("rezultat_labirint.txt");

/**
 * @brief parcurge labirintul in toate variantele sale si insemneaza distanta de la 
 *        punctul de inceput
 * 
 * @param start Punct punctul de unce incepe parcurgerea
 * @param labrint int labirintul sub forma de matrice de numere intregi
 * @param nrlinii int nuamrul de linii
 * @param nrcol int numarul de coloane
 * @param queue int* coada
 * @return int - ordinea de parcurgere
 */
int Lee(Punct start, int labrint[][101], int nrlinii, int nrcol, Punct queue[]) {
    Punct crt;
    //este un algortm care se bazeaza pe parcurgerea in latime
    int st = 1, dr = 0;
    queue[++dr] = start;
    labrint[start.x][start.y] = 1;
    //pune in coada punctul de start
    while( st <= dr) {
        crt = queue[st]; 
        
        for( int k = 0; k < 4; ++k) {
            int i = crt.x + di[k], j = crt.y + dj[k];
            if( i >= 0 && i < nrlinii && j >= 0 && j < nrcol && labrint[i][j] == 0) {

                labrint[i][j] = labrint[crt.x][crt.y] + 1;
                Punct vecin;
                vecin.x = i, vecin.y = j;
                //pune in coada vecinii care urmeaza a fi vizitati
                queue[++dr] = vecin;

            }
        }
        st++;
    }
    return dr;
}

/**
 * @brief parcurge drumul de lungime  minima pornind de la destinatie
 * 
 * @param start Punct - punctul destinatie
 * @param labirint int - matricea trecuta prin algorimul lui Lee
 * @param drum int - matricea in care construieste drumul
 * @param lg int lungimea curenta
 */
void Traseu( Punct start, int labirint[][101], int drum[][101], int lg) {
    if(labirint[start.x][start.y] == 1)
    {   
        fout << "Lungimea drumului este: " << lg << "\n";
        drum[start.x][start.y] = 8;
    }
    else
    {
        int p = -1;
        for(int k = 0 ; k < 4 && p == -1 ; k ++)
            if(labirint[start.x][start.y] == labirint[start.x + di[k]][start.y + dj[k]] + 1)
                p = k;
        Punct pt;
        pt.x = start.x + di[p];
        pt.y = start.y + dj[p];
        Traseu( pt, labirint, drum, lg + 1);
        drum[start.x][start.y] = 8;
    }
}


int main() {
    char labirint_char[101][101];
    int labirint[101][101] = {0};

    Punct queue[100001];
    int indice = 0, lines = 0, cols = 0, istart, jstart;
    while(fin.getline(labirint_char[lines], 1001)) {
        lines++;
    }
    cols = strlen(labirint_char[1]);

    //transforma din matrice de caractere in matrice de numre intregi
    Punct start, finish;
    for( int i = 0; i < lines; ++i)
        for( int j = 0; j < cols; ++j) {
            if( labirint_char[i][j] == '1') labirint[i][j] = -1;
            else if( labirint_char[i][j] == 'S') {
                //extrage startul
                labirint[i][j] = 0;
                start.x = i;
                start.y = j;
            }
            else if( labirint_char[i][j] == 'F') {
                //exrage finishul
                labirint[i][j] = 0;
                finish.x = i;
                finish.y = j;
            }
        }
            
    Lee(start, labirint, lines, cols, queue);
  
    //creeaza matriccea in care este insemnat drumul de lungime minima
    int drum[101][101] = {0};
    for( int i = 0; i < lines; ++i)
        for( int j = 0; j < cols; ++j)
            if( labirint[i][j] == -1)
                drum[i][j] = 7;
    Traseu( finish, labirint, drum, 1);

    //afiseaza rezultatul