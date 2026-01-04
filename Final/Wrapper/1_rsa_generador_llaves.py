# generador_llaves_rsa.py
import secrets
import math

#  funciones matemáticas
def mcd_extendido(a: int, b: int):
    if b == 0:
        return a, 1, 0
    mcd, x1, y1 = mcd_extendido(b, a % b)
    return mcd, y1, x1 - (a // b) * y1

def inverso_modular(a: int, m: int) -> int:
    mcd, x, _ = mcd_extendido(a, m)
    if mcd != 1:
        raise ValueError("No existe inverso modular")
    return x % m

#  primalidad
def es_primo_probable(n: int, rondas: int = 40) -> bool:
    if n < 2:
        return False
    primos_pequenos = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37]
    for p in primos_pequenos:
        if n == p:
            return True
        if n % p == 0:
            return False

    # escribir n-1 = d * 2^s
    d = n - 1
    s = 0
    while d % 2 == 0:
        d //= 2
        s += 1

    for _ in range(rondas):
        a = secrets.randbelow(n - 3) + 2  # [2, n-2]
        x = pow(a, d, n)
        if x == 1 or x == n - 1:
            continue
        testigo = True
        for _r in range(s - 1):
            x = (x * x) % n
            if x == n - 1:
                testigo = False
                break
        if testigo:
            return False
    return True

def generar_primo(bits: int) -> int:
    while True:
        x = secrets.randbits(bits)
        x |= (1 << (bits - 1))  # asegurar longitud de bits
        x |= 1                  # asegurar impar
        if es_primo_probable(x):
            return x

# generación de llaves RSA 
def generar_llaves_rsa(bits: int = 1024, e: int = 65537):
    if bits < 512:
        raise ValueError("Use al menos 512 bits para seguridad de demostración.")
    p = generar_primo(bits // 2)
    q = generar_primo(bits // 2)
    while q == p:
        q = generar_primo(bits // 2)

    n = p * q
    phi = (p - 1) * (q - 1)

    if math.gcd(e, phi) != 1:
        # respaldo: encontrar e impar pequeño
        e = 3
        while math.gcd(e, phi) != 1:
            e += 2

    d = inverso_modular(e, phi)
    return (e, n), (d, n)

def escribir_archivos_llaves(publica, privada, ruta_publica="public_key.txt", ruta_privada="private_key.txt"):
    e, n = publica
    d, n2 = privada
    assert n == n2
    with open(ruta_publica, "w", encoding="utf-8") as f:
        f.write(f"{e}\n{n}\n")
    with open(ruta_privada, "w", encoding="utf-8") as f:
        f.write(f"{d}\n{n}\n")

def main():
    publica, privada = generar_llaves_rsa(bits=1024)
    escribir_archivos_llaves(publica, privada)
    print("OK. Generadas:")
    print(" - public_key.txt  (e, n)")
    print(" - private_key.txt (d, n)")

if __name__ == "__main__":
    main()
