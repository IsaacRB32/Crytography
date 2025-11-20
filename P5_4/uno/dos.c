#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void binario(unsigned char x) {
    for (int i = 7; i >= 0; i--) printf("%d", (x >> i) & 1);
}

void generar_permutacion(int n, int P[]) {
    int N[n];
    for (int i = 0; i < n; i++) N[i] = i + 1;
    for (int i = 0; i < n; i++) {
        int indice = rand() % (n - i);
        P[i] = N[indice];
        for (int j = indice; j < n - i - 1; j++) N[j] = N[j + 1];
    }
}

unsigned char permutacion(unsigned char dato, int P[8]) {
    unsigned char resultado = 0x0;
    for (int i = 0; i < 8; i++) {
        int pos_perm = 8 - P[i];
        int pos_res = 7 - i;
        unsigned char bit = (dato >> pos_perm) & 0x01;
        resultado = resultado | (bit << pos_res);
    }
    return resultado;
}

int main() {
    srand(time(NULL));
    unsigned char dato = 0x42;
    int P[8];

    printf("Dato original: ");
    binario(dato);
    printf(" (0x%02X)\n\n", dato);

    for (int i = 0; i < 10; i++) {
        generar_permutacion(8, P);
        printf("P%d = [ ", i + 1);
        
        for (int j = 0; j < 8; j++)
            printf("%d ", P[j]);

        printf("]\n");

        unsigned char resultado = permutacion(dato, P);
        printf("Resultado: ");
        binario(resultado);
        printf(" (0x%02X)\n\n", resultado);
    }

    return 0;
}
