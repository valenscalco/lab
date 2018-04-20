#include "tp2.h"


void c_getopt(int argc, char *argv[]){

	setlocale(LC_ALL, "spanish");
	char buffer[80], buffer2[1], *cadena, cant_palabras[10];
	int nread, ph[2],hp[2], ph2[2], palabras=0, file, file_salida, pid1, pid2;
	int status1, status2;

		pipe(ph);
		pipe(ph2);
		pipe(hp);

		pid1 = fork();
		if(pid1 == 0){
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
			close(ph[0]);

			sprintf(cant_palabras,"%d", palabras);
				write(hp[1],cant_palabras,10);						
			close(hp[1]);
			exit(0);
		}

		pid2 = fork();

		if (pid2 == 0){
			printf("Hijo2  - PID(%d) PPID(%d)\n", getpid(), getppid());
			close(ph2[1]);
			close(ph[1]);
			close(hp[1]);
			char letra, auxletra;
			file_salida = open(argv[4],O_WRONLY | O_CREAT | O_TRUNC,0664);				
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
				}else{						
					auxletra= letra;
					buffer2[0]= auxletra;
					write(file_salida,buffer2,nread);
								
				}
				//else if(letra==163 || letra==233){ 
				//	letra='u';
				//	 auxletra= letra;
				//	 buffer2[0]= auxletra;
				//	 write(file_salida,buffer2,nread);
				//}
				    
			}
			close(ph2[0]);
			close(ph[0]);
			close(hp[0]);
			close(file_salida);
		}

		 if ((pid1 > 0) && (pid2 > 0)) {
			printf("Padre1 - PID(%d) PPID(%d)\n", getpid(), getppid());			
			close(ph[0]);
			close(ph2[0]);
		
			file=open(argv[2], O_RDONLY,0777);
			memset(buffer, 0, sizeof buffer);
   			while((nread = read(file, buffer, sizeof buffer)) >0){
      				write(ph[1], buffer, nread);
      				write(ph2[1], buffer, nread);	
			}
			close(file);
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

