#include "servicio.h"

/* Función que crea la cantidad de hijos deseada por el usuario*/
void crearHijos(int cantHijos, int menorMayor, char * archivo, int palabrasTotales){
	int i;
	int j;
	int m=1;
	int cantBytes;
	int fd1[2];
	int fd2[2];
	int fd3[2];
	int fd4[2];
	int lectura1=0;
	int lectura2=0;
	int lectura3=0;
	int lectura4=0;
	int escritura1=0;
	int escritura2=0;
	int escritura3=0;
	int escritura4=0;
	int file;
	char buffer[BUFFER];
	float porcentaje;
	int vectorLetras[15];
	int vectorParalelo[15];
	int aux;
	int aux2;

	printf("Proceso padre %d \n", getpid());
	file = open(archivo, O_RDWR);
	//Creo los pipes
	pipe(fd1);
	pipe(fd2);
	pipe(fd3);
	pipe(fd4);
	//Etiqueto los descriptores que van a usar los pipes
	lectura1 = fd1 [0];
	lectura2 = fd2 [0];
	lectura3 = fd3 [0];
	lectura4 = fd4 [0];
	escritura1 = fd1 [1];
	escritura2 = fd2 [1];
	escritura3 = fd3 [1];
	escritura4 = fd4 [1];
	//Escribimos en uno de los pipes
	while((cantBytes = read(file,buffer,BUFFER)) > 0){
		write(escritura1,buffer,cantBytes);
	}
	cantBytes = 0;
	close(file);

	for(i=0; i<cantHijos; i++){
		switch(fork()){
			case 0 :
				if(i!=cantHijos-1){
					//Cerramos la lectura/escritura
					close(escritura1);
					close(lectura2);
					close(escritura3);
					close(escritura4);
					close(lectura3);
					close(lectura4);	
					//Hijos normales
					printf("PID hijo: %d - PID Padre: %d \n", getpid(), getppid());
					if(i==0){
						//Leemos del fd1 y escribimos en el fd2
						while((cantBytes = read(lectura1, buffer, BUFFER)) > 0){
							write(escritura2, buffer, cantBytes);
							break;
						}
						cantBytes = 0;
					}
					else{
						//Leemos del fd2 y escribimos en el fd2
						while((cantBytes = read(lectura2, buffer, BUFFER)) > 0){
							write(escritura2, buffer, cantBytes);
							break;
						}
						cantBytes = 0;
					}
					close(lectura1);
					close(escritura2);
					return;
				}
				else{	
					//Cerramos la lectura/escritura
					close(lectura1);
					close(escritura2);
					close(lectura3);
					close(lectura4);
					//Hijo final (monitor)
					printf("PID hijo monitor: %d - PID Padre: %d \n", getpid(), getppid());
					//Leemos del fd2 y escribimos en el fd3
					while((cantBytes = read(lectura2, &buffer, sizeof(char))) > 0){
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
						write (escritura3, vectorLetras, 15*sizeof(int));
						write (escritura4, vectorParalelo, 15*sizeof(int));
						break;
					}
					cantBytes = 0;
					close(escritura3);
					close(escritura4);
					close(lectura2);
					close(escritura1);
					close(lectura3);
					close(lectura4);
					return;
				}
				break;
		}
	}
	//Cerramos la lectura/escritura
	close(escritura1);
	close(escritura2);
	close(lectura1);
	close(lectura2);
	close(escritura3);
	close(escritura4);
	//Leemos los datos ordenados e imprimimos
	read(lectura3, vectorLetras, sizeof(vectorLetras));
	read(lectura4, vectorParalelo, sizeof(vectorLetras));
	for(i=0;i<15;i++){
		porcentaje=(vectorLetras[i]*100)/palabrasTotales;
		printf("%i palabras con  %i caracteres - %2.f %c \n",vectorLetras[i],vectorParalelo[i],porcentaje,37);
	}
	//Cerramos la lectura/escritura
	close(lectura3);
	close(lectura4);
}
