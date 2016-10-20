#include "http_h.h"

char *URI (char *buffer,char *archivo, char *mime, char *ruta, long *longitud){

	int fd,leido;
	char buffer2[1024];
    memset(buffer2,0,sizeof(buffer2));
	char buffer3[1024];
	memset(buffer3,0,sizeof(buffer3));
	char buffer4[1024];
	memset(buffer4,0,sizeof(buffer4));
	char bufferleido[256];
	memset(bufferleido,0,sizeof(bufferleido));
	char version[256];
	memset(version,0,sizeof(version));
	char archivo2[1024];
	memset(archivo2,0,sizeof(archivo2));
	char extensionaux[256];
	memset(extensionaux,0,sizeof(extensionaux));
	char extension[1024];
	memset(extension,0,sizeof(extension));
	char mime2[1024];
	memset(mime2,0,sizeof(mime2));

	strncpy(buffer2,buffer,strlen(buffer));

	printf ("%s\n",buffer);
	
	strtok_r(buffer2," ",(char **)&version);//metodo get
	strtok_r(NULL," ",(char **)&version);
	
	strcpy (buffer3 , strtok(buffer,"/"));
	strcpy(buffer3 ,strtok(NULL," ")); 
	strcpy(archivo2, buffer3); // el nombre del archivo que solicito el cliente

	strncpy(extensionaux,archivo2,strlen(archivo2));

	strcpy(buffer4, strtok(extensionaux,"."));
	strcpy(buffer4, strtok(NULL," "));
	
	
	if (buffer4 == NULL){
	strcpy(extension, "error");
	}else {
		strcpy(extension, buffer4);
	}

    strcpy(mime2,types(extension));
    
	strncpy(mime,mime2,strlen(mime2));
	strncpy(archivo,ruta,256);
	strncat(archivo,archivo2,256);

	if ((fd = open(archivo,O_RDONLY)) != -1){ // si el archivo existe
			
		while ((leido = read(fd,bufferleido,sizeof(bufferleido))) > 0)//despues ver llamada a sistema fstat

			*longitud = *longitud + leido;
			
			close (fd);
	}

	return *(char **)version;
} 
