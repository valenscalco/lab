#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "contar.h"

int main(int argc, char **argv){
	int leido,contador=0;
	char buffer[1500];
	
	while ((leido = read(STDIN_FILENO,buffer, sizeof buffer)) > 0){
		printf("Cantidad de bytes: %d \n",leido);
		char *delimitador=" \n\t";
		contador = contar(leido,buffer,delimitador);
        	printf("Cantidad de palabras: %d \n",contador);
		delimitador="."; //las oraciones se delimitan por punto
		contador = contar(leido,buffer,delimitador);
       		 printf("Cantidad de oraciones: %d \n",contador);
		delimitador="\303"; //caracter especial
		contador = contar(leido,buffer,delimitador);
       		 printf("Cantidad de palabras con c.especiales: %d \n",contador);
	}
	return 0;
}

