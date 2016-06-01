#include "histograma.h"

int main(int argc,char *argv[])
{
	system("/usr/bin/clear");
	char buffer[1000];
	int leido,orden,hijos,i,palabras,newleido;
	float por;

	//Entrada estandar
	leido = read(0,buffer,sizeof buffer);
	write(1, buffer, leido);
	printf("leido=%d\n",leido);

	// -n , -o , numero de hijos y orden
	orden=parametros(argv[1],argv[3],argv[2],argv[4]);//defino el orden en el que quiero los parametros, funcion: parametros.c
	hijos=atoi(argv[2]);//numero de hijos lo paso a int
	
	//analizar cadena
	palabras=romper(buffer,leido);//da el numero de palabras con la funcion romper.c
	printf("\n");
	
	//creacion de hijos
	int fd[2],fd1[2],fd2[2],fd3[2],*ptr,*ptr2;
	char aux[leido];
	ptr=(int*)malloc(sizeof(char)*20);
	ptr2=(int*)malloc(sizeof(char)*20);
	newleido=(leido/hijos)+(leido%hijos);
	pipe(fd);
	pipe(fd1);
	pipe(fd2);
	pipe(fd3);
	write(fd[1],buffer,leido);
	for(i=0;i<hijos+1;i++){
		switch(fork()){//hijos
			case 0:
				if(i != hijos-1){
					close(fd[1]);
					close(fd2[0]);
					close(fd2[1]);
					if(read(fd[0],aux,newleido)>0){
						printf("\n PID=%d\n",getpid());
						ptr=distribucion(aux,newleido);//arma un vector de distribucion
						write(fd1[1],ptr,newleido);
						write(fd3[1],ptr,newleido);
					}
					close(fd1[1]);
					close(fd[0]);
					close(fd3[1]);
					return 0;
				}
				if(i == hijos-1){//monitor
					close(fd1[1]);
					while (read(fd1[0],ptr,newleido)>0){
						ptr2=ordenar(orden,ptr);
						write(fd2[1],ptr2,newleido);
					}
					close(fd1[0]);
					close(fd2[1]);
					close(fd2[0]);
					return 0;
				}
		break;
		}
	}
	//padre
	close(fd[0]);
	close(fd1[0]);
	close(fd1[1]);
	close(fd2[1]);
	close(fd3[1]);
	while(read(fd3[0],ptr,newleido)){
		for(i=0;i<20;i++){
                	if(ptr[i]!=0){
                        	printf(" hay %d palabras con %d caracteres\n ",ptr[i],i);
                	}       
        	}
	}
	printf("\n");
	while (read(fd2[0],ptr2,newleido)>0){
		printf("Porcentaje de palabras en el texto\n");
		for (i=0;i<30;i++){
			if (ptr2[i]!=0){
				por=(ptr2[i]*100)/(float)palabras;
				printf("hay %d palabras ---> %f%% \n", ptr2[i],por);
			}
		}
	}
	return 0;

}

