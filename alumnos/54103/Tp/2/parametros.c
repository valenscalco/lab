#include "histograma.h"


int parametros (char * n ,char * hijos,char * o,char * ad ){
	
	int valor=0;

	if (!strcmp(n,"-n")){
//		printf ("Numero de hijos %s\n", hijos);
	} else{	printf("Parametros incorrectos\n");
		exit (0); 
	}
	if (!strcmp(o,"-o")){
		if(!strcmp(ad,"a") || !strcmp(ad,"d")){
			if (!strcmp(ad,"a")){
//				printf ("Va de menor a mayor\n");
				valor=1;
			}
			if (!strcmp(ad,"d")){
//				printf ("Va de mayor a menor\n");
				valor =0;
			}
		}else {printf("parametros incorrectos\n");
			exit (0);
		}
		
	}else{ printf("paramentros incorrectos\n");
		exit (0);	
	}
	
	return valor;
}
