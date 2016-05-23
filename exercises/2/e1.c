/**
 * Ejercicio 1) Implementar una función que retorne la posición de un
 * número dado. Si el número se repite, al volver a buscar por ese
 * número, la función debería devolver la siguiente posición del
 * número buscado.
 */
#include <unistd.h>

#include "lib.h"

#define SIZE 14

int main(int argc, char **argv)
{
    int sample[SIZE] = {0, 9, 8, 2, 2, 2, 5, 9, 5, 0, 3, 2, 3, 7};    
    int idx;

    //idx = get_index(...);
    printf("%d\n", idx);

    return 0;
}

