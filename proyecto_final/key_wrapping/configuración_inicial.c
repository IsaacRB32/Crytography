// setup.c
// Genera: Sbox.txt, Sbox_inv.txt, p.txt, p_inv.txt, llave.txt 
// Formatos pensados para ser leídos fácilmente por la parte de CTR

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// --------- S-box (0..15) ----------
static void generar_Sbox(int S[16]) {
    int usados[16] = {0};
    int i = 0;
    while (i < 16) {
        int x = rand() % 16;
        if (!usados[x]) {
            usados[x] = 1;
            S[i] = x;
            i++;
        }
    }
}

static void generar_inversa_Sbox(const int S[16], int S_inv[16]) {
    for (int i = 0; i < 16; i++) {
        int val = S[i];
        S_inv[val] = i;
    }
}

// --------- Permutación P (1..8) ----------
static void generar_permutacion(int n, int P[]) {
    int *N = (int*)malloc((size_t)n * sizeof(int));
    if (!N) {
        fprintf(stderr, "Error: malloc failed\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) N[i] = i + 1;

    for (int i = 0; i < n; i++) {
        int indice = rand() % (n - i);
        P[i] = N[indice];
        for (int j = indice; j < n - i - 1; j++) N[j] = N[j + 1];
    }

    free(N);
}

static void generar_inversa_permutacion(int n, const int P[], int P_inv[]) {
    // P es 1..n
    // P_inv también en 1..n, como en tu código actual
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i + 1 == P[j]) {
                P_inv[i] = j + 1;
                break;
            }
        }
    }
}

//  Llave K de 32 bits 
static unsigned int generar_llave_32(void) {
    // Genera 32 bits combinando 2 llamadas.
    unsigned int a = (unsigned int)(rand() & 0xFFFF);
    unsigned int b = (unsigned int)(rand() & 0xFFFF);
    return (a << 16) | b;
}

//  Escritura de archivos 
static void escribir_Sbox(const char *path, const int S[16]) {
    FILE *f = fopen(path, "w");
    if (!f) {
        fprintf(stderr, "Error: no se pudo abrir %s\n", path);
        exit(1);
    }
    // Encabezado como  initial.c (y CTR.c lo salta con fgets)
    fprintf(f, "z\tS(z)\n");
    for (int i = 0; i < 16; i++) {
        fprintf(f, "%X\t%X\n", i, S[i]);
    }
    fclose(f);
}

static void escribir_Sbox_inv(const char *path, const int S_inv[16]) {
    FILE *f = fopen(path, "w");
    if (!f) {
        fprintf(stderr, "Error: no se pudo abrir %s\n", path);
        exit(1);
    }
    fprintf(f, "S(z)\tS^(-1)(z)\n");
    for (int i = 0; i < 16; i++) {
        fprintf(f, "%X\t\t%X\n", i, S_inv[i]);
    }
    fclose(f);
}

static void escribir_P(const char *path, const int P[8]) {
    FILE *f = fopen(path, "w");
    if (!f) {
        fprintf(stderr, "Error: no se pudo abrir %s\n", path);
        exit(1);
    }
    // Una línea con 8 enteros separados por espacio
    for (int i = 0; i < 8; i++) {
        fprintf(f, "%d%c", P[i], (i == 7) ? '\n' : ' ');
    }
    fclose(f);
}

static void escribir_llave(const char *path, unsigned int K) {
    FILE *f = fopen(path, "w");
    if (!f) {
        fprintf(stderr, "Error: no se pudo abrir %s\n", path);
        exit(1);
    }
    // Misma convención que tu initial.c: 8 hex dígitos
    fprintf(f, "%08X\n", K);
    fclose(f);
}

int main(void) {
    srand((unsigned int)time(NULL));

    int S[16], S_inv[16];
    int P[8], P_inv[8];
    unsigned int K;

    generar_Sbox(S);
    generar_inversa_Sbox(S, S_inv);

    generar_permutacion(8, P);
    generar_inversa_permutacion(8, P, P_inv);

    K = generar_llave_32();

    // Archivos de salida
    escribir_Sbox("Sbox.txt", S);
    escribir_Sbox_inv("Sbox_inv.txt", S_inv);
    escribir_P("p.txt", P);
    escribir_P("p_inv.txt", P_inv);
    escribir_llave("llave.txt", K);

    printf("OK. Generado:\n");
    printf(" - Sbox.txt\n");
    printf(" - Sbox_inv.txt\n");
    printf(" - p.txt\n");
    printf(" - p_inv.txt\n");
    printf(" - llave.txt\n");
    return 0;
}
