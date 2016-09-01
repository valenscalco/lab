#include <unistd.h>
void main() 
{
	char buff[80];
	read(STDIN_FILENO, buff, sizeof buff);
	printf("%s", buff);
}
