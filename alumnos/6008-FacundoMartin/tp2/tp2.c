#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "servicio.h"

int main(int argc, char **argv)
{
    char buffer[80],archivo[50];
    int nread,fd[2],fd2[2],fd3[2],words=0,opt,control=-1,fdarchivo, leer=0,leido;
    char *out, texto[80];

    //Verifico Argunemntos
    while ((opt = getopt(argc, argv,"i:o:")) != -1) {
    	switch (opt) {
    		case 'i':
    			fdarchivo = open (optarg,O_RDONLY);
    			leer=1;
    			break;
    		case 'o':
                strcpy(archivo,optarg);
                control=1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-o] file\n",argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    if (control==-1) {
        fprintf(stderr, "Se esperaban argumentos\n");
        exit(EXIT_FAILURE);
    }
    //Creo pipes
    pipe(fd);
    pipe(fd2);
    pipe(fd3);

    //Leo los datos de entrada
    do {
        memset(buffer, 0, sizeof buffer);
        if(leer==0){
        	nread = read(STDIN_FILENO, buffer, sizeof buffer);
        }
        else{
        	nread = read(fdarchivo, buffer, sizeof buffer);
        }

		write(fd2[1],buffer,nread);
		write(fd3[1],buffer,nread);

    } while (nread > 0);

    //Creo hijo que cuenta palabras
	if(fork()==0){
		int palabras=0;
		close(fd2[1]);
		close(fd[0]);
		close(fd3[0]);
		close(fd3[1]);

		do{
			memset(texto, 0, sizeof texto);
			leido = read(fd2[0],texto,sizeof texto);
			palabras += contarP(texto);
		} while (leido > 3);

		write(fd[1],&palabras,sizeof(int));
		close(fd[1]);
		close(fd2[0]);
		return 0;
	}

	//Creo hijo que pasa palabras a mayusculas
	if(fork()==0){
		close(fd[1]);
		close(fd[0]);
		close(fd2[1]);
		close(fd2[0]);
		close(fd3[1]);
		char *temp = malloc(80);

		do{
			memset(texto, 0, sizeof texto);
			leido = read(fd3[0],texto,sizeof texto);
			
			const size_t old_len = strlen(temp);
	    	const size_t out_len = old_len + leido + 1;
			out = malloc(out_len);

	    	memcpy(out, temp, old_len);
	    	memcpy(out + old_len, texto, leido);

	    	temp = realloc(temp,out_len);
	    	memcpy(temp, out, out_len);
		} while (leido > 3);

		temp = mayus(temp);
		fdarchivo = open (archivo,O_RDWR|O_TRUNC|O_CREAT, S_IRUSR|S_IWUSR);
		write(fdarchivo,temp,strlen(temp));
		printf("Se creo un archivo llamado: %s\n",archivo);
		
		close(fdarchivo);
		close(fd3[0]);
		free(temp);
		return 0;
	}

	//Muestro la cantidad de palabras en el proceso padre
	else{
		sleep(1);
		close(fd[1]);
		close(fd2[1]);
		read(fd[0],&words,sizeof(int));
		printf("Las palabras son: %d\n",words);
    	return 0;
	}

}
