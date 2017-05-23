#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "proc.h"
#include "parser.h"


void hijoA(int *pfd)
{
    char buf[80];
    int nread;
    int count = 0;

    memset(buf, 0, sizeof buf);
    close(pfd[1]);

    while ((nread = read(pfd[0], &buf, 80)) > 0) {
        count += count_w(buf);
    }

    printf("hijoA(): %d\n", count);

    close(pfd[0]);
    exit(0);
}

void hijoB(int *pfd)
{
    char buf[80];
    int nread;
    int count = 0;

    memset(buf, 0, sizeof buf);
    close(pfd[1]);

    while ((nread = read(pfd[0], &buf, 80)) > 0) {
        count += count_w(buf);
    }

    printf("hijoB(): %d\n", count);

    close(pfd[0]);
    exit(0);
}

int launchProc(int nh, int *pfd)
{
    void (*func)(int *pd);

    switch(fork()) {
    case 0:
        func = nh == 0 ? hijoA : hijoB;
        func(pfd);
        return 0;

    case -1:
        perror("fork()");
        return -1;
    }

    return 0;
}

