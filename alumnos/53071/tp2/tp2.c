/*
 * Computación II: TP2: Comunicación entre procesos con pipes.
 */
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "servicio.h"


int main(int argc, char **argv)
{
    char buffer[500];
    int *salida,hijos,fd[2],fd_hap[2],i;
    int *ser;
    char *tok;
    pid_t pid_hijo_m, pid_hijo;
    int c;

    ser = malloc(16*sizeof(int));
    salida = malloc(16*sizeof(int));
    memset(salida,0,16*sizeof(int));
    memset(buffer,0, sizeof(buffer));

    if (pipe(fd) < 0){
        perror("pipe()");
        return -1;
    }

    if (pipe(fd_hap) < 0){
        perror("pipe()");
        return -1;
    }
    while (( c = getopt(argc,argv,"n:o:")) != -1){
        switch (c){
            case 'n':
                hijos=atoi(optarg);
                read(STDIN_FILENO, buffer, sizeof(buffer));
                tok = strtok (buffer,"\n");
                for(i=0;i<hijos;i++){
                    if(tok != NULL && i>0){
                        tok = strtok(NULL,"\n");
                    }
                    pid_hijo=fork();//n hijos
                    if(pid_hijo==0){
                        if (tok != NULL && i != hijos-1){
                            close(fd[0]);
                            ser=forks(tok);
                            write(fd[1],ser,16*sizeof(int));
                            close(fd[1]);
                            return 0;
                        }
                        if (tok != NULL && i == hijos-1){
                            close(fd[0]);
                            while(tok != NULL){
                                ser=forks(tok);
                                write(fd[1],ser,16*sizeof(int));
                                tok = strtok (NULL,"\n");
                            }
                            return 0;
                        }
                        return 0;
                    }
                }
                close(fd[1]);
                pid_hijo_m=fork(); //hijo monitor
                if((pid_hijo_m)==0){
                    while((read(fd[0],ser,16*sizeof(int)))>1){
                        for(i=0;i<16;i++){
                            salida[i]=salida[i]+ser[i];
                        }
                    }

                    close(fd[0]);
                    write(fd_hap[1],salida,16*sizeof(int));
                    return 0;
                }
                close(fd_hap[1]);
                read(fd_hap[0],salida,16*sizeof(int)); //padre
                for(i=1;i<15;i++){
                    printf("Hay %d palabras de %d caracteres\n",salida[i],i);
                } 
                return 0;

                break;
            case 'o':
                break;
            case '?':
                if (optopt == 'n' || optopt == 'o')
                    fprintf(stderr,"Option -%c needs argument\n",optopt);
                else
                    fprintf(stderr,"Unknown option -%c. \n",optopt);
                break;
            default: 
                break;
        }
    }
    return 0;
}

