#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "servicio.h"

int * contar(char *linea){
	static int palabras[16];
	int n,largo;
	char *pos,*word;
	for(n=0;n<15;n++){
		palabras[n]=0;	
	}
	word = strtok_r(linea," ¿?,.\"\n",&pos);
	while(word){
		largo = strlen(word);
		switch(largo){
			case 1:
				palabras[1]++;
				break;
			case 2:
				palabras[2]++;
				break;
			case 3:
				palabras[3]++;
				break;
			case 4:
				palabras[4]++;
				break;
			case 5:
				palabras[5]++;
				break;
			case 6:
				palabras[6]++;
				break;
			case 7:
				palabras[7]++;
				break;
			case 8:
				palabras[8]++;
				break;
			case 9:
				palabras[9]++;
				break;
			case 10:
				palabras[10]++;
				break;
			case 11:
				palabras[11]++;
				break;
			case 12:
				palabras[12]++;
				break;
			case 13:
				palabras[13]++;
				break;
			case 14:
				palabras[14]++;
				break;
			case 15:
				palabras[15]++;
				break;
			default:
				break;
		}
		word = strtok_r(NULL," ¿?,.\"",&pos);
	}
	return palabras;
}

void mostrar(int *total){
	int n;
	printf("\tSe encontraron:\n\n");
	for(n=1;n<16;n++){
		printf("%d palabra/s de %d letra/s\n",total[n],n);
	}
}
