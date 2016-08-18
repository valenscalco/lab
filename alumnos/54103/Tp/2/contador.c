#include "histograma.h"


int* contador (int valor , int* aux ){
	int z,g,temp;
	
	if(valor==1){
		for(z=0; z<(20-1); z++){
			for (g=z+1; g<20; g++){
				if(aux[g]< aux[z]){
					temp=aux[g];
					aux[g]=aux[z];
					aux[z]=temp;
					
				}				
			}	
		}	
	} else if (valor ==0){
		for(z=0; z<(20-1); z++){
               		for (g=z+1; g<20; g++){
                        	if(aux[g]>aux[z]){
                                	temp=aux[g];
                                        aux[g]=aux[z];
                                        aux[z]=temp;
					
                               	}
                       	}
               	}
             } 			
	
return aux;
	

}
