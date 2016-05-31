#include "servicio.h"

int main (int arg, char **argv){
	char * n;
	char * o;
	int numHijos;
	char * orden;
	int menorMayor=0;
	char * archivo;
    int palabrasTotales;

	//Leemos las opciones y se las pasamos a una variable
    archivo = argv[1];
    n = argv[2];
    numHijos=atoi(argv[3]);
    o = argv[4];
    orden=argv[5];

	//Contador de palabras totales
	palabrasTotales = contarPalabras(archivo);

	//Errores
	menorMayor = detectarErrores(n,o,numHijos,orden,menorMayor);

	//Creación de procesos padre-hijo y pipes
	crearHijos(numHijos,menorMayor,archivo,palabrasTotales);
	return 0;
}