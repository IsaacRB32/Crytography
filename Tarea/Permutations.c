#include <stdio.h>

void binario(unsigned char x) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (x >> i) & 1); 
    }
}

unsigned char permutacion(unsigned char dato, int P[8]) {
    unsigned char resultado = 0x0;
    for (int i = 0; i < 8; i++) {
        int posicion_permutacion = 8 - P[i]; 
        int posicion_resultado = 7 - i;
        unsigned char bit = (dato >> posicion_permutacion) & 0x01;
        resultado = resultado | (bit << posicion_resultado);
    }

    return resultado;
}


int main() {
    int P[8] = {4, 3, 2, 1, 8, 7, 6, 5};
    unsigned char dato = 0x42;

    unsigned char resultado = permutacion(dato, P);

    printf("Dato original: ");
    binario(dato);
    printf("    (0x%02X)\n", dato);

    printf("Dato permutado: ");
    binario(resultado);
    printf("    (0x%02X)\n", resultado);

    return 0;
}
