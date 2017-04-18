#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "head.h"
#include <sys/mman.h>
#include <semaphore.h>

int main (int argc, char **argv){
    char *ptr;
    int *ptr1;
    int *ser,*salida;
    char *tok;
    int i;
    sem_t *sem1=NULL;
    sem_t *sem2=NULL;

    ptr = mmap(NULL,sizeof(char)*2048,PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);  //memoria para el texto
    ptr1 = mmap(NULL,sizeof(char)*2048,PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);  //memoria para el texto
    sem1 = mmap(NULL,sizeof(sem_t),PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);     //memoria para los semaforos
    sem2 = mmap(NULL,sizeof(sem_t),PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    sem_init(sem1,1,0); //inicializo los semaforos en 0
    sem_init(sem2,1,0);

    switch (fork()){
        case 0: //hijo
            sem_wait(sem1);

            ser = malloc(16*sizeof(int));
            salida = malloc(16*sizeof(int));
            memset(salida,0,16*sizeof(int));

            tok = strtok(ptr,"\n");

            while (tok !=NULL){  //if
                ser=contador(tok);
                for(i=0;i<16;i++){
                    ptr1[i]=ptr1[i]+ser[i];
                } 
                tok = strtok(NULL,"\n");
            }
            sem_post(sem2);
            return 0;
        case -1: //error fork
            perror("fork(): ");
            return -1;
        default: //padre
            break;
    }


    memset(ptr,0,sizeof(char)*2048);

    read(STDIN_FILENO,ptr,sizeof(char)*2048);

    sem_post(sem1);
    sem_wait(sem2);


    printf("\n");
    for(i=1;i<15;i++){
        printf("Hay %d palabras de %d caracteres\n",ptr1[i],i);    
    }  
    return 0; 
}  
