#include <stdio.h>
#include <string.h>
#include <unistd.h>

	int main(int argc, char **argv){
	char buff[303], tokbuff[303]="\0"; 
   	char s1[2] = " ";//Para palabras.
	char s2[64]="ÁÉÍÓÚÜÑÄËḮÖäëïöáéíóúñü";//Para contar caracteres especiales.Yo considero solo los acentos como caracteres espeiales|ñ|Dieresis
	char s3[50]=".";//Para oraciones. 
	char *leido;
	char var2[64]="\0";
   	int cntp=1,cnte=0,cnto=0,var;


while(var=read(STDIN_FILENO,buff,sizeof(buff))>0){//var: Es el retorno de READ que va a ser la cantidad de bits que puedo leer de mi FD. BUFF: es un puntero a la direccion de memoria donde voy a escribir donde voy a escribir esos datos. SIZEOF(BUFF) es cuanto voy a leer.

strcpy(tokbuff,buff);//Copio el Buffer xq sino me lo pisa
leido = strtok( tokbuff, s1 );    // Primera llamada u ocurrecia => Primer token

	while( (leido = strtok( NULL, s1 )) != NULL ){    // Posteriores llamadas
 	//printf("%s\n\n",leido);
 	cntp++;
	}
strcpy(tokbuff,buff);
leido = strtok(tokbuff, s2);

	while( (leido = strtok( NULL, s2 )) !=NULL ){
	cnte++;
	//printf("%s\n\n",leido);
	
	}
strcpy(tokbuff,buff);
leido = strtok(tokbuff, s3);

	while( (leido = strtok( NULL, s3 )) !=NULL ){
	cnto++;
	//printf("%s\n",leido);
	}
}

	sprintf(var2,"Total de Palabras: %8d \n",cntp+1);//printf("Total palabra: %i\n",cntp+1);
	write(STDOUT_FILENO,var2,sizeof(var2));
	memset(var2,0,sizeof var2);

	sprintf(var2,"Total de Caracteres Especiales: %8d \n",cnte);//	printf("Total Caracteres Especiales: %i\n",cnte);
	write(STDOUT_FILENO,var2,sizeof(var2));
	memset(var2,0,sizeof var2);

	sprintf(var2,"Total de Oraciones: %8d \n",cnto);//	printf("Total de oraciones: %i\n",cnto);
	write(STDOUT_FILENO,var2,sizeof(var2));

   return 0;
}
