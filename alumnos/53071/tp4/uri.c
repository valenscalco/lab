#include "http.h"

char *URI (char *buffer,char *archivo, char *mime, char *ruta, long *longitud){

	int fd,leido;
	char *buffer2 = malloc(1024*sizeof(char));
	char *buffer3 = malloc(256*sizeof(char));
	char *buffer4 = malloc(256*sizeof(char));
	char bufferleido[256];
	memset(bufferleido,0,sizeof(bufferleido));
	char *version = malloc(256*sizeof(char));
	char *archivo2;
	char extensionaux[256];
	memset(extensionaux,0,sizeof(extensionaux));
	char *extension = malloc(256*sizeof(char));

	strncpy(buffer2,buffer,strlen(buffer));

	printf ("%s\n",buffer);
	
	strtok_r(buffer2," ",&version);//metodo get
	strtok_r(NULL," ",&version);
	
	buffer3 = strtok(buffer,"/");
	buffer3 = strtok(NULL," "); 
	archivo2 = buffer3; // el nombre del archivo que solicito el cliente

	strncpy(extensionaux,archivo2,strlen(archivo2));

	buffer4 = strtok(extensionaux,".");
	buffer4 = strtok(NULL," ");
	
	if (buffer4 == NULL){
	extension = "error";
	}else {
		extension = buffer4;
	}

	if (strcmp(extension,"html") == 0){
			strncpy(mime,"text/html",256);
	}

	if (strcmp(extension,"jpg") == 0){
			strncpy(mime,"image/jpeg",256);
	}

	if (strcmp(extension,"pdf") == 0){
			strncpy(mime,"application/pdf",256);
	}

	if (strcmp(extension,"txt") == 0){
			strncpy(mime,"text/plain",256);
	}

	if (strcmp(extension,"png") == 0){
			strncpy(mime,"image/png",256);
	}

	if (strcmp(extension,"error") == 0){
		strncpy(mime,"error",256);
	}
	
	strncpy(archivo,ruta,256);
	strncat(archivo,archivo2,256);

	if ((fd = open(archivo,O_RDONLY)) != -1){ // si el archivo existe
			
		while ((leido = read(fd,bufferleido,sizeof(bufferleido))) > 0)

			*longitud = *longitud + leido;
			
			close (fd);
	}

	return version;
}
