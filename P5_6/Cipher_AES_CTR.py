import os
import base64
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes

def cifrar_aes_ctr(key, data):
    iv = os.urandom(16)

    cipher = Cipher(algorithms.AES(key), modes.CTR(iv))
    encryptor = cipher.encryptor()

    ciphertext = encryptor.update(data) + encryptor.finalize()

    return iv, ciphertext


print("**Cifrado AES en CTR**")
key = os.urandom(32)

archivo = input("Ingresa el nombre del archivo que deseas cifrar: ")

with open(archivo, "rb") as f:
    contenido = f.read()

iv, ciphertext = cifrar_aes_ctr(key, contenido)

cipher_b64 = base64.b64encode(ciphertext).decode()
with open("cipher.txt", "w") as f:
    f.write(cipher_b64)

with open("llave.txt", "w") as f:
    f.write(key.hex())

with open("iv.txt", "w") as f:
    f.write(iv.hex())

print("\nLlave generada (hex):")
print(key.hex())

print("\nIV generado (hex):")
print(iv.hex())

print("\nCiphertext guardado en cipher.txt")
print("Llave guardada en llave.txt")
print("IV guardado en iv.txt")
