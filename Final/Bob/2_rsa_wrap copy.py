
pub_path = input("Archivo de llave pública destino (e,n): ")
k_path   = input("Archivo con K en hex: ")
out_path = input("Archivo de salida (K cifrada): ")

with open(pub_path, "r") as f:
    e = int(f.readline().strip())
    n = int(f.readline().strip())

with open(k_path, "r") as f:
    K = int(f.readline().strip(), 16)

C = pow(K, e, n)

with open(out_path, "w") as f:
    f.write(str(C) + "\n")

print("\nK cifrada con RSA")
print("C =", C)
print("Archivo generado:", out_path)
