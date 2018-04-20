#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main ()
{
	char buffer[16384];
	char buffer2[16384];
	char buffer3[16384];

	char * pch;
	char * pch2;
	char * pch3;

	int palabras = 0;
	int oraciones = 0;
	int especiales = 0;


	while (read(STDIN_FILENO, buffer, sizeof(buffer))>0){


		strcpy(buffer2, buffer);
		strcpy(buffer3, buffer);


		//memcpy(buffer2, buffer, sizeof(buffer));
		//memcpy(buffer3, buffer, sizeof(buffer));

			
		pch = strtok (buffer," ,.-\n");
		while (pch != NULL)
	  {

	  	pch = strtok (NULL, " ,.-\n");
		palabras++;
	  }


	  pch2 = strtok (buffer2,".");
		while (pch2 != NULL)
	  {
		pch2 = strtok (NULL, ".");
		oraciones++;
	  }


		pch3 = strtok (buffer3,"á");
		while (pch3 != NULL)
	  {
	  	pch3 = strtok (NULL, "á");
		especiales++;
	  }

}

	printf("palabras: %d\n", palabras);
	printf("oraciones: %d\n", oraciones);
	printf("especiales: %d\n", especiales);
	return 0;
}