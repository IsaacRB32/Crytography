#include <stdio.h>

unsigned char f_por_x(unsigned char polinomio) {
    unsigned char resultado;
    unsigned char bitMasSigni;

    resultado = polinomio << 1;

    bitMasSigni = polinomio & 0x80;

    if (bitMasSigni == 0x80){
        resultado = resultado ^ 0x2B;
    }
    
    return resultado;
}

int main() {
    int entrada;
    unsigned char polinomio;

    printf("Ingresa un polinomio en hexadecimal: ");
    scanf("%X", &entrada);

    polinomio = (unsigned char) entrada;

    unsigned char result = f_por_x(polinomio);

    printf("f(x) = 0x%02X\n", polinomio);
    printf("x * f(x) mod m(x) = 0x%02X\n", result);

    return 0;
}
