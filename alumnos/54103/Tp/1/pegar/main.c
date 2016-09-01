#include "pegar.h"

int main (int argc, char ** argv ){
	
	int i=0,j=0,k=0,l=0,o,fd,file1,file2,file3,file4;
	char buffer;
	//char buff[80];
	if (argc==1){
		//read (STDIN_FILENO,buff,sizeof buff);
		printf("Ingrese los argumentos correctamentes");
		exit(EXIT_SUCCESS);
	}
	printf("el numero de argumentos es: %d\n" , argc);
	printf("Sus argumentos son: %s\t%s\t%s\t%s\t\n",argv[1], argv[2], argv[3], argv[4]);	
	
	
	file1=open(argv[1],O_RDWR,NULL);
	while(read(file1,&buffer,1)>0){
		i++;
		}
	printf("El tamaño del archivo es: %d\n",i);
	
	
	file2=open(argv[2],O_RDWR,NULL);
        while(read(file2,&buffer,1)>0){
                j++;
                }
        printf("El tamaño del archivo es: %d\n",j);


	file3=open(argv[3],O_RDWR,NULL);
        while(read(file3,&buffer,1)>0){
                k++;
                }
        printf("El tamaño del archivo es: %d\n",k);


 	file4=open(argv[4],O_RDWR,NULL);
        while(read(file4,&buffer,1)>0){
                l++;
                }
        printf("El tamaño del archivo es: %d\n",l);
	
	
	o=i+j+k+l;
	printf("El archivo original poseia una tamaño de %d\n", o);
	
	file1=open(argv[1],O_RDWR, NULL);
	fd=open("dog.ppm",O_WRONLY|O_CREAT, 0644);;
	while(read(file1,&buffer,1)>0){
		write(fd,&buffer,1);
	}
	close(fd);

	file2=open(argv[2],O_RDWR, NULL);
        fd=open("dog.ppm",O_APPEND | O_RDWR, 0644);;
        while(read(file2,&buffer,1)>0){
                write(fd,&buffer,1);
        }
        close(fd);
	
	file3=open(argv[3],O_RDWR, NULL);
        fd=open("dog.ppm",O_APPEND | O_RDWR, 0644);;
        while(read(file3,&buffer,1)>0){
                write(fd,&buffer,1);
        }
        close(fd);

	file4=open(argv[4],O_RDWR, NULL);
        fd=open("dog.ppm",O_APPEND | O_RDWR, 0644);;
        while(read(file4,&buffer,1)>0){
                write(fd,&buffer,1);
        }
        close(fd);

	close(file1);
	close(file2);
	close(file3);
	close(file4);

	return 0;
	
}
