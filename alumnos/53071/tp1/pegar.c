#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "head.h"

int main(int cant, char **valor){
	
	int leido, archivo; //para las funciones, read, write, open
	int i, j = 0; //contadores
	char buf[500] = ""; //para guardar por entrada
	char nombreArchivo[20]; //nombre del archivo
	char tmp[20]; //auxiliar

	if(cant == 2){ //si son dos..
		strcpy(nombreArchivo, valor[1]); //copiamos valor a nombreArchivo, solo para cadenas
	}
	else{ //si no..
		strcpy(nombreArchivo, "dog.ppm-00");
	}

	printf("\nNombre del archivo a abrir: %s\n", nombreArchivo);

	if( (archivo = open(nombreArchivo, O_RDWR)) < 0){ //abrimos solo lectura y escritura; < 0 por si tira error
		perror("open()");
		if( (archivo = open(nombreArchivo, O_RDWR | O_CREAT, 0600)) > 0){ //creamos el archivo si este no existe, > 0 por si sale bien
			printf("Archivo %s creado con exito.\n", nombreArchivo);
		}
	}

	printf("\n");

	/*Leemos por entrada hasta que finalice*/
    while( (leido = read(STDIN_FILENO, buf, sizeof buf)) > 0){
		//buf[leido] = 0; //igual a cero para terminar dentro del buf
		for(i=0; i < leido; i++){
			tmp[j] = *(buf+i);
			j++;
			if(*(buf+i) == '\n'){ //si es un salto
				tmp[j-1] = 0; //termina antes
				j = 0;
				
				if(guardar(archivo, tmp) < 0){
					printf("Error al abrir %s.\n", tmp);
				}
				else{
					printf("Archivo %s guardado.\n", tmp);
				}
			}
		}
	}
		
	close(archivo);
	return 0;
}

