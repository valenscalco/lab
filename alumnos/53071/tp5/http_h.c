#include "http_h.h"

void *http(void *sd_conn){

    char *ruta = "archivos/";
    int fd, leido, leido2,sdc;
    long longitud = 0;
    char buffer[1024];
    char buffer2[1024];
    char archivo[256];
    char mime[256]; 
    char *version = NULL;
    char *estado = NULL;
    char cabecera[512];
    char *version2 = "HTTP/1.0";

    sdc = *((int *)sd_conn);
    free(sd_conn);
    memset(buffer,0,sizeof(buffer));//uso esta funcion para rellenar todo el espacio de buffer 
    memset(buffer2,0,sizeof(buffer2));

    if ((leido = read(sdc, buffer, sizeof(buffer))) > 0){ //funcion para leer del descriptor de la conexion del socket y lo que lee lo guarda en buff
        memset(archivo,0,sizeof(archivo));
        memset(mime,0,sizeof(mime));
        version = URI(buffer,archivo,mime,ruta, &longitud); //funcion para identificar el archivo solicitado

        if (!(strncmp(buffer,"GET",3) == 0) && !(strncmp(buffer,"POST",4) == 0)){
            estado = "500 INTERNAL SERVER ERROR\n";
            write(sdc,estado,strlen(estado));
            exit(0);
        } else if (!(strncmp(version,"HTTP/1.0",8) == 0) && !(strncmp(version,"HTTP/1.1",8) == 0)){
            write(STDOUT_FILENO,version,sizeof version);
            estado = "ERROR VERSION --> HTTP/1.0 o HTTP/1.1\n";
            write(sdc,estado,strlen(estado));
            exit(0);
        }

        else if ((fd = open(archivo, O_RDONLY)) < 0){
            estado = "404 NOT FOUND\n";
            write(sdc,estado,strlen(estado));
        }

        else { 
            estado = "200 OK";

            leido2 = snprintf(cabecera, sizeof cabecera, "%s %s\nContent-Length: %ld\nContent-Type: %s\n\n", version2, estado, longitud, mime);


            write(sdc,cabecera,leido2);//este write me da la cabecera en la respuesta al cliente

            while((leido2 = read(fd, buffer2, sizeof buffer2)) > 0){
                write(sdc,buffer2,leido2);//este write me muestra la solicitud (request) que se le hace al servidor
                if (strncmp(buffer,"POST",4)==0){
                printf("Content-Length: %ld\nContent-Type: %s\n\n",longitud, mime); 
                }
                memset(buffer2,0,sizeof(buffer2));
            }
            close(fd);
            close(sdc);
            pthread_exit(NULL);

        }

    } 

    close(fd);
    close(sdc);
    pthread_exit(NULL);

}
