#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char **argv){

	int pid1, pid2;
	char buff[1500]="\0", tokbuff[380]="\0";
	char s1[7] = " .\n\t";
	char *leido;
	int cant_leida;
	int cntp=1,var,descriptor_entrada,descriptor_salida;
	int opcion;
	int bandera=0;
//	char var2[64]="\0";
	char *nomentrada,*nomsalida;
	int padrehijo1[2],padrehijo2[2], hijopadre[2];
	int flag1 =0;
	int flag2 =0;
	char cadena[800]; 
							
				while ((opcion = getopt (argc, argv, "i:o:") != -1)){
				switch (opcion) {
					case 'i':
						bandera=1;
						nomentrada = optarg;
						printf("-i = %s \n",nomentrada);
						break;
					case 'o':
						nomsalida = optarg;
						printf("-o = %s \n",nomsalida);
						break;	
					 
				}
		 	}

	pipe(padrehijo1);//declaro las conexiones de las tuberias
	pipe(padrehijo2);
	pipe(hijopadre);
	/////////
	//hijo 1///CUENTA CANTIDAD DE PALABRAS
	/////////
	pid1=fork();
	if(pid1==0){
				printf("PID del Hijo 1: %d\n", getpid());
				while((var=read(padrehijo1[0],buff,sizeof buff)>0)){//var: Es el retorno de READ que va a ser la cantidad de bits que puedo leer de mi FD. BUFF: es un puntero a la direccion de memoria donde voy a escribir donde voy a escribir esos datos. SIZEOF(BUFF) es cuanto voy a leer.
					strcpy(tokbuff,buff);//Copio el Buffer xq sino me lo pisa
					leido = strtok( tokbuff, s1 );    // Primera llamada u ocurrecia => Primer token
						while((leido = strtok( NULL, s1 )) != NULL ){    // Posteriores llamadas
					 	//printf("%s\n\n",leido);
					 	cntp++; 
				}
				//sprintf(var2,"Total de Palabras contadas por el Padre: %8d \n\n",cntp+1);//printf("Total palabra: %i\n",cntp+1);
				//cntp++;
				write(hijopadre[1],&cntp,sizeof(cntp));//Le manda al Padre 
				sleep(2);
				close(hijopadre[1]);	
				
				}	
		close(padrehijo1[1]);
		close(hijopadre[0]);			
		return 0;
	}
	/////////
	//hijo 2///HACE MAYUSCULA CIERTAS PALABRAS
	/////////
	pid2=fork();
	if(pid2==0){
			
			printf("PID del Hijo 2: %d\n", getpid());
			int i,var; 
			char pal1[30]="preexistentes";	
			char pal2[30]="Argentina";
			memset(cadena, 0, sizeof(cadena));
			while((var=read(padrehijo2[0],cadena,sizeof cadena)>0)){	
				

				leido = strtok(cadena, " ,");    // Primera llamada u ocurrecia => Primer token
				//printf("%s", leido);
				while( leido != NULL ){    // Posteriores llamadas
		 			//printf("%s\n\n",leido);
		 			strcpy(buff,leido);//Copio el Buffer xq sino me lo pisa	
		 			flag1=strcmp(buff, pal1)==0;
		 			flag2=strcmp(buff, pal2)==0;
		 			if(flag1||flag2){
					    for(i = 0; i < sizeof buff; i++){ 
					    	buff[i] = toupper(buff[i]);
						}  
						
					}
					leido = strtok(NULL, " ,");
					printf("%s ", buff);
				} }

	close(padrehijo2[1]);
  	descriptor_salida = open( nomsalida, O_CREAT|O_RDWR|O_APPEND, 0666);//Se lo intenta mandar al padre 
  	write(descriptor_salida,buff,sizeof buff);
  	return 0;
	}
	/////////
	//Padre//
	/////////
	close(padrehijo1[0]);
	close(padrehijo2[0]);
	close(hijopadre[1]);

	//printf("EL TOTAL DE PALABRAS ES: \n" );
printf("PID del Padre: %d\n", getpid());
	//sleep(1);


	if(bandera == 0){//Cuando Bandera es 0, uso CAT
		while((cant_leida = read(STDIN_FILENO,buff,sizeof buff))>0){
			write(padrehijo1[1],buff,sizeof buff);
			write(padrehijo2[1],buff,sizeof buff);
		}	
		close(padrehijo1[1]);
		close(padrehijo2[1]);
	}else{//hay que abrirlo mediante un OPEN
		
		descriptor_entrada=open(nomentrada, O_CREAT|O_RDWR|O_APPEND);
		while(( cant_leida = read(descriptor_entrada,buff,sizeof buff))>0){
			write(padrehijo1[1],buff,sizeof buff);
			write(padrehijo2[1],buff,sizeof buff);

		
	}	close(padrehijo1[1]);
		close(padrehijo2[1]);
}
sleep(1);

read(hijopadre[0],&cntp,sizeof cntp);
close(hijopadre[0]);
printf("EL TOTAL DE PALABRAS ES: %d\n",cntp+1);

printf("PID del Padre: %d\n", getpid());

return 0;

}
