#include "histograma.h"
int* distribucion(char* buffer,int leido){
	int *dist,i,palabras=0,caracter=0;
	dist=(int*)malloc(sizeof(char)*20);
	for(i=0;i<20;i++){
		dist[i]=0;
	}
	for(i=0;i<leido;i++){
		if(buffer[i]==' ' || i==leido-1){
			palabras++;
			dist[caracter]=dist[caracter]+1;
			caracter=0;
		}else{
			caracter++;
		}
	}
	/*for(i=0;i<20;i++){
		if(dist[i]!=0){
			printf(" hay %d palabras con %d caracteres\n ",dist[i],i);
		}	
	}*/
return dist;
}
