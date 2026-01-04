from sympy import randprime
import random
import math

def generar_primo(bits):
    minimo = 2**(bits - 1)
    maximo = 2**bits - 1
    return randprime(minimo, maximo)

def generar_llaves(bits, nombre_pub, nombre_priv):

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
        if e % 2 == 0:
            e += 1
        if e not in (3, 65537) and math.gcd(e, phi) == 1:
            break

    print(f"e = {e}\n")

    d = pow(e, -1, phi)
    print(f"d = {d}\n")

    print("Llave publica (e, n):")
    print(f"({e}, {n})\n")

    print("Llave privada (d, n):")
    print(f"({d}, {n})\n")

    with open(nombre_pub, "w") as f:
        f.write(f"{e}\n{n}\n")

    with open(nombre_priv, "w") as f:
        f.write(f"{d}\n{n}\n")

    print(f"Llave pública guardada en: {nombre_pub}")
    print(f"Llave privada guardada en: {nombre_priv}")

    if n <= 2**32:
        print("\n[ADVERTENCIA]")
        print("El valor de n NO cumple n > 2^32.")
        print("Esto podría violar la condición 1 <= K < n (K es de 32 bits).")
        print("Se recomienda usar bits >= 32 (ej. 64).\n")
    else:
        print("\n[OK]")
        print("n > 2^32, se cumple la condición 1 <= K < n para K de 32 bits.\n")

tamanio = int(input("Ingrese el tamanio en bits (ej. 64, 128, 256): "))

nombre_llave_publica = input("Ingrese el nombre del archivo de la llave pública (e,n): ")
nombre_llave_privada = input("Ingrese el nombre del archivo de la llave privada (d,n): ")

generar_llaves(tamanio, nombre_llave_publica, nombre_llave_privada)
