import os
import base64

print("**-- Generador de Llave AES --**")

print("Selecciona el tamaño de la llave:")
print("1-. 128 bits")
print("2-. 192 bits")
print("3-. 256 bits")

opcion = input("Ingresa una opción (1-3): ")

if opcion == "1":
    key_size = 16
elif opcion == "2":
    key_size = 24  
elif opcion == "3":
    key_size = 32 
else:
    print("Opcion no valida")
    exit()

nombre_archivo = input("Ingresa el nombre con el que deseas guardar la llave (ejem: llave.txt): ")

key = os.urandom(key_size)

key_b64 = base64.b64encode(key).decode()

with open(nombre_archivo, "w") as f:
    f.write(key_b64)

print("\nLlave generada correctamente.")
print(f"Tamaño: {key_size * 8} bits")
print(f"Archivo creado: {nombre_archivo}")


