#!/usr/bin/python
from argparse import ArgumentParser
import os
import multiprocessing


class Proceso():
    def arguments(self):
        parser = ArgumentParser(description='TP1-- procesa ppm')
        parser.add_argument("-r ", "--red", default=1,
                            help="Escala para rojo")
        parser.add_argument("-g ", "--green", default=1,
                            help="Escala para verde")
        parser.add_argument("-b ", "--blue", default=1,
                            help="Escala para azul")
        parser.add_argument("-s ", "--size", default=1024,
                            help="Bloque de lectura")
        parser.add_argument("-f ", "--file", default="",
                            help="Archivo a procesar")
        args = parser.parse_args()
        return args

    def main(self):
        # leer imagen
        args = self.arguments()
        path = os.path.dirname(os.path.abspath(__file__))
        size = int(args.size)
        archivo = os.open(path + "/" + args.file, os.O_RDONLY)
        # Crear archivo azul, rojo, verde
        archivo_r = os.open(path + "/r_" + args.file, os.O_WRONLY)
        archivo_g = os.open(path + "/g_" + args.file, os.O_WRONLY)
        archivo_b = os.open(path + "/b_" + args.file, os.O_WRONLY)
        i = 0
        while True:
            leido = os.read(archivo, size)  # cambiarleidoporimagenoalgoparecid
            cant = len(leido)
            # sacar comentario
            if i == 0:
                for i in range(leido.count(b"\n# ")):
                    barra_n_as = leido.find(b"\n# ")
                    barra_n = leido.find(b"\n", barra_n_as + 1)
                    leido = leido.replace(leido[barra_n_as:barra_n], b"")
                print(leido)
            # sacar encabezado
                primer_n = leido.find(b"\n") + 1
                seg_n = leido.find(b"\n", primer_n) + 1
                ultima_barra_n = leido.find(b"\n", seg_n) + 1
                encabezado = leido[:ultima_barra_n].decode()
                cuerpo_imagen = leido[ultima_barra_n:]
                lista_imagen = [i for i in cuerpo_imagen]
                lista_r = [i for i in cuerpo_imagen]
                lista_g = [i for i in cuerpo_imagen]
                lista_b = [i for i in cuerpo_imagen]
                print(encabezado)
                print(lista_imagen)
            else:
                cuerpo_imagen = leido
            lista_imagen = [i for i in cuerpo_imagen]
            lista_r = [i for i in cuerpo_imagen]
            lista_g = [i for i in cuerpo_imagen]
            lista_b = [i for i in cuerpo_imagen]
            i += 1
            filtro_r = self.intensidad_r(lista_r, args.red)
            print("Filtro rojo")
            print(filtro_r)
            filtro_g = self.intensidad_g(lista_g, args.green)
            print("Filtro verde")
            print(filtro_g)
            filtro_b = self.intensidad_b(lista_b, args.blue)
            print("Filtro blue")
            print(filtro_b)
            if cant != size:
                break
        os.close(archivo)

    def intensidad_r(self, lista, intensidad):
        self.lista = lista
        x = 0
        for i in range(0, len(lista), 3):
            self.lista[i] = int(float(self.lista[i]) * float(intensidad))
            x = i+2
            if self.lista[i] > 255:
                self.lista[i] = 255
            if x-1 < len(lista):
                self.lista[i + 1] = 0
            if x < len(lista):
                self.lista[i + 2] = 0
        return self.lista

    def intensidad_g(self, lista, intensidad):
        self.lista = lista
        x = 0
        for i in range(0, len(lista), 3):
            x = i+2
            if x-1 < len(lista):
                self.lista[i + 1] = int(float(self.lista[i+1]) *
                                        float(intensidad))
                if self.lista[i + 1] > 255:
                    self.lista[i + 1] = 255
            self.lista[i] = 0
            if x < len(lista):
                self.lista[i + 2] = 0
        return self.lista

    def intensidad_b(self, lista, intensidad):
        self.lista = lista
        for i in range(0, len(lista), 3):
            x = i+2
            if x < len(lista):
                self.lista[i + 2] = int(float(self.lista[i + 2]) *
                                        float(intensidad))
                if self.lista[i + 2] > 255:
                    self.lista[i + 2] = 255
            if x-1 < len(lista):
                self.lista[i + 1] = 0
            self.lista[i] = 0
        return self.lista


if __name__ == "__main__":
    pro = Proceso()
    pro.main()
