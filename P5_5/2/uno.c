#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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

void generar_permutacion(int n, int P[]) {
    int N[n];
    for (int i = 0; i < n; i++) N[i] = i + 1;
    for (int i = 0; i < n; i++) {
        int indice = rand() % (n - i);
        P[i] = N[indice];
        for (int j = indice; j < n - i - 1; j++) N[j] = N[j + 1];
    }
}

void generar_inversa_permutacion(int n, int P[], int P_inv[]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i + 1 == P[j]) {
                P_inv[i] = j + 1;
                break;
            }
        }
    }
}

unsigned char permutacion(unsigned char dato, int P[8]) {
    unsigned char resultado = 0x0;
    for (int i = 0; i < 8; i++) {
        int pos_perm = 8 - P[i];
        int pos_res = 7 - i;
        unsigned char bit = (dato >> pos_perm) & 0x01;
        resultado = resultado | (bit << pos_res);
    }
    return resultado;
}

unsigned char cifrar_bloque(unsigned char M, unsigned char k0, unsigned char k1, unsigned char k2, unsigned char k3, int S[16], int P[8]) {
    
    for (int i = 0; i < 3; i++) {
        if (i == 0) M = M ^ k0;
        else if (i == 1) M = M ^ k1;
        else M = M ^ k2;

        sustitution_function(&M, S, 1);
        M = permutacion(M, P);
    }

    M = M ^ k3;
    return M;
}

static const char b64chars[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char* base64_encode(const unsigned char* mensaje, int len) {
    char* out = malloc((len*4)/3 + 4);
    int j = 0;
    unsigned int val = 0;
    int valb = -6;

    for (int i = 0; i < len; i++) {
        val = (val << 8) + mensaje[i];
        valb += 8;
        while (valb >= 0) {
            out[j++] = b64chars[(val >> valb) & 0x3F];
            valb -= 6;
        }
    }

    if (valb > -6)
        out[j++] = b64chars[((val << 8) >> (valb + 8)) & 0x3F];

    while (j % 4)
        out[j++] = '=';

    out[j] = '\0';
    return out;
}


int main() {
    srand(time(NULL));

    char nombreLlave[100], nombreSbox[100];
    FILE *archivoLlave, *archivoSbox;
    char mensaje[1024];
    //unsigned char M; 
    unsigned int K;
    int S[16];
    int P[8], P_inv[8];

    generar_permutacion(8, P);
    generar_inversa_permutacion(8, P, P_inv);

    printf("Ingrese el nombre del archivo donde esta almacenada la llave: ");
    scanf("%99s", nombreLlave);

    printf("Ingrese el nombre del archivo donde esta almacenada la funcion S: ");
    scanf("%99s", nombreSbox);

    archivoLlave = fopen(nombreLlave, "r");
    archivoSbox = fopen(nombreSbox, "r");

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

    FILE *archP = fopen("p.txt", "w");
    for (int i = 0; i < 8; i++) fprintf(archP, "%d ", P[i]);
    FILE *archP_inv = fopen("p_inv.txt", "w");
    for (int i = 0; i < 8; i++) fprintf(archP_inv, "%d%c", P_inv[i], i==7?'\n':' ');
    fclose(archP_inv);
    fclose(archP);
    fclose(archP_inv);


    printf("Ingresa el mensaje en ASCII a cifrar: ");
    scanf(" %[^\n]", mensaje);

    unsigned char k0 =  K & 0xFF;
    unsigned char k1 = (K >> 8)  & 0xFF;
    unsigned char k2 = (K >> 16) & 0xFF;
    unsigned char k3 = (K >> 24) & 0xFF;

    int len_mensaje = strlen(mensaje);
    
    unsigned char ciphertext[len_mensaje];

    for (int i = 0; i < len_mensaje; i++) {
        ciphertext[i] = cifrar_bloque(mensaje[i], k0, k1, k2, k3, S, P);
    }

    char* base64 = base64_encode(ciphertext, len_mensaje);

    printf("\nCIPHERTEXT BASE64:\n%s\n", base64);

    free(base64);

    return 0;
}
