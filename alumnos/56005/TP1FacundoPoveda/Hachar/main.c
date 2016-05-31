#include "hacha.h"

void info (char ** argv){
        /* Función que muestra informarción al usuario */
        printf("El nombre del archivo introducido es : %s \n", argv[1]);
}

int cantPartes (int tamano){
	/* Función que recibe el tamaño en bytes del archivo 
	y devuelve una la cantidad en bytes de cada partes */
	printf("El peso del archivo a introducido es de : %i bytes \n", tamano);
	return tamano/3;
}

void crearPartes (int file, char *aux, int part){
	/* Función que recibe el archivo a leer, una variable auxiliar y el tamaño de una de las partes y crea los N archivos */
	int part1;
        int part2;
        int part3;
	int cont2=0;
	
 	while(read (file,aux,part)){
                cont2++;
                if(cont2==1){
                        part1 = open("Parte1", O_CREAT | O_RDWR, 0644);
                        write(part1, aux, part);
                }
                if(cont2==2){
                        part2 = open("Parte2", O_CREAT | O_RDWR, 0644);
                        write(part2, aux, part);
                }
                if(cont2==3){
                        part3 = open ("Parte3", O_CREAT | O_RDWR, 0644);
                        write(part3, aux, part);
                        while(read(file,aux,1)>0){
                                write(part3, aux, 1);}
                        break;
                }

}
	close (part1);
        close (part2);
        close (part3);

}



int main (int argc, char ** argv){
	int file;
	char *aux;
	int part; 
	char buffer;
	int cont=0;

	//Información al usuario	
	info(argv);
	
	//Abrimos el archivo con permisos de lectura y leemos de a 1 byte
	file = open(argv[1], O_RDONLY, NULL);
	while(read(file,&buffer,1)>0){
		cont++;
	}
	
	//Tamaño de las partes
	part = cantPartes(cont);
	
	//Reservo memoria dinámica
	aux = calloc(part,1);

	//Abro de nuevo - ERROR ? - y leo la cantidad de 1/3 de los bytes
	file = open(argv[1], O_RDONLY, NULL);
	
	//Creo las partes
	crearPartes(file,aux,part);
		
	//Cerramos el archivo principal
	close (file);
	
	return 0;
}
