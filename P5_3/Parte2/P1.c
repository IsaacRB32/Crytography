#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generarLlave (unsigned int *K){
        *K = ((unsigned int)rand() << 16 | (unsigned int)rand());
}

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

int main (){
    srand(time(NULL));
    unsigned int K;
    int S[16];

    generarLlave(&K);
    S_random(S);

    FILE *archivoLlave = fopen("llave.txt", "w");
    fprintf(archivoLlave, "%08X", K);
    fclose(archivoLlave);

    FILE *archivoSbox = fopen("Sbox.txt", "w");
    fprintf(archivoSbox, "z\tS(z)\n");
    for (int i = 0; i < 16; i++) {
        fprintf(archivoSbox, "%X\t%X\n", i, S[i]);
    }
    fclose(archivoSbox);

    return 0;
}



