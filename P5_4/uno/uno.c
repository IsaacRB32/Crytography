#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void S_random (int *S){
    int usados[16] = {0};
    int iter = 0;

    while (iter < 16){
        int numero = rand() % 16;
        if(!usados[numero]){
            usados[numero] = 1;
            S[iter]=numero;
            iter++;
        }
    }
}

void generar_inversa_S(int S[16], int S_inv[16]) {
    for (int i = 0; i < 16; i++) {
        int valor = S[i];
        S_inv[valor] = i; 
    }
}

int main (){
    srand(time(NULL));
    unsigned int K;
    int S[16];
    int S_inv[16];

    S_random(S);

    FILE *archivoSbox = fopen("Sbox.txt", "w");
    fprintf(archivoSbox, "z\tS(z)\n");
    for (int i = 0; i < 16; i++) {
        fprintf(archivoSbox, "%X\t%X\n", i, S[i]);
    }
    fclose(archivoSbox);

    generar_inversa_S(S, S_inv);

    FILE *archivoInv = fopen("Sbox_inv.txt", "w");
    fprintf(archivoInv, "S(z)\tS^(-1)(z)\n");
    for (int i = 0; i < 16; i++) {
        fprintf(archivoInv, "%X\t\t%X\n", i, S_inv[i]);
    }
    fclose(archivoInv);

    return 0;
}



