from sympy import randprime
import random
import math

def generar_primo(bits):
    minimo = 2**(bits - 1)
    maximo = 2**bits - 1
    return randprime(minimo, maximo)

def generar_llaves(bits):

    p = generar_primo(bits)
    q = generar_primo(bits)
    
    while q == p:
        q = generar_primo(bits)

    print(f"p = {p}\n")
    print(f"q = {q}\n")

    n = p * q

    phi = (p - 1) * (q - 1)
    print(f"Phi(n) = {phi}\n")

    while True:
        e = random.randrange(2, phi)
        if e not in (3, 65537) and math.gcd(e, phi) == 1:
            break

    print(f"e = {e}\n")

    d = pow(e, -1, phi)
    print(f"d = {d}\n")

    print("Llave publica (e, n):")
    print(f"({e}, {n})\n")

    print("Llave privada (d):")
    print(d)

    return

tamanio = int(input("Ingrese el tamanio: "))
generar_llaves(tamanio)




# El valor de e debe de ser impar, para que tenga posibiliadades para que sea coprimo de phi de n, si no es impar sumar uno y probar de nuevo, en lugar de generar una e nueva aleatoria