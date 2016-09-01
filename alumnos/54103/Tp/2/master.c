#include "histograma.h"


int * master(int tam, char * buff){
	int a=0, i;
	int c=0;
	int * aux;
	aux=calloc (20,1);
	for (i=0;i<30;i++){
		aux[i]=0;
	}	
	for (i=0; i<tam; i++){
		if(buff[i]!= ' ' ){
			 c++;
		}else {	
			a++;
			aux[c]=aux[c]+1;
			c=0;
			}
		
	}
	
	return aux;

}
