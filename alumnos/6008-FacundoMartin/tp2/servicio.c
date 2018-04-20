#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "servicio.h"

int contarP(char *texto){
	int palabras=0;

	int i=0;
	for (i = 0; i < strlen(texto); i++){
		if(texto[i] == ' '){
			palabras++;
		}
	}

	return palabras;
}

char *mayus(char *texto){
	int i=0,tmp=0;
	for (i = 0; i < strlen(texto); i++){
		if(texto[i] >= 'A' && texto[i] <= 'Z'){
			tmp=i;
			while(texto[tmp]!=' '){
				texto[tmp] = toupper(texto[tmp]);
				tmp++;
			}
		}
	}
	return texto;
}