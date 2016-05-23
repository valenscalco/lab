#include <unistd.h>
#include <stdio.h>
#define SIZE 14
int main(int argc, char **argv)
{
int sample[SIZE] = {0, 9, 8, 2, 2, 2, 5, 9, 5, 0, 3, 2, 3, 7};
int i,j,aux;

for (i = 0; i < SIZE; i++) {
	for (j = i + 1; j < SIZE; j++) {
		if (sample[i] > sample[j]) {
			aux =  sample[i];
			sample[i] = sample[j];
			sample[j] = aux;
		}
	}        
}

for (i = 0; i < SIZE; i++) {
printf("%d\n", sample[i]);
// TODO ...
}
return 0;
}
