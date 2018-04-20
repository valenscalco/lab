#include "tp2.h"


void c_cat(int argc, char *argv[]){

	setlocale(LC_ALL, "spanish");
	char buffer[80], buffer2[1], *cadena, cant_palabras[10];
	int nread, ph[2],hp[2], ph2[2], palabras=0, file_salida, pid1, pid2;
	int status1, status2;

		pipe(ph);
		pipe(ph2);
		pipe(hp);


		if((pid1=fork()) == 0){
			printf("Hijo1  - PID(%d) PPID(%d)\n", getpid(), getppid());
			close(ph[1]);
			close(ph2[1]);
			memset(buffer, 0, sizeof buffer);
		       	while((nread = read(ph[0], buffer, sizeof buffer)) > 0 ){
		       		//write(1, buffer, nread);
				char copia[nread];
				strcpy(copia,buffer);
				cadena = strtok(copia," \t\n");
				while((cadena =strtok(NULL," \t\n"))!= NULL){
					palabras++;
				}			
			}
			palabras++; //Por la ultima palabra
			close(hp[0]);
			close(ph2[0]);
			close(ph[0]);

			sprintf(cant_palabras,"%d", palabras);
			write(hp[1],cant_palabras,10);
						
			close(hp[1]);
			//exit(0);
		}else{
		if ((pid2=fork()) == 0){
			printf("Hijo2  - PID(%d) PPID(%d)\n", getpid(), getppid());
			close(ph2[1]);
			close(ph[1]);
			close(hp[1]);
			char letra, auxletra;
			file_salida = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC,0664);				
			memset(buffer2, 0, sizeof buffer2);
			while((nread = read(ph2[0], buffer2, sizeof buffer2)) > 0 ){
				letra = buffer2[0];	
				if(isupper(letra)){						
					write(file_salida,buffer2,nread);
					auxletra= letra;
				}else if(islower(letra)){
					if(isupper(auxletra)){
						  auxletra = toupper(letra);
						  buffer2[0] = auxletra;
		  			          write(file_salida,buffer2,nread);
					}else{
						 auxletra = letra;
						 buffer2[0] = auxletra;
		   			         write(file_salida,buffer2,nread);
					}
				}else if(isspace(letra)){
	 				buffer2[0] =letra;
					write(file_salida,buffer2,nread);
					auxletra= letra;
				}else if(isdigit(letra)){
	      				buffer2[0] =letra;
					write(file_salida,buffer2,nread);
					auxletra= letra;
				}else if(ispunct(letra)){
					buffer2[0] =letra;
					write(file_salida,buffer2,nread);
					auxletra= letra;
				}/*else if(letra==225 || letra==233 || letra==237 || letra==243 || letra==250){  
					 letra=letra-32;
					 auxletra= letra;
					 buffer2[0]= auxletra;
					 write(file_salida,buffer2,nread);
					//225, 233,237,243,250=> 193,201,205,2011,218
				}*/else{						
					auxletra= letra;
					buffer2[0]= auxletra;
					write(file_salida,buffer2,nread);
								
				}
				    
			}  
			close(ph2[0]);
			close(ph[0]);
			close(hp[0]);
			close(file_salida);
		}else{
			printf("Padre2 - PID(%d) PPID(%d)\n", getpid(), getppid());			
			close(ph[0]);
			close(ph2[0]);

			memset(buffer, 0, sizeof buffer);
		        while((nread = read(STDIN_FILENO, buffer, sizeof buffer)) >0){
		        	write(ph[1], buffer, nread);
		        	write(ph2[1], buffer, nread);
			}
			close(ph[1]);
			close(ph2[1]);
			close(hp[1]);

			read(hp[0], cant_palabras, sizeof cant_palabras);
			printf("Cantidad de palabras: %s\n", cant_palabras);
			close(hp[0]);

			waitpid(pid1, &status1, 0);
			waitpid(pid2, &status2, 0);
			
		}
		}
	

}


