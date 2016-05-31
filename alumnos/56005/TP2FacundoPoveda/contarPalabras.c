#include "servicio.h"

int contarPalabras (char * archivo){
         int i;
         int cantPalabras = 0;
         int cantLetras = 0;
         int file;
         char buffer[BUFFER];
         //Abrimos el archivo con permisos de lectura 
         file = open(archivo, O_RDONLY, NULL);
         //Leemos el archivo
         read(file, &buffer, BUFFER);
         for(i = 0; i < strlen(buffer); i++){
                 if(buffer[i] == ' ' && i > 0 && buffer[i - 1] != ' '){
                         cantPalabras++; }
                 if(buffer[i] != ' ' || buffer[i] !='\n'){
                         cantLetras++;
                 }
         }
         printf("Cantidad de letras totales: %i", cantLetras);
         printf("\n");
         printf("Cantidad de palabras totales: %i", cantPalabras);
         printf("\n");
         //Cerramos el archivo abierto
         close(file);
    return cantPalabras;
}
