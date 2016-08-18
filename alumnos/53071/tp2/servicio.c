#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include "servicio.h"

int * forks(char *tok){
    int *salida;
    int largo;
    char *ptrptr;
    char *palabra;

    salida = malloc(16*sizeof(int));

    palabra = strtok_r(tok," ¿?,.\"\n",&ptrptr);
    while(palabra != NULL){

        largo = strlen(palabra);
        switch(largo){
            case 1:
                salida[1]++;
                break;
            case 2:
                salida[2]++;
                break;
            case 3:
                salida[3]++;
                break;
            case 4:
                salida[4]++;
                break;
            case 5:
                salida[5]++;
                break;
            case 6:
                salida[6]++;
                break;
            case 7:
                salida[7]++;
                break;
            case 8:
                salida[8]++;
                break;
            case 9:
                salida[9]++;
                break;
            case 10:
                salida[10]++;
                break;
            case 11:
                salida[11]++;
                break;
            case 12:
                salida[12]++;
                break;
            case 13:
                salida[13]++;
                break;
            case 14:
                salida[14]++;
                break;
            default:
                break;
        }
        palabra = strtok_r(NULL," ¿?,.\"",&ptrptr);
    }
    return salida;
}

