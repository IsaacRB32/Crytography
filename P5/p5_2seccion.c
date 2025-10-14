#include<stdio.h>
void numero_binario (int numero_decimal) {
    int binario[8] = {0};
    int i = 0;

    while (numero_decimal > 0 && i < 8) {
        binario[i] = numero_decimal % 2; 
        numero_decimal = numero_decimal / 2;
        i++;
    }

    for (int j = 7; j >= 0; j--) {
        printf("%d", binario[j]);
    }
    printf("\n");
}

void obtener_nesimo_bit (){

    unsigned char numero;
    
    int n;

    printf("Ingrese un numero (0-255): ");
    scanf("%hhu", &numero);
    printf("Numero ingresado en binario\n");
    numero_binario((int)numero);
    
    printf("Ingrese el numero de bit que desea obtener (0-7): ");
    scanf("%d", &n);

    unsigned char resultado;
    unsigned char mask = 0000001;

    for (int i = 1; i <= n; i++){
        resultado = numero >> i;
    }
    printf("\n El bit en el bit %d es: %d\n",n,(resultado & mask));
}

void activar_nesimo_bit (){
    unsigned char numero;
    unsigned char nueva_mask, mask = 00000001;
    int n;

    printf("Ingrese un numero (0-255): ");
    scanf("%hhu", &numero);
    printf("Numero ingresado en binario\n");
    numero_binario((int)numero);
    
    printf("Ingrese el numero de bit que desea activar (0-7): ");
    scanf("%d", &n);

    nueva_mask = (mask << n);

    printf("Resultado en binario: ");
    numero_binario((int)(nueva_mask | numero));
    printf("\n Resultado en decimal: %d\n",(nueva_mask | numero));
}

void ceros_iniciales (){
    unsigned char numero;
    unsigned char nueva_mask, mask = 00000001;
    int bit;

    printf("Ingrese un numero (0-255): ");
    scanf("%hhu", &numero);
    printf("Numero ingresado en binario\n");
    numero_binario((int)numero);
    int n = 0;
    for (int i = 7; i >= 0; i--){
        bit = (numero >> i)&mask;
        //printf("%d",bit);
        if (bit == 0){
            n++;
        }else{
            break;
        }
    }
    printf("\nHay %d ceros iniciales",n);
}

int main (){
    
    //obtener_nesimo_bit();

    //activar_nesimo_bit();

    ceros_iniciales();
    
    return 0;
}