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
    #print(f"Z{n}* = {zn_estrella}")
    #print(f"Z{n} = {zn}")
    
    #Vamos a generara la llave de la forma K(a,b)
    #a pertene a Zn* y b pertenece a Zn
    a = random.choice(zn_estrella)
    b = random.choice(zn)

    k.append(a)
    k.append(b)
    
    return k

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

##  Esto es el main ##

ascii_printables = [chr(i) for i in range(32, 127)]
tamanio_alfabeto = len(ascii_printables)
print(ascii_printables)

mensaje = input("Escribe un mensaje: ")
llave = generarLlave(tamanio_alfabeto)
print(f"Tu llave aleatoria es K = {llave}")

mensaje_cifrado = "".join(affineCipher(mensaje, llave, ascii_printables))
mensaje_descifrado = "".join(affinDecipher(mensaje_cifrado,llave,ascii_printables))

print(f"Tu mensaje cifrado es: {mensaje_cifrado}")
print(f"Tu mensaje decifrado es: {mensaje_descifrado}")
