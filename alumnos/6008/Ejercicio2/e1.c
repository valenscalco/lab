/**
 * Ejercicio 1) Implementar una función que retorne la posición de un
 * número dado. Si el número se repite, al volver a buscar por ese
 * número, la función debería devolver la siguiente posición del
 * número buscado.
 */
#include <unistd.h>
#include <stdio.h>
#include "lib.h"

#define SIZE 14

int main(int argc, char **argv)
{
	int sample[SIZE] = {0, 9, 8, 2, 2, 2, 5, 9, 5, 0, 3, 2, 3, 7};    
	int idx,numero,i;

	printf("El arrelgo es:\n");
	for(i=0;i<SIZE;i++){
		printf(" %d ",sample[i]);
	}
	printf("\n");	
	while(numero!=100){
		printf("Ingrese un numero, numero 100 para salir: ");
		scanf("%d",&numero);
		if((idx = get_index(numero,sample,SIZE)) != -1){
			printf("La posicion del numero ingresado es: %d\n", idx);
			for(i=0;i<SIZE;i++){
				if(sample[i]==numero){
					sample[i]=99;
					break;
				}
			}
		}
		else{
			printf("El numero ingresado no se encuentra en el arreglo o ya fue repetido todas las veces que estaba\n");
		}
	}
	return 0;
}

