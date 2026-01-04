#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

void S_random(int *S) {
    int usados[16] = {0};
    int iter = 0;

    while (iter < 16) {
        int numero = rand() % 16;
        if (!usados[numero]) {
            usados[numero] = 1;
            S[iter] = numero;
            iter++;
        }
    }
}

void generar_inversa_S(const int S[16], int S_inv[16]) {
    for (int i = 0; i < 16; i++) {
        int valor = S[i];
        S_inv[valor] = i;
    }
}

void generar_permutacion8(int P[8]) {
    int N[8];
    for (int i = 0; i < 8; i++) N[i] = i + 1;  // 1..8

    for (int i = 0; i < 8; i++) {
        int idx = rand() % (8 - i);
        P[i] = N[idx];
        for (int j = idx; j < 8 - i - 1; j++) {
            N[j] = N[j + 1];
        }
    }
}

void generar_inversa_permutacion8(const int P[8], int P_inv[8]) {
    
    for (int x = 0; x < 8; x++) {
        int val = x + 1;
        for (int j = 0; j < 8; j++) {
            if (P[j] == val) {
                P_inv[x] = j + 1; 
                break;
            }
        }
    }
}


void generarLlave (unsigned int *K){
    *K = (((unsigned int)rand() << 16) | (unsigned int)rand());
}


int main(void) {
    srand((unsigned int)time(NULL));

    unsigned int K;
    int S[16];
    int S_inv[16];
    int P[8], P_inv[8];

    S_random(S);
    generar_inversa_S(S, S_inv);

    generar_permutacion8(P);
    generar_inversa_permutacion8(P, P_inv);

    generarLlave(&K);
    if (K == 0) K = 1;

    FILE *archivoSbox = fopen("Sbox.txt", "w");
    if (!archivoSbox) { perror("Sbox.txt"); return 1; }
    fprintf(archivoSbox, "z\tS(z)\n");
    for (int i = 0; i < 16; i++) fprintf(archivoSbox, "%X\t%X\n", i, S[i]);
    fclose(archivoSbox);

    FILE *archivoInv = fopen("Sbox_inv.txt", "w");
    if (!archivoInv) { perror("Sbox_inv.txt"); return 1; }
    fprintf(archivoInv, "S(z)\tS^(-1)(z)\n");
    for (int i = 0; i < 16; i++) fprintf(archivoInv, "%X\t\t%X\n", i, S_inv[i]);
    fclose(archivoInv);

    FILE *archivoLlave = fopen("llave.txt", "w");
    if (!archivoLlave) { perror("llave.txt"); return 1; }
    fprintf(archivoLlave, "%08X\n", K);
    fclose(archivoLlave);


    FILE *archP = fopen("p.txt", "w");
    if (!archP) { perror("p.txt"); return 1; }
    for (int i = 0; i < 8; i++) fprintf(archP, "%d%c", P[i], (i == 7) ? '\n' : ' ');
    fclose(archP);

    FILE *archP_inv = fopen("p_inv.txt", "w");
    if (!archP_inv) { perror("p_inv.txt"); return 1; }
    for (int i = 0; i < 8; i++) fprintf(archP_inv, "%d%c", P_inv[i], (i == 7) ? '\n' : ' ');
    fclose(archP_inv);

    printf("Archivos generados: Sbox.txt, Sbox_inv.txt, llave.txt, p.txt, p_inv.txt\n");
    return 0;
}