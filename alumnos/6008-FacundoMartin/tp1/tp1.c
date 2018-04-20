#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "servicio.h"

#define SIZE 60000

int main(int argc, char **argv)
{
	char buffer[SIZE],texto[SIZE];
	int leido,palabras,oraciones,especiales;
	memset(buffer,0, sizeof(buffer));

	leido = read(STDIN_FILENO, buffer, sizeof buffer);
	write(STDOUT_FILENO, buffer, leido);
	//Contar Palabras
	strcpy(texto,buffer);
	palabras = contarP(texto);

	//Contar Oraciones
	strcpy(texto,buffer);
	oraciones = contarO(texto);

	//Contar Caracteres Especiales
	strcpy(texto,buffer);
	especiales = contarE(texto);

  	//Resultados
  	printf("\nEl texto tiene %d palabras.\n",palabras);
  	printf("El texto tiene %d oraciones.\n",oraciones);
  	printf("El texto tiene %d palabras con caracteres especiales.\n",especiales);
	return 0;
}
