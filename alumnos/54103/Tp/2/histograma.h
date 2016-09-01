#ifndef _histograma_h_
#define _histograma_h

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <getopt.h>
#include<sys/wait.h>

int main (int , char**);
int parametros (char*,char*,char*,char*);
int * master (int , char*);
int * contador(int , int *);
int romper (char*, int );


#endif 
