/*
 * Computación II: TP2: Comunicación entre procesos con pipes.
 * <federico.hernandez@um.edu.ar>
 * <carlos.taffernaberry@um.edu.ar>
 */
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

#include "servicio.h"
#include "monitor.h"


int main(int argc, char **argv)
{
	int i, nread=0;
	int ph[2];	// comunicación padre - hijos
	int hm[2];	// comunicación	hijos - monitor
	int mp[2];	// comunicación	monitor - padre
	char line[MAX_LINE];
    char message[MAX_MSG];
    int wordlen, count, total;
    float avg;

	if (pipe(ph)) {
		perror("pipe(ph)");
		return 1;
	}

	if (pipe(hm)) {
		perror("pipe(hm)");
		return 1;
	}

	if (pipe(mp)) {
		perror("pipe(mp)");
		return 1;
	}

	// Se lanza hijo de control (monitor). Importante lanzarlo primero !!!
	switch (fork()) {
	case -1:
		perror("fork(monitor)");
		return 2;

	case 0:	// monitor
        monitor(mp, ph, hm);
        return 0;
	}

	// se lanzan los hijos
	// cambiar el harcoded de 3 por argv !!!
	for (i=0; i < 3; i++) {
		switch (fork()) {
		case -1:
			perror("fork(hijos)");
			return 2;

		case 0:	/* hijos */
			servicio(mp, ph, hm);
            return 0;
		}
	}

	// padre
	close(hm[0]); // pipe entre hijos y monitor
	close(hm[1]);
	close(mp[1]); // escritura entre monitor y padre
	close(ph[0]); // lectura entre padre y hijos

	// lee del stdin y se lo envía a los hijos
	do {
	    memset(line, 0, sizeof line);
        nread = read(STDIN_FILENO, line, sizeof line);
		write(ph[1], line, sizeof line);
	} while (nread > 0);

	// IMPORTANTISIMOOOOO
	close(ph[1]);

    // lee del hijo monitor
    memset(message, 0, sizeof message);
	while ((nread = read(mp[0], message, sizeof message)) > 0) {
        //write(STDOUT_FILENO, message, nread);
        //printf("\n");
        
        if (sscanf(message, "%d:%d:%f", &wordlen, &count, &avg) == 3) {
            printf("%d palabras de %d caracteres - %0.2f %%\n", wordlen, count, avg);
        } else {             
            sscanf(message, "total=%d", &total);
            printf("total: %d palabras\n", total);
        }

        memset(message, 0, sizeof message);
    }

	// no es nesario, pero queda prolijo
	close(mp[0]);

	/* 
     * Para asegurarme que terminan todos.
	 * Si nadie escribe en el stdout() excepto el padre, no hay problemas.
	 */
	wait(NULL);
	wait(NULL);
	wait(NULL);
	wait(NULL);
	return 0;
}
