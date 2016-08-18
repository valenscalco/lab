#include "servicio.h"

/* Función que crea la cantidad de hijos deseada por el usuario*/
void crearHijos(int cantHijos, int menorMayor, char * archivo, int palabrasTotales){
	int i;
	int cantBytes;
    int bytesTexto=0;
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
    int parte;

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
    for (i=0; i<sizeof(buffer); i++) {
        //Guardo en una variable la cantidad total de bytes del texto
        bytesTexto++;
    }
    //Guardo en una variable la cantidad de bytes que va a procesar cada hijo
    parte = bytesTexto/cantHijos;
    printf("Parte: %i %i \n", bytesTexto, parte);
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
						histograma(lectura2,buffer,vectorLetras,vectorParalelo,menorMayor);
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
