
d = int(input("Ingresa el valor de d: "))
n = int(input("Ingresa el valor de n: "))

#c = int(input("Ingresa el valor del ciphertext c: "))
archivo = input("Ingresa el nombre del archivo (ej. ciphertext.txt): ")
with open(archivo, "r") as f:
    c = int(f.read().strip())
print(f"Ciphertext leido del archivo: {c}")

# c) Desciframos: m = c^d mod n
m = pow(c, d, n)

print(f"Mensaje descifrado (m): {m}")
