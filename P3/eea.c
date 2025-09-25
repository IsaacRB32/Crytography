#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int gcd;
    int s;
    int t;
} Resultado;

Resultado eea(int r0, int r1) {
    int s0 = 1, t0 = 0;
    int s1 = 0, t1 = 1;

    int ri_2 = r0, ri_1 = r1;
    int si_2 = s0, si_1 = s1;
    int ti_2 = t0, ti_1 = t1;

    int ri, qi, si, ti;
    int iter = 1;

    printf("\nIteraciones del algoritmo extendido de Euclides:\n");
    printf("Iteracion| q   | r        | s        | t\n");
    printf("-------------------------------------------\n");

    do {
        ri = ri_2 % ri_1;
        qi = (ri_2 - ri) / ri_1;

        si = si_2 - qi * si_1;
        ti = ti_2 - qi * ti_1;

        printf("%5d    | %2d  | %8d | %8d | %8d\n", iter, qi, ri, si, ti);

        ri_2 = ri_1; ri_1 = ri;
        si_2 = si_1; si_1 = si;
        ti_2 = ti_1; ti_1 = ti;

        iter++;

    } while (ri != 0);

    Resultado res = {ri_2, si_2, ti_2};
    return res;
}

int main() {
    srand(time(NULL));

    for (int i = 0; i < 5; i++) {
        int r0 = rand() % 100 + 1;
        int r1 = rand() % 100 + 1;
        
        Resultado r = eea(r0, r1);
        printf("\nResultado final:\n");
        printf("gcd(%d,%d) = %d\n", r0, r1, r.gcd);
        printf("s = %d, t = %d\n", r.s, r.t);
    }

    return 0;
}

