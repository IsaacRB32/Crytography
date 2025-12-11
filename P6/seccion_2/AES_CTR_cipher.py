import os
import base64
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes

def cifrar_aes_ctr(key, data):
    iv = os.urandom(16)  
    cipher = Cipher(algorithms.AES(key), modes.CTR(iv))
    encryptor = cipher.encryptor()
    ciphertext = encryptor.update(data) + encryptor.finalize()
    return iv, ciphertext

print("**-- CIFRADO AES en CTR --**")

archivo_llave = input("Ingresa el nombre del archivo que contiene la llave (ejem: llave.txt): ")

with open(archivo_llave, "r") as f:
    key_b64 = f.read().strip()

try:
    key = base64.b64decode(key_b64)
except Exception:
    print("Error: la llave no esta en base64")
    exit()

print(f"\nLlave cargada correctamente ({len(key)*8} bits)\n")

archivo_entrada = input("Ingresa el archivo que deseas cifrar (ejem: mensaje.txt): ")

with open(archivo_entrada, "rb") as f:
    contenido = f.read()

iv, ciphertext = cifrar_aes_ctr(key, contenido)

iv_b64 = base64.b64encode(iv).decode()
cipher_b64 = base64.b64encode(ciphertext).decode()

archivo_salida = input("Ingresa el nombre del archivo para guardar el ciphertext (ej: ciphertext.txt): ")

with open(archivo_salida, "w") as f:
    f.write(cipher_b64)

with open("iv.b64", "w") as f:
    f.write(iv_b64)

print("\nCIFRADO COMPLETO")
print(f"- Ciphertext guardado en: {archivo_salida}")
print("- IV guardado en: iv.b64 (base64)")
print(f"- Tamaño del ciphertext: {len(ciphertext)} bytes cifrados")
