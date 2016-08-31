#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
//para ejecutar ./pegar <n> <parte-*> <final>
int main(int argc,char *argv[])
{
	int tamano[15],i,j,fd,n,total=0;
        char *buf[15];
        int fdp[15],k=0;
	n=atoi(argv[1]);
	for(j=2 ; j<n+2 ; j++)
        {
                fdp[k]=open(argv[j],O_RDWR);
                tamano[k]=lseek(fdp[k],0,SEEK_END);
		lseek(fdp[k],0,SEEK_SET);
                buf[k]=(char *)malloc(tamano[k]*sizeof(char)); 
		read(fdp[k],buf[k],tamano[k]);
		total=tamano[k] + total;
		k++;
	}
	fd=open(argv[n+2],O_CREAT|O_RDWR,0644);
	for(i=0;i<n;i++)
	{
		write(fd,buf[i],tamano[i]);
		lseek(fd,(i+1)*(tamano[i]),SEEK_SET);
	}
return 0;
}
