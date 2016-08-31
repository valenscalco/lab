#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "servicio.h"

int abrir_archivo(char *file_name) {
    return open(file_name, O_RDWR, 0777);
}

void contar_palabras(char *line, int nchars, int fd_hijo_monitor[2]) {

    int i;
    int letras=0;

    /* ********* */

    for (i=0; i<nchars; i++) {
        /* Caracteres q aparecen en el texto */
        if ( line[i]!=32 && line[i]!=34 && line[i]!=59 && line[i]!=45 &&
             line[i]!=44 && line[i]!=46 && line[i]!=63 && line[i]!=10 ) {
            /* Si esta acentuada, no sumo la letra
             * [130,160,161,162,163]
             */
            letras++;
        } else {
            if (letras != 0) {
                close(fd_hijo_monitor[0]);                         /* cierro la lectura */
                write(fd_hijo_monitor[1], letras + "", sizeof letras);

                letras = 0;
            }
        }
    }
}

void lanzar_hijos(int cant, int fd_monitor_padre[2]) {

    int i;
    int leido = 0;
    int fd_file;

    int fd_monitor_hijo[2];
    int fd_hijo_monitor[2];

    pid_t pid_hijo;
    pid_t pid_monitor;

    char *file_name = "file.txt";
    char buffer_1[50];
    char buffer_2[50];
    char buffer_3[50];

    /* ********* */

    if (pipe(fd_monitor_hijo) < 0) {
        perror("pipe(fd_monitor_hijo)\n");
        exit(EXIT_FAILURE);
    }

    if (pipe(fd_hijo_monitor) < 0) {
        perror("pipe(fd_hijo_monitor)\n");
        exit(EXIT_FAILURE);
    }

    pid_monitor = fork();

    if (pid_monitor == 0) {
        /* PROCESO MONITOR */
        if ((fd_file = abrir_archivo(file_name))) {
            while ((leido = read(fd_file, buffer_1, sizeof buffer_1)) > 0) {
                close(fd_monitor_hijo[0]);                  /* cierro la lectura */
                write(fd_monitor_hijo[1], buffer_1, leido);

                close(fd_hijo_monitor[1]);                  /* cierro la escritura */
                read(fd_hijo_monitor[0], buffer_2, sizeof buffer_2);

                close(fd_monitor_padre[0]);                 /* cierro la lectura */
                write(fd_monitor_padre[1], buffer_2, sizeof buffer_2);
            }
        } else {
            perror("open()");
            exit(EXIT_FAILURE);
        }
        // exit(EXIT_SUCCESS);
    } else if (pid_monitor == -1) {
        perror("fork(monitor)");
        exit(EXIT_FAILURE);
    } else {
        /* DEMAS PROCESOS HIJOS */
        for (i=0; i<cant; i++) {
            if ((pid_hijo = fork()) == -1) {
                perror("fork(hijos)");
                exit(EXIT_FAILURE);
            } else if (pid_hijo == 0) {
                /* PROCESO HIJO */
                close(fd_monitor_hijo[1]);                  /* cierro la escritura */
                read(fd_monitor_hijo[0], buffer_3, leido);

                contar_palabras(buffer_3, leido, fd_hijo_monitor);
                // exit(EXIT_SUCCESS);
            }
        }
    }

    exit(EXIT_SUCCESS);
}

void calcular_resultado(int fd_monitor_padre[2], char *orden) {

    int leidos;
    char buffer[50];

    /* ********* */
    printf("\n----- En el padre -----\n");

    // close(fd_monitor_padre[1]);                             /* cierro la escritura */

    while ((leidos = read(fd_monitor_padre[0], buffer, sizeof buffer)) > 0) {
        // read(fd_monitor_padre[0], buffer, sizeof buffer);
        write(STDOUT_FILENO, buffer, leidos);
    }
}
