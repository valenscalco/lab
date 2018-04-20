#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char **argv)
{
	int leer ;
	char buff [2000], buffcpy [2000], buffcpy1 [2000] ; 
	char esp [] = " \t\n", pun [] = ".", cesp [] = "\303" ;
	char *palabras, *oraciones, *cespeciales ;
	int contpal = 0, contora = 0, contces = 0 ;
	//arc = open ( "/home/hp/Escritorio/compu2/lab/tps/tp1/noticia1", O_RDONLY ) ;	
	//	if( arc != -1 ) {
	//		printf ( "El archivo existe: \n" ) ;
	while ( (leer = read (0,buff,2000) ) > 0 )  {
		//write ( 1,buff,leer ) ; 
		strncpy ( buffcpy,buff,2000 ) ;
		strncpy ( buffcpy1,buffcpy,2000 ) ;
   		printf( "buffcpy=%s\n",buffcpy );
   		printf( "buffcpy1=%s\n",buffcpy1 );
		palabras = strtok ( buff, esp ) ;
		while ( ( palabras=strtok (NULL,esp) ) != NULL ) {
			contpal++;
    		}
		oraciones = strtok ( buffcpy,pun );
		while ( ( oraciones=strtok (NULL,pun) ) != NULL ) {
			contora++;
		}
		cespeciales = strtok ( buffcpy1,cesp );
		while ( ( cespeciales=strtok (NULL,cesp) ) != NULL ) {
			contces++;
		}
	printf ( "La cantidad de palabras es: %d\n", contpal ) ;
	printf ( "La cantidad de oraciones es : %d\n", contora ) ;
	printf ( "La cantidad de palabras con caracteres especiales es : %d\n", contces ) ;
	}	
	return 0;
}
