#!/usr/bin/python3
import socketserver
import os
from os import remove
from body import main
import argparse as args


class Handler(socketserver.BaseRequestHandler):
    def handle(self):
        dic = {"txt": " text/plain", "jpg": " image/jpeg", "ppm": " image/x-portable-pixmap", "html": " text/html", "pdf": " application/pdf"}
        self.data = self.request.recv(1024)
        encabezado = self.data.decode().splitlines()[0]
        archivo = "." + encabezado.split()[1]
        if archivo == './':
            archivo = './index.html'
        extension = archivo.split('.')[2]
        '''print(self.client_address)
        print(self.data)'''
        if archivo == './index.html':
            path = '/home/valenscalco/server/'
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

                image = (archivo, color, str(intensidad)).main()
                image1 = open('/home/valenscalco/server/temp.ppm', "wb")
                image1.write(image)
                image1.close

                archivo = '/home/valenscalco/server/temp.ppm'
            else:
                archivo = '/home/valenscalco/server/' + archivo.split('/')[1]

        fd = os.open(archivo, os.O_RDONLY)
        body = os.read(fd, os.path.getsize(archivo))
        os.close(fd)

        if archivo.find("ppm") != -1:
            remove('/home/valenscalco/server/temp.ppm')

        header = bytearray("HTTP/1.1 200 OK\r\nContent-type:" + dic[extension] + "\r\nContent-length:" + str(len(body))+"\r\n\r\n", 'utf8')
        self.request.sendall(header)
        self.request.sendall(body)

        if archivo == './404Error.html':
            path = '/home/valenscalco/server/'
            os.chdir(path)
            fd = os.open(archivo, os.O_RDONLY)
            body = os.read(fd, 50000)
            os.close(fd)
            header = bytearray("HTTP/1.1 404 Not Found\nContent-Type:" + dic[extension] + "\r\nContent-length:"+str(len(body))+"\r\n\r\n",'utf8')
            self.request.sendall(header)
            self.request.sendall(body)
        '''if os.path.isfile(archivo) is False:  # si no esta el archivo
            archivo = './404Error.html'
        fd = os.open(archivo, os.O_RDONLY)
        body = os.read(fd, 50000)'''


socketserver.TCPServer.allow_reuse_address = True
server = socketserver.TCPServer(("0.0.0.0", 5000), Handler)
server.serve_forever()
