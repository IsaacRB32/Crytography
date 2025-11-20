#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        resultado = resultado | (bit << pos_res);
    }
    return resultado;
}

void cargar_permutacion(const char *nombre, int P[8]) {
    FILE *f = fopen(nombre, "r");
    for (int i = 0; i < 8; i++)
        fscanf(f, "%d", &P[i]);
    fclose(f);
}

unsigned char descifrar_bloque(unsigned char C, unsigned char k0, unsigned char k1, unsigned char k2, unsigned char k3, int S_inv[16], int P_inv[8]
) {
    unsigned char M;

    M = C ^ k3;
    for (int i = 2; i >= 0; i--) {
        M = permutacion(M, P_inv);
        sustitution_function(&M, S_inv, 1);

        if (i == 0) M ^= k0;
        else if (i == 1) M ^= k1;
        else M ^= k2;
    }

    return M;
}

static const int B64index[256] = {
    [0 ... 255] = -1,
    ['A']=0,['B']=1,['C']=2,['D']=3,['E']=4,['F']=5,['G']=6,['H']=7,['I']=8,['J']=9,
    ['K']=10,['L']=11,['M']=12,['N']=13,['O']=14,['P']=15,['Q']=16,['R']=17,['S']=18,['T']=19,
    ['U']=20,['V']=21,['W']=22,['X']=23,['Y']=24,['Z']=25,
    ['a']=26,['b']=27,['c']=28,['d']=29,['e']=30,['f']=31,['g']=32,['h']=33,['i']=34,['j']=35,
    ['k']=36,['l']=37,['m']=38,['n']=39,['o']=40,['p']=41,['q']=42,['r']=43,['s']=44,['t']=45,
    ['u']=46,['v']=47,['w']=48,['x']=49,['y']=50,['z']=51,
    ['0']=52,['1']=53,['2']=54,['3']=55,['4']=56,['5']=57,['6']=58,['7']=59,['8']=60,['9']=61,
    ['+']=62,['/']=63
};

unsigned char* base64_decode(const char *src, int *out_len) {
    int len = strlen(src);
    unsigned char *out = malloc(len * 3 / 4 + 3);

    int j = 0, val = 0, valb = -8;

    for (int i = 0; i < len; i++) {
        int c = B64index[(unsigned char)src[i]];
        if (c == -1) continue;

        val = (val << 6) + c;
        valb += 6;

        if (valb >= 0) {
            out[j++] = (val >> valb) & 0xFF;
            valb -= 8;
        }
    }

    *out_len = j;
    return out;
}

int main() {
    char nombreLlave[100], nombreSinv[100], nombreP_inv[100];
    FILE *archivoLlave, *archivoSinv;
    unsigned int K;
    int S_inv[16], P_inv[8];

    printf("Ingrese el archivo con la llave: ");
    scanf("%99s", nombreLlave);

    printf("Ingrese el archivo con S^(-1): ");
    scanf("%99s", nombreSinv);

    printf("Ingrese el archivo con P^(-1): ");
    scanf("%99s", nombreP_inv);

    archivoLlave = fopen(nombreLlave, "r");
    fscanf(archivoLlave, "%X", &K);
    fclose(archivoLlave);

    archivoSinv = fopen(nombreSinv, "r");

    char header[20];
    fgets(header, sizeof(header), archivoSinv);

    for (int i = 0; i < 16; i++) {
        int z, val;
        fscanf(archivoSinv, "%X %X", &z, &val);
        S_inv[z] = val;
    }
    fclose(archivoSinv);

    cargar_permutacion(nombreP_inv, P_inv);

    char base64[2048];
    printf("\nIngrese el ciphertext (Base64):\n");
    scanf(" %[^\n]", base64);

    int clen;
    unsigned char *cipher = base64_decode(base64, &clen);

    unsigned char k0 =  K & 0xFF;
    unsigned char k1 = (K >> 8)  & 0xFF;
    unsigned char k2 = (K >> 16) & 0xFF;
    unsigned char k3 = (K >> 24) & 0xFF;

    printf("\nMensaje descifrado:\n");

    for (int i = 0; i < clen; i++) {
        unsigned char M = descifrar_bloque(cipher[i], k0, k1, k2, k3, S_inv, P_inv);
        printf("%c", M);
    }

    printf("\n");

    free(cipher);
    return 0;
}
