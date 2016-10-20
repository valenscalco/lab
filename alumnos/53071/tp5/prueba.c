#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <assert.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include "http_h.h"

int main (int argc , char **argv){

    int opcion;
	int puerto;

    while ((opcion = getopt(argc,argv, "p:")) != -1){ //manejo de argumentos, en este caso se le pasa un 
        //argumento que es el puerto para que funcione el webserver
        switch (opcion){
            case 'p':  // puerto
		puerto=atoi(optarg);
		create_sock(puerto);
                break;
            case '?':
                if (optopt == 'p')
                    fprintf(stderr,"Option -%c needs argument\n",optopt);
                else
                    fprintf(stderr,"Unknown option -%c. \n",optopt);
                break;
                return 0;
        }
        }

        return 0;
    }

