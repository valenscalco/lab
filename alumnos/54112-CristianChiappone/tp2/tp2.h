#ifndef _tp2_h_
#define _tp2_h

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <getopt.h>
#include<sys/wait.h>
#include <ctype.h>
#include <locale.h>


int main(int , char**);
void c_getopt(int , char**);
void c_cat(int , char**);
#endif 

//compilacion: gcc -o tp2 tp2.h main.c c_getopt.c c_cat.c

