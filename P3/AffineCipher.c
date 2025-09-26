#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int gcd;
    int s;
    int t;
} Resultado;

Resultado eea(int r0, int r1) {
    int s0 = 1, t0 = 0;
    int s1 = 0, t1 = 1;

    int ri_2 = r0, ri_1 = r1;
    int si_2 = s0, si_1 = s1;
    int ti_2 = t0, ti_1 = t1;

    int ri, qi, si, ti;

    do {
        ri = ri_2 % ri_1;
        qi = (ri_2 - ri) / ri_1;

        si = si_2 - qi * si_1;
        ti = ti_2 - qi * ti_1;

        ri_2 = ri_1; ri_1 = ri;
        si_2 = si_1; si_1 = si;
        ti_2 = ti_1; ti_1 = ti;

    } while (ri != 0);

    Resultado res = {ri_2, si_2, ti_2};
    return res;
}

int inverso_mod(int a, int m) {
    Resultado r = eea(a, m);
    if (r.gcd != 1) {
        printf("%d no tiene inverso mod %d\n", a, m);
        return -1;
    }
    int inv = r.s % m;
    if (inv < 0) inv += m;
    return inv;
}

void construirAlfabeto(char *alfabeto, int *n) {
    int indice = 0;
    for (int i = 32; i <= 126; i++) {
        alfabeto[indice++] = (char)i;
    }
    alfabeto[indice] = '\0';
    *n = indice;
}

int indiceAlfabeto(char c, const char *alfabeto, int n) {
    for (int i=0; i<n; i++) {
        if (alfabeto[i]==c) return i;
    }
    return -1;
}

void affineCipher(const char *mensaje, char *resultado, int a, int b, const char *alfabeto, int n) {
    for (int i=0; mensaje[i] != '\0'; i++) {
        char c = mensaje[i];
        int pos = indiceAlfabeto(c, alfabeto, n);
        if (pos != -1) {
            int ciph = (a*pos + b) % n;
            resultado[i] = alfabeto[ciph];
        } else {
            resultado[i] = c;
        }
    }
    resultado[strlen(mensaje)] = '\0';
}

void affineDecipher(const char *mensaje_cifrado, char *resultado, int a, int b, const char *alfabeto, int n) {
    int a_inv = inverso_mod(a, n);
    if (a_inv == -1) {
        resultado[0]='\0';
        return;
    }
    for (int i=0; mensaje_cifrado[i] != '\0'; i++) {
        char c = mensaje_cifrado[i];
        int pos = indiceAlfabeto(c, alfabeto, n);
        if (pos != -1) {
            int m = ((pos - b) * a_inv) % n;
            if (m < 0) m += n;
            resultado[i] = alfabeto[m];
        } else {
            resultado[i] = c;
        }
    }
    resultado[strlen(mensaje_cifrado)] = '\0';
}

void generarLlaveRandom(int n, int *a, int *b) {
    int zn_estrella[n];
    int contador_estrella = 0;
    for (int i=1; i<n; i++) {
        if (eea(i, n).gcd == 1) {
            zn_estrella[contador_estrella++] = i;
        }
    }
    int zn[n];
    int contador_z = 0;
    for (int i=1; i<n; i++) {
        zn[contador_z++] = i;
    }

    srand((unsigned int)time(NULL));
    *a = zn_estrella[rand() % contador_estrella];
    *b = zn[rand() % contador_z];
}


int main() {
    char alfabeto[100];
    int n;
    construirAlfabeto(alfabeto, &n);

    int opcion;
    do {
        printf("\n*** Affine Cipher ***\n");
        printf("1. Cifrar mensaje\n");
        printf("2. Descifrar mensaje\n");
        printf("3. Salir\n");
        printf("Elija una opcion: ");
        scanf("%d", &opcion);
        getchar();

        if (opcion == 1) {
            int a,b;
            generarLlaveRandom(n, &a, &b);
            printf("\nLlave aleatoria: K = (%d,%d)\n", a, b);

            char mensaje[100];
            printf("*Alfabeto ASCII*\n", n);
            printf("%s\n\n", alfabeto);
            printf("Ingrese mensaje a cifrar: M = ");
            fgets(mensaje, sizeof(mensaje), stdin);
            mensaje[strcspn(mensaje, "\n")] = '\0';

            char cifrado[100];
            affineCipher(mensaje, cifrado, a, b, alfabeto, n);
            printf("Mensaje cifrado: C = %s\n", cifrado);
        }
        else if (opcion == 2) {
            int a,b;
             printf("Llave de la forma K = (a,b)");
            printf("Ingrese a: ");
            scanf("%d", &a);
            printf("Ingrese b: ");
            scanf("%d", &b);
            getchar();

            char mensaje_cifrado[100];
            printf("Ingrese mensaje cifrado: C = ");
            fgets(mensaje_cifrado, sizeof(mensaje_cifrado), stdin);
            mensaje_cifrado[strcspn(mensaje_cifrado, "\n")] = '\0';

            char descifrado[100];
            affineDecipher(mensaje_cifrado, descifrado, a, b, alfabeto, n);
            printf("Mensaje descifrado: M = %s\n", descifrado);
        }
        else if (opcion == 3) {
            printf("Adios\n");
        }
        else {
            printf("Opcion no valida\n");
        }

    } while (opcion != 3);

    return 0;
}
