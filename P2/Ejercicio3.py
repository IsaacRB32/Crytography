from sympy import factorint
import random

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

def inverso (n,a):
    zn_estrella = zetaEstrella(n)
    if a not in zn_estrella: 
        print(f"{a} no pertenece a Z{n}*")
        return [] 
    for b in zn_estrella:
        calculo = (a*b)%n
        if calculo == 1:
            inverso = b
    return inverso

def generarLlave (n):
    k =[]
    zn_estrella = zetaEstrella(n)
    zn = []
    for valor in range(1,n):
        zn.append(valor)
    print(f"Z{n}* = {zn_estrella}")
    print(f"Z{n} = {zn}")
    
    #Vamos a generara la llave de la forma K(a,b)
    #a pertene a Zn* y b pertenece a Zn
    a = random.choice(zn_estrella)
    b = random.choice(zn)

    k.append(a)
    k.append(b)
    
    return k

tamanio = int(input("Ingresa un tamaño de alfabeto: "))

print(f"K = {generarLlave(tamanio)}")