#include <stdio.h>

int main () {
    printf("--------------------- UNO ----------------\n");
    unsigned char data = 'Y';
    printf("Caracter: %c\n", data);
    printf("Hexadecimal: %x\n", data);
    printf("Decimal: %d\n", data);

    printf("--------------------- DOS ----------------\n");
    data = 'Y';
    for (int i = 0; i < 8; i++){
        data = data << 1;
        printf("Corrimiento izquierda #%d:\n Caracter:%c \n Hexadecimal:%x \n Decimal:%d\n\n", i+1, data, data, data);
    }

    printf("--------------------- TRES ----------------\n");
    data = 'A'; 
    for (int i = 0; i < 8; i++){
        data = data >> 1;
        printf("Corrimiento derecha #%d:\n Caracter:%c \n Hexadecimal:%x \n Decimal:%d\n\n", i+1, data, data, data);
    }

    printf("--------------------- CUATRO ----------------\n");
    unsigned char v1 = 0b1101;   // 13
    unsigned char v2 = 0b1110;   // 14
    unsigned char result;

    result = v1 & v2;

    printf("AND: Hexa: %x Dec: (%d)\n",result, result);

    result = v1 | v2;
    printf("OR: Hexa: %x Dec: (%d)\n",result, result);

    result = v1 ^ v2;
    printf("XOR: Hexa: %x Dec: (%d)\n",result, result);

    printf("--------------------- CINCO ----------------\n");

    unsigned char data2 = 0b10101100;  // 172
    unsigned char mask = 0b10000000; 
    unsigned char result2;

    result2 = data2 & mask;

    printf("data2 en binario: 0b10101100\n");
    printf("Mask en binario: 0b10000000\n");
    printf("Resultado AND= Hex: %x, Dec: %d\n", result2, result2);

    printf("--------------------- SEIS ----------------\n");

    data2 = 0b10101100;  // 172
    mask = 0b00001111;   
    unsigned char result3;

    result3 = data2 & mask;

    printf("data2 en binario: 0b10101100\n");
    printf("Mask en binario: 0b00001111\n");
    printf("Resultado AND= Hex: %x, Dec: %d\n", result3,result3);

    return 0;
}