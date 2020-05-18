#! /usr/bin/python
import sys
import os
import argparse
import multiprocessing
import array

# Definicion de los argumentos
parser = argparse.ArgumentParser(description='Tp1 - procesa ppm')
parser.add_argument('-r', '--red', type=float, default=1,
                    help='Escala para rojo')
parser.add_argument('-g', '--green', type=float, default=1,
                    help='Escala para verde')
parser.add_argument('-b', '--blue', type=float, default=1,
                    help='Escala para azul')
parser.add_argument('-s', '--size', type=int, default=10,
                    help='Bloque de lectura')
parser.add_argument('-f', '--file', help='Archivo a procesar')
args = parser.parse_args()

try:
    if args.red < 0 or args.green < 0 or args.blue < 0 or args.size <= 0:
        raise ValueError
except ValueError:
    print("Error. Los valores negativos no son válidos")
    sys.exit()

try:
    if args.file.find(".ppm") == -1:
        raise UserWarning
except UserWarning:
    print("Error. Archivo no es PPM")
    sys.exit()


queuer = multiprocessing.Queue()
queueg = multiprocessing.Queue()
queueb = multiprocessing.Queue()


def main():
    # abrir archivo
    path = os.path.dirname(os.path.abspath(__file__))
    size = int(args.size)
    try:
        archivo = os.open(path + "/" + args.file, os.O_RDONLY)
    except FileNotFoundError:
        print("El archivo no se encuentra en el directorio")
        sys.exit()
    leido = os.read(archivo, size)
    # sacar comentario
    i = 0
    if i == 0:
        for i in range(leido.count(b"\n# ")):
            barra_n_as = leido.find(b"\n# ")
            barra_n = leido.find(b"\n", barra_n_as + 1)
            leido = leido.replace(leido[barra_n_as:barra_n], b"")
    # sacar encabezado
    primer_n = leido.find(b"\n") + 1
    seg_n = leido.find(b"\n", primer_n) + 1
    ultima_barra_n = leido.find(b"\n", seg_n) + 1
    encabezado = leido[:ultima_barra_n].decode()
    # guardo el cuerpo
    cuerpo = leido[ultima_barra_n:]
    # envio primer parte del cuerpo
    queuer.put(cuerpo)
    queueg.put(cuerpo)
    queueb.put(cuerpo)
    # creo hijos
    h_r = multiprocessing.Process(target=cambiar_colores_red, args=(encabezado, queuer))
    h_g = multiprocessing.Process(target=cambiar_colores_green, args=(encabezado, queueg))
    h_b = multiprocessing.Process(target=cambiar_colores_blue, args=(encabezado, queueb))
    # inicio los hijos
    h_r.start()
    h_g.start()
    h_b.start()
    # paso el resto del cuerpo
    while True:
        cuerpo = os.read(archivo, args.size)
        queuer.put(cuerpo)
        queueg.put(cuerpo)
        queueb.put(cuerpo)
        if len(cuerpo) != args.size:
            break
    queuer.put("Terminamos")
    queueg.put("Terminamos")
    queueb.put("Terminamos")
    # uno al los hijos con el padre
    h_r.join()
    h_g.join()
    h_b.join()

    if os.path.exists('red.ppm') and os.path.exists('green.ppm') and os.path.exists('blue.ppm'):
        print("Archivos creados con exito")
    else:
        print("Uno o mas archivos no fueron creados")
    # cierro el archivo
    os.close(archivo)


# Estas funciones se encarga de escalar el color de la imagen
def cambiar_colores_red(encabezado, queuer):
    imager = []
    cuerpo = b''
    while True:
        mensaje = queuer.get()
        if mensaje == "Terminamos":
            break
        else:
            cuerpo = cuerpo + mensaje
    cuerpo_c = [i for i in cuerpo]
    for j in range(0, len(cuerpo_c), 3):
        valor = int(float(cuerpo_c[j]) * float(args.red))
        if valor > 255:
            valor = 255
        imager.append(valor)
        imager.append(0)
        imager.append(0)
    image_r = array.array('B', imager)
    with open('red.ppm', 'wb') as f:
        f.write(bytearray(encabezado, 'ascii'))
        image_r.tofile(f)


def cambiar_colores_green(encabezado, queueg):
    imageg = []
    cuerpo = b''
    while True:
        mensaje = queueg.get()
        if mensaje == "Terminamos":
            break
        else:
            cuerpo = cuerpo + mensaje
    cuerpo_c = [i for i in cuerpo]
    for j in range(1, len(cuerpo_c), 3):
        valor = int(float(cuerpo_c[j]) * float(args.green))
        if valor > 255:
            valor = 255
        imageg.append(0)
        imageg.append(valor)
        imageg.append(0)
    image_g = array.array('B', imageg)
    with open('green.ppm', 'wb') as f:
        f.write(bytearray(encabezado, 'ascii'))
        image_g.tofile(f)


def cambiar_colores_blue(encabezado, queueb):
    imageb = []
    cuerpo = b''
    while True:
        mensaje = queueb.get()
        if mensaje == "Terminamos":
            break
        else:
            cuerpo = cuerpo + mensaje
    cuerpo_c = [i for i in cuerpo]
    for j in range(2, len(cuerpo_c), 3):
        valor = int(float(cuerpo_c[j]) * float(args.blue))
        if valor > 255:
            valor = 255
        imageb.append(0)
        imageb.append(0)
        imageb.append(valor)
    image_b = array.array('B', imageb)
    with open('blue.ppm', 'wb') as f:
        f.write(bytearray(encabezado, 'ascii'))
        image_b.tofile(f)


if __name__ == "__main__":
    main()
