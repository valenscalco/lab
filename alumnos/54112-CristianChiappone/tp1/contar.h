#ifndef _contar_h_
#define _contar_h

int contar(int leido,char* buffer, char* delimitador){
        int contador=0;
        char *cadena,copia[leido];

        strcpy(copia,buffer);
        cadena = strtok(copia,delimitador);
        while(cadena != NULL){
                cadena=strtok(NULL,delimitador);
                contador++;
        }
        return contador;
}

#endif 

