#include "tp2.h"



int main(int argc, char *argv[]){
	
	if(argc == 5){
		c_getopt(argc,argv);
	}else if(argc == 3){
		c_cat(argc,argv);		

	}	

	return 0;
}

