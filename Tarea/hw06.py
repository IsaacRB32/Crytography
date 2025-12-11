# import time
# import platform

# def log_discreto_fuerza_bruta(base, modulo, objetivo, max_iter=None):
#     """
#     Calcula el logaritmo discreto de 'objetivo' en base 'base' módulo 'modulo'
#     usando fuerza bruta.

#     Busca el menor x >= 1 tal que:
#         base**x ≡ objetivo (mod modulo)

#     Parámetros:
#         base    : base de la potencia
#         modulo  : módulo
#         objetivo: valor al que queremos llegar
#         max_iter: límite opcional de iteraciones (None = sin límite)

#     Regresa:
#         (x, tiempo) si lo encontró
#         (None, tiempo) si no lo encontró antes de max_iter
#     """
#     inicio = time.time()

#     x = 1
#     valor = base % modulo  # base^1 mod modulo

#     while True:
#         if valor == objetivo % modulo:
#             fin = time.time()
#             return x, fin - inicio

#         x += 1
#         if max_iter is not None and x > max_iter:
#             fin = time.time()
#             return None, fin - inicio

#         # Valor siguiente: base^x = base * base^(x-1)
#         valor = (valor * base) % modulo


# def main():
#     print("=== Tarea 6: Logaritmo discreto por fuerza bruta ===\n")

#     # Información básica de la máquina (el resto lo describes tú en el reporte)
#     print("Información de la máquina donde se ejecuta el programa:")
#     print("  Sistema operativo:", platform.system(), platform.release())
#     print("  Procesador:", platform.processor())
#     print()

#     # Cada tupla: (etiqueta, base, modulo, objetivo, max_iter)
#     # OJO: los números grandes van SIN comas.
#     casos = [
#         ("a", 3, 641, 285, None),
#         ("b", 2, 24499, 2697, None),
#         ("c", 5, 3558889333, 2199600647, None),
#         ("d", 2, 925524359093, 10792277226, None),
#         # Para los grandes pongo un límite de iteraciones para
#         # que puedas ver que no alcanza; puedes subirlos si quieres.
#         ("e", 3, 500000009, 187776257, 50_000_000),           # hasta 50 millones
#         ("f", 2, 125575187655652982347, 5508961339840704716, 1_000_000),
#         ("g", 3, 1137502605019948121127675639359813423,
#               97139203429660076870914437702869646928, 1_000_000),
#     ]

#     for etiqueta, base, modulo, objetivo, limite in casos:
#         print(f"Ejercicio {etiqueta}) {base}^x ≡ {objetivo} (mod {modulo})")
#         print("  (Ctrl+C para interrumpir manualmente si tarda demasiado)")
#         try:
#             x, t = log_discreto_fuerza_bruta(base, modulo, objetivo, max_iter=limite)
#         except KeyboardInterrupt:
#             print("  Búsqueda interrumpida por el usuario.\n")
#             continue

#         if x is None:
#             print(f"  No se encontró x en el rango 1..{limite:,}.")
#             print(f"  Tiempo transcurrido: {t:.2f} segundos\n")
#         else:
#             print(f"  Solución: x = {x}")
#             print(f"  Verificación: pow({base}, {x}, {modulo}) = {pow(base, x, modulo)}")
#             print(f"  Tiempo: {t:.4f} segundos\n")


# if __name__ == "__main__":
#     main()


import time
import platform

def find_x(base, modulo, objetivo):
    inicio = time.time()

    iter_x = 1
    valor = base % modulo  # base^1 mod modulo

    while True:
        if valor == objetivo % modulo:
            fin = time.time()
            return iter_x, fin - inicio

        iter_x += 1
        valor = (valor * base) % modulo


# Lista de casos (índice igual a letra)
casos = {
    "a": ("a", 3, 641, 285),
    "b": ("b", 2, 24499, 2697),
    "c": ("c", 5, 3558889333, 2199600647),
    "d": ("d", 2, 925524359093, 10792277226),
    "e": ("e", 3, 500000009, 187776257),
    "f": ("f", 2, 125575187655652982347, 5508961339840704716),
    "g": ("g", 3, 1137502605019948121127675639359813423,
               97139203429660076870914437702869646928)
}


while True:
    print("\nSeleccione una ecuación:\n")
    print("a) 3^x mod 641 = 285")
    print("b) 2^x mod 24499 = 2697")
    print("c) 5^x mod 3558889333 = 2199600647")
    print("d) 2^x mod 925524359093 = 10792277226")
    print("e) 3^x mod 500000009 = 187776257")
    print("f) 2^x mod 125575187655652982347 = 5508961339840704716")
    print("g) 3^x mod (N grande) = (valor enorme)")
    print("Salir (cualquier otra letra)")

    opc = input("\nEscribe la letra (ejem: a): ").lower()

    if opc not in casos:
        print("\nSaliendo del programa...")
        break

    etiqueta, base, mod, objetivo = casos[opc]

    print(f"\nResolviendo ejercicio {etiqueta}:")
    print(f"{base}^x mod {mod} = {objetivo}\n")

    try:
        x, t = find_x(base, mod, objetivo)
        print(f"✔ Solución encontrada: x = {x}")
        print(f"⏱ Tiempo: {t:.6f} segundos")
    except KeyboardInterrupt:
        print("\n⛔ Búsqueda interrumpida por el usuario (CTRL+C)")

