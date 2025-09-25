#include <stdio.h>
#include <stdlib.h>



/**
 * Algoritmo Extendido de Euclides - Implementación Iterativa
 * Encuentra MCD(r0_inicial, r1_inicial) y los coeficientes s y t
 * tales que: MCD = s * r0_inicial + t * r1_inicial.
 * r0_inicial Primer número.
 * r1_inicial Segundo número.
 * s_final Puntero para almacenar el coeficiente 's'.
 * t_final Puntero para almacenar el coeficiente 't'.
 * El Máximo Común Divisor (MCD).
 */
int algoritmo_euclides_extendido(int r0_inicial, int r1_inicial, int *s_final, int *t_final) {
    // La notación sigue el pseudocódigo de la tabla (r_i, s_i, t_i)
    int r_anterior = r0_inicial; // r_{i-2}
    int r_actual = r1_inicial;   // r_{i-1}
    int s_anterior = 1;          // s_0
    int s_actual = 0;            // s_1
    int t_anterior = 0;          // t_0
    int t_actual = 1;            // t_1

    int i = 1; // Contador de iteraciones
    
    // Imprimir inicialización
    printf("--------------------------------------\n");
    printf("Inicialización (i=0, i=1):\n");
    printf("i=0: r0=%d, s0=%d, t0=%d\n", r0_inicial, 1, 0);
    printf("i=1: r1=%d, s1=%d, t1=%d\n", r1_inicial, 0, 1);
    printf("--------------------------------------\n");

    // Bucle principal: MIENTRAS r_actual (r_i) sea diferente de 0
    while (r_actual != 0) {
        
        // 1.3 q_i = (r_{i-2} / r_{i-1})
        int cociente = r_anterior / r_actual;
        
        // 1.2 r_siguiente = r_{i-2} mod r_{i-1}
        int r_siguiente = r_anterior % r_actual;
        
        // 1.4 s_siguiente = s_{i-2} - cociente * s_{i-1}
        int s_siguiente = s_anterior - cociente * s_actual;
        
        // 1.5 t_siguiente = t_{i-2} - cociente * t_{i-1}
        int t_siguiente = t_anterior - cociente * t_actual;

        // Imprimir los valores de la sustitución para la fila i+1
        printf("Iteración i=%d:\n", i + 1);
        printf("cociente (q_%d) = %d\n", i, cociente);
        printf("r_%d = %d - %d * %d = %d\n", 
               i+1, r_anterior, cociente, r_actual, r_siguiente);
        printf("s_%d = %d - %d * %d = %d\n", 
               i+1, s_anterior, cociente, s_actual, s_siguiente);
        printf("t_%d = %d - %d * %d = %d\n", 
               i+1, t_anterior, cociente, t_actual, t_siguiente);
        printf("--------------------------------------\n");

        // Actualizar variables para la siguiente iteración
        r_anterior = r_actual; 
        r_actual = r_siguiente; 
        s_anterior = s_actual; 
        s_actual = s_siguiente; 
        t_anterior = t_actual; 
        t_actual = t_siguiente; 
        
        //  i = i + 1
        i++;
    }

    // RETORNO: El MCD es el último r_i distinto de 0 (r_anterior).
    // Los coeficientes s y t son los correspondientes al MCD.
    *s_final = s_anterior;
    *t_final = t_anterior;
    
    return r_anterior; // MCD
}



int main() {
    int a, n;
    int s_coef, t_coef, mcd;
    int r0_uso, r1_uso;

    printf("--- Algoritmo Extendido de Euclides ---\n");
    printf("Introduce dos enteros positivos (A y N):\n");
    printf("Forma de entrada: A N\n");
    if (scanf("%d %d", &a, &n) != 2 || a <= 0 || n <= 0) {
        printf("Entrada inválida. Ambos números deben ser positivos.\n");
        return 1;
    }

    // La función requiere r0 > r1 para seguir la notación de la tabla.
    if (n > a) {
        r0_uso = n; 
        r1_uso = a; 
    } else {
        r0_uso = a; 
        r1_uso = n;
    }
    
    // Si r1 es 0, no tiene sentido para el algoritmo, pero se maneja si r0=a y r1=0.
    if (r1_uso == 0) {
        printf("El segundo número no puede ser cero.\n");
        return 1;
    }

    // La función main llama a 'algoritmo_euclides_extendido', 
    mcd = algoritmo_euclides_extendido(r0_uso, r1_uso, &s_coef, &t_coef);

    printf("\n======================================\n");
    printf("RESULTADO FINAL:\n");
    printf("MCD(%d, %d) = %d\n", a, n, mcd);
    
    // La ecuación debe expresarse en términos de 'a' y 'n'.
    // Los coeficientes 's' y 't' obtenidos corresponden a r0_uso y r1_uso.
    if (n > a) { // r0_uso=n, r1_uso=a => MCD = s*n + t*a
        // Reordenamos para que 'a' vaya primero:
        printf("RESPUESTA: %d = (%d) * %d + (%d) * %d\n", mcd, t_coef, a, s_coef, n);
    } else { // r0_uso=a, r1_uso=n => MCD = s*a + t*n
        printf("RESPUESTA: %d = (%d) * %d + (%d) * %d\n", mcd, s_coef, a, t_coef, n);
    }
    printf("======================================\n");

    // Cálculo del Inverso Modular
    if (mcd == 1) {
        int inverso_modular;
        int num_a_invertir = a;
        int modulo = n;
        int coeficiente_inverso;

        // El inverso de 'a' es el coeficiente que multiplica a 'a' en la Identidad de Bézout.
        if (n > a) {
            coeficiente_inverso = t_coef; // 'a' está multiplicado por 't'
        } else {
            coeficiente_inverso = s_coef; // 'a' está multiplicado por 's'
        }

        // Ajustar el inverso a un valor positivo en el rango DE 0 a n-1
        inverso_modular = (coeficiente_inverso % modulo + modulo) % modulo;

        printf("\nPara el inverso de %d módulo %d:\n", num_a_invertir, modulo);
        printf("El inverso modular de %d (mod %d) es **%d**.\n", num_a_invertir, modulo, inverso_modular);
        printf("Comprobación: %d * %d mod %d = %d\n", num_a_invertir, inverso_modular, modulo, (long long)num_a_invertir * inverso_modular % modulo);
    } else {
        printf("\nEl inverso modular de %d módulo %d no existe, ya que MCD(%d, %d) != 1.\n", a, n, a, n);
    }

    return 0;
}
