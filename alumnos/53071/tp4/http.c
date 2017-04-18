#include "http.h"

void http(int sd_conn, struct sockaddr * cliente, char *ruta){
	
	int fd, leido, leido2;
	long longitud = 0;
	char buffer[1024];
	char buffer2[1024];
	char archivo[256];
	char mime[256]; 
	char *version = NULL;
	char *estado = NULL;
	char cabecera[512];
	char *version2 = "HTTP/1.1";

	memset(buffer,0,sizeof(buffer));//uso esta funcion para rellenar todo el espacio de buffer 
	memset(buffer2,0,sizeof(buffer2));

	if ((leido = read(sd_conn, buffer, sizeof(buffer))) > 0){ //funcion para leer del descriptor de la conexion del socket y lo que lee lo guarda en buff
		memset(archivo,0,sizeof(archivo));
		memset(mime,0,sizeof(mime));
		version = URI(buffer,archivo,mime,ruta, &longitud); //funcion para identificar el archivo solicitado
		
		if (!(strncmp(buffer,"GET",3) == 0)){
			estado = "500 INTERNAL SERVER ERROR\n";
			write(sd_conn,estado,strlen(estado));
			exit(0);
		} else if (!(strncmp(version,"HTTP/1.1",8) == 0)){
			estado = "ERROR VERSION --> HTTP/1.1\n";
			write(sd_conn,estado,strlen(estado));
			exit(0);
		}

		else if ((fd = open(archivo, O_RDONLY)) < 0){
			estado = "404 NOT FOUND\n";
			write(sd_conn,estado,strlen(estado));
		}

		else { 
			estado = "200 OK";

			leido2 = snprintf(cabecera, sizeof cabecera, "%s %s\nContent-Length: %ld\nContent-Type: %s\n\n", version2, estado, longitud, mime);


		    write(sd_conn,cabecera,leido2);//este write me da la cabecera en la respuesta al cliente

			while((leido2 = read(fd, buffer2, sizeof buffer2)) > 0){
				write(sd_conn,buffer2,leido2);//este write me muestra la solicitud (request) que se le hace al servidor
				memset(buffer2,0,sizeof(buffer2));
			}
			close(fd);
			close(sd_conn);
		}

	} 

	close(fd);
	close(sd_conn);

}
