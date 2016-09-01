#include "histograma.h"


int parametros (char* a1,char* a3, char* a2,char* a4){
	
	int valor,hijos;
	if (!strcmp(a1,"-n") && !strcmp(a3,"-o") && (!strcmp(a4,"a") || !strcmp(a4,"d"))){
                hijos=atoi(a2);
                if (!strcmp(a4,"a")){
                        printf("Orden: Menor a Mayor\n");
               		valor=0;
                }
                else if (!strcmp(a4,"d")){
                        printf ("Orden: Mayor a Menor\n");
	                valor=1;
                } 
        }
         else{
                printf("Parametro incorrecto\n");
                exit (0);
        }
	printf("Numero de hijos: %d\n", hijos);

return valor;
}
