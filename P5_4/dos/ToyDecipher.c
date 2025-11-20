#include <stdio.h>
#include <stdlib.h>

void sustitution_function(unsigned char *M, int S_inv[16], int tamanio) {
    for (int i = 0; i < tamanio; i++) {
        unsigned char character = M[i];
        unsigned char mask_for_bits = 0x0F;
        unsigned char cuatro_mst, cuatro_lst, new_cuatro_mst, new_cuatro_lst, new_character;

        cuatro_mst = (character >> 4) & mask_for_bits;
        cuatro_lst = character & mask_for_bits;

        new_cuatro_mst = S_inv[cuatro_mst];
        new_cuatro_lst = S_inv[cuatro_lst];

        new_character = (new_cuatro_mst << 4) | new_cuatro_lst;

        M[i] = new_character;
    }
}

unsigned char permutacion(unsigned char dato, int P_inv[8]) {
    unsigned char resultado = 0x0;
    for (int i = 0; i < 8; i++) {
        int pos_perm = 8 - P_inv[i];
        int pos_res = 7 - i;
        unsigned char bit = (dato >> pos_perm) & 0x01;
        resultado |= (bit << pos_res);
    }
    return resultado;
}


void cargar_permutacion(const char *nombre, int P[8]) {
    FILE *f = fopen(nombre, "r");
    for (int i = 0; i < 8; i++) fscanf(f, "%d", &P[i]);
    fclose(f);
}

int main() {
    char nombreLlave[100], nombreSinv[100], nombreP_inv[100];
    FILE *archivoLlave, *archivoSinv;
    unsigned int K;
    int S_inv[16], P_inv[8];
    unsigned char C;

    printf("Ingrese el nombre del archivo donde esta almacenada la llave: ");
    scanf("%99s", nombreLlave);

    printf("Ingrese el nombre del archivo donde esta almacenada la funcion S^(-1): ");
    scanf("%99s", nombreSinv);

    printf("Ingrese el nombre del archivo donde esta almacenada la permutacion inversa P^(-1): ");
    scanf("%99s", nombreP_inv);

    archivoLlave = fopen(nombreLlave, "r");

    fscanf(archivoLlave, "%X", &K);
    fclose(archivoLlave);

    archivoSinv = fopen(nombreSinv, "r");

    char encabezado[20];
    fgets(encabezado, sizeof(encabezado), archivoSinv);
    for (int i = 0; i < 16; i++) {
        int z, val;
        fscanf(archivoSinv, "%X %X", &z, &val);
        S_inv[z] = val;
    }
    fclose(archivoSinv);

    cargar_permutacion(nombreP_inv, P_inv);

    printf("\nIngrese el valor hexadecimal C cifrado: ");
    unsigned int tempC;
    scanf("%X", &tempC);
    C = (unsigned char) tempC;

    unsigned char k0 =  K & 0xFF;
    unsigned char k1 = (K >> 8)  & 0xFF;
    unsigned char k2 = (K >> 16) & 0xFF;
    unsigned char k3 = (K >> 24) & 0xFF;

    unsigned char M = C ^ k3;

    for (int i = 2; i >= 0; i--) {
        M = permutacion(M, P_inv);
        sustitution_function(&M, S_inv, 1);
        if (i == 0) M ^= k0;
        else if (i == 1) M ^= k1;
        else M ^= k2;
    }

    printf("\nCaracter decifrado: '%c' (HEX: %02X)\n", M, M);

    return 0;
}
