#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 14
#define MAX_SIZE 14 * sizeof(int)
int main(int argc, char **argv)
{
int sample[SIZE] = {0, 9, 8, 2, 2, 2, 5, 9, 5, 0, 3, 2, 3, 7};
int i,j,aux,a=0;
int *nuevo=NULL;

nuevo = malloc(MAX_SIZE);

for(i = 0; i < SIZE; i++){
	aux = 0;
	for(j = 0; j < SIZE; j++){
		if(i!=j  && sample[i]==sample[j]){
			aux=1;
		}
	}
	if(aux==1){
		nuevo[a]=sample[i];
		a++;
	}
}
for(a = 0; a < 12; a++){
	printf("%d\n",nuevo[a]);
}
return 0;
}
