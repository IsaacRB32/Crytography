# rsa_unwrap.py
def read_private_key(path="private_key.txt"):
    with open(path, "r", encoding="utf-8") as f:
        d = int(f.readline().strip())
        n = int(f.readline().strip())
    return d, n

def read_ciphertext(path="K_enc.txt") -> int:
    with open(path, "r", encoding="utf-8") as f:
        return int(f.readline().strip())

def main():
    d, n = read_private_key("private_key.txt")  # <-- privada de Bob
    C = read_ciphertext("K_enc.txt")

    K = pow(C, d, n)

    # Guarda en el mismo formato que su C (8 hex digits)
    with open("llave_recuperada.txt", "w", encoding="utf-8") as f:
        f.write(f"{K & 0xFFFFFFFF:08X}\n")

    print("OK. Wrote llave_recuperada.txt (recovered K).")

if __name__ == "__main__":
    main()
