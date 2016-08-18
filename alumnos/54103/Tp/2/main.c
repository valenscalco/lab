#include "histograma.h"


int main (int argc, char ** argv){

	char buffer[1000];
	char * buffer2, *buff;
	int tam,i,f,h,fd[2], fd1[2],fd2[2],fd3[2];
	float palabras, por;
	int *aux, *aux2;

	//Entrada Estandar
	tam = read (STDIN_FILENO, buffer, sizeof buffer);
	//tam=strlen(buffer);
	write (STDOUT_FILENO, buffer,tam);
	h = atoi(argv[2]);
	//Trabajo con -n y -o
	f=parametros(argv[1],argv[2],argv[3],argv[4]);
	buff=calloc(tam,1);
	// manejo de texto
	tam=tam/h+(tam%h);
	h=h+1;
	aux= calloc(20,1);
	aux2=calloc (20,1);
	pipe(fd);
	pipe (fd1);
	pipe (fd2);
	pipe (fd3);
	write (fd[1], buffer, sizeof buffer);	
	//write (fd[1], buffer, tam);	
	//Cuento las palabras
	buffer2=buffer;
	//strncpy(buffer2, buffer, sizeof buffer2);
	// buffer2 = strdup(buffer)
	palabras=romper(buffer2,tam);
	// creacion de hijos
	for (i=0;i<h;i++){
		switch (fork()){
			case 0: 
				if (i!=h-1){//hijos 	
					close(fd[1]);
					close(fd2[0]);
					close(fd2[1]);
					while (read (fd[0], buff, tam)>0){	
						printf("Soy el hijo->%d --> %s\n",getpid(), buff);  
						aux=master(tam,buff);
						write (fd1[1],aux,tam);
						write (fd3[1],aux,tam);	
						break;
					}
					close (fd1[1]);
					close (fd[0]);
					return 0;
				}		

				if (i==h-1){// hijo monitor
					close (fd1[1]);
					//printf("Trabajando\n");
					while (read(fd1[0], aux,tam)>0){
						aux2=contador(f,aux);
						write (fd2[1],aux2,tam);
					}
					close (fd1[0]);
					close (fd2[1]);
					close (fd2[0]);

					//break;
					return 0;
				}
				break;			
		}

	}	
	//padre
	close (fd1[0]);
	close (fd1[1]);
	close(fd[0]);
	close (fd2[1]);
	close (fd3[1]);
	printf("\n");
	printf ("\n");
	while (read(fd3[0],aux,tam)>0){
		printf("Cantidad de palabras por caracter\n");
		for (i=0;i<30;i++){
			if(aux[i]!=0){
				printf ("hay %d palabras de %d caracteres\n", aux[i],i);
			}
		}
	}
	printf ("\n");
	//while (read(fd2[0], aux2, 20)>0){
	while (read(fd2[0], aux2, tam)>0){
		printf("Porcentaje de palabras en el texto\n");
		for (i=0;i<30;i++){
			if (aux2[i]!=0){
				por=(aux2[i]*100)/(float)palabras;
				printf("hay %d palabras ---> %f%% \n", aux2[i],por);
			}
		}
	}
	return 0;
}
