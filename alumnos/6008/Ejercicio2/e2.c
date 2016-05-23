/**
 * Ejercicio 2) Encontrar el elemento que más ocurrencias tiene.
 */
#include <unistd.h>
#include <stdio.h>
#include "lib.h"
#define SIZE 14


int main(int argc, char **argv)
{
    int sample[SIZE] = {0, 9, 8, 2, 2, 2, 5, 9, 5, 0, 3, 2, 3, 7};
    int max_repeating_num;

    max_repeating_num = get_max_repeating_num(sample, SIZE);
    printf("number: %d\n", max_repeating_num);

    return 0;
}

