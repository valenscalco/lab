import matplotlib.pyplot as plt
import seaborn as sns

sns.set()
valor = []
archivo = open("/home/valenscalco/comp2/lab/tps/tp1/Histograma.txt")
for linea in archivo.readlines(): 
    valor.append(int(linea))
archivo.close()
valor.sort()
plt.hist(valor, histtype='bar', rwidth=0.95)
plt.xlabel("Valores archivados")
plt.ylabel("Frecuencia")
plt.title("Histograma de valores del archivo")
plt.show()