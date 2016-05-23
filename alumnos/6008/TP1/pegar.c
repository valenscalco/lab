#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#define SIZE 60000

int main(int argc, char **argv)
{
	int leer,fd,fd2;
	char buffer[512],img[SIZE];
	char * pch;
	fd = open (argv[1],O_RDWR|O_TRUNC|O_CREAT, S_IRUSR|S_IWUSR);
	read(0,buffer,5120);
	pch = strtok (buffer,"\n");
	while (pch != NULL){
		fd2 = open (pch,O_RDWR);
		leer=read(fd2,img,SIZE);
		write(fd,img,leer);
		close(fd2);
		pch = strtok (NULL, "\n");
	}
	close(fd);

	return 0;
}
