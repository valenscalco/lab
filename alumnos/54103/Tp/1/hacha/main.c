#include "hacha.h"

int main (int argc, char ** argv ){
	
	char *aux;
	int fd,i=0,j,k=0,file1,file2,file3,file4;
	char buffer;
	if (argc==1){
	printf ("Ingrese los argumentos: \n");
	exit(EXIT_SUCCESS);
	}
	
	fd=open( argv[1],O_RDWR, NULL );	
		if(fd==-1){
			perror("error al abrir el archivo");
		}
		while(read(fd,&buffer,1)>0){
		i++;
		}
	j=i/4;
	printf("\nLa cantidad de bytes del archivo es:%d\n ",i);	
	aux=calloc(j,1);
	fd=open( argv[1],O_RDWR, NULL );
	while(read (fd,aux,j)){
		k++;
		if(k==1){
		file1=open("part1",O_CREAT| O_RDWR, 0644);
		write(file1,aux,j);
		}
		else if(k==2){
		file2=open("part2",O_CREAT| O_RDWR, 0644);
       	        write(file2,aux,j);
                }     
		else if(k==3){
                file3=open("part3",O_CREAT| O_RDWR, 0644);
                write(file3,aux,j);
                }     
	
		else if(k==4){
		file4=open("part4",O_CREAT| O_RDWR, 0644);
       	        write(file4,aux,j);
	               	while(read(fd,aux,1)>0){
				write(file4,aux,1);
				}     	
			break;
		}	

	}
	close(fd);
	close(file1);
	close(file2);
	close(file3);
	close(file4);
	return 0;

}  
