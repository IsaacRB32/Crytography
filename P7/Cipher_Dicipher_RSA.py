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


def generar_llaves_64bits():

    e, n, d = generar_llaves(64)

    with open("llaves_RSA_64bits.txt", "w") as f:
        f.write("LLAVE PUBLICA:\n")
        f.write(f"e = {e}\n")
        f.write(f"n = {n}\n\n")

        f.write("LLAVE PRIVADA:\n")
        f.write(f"d = {d}\n")

    print("\nLlave publica y privada se guardaron en 'llaves_RSA_64bits.txt'")
    print(f"e = {e}")
    print(f"n = {n}")
    print(f"d = {d}\n")



def cipher_rsa(e, n):

    r = random.getrandbits(32)
    print(f"\nEl valor de (32 bits) random es r: {r}")

    c = pow(r, e, n)
    print(f"Ciphertext c = {c}")

    with open("ciphertext.txt", "w") as f:
        f.write(str(c))

    print("El ciphertext se guardo en 'ciphertext.txt'\n")

    return r, c


def decipher_rsa(d, n, c):

    m = pow(c, d, n)
    print(f"\nMensaje descifrado M: {m}\n")
    return m



def mostrar_menu():
    print("***--- RSA ---***")
    print("1) Generar llaves (64 bits) y guardar en archivo")
    print("2) Cifrar r (32 bits) con RSA usando (e, n)")
    print("3) Descifrar c con RSA usando (d, n)")
    print("0) Salir")


while True:
    mostrar_menu()
    opcion = input("Selecciona una opcion: ").strip()

    if opcion == "1":
        generar_llaves_64bits()

    elif opcion == "2":
        e = int(input("Ingresa el valor de e: "))
        n = int(input("Ingresa el valor de n: "))
        cipher_rsa(e, n)

    elif opcion == "3":
        d = int(input("Ingresa el valor de d: "))
        n = int(input("Ingresa el valor de n: "))

        nombre_archivo = input("Nombre del archivo (ej. ciphertext.txt): ").strip()
        with open(nombre_archivo, "r") as f:
            c_str = f.read().strip()
            c = int(c_str)
        print(f"Ciphertext leído del archivo: {c}")


        decipher_rsa(d, n, c)

    elif opcion == "0":
        print("Saliendo...")
        break

    else:
        print("Opción no válida. Intenta de nuevo.\n")



