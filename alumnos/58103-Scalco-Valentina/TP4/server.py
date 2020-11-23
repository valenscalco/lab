#! /usr/bin/python
import sys
import asyncio as asy
import os
import argparse
import socketserver


# Definicion de los argumentos
parser = argparse.ArgumentParser(description='Tp3 - servidor web y filtro de ppm')
parser.add_argument('-d', '--documentroot', default='/home/valenscalco/comp2/lab/alumnos/58103-Scalco-Valentina/TP4/', type=str,
                    help='Directorio donde están los documentos web')
parser.add_argument('-p', '--port', default=5000, help='Puertoen donde espera conexiones')
parser.add_argument('-s', '--size', default=1024, help='Bloque de lectura máximo para los documentos')
parser.add_argument('-c', '--child', default=0, help='Cantidad de hijos para procesar')

args = parser.parse_args()


class Handler(socketserver.BaseRequestHandler):
    async def handle(self):
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
            fd = await os.open(archivo, os.O_RDONLY)
            body = os.read(fd, 50000)
            os.close(fd)
            header = bytearray("HTTP/1.1 404 Not Found\nContent-Type:" + dic[extension] + "\r\nContent-length:"+str(len(body))+"\r\n\r\n",'utf8')
        else:
            extension = archivo.split('.')[2]
            archivo = args.documentroot + archivo.split('/')[1]

        fd = os.open(archivo, os.O_RDONLY)
        body = os.read(fd, os.path.getsize(archivo))
        await os.close(fd)

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
    Handler()
