#include <stdio.h>
#include <string.h> 
#define SIZE 3

int main (int argc, char **argv)
{
    char str[SIZE] ={'0','3','3'};
    char * pch;
    int i;
    //for (i=0;i<SIZE;i++){
    //printf ("Looking for the 2 character in \"%s\"...\n",str[i]);
    //}

    pch=strchr(str,'3');
    while (pch!=NULL)
    {
        printf ("found at %d\n",pch-str+1);
        pch=strchr(pch+1,'3');
    }
    return 0;
}
