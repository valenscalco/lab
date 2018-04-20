#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <signal.h>
#include <semaphore.h>

#include "servicio.h"

//Crear memoria compartida
void* create_shared_memory(size_t size) {
  // La memoria se va a poder leer y escribir:
  int protection = PROT_READ | PROT_WRITE;

  // El buffer va a ser compartido (shared) pero anonimo (solo los procesos hijos podran usarla):
  int visibility = MAP_ANONYMOUS | MAP_SHARED;

  // Creo la memoria; 
  return mmap(NULL, size, protection, visibility, 0, 0);
}

//Main
int main(int argc, char **argv)
{
    char buffer[80],palabrasStr[10];
    int nread,fdarchivo,opt,cont=0,shmemSize,palabras=0;
    sem_t *semaforo;
    char* texto;
    void* shmem = create_shared_memory(320000);
    semaforo = create_shared_memory(sizeof(sem_t));
    void* palabrasMem = create_shared_memory(sizeof(char)*10);
    pid_t hijo1,hijo2,hijo3;

    //Verifico Argunemntos
    while ((opt = getopt(argc, argv,"i:")) != -1) {
    	switch (opt) {
    		case 'i':
    			fdarchivo = open (optarg,O_RDONLY);
    			break;
            default:
                fprintf(stderr, "Usage: %s [-i] file\n",argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    sem_init(semaforo,1,0);
    //Creo hijos
    if((hijo1=fork())==0){
    	sem_wait(semaforo);
    	shmemSize = strlen(shmem); //Busco tamaño del texto
    	texto = malloc(shmemSize/2); //Le asigno la mitad del tamaño porque solo procesa una mitad
    	memcpy(texto,shmem,shmemSize/2); 
    	memcpy(palabrasStr,palabrasMem,sizeof(palabrasStr)); //Veo cuantas palabras tenia contadas y lo paso a un int
    	palabras = atoi(palabrasStr);
    	palabras = contarP(texto) + palabras;
    	sprintf(palabrasStr,"%d",palabras);
    	memcpy(palabrasMem,palabrasStr,sizeof(palabrasStr)); //Paso de int a string y lo guardo en mem compartida
    	free(texto);
    	sem_post(semaforo);
    	return 0;
    }

    if((hijo2=fork())==0){
    	sem_wait(semaforo);
		shmemSize = strlen(shmem); //Busco tamaño del texto
    	texto = malloc(shmemSize/2); //Le asigno la mitad del tamaño porque solo procesa una mitad
    	memcpy(texto,shmem+(shmemSize/2),shmemSize/2);
    	memcpy(palabrasStr,palabrasMem,sizeof(palabrasStr)); //Veo cuantas palabras tenia contadas y lo paso a un int
    	palabras = atoi(palabrasStr);
    	palabras = contarP(texto) + (palabras -1);
    	sprintf(palabrasStr,"%d",palabras);
    	memcpy(palabrasMem,palabrasStr,sizeof(palabrasStr)); //Paso de int a string y lo guardo en mem compartida
    	free(texto);
    	sem_post(semaforo);
    	return 0;
    }

    if((hijo3=fork())==0){
    	sem_wait(semaforo);
    	shmemSize = strlen(shmem);
    	texto = malloc(shmemSize);
    	memcpy(texto,shmem,shmemSize);
    	printf("La cantidad de palabras del conjunto es de: %d\n",contarEsp(texto));
    	free(texto);
    	sem_post(semaforo);
    	return 0;
    }

    //Cargo el contenido del archivo en memoria compartida
    do {
        memset(buffer, 0, sizeof buffer);
        nread = read(fdarchivo, buffer, sizeof buffer);
        memcpy(shmem+(80*cont), buffer, nread);
        cont++;
    } while (nread > 0);

    sem_post(semaforo);
    sleep(1);

    memcpy(palabrasStr,palabrasMem,sizeof(palabrasStr));
    printf("Las cantidad de palabras es de: %s\n",palabrasStr);

    return 0;
}