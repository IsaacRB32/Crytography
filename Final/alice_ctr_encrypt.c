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

        new_cuatro_mst = (unsigned char)S[cuatro_mst];
        new_cuatro_lst = (unsigned char)S[cuatro_lst];

        new_character = (unsigned char)((new_cuatro_mst << 4) | new_cuatro_lst);
        M[i] = new_character;
    }
}

unsigned char permutacion(unsigned char dato, int P[8]) {
    unsigned char resultado = 0x0;
    for (int i = 0; i < 8; i++) {
        int pos_perm = 8 - P[i];
        int pos_res  = 7 - i;
        unsigned char bit = (dato >> pos_perm) & 0x01;
        resultado = (unsigned char)(resultado | (bit << pos_res));
    }
    return resultado;
}

unsigned char cifrar_bloque(unsigned char M, unsigned char k0, unsigned char k1, unsigned char k2, unsigned char k3, int S[16], int P[8]) {
    for (int i = 0; i < 3; i++) {
        if (i == 0) M = (unsigned char)(M ^ k0);
        else if (i == 1) M = (unsigned char)(M ^ k1);
        else M = (unsigned char)(M ^ k2);

        sustitution_function(&M, S, 1);
        M = permutacion(M, P);
    }
    M = (unsigned char)(M ^ k3);
    return M;
}


static const char b64chars[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char* base64_encode(const unsigned char* mensaje, int len) {
    char* out = (char*)malloc((len * 4) / 3 + 8);
    if (!out) return NULL;

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

void leer_permutacion_archivo(const char *nombre, int P[8]) {
    FILE *f = fopen(nombre, "r");
    if (!f) {
        perror("No se pudo abrir p.txt");
        exit(1);
    }

    for (int i = 0; i < 8; i++) {
        if (fscanf(f, "%d", &P[i]) != 1) {
            fclose(f);
            fprintf(stderr, "Formato inválido en p.txt\n");
            exit(1);
        }
        if (P[i] < 1 || P[i] > 8) {
            fclose(f);
            fprintf(stderr, "p.txt fuera de rango (valores 1..8)\n");
            exit(1);
        }
    }
    fclose(f);

    int seen[9] = {0};
    for (int i = 0; i < 8; i++) {
        if (seen[P[i]]) {
            fprintf(stderr, "p.txt inválido: valor repetido\n");
            exit(1);
        }
        seen[P[i]] = 1;
    }
}

unsigned char* leer_archivo_bytes(const char *path, long *out_len) {
    *out_len = 0;
    FILE *f = fopen(path, "rb");
    if (!f) {
        perror("No se pudo abrir archivo de entrada");
        return NULL;
    }

    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return NULL; }
    long sz = ftell(f);
    if (sz < 0) { fclose(f); return NULL; }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return NULL; }

    unsigned char *buf = (unsigned char*)malloc((size_t)sz);
    if (!buf) { fclose(f); return NULL; }

    size_t r = fread(buf, 1, (size_t)sz, f);
    fclose(f);

    if (r != (size_t)sz) {
        free(buf);
        return NULL;
    }

    *out_len = sz;
    return buf;
}

int escribir_archivo_bytes(const char *path, const unsigned char *buf, long len) {
    FILE *f = fopen(path, "wb");
    if (!f) {
        perror("No se pudo abrir archivo de salida");
        return 0;
    }
    size_t w = fwrite(buf, 1, (size_t)len, f);
    fclose(f);
    return (w == (size_t)len);
}

unsigned int leer_llave_hex(const char *nombreLlave) {
    FILE *f = fopen(nombreLlave, "r");
    if (!f) { perror("llave"); exit(1); }
    unsigned int K;
    if (fscanf(f, "%X", &K) != 1) {
        fclose(f);
        fprintf(stderr, "Formato inválido en llave.txt\n");
        exit(1);
    }
    fclose(f);
    return K;
}

void leer_sbox(const char *nombreSbox, int S[16]) {
    FILE *f = fopen(nombreSbox, "r");
    if (!f) { perror("sbox"); exit(1); }

    char encabezado[64];
    fgets(encabezado, sizeof(encabezado), f);

    for (int i = 0; i < 16; i++) {
        int z, val;
        if (fscanf(f, "%X %X", &z, &val) != 2) {
            fclose(f);
            fprintf(stderr, "Sbox.txt incompleto o inválido\n");
            exit(1);
        }
        S[z] = val;
    }
    fclose(f);
}

int main() {
    srand((unsigned)time(NULL));

    char nombreLlave[256], nombreSbox[256];
    char inputPath[256];

    FILE *archivoLlave, *archivoSbox;

    unsigned int K;
    int S[16];
    int P[8];

    leer_permutacion_archivo("p.txt", P);

    printf("Ingrese el nombre del archivo donde esta almacenada la llave (ej. llave.txt): ");
    scanf("%255s", nombreLlave);

    printf("Ingrese el nombre del archivo donde esta almacenada la funcion S (ej. Sbox.txt): ");
    scanf("%255s", nombreSbox);

    printf("Ingrese el archivo a cifrar (ej. entrada.txt): ");
    scanf("%255s", inputPath);

    K = leer_llave_hex(nombreLlave);
    leer_sbox(nombreSbox, S);

    unsigned char k0 =  (unsigned char)(K & 0xFF);
    unsigned char k1 =  (unsigned char)((K >> 8)  & 0xFF);
    unsigned char k2 =  (unsigned char)((K >> 16) & 0xFF);
    unsigned char k3 =  (unsigned char)((K >> 24) & 0xFF);
    
    long len_plaintext = 0;
    unsigned char *plaintext = leer_archivo_bytes(inputPath, &len_plaintext);
    if (!plaintext && len_plaintext != 0) {
        fprintf(stderr, "Error leyendo archivo de entrada.\n");
        return 1;
    }
    
    unsigned char iv0 = (unsigned char)(rand() % 256);

    long len_mensaje = len_plaintext + 1;
    unsigned char *ciphertext = (unsigned char*)malloc((size_t)len_mensaje);
    if (!ciphertext) {
        fprintf(stderr, "malloc failed\n");
        free(plaintext);
        return 1;
    }

    ciphertext[0] = iv0;

    unsigned char iv = iv0;
    for (long i = 0; i < len_plaintext; i++) {
        unsigned char ks = cifrar_bloque(iv, k0, k1, k2, k3, S, P);
        ciphertext[i + 1] = (unsigned char)(plaintext[i] ^ ks);
        iv++;   
    }

    char *b64 = base64_encode(ciphertext, (int)len_mensaje);
    if (!b64) {
        fprintf(stderr, "Error en base64_encode\n");
        free(ciphertext);
        free(plaintext);
        return 1;
    }

    if (!escribir_archivo_bytes("cipher.b64", (unsigned char*)b64, (long)strlen(b64))) {
        fprintf(stderr, "Error escribiendo cipher.b64\n");
        free(b64);
        free(ciphertext);
        free(plaintext);
        return 1;
    }

    printf("\nOK: Archivo cifrado en CTR.\n");
    printf("IV (hex): %02X\n", iv0);
    printf("Salida base64  : cipher.b64\n");

    free(b64);
    free(ciphertext);
    free(plaintext);
    return 0;
}
