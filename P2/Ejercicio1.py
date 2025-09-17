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

print("Calculadora de Zn*")

n = int(input("Ingresa un numero: "))
result = zetaEstrella(n)
print(f"Z{n}* = {result}")
