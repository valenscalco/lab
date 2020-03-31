import random
#Nro ingresado por la computadora.  
n = (random.randrange(10))
print("El numero dado por arumento es: ", n)
#Si se quiere que el nro lo ingrese el usuario, se usa la linea:
# n = int(input("Ingrese un numero \n"))
m = n + (n*11) + (n*111)
print("El resultado de la sumatoria es: ", m)
