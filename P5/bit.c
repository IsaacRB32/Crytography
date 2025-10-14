#include <stdio.h>
#include <stdlib.h>

int main() {
    unsigned int num;
    printf("Introduce un número hexadecimal (por ejemplo 0x1A3 o 1A3): ");
    scanf("%x", &num); // %x lee hexadecimal directamente


    for (int i = sizeof(num) * 8 - 1; i >= 0; i--) {
        putchar((num & (1 << i)) ? '1' : '0');
    }

    return 0;
}
