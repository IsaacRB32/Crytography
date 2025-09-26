import ctypes, os
from sympy import factorint
import random

# Cargar la librería C con EEA  #######################333
class Resultado(ctypes.Structure):
    _fields_ = [("gcd", ctypes.c_int),
                ("s", ctypes.c_int),
                ("t", ctypes.c_int)]

dll_path = os.path.join(os.path.dirname(__file__), "eealib.dll")
lib = ctypes.CDLL(dll_path)

lib.eea.argtypes = [ctypes.c_int, ctypes.c_int]
lib.eea.restype = Resultado
###########################################################333

def esMultiplo(numero, divisor):
    return numero % divisor == 0

def zetaEstrella(n):
    if n < 2:
        print("Tienes que introducir un n mayor o igual a 2")
        return []
    
    resultado = []
    factores = list(factorint(n))  
    
    for i in range(1, n):
        es_valido = True
        for primo in factores:
            if esMultiplo(i, primo):
                es_valido = False
                break
        if es_valido:
            resultado.append(i)
    
    return resultado

# def inverso (n,a):
#     zn_estrella = zetaEstrella(n)
#     if a not in zn_estrella: 
#         print(f"{a} no pertenece a Z{n}*")
#         return [] 
#     for b in zn_estrella:
#         calculo = (a*b)%n
#         if calculo == 1:
#             inverso = b
#     return inverso

def inverso(n, a):
    # usamos la libreria en C
    res = lib.eea(a, n)
    if res.gcd != 1:
        print(f"{a} no tiene inverso modulo {n}")
        return None
    return res.s % n  


def generarLLaveRandom (n):
    k =[]
    zn_estrella = zetaEstrella(n)
    zn = []
    for valor in range(1,n):
        zn.append(valor)
    a = random.choice(zn_estrella)
    b = random.choice(zn)

    k.append(a)
    k.append(b)
    
    return k

def generarLLavesDeUnN (n):
    keys =[]
    zn_estrella = zetaEstrella(n)
    zn = []

    nombre_archivo = f"claves_validas_n{n}.txt"
    
    for valor in range(1,n):
        zn.append(valor)

    with open(nombre_archivo, "w", encoding="utf-8") as f:
        
        f.write(f"Z{n}* = {zn_estrella}\n")
        f.write(f"Z{n} = {zn}\n\n")
        f.write("Claves validas (a, b) con a⁻¹ mod n:\n")
        f.write("-" * 40 + "\n")

        for a in zn_estrella:
            inverso_a = inverso(n, a)
            for b in zn:
                clave = (a, b, inverso_a)
                keys.append(clave)
                f.write(f"a={a}, b={b}, a^-1={inverso_a}\n")    
    return keys 

def indiceAlfabeto(letra,alfabeto):
    for indice in range(len(alfabeto)):
        if alfabeto[indice] == letra:
            return indice
    return -1

def affineCipher (mensaje, llave, ascii_printables):
    mensaje_cifrado = []
    for letra in mensaje:
        posicion = indiceAlfabeto(letra,ascii_printables)
        if posicion != -1 :
            c = (llave[0]*posicion+llave[1])%len(ascii_printables)
            mensaje_cifrado.append(ascii_printables[c])
        
    return mensaje_cifrado

def affinDecipher (mesaje_cifrado, llave, ascii_printables):
    mensaje_descifrado = []
    inverso_valor = inverso(len(ascii_printables),llave[0])
    for letra in mesaje_cifrado:
        posicion = indiceAlfabeto(letra,ascii_printables)
        if posicion != -1 :
            m = ((posicion-llave[1])*inverso_valor)%len(ascii_printables)
            mensaje_descifrado.append(ascii_printables[m])
    return mensaje_descifrado



while(True):
    print("\n\t*** Pruebas de la practica 2 ***\n")
    print("1-.Dado el tamaño de un alfabeto n, listar todas las claves válidas para ")
    print("el cifrado afín y el correspondiente a⁻¹ mod n. Guardarlas en un archivo de texto.\n")
    print("2-.Un estudiante del equipo debe generar aleatoriamente una clave válida ")
    print("para el cifrado afín y cifrar un mensaje M (con al menos 50 caracteres).\n")
    print("3-.El otro estudiante debe usar K y C dados y recuperar el mensaje original M.\n")
    print("4-.Salir\n")
    opc = int(input("Ingrese una opcion: "))
    if opc == 1:
        tamanio = int(input("Ingresa un tamanio de alfabeto: "))
        print(generarLLavesDeUnN(tamanio))
    elif opc == 2:
        ascii_printables = [chr(i) for i in range(32, 127)]
        tamanio_alfabeto = len(ascii_printables)
        print(f"Alfaebto ASCII n=95: \n {ascii_printables}\n")
        k_valida_random = generarLLaveRandom(tamanio_alfabeto)
        print(f"**  La llave randon generada es K = {k_valida_random}   **")
        print("\nAhora cifraras un mensaje con esa llave")
        mensaje = input("Mensaje M = ")
        mensaje_cifrado = "".join(affineCipher(mensaje,k_valida_random,ascii_printables))
        print(f"\n**    El mensaje cifrado es C = {mensaje_cifrado} **")
    elif opc == 3:
        ascii_printables = [chr(i) for i in range(32, 127)]
        llave_compartida = []
        print("Recuerda que tu llave es de la forma K = (a,b)")
        a = int(input("Ingresa el valor a de tu llave: "))
        b = int(input("Ingresa el valor b de tu llave: "))
        llave_compartida.append(a)
        llave_compartida.append(b)
        print(f"La llave es K = {llave_compartida}")
        mensaje_cifrado = input("Ingresa el mensaje cifrado C = ")
        mensaje_decifrado = "".join(affinDecipher(mensaje_cifrado,llave_compartida,ascii_printables))
        print(f"\n**    El mensaje es M = {mensaje_decifrado}   **")
    elif opc == 4:
        break
    else:
        print("Opcion no valida")
        

    