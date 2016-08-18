#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define _DEBUG_ 1

#define GOTO_ERR(errno, msg) do { ret = errno; perror(msg); goto error; } while (0);

struct opts {
    int nparts;
    char filename[50];
};


int set_opts(int argc, char **argv, struct opts *o);
long get_filesize(char *filename);


int main(int argc, char **argv)
{
    int nread, nwrite;
    char *buff;
    int mem_size, file_size;
    struct opts o;
    int fdin, fd;
    char filename[60];
    int i;
    int ret = 0;

    if (set_opts(argc, argv, &o) < 0) {
        fprintf(stderr, "Usage: %s [-n n_parts] [-f filename]\n", argv[0]);
        return 1;
    }

    #if _DEBUG_
    printf("[INFO] Opciones= filename: %s, nparts: %d\n", o.filename, o.nparts);
    #endif

    if ((file_size = get_filesize(o.filename)) < 0) {
        GOTO_ERR(2, "get_filesize()");
    }

    if ((fdin = open(o.filename, O_RDONLY)) < 0) {
        GOTO_ERR(3, "open()");
    }

    mem_size = round(file_size / o.nparts) * sizeof (char);

    if ((buff = malloc(mem_size)) == NULL) {
        GOTO_ERR(4, "malloc()");
    }

    for (i = 0; i < o.nparts; i++) {
        if ((nread = read(fdin, buff, mem_size)) < 0) {
            GOTO_ERR(5, "read()");
        }
    
        memset(filename, 0, sizeof filename); 
        snprintf(filename, sizeof filename, "%s-%d", o.filename, i);
        
        if ((fd = open(filename, O_CREAT | O_WRONLY, 0644)) < 0) {
            GOTO_ERR(6, "open()");
        }

        if ((nwrite = write(fd, buff, nread)) < 0) {
            GOTO_ERR(7, "write()");
        }
       
        #if _DEBUG_
        printf("[INFO] Nro de Bytes copiados en %s: %d\n", filename, nwrite);
        #endif
        
        close(fd);
    }
    
    #if _DEBUG_
    printf("[INFO] Nro de archivos creados %d\n", o.nparts);
    #endif

error:
    if (fd > 0) close(fd);
    if (fdin > 0) close(fdin); 
    if (buff) free(buff);
    return ret;
}


int set_opts(int argc, char **argv, struct opts *o)
{
    int opt;
    int flags_cnt = 0;

    while ((opt = getopt(argc, argv, "n:f:")) != -1) {
        switch (opt) {
            case 'n':
                o->nparts = atoi(optarg);
                flags_cnt++;
                break;

            case 'f':
                memset(o->filename, 0, sizeof o->filename);
                strncpy(o->filename, optarg, sizeof o->filename);
                flags_cnt++;
                break;

            default: /* '?' */
                return -1;
        }
    }

    if (flags_cnt != 2) {
        return -1;
    }

    return 0;
}

long get_filesize(char *filename)
{
    struct stat finfo;

    if (stat(filename, &finfo) < 0) {
        return -1;
    }

    return finfo.st_size;
}

