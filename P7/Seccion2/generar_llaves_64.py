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

    n = p * q
    phi = (p - 1) * (q - 1)

    while True:
        e = random.randrange(2, phi)
        if e not in (3, 65537) and math.gcd(e, phi) == 1:
            break

    d = pow(e, -1, phi)

    return e, n, d


e, n, d = generar_llaves(64)

with open("llaves_RSA_64bits.txt", "w") as f:
    f.write("LLAVE PUBLICA:\n")
    f.write(f"e = {e}\n")
    f.write(f"n = {n}\n\n")

    f.write("LLAVE PRIVADA:\n")
    f.write(f"d = {d}\n")

print("Llave pública y privada guardadas en llaves_RSA_64bits.txt")
