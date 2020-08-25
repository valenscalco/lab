#! /usr/bin/python
import sys
import os
import argparse
import multiprocessing

# Definicion de los argumentos
parser = argparse.ArgumentParser(description='Tp2 - procesa ppm')
parser.add_argument('-s', '--size', type=int, default=1024,
                    help='Bloque de lectura')
parser.add_argument('-f', '--file', default="Steganography.ppm", help='Archivo a procesar')
parser.add_argument('-t', '--offset', default=0,
                    help='Offset en pixels del inicio del raster')
parser.add_argument('-i', '--interleave', default=1,
                    help='Interleave de modificacion en pixel')

args = parser.parse_args()

queuec = multiprocessing.Queue()


def main():
    # abrir archivo
    path = os.path.dirname(os.path.abspath(__file__))
    size = int(args.size)
    dimen = False
    try:
        archivo = os.open(path + "/" + args.file, os.O_RDONLY)
    except FileNotFoundError:
        print("El archivo no se encuentra en el directorio")
        sys.exit()
    leido = os.read(archivo, size)
    path = os.path.dirname(__file__) + "/"
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
    if args.offset == 0:
        ultima_barra = leido.find(b")", ultima_barra_n) - 1
    else:
        ultima_barra = leido.find(b"(", ultima_barra_n) - 1
    encabezado = leido[:ultima_barra].decode()
    print(encabezado)
    # saco #UMCOMPU2 y L_TOTAL
    linea = encabezado.splitlines()
    for i in range(len(linea)):
        if dimen is False:
            word = linea[i].split()
            if len(word) == 4:
                cifrado = str(word[0])
                L_TOTAL = int(word[3])
                dimen = True
    # guardo el cuerpo
    cuerpo = leido[ultima_barra:]
    # envio primer parte del cuerpo
    queuec.put(cuerpo)
    # creo hijo
    h_c = multiprocessing.Process(target=seek_info, args=(encabezado, queuec, L_TOTAL, cifrado))
    # inicio hijo
    h_c.start()
    # paso el resto del cuerpo
    while True:
        cuerpo = os.read(archivo, args.size)
        queuec.put(cuerpo)
        if len(cuerpo) != args.size:
            break
    queuec.put("Terminamos")
    # uno hijo con el padre
    h_c.join()
    os.close(archivo)


def seek_info(encabezado, queuec, L_TOTAL, cifrado):
    imagec = ''
    cuerpo = b''
    while True:
        mensaje = queuec.get()
        if mensaje == "Terminamos":
            break
        else:
            cuerpo = cuerpo + mensaje
    cuerpo_c = [i for i in cuerpo]
    x = L_TOTAL * 8
    k = 0
    start = 0
    wtf = int(args.offset)
    for j in range(wtf, len(cuerpo_c), int(args.interleave)):
        if start < wtf:
            start += 1
        else:
            valor = ''.join(format(ord(x), '08b') for x in str(cuerpo_c[j]))
            if x > k:
                c = valor[-1:]
                if c == '0':
                    bit = '0'
                else:
                    bit = '1'
                k += 1
                imagec += bit
    message = ''.join(chr(int(imagec[i:i+8], 2)) for i in range(int(args.offset), len(imagec), 8))
    # rot13
    if cifrado == "#UMCOMPU2-C":
        verdadera = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
        falsa = " nopqrstuvwxyzabcdefghijklmNOPQRSTUVWXYZABCDEFGHIJKLM"
        transform = dict(zip(verdadera, falsa))
        message = ''.join(transform.get(char, char) for char in str(message))
    print("El mensaje oculto es:")
    print(message)


if __name__ == "__main__":
    main()
