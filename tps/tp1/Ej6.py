lista = input("Ingrese la lista de numeros dividida por comas: \n").split(",")
for i in range(len(lista)): lista[i] = int(lista[i])
lista.sort(reverse=True)
print(lista)