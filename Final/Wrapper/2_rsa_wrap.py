# rsa_wrap.py
def read_public_key(path="public_key.txt"):
    with open(path, "r", encoding="utf-8") as f:
        e = int(f.readline().strip())
        n = int(f.readline().strip())
    return e, n

def read_K_hex(path="llave.txt") -> int:
    with open(path, "r", encoding="utf-8") as f:
        s = f.readline().strip()
    # acepta "A1B2C3D4" o "0xA1B2..."
    return int(s, 16)

def main():
    e, n = read_public_key("public_key.txt")  # <-- pública de Bob
    K = read_K_hex("llave.txt")               # <-- K de 32 bits (hex)

    if not (1 <= K < n):
        raise SystemExit("Error: K must satisfy 1 <= K < n")

    C = pow(K, e, n)

    with open("K_enc.txt", "w", encoding="utf-8") as f:
        f.write(str(C) + "\n")

    print("OK. Wrote K_enc.txt (RSA ciphertext of K).")

if __name__ == "__main__":
    main()
