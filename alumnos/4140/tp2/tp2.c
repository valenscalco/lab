/*
 * Computación II: TP2: Comunicación entre procesos con pipes.
 * <carlos.taffernaberry@um.edu.ar>
 * <federico.hernandez@um.edu.ar>
 */

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "servicio.h"

int main(int argc, char **argv) {

    int hijos;
    int opcion;
    char *orden;
    int fd_monitor_padre[2];

    /* ********* */

    while ((opcion = getopt(argc, argv, "n:o:")) != -1) {
        switch (opcion) {
            case 'n':
                hijos = atoi(optarg);
                break;
            case 'o':
                orden = optarg;
                break;
            default:
                printf("Modo de uso: \n ./tp2 -n <nro_hijos> -o d (<d> de  mayor a menor, <a> de menor a mayor)\n");
                return 0;
        }
    }

    if (pipe(fd_monitor_padre) < 0) {
        perror("pipe(fd_monitor_padre)\n");
        exit(EXIT_FAILURE);
    }

    lanzar_hijos(hijos, fd_monitor_padre);

    calcular_resultado(fd_monitor_padre, orden);

    exit(EXIT_SUCCESS);
}
