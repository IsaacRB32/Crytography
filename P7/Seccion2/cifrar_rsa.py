import random

e = int(input("Ingresa el valor de e: "))
n = int(input("Ingresa el valor de n: "))

r = random.getrandbits(32)
print(f"r generado (32 bits): {r}")

# c) Ciframos usando: c = r^e mod n
c = pow(r, e, n)
print(f"Ciphertext c = {c}")

with open("ciphertext.txt", "w") as f:
    f.write(str(c))

print("El ciphertext se guardó en 'ciphertext.txt'")
