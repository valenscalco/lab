#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>


int main(int argc, char **argv)
{
    char buffer[80000];
    char buffer2[80000];
    char buffer_sprin[8000];
    char buffer3[1];
    char * pch;
	

    int a[2];
    int b[2];
    int c[2];
    int d[2];
    int palabras = 0;
    int nread;
    int file;
    int bytes;
    int fd;

    pipe(a);
    pipe(b);
    pipe(c);
    pipe(d);

    switch (fork()) {

    case 0:

       //hijo 1
    	close(a[1]);
    	close(c[1]);
    	close(d[1]);
    	close(c[0]);
		memset(buffer, 0, sizeof buffer);
		do {
			nread = read(a[0], buffer, sizeof buffer);
			pch = strtok (buffer," ,.-\n\t");
			while (pch != NULL)
			  {
			  	pch = strtok (NULL, " ,.-\n\t");
				palabras++;
			  }
		} while (nread > 0);

	    close(a[0]);
	    close(b[0]);
    
	    sprintf(buffer_sprin,"palabras: %d", palabras);
	    write(b[1],buffer_sprin,80);

	    close(b[1]);

    	return 0;

    case -1: // error
        perror("fork()");
        return -1;

    default:

      	//padre

    	close(a[0]);

    	memset(buffer, 0, sizeof buffer);

	    do {
	        nread = read(STDIN_FILENO, buffer, sizeof buffer);
	        write(a[1], buffer, nread);
	        write(c[1], buffer, nread);
	    } while (nread > 0);

	    close(a[1]);
	    close(b[1]);
	    close(c[1]);
	    close(d[1]);

	    read(b[0],buffer_sprin, sizeof(buffer_sprin));
	    printf("%s\n", buffer_sprin);
	    
	    read(d[0],buffer3, sizeof(buffer3));
	    printf("%s\n", buffer3);

	    close(b[0]);
	    close(d[0]);

		if (fork() == 0)
		{
			//hijo 2

			close(a[1]);
			close(b[1]);
			close(c[1]);
			close(d[0]);

			file = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
			memset(buffer2, 0, sizeof buffer2);
			if (file < 0){
				perror ("unable to create:");
				return -1;
			}
			do {
				nread = read(c[0], buffer2, sizeof buffer2);
				for(int i=0;i<buffer2[i];i++){
					if(buffer2[i]>= 'a' && buffer2[i]<= 'z'){
					buffer2[i] -=32;
					}

				}

				write(file,buffer2,nread);


			} while (nread > 0);

			close(file);

			fd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0664);

			memset(buffer3, 0, sizeof buffer3);

			while ((bytes = read(fd, buffer3, sizeof buffer3))>0){

				printf("arr: %d\n", bytes);

				bytes++;

			}

			printf("aas:%d\n", bytes);


			sprintf(buffer3,"caracteres: %d", bytes);
	    	write(d[1],buffer3,80000);
						
	    	close(c[0]);
			close(d[1]);

		}


    }


    return 0;
}