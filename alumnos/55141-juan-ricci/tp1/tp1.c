#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
	int pal = 0, orac = 0, caresp = 0;
	int i;
	char buff[10];
 
	while (read(0,buff,10) > 0){
		for(i=0;i<=10;i++){ //recorre el buffer
			if (buff[i] == ' ' || buff[i] == '.'){
				pal++;}
			if (buff[i] == '.') {
				orac++;}
			if (buff[i] == '\303'){
				caresp++;}
		}
	}
	printf("-->Hay %d palabras en el texto.\n",pal);
        printf("-->Hay %d oraciones.\n",orac);
        printf("-->Hay %d caracteres especiales.\n",caresp);

        return 0;
}
