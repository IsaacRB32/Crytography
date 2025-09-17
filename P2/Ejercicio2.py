from sympy import factorint

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
        return None 
    for b in zn_estrella:
        calculo = (a*b)%n
        if calculo == 1:
            inverso = b
    return inverso

n = int(input("Ingresa un n >= 2: "))
a = int(input(f"Ingresa un a que pertenezca a Z{n}*: "))

inverso_ret = inverso(n,a)
print(f"{a}^-1 = {inverso_ret}")