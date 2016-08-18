/**
 * Ejercicio 2) Encontrar el elemento que más ocurrencias tiene.
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
    int sample[SIZE] = {0, 9, 8, 2, 2, 2, 5, 9, 5, 0, 3, 2, 3, 7};
    int max_repeating_num;

    max_repeating_num = get_max_repeating_num(sample, SIZE);
    printf("number: %d\n", max_repeating_num);

    return 0;
}

