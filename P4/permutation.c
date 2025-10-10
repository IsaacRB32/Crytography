#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* permutation(char *M, int *P, int tamanioP) {
    int size_M = strlen(M);
    int size_P = tamanioP;
    
    int blocks = size_M / size_P;
    int module = size_M % size_P;
    int aux_t = 0;

    if (module != 0) {
        int missings = size_P - module;
        M = realloc(M, size_M + missings + 1);
        for (int i = 0; i < missings; i++) {
            M[size_M + i] = 'X';
        }
        M[size_M + missings] = '\0';
        blocks++;
    }

    char *C = (char *)malloc(blocks * size_P + 1);
    aux_t = 0;

    for (int i = 0; i < blocks; i++) {
        for (int j = 0; j < size_P; j++) {
            C[aux_t + j] = M[aux_t + P[j] - 1];
        }
        aux_t += size_P;
    }
    C[blocks * size_P] = '\0';

    return C;
}

int main() {
    char nombreArchivo[100], nombreSalida[100];
    FILE *archivo;
    char *M, *C;
    long size;
    int *P, tamanio;

    printf("Ingrese el nombre del archivo de texto (ej. mensaje.txt): ");
    scanf("%99s", nombreArchivo);

    archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo '%s'.\n", nombreArchivo);
        return 1;
    }

    fseek(archivo, 0, SEEK_END);
    size = ftell(archivo);
    rewind(archivo);


    M = (char *)malloc((size + 1) * sizeof(char));
    fread(M, 1, size, archivo);
    M[size] = '\0';
    fclose(archivo);

    printf("Archivo '%s' leido bien (%ld bytes)\n", nombreArchivo, size);

    printf("Ingrese el tamanio de la permutacion: ");
    scanf("%d", &tamanio);

    if (tamanio < 3) printf("El tamanio de la permutacion tiene que ser mayor igual a 3\n"); return 0;

    P = (int *)malloc(tamanio * sizeof(int));
    printf("Ingrese los %d numeros de la permutacion separados por espacio:\n", tamanio);
    for (int i = 0; i < tamanio; i++) scanf("%d", &P[i]);

    C = permutation(M, P, tamanio);


    strcpy(nombreSalida, nombreArchivo);
    char *punto = strrchr(nombreSalida, '.');
    if (punto) strcpy(punto, ".pi");
    else strcat(nombreSalida, ".pi");

    FILE *salida = fopen(nombreSalida, "w");
    if (salida == NULL) {
        printf("No se pudo crear el archivo de salida\n");
        return 1;
    }

    fprintf(salida, "%s", C);
    fclose(salida);

    printf("\nMensaje guardado como '%s'\n", nombreSalida);

    free(M);
    free(P);
    free(C);
    return 0;
}
