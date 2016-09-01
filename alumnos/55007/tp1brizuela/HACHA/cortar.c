#include "cortar.h"
//para ejecutar ./cortar <archivo> <n> <parte*>
int main(int argc,char *argv[])
{
	int tamano,i,j,fd,parte[15],n;
	char *buf[15];
	int fdp[15],k=0;
	fd=open(argv[1],O_RDWR);
	tamano=lseek(fd,0,SEEK_END);
	n=atoi(argv[2]);
	lseek(fd,0,SEEK_SET);
	for(i=0;i<n;i++)
	{	
		if(i==(n-1))
		{
			parte[i]=(tamano/n) + (tamano%n);
			buf[i]=(char *)malloc(parte[i]*sizeof(char));
                        read(fd,buf[i],parte[i]);
		}
		else{
			parte[i]=tamano/n;
			buf[i]=(char *)malloc(parte[i]*sizeof(char));
			read(fd,buf[i],parte[i]);
			lseek(fd,(i+1)*(parte[i]),SEEK_SET);//probar sin lseek
		}
	}
	close(fd);
	for(j=3 ; j<n+4 ; j++)//le sumo 4 porque 3 son argumentos fijos
	{
		fdp[k]=open(argv[j],O_CREAT|O_RDWR,0644);
		write(fdp[k],buf[k],parte[k]);
		k++;
	}
return 0;
}
