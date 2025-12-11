import os

def generar_llave(bits):
    size_bytes = bits // 8
    key = os.urandom(size_bytes)
    return key


print("**Generar llave AES**")

tamanios = [128, 192, 256]

for bits in tamanios:
    key = generar_llave(bits)
    print(f"\nLlave AES-{bits} bits:")
    print(key.hex())
