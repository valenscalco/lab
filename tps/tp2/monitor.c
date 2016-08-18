#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "servicio.h"
#include "monitor.h"


int monitor(int *mp, int *ph, int *hm)
{
    char message[MAX_MSG];
    int counter[MAX_WORDLEN];
    int i;
    int key, value;
    int nread;
    int total=0;
    float avg=0.0;

	memset(counter, 0, sizeof counter);

	// se cierra lo que no se usa
    close(ph[0]);
    close(ph[1]);
    close(hm[1]); // escritura hijos y monitor
    close(mp[0]); // lectura entre monitor y padre

    // leo desde los hijos
    memset(message, 0, sizeof message);
    while ((nread = read(hm[0], message, sizeof message)) > 0) {
        /*  
         *  parsea el mensaje para incrementar los contadores
         *  key: cant de letras de la palabra
         *  value: contador de palabras de x cant de letras
         */
        sscanf(message, "%d:%d", &key, &value);
        counter[key] += value;
        total += value;
    }

    for (i=0; i < MAX_WORDLEN; i++) {
        if (counter[i] == 0)
            continue;

        avg = ((float)counter[i] / (float)total) * 100.0;

        // escribo al padre
        memset(message, 0, sizeof message);
        snprintf(message, sizeof message, "%d:%d:%.2f", i+1, counter[i], avg);
        write(mp[1], message, sizeof message);
    }

#ifdef DEBUG      
    printf("TOTAL: %d palabras\n", total);
#endif    

    memset(message, 0, sizeof message);
    snprintf(message, sizeof message, "total=%d", total);
    write(mp[1], message, sizeof message);

    // no es nesario, pero queda prolijo :-)
    close(mp[1]);
    close(hm[0]);
	return 0;
}
