#include "histograma.h"
int romper(char* buffer,int leido){
        int i=0;
        char *cadena,copia[leido];
	strcpy(copia,buffer);
        cadena = strtok(copia," ");
        while(cadena != NULL){
                cadena = strtok(NULL," ");
                i++;
        }
        printf("\nnumero de palabras= %d\n",i);
return i;
}

