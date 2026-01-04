#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

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

unsigned char* leer_archivo_texto(const char *path, long *out_len) {
    *out_len = 0;
    FILE *f = fopen(path, "rb");
    if (!f) {
        perror("No se pudo abrir cipher.b64");
        return NULL;
    }

    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return NULL; }
    long sz = ftell(f);
    if (sz < 0) { fclose(f); return NULL; }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return NULL; }

    unsigned char *buf = (unsigned char*)malloc((size_t)sz + 1);
    if (!buf) { fclose(f); return NULL; }

    size_t r = fread(buf, 1, (size_t)sz, f);
    fclose(f);
    buf[r] = '\0';

    *out_len = (long)r;
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

int b64_index(char c) {
    if (c >= 'A' && c <= 'Z') return c - 'A';
    if (c >= 'a' && c <= 'z') return c - 'a' + 26;
    if (c >= '0' && c <= '9') return c - '0' + 52;
    if (c == '+') return 62;
    if (c == '/') return 63;
    return -1;
}

unsigned char* base64_decode(const unsigned char *in, long in_len, long *out_len) {
    *out_len = 0;

    long valid = 0;
    for (long i = 0; i < in_len; i++) {
        unsigned char c = in[i];
        if (isspace(c)) continue;
        valid++;
    }

    if (valid % 4 != 0) {
        fprintf(stderr, "Base64 inválido: longitud no múltiplo de 4\n");
        return NULL;
    }

    long alloc = (valid / 4) * 3;
    unsigned char *out = (unsigned char*)malloc((size_t)alloc);
    if (!out) return NULL;

    long j = 0;
    int quad[4];
    int qi = 0;

    for (long i = 0; i < in_len; i++) {
        unsigned char c = in[i];
        if (isspace(c)) continue;

        if (c == '=') quad[qi++] = -2;
        else {
            int idx = b64_index((char)c);
            if (idx < 0) { free(out); return NULL; }
            quad[qi++] = idx;
        }

        if (qi == 4) {
            int a = quad[0], b = quad[1], c2 = quad[2], d = quad[3];

            if (a < 0 || b < 0) { free(out); return NULL; }

            unsigned int triple = (unsigned int)((a << 18) | (b << 12) |
                                 ((c2 > -1 ? c2 : 0) << 6) |
                                 (d  > -1 ? d  : 0));

            out[j++] = (unsigned char)((triple >> 16) & 0xFF);
            if (c2 != -2) out[j++] = (unsigned char)((triple >> 8) & 0xFF);
            if (d  != -2) out[j++] = (unsigned char)(triple & 0xFF);

            qi = 0;
        }
    }

    *out_len = j;
    return out;
}

int main() {
    char nombreLlave[256], nombreSbox[256];
    char ciphertext[256];
    char plaintext[256];

    unsigned int K;
    int S[16];
    int P[8];

    printf("Ingrese el nombre del archivo donde esta almacenada la llave (ej. llave.txt): ");
    scanf("%255s", nombreLlave);

    printf("Ingrese el nombre del archivo donde esta almacenada la funcion S (ej. Sbox.txt): ");
    scanf("%255s", nombreSbox);

    printf("Ingrese el archivo base64 del cifrado (cipher.b64): ");
    scanf("%255s", ciphertext);

    printf("Ingrese el nombre del archivo recuperado (ej. decipher.txt): ");
    scanf("%255s", plaintext);

    leer_permutacion_archivo("p.txt", P);
    K = leer_llave_hex(nombreLlave);
    leer_sbox(nombreSbox, S);

    unsigned char k0 = (unsigned char)(K & 0xFF);
    unsigned char k1 = (unsigned char)((K >> 8) & 0xFF);
    unsigned char k2 = (unsigned char)((K >> 16) & 0xFF);
    unsigned char k3 = (unsigned char)((K >> 24) & 0xFF);

    long b64_len = 0;
    unsigned char *b64_txt = leer_archivo_texto(ciphertext, &b64_len);
    if (!b64_txt) {
        fprintf(stderr, "No se pudo leer cipher.b64\n");
        return 1;
    }

    long data_len = 0;
    unsigned char *data = base64_decode(b64_txt, b64_len, &data_len);
    free(b64_txt);

    if (!data || data_len < 1) {
        fprintf(stderr, "Base64 inválido o vacío\n");
        free(data);
        return 1;
    }

    unsigned char iv0 = data[0];
    long len_ciphertext = data_len - 1;
    unsigned char *ciphertext = data + 1;

    unsigned char *plaintext = (unsigned char*)malloc((size_t)len_ciphertext);
    if (!plaintext) {
        fprintf(stderr, "malloc failed\n");
        free(data);
        return 1;
    }

    unsigned char iv = iv0;
    for (long i = 0; i < len_ciphertext; i++) {
        unsigned char ks = cifrar_bloque(iv, k0, k1, k2, k3, S, P);
        plaintext[i] = (unsigned char)(ciphertext[i] ^ ks);
        iv++;
    }

    if (!escribir_archivo_bytes(plaintext, plaintext, len_ciphertext)) {
        fprintf(stderr, "Error escribiendo archivo recuperado\n");
        free(plaintext);
        free(data);
        return 1;
    }

    printf("\nOK: Archivo recuperado.\n");
    printf("IV (hex): %02X\n", iv0);
    printf("Salida: %s (len=%ld bytes)\n", plaintext, len_ciphertext);

    free(plaintext);
    free(data);
    return 0;
}
