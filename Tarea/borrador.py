import time
import platform

def find_x (base, modulo, objetivo):
    inicio = time.time()

    iter_x = 1

    valor = base % modulo

    while True :
        if (valor == objetivo):
            fin = time.time()
            return iter_x, fin-inicio

        iter_x += 1
        
        valor = (valor*base)%modulo


casos = {
    "a": (3, 641, 285),
    "b": (2, 24499, 2697),
    "c": (5, 3558889333, 2199600647),
    "d": (2, 925524359093, 107922727226),
    "e": (3, 500000009, 187776257),
    "f": (2, 12575817766556298347, 5508961339840704716),
    "g": (3, 113750260501994812111267656933598813423,
              97139203429660076870914437708269649628),
}


while True:
    print("\nSeleccione una ecuación:\n")
    print("a) 3^x mod 641 = 285")
    print("b) 2^x mod 24499 = 2697")
    print("c) 5^x mod 3558889333 = 2199600647")
    print("d) 2^x mod 925524359093 = 107922727226")
    print("e) 3^x mod 500000009 = 187776257")
    print("f) 2^x mod 12575817766556298347 = 5508961339840704716")
    print("g) 3^x mod 113750260501994812111267656933598813423 = 97139203429660076870914437708269649628")
    print("Salir (cualquier otra letra)")

    opc = input("\nEscribe la letra (ejem: a): ").lower()

    if opc not in casos:
        print("\nSaliendo")
        break

    base, mod, objetivo = casos[opc]

    print(f"\nResolviendo ejercicio {opc}:")
    print(f"{base}^x mod {mod} = {objetivo}\n")

    try:
        x, t = find_x(base, mod, objetivo)
        print(f"Solucion encontrada: x = {x}")
        print(f"Tiempo: {t:.6f} segundos")
    except KeyboardInterrupt:
        print("\nBusqueda interrumpida")