#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "proc.h"


int main(int argc, char **argv)
{
    char buffer[80];
    int nread;
    int pfd[2][2];

    for (int i=0; i<2; i++) {
        pipe(pfd[i]);
        launchProc(i, pfd[i]);
    }

    close(pfd[0][0]);
    close(pfd[1][0]);

    do {
        memset(buffer, 0, sizeof buffer);
        nread = read(STDIN_FILENO, buffer, sizeof buffer);
        write(pfd[0][1], buffer, nread);
        write(pfd[1][1], buffer, nread);
    } while (nread > 0);

    close(pfd[0][1]);
    close(pfd[1][1]);
    return 0;
}

