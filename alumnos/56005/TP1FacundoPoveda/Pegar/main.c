#include "pegar.h"
	
int main (int argc, char ** argv){
	int part1;
	int part2;
	int part3;
	int archivo;
	char buffer;

	//Abrimos las 3 partes con permiso solo de lectura
	part1 = open("Parte1", O_RDONLY , NULL);
	part2 = open("Parte2", O_RDONLY , NULL);
        part3 = open("Parte3", O_RDONLY , NULL);
	
	//Creamos un archivo nuevo con permisos de lectura/escritura
	archivo = open("Archivo", O_RDWR | O_CREAT | O_APPEND, 0644);
	//Mientras que podamos leer la parte1 de a 1 byte
	while(read(part1,&buffer,1)>0){
	//Escribimos en el archivo lo que tenemos en el buffer de a un byte
	write(archivo,&buffer,1);
	}
        while(read(part2,&buffer,1)>0){
        write(archivo,&buffer,1);
        }
        while(read(part3,&buffer,1)>0){
        write(archivo,&buffer,1);
        }
	//Cerramos todos los archivos abiertos
        close(archivo);
	close(part1);
	close(part2);
	close(part3);
	
	return 0;	
}

