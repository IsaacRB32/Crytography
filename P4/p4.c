#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void permutation(char *M, int *P, int tamanioP) {
    printf("\nPermutacion recibida: ");
    for (int i = 0; i < tamanioP; i++) {
        printf("%d ", P[i]);
    }
    printf("\n");
    printf("Mensaje recibido: \n");
    printf("%s\n",M);

    int size_M = strlen(M);
    int size_P = tamanioP;
    printf("%d, %d\n", size_M, size_P);
    int blocks = size_M/size_P;
    int module = size_M % size_P;
    int aux_t = 0;

    if (module != 0) {
        for (int i = 0; i < size_P - module ; i++) {
            M[size_M + i] = 'X';
        }
        M[size_M + (size_P - module)] = '\0'; 
        blocks++;
    }

    char C[blocks * size_P + 1];

    for (int i = 0; i < blocks; i++){
        for (int j = 0; j < size_P ; j++){
            C[aux_t + j] = M[aux_t+P[j]-1];
        }
        aux_t = aux_t + size_P;
    }
    C[blocks * size_P] = '\0';
    
    printf("Mensaje final es: %s", C);
}

int main() {
    char nombreArchivo[100];
    FILE *archivo;
    int c, iter = 0;
    char M[500];
    int *P, tamanio;

    printf("Ingrese el nombre del archivo de texto (ej. mensaje.txt): ");
    scanf("%99s", nombreArchivo);

    archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo\n", nombreArchivo);
        return 1;
    }

    printf("Archivo '%s' abierto correctamente\n\n", nombreArchivo);
    printf("Contenido del archivo:\n");

    while ((c = fgetc(archivo)) != EOF) {
        if (iter >= 499) break; 
        M[iter++] = (char)c;
    }
    M[iter] = '\0';
    fclose(archivo);

    printf("\n\nIngrese el tamanio de la permutacion: ");
    scanf("%d", &tamanio);

    P = (int *)malloc(tamanio * sizeof(int));

    printf("Ingrese los %d numeros de la permutacion, separados por espacio (ej. 3 1 4 2):\n", tamanio);
    for (int i = 0; i < tamanio; i++) {
        scanf("%d", &P[i]);
    }

    permutation(M, P, tamanio);

    free(P);
    return 0;
}
