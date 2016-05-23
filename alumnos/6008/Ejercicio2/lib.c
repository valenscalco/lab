#include "lib.h"

int get_index(int value, int *array, int len)
{
    int i;
    
    for (i=0; i<len; i++) {
	if(array[i]==value){
		return &array[i];
	}
    }

    return -1;
}

int get_max_repeating_num(int *array, int len)
{
	int max,i,j,aux,rep;
	
	for(i=0;i<len;i++){
		aux=0;
		for(j=0;j<len;j++){
			if(array[i]==array[j]){
				aux++;
			}
		}
		if(aux>rep){
			max=array[i];
			rep=aux;
		}
	}

	return max;
}
