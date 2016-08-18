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

int get_index(int value,char array[SIZE], int len)
{
    char *pch;
    int i;
    printf("valor %d\n",value);
    pch=strchr(array,value); 
    for (i=0;i<len;i++){
        if (array[i]==value){        
        printf ("found at %d\n",pch-array+1);
        pch=strchr(pch+1,value);
        }
    }
    return 0;
}

/*int get_max_repeating_num(int *array, int len)
  {


  return -1;
  } */
