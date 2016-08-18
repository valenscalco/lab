/**
 * Ejercicio 1) Implementar una función que retorne la posición de un
 * número dado. Si el número se repite, al volver a buscar por ese
 * número, la función debería devolver la siguiente posición del
 * número buscado.
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "lib.h"
#define SIZE 14

int main(int argc, char **argv)
{
    char sample[SIZE] = {0, 9, 8, 2, 2, 2, 5, 9, 5, 0, 3, 2, 3, 7};    
    int idx;
    int valor;

    valor=atoi(argv[1]);
    //printf("%d\n",sample[SIZE]);
    idx = get_index(valor,sample,SIZE);
    printf("%d\n", idx);

    return 0;
}

