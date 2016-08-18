#include "histograma.h"

int romper(char* buffer,int leido){
	
	int i=0;
	char *cadena2;
	cadena2 = strtok(buffer," ");
       	while(cadena2 != NULL){    
               	cadena2 = strtok(NULL," ");
		i++;
	}
//	printf("Hay %d palabras\n",i);
	return i;
}
