#include "servicio.h"

/*Función que detecta errores cometidos por el usuario*/
int detectarErrores(char * n, char * o, int numHijos, char * orden, int menorMayor){
    if(strcmp(n,"-n")){
        printf("Error en el argumento -n \n");
        exit(0);
    }
    if(numHijos<0){
        printf("La cantidad de hijos no puede ser negativa \n");
        exit(0);
    }
    if(strcmp(o,"-o")){
        printf("Error en el argumento -o \n");
        exit(0);
    }
    
    //Información al usuario
    if(!strcmp(orden,"a")){
        printf("Orden: De menor a mayor \n");
        return 1;
    }
    else
        if(!strcmp(orden,"d")){
            printf("Orden: De mayor a menor \n");
            return 2;
        }else{
            printf("Error en el argumento del orden \n");
            return 0;
        }
}
