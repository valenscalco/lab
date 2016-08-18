#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>

#define _DEBUG_ 1
#define BUFF_SIZE 1024


int main(int argc, char **argv)
{
    int nread, nwrite;
    char buff[BUFF_SIZE], buff_in[BUFF_SIZE];
    int fd, fdin;
    char *filename;

    if (argc != 2) {
        fprintf(stderr, "Usage: ls parts | ./%s [file_name]\n", argv[0]);
        return 1;
    }

    if ((fd = open(argv[1], O_CREAT | O_WRONLY, 0644)) < 0) {
        perror("open()");
        return 2;
    }

    memset(buff_in, 0, sizeof buff_in);
    read(STDIN_FILENO, buff_in, sizeof buff_in);

    filename = strtok(buff_in, " \n\t");
    do {
        #if _DEBUG_
        printf("[INFO] Leyendo %s ...\n", filename);
        #endif
 
        if ((fdin = open(filename, O_RDONLY)) <0) {
            perror("open()");
            return 3;
        }
       
        while ((nread = read(fdin, buff, sizeof buff)) > 0) {
            if ((nwrite = write(fd, buff, nread)) < 0) {
                perror("write()");
                return 4;
            }
        }
        
        close(fdin);
    } while ((filename = strtok(NULL, " \n\t")) != NULL);
    
    #if _DEBUG_
    printf("[INFO] Archivo creado \"%s\"\n", argv[1]);
    #endif

    if (fd > 0) close(fd);
    return 0;
}

