#Para que funcione debe tener descargado matplotlib y seaborn en su computadora
import matplotlib.pyplot as plt
import seaborn as sns

sns.set()

valor = []
print("Ingrese un numero. Al terminar apriete enter")
while True:
     valor1 = input()
     if valor1 != "":
          valor.append(int(valor1))
     else:
          break
valor.sort()
plt.hist(valor, histtype='bar', rwidth=0.95)
plt.xlabel("Valores ingresados")
plt.ylabel("Frecuencia")
plt.title("Histograma de valores ingresados")
plt.show()