#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "servicio.h"

int contarP(char *texto){

	int palabras=0;

	char *pos,*pch;

	pch = strtok_r(texto," \n",&pos);
	while(pch){

			palabras++;
		pch = strtok_r(NULL," \n",&pos);
	}
	return palabras;
}

int contarEsp(char *texto){
	int palabras=0;

	char *pos,*pch;

	pch = strtok_r(texto," ,.!;:\n",&pos);
	while(pch){
		if(strcmp(pch,"Hypertext")==0){
			palabras++;
		}
		if(strcmp(pch,"protocol")==0){
			palabras++;
		}
		if(strcmp(pch,"HTTP")==0){
			palabras++;
		}
		if(strcmp(pch,"MIME")==0){
			palabras++;
		}
		if(strcmp(pch,"gateway")==0){
			palabras++;
		}
		if(strcmp(pch,"URL")==0){
			palabras++;
		}
		if(strcmp(pch,"URI")==0){
			palabras++;
		}
		pch = strtok_r(NULL," ,.!;:\n",&pos);
	}

	return palabras;
}