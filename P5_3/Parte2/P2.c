#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void sustitution_function(unsigned char *M, int S[16], int tamanio) {
    for (int i = 0; i < tamanio; i++) {
        unsigned char character = M[i];
        unsigned char mask_for_bits = 0x0F;
        unsigned char cuatro_mst, cuatro_lst, new_cuatro_mst, new_cuatro_lst, new_character;

        cuatro_mst = (character >> 4) & mask_for_bits;
        cuatro_lst = character & mask_for_bits;

        new_cuatro_mst = S[cuatro_mst];
        new_cuatro_lst = S[cuatro_lst];

        new_character = (new_cuatro_mst << 4) | new_cuatro_lst;

        M[i] = new_character;
    }
}

int main (){
    char nombreLlave[100];
    char nombreSbox[100];
    FILE *archivoLlave;
    FILE *archivoSbox;
    unsigned char M; 
    unsigned int K;
    int S[16];

    printf("Ingrese el nombre del archivo donde esta almacenada la llave: ");
    scanf("%99s", nombreLlave);

    printf("Ingrese el nombre del archivo donde esta almacenada la funcion S: ");
    scanf("%99s", nombreSbox);

    archivoLlave = fopen(nombreLlave, "r");
    if (archivoLlave == NULL) {
        printf("No se pudo abrir el archivo de la llave: %s\n", nombreLlave);
        return 1;
    }

    archivoSbox = fopen(nombreSbox, "r");
    if (archivoSbox == NULL) {
        printf("No se pudo abrir el archivo de la funcion S: %s\n", nombreSbox);
        fclose(archivoLlave);
        return 1;
    }

    printf("\nArchivos abiertos correctamente:\n");

    printf("\nIngrese el caracter ASCII: ");
    scanf(" %c", &M);

    printf("El caracter ingresado es '%c', su valor ASCII es: %d y en HEX es: %02X\n", M, M, M);

    fscanf(archivoLlave, "%X", &K); 
    fclose(archivoLlave);

    char encabezado[20];
    fgets(encabezado, sizeof(encabezado), archivoSbox);
    for (int i = 0; i < 16; i++) {
        int z, val;
        fscanf(archivoSbox, "%X %X", &z, &val);
        S[z] = val;
    }
    fclose(archivoSbox);

    unsigned char k0 =  K & 0xFF;
    unsigned char k1 = (K >> 8)  & 0xFF;
    unsigned char k2 = (K >> 16) & 0xFF;
    unsigned char k3 = (K >> 24) & 0xFF;

    for (int i = 0; i < 3; i++) {
    if (i == 0) {
        M = M ^ k0;
    } 
    else if (i == 1) {
        M = M ^ k1;
    } 
    else {
        M = M ^ k2;
    }
    sustitution_function(&M, S, 1); 
    }

    unsigned char C = M ^ k3;

    printf("\nCaracter cifrado: %02X\n", C); 

    fclose(archivoLlave);
    fclose(archivoSbox);

    return 0;
}