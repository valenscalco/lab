'''
Lo que hace este programa es la Sucesión de Fibonacci.
Este esta dividido en dos partes.
'''

def fibo (n, a=0, b=1):
    while n!=0:
        return fibo (n-1, b, a+b)
    return a
'''
Esta es una funcion recursiva, la cual, repite el bucle mientras que n(siendo el nro de veces que se llamara a ella misma, 
disminuyendo cada vez que se auto llama) sea distinto de cero,
devolviendo a si misma tres argumentos.
a es el numero anterior y b es la suma entre el numero actual y el anterior.
'''

for i in range(0,10):
    print(fibo(i))
'''
En este bucle, llama a la funcion fibo diez veces, enviando el termino que se quiere calcular.
Para asi saber los primeros  terminos de la Sucesión de Fibonacci. Luego los va imprimiendo a
medida que le vayan devolviendo cada valor.
'''


