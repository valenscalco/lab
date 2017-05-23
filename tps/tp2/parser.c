#include <string.h>

#include "parser.h"

int count_w(char *line)
{
    char *tok;
    char *delim = " ";
    int count = 0;

    for (tok = strtok(line, delim);
            tok != NULL;
            tok = strtok(NULL, delim), count++);

    return count;
}
