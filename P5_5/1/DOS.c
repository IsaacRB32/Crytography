#include <stdio.h>

unsigned char f_por_x(unsigned char polinomio) {
    unsigned char resultado = polinomio << 1;
    if (polinomio & 0x80) { 
        resultado ^= 0x2B;   
    }
    return resultado;
}

unsigned char multiplicar_GF(unsigned char f, unsigned char g) {
    unsigned char resultado;
    unsigned char bitMenosSignificativo;
    unsigned char nuevoF;
    unsigned char nuevoG;
    resultado = 0;
    nuevoF = f;
    nuevoG = g;

    while (nuevoG != 0) {
        bitMenosSignificativo = nuevoG & 0x01;
        if (bitMenosSignificativo == 0x01) {
            resultado = resultado ^ nuevoF;
        }
        nuevoF = f_por_x(nuevoF);
        nuevoG = nuevoG >> 1;
    }
    return resultado;
}

int main() {
    int aux1, aux2;
    unsigned char f, g;

    printf("Ingresa f(x) en hexadecimal: ");
    scanf("%X", &aux1);
    f = (unsigned char) aux1;

    printf("Ingresa g(x) en hexadecimal: ");
    scanf("%X", &aux2);
    g = (unsigned char) aux2;

    unsigned char result = multiplicar_GF(f, g);

    printf("\nf(x) = 0x%02X\n", f);
    printf("g(x) = 0x%02X\n", g);
    printf("f(x) * g(x) mod m(x) = 0x%02X\n", result);

    return 0;
}
