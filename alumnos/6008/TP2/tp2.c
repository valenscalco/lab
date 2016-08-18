/*
 * Computación II: TP2: Comunicación entre procesos con pipes.
 */
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

#include "servicio.h"


int main(int argc, char **argv)
{
	char buffer[2048];
	int *total,hijos,n,fd[2],fd2[2],returnstatus,*palabras;
	char * pch;
	pid_t childpid;
	
	palabras = malloc(16*sizeof(int));
	total = malloc(16*sizeof(int));
	if (pipe(fd) < 0){
		perror("pipe()");
		return -1;
	}
	
	if(argv[1]&&argv[3]&&strcmp(argv[1],"-n ")&&strcmp(argv[3],"-o ")){
		hijos=atoi(argv[2]);
		memset(total,0,16*sizeof(int));
		memset(buffer,0, sizeof(buffer));
		read(STDIN_FILENO, buffer, sizeof(buffer));
		pch = strtok (buffer, "\n");
		for(n=0;n<hijos;n++){
			if(pch != NULL && n>0){
				pch = strtok(NULL,"\n");
			}
			if(fork()==0){
					if (pch != NULL && n != hijos-1){
						close(fd[0]);
						palabras=contar(pch);
						write(fd[1],palabras,16*sizeof(int));
						close(fd[1]);
						return(0);
					}
					if (pch != NULL && n == hijos-1){
						close(fd[0]);
						while(pch != NULL){
							palabras=contar(pch);
							write(fd[1],palabras,16*sizeof(int));
							pch = strtok (NULL,"\n");
						}
						close(fd[1]);
						return(0);
					}

					return(0);
				}
		}
		close(fd[1]);
		if (pipe(fd2) < 0){
			perror("pipe()");
			return -1;
		}
		if((childpid=fork())==0){
			while((read(fd[0],palabras,16*sizeof(int)))>1){
				for(n=0;n<16;n++){
					total[n]=total[n]+palabras[n];
				}
			}
			
			close(fd[0]);
			write(fd2[1],total,16*sizeof(int));
			return 0;
		}
		close(fd[0]);
			
		if(childpid!=0){
			waitpid(childpid,&returnstatus,0);
			close(fd2[1]);
			read(fd2[0],total,16*sizeof(int));
			mostrar(total);
			return(0);
		}
	}
	else{
		printf("Ejecucion incorrecta del programa. $ cat <archivo> | ./tp2 -n <nro_hijos> -o d\n");
	}
	free(palabras);
	free(total);
	return 0;
}
