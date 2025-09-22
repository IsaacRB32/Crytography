#include <stdio.h>
#include <stdlib.h>

#define MAX 10000


// obtenemos el maximo comun divisor

/*int maximo_comun_divisor(int r0, int r1){
    if(r0 < r1){
        printf("El valor de r1 no es mayor que r1, se finaliza.");
        return 0;
        //exit();
    }
    
    int aux; // para no perder el valor de r1
    while(r1 != 0){
        aux = r1;
        r1 = r0 % r1; 
        r0 = r1;
    }
    
    return r0;
}*/


int maximo_comun_divisor_recursivo(int a, int b, int ) {
    int cociente[MAX], residuo[MAX];
    int s[MAX];
    int t[MAX];
    int aux1, aux2;
    int i;
    do{
        if(i == 0){
            residuo[i] = b % a;
            aux = b;
            cociente[i] = b / a;
            s[i]= 
            t[i]= b / a;
        }
         
        
        i++;
    }while(r1 !=0);
    
    return;
}




/*int maximo_comun_divisor_recursivo(int r0, int r1, int i) {
    if (r1 == 0) return r0;
    i++;
    int residuo[];
    residuo[i] = r1 % r0;
    /*if(residuo[i] <-1){
        cociente = r1/r0;
    }else{*/
  /*  cociente = (residuo[i-1] - residuo[i])/ r0;
    //}
    
    
    
    
    
    return maximo_comun_divisor_recursivo(r1, residuo[], i);
}*/



int main(){
    int r1, r0;
    int a;
    scanf("%d %d", &r0, &r1);
    
    a = maximo_comun_divisor_recursivo(r0, r1, 0);
    printf("%d", a);
}

