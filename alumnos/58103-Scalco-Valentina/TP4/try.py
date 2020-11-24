#! /usr/bin/python
import asyncio
import os
import argparse
import time


# Definicion de los argumentos
parser = argparse.ArgumentParser(description='Tp4 - servidor web asincrono')
parser.add_argument('-d', '--documentroot', default='/home/valenscalco/comp2/lab/alumnos/58103-Scalco-Valentina/TP4/', type=str,
                    help='Directorio donde están los documentos web')
parser.add_argument('-p', '--port', default=5000, help='Puertoen donde espera conexiones')
parser.add_argument('-s', '--size', default=1024, help='Bloque de lectura máximo para los documentos')
parser.add_argument('-b', '--debug', default=False, help='Debug')

args = parser.parse_args()


async def handle(reader, writer):
    data = await reader.read(1024)
    ip, port = writer.get_extra_info('peername')
    encabezado = ""

    try:
        encabezado = data.decode().splitlines()[0]
        archivo = "." + encabezado.split()[1]
        if args.debug:
            asyncio.create_task(debug('handle', archivo))
        if archivo == './':
            archivo = './index.html'
    except:
        archivo = './index.html'

    code = '200 OK'
    task = asyncio.create_task(open_file(archivo, writer, code))
    task1 = asyncio.create_task(logs(ip, port))

    await task
    await task1


async def open_file(archivo, writer, code):
    if args.debug:
        asyncio.create_task(debug('open_file', archivo))
    archivo = args.documentroot + archivo
    size = args.size
    try:
        fd = open(archivo, "rb")
        await escritura(archivo, fd, writer, code, size)
    except FileNotFoundError:
        archivo = args.documentroot + "404Error.html"
        code = "404 Not Found"
        fd = open(archivo, "rb")
        await escritura(archivo, fd, writer, code, size)
    except:
        archivo = args.documentroot + '500error.html'
        code = "500 Internal server error"
        fd = open(archivo, "rb")
        await escritura(archivo, fd, writer, code, size)


async def escritura(archivo, fd, writer, code, size):
    if args.debug:
        req = archivo.lstrip(args.documentroot)
        asyncio.create_task(debug('escritura', req))
    dic = {".txt": " text/plain", ".jpg": " image/jpeg", ".ppm": " image/x-portable-pixmap", ".html": " text/html", ".pdf": " application/pdf"}

    extension = os.path.splitext(archivo)[1]
    header = bytearray("HTTP/1.1 " + code + "\r\nContent-type:" + dic[extension] + "\r\nContent-length:" + str(os.path.getsize(archivo)) + "\r\n\r\n" , "utf8")

    writer.write(header)
    await writer.drain()

    while True:
        data = fd.read(size)
        writer.write(data)
        if len(data) != size:
            break

    await writer.drain()
    writer.close()
    await writer.wait_closed()


async def logs(ip, port):
    now = time.ctime()
    log = f'> client: {ip}:{port}; date:{now}\n'
    with open('logs.txt', 'a') as logs:
        logs.write(log)


async def debug(furName, req):
    now = time.ctime()
    mjs = f'> funtion: {furName}; date:{now}; file:{req}\n'
    with open('debug.txt', 'a') as f:
        f.write(mjs)


async def main():
    port = args.port
    server = await asyncio.start_server(handle, '172.17.0.1', port)
    async with server:
        await server.serve_forever()


if __name__ == "__main__":
    asyncio.run(main())
