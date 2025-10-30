#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int generarLlave (char*K, int tamanio){
    if (tamanio <= 0){
        printf("La llave tiene que ser mayor a 0");
        return 0;
    }
    
    for (int i = 0; i < tamanio; i++)
    {
        K[i] = rand() % 256;
    }    
}

void cifrar(char*M, char*K, char*C, int tamanio){
    for (int i = 0; i < tamanio; i++){
        C[i] = M[i] ^ K[i];
    }
}

void hexadecimal(char*M, int tamanio){
    for (int i = 0; i < tamanio; i++)
    {
        printf("%02X ", (unsigned char)M[i]);
    }
    printf("\n");
}

int main(){
    int tamanio;
    size_t size = 0;
    char *M = NULL;

    srand(time(NULL));

    printf("Ingrese el mensaje: ");
    getline(&M,&size,stdin);

    tamanio = strlen(M);
    if (M[tamanio-1] == '\n'){
        M[tamanio-1] = '\0';
        tamanio--;
    }

    char *K = malloc(tamanio * sizeof(char));
    char *C = malloc(tamanio * sizeof(char));
    char *D = malloc(tamanio * sizeof(char));
    
    generarLlave(K,tamanio);
    cifrar(M,K,C,tamanio);
    cifrar(C,K,D,tamanio);
    
    printf("MENSAJE:");
    hexadecimal(M,tamanio);
    printf("LLAVE:");
    hexadecimal(K,tamanio);
    
    printf("CIFRADO:");
    hexadecimal(C,tamanio);
    
    printf("DECIFRADO:");
    hexadecimal(D,tamanio);

    free(M);
    free(C);
    free(K);
    free(D);
    return 0;
}