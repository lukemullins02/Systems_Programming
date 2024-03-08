#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void decompress(int a, char** b){ 

  if(a >= 0){

    int h = atoi(b[2]);
    int k = 3;

    // Loops through arguments provided by user
    for(int i = 0; i < a-1 && k < a; i++){       

       long int x = atol(b[k]);
       long int quotient = x;
       long int remainder = 0;
       int bit[8] = {0};
       int bitIndex = 0;  

       // Converts to binary   
    for(int i = 7; i >= 0; i--){
       remainder = quotient % 2;
       quotient = quotient/2;
       bit[i] = remainder;
       bitIndex++;
    }

    char store[10 & 11] = {0};

    int j = 0;

    // Stores DNA string 
    for(int i = 0; i < h; i++){
       if((bit[j] == 0) && (bit[j+1] == 0)){
	 store[i] = 'A';
       }
       else if((bit[j] == 0) && (bit[j+1] == 1)){
         store[i] = 'T';
       }
       else if((bit[j] == 1) && (bit[j+1] == 0)){
         store[i] = 'C';            
       }
       else if((bit[j] == 1) && (bit[j+1] == 1)){
         store[i] = 'G';
	}
	 j = j+2;
     }


    // Prints out DNA string 
     for(int i = 0; i < 4; i++){
       printf("%c", store[i]);
     }
     
     h = h-4;    
     k++;
     
    }

    
  }

}
