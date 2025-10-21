#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void hexadecimal(char*M, int tamanio){
    for (int i = 0; i < tamanio; i++)
    {
        printf("%02X ", (unsigned char)M[i]);
    }
    printf("\n");
}

void table_sustitution (int S[16]){
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
    
    FILE *f = fopen("Sbox.txt", "w");
    fprintf(f, "z\tS(z)\n");
    for (int i = 0; i < 16; i++) {
        fprintf(f, "%X\t%X\n", i, S[i]);
    }
    fclose(f);
}

void sustitution_function(char*M,int S[16], int tamanio){
    printf("Mensaje actual: %s\n", M);
    printf("Mensaje actual en hexadecimal:");
    hexadecimal(M,tamanio);
    for (int i = 0; i < tamanio; i++){
        unsigned char character = M[i];
        unsigned char mask_for_bits = 0b00001111;
        unsigned char cuatro_mst, cuatro_lst,new_cuatro_mst, new_cuatro_lst,new_character;
        printf("\n\t*   Caracter actual: %X   *\n", character);
        cuatro_mst = (character >> 4) & mask_for_bits;
        printf("Los primeros cuatro bits mas significativos: %X\n",cuatro_mst);
        cuatro_lst = character & mask_for_bits; 
        printf("Los ultimos cuatro bits menos significativos: %X\n",cuatro_lst);

        printf("\n\tAplicando la funcion S\n");
        new_cuatro_mst = S[cuatro_mst];
        printf("Los nuevos primeros cuatro bits: %X\n", new_cuatro_mst);
        new_cuatro_lst = S[cuatro_lst];
        printf("Los nuevos ultimos cuatro bits: %X\n", new_cuatro_lst);

        new_character = (new_cuatro_mst << 4) | new_cuatro_lst;
        printf("\n\t--   Nuevo caracter: %X   --\n", new_character);
        M[i] = new_character;
    }
    printf("El nuevo mensaje es: %s\n", M);
    printf("Mensaje nuevo en hexadecimal:");
    hexadecimal(M,tamanio);
}

int main (){
    int S[16];
    char M[100];
    int tamanio;
    srand(time(NULL));
    
    table_sustitution(S);
    for ( int i = 0; i < 16; i++){
        printf("%X\t%X\n", i, S[i]);
    }
    
    printf("Ingrese mensaje: M = ");
    fgets( M, sizeof(M), stdin);
    M[strcspn(M, "\n")] = '\0';

    tamanio = strlen(M);

    sustitution_function(M,S,tamanio);
    
    return 0;
}

    
