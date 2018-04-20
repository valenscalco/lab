#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "servicio.h"

int contarP(char *texto){
	int palabras=1;
	char *pos,*pch;

	pch = strtok_r(texto," ,-",&pos);
	while(pch){
		palabras++;
		pch = strtok_r(NULL," ,-",&pos);
	}
	return palabras;
}

int contarO(char *texto){
	int oraciones=-1;
	char *pos,*pch;

	pch = strtok_r(texto,".",&pos);
	while(pch){
		oraciones++;
		pch = strtok_r(NULL,".",&pos);
	}
	
	return oraciones;
}

int contarE(char *texto){
	int especiales=-1;
	char *pos,*pch;

	pch = strtok_r(texto,"áéíóúüÁÉÍÓÚÜ",&pos);
	while(pch){
		especiales++;
		pch = strtok_r(NULL,"áéíóúüÁÉÍÓÚÜ",&pos);
	}
	return especiales;
}