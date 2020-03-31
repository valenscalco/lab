nro = int(input("Ingrese un numero \n"))
mul = int(input("Ingrese el numero de cantidad de multiplicacion \n"))
cant1 = ""
su = 0
for i in range (mul):
    cant1 += "1"
    su += int(cant1)*nro
print ("La suma total es: ", su)