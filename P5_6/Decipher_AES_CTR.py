import os
import base64
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes

def descifrar_aes_ctr(key, iv, ciphertext):
    cipher = Cipher(algorithms.AES(key), modes.CTR(iv))
    decryptor = cipher.decryptor()
    return decryptor.update(ciphertext) + decryptor.finalize()


print("**Descifrado AES en CTR**")

archivo_llave = input("Ingresa el archivo que contiene la llave (hex): ")
archivo_iv = input("Ingresa el archivo que contiene el IV (hex): ")
archivo_cipher = input("Ingresa el archivo que contiene el ciphertext (base64): ")

for file in [archivo_llave, archivo_iv, archivo_cipher]:
    if not os.path.exists(file):
        print(f"Error: No se encontró el archivo {file}")
        exit()

with open(archivo_llave, "r") as f:
    key_hex = f.read().strip()
key = bytes.fromhex(key_hex)

with open(archivo_iv, "r") as f:
    iv_hex = f.read().strip()
iv = bytes.fromhex(iv_hex)

with open(archivo_cipher, "r") as f:
    cipher_b64 = f.read().strip()
ciphertext = base64.b64decode(cipher_b64)

plaintext = descifrar_aes_ctr(key, iv, ciphertext)

with open("plain.txt", "wb") as f:
    f.write(plaintext)

print("\nEl texto descifrado ha sido guardado en plain.txt")
