#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "servicio.h"


int servicio(int *mp, int *ph, int *hm)
{
	char *token=NULL;
	const char *delim = " !?¿¡!.,;:()-_\t\r\n";
	int wordlen=0, nread;
	char line[MAX_LINE];
    char message[MAX_MSG];
    int counter[MAX_WORDLEN];
    int i;

	memset(line, 0, sizeof line);
	memset(counter, 0, sizeof counter);

	// se cierra lo que no se usa
	close(mp[0]); // escritura entre monitor y padre
	close(mp[1]);
	close(ph[1]); // escritura entre padre y hijos
	close(hm[0]); // lectura entre hijos y monitor

	do {
		memset(line, 0, sizeof line);
        nread = read(ph[0], line, sizeof line);

        // parsea palabras */    
		for (token=strtok(line, delim); 
				token != NULL; 
				token=strtok(NULL, delim))
		{
            wordlen = strlen(token);
#ifdef DEBUG           
            printf("word: %s\n", token);
#endif           
            if (wordlen > MAX_WORDLEN) {
                printf("La palabra %s contiene más de %d caracteres!\n", token, MAX_WORDLEN);
                continue;
            }
            counter[wordlen-1]++;
		}
	} while (nread > 0);

    for (i=0; i < MAX_WORDLEN; i++) {
        if (counter[i] == 0)
            continue;

        // escribe al monitor
        memset(message, 0, sizeof message);
        snprintf(message, sizeof message, "%d:%d", i+1, counter[i]);
        write(hm[1], message, sizeof message);
    }

	close(ph[0]);
	close(hm[1]);
	return 0;
}
