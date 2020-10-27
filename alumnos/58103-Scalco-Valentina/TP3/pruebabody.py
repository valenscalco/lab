#! /usr/bin/python
import sys
from os import remove
import os
import argparse
import array
import multiprocessing
import socketserver
from time import time


# Definicion de los argumentos
parser = argparse.ArgumentParser(description='Tp3 - servidor web y filtro de ppm')
parser.add_argument('-d', '--documentroot', default='/home/valenscalco/comp2/lab/alumnos/58103-Scalco-Valentina/TP3/', type=str,
                    help='Directorio donde están los documentos web')
parser.add_argument('-p', '--port', default=5000, help='Puertoen donde espera conexiones')
parser.add_argument('-s', '--size', default=1024, help='Bloque de lectura máximo para los documentos')
parser.add_argument('-c', '--child', default=0, help='Cantidad de hijos para procesar')

args = parser.parse_args()

queuer = multiprocessing.Queue()
queueg = multiprocessing.Queue()
queueb = multiprocessing.Queue()
queuebw = multiprocessing.Queue()


def main(archivo, color, intensidad):
    # abrir archivo
    path = os.path.dirname(os.path.abspath(__file__))
    size = int(args.size)
    try:
        archivo1 = os.open(path + "/" + archivo, os.O_RDONLY)
    except FileNotFoundError:
        print("El archivo no se encuentra en el directorio")
        sys.exit()
    leido = os.read(archivo1, size)
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
    if color == 'red':
        # envio primer parte del cuerpo
        queuer.put(cuerpo)
        # creo hijos
        h_r = multiprocessing.Process(target=cambiar_colores_red, args=(encabezado, queuer, intensidad))
        # inicio los hijos
        h_r.start()
        # paso el resto del cuerpo
        while True:
            cuerpo = os.read(archivo1, int(args.size))
            queuer.put(cuerpo)
            if len(cuerpo) != int(args.size):
                break
        queuer.put("Terminamos")
        # uno al los hijos con el padre
        h_r.join()

    elif color == 'blue':
        # envio primer parte del cuerpo
        queueb.put(cuerpo)
        # creo hijos
        h_b = multiprocessing.Process(target=cambiar_colores_blue, args=(encabezado, queueb, intensidad))
        # inicio los hijos
        h_b.start()
        # paso el resto del cuerpo
        while True:
            cuerpo = os.read(archivo1, int(args.size))
            queueb.put(cuerpo)
            if len(cuerpo) != int(args.size):
                break
        queueb.put("Terminamos")
        # uno al los hijos con el padre
        h_b.join()

    elif color == 'green':
        # envio primer parte del cuerpo
        queueg.put(cuerpo)
        # creo hijos
        h_g = multiprocessing.Process(target=cambiar_colores_green, args=(encabezado, queueg, intensidad))
        # inicio los hijos
        h_g.start()
        # paso el resto del cuerpo
        while True:
            cuerpo = os.read(archivo1, int(args.size))
            queueg.put(cuerpo)
            if len(cuerpo) != int(args.size):
                break
        queueg.put("Terminamos")
        # uno al los hijos con el padre
        h_g.join()

    elif color == 'black&white':
        # envio primer parte del cuerpo
        queuebw.put(cuerpo)
        # creo hijos
        h_bw = multiprocessing.Process(target=cambiar_colores_bw, args=(encabezado, queuebw, intensidad))
        # inicio los hijos
        h_bw.start()
        # paso el resto del cuerpo
        while True:
            cuerpo = os.read(archivo1, int(args.size))
            queuebw.put(cuerpo)
            if len(cuerpo) != int(args.size):
                break
        queuebw.put("Terminamos")
        # uno al los hijos con el padre
        h_bw.join()
    # cierro el archivo
    os.close(archivo1)
    tiempo = time()
    print("El tiempo de ejecución es: ", time() - tiempo, "segundos")


# Estas funciones se encarga de escalar el color de la imagen
def cambiar_colores_red(encabezado, queuer, intensidad):
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
        valor = int(float(cuerpo_c[j]) * float(intensidad))
        if valor > 255:
            valor = 255
        imager.append(valor)
        imager.append(0)
        imager.append(0)
    image_r = array.array('B', imager)
    with open(args.documentroot + 'red.ppm', 'wb') as f:
        f.write(bytearray(encabezado, 'ascii'))
        image_r.tofile(f)


def cambiar_colores_green(encabezado, queueg, intensidad):
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
        valor = int(float(cuerpo_c[j]) * float(intensidad))
        if valor > 255:
            valor = 255
        imageg.append(0)
        imageg.append(valor)
        imageg.append(0)
    image_g = array.array('B', imageg)
    with open(args.documentroot + 'green.ppm', 'wb') as f:
        f.write(bytearray(encabezado, 'ascii'))
        image_g.tofile(f)


def cambiar_colores_blue(encabezado, queueb, intensidad):
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
        valor = int(float(cuerpo_c[j]) * float(intensidad))
        if valor > 255:
            valor = 255
        imageb.append(0)
        imageb.append(0)
        imageb.append(valor)
    image_b = array.array('B', imageb)
    with open(args.documentroot + 'blue.ppm', 'wb') as f:
        f.write(bytearray(encabezado, 'ascii'))
        image_b.tofile(f)


def cambiar_colores_bw(encabezado, queuebw, intensidad):
    imageb = []
    cuerpo = b''
    i = 0
    prom = 0
    while True:
        mensaje = queuebw.get()
        if mensaje == "Terminamos":
            break
        else:
            cuerpo = cuerpo + mensaje
    cuerpo_c = [i for i in cuerpo]
    for j in range(1, len(cuerpo_c), 1):
        valor = int(float(cuerpo_c[j]))
        prom += valor
        i += 1
        if i == 3:
            prom = int((prom//3) * float(intensidad))
            if prom > 255:
                prom = 255
            imageb.append(prom)
            imageb.append(prom)
            imageb.append(prom)
            prom = 0
            i = 0
    image_b = array.array('B', imageb)
    with open(args.documentroot + 'black&white.ppm', 'wb') as f:
        f.write(bytearray(encabezado, 'ascii'))
        image_b.tofile(f)


class Handler(socketserver.BaseRequestHandler):
    def handle(self):
        dic = {"txt": " text/plain", "jpg": " image/jpeg", "ppm": " image/x-portable-pixmap", "html": " text/html", "pdf": " application/pdf"}
        self.data = self.request.recv(1024)
        encabezado = self.data.decode().splitlines()[0]
        archivo = "." + encabezado.split()[1]
        if archivo == './':
            archivo = './index.html'
        extension = archivo.split('.')[2]
        if archivo == './index.html':
            path = args.documentroot
            os.chdir(path)
            fd = os.open(archivo, os.O_RDONLY)
            body = os.read(fd, 50000)
            os.close(fd)
            header = bytearray("HTTP/1.1 404 Not Found\nContent-Type:" + dic[extension] + "\r\nContent-length:"+str(len(body))+"\r\n\r\n",'utf8')
        else:
            extension = archivo.split('.')[2]
            if archivo.find("ppm") != -1:
                extension = 'ppm'
                color = archivo.split("?")[1].split("=")[0]
                intensidad = archivo.split("?")[1].split("=")[1]
                archivo = archivo.split("?")[0]
                main(archivo, color, int(intensidad))
                archivo = args.documentroot + color + '.' + extension
            else:
                archivo = args.documentroot + archivo.split('/')[1]

        fd = os.open(archivo, os.O_RDONLY)
        body = os.read(fd, os.path.getsize(archivo))
        os.close(fd)

        if archivo.find("ppm") != -1:
            remove(args.documentroot + color + '.' + extension)

        header = bytearray("HTTP/1.1 200 OK\r\nContent-type:" + dic[extension] + "\r\nContent-length:" + str(len(body))+"\r\n\r\n", 'utf8')
        self.request.sendall(header)
        self.request.sendall(body)

        if archivo == './404Error.html':
            path = args.documentroot
            os.chdir(path)
            fd = os.open(archivo, os.O_RDONLY)
            body = os.read(fd, 50000)
            os.close(fd)
            header = bytearray("HTTP/1.1 404 Not Found\nContent-Type:" + dic[extension] + "\r\nContent-length:"+str(len(body))+"\r\n\r\n",'utf8')
            self.request.sendall(header)
            self.request.sendall(body)
        if archivo == './500error.html':
            path = args.documentroot
            os.chdir(path)
            fd = os.open(archivo, os.O_RDONLY)
            body = os.read(fd, 50000)
            os.close(fd)
            header = bytearray("HTTP/1.1 500 Internal Server Error\nContent-Type:" + dic[extension] + "\r\nContent-length:"+str(len(body))+"\r\n\r\n",'utf8')
            self.request.sendall(header)
            self.request.sendall(body)


socketserver.TCPServer.allow_reuse_address = True
server = socketserver.TCPServer(("0.0.0.0", int(args.port)), Handler)
server.serve_forever()


if __name__ == "__main__":
    main()
