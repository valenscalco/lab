#include "lib.h"
#include <stdio.h>

void get_index(int value, int *array, int len) {
    int i;

    for (i=0; i<len; i++) {
        if (array[i] == value) {
            printf("\nposicion [%d]",i);
        }
    }
}


/*int get_index(int value, int *array, int len) {
    int i;

    for (i=0; i<len; i++) {
        if (array[i] == value) {
            array[i] = -1;
            printf("\npos: %d",i);
            get_index(value, array, len);
            // return i;
        }
    }

    return -1;
}*/

int get_max_repeating_num(int *array, int len) {
    int i, j;
    int count=0, max=1;

    for (i=0; i<len; i++) {
        count=0;
        for (j=0; j<len; j++) {
            if (array[i] == array[j]) {
                count++;
            }
        }
        if (count > max) {
            max = count;
        }
    }

    return max;
}
