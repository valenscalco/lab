#include "servicio.h"

/* Función que hace el histograma de palabras y letras */
void histograma(int lectura2, char *buffer, int * vectorLetras, int * vectorParalelo,int menorMayor){
	int m=1;
    int i=0;
    int j=0;
	int aux;
	int aux2;

		//Limpiamos el vector que vamos a llenar
		for(i=0;i<15;i++){
			vectorLetras[i]=0;
		}
		//Cargamos el vector paralelo con la cantidad de letras por palabras
		for(i=0;i<15;i++){
			vectorParalelo[i]=m;
			m++;
		}
		for(i = 0; i < strlen(buffer); i++){
			//Contador para palabras con 1 caracter
			if(buffer[i-1] == ' ' && buffer[i] != ' ' && buffer[i+1] == ' '){
				vectorLetras[0]++;
			}
			//Contador para palabras con 2 caracteres
			if(buffer[i-1] == ' ' && buffer[i] != ' ' && buffer[i+1] != ' ' && buffer[i+2] == ' '){
				vectorLetras[1]++;
			}
			//Contador para palabras con 3 caracteres
			if(buffer[i-1] == ' ' && buffer[i] != ' ' && buffer[i+1] != ' ' && buffer[i+2] != ' ' && buffer[i+3] == ' '){
				vectorLetras[2]++;
			}
			//Contador para palabras con 4 caracteres
			if(buffer[i-1] == ' ' && buffer[i] != ' ' && buffer[i+1] != ' ' && buffer[i+2] != ' ' && buffer[i+3] != ' ' && buffer[i+4] == ' '){
				vectorLetras[3]++;
			}
			//Contador para palabras con 5 caracteres
			if(buffer[i-1] == ' ' && buffer[i] != ' ' && buffer[i+1] != ' ' && buffer[i+2] != ' ' && buffer[i+3] != ' ' && buffer[i+4] != ' ' && buffer[i+5] == ' '){
				vectorLetras[4]++;
			}
			//Contador para palabras con 6 caracteres
			if(buffer[i-1] == ' ' && buffer[i] != ' ' && buffer[i+1] != ' ' && buffer[i+2] != ' ' && buffer[i+3] != ' ' && buffer[i+4] != ' ' && buffer[i+5] != ' ' && buffer[i+6] == ' '){
				vectorLetras[5]++;
			}
			//Contador para palabras con 7 caracteres
			if(buffer[i-1] == ' ' && buffer[i] != ' ' && buffer[i+1] != ' ' && buffer[i+2] != ' ' && buffer[i+3] != ' ' && buffer[i+4] != ' ' && buffer[i+5] != ' ' && buffer[i+6] != ' ' && buffer[i+7] == ' '){
				vectorLetras[6]++;
			}
			//Contador para palabras con 8 caracteres
			if(buffer[i-1] == ' ' && buffer[i] != ' ' && buffer[i+1] != ' ' && buffer[i+2] != ' ' && buffer[i+3] != ' ' && buffer[i+4] != ' ' && buffer[i+5] != ' ' && buffer[i+6] != ' ' && buffer[i+7] != ' ' && buffer[i+8] == ' '){
				vectorLetras[7]++;
			}
			//Contador para palabras con 9 caracteres
			if(buffer[i-1] == ' ' && buffer[i] != ' ' && buffer[i+1] != ' ' && buffer[i+2] != ' ' && buffer[i+3] != ' ' && buffer[i+4] != ' ' && buffer[i+5] != ' ' && buffer[i+6] != ' ' && buffer[i+7] != ' ' && buffer[i+8] != ' ' && buffer[i+9] == ' '){
				vectorLetras[8]++;
			}
			//Contador para palabras con 10 caracteres
			if(buffer[i-1] == ' ' && buffer[i] != ' ' && buffer[i+1] != ' ' && buffer[i+2] != ' ' && buffer[i+3] != ' ' && buffer[i+4] != ' ' && buffer[i+5] != ' ' && buffer[i+6] != ' ' && buffer[i+7] != ' ' && buffer[i+8] != ' ' && buffer[i+9] != ' ' && buffer[i+10] == ' '){
				vectorLetras[9]++;
			}
			//Contador para palabras con 11 caracteres
			if(buffer[i-1] == ' ' && buffer[i] != ' ' && buffer[i+1] != ' ' && buffer[i+2] != ' ' && buffer[i+3] != ' ' && buffer[i+4] != ' ' && buffer[i+5] != ' ' && buffer[i+6] != ' ' && buffer[i+7] != ' ' && buffer[i+8] != ' ' && buffer[i+9] != ' ' && buffer[i+10] != ' ' && buffer[i+11] == ' '){
				vectorLetras[10]++;
			}
			//Contador para palabras con 12 caracteres
			if(buffer[i-1] == ' ' && buffer[i] != ' ' && buffer[i+1] != ' ' && buffer[i+2] != ' ' && buffer[i+3] != ' ' && buffer[i+4] != ' ' && buffer[i+5] != ' ' && buffer[i+6] != ' ' && buffer[i+7] != ' ' && buffer[i+8] != ' ' && buffer[i+9] != ' ' && buffer[i+10] != ' ' && buffer[i+11] != ' ' && buffer[i+12] == ' '){
				vectorLetras[11]++;
			}
			//Contador para palabras con 13 caracteres
			if(buffer[i-1] == ' ' && buffer[i] != ' ' && buffer[i+1] != ' ' && buffer[i+2] != ' ' && buffer[i+3] != ' ' && buffer[i+4] != ' ' && buffer[i+5] != ' ' && buffer[i+6] != ' ' && buffer[i+7] != ' ' && buffer[i+8] != ' ' && buffer[i+9] != ' ' && buffer[i+10] != ' ' && buffer[i+11] != ' ' && buffer[i+12] != ' ' && buffer[i+13] == ' '){
				vectorLetras[12]++;
			}
			//Contador para palabras con 14 caracteres
			if(buffer[i-1] == ' ' && buffer[i] != ' ' && buffer[i+1] != ' ' && buffer[i+2] != ' ' && buffer[i+3] != ' ' && buffer[i+4] != ' ' && buffer[i+5] != ' ' && buffer[i+6] != ' ' && buffer[i+7] != ' ' && buffer[i+8] != ' ' && buffer[i+9] != ' ' && buffer[i+10] != ' ' && buffer[i+11] != ' ' && buffer[i+12] != ' ' && buffer[i+13] != ' ' && buffer[i+14] == ' '){
				vectorLetras[13]++;
			}
			//Contador para palabras con 15 caracteres
			if(buffer[i-1] == ' ' && buffer[i] != ' ' && buffer[i+1] != ' ' && buffer[i+2] != ' ' && buffer[i+3] != ' ' && buffer[i+4] != ' ' && buffer[i+5] != ' ' && buffer[i+6] != ' ' && buffer[i+7] != ' ' && buffer[i+8] != ' ' && buffer[i+9] != ' ' && buffer[i+10] != ' ' && buffer[i+11] != ' ' && buffer[i+12] != ' ' && buffer[i+13] != ' ' && buffer[i+14] != ' ' && buffer[i+15] == ' '){
				vectorLetras[14]++;
			}
		}
		//Si el orden es de menor a mayor
		if (menorMayor==1){
			//Ocupamos el método burbuja para ordenar el vector
			for(i=0; i<15; i++){
				for(j=0; j<15-i; j++){
					if(vectorLetras[j] > vectorLetras[j+1]){
						aux=vectorLetras[j];
						vectorLetras[j]=vectorLetras[j+1];
						vectorLetras[j+1]=aux;
						aux2=vectorParalelo[j];
						vectorParalelo[j]=vectorParalelo[j+1];
						vectorParalelo[j+1]=aux2;
					}
				}
			}
		}
		//Si el orden es de mayor a menor
		if (menorMayor==2){
			for(i=0; i<15; i++){
				for(j=0; j<15-i; j++){
					if(vectorLetras[j] < vectorLetras[j+1]){
						aux=vectorLetras[j];
						vectorLetras[j]=vectorLetras[j+1];
						vectorLetras[j+1]=aux;
						aux2=vectorParalelo[j];
						vectorParalelo[j]=vectorParalelo[j+1];
						vectorParalelo[j+1]=aux2;
					}
				}
			}

		}
		
	}
