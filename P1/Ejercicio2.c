#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#define ASCII_START 32
#define ASCII_END 126

int indiceAlfabeto(char a, char alfabeto[], int n){
    for (int i = 0; i < n; i++){
        if(alfabeto[i] == a) return i;
    }
    return -1;
}

void cifrar (char palabra[], int key, char alfabeto[], int n){
    char cifrado[500];
    int indice;

    for (int i = 0; palabra[i] != '\0'; i++){
        indice = indiceAlfabeto(palabra[i],alfabeto,n);
        if (indice != -1){
            cifrado[i]=alfabeto[(indice + key)%n];
        }else{
            cifrado[i] = palabra[i];
        }
    }
    cifrado[strlen(palabra)] = '\0';
    printf("C = %s\n", cifrado);
}

void descifrar (char palabraCifrada[], int key, char alfabeto[], int n){
    char palabra[500];
    int indice;

    for (int i = 0; palabraCifrada[i] != '\0'; i++){
        indice = indiceAlfabeto(palabraCifrada[i], alfabeto,n);
        if(indice != -1 ){
            int resta = (indice-key);
            if(resta >= 0){
                palabra[i] = alfabeto[(resta)%n];
            }else{
                palabra[i] = alfabeto[n-(-resta%n)];
            }
        }else{
            palabra[i] = palabraCifrada[i];
        }    
    }

    palabra[strlen(palabraCifrada)] = '\0';
    printf("Tu mensaje es -> M =1 %s\n",palabra);
    
}

int main() {
    char alfabetoIngles[26];
    char alfabetoASCII[95];
    char alfabetoPersonal[95];
    char palabra[500];
    int key;
    int opc, opcAlfa, num_carac, c;
    srand(time(NULL));

    for (int i = 0; i < 26; i++)
                alfabetoIngles[i] = 'a' + i;

    for (int i = 0; i < 95; i++)
                    alfabetoASCII[i] = ASCII_START + i;

    while (1) {
        printf("**Menu**\n");
        printf("1. Cifrar\n");
        printf("2. Decifrar\n");
        printf("3. Cifrar o Decifrar con alfabeto aleatorio\n");
        printf("Selecciona una opcion: ");
        scanf("%d", &opc);

        if (opc == 1) {
            printf("**Seleccione el tipo de alfabeto**\n");
            printf("1. Ingles\n");
            printf("2. ASCII\n");
            printf("Selecciona una opcion: ");
            scanf("%d", &opcAlfa);

            if (opcAlfa == 1) {

                for (int i = 0; i < 26; i++)
                    printf("%c ", alfabetoIngles[i]);
                printf("\n");
                
                while ((c = getchar()) != '\n' && c != EOF);

                printf("\nIngresa un mesaje -> M = ");
                fgets(palabra, sizeof(palabra), stdin);
                // Quito el salto de línea al final
                palabra[strcspn(palabra, "\n")] = '\0';

                while (1) {
                    printf("Ingresa una llave (1-26) -> K = ");
                    scanf("%d", &key);
                    if (key >= 1 && key <= 26)
                        break;
                    printf("Tu llave debe pertenecer a Z26\n");
                }

                cifrar(palabra, key, alfabetoIngles, 26);

            } else if (opcAlfa == 2) {

                for (int i = 0; i < 95; i++)
                    printf("%c ", alfabetoASCII[i]);
                printf("\n");
                
                while ((c = getchar()) != '\n' && c != EOF);

                printf("\nIngresa un mensaje -> M = ");
                fgets(palabra, sizeof(palabra), stdin);

                palabra[strcspn(palabra, "\n")] = '\0';

                while (1) {
                    printf("Ingresa una llave (1-95) -> K = ");
                    scanf("%d", &key);
                    if (key >= 1 && key <= 95)
                        break;
                    printf("Tu llave debe pertenecer a Z95\n");
                }

                cifrar(palabra, key, alfabetoASCII, 95);

            }else{
                printf("Opcion no valida\n");
                break;
            }

        }else if (opc == 2){
            printf("**Seleccione el tipo de alfabeto**\n");
            printf("1. Ingles\n");
            printf("2. ASCII\n");
            printf("Selecciona una opcion: ");
            scanf("%d", &opcAlfa);
            
            while ((c = getchar()) != '\n' && c != EOF);

            printf("\nIngresa el mensaje -> C = ");
            fgets(palabra, sizeof(palabra), stdin);

            palabra[strcspn(palabra, "\n")] = '\0';

            if (opcAlfa == 1){
                while (1) {
                    printf("Ingresa la llave (1-26) -> K = ");
                    scanf("%d", &key);
                    if (key >= 1 && key <= 26)
                        break;
                    printf("Tu llave debe pertenecer a Z26\n");
                }
                descifrar(palabra,key,alfabetoIngles,26);
                
            }else if (opcAlfa == 2){
                
                while (1) {
                    printf("Ingresa la llave (1-95) -> K = ");
                    scanf("%d", &key);
                    if (key >= 1 && key <= 95)
                        break;
                    printf("Tu llave debe pertenecer a Z95\n");
                }
                descifrar(palabra,key,alfabetoASCII,95);
            }else{
                printf("Opcion no valida\n");
            }
        }else if (opc == 3) {
            static int alfabetoGenerado = 0; //Indicador que me dice si ya esta guardado el alfabeto
            static int num_carac_guardado;
            static char alfabetoPersonalGuardado[95];

            if (!alfabetoGenerado) {
                printf("Ingresa la cantidad de caracteres de tu alfabeto: ");
                scanf("%d", &num_carac_guardado);

                // Genero alfabetoPersonal aleatorio
                for (int i = 0; i < num_carac_guardado; i++)
                    alfabetoPersonalGuardado[i] = ASCII_START + rand() % (ASCII_END - ASCII_START + 1);

                printf("Alfabeto generado: ");
                for (int i = 0; i < num_carac_guardado; i++)
                    printf("%c ", alfabetoPersonalGuardado[i]);
                printf("\n");

                alfabetoGenerado = 1; // ya está creado y se conserva
            }
            printf("Alfabeto en uso: ");
            for (int i = 0; i < num_carac_guardado; i++)
                printf("%c ", alfabetoPersonalGuardado[i]);
            printf("\n");

            printf("¿Quieres cifrar (1) o descifrar (2)? ");
            scanf("%d", &opc);

            if (opc == 1) {
                while ((c = getchar()) != '\n' && c != EOF);

                printf("\nIngresa un mensaje -> M = ");
                fgets(palabra, sizeof(palabra), stdin);

                palabra[strcspn(palabra, "\n")] = '\0';

                while (1) {
                    printf("Ingresa una llave (1-%d) -> K = ", num_carac_guardado);
                    scanf("%d", &key);
                    if (key >= 1 && key <= num_carac_guardado)
                        break;
                    printf("Tu llave debe pertenecer a Z%d\n", num_carac_guardado);
                }
                
                cifrar(palabra, key, alfabetoPersonalGuardado, num_carac_guardado);
            } else if (opc == 2) {
                while ((c = getchar()) != '\n' && c != EOF);

                printf("\nIngresa el mensaje -> C = ");
                fgets(palabra, sizeof(palabra), stdin);

                palabra[strcspn(palabra, "\n")] = '\0';

                while (1) {
                    printf("Ingresa la llave (1-%d) -> K = ", num_carac_guardado);
                    scanf("%d", &key);
                    if (key >= 1 && key <= num_carac_guardado)
                        break;
                    printf("Tu llave debe pertenecer a Z%d\n", num_carac_guardado);
                }
                descifrar(palabra, key, alfabetoPersonalGuardado, num_carac_guardado);
            }
        }else{
            printf("Opcion no valida\n");
            break;
        }
    }

    return 0;
}