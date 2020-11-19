#! /usr/bin/python
import sys
from os import remove
import os
import argparse
import array
import multiprocessing
import socketserver
import time


# Definicion de los argumentos
parser = argparse.ArgumentParser(description='Tp3 - servidor web y filtro de ppm')
parser.add_argument('-d', '--documentroot', default='/home/valenscalco/comp2/lab/alumnos/58103-Scalco-Valentina/TP3/', type=str,
                    help='Directorio donde están los documentos web')
parser.add_argument('-p', '--port', default=5000, help='Puertoen donde espera conexiones')
parser.add_argument('-s', '--size', default=1024, help='Bloque de lectura máximo para los documentos')
parser.add_argument('-c', '--child', default=1, help='Cantidad de hijos para procesar')

args = parser.parse_args()

queuec = multiprocessing.Queue()


def main(archivo, color, intensidad):
    # abrir archivo
    path = os.path.dirname(os.path.abspath(__file__))
    size = int(args.size)
    try:
        archivo1 = os.open(path + "/" + archivo, os.O_RDONLY)
        t = os.path.getsize(archivo1)
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
    # envio primer parte del cuerpo
    queuec.put(cuerpo)
    h_c = []
    lock = multiprocessing.Lock()
    # kep = []
    for i in range(int(args.child)):
        h_c.append(multiprocessing.Process(target=cambiar_colores, args=(encabezado, queuec, intensidad, color, lock)))
        h_c[i].start()
    while True:
        # paso el resto del cuerpo
        cuerpo = os.read(archivo1, int(args.size))
        queuec.put(cuerpo)
        if len(cuerpo) != int(args.size):
            break
    for i in range(int(args.child)):
        queuec.put("Terminamos")
    for i in range(len(h_c)):
        print(h_c[i])
        h_c[i].join()
        print(h_c[i])
    # cierro el archivo
    os.close(archivo1)
    tiempo = time.time()
    print("El tiempo de ejecución es: ", time.time() - tiempo, "segundos")


# Estas funciones se encarga de escalar el color de la imagen
def cambiar_colores(encabezado, queuec, intensidad, color, lock):
    imagec = []
    cuerpo = b''
    prom = 0
    i = 0
    lock.acquire()
    while True:
        mensaje = queuec.get()
        if mensaje == "Terminamos":
            break
        else:
            cuerpo = cuerpo + mensaje
    cuerpo_c = [i for i in cuerpo]
    if color == 'red':
        for j in range(0, len(cuerpo_c), 3):
            valor = int(float(cuerpo_c[j]) * float(intensidad))
            if valor > 255:
                valor = 255
            imagec.append(valor)
            imagec.append(0)
            imagec.append(0)
    elif color == 'green':
        for j in range(1, len(cuerpo_c), 3):
            valor = int(float(cuerpo_c[j]) * float(intensidad))
            if valor > 255:
                valor = 255
            imagec.append(0)
            imagec.append(valor)
            imagec.append(0)
    elif color == 'blue':
        for j in range(2, len(cuerpo_c), 3):
            valor = int(float(cuerpo_c[j]) * float(intensidad))
            if valor > 255:
                valor = 255
            imagec.append(0)
            imagec.append(0)
            imagec.append(valor)
    elif color == 'black&white':
        for j in range(1, len(cuerpo_c), 1):
            valor = int(float(cuerpo_c[j]))
            prom += valor
            i += 1
            if i == 3:
                prom = int((prom//3) * float(intensidad))
                if prom > 255:
                    prom = 255
                imagec.append(prom)
                imagec.append(prom)
                imagec.append(prom)
                prom = 0
                i = 0
    lock.release()
    image_r = array.array('B', imagec)
    with open(args.documentroot + color + '.ppm', 'wb') as f:
        f.write(bytearray(encabezado, 'ascii'))
        image_r.tofile(f)


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
