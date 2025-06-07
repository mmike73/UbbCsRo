//
// Created by Mihai Moldovan on 28.02.2024.
//
#include <stdio.h>
#include <string.h>
int calc_sum();
int genereaza_n_prime(int a[], int n);
int genereaza_prime_ltn(int a[], int n);
int reprezentari_s(int a[], int b[], int n);
int insertion_sort(int n, int a[]);
int descompunere_f_p(int n, int a[], int b[]);
int suma_nre_prime(int n, int a[]);
int zecimale(int a[], float raport, int n);
int sir_termeni(int a[], int n);
int pascal_triangle(int triangle[][101], int m);
int exponent_p_fact(int n, int p);
int exponent_10_lista(int a[], int n);
int ind_euler(int a[], int n);
int ind_nr_div(int a[], int numar);


int main() {
    char command[21] = "";
    while(1) {
        int n = 0;
        int a[10001] = {0}, b[101] = {0};
        printf(">>> ");
        scanf("%s", &command);
        if(strcmp(command, "exit") == 0)
            return 0;
        else if( strcmp(command, "hello") == 0)
            printf("Hello, World!\n");
        else if( strcmp(command, "suma") == 0 || strcmp(command, "0") == 0) {
            printf("%d\n",calc_sum());
        }




        else if(strcmp(command, "reprezentari_suma_consecutive") == 0 || strcmp(command, "3") == 0) {
            printf("Introdu un numar: ");
            scanf("%d", &n);
            int nr_reprezentari = reprezentari_s(a, b, n);
            printf("Numarul reprezentarilor este %d.\n", nr_reprezentari);
            for( int i = 1; i <= nr_reprezentari; i ++) {
                for (int j = a[i]; j < b[i]; j++)
                    printf("%d + ", j);
                printf("%d = %d\n", b[i], n);
            }
        }
        else if(strcmp(command, "sir_termeni") == 0 || strcmp((command), "5") == 0) {
            printf("Introdu un numar: ");
            scanf("%d", &n);
            sir_termeni( a, n);
            for( int i = 1; i <= n; ++i)
                printf("%d ", a[i]);
            printf("\n");
        }







        else if( strcmp(command, "n_prime") == 0 || strcmp(command, "1") == 0) {
            printf("Introdu un numar: ");
            scanf("%d", &n);
            int nr_prime = genereaza_n_prime(a, n);
            for( int i = 0; i < nr_prime; i += 1) {
                printf("%d ", a[i]);
            }
            printf("\n");
        }
        else if( strcmp(command, "prime_lt_n") == 0 || strcmp(command, "2") == 0) {
            printf("Introdu un numar: ");
            scanf("%d", &n);
            int nr_prime = genereaza_prime_ltn(a, n);
            for( int i = 0; i < nr_prime; i += 1) {
                printf("%d ", a[i]);
            }
            printf("\n");
        }
        else if(strcmp(command, "zecimale") == 0 || strcmp(command, "4") == 0) {
            int k, m;
            printf("Introdu numaratorul(k): ");
            scanf("%d", &k);
            printf("Introdu numitorul(m): ");
            scanf("%d", &m);
            printf("Introdu numarul de zecimale: ");
            scanf("%d", &n);
            float k1 = (float)k, m1 = (float)m, raport = k1 / m1;
            zecimale(a,raport, n);
            for( int i = 1; i <= n; i ++ )
                printf("%d ", a[i]);
        }
        else if(strcmp(command, "triunghiul_lui_Pascal") == 0 || strcmp(command, "6") == 0) {
            int m, k, triangle[101][101] = {0};
            printf("Introdu numarul de obiecte(m): ");
            scanf("%d", &m);
            printf("Luate a cate(k): ");
            scanf("%d", &k);
            pascal_triangle(triangle, m);
            for( int i = 0; i <= m; ++i, printf("\n"))
                for (int j = 0; j <= i; j++) {
                    printf("C(%d, %d) = %d  ", i, j, triangle[i][j]);
                }
        }
        else if(strcmp(command, "radical") == 0 || strcmp(command,"7") == 0) {
            int precision;
        }
        else if(strcmp(command, "exp_prim_fact") == 0 || strcmp(command, "8") == 0) {
            int prim;
            printf("Introdu un numar prim: ");
            scanf("%d", &prim);
            printf("Introdu un numar(n, pt care se realizeaza n!): ");
            scanf("%d", &n);
            int exp = exponent_p_fact(n, prim);
            printf("%d\n", exp);
        }
        else if(strcmp(command, "nr_zero_sfarsit") == 0 || strcmp(command, "9") == 0) {
            int cnt = 0, aux = 1;
            printf("Introdu numere si incheei citirea introducand 0: ");
            while( aux != 0) {
                scanf("%d", &aux);
                cnt ++;
                a[cnt] = aux;
            }
            cnt--;
            int rez = exponent_10_lista(a, cnt);
            printf("%d\n",rez);

        }
        else if(strcmp(command, "factori_primi") == 0 || strcmp(command, "13") == 0) {
            int nr_f;
            printf("Introdu un numar: ");
            scanf("%d", &n);
            nr_f = descompunere_f_p(n, a, b);
            for( int i = 1; i <= nr_f; ++i) {
                printf("numar prim: %d exponent: %d\n", a[i], b[i]);
            }
        }
        else if(strcmp(command, "sum_2_prime") == 0 || strcmp(command, "14") == 0) {
            int x = 0, y = 0;
            printf("Introdu un numar PAR: ");
            scanf("%d", &n);
            if(suma_nre_prime(n, a) == -1) {
                printf("Introdu un numar par!!!\n");
            }
            else
                printf("%d + %d = %d\n", a[0], a[1], n);
        }
        else if(strcmp(command, "prime_intre_ele") == 0 || strcmp(command, "15") == 0) {
            int x, cnt;
            printf("Introdu un numar: ");
            scanf("%d", &x);
            ind_nr_div(a, x);
            for( int i = 1; i < x; i++)
                if(a[i] == 0) printf("%d ", i);
            printf("\n");
        }
    }
    return 0;
}
