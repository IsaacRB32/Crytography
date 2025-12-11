from sympy import randprime

def generar_primo(bits):
    minimo = 2**(bits - 1)
    maximo = 2**bits - 1
    return randprime(minimo, maximo)

print("** Numeros primos generados **\n")

bits = [32, 64, 128, 512, 2048]

for b in bits:
    primo = generar_primo(b)
    print(f"Primo de {b} bits:")
    print(primo)
