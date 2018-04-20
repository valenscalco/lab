#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
    char buffer[80];
    int nread;

    do {
        memset(buffer, 0, sizeof buffer);
        nread = read(STDIN_FILENO, buffer, sizeof buffer);
        write(STDOUT_FILENO, buffer, nread);
    } while (nread > 0);

    return 0;
}

