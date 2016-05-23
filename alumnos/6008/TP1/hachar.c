#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#define SIZE 60000

int main(int argc, char **argv)
{
	int fd,fd2,n=0,leer;
	char buffer[SIZE];
	char tmp[100];
	fd = open (argv[1],O_RDONLY);
	
	while ((leer = read(fd,buffer,SIZE)) > 0){
		snprintf(tmp, 100, "%s-%d", argv[1],n);
		fd2 = open (tmp,O_RDWR|O_TRUNC|O_CREAT, S_IRUSR|S_IWUSR);
		write(fd2,buffer,leer);
		close(fd2);
		n++;
	}
	
	close(fd);

	return 0;
}
