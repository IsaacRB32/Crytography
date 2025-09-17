#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int Multiplicacion (int n) {
    
    int resultado = 0;

    for (int fila = 1; fila < n; fila++){
        
        for (int columna = 1; columna < n; columna++){
            
            resultado = (fila * columna) % n;
            printf("%2d ", resultado);
        }
        printf("\n");   
    } 
}


int main(){

    //Números pares para 2 ≤ n ≤ 50.
    int numerosPares [25] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50};

    //Números impares para 2 ≤ n ≤ 50.
    int numerosImpares[25] = {3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49};

    //Números primos para 2 ≤ n ≤ 50
    int primos [15] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};

    srand(time(NULL));

    int randomNumerosPares = rand() % 25;
    int randomNumerosImpares = rand() % 25;
    int randomPrimos = rand() % 15;

    int Zprimos = primos[randomPrimos];

    printf("Numeros Primos 2 ≤ n ≤ 50: Tabla de multiplicar de Z%d-{0}\n", Zprimos);
  
    // Multiplicacion(Zprimos);
    Multiplicacion(7);


    int ZnumerosPares = numerosPares[randomNumerosPares];

    printf("\n");
    printf("\nNumeros Pares 2 ≤ n ≤ 50: Tabla de multiplicar de Z%d-{0}\n", ZnumerosPares);
  
    Multiplicacion(ZnumerosPares);

    int ZnumerosImpares = numerosImpares[randomNumerosImpares];

    printf("\n");
    printf("\nNumeros Impares 2 ≤ n ≤ 50: Tabla de multiplicar de Z%d-{0}\n", ZnumerosImpares);
  
    Multiplicacion(ZnumerosImpares);
    
    return 0;

}