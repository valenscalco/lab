#! /usr/bin/python
import sys
import os
import argparse
import array
import threading
import multiprocessing
from time import time

# Definicion de los argumentos
parser = argparse.ArgumentParser(description='Tp2 - procesa ppm')
parser.add_argument('-s', '--size', type=int, default=10,
                    help='Bloque de lectura')
parser.add_argument('-f', '--file', help='Archivo a procesar')
parser.add_argument('-m', '--message', help='mensaje esteganografico')
parser.add_argument('-t', '--offset', default=True,
                    help='Offset en pixels del inicio del raster')
parser.add_argument('-i', '--interleave', default=True,
                    help='Interleave de modificacion en pixel')
parser.add_argument('-o', '--output', default='Steganography.ppm', help='Estego-mensaje')
parser.add_argument('-c', '--cifrado', default=0, help='Cifrado rot13')

args = parser.parse_args()

queuec = multiprocessing.Queue()

try:
    if args.file.find(".ppm") == -1:
        raise UserWarning
except UserWarning:
    print("Error. Archivo no es ppm")
    sys.exit()

try:
    if args.message.find(".txt") == -1:
        raise UserWarning
except UserWarning:
    print("Error. Archivo no es txt")
    sys.exit()

try:
    if args.output.find(".ppm") == -1:
        raise UserWarning
except UserWarning:
    print("Error. El nombre del archivo a crear no tiene la terminación .ppm")
    sys.exit()


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
    dimen = False
    path = os.path.dirname(__file__) + "/"
    try:
        with open(path + args.message, "rb") as archivo_msg:
            message = archivo_msg.read()
    except FileNotFoundError:
        print("El archivo no se encuentra en el directorio")
        sys.exit()
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
    # rot13
    if args.cifrado != 0:
        encabezado_new = encabezado + '#UMCOMPU2-C {} {} {}'.format(args.offset, args.interleave, len(message) + 4)
        verdadera = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
        falsa = "nopqrstuvwxyzabcdefghijklmNOPQRSTUVWXYZABCDEFGHIJKLM"
        transform = dict(zip(verdadera, falsa))
        message = ''.join(transform.get(char, char) for char in str(message))
    else:
        encabezado_new = encabezado + '#UMCOMPU2N {} {} {} '.format(args.offset, args.interleave, (len(message) + 4))
    # print(encabezado_new)
    # saco ancho y largo
    linea = leido.splitlines()
    for i in range(len(linea)):
        if dimen is False:
            word = linea[i].split()
            if len(word) == 2:
                width = int(word[0])
                height = int(word[1])
                dimen = True
                num_bytes = width * height * 3 // 8
    # guardo el cuerpo
    cuerpo = leido[ultima_barra_n:]
    # envio primer parte del cuerpo
    queuec.put(cuerpo)
    h_r = threading.Thread(target=hide_info_r, args=(encabezado_new, queuec, num_bytes, message))
    h_r.start()
    # paso el resto del cuerpo
    while True:
        cuerpo = os.read(archivo, args.size)
        queuec.put(cuerpo)
        if len(cuerpo) != args.size:
            break
    queuec.put("Terminamos")
    h_r.join()
    if os.path.exists('{}'.format(args.output)):
        print("Archivo creado con exito")
    else:
        print("El archivo no fue creado")
    os.close(archivo)
    tiempo = time()
    print("El tiempo de ejecución es: ", time() - tiempo, "segundos")


def hide_info_r(encabezado_new, queuec, num_bytes, message):
    imagec = []
    cuerpo = b''
    k = 0
    start = 0
    if message != " ":
        binario = ''.join(format(ord(x), '08b') for x in str(message))
    else:
        raise TypeError("Mensaje vacío. Por favor ingrese un mensaje")

    # veo si num de bytes mensaje es menor que el de imagen
    if len(message) > num_bytes:
        raise ValueError("Error bytes insuficientes")
    while True:
        mensaje = queuec.get()
        if mensaje == "Terminamos":
            break
        else:
            cuerpo = cuerpo + mensaje
    cuerpo_c = [i for i in cuerpo]
    x = len(binario)
    inicio_r = 0 + (3 * int(args.offset))
    for j in range(0, len(cuerpo_c), int(args.interleave)):
        valor = cuerpo_c[j]
        if start < inicio_r:
            start += 1
            imagec.append(cuerpo_c[j])
        else:
            if x > k:
                bit = binario[k]
                if valor % 2 != int(bit):
                    if valor > 255:
                        valor -= 1
                    else:
                        valor += 1
                k += 1
                imagec.append(valor)
            else:
                imagec.append(cuerpo_c[j])
    h_g = threading.Thread(target=hide_info_g, args=(encabezado_new, imagec, binario))
    h_g.start()
    h_g.join()


def hide_info_g(encabezado_new, imagec, binario):
    k = 0
    start = 0
    x = len(binario)
    inicio_g = 1 + (3 * int(args.offset))
    for j in range(0, len(imagec), int(args.interleave)):
        valor = imagec[j]
        if start < inicio_g:
            start += 1
            imagec.append(imagec[j])
        else:
            if x > k:
                bit = binario[k]
                if valor % 2 != int(bit):
                    if valor > 255:
                        valor -= 1
                    else:
                        valor += 1
                k += 1
                imagec.append(valor)
            else:
                imagec.append(imagec[j])
    h_b = threading.Thread(target=hide_info_b, args=(encabezado_new, imagec, binario))
    h_b.start()
    h_b.join()


def hide_info_b(encabezado_new, imagec, binario):
    k = 0
    start = 0
    x = len(binario)
    inicio_b = 2 + (3 * int(args.offset))
    for j in range(0, len(imagec), int(args.interleave)):
        valor = imagec[j]
        if start < inicio_b:
            start += 1
            imagec.append(imagec[j])
        else:
            if x > k:
                bit = binario[k]
                if valor % 2 != int(bit):
                    if valor > 255:
                        valor -= 1
                    else:
                        valor += 1
                k += 1
                imagec.append(valor)
            else:
                imagec.append(imagec[j])
    image_c = array.array('B', imagec)
    with open('{}'.format(args.output), 'wb') as f:
        f.write(bytearray(encabezado_new, 'ascii'))
        image_c.tofile(f)


if __name__ == "__main__":
    main()
