#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include "head.h"

int guardar(int archivo, char *nombre){

	int leido, escrito, archivo2;
	char buff[2000];
	
	if( (archivo2 = open(nombre, O_RDONLY)) < 0){
		return -1;		
	}

	while( (leido = read(archivo2, buff, sizeof buff)) > 0){
		buff[leido] = 0;
		escrito = write(archivo, buff, leido);
		//printf("%d\n",escrito);
		//printf("%s\n",buff);
	}

	close(archivo2);
	return 0;
}

