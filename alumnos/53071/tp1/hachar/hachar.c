#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>  
#define MAX_SIZE 13

int main(int cant, char **valor)
{
	int archivo,archivo2,leido;
	char buf[MAX_SIZE];
	 char nombreArchivo[20]; 
	int i=0;
	char nombre[15]="";

     if(cant == 2){ //si son dos..
        strcpy(nombreArchivo, valor[1]); //copiamos valor a nombreArchivo, solo para cadenas
    }
    else{ //si no..
        strcpy(nombreArchivo, "hola.txt");
    }

    if( (archivo = open(nombreArchivo, O_RDWR)) < 0){ //abrimos solo lectura y escritura; < 0 por si tira error
        perror("open()");
    } 
    
	while((leido = read(archivo,buf,MAX_SIZE))>0){
            sprintf(nombre,"%s-%d",valor[1],i);
            archivo2=open(nombre, O_CREAT | O_RDWR, 0744);
            write(archivo2,buf,leido);
           i++; 
	}
	close(archivo2);
	close(archivo);
	return 0;
}
