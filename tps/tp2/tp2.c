#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hijoA(int *pfd);
void hijoB(int *pfd);

int launchProc(int nh, int *pfd);

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

void hijoA(int *pfd)
{
    char buf[80];
    int nread;

    memset(buf, 0, sizeof buf);
    close(pfd[1]);

    while ((nread = read(pfd[0], &buf, 80)) > 0) {
        write(STDOUT_FILENO, &buf, nread);
    }

    close(pfd[0]);
    exit(0);
}

void hijoB(int *pfd)
{
    char buf[80];
    int nread;

    memset(buf, 0, sizeof buf);
    close(pfd[1]);

    while ((nread = read(pfd[0], &buf, 80)) > 0) {
        write(STDOUT_FILENO, &buf, nread);
    }

    close(pfd[0]);
    exit(0);
}

