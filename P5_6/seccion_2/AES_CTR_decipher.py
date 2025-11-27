import os
import base64
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes

def descifrar_aes_ctr(key, iv, ciphertext):
    cipher = Cipher(algorithms.AES(key), modes.CTR(iv))
    decryptor = cipher.decryptor()
    plaintext = decryptor.update(ciphertext) + decryptor.finalize()
    return plaintext


print("**-- DESCIFRADO AES en CTR --**")

archivo_llave = input("Ingresa el archivo que contiene la llave (ejem: llave.txt): ")

with open(archivo_llave, "r") as f:
    key_b64 = f.read().strip()

try:
    key = base64.b64decode(key_b64)
except Exception:
    print("Error: la llave no esta en base64.")
    exit()

archivo_iv = input("Ingresa el archivo que contiene el IV (ejem: iv.b64): ")

with open(archivo_iv, "r") as f:
    iv_b64 = f.read().strip()

try:
    iv = base64.b64decode(iv_b64)
except Exception:
    print("Error: el IV no esta en base64")
    exit()

archivo_cipher = input("Ingresa el archivo que contiene el ciphertext (ejem: chiper.txt): ")

with open(archivo_cipher, "r") as f:
    cipher_b64 = f.read().strip()

try:
    ciphertext = base64.b64decode(cipher_b64)
except Exception:
    print("Error: el ciphertext no esta en base64")
    exit()


archivo_salida = input("Ingresa el nombre del archivo donde guardar el texto plano recuperado (ejem: plain.txt): ")

plaintext = descifrar_aes_ctr(key, iv, ciphertext)

with open(archivo_salida, "wb") as f:
    f.write(plaintext)

print("\nDESCIFRADO COMPLETO")
print(f"Texto plano recuperado guardado en: {archivo_salida}")
