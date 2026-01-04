
priv_path = input("Archivo de llave privada (d,n): ")
ct_path   = input("Archivo con K cifrada (K_wrap.txt): ")
out_path  = input("Archivo de salida (K recuperada): ")

with open(priv_path, "r") as f:
    d = int(f.readline().strip())
    n = int(f.readline().strip())

with open(ct_path, "r") as f:
    C = int(f.readline().strip())

K = pow(C, d, n)

with open(out_path, "w") as f:
    f.write(f"{K & 0xFFFFFFFF:08X}\n")

print("\nK recuperada con RSA")
print("K =", hex(K))
print("Archivo generado:", out_path)
